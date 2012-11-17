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

    connect(processManager, SIGNAL(finished(bool,QString)), SLOT(finished(bool,QString)));
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

    ExeCall::Status status = processManager->run(workingDirectory, args, logFile);

    if (status == ExeCall::OK) {

        disableButton();
    }
}

void Runner::finished(bool success, const QString& errorMsg) {

    if (!success) {

        showErrorMsg(errorMsg);
    }

    enableButton();

    QString editor = getStrOption("text_editor");

    QProcess::startDetached(editor+" "+workingDirectory+"/"+logFile);
}

void Runner::enableButton() {

    runButton->setText(RUN);

    runButton->setEnabled(true);
}

void Runner::disableButton() {

    runButton->setText(RUNNING);

    runButton->setDisabled(true);
}
