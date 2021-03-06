// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStatusBar>
#include <QVector>
#include "Runner.hpp"
#include "ConcatPdfs.hpp"
#include "ConvertAllEps.hpp"
#include "ErrorMsg.hpp"
#include "Launcher.hpp"
#include "GlobalSettings.hpp"
#include "ProcessManager.hpp"

namespace {

const char RUN[] = "&Run";

const char RUNNING[] = "Please wait...";

}

Runner::Runner(QWidget *parent, QStatusBar* mainWindowStatusBar)
:   QWidget(parent),
    statusBar(mainWindowStatusBar)
{

    layout = new QHBoxLayout(this);



    runButton = new QPushButton(RUN);

    QFontMetrics fontMetrics = runButton->fontMetrics();

    runButton->setMinimumWidth(fontMetrics.width(RUNNING)*1.5);

    runButton->setFocusPolicy(Qt::StrongFocus);

    connect(runButton, SIGNAL(clicked()), SLOT(runButtonClicked()));

    layout->addStretch(1);

    layout->addWidget(runButton);

    layout->addStretch(1);


    processManager = new ProcessManager(this);

    converter = new ConvertAllEps(this, mainWindowStatusBar);

    pdf_concat = new ConcatPdfs(this);


    connect(processManager, SIGNAL(runFinished(bool,QString)), SLOT(onRunFinished(bool,QString)));

    connect(processManager, SIGNAL(runStarted()), SLOT(onRunStarted()));

    connect(converter, SIGNAL(finished(bool)), SLOT(onConversionFinished(bool)));

    connect(pdf_concat, SIGNAL(finished(bool)), SLOT(onConcatFinished(bool)));
}

void Runner::newProjectSelected(const QString& newProjectPath,
                                        const QString& newProjectName)
{
    projectPath = newProjectPath;

    projectName = newProjectName;

    logFile = "log.txt";
}

void Runner::runButtonClicked() {

    QFileInfo rgfFile(projectPath+"/"+projectName+".rgf");

    if (!rgfFile.exists() || !rgfFile.isFile()) {

        showErrorMsg("the data file is not created or selected yet");
        return;
    }

    emit generateSetFile();

    qDebug() << "Runner invokes external exe";

    QStringList args;

    args.append(projectName);

    processManager->run(projectPath, args, logFile);
}

void Runner::onRunStarted() {

    runButton->setDisabled(true);

    runButton->setText(RUNNING);

    statusBar->showMessage("Running, please be patient...");

    qDebug() << "Button disabled!";
}

void Runner::onRunFinished(bool success, const QString& errorMsg) {

    if (!success) {

        showErrorMsg(errorMsg);
    }

    showLog();

    bool pointerToFolderOK = false;

    finalProjectFolder = dirToShow(pointerToFolderOK); // Side effect: always deletes the pointer

    if (pointerToFolderOK && opts().getConvertToPdf()) {

        converter->run(finalProjectFolder);  // calls onConversionFinished in the end
    }
    else {

        onConcatFinished(success && pointerToFolderOK);
    }
}

void Runner::onConversionFinished(bool ok) {

    if (ok) {

        statusBar->showMessage("Concatenating all PDF files"); // Hack: compare with MainWindow closeEvent()

        pdf_concat->run(finalProjectFolder, projectName);
    }
    else {
        onConcatFinished(ok);
    }
}

void Runner::onConcatFinished(bool ok) {

    runButton->setText(RUN);

    runButton->setEnabled(true);

    QString msg = ok ? QString("Done") : QString("Error occured");

    statusBar->showMessage(msg, 2000);

    qDebug() << "Button enabled!";

    showResultDir();

    showPdfIfDemo();
}

void Runner::showLog() const {

    if (opts().getShowLogfile()) {

        openInTextEditor(projectPath+"/"+logFile);
    }
}

void Runner::showResultDir() const {

    if (opts().getShowResultDirectory()) {

        showInFileManager(finalProjectFolder);
    }
}

void Runner::showPdfIfDemo() const {

    if (projectName!="demo") {
        return;
    }

    QVector<QString> demoPDFs = QVector<QString>();
    demoPDFs.append(finalProjectFolder+"/5_PS_SEPARATED/FRACTURE/WELL-1_FRACTURE.pdf");
    demoPDFs.append(finalProjectFolder+"/6_WELL_PS_SEPARATED/FRACTURE/WELL-1_FRACTURE_TILTED.pdf");

    foreach (QString demoPDF, demoPDFs) {
        qDebug() << "Trying to open demo pdf at" << demoPDF;
        if (QFile::exists(demoPDF))
            openPDF(demoPDF);
    }
}

QString Runner::dirToShow(bool& pointerToFolderOK) const {

    pointerToFolderOK = false;

    QString dir_to_show = projectPath;

    QFile file(projectPath+"/project_folder_name"); // TODO Another magic constant...

    if (file.open(QIODevice::ReadOnly)) {

        QString folder_name = projectPath + "/" +QTextStream(&file).readLine();

        if (folder_name.endsWith(projectName, Qt::CaseInsensitive) &&
            QFileInfo(folder_name).isDir())
        {
            dir_to_show =  folder_name;
            pointerToFolderOK = true;
        }
    }

    file.remove();

    return dir_to_show;
}
