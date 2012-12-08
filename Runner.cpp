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

void Runner::inputFileSelected(const QString& name) {

    QFileInfo file(name);

    workingDirectory = file.absolutePath();

    fileName = file.fileName();

    logFile = "log.txt";
}

QString Runner::croppedFileName() const {

    if (fileName.size() > 4) {

        return fileName.left(fileName.size()-4);
    }

    return fileName;
}

void Runner::runButtonClicked() {

    if (workingDirectory.isEmpty()) {

        showErrorMsg("no input .rgf file selected yet");
        return;
    }

    emit generateSetFile();

    qDebug() << "Runner invokes external exe";

    QStringList args;

    args.append(croppedFileName());

    processManager->run(workingDirectory, args, logFile);
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

    if (getStrOption("show_logfile")=="yes") {

        openInTextEditor(workingDirectory+"/"+logFile);
    }
}

void Runner::showResultDir() const {

    if (getStrOption("show_result_directory")=="yes") {

        showInFileManager(workingDirectory);
    }
}

