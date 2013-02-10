// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifdef __linux__
#include <QDebug>
#include <QProcess>
#include <QString>
#include "Launcher.hpp"

bool openWithDefaultApp(const QString& file) {

    return QProcess::startDetached("xdg-open "+file);
}

void openDirectoryWithFileManager(const QString& directory) {

    openWithDefaultApp(directory);
}

QString getAssociatedApp(const wchar_t* , const wchar_t* word = L"open") {

    if (word==word) { ;} // to make the compiler shut up

    return QString();

}

#endif
