// Copyright (C) 2012-2015, Ali Baharev
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


struct Pair {
    Pair() { }
    Pair(const QStringList& fields) : key(fields.at(0)), value(fields.at(1)) { }
    QString key;
    QString value;
};

typedef QMap<QString,QString> Map;

GUISettings::GUISettings() : strOptions(*new Map()) {

    strOptions[executable_name()]  = "sg2ps";

    strOptions[eps2pdf_converter()] = "ps2pdf";

    strOptions[start_browsing_from_directory()] = QDir::homePath();

    strOptions[text_editor()] = QString();

    strOptions[file_manager()] = QString();

    strOptions[convert_to_pdf()] = "yes"; // TODO Stringly typed...

    strOptions[delete_eps_on_success()] = "yes";

    strOptions[show_logfile()] = "yes";

    strOptions[show_result_directory()] = "yes";

    strOptions[pdf_viewer()] = QString();

    strOptions[spreadsheet()] = QString();

    strOptions[spreadsheet_flag()] = QString();

    qDebug() << "Current path: " << QDir::currentPath();
}

GUISettings::~GUISettings() {

    delete &strOptions;
}

QString GUISettings::getSettingsFileName() const {

    return "settings.txt";
}

QString GUISettings::executable_name() const {

    return "executable_name";
}

QString GUISettings::getExecutableName() const {

    return getStrOption(executable_name());
}

QString GUISettings::eps2pdf_converter() const {

    return "eps2pdf_converter";
}

QString GUISettings::getEps2PdfConverter() const {

    return getStrOption(eps2pdf_converter());
}

QString GUISettings::start_browsing_from_directory() const {

    return "start_browsing_from_directory";
}

QString GUISettings::getStartBrowsingFromDirectory() const {

    return getStrOption(start_browsing_from_directory());
}

QString GUISettings::text_editor() const {

    return "text_editor";
}

QString GUISettings::getTextEditor() const {

    return getStrOption(text_editor());
}

QString GUISettings::file_manager() const {

    return "file_manager";
}

QString GUISettings::getFileManager() const {

    return getStrOption(file_manager());
}

QString GUISettings::convert_to_pdf() const {

    return "convert_to_pdf";
}

bool GUISettings::getConvertToPdf() const {

    return getStrOption(convert_to_pdf()) == "yes";
}

QString GUISettings::delete_eps_on_success() const {

    return "delete_eps_on_success";
}

bool GUISettings::getDeleteEpsOnSuccess() const {

    return getStrOption(delete_eps_on_success()) == "yes";
}

QString GUISettings::show_logfile() const {

    return "show_logfile";
}

bool GUISettings::getShowLogfile() const {

    return getStrOption(show_logfile())=="yes";
}

QString GUISettings::show_result_directory() const {

    return "show_result_directory";
}

bool GUISettings::getShowResultDirectory() const {

    return getStrOption(show_result_directory())=="yes";
}

QString GUISettings::pdf_viewer() const {

    return "pdf_viewer";
}

QString GUISettings::getPdfViewer() const {

    return getStrOption(pdf_viewer());
}

QString GUISettings::spreadsheet() const {

    return "spreadsheet";
}

QString GUISettings::getSpreadsheet() const {

    return getStrOption(spreadsheet());
}

QString GUISettings::spreadsheet_flag() const {

    return "spreadsheet_flag";
}

QString GUISettings::getSpreadsheetFlag() const {

    return getStrOption(spreadsheet_flag());
}

bool GUISettings::hasDefinedPdfViewer() const {

    return !getPdfViewer().isEmpty();
}

bool GUISettings::hasDefinedSpreadsheet() const {

    return !getSpreadsheet().isEmpty();
}

void GUISettings::readSettings() {

    QVector<Pair> userOptions = readPairs();

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
}

QVector<Pair> GUISettings::readPairs() const {

    QVector<Pair> userOptions;

    QFile file(getSettingsFileName());

    if (file.open(QIODevice::ReadOnly)) {

        QTextStream in(&file);

        parseSettingsFile(in, userOptions);
    }
    else {

        qDebug() << "Settings file not found!";

        dumpSettings();
    }

    return userOptions;
}

void GUISettings::parseSettingsFile(QTextStream& in, QVector<Pair>& userOptions) const {

    QRegExp rx("(\\w+)(\\s+)(.+)");

    while(!in.atEnd()) {

        const QString origLine = in.readLine();

        QString line = removeComment(origLine).trimmed();

        if (line.isEmpty()) {

            continue;
        }

        int pos = rx.indexIn(line);

        if (pos > -1) {

            Pair opt;

            opt.key   = rx.cap(1);
            opt.value = rx.cap(3);

            userOptions.push_back(opt);
        }
        else {

            showError("reading line \""+origLine+"\"");
        }
    }
}

QString GUISettings::removeComment(const QString &origLine) const {

    return origLine.left( origLine.indexOf('#') );
}

void GUISettings::dumpSettings() const {

    QFile settings(getSettingsFileName());

    if (!settings.open(QIODevice::WriteOnly | QIODevice::Text)) {

        return;
    }

    QTextStream out(&settings);

    QMapIterator<QString,QString> i(strOptions);

     while (i.hasNext()) {

         i.next();

         if (i.value().isEmpty()) {

             out << "# " << i.key() << '\n';
         }
         else {

             out << i.key() << "\t\t" << i.value() << '\n';
         }
     }
}
