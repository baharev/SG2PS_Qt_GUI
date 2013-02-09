// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QPushButton>
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
:   QWidget(parent)
{

    layout = new QHBoxLayout(this);



    runButton = new QPushButton(RUN);

    QFontMetrics fontMetrics = runButton->font();

    runButton->setMinimumWidth(fontMetrics.width(RUNNING)*1.5);

    connect(runButton, SIGNAL(clicked()), SLOT(runButtonClicked()));

    layout->addStretch(1);

    layout->addWidget(runButton);

    layout->addStretch(1);


    processManager = new ProcessManager(this);

    converter = new ConvertAllEps(this, mainWindowStatusBar);


    connect(processManager, SIGNAL(runFinished(bool,QString)), SLOT(onRunFinished(bool,QString)));

    connect(processManager, SIGNAL(runStarted()), SLOT(onRunStarted()));

    connect(converter, SIGNAL(finished()), SLOT(onConversionFinished()));
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

        onConversionFinished();
    }
}

void Runner::onConversionFinished() {

    runButton->setText(RUN);

    runButton->setEnabled(true);

    qDebug() << "Button enabled!";

    showResultDir();
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
