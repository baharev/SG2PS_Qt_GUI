// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QString>
#include "Launcher.hpp"
#include "ErrorMsg.hpp"
#include "GlobalSettings.hpp"

void openInTextEditor(const QString& fileName) {

    QString nativeFileName = QDir::toNativeSeparators(fileName);

    QString editor = opts().getTextEditor();

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

    QString file_manager = opts().getFileManager();

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

void handle_missing_pdf_viewer() {

    QMessageBox mbox(QMessageBox::Critical, "Error",
                     "Error: failed to find the application that could open pdf files!\n"
                     "Try to download such an application now?",
                     QMessageBox::Yes | QMessageBox::No);

    int ret = mbox.exec();

    if (ret==QMessageBox::Yes) {

        openWithDefaultApp("http://get.adobe.com/reader/");
    }
}

void openPDF(const QString& fileName) {

    QString nativeFileName = QDir::toNativeSeparators(fileName);

    QString pdf_viewer = opts().getPdfViewer();

    if (pdf_viewer.isEmpty() || !QProcess::startDetached(pdf_viewer+" " +nativeFileName)) {

        bool success = openWithDefaultApp(nativeFileName);

        if (!success) {

            handle_missing_pdf_viewer();
        }
    }
}

void handle_missing_spreadsheet_editor() {

    // TODO Make sure the Manual actually has such a section
    // TODO Try to resolve it on loading the applicaton,
    // somewhat ugly that it occurs later on demand

    showErrorMsg("could not find the default application associated with spreadsheet documents. "
                 "Please read the manual under <b>Editing data files</b>");
}

bool canOpenSpreadsheet() {

    return (canOpenFileExtension(L".xls")); // .csv is often associated with the text editor

}

bool openSpreadsheetWithDefault(const QString& nativeFileName) {

    if (canOpenSpreadsheet()) {

        qDebug() << "Attempting to open " << nativeFileName << " with default application";

        return openWithDefaultApp(nativeFileName);
    }
    else {

        handle_missing_spreadsheet_editor();

        return false;
    }
}

bool openSpreadsheetWithUserSpecified(const QString& spreadsheet, const QString& nativeFileName) {

    QStringList args;

    QString flag = opts().getSpreadsheetFlag();

    if (!flag.isEmpty()) {

        args.append(flag);
    }

    args.append( nativeFileName );

    qDebug() << "Attempting to execute " << spreadsheet << "   " << args;

    return QProcess::startDetached(spreadsheet, args);
}

bool openSpreadsheet(const QString& file) {

    QString spreadsheet = opts().getSpreadsheet();

    QString nativeFileName = QDir::toNativeSeparators( file );

    if (spreadsheet.isEmpty()) {

        return openSpreadsheetWithDefault(nativeFileName);
    }
    else {

        return openSpreadsheetWithUserSpecified(spreadsheet, nativeFileName);
    }
}

QString run_back_end_with(const char flag[]) {

    QProcess p;

    QStringList args(flag);

    p.start( opts().getExecutableName(), args );

    bool success = p.waitForFinished(3000);

    return success ? QString(p.readAllStandardOutput()) : QString();
}

QString back_end_was_built_on() {

    QString version = run_back_end_with("-v");

    return version.isEmpty() ? QString("(failed to find it)\n") : version;
}

QString version_id_of_back_end() {

    QString id = run_back_end_with("--version-id");

    return id.isEmpty() ? QString("unknown") : id;
}

bool isPdfViewerOK() {

    // TODO Not clear what to do if the user did not accept
    // the GS licence that comes with the program

    if (opts().hasDefinedPdfViewer()) {

        return true; // and hope it is OK...
    }
    else if (canOpenFileExtension(L".pdf")) {

        return true;
    }
    else {

        qDebug() << "Neither defined, nor associated pdf viewer!";

        handle_missing_pdf_viewer();

        return false;
    }
}

bool isSpreadsheetOK() {

    if (opts().hasDefinedSpreadsheet()) {

        return true; // and hope it is OK...
    }
    else if (canOpenSpreadsheet()) {

        // TODO On Linux it is not OK, the user must define it anyway
        // because .rgf is likely to be mapped to the text editor but we check
        // for the .xls extension... :(

        return true;
    }
    else {

        qDebug() << "Neither defined, nor associated app for editing CSV files!";

        handle_missing_spreadsheet_editor();

        return false;
    }
}

bool isBackendOK() {

    QString id = run_back_end_with("--version-id");

    if (id.isEmpty()) {

        showErrorMsg("failed to start command line backend sg2ps");

        return false;
    }
    else {

        return true;
    }
}

bool isInstalledSoftwareOK() {

    bool pdfOK = isPdfViewerOK();

    bool spreadsheetOK = isSpreadsheetOK();

    bool backendOK = isBackendOK();

    return pdfOK && spreadsheetOK  && backendOK;
}
