// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QPushButton>
#include "Runner.hpp"
#include "ErrorMsg.hpp"
#include "Launcher.hpp"
#include "GlobalSettings.hpp"
#include "ProcessManager.hpp"


namespace {

const char RUN[] = "Run";

const char RUNNING[] = "Please wait...";

}

Runner::Runner(QWidget *parent)
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

    connect(processManager, SIGNAL(runFinished(bool,QString)), SLOT(onRunFinished(bool,QString)));

    connect(processManager, SIGNAL(runStarted()), SLOT(onRunStarted()));
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

        showErrorMsg("the RGF file is not created or selected yet");
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

    qDebug() << "Button disabled!";
}

void Runner::onRunFinished(bool success, const QString& errorMsg) {

    if (!success) {

        showErrorMsg(errorMsg);
    }

    runButton->setText(RUN);

    runButton->setEnabled(true);

    qDebug() << "Button enabled!";

    showResultDir();

    showLog();
}

void Runner::showLog() const {

    if (opts().getShowLogfile()) {

        openInTextEditor(projectPath+"/"+logFile);
    }
}

void Runner::showResultDir() const {

    if (opts().getShowResultDirectory()) {

        showInFileManager(projectPath);
    }
}

