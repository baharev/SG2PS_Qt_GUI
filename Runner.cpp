// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStatusBar>
#include "Runner.hpp"
#include "ConvertAllEps.hpp"
#include "ErrorMsg.hpp"
#include "Launcher.hpp"
#include "GlobalSettings.hpp"
#include "ProcessManager.hpp"

namespace {

const char RUN[] = "Run";

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

    connect(runButton, SIGNAL(clicked()), SLOT(runButtonClicked()));

    layout->addStretch(1);

    layout->addWidget(runButton);

    layout->addStretch(1);


    processManager = new ProcessManager(this);

    converter = new ConvertAllEps(this, mainWindowStatusBar);


    connect(processManager, SIGNAL(runFinished(bool,QString)), SLOT(onRunFinished(bool,QString)));

    connect(processManager, SIGNAL(runStarted()), SLOT(onRunStarted()));

    connect(converter, SIGNAL(finished(bool)), SLOT(onConversionFinished(bool)));
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

    args.append("-gui_calls");

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

        onConversionFinished(success && pointerToFolderOK);
    }
}

void Runner::onConversionFinished(bool done) {

    runButton->setText(RUN);

    runButton->setEnabled(true);

    QString msg = done ? QString("Done") : QString("Error occured");

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

    QString demoPDF = finalProjectFolder+"/5_ps_separated/STRIAE/ANG001_STRIAE_X.pdf";

    qDebug() << "Trying to open demo pdf at" << demoPDF;

    if (QFile::exists(demoPDF)) {

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
