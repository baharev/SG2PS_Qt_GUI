// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDir>
#include <QDebug>
#include <QProcess>
#include <QString>
#ifdef _WIN32
#include <windows.h>
#include <ShellApi.h>
#include <Shlwapi.h>
#endif
#include "Launcher.hpp"
#include "GlobalSettings.hpp"
#include "ErrorMsg.hpp"

#ifdef _WIN32

void openWithDefaultApp(const QString& file) {

    ShellExecute(GetDesktopWindow(), L"open", (wchar_t*)file.utf16(), NULL, NULL, SW_SHOWNORMAL);

}

void openDirectoryWithFileManager(const QString& directory) {

    ShellExecute(GetDesktopWindow(), L"explore", (wchar_t*)directory.utf16(), NULL, NULL, SW_SHOWMAXIMIZED);
}

QString getAssociatedApp(const wchar_t* extension, const wchar_t* word = L"open") {

    DWORD dwSize = 512;

    wchar_t appPath[512] = { 0 };

    HRESULT hr = AssocQueryStringW(ASSOCF_VERIFY,
                                   ASSOCSTR_EXECUTABLE,
                                   extension,
                                   word,
                                   appPath,
                                   &dwSize );

    QString app;

    switch (hr) {

    case S_OK:
        app = QString::fromWCharArray(appPath);
        app = QDir::toNativeSeparators(app);
        qDebug() << "Extension" << extension;
        qDebug() << "App" << app;
        break;
    case E_POINTER:
        qDebug() << "AssocQueryStringW" << "E_POINTER";
        break;
    case S_FALSE:
        qDebug() << "AssocQueryStringW" << "S_FALSE";
        break;
    default:
        qDebug() << "unknown: " << hr << endl;
    }

    return app;
}

#else

void openWithDefaultApp(const QString& file) {

    QProcess::startDetached("xdg-open "+file);

}

void openDirectoryWithFileManager(const QString& directory) {

    openWithDefaultApp(directory);
}

QString getAssociatedApp(const wchar_t* , const wchar_t* word = L"open") {

    if (word==word) { ;} // to make the compiler shut up

    return QString();

}

#endif

void openInTextEditor(const QString& fileName) {

    QString nativeFileName = QDir::toNativeSeparators(fileName);

    QString editor = getStrOption("text_editor");

    if (editor.isEmpty()) {

        openWithDefaultApp(nativeFileName);
    }
    else {

        bool success = QProcess::startDetached(editor+" " +nativeFileName);

        if (!success) {

            qDebug() << "user defined text_editor failed to start, calling default";

            openWithDefaultApp(nativeFileName);
        }
    }
}

void showInFileManager(const QString& directory) {

    QString nativeDirectory = QDir::toNativeSeparators(directory);

    QString file_manager = getStrOption("file_manager");

    if (file_manager.isEmpty()) {

        openDirectoryWithFileManager(nativeDirectory);
    }
    else {

        bool success = QProcess::startDetached(file_manager+" " +nativeDirectory);

        if (!success) {

            qDebug() << "user defined file_manager failed to start, calling default";

            openDirectoryWithFileManager(nativeDirectory);
        }
    }
}

void openPDF(const QString& fileName) {

    QString nativeFileName = QDir::toNativeSeparators(fileName);

    QString pdf_viewer = getStrOption("pdf_viewer");

    if (pdf_viewer.isEmpty()) {

        openWithDefaultApp(nativeFileName);
    }
    else {

        bool success = QProcess::startDetached(pdf_viewer+" " +nativeFileName);

        if (!success) {

            qDebug() << "user defined pdf_viewer failed to start, calling default";

            openWithDefaultApp(nativeFileName);
        }
    }
}

void openSpreadsheet(const QString& file) {

    QString spreadsheet = getStrOption("spreadsheet");

    if (spreadsheet.isEmpty()) {

        spreadsheet = getAssociatedApp(L".xls");
    }

    if (spreadsheet.isEmpty()) {

        // TODO Make sure the Manual actuall has such a section
        // TODO Try to resolve it on loading the applicaton,
        // somewhat ugly that it occurs later on demand

        showErrorMsg("could not find the default application associated with spreadsheet documents, "
                     "please read the manual under Editing RGF files");
        return;
    }

    QStringList args;

    QString flag = getStrOption("spreadsheet_flag");

    if (!flag.isEmpty()) {

        args.append(flag);
    }

    args.append( QDir::toNativeSeparators(file) );

    QProcess::startDetached(spreadsheet, args);

}
