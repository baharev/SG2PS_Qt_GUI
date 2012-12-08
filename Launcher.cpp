// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDir>
#include <QDebug>
#ifdef _WIN32
#include <windows.h>
#include <ShellApi.h>
#include <QString>
#else
#include <QProcess>
#endif
#include "Launcher.hpp"
#include "GlobalSettings.hpp"

#ifdef _WIN32

void openWithDefaultApp(const QString& file) {

    ShellExecute(GetDesktopWindow(), L"open", (wchar_t*)file.utf16(), NULL, NULL, SW_SHOWNORMAL);

}

void openDirectoryWithFileManager(const QString& directory) {

    ShellExecute(GetDesktopWindow(), L"explore", (wchar_t*)directory.utf16(), NULL, NULL, SW_SHOWMAXIMIZED);
}

#else

void openWithDefaultApp(const QString& file) {

    QProcess::startDetached("xdg-open "+file);

}

void openDirectoryWithFileManager(const QString& directory) {

    openWithDefaultApp(directory);
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
