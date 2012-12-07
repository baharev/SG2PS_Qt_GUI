// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QtGlobal>
#include <QMap>
#include <QVector>
#include <QString>

#include "GUISettings.hpp"
#include "ErrorMsg.hpp"

namespace {

const char EDITOR[] =
#if defined _WIN32
        "notepad"
#elif (defined __linux__)
        "kate"
#else
        #error Define your text editor
#endif
;

// TODO Clean up this mess: decorate filename with /root,?
const char FILE_MANAGER[] =
#if defined _WIN32
        "explorer /root," // Otherwise a malformed window pops up
#elif (defined __linux__)
        "konqueror " // The space is important, due to Windows quirks...
#else
        #error Define your file manager
#endif
;

}

struct Pair {
    Pair() { }
    Pair(const QStringList& fields) : key(fields.at(0)), value(fields.at(1)) { }
    QString key;
    QString value;
};

typedef QMap<QString,QString> Map;

GUISettings::GUISettings()
    :   strOptions(*new Map()),
    userOptions(*new QVector<Pair>)
{

    strOptions["executable_name"]  = "sg2ps";

    strOptions["start_browsing_from_directory"] = QDir::homePath();

    strOptions["text_editor"] = EDITOR;

    strOptions["file_manager"] = FILE_MANAGER;

    strOptions["show_logfile"] = "yes"; // TODO Stringly typed...

    strOptions["show_result_directory"] = "yes";

    qDebug() << "Current path: " << QDir::currentPath();
}

GUISettings::~GUISettings() {

    delete &strOptions;

    delete &userOptions;
}

void GUISettings::readSettings() {

    userOptions.clear();

    readPairs();

    foreach (Pair option, userOptions) {

        setValue(option.key, option.value);
    }
}

void GUISettings::setValue(const QString& key, const QString& value) {

    Map::iterator it = strOptions.find(key);

    if (it==strOptions.end()) {

         errorKeyNotFound(key);
    }
    else {

        qDebug() << key << value;

        it.value() = value;
    }
}


QString GUISettings::getStrOption(const QString& key) const {

    Map::const_iterator it = strOptions.find(key);

    if (it==strOptions.end()) {

        errorKeyNotFound(key);

        return "";
    }
    else {

        return it.value();
    }
}

void GUISettings::errorKeyNotFound(const QString& key) const {

    showError("key \"" + key + "\" not found");
}

void GUISettings::showError(const QString &what) const {

    showErrorMsg(what);

    // TODO Exit here?
}

void GUISettings::readPairs() {

    QFile file("settings.txt");

    if(!file.open(QIODevice::ReadOnly)) {

        qDebug() << "Settings file not found!";

        return;
    }

    QTextStream in(&file);

    while(!in.atEnd()) {

        const QString origLine = in.readLine();

        QString line = removeComment(origLine);

        line = line.trimmed();

        if (line.isEmpty()) {

            continue;
        }

        QRegExp rx("(\\w+)(\\s+)(.+)");

        int pos = rx.indexIn(line);

        if (pos > -1) {

            Pair opt;

            opt.key   = rx.cap(1);
            opt.value = rx.cap(3);

            userOptions.push_back(opt);
        }
        else {

            showError("reading line \""+origLine+"\"");

            break;
        }
    }

    file.close();
}

QString GUISettings::removeComment(const QString &origLine) {

    return origLine.left( origLine.indexOf('#') );
}
