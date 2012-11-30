// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QPushButton>
#include "Runner.hpp"
#include "ProcessManager.hpp"
#include "GlobalSettings.hpp"
#include "ErrorMsg.hpp"

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

    // TODO Move these below into there own class

    QString editor = getStrOption("text_editor");

    QProcess::startDetached(editor+" "+workingDirectory+"/"+logFile);

    QString file_manager = getStrOption("file_manager");

    QString cmd = file_manager+QDir::toNativeSeparators(workingDirectory);

    QProcess::startDetached(cmd);
}
