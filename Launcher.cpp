// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QString>
#include "Launcher.hpp"
#include "GlobalSettings.hpp"
#include "ErrorMsg.hpp"

QString getAssociatedApp(const wchar_t* extension, const wchar_t* word = L"open");

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

void openSpreadsheet(const QString& file) {

    QString spreadsheet = opts().getSpreadsheet();

    if (spreadsheet.isEmpty()) {

        spreadsheet = getAssociatedApp(L".xls");
    }

    if (spreadsheet.isEmpty()) {

        // TODO Make sure the Manual actually has such a section
        // TODO Try to resolve it on loading the applicaton,
        // somewhat ugly that it occurs later on demand

        showErrorMsg("could not find the default application associated with spreadsheet documents. "
                     "Please read the manual under <b>Editing data files</b>");
        return;
    }

    QStringList args;

    QString flag = opts().getSpreadsheetFlag();

    if (!flag.isEmpty()) {

        args.append(flag);
    }

    args.append( QDir::toNativeSeparators(file) );

    QProcess::startDetached(spreadsheet, args);

}

QString run_back_end_with(const char flag[]) {

    QProcess p;

    QStringList args(flag);

    p.start( opts().getExecutableName(), args );

    bool success = p.waitForFinished(3000);

    return success ? QString(p.readAllStandardOutput()) : QString();
}

QString back_end_version() {

    QString version = run_back_end_with("-v");

    return version.isEmpty() ? QString("(failed to find it)\n") : version;
}

QString back_end_version_id() {

    QString id = run_back_end_with("--version-id");

    return id.isEmpty() ? QString("unknown") : id;
}
