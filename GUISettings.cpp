#include <QDebug>
#include <QDir>
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

GUISettings::GUISettings() {

    strOptions["exe_name"]  = "sg2ps";

    strOptions["start_dir"] = QDir::homePath();

    strOptions["text_editor"] = EDITOR;

    qDebug() << QDir::currentPath();
}

void GUISettings::readSettings() {

    // TODO Read these from config file

    setValue("start_dir", "/home/ali/ws-juno/Test/");

    setValue("exe_name", "/home/ali/ws-juno/SG2PS/Debug/SG2PS");
}

void GUISettings::setValue(const QString& key, const QString& value) {

    QMap<QString,QString>::iterator it = strOptions.find(key);

    if (it==strOptions.end()) {

         errorKeyNotFound(key);
    }
    else {

        it.value() = value;
    }
}


QString GUISettings::getStrOption(const QString& key) const {

    QMap<QString,QString>::const_iterator it = strOptions.find(key);

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
