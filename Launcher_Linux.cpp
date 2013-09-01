// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifdef __linux__
#include <QDebug>
#include <QMimeDatabase>
#include <QProcess>
#include <QString>
#include "Launcher.hpp"
#include "ErrorMsg.hpp"

bool openWithDefaultApp(const QString& file) {

    QString command("xdg-open "+file);

    bool success = QProcess::startDetached(command);

    if (!success) {

        showErrorMsg("failed to execute \""+command+"\"");
    }

    return success;
}

bool openWithAppAssoc(const QString& nativeFileName, const QString& extension) {

    qDebug() << "Extension" << extension << "ignored, opening with xdg-open instead";

    return openWithDefaultApp(nativeFileName);
}

bool openWithShortAppname(const QString& filename, const QString& appname, const QString& flag) {

    QStringList args;

    if (!flag.isEmpty()) {

        args.append(flag);
    }

    args.append(filename);

    qDebug() << "Attempting to execute" << appname << args;

    return QProcess::startDetached(appname, args);
}

void openDirectoryWithFileManager(const QString& directory) {

    openWithDefaultApp(directory);
}

QString getMimeTypeForExtension(const QString& extension) {

    QString file(QString::fromWCharArray(L"dummy") + extension);

    QMimeDatabase db;

    QMimeType mimeType = db.mimeTypeForFile(file, QMimeDatabase::MatchExtension);

    QString mime = mimeType.isDefault() ? QString() : mimeType.name();

    if (!mime.isEmpty()) {

        qDebug() << "Mime type for " << extension << " extension "
                 << "is " << mime;
    }
    else {

        qDebug() << "Only default mime type is found for " << extension;
    }

    return mime;
}

bool associatedAppExists(const QString& mime) {

    if (mime.isEmpty()) {

        return false;
    }

    QProcess p;

    QStringList args;

    args.append("query");

    args.append("default");

    args.append(mime);

    p.start("xdg-mime", args );

    bool success = p.waitForFinished(3000);

    QString defaultApp = success ? QString(p.readAllStandardOutput()) : QString();

    if (!success) {

        qDebug() << "The xdg-mime query timed out";

    }
    else if (defaultApp.isEmpty()) {

        qDebug() << "Apparently no associated app for " << mime;
    }
    else {

        qDebug() << "Associated app is " << defaultApp;
    }

    return !defaultApp.isEmpty();
}

bool hasAssociatedApp(const wchar_t* ext) {

    QString extension = QString::fromWCharArray(ext);

    qDebug() << "Looking for the associated app for extension " << extension;

    QString mime = getMimeTypeForExtension(extension);

    return associatedAppExists(mime);
}

#endif
