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

    strOptions["exe_name"]  = "sg2ps";

    strOptions["start_dir"] = QDir::homePath();

    strOptions["text_editor"] = EDITOR;

    qDebug() << QDir::currentPath();
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

    showError("key " + key + " not found");
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

        QString line = in.readLine();

        if (line.isEmpty() || line.startsWith('#')) {

            continue;
        }

        QStringList fields = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);

        if (fields.size()!=2) {

            showError("reading line \""+line+"\"");

            break;
        }

        userOptions.push_back(Pair(fields));
    }

    file.close();
}
