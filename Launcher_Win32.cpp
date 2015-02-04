// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifdef _WIN32
#include <QDebug>
#include <QDir>
#include <QString>
#include <windows.h>
#include <ShellApi.h>
#include <Shlwapi.h>
#include "Launcher.hpp"

bool openWithDefaultApp(const QString& file) {

    int ret = (int) ShellExecute(GetDesktopWindow(), L"open", (wchar_t*)file.utf16(), NULL, NULL, SW_SHOWNORMAL);

    return ret > 32;
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
        qDebug() << "Extension" << QString::fromWCharArray(extension);
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

bool hasAssociatedApp(const wchar_t* ext) {

    QString extension = QString::fromWCharArray(ext);

    qDebug() << "Looking for the associated app for extension " << extension;

    QString app = getAssociatedApp(ext);

    return !app.isEmpty();
}

bool openWithShortAppname(const QString& nativeFilename, const QString& shortAppName, const QString& ) {

    QString file("\""+nativeFilename+"\"");

    qDebug() << "Attempting to execute command" << shortAppName << file;

    int ret = (int) ShellExecute(GetDesktopWindow(), L"open", (wchar_t*)shortAppName.utf16(), (wchar_t*)file.utf16(), NULL, SW_SHOWNORMAL);

    return ret > 32;
}

bool openWithAppAssoc(const QString& file, const QString& extension) {

    QString app = getAssociatedApp((const wchar_t*)extension.utf16());

    if (app.isEmpty()) {

        return false;
    }
    else {

        QString dummy; // TODO Default arg instead?

        return openWithShortAppname(file, app, dummy);
    }
}

#endif
