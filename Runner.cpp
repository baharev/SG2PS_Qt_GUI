#include <QFileInfo>
#include <QHBoxLayout>
#include <QPushButton>
#include "Runner.hpp"
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

    connect(processManager, SIGNAL(finished(bool,QString)), SLOT(finished(bool,QString)));
}

void Runner::inputFileSelected(const QString& name) {

    QFileInfo file(name);

    workingDirectory = file.absolutePath();

    fileName = file.fileName();

}

QString Runner::croppedFileName() const {

    if (fileName.size() > 4) {

        return fileName.left(fileName.size()-4);
    }

    return fileName;
}

void Runner::runButtonClicked() {

    if (workingDirectory.isEmpty()) {

        // TODO Show error: select input first
        return;
    }

    QStringList args;

    args.append(croppedFileName());

    // TODO Set up logging!

    ExeCall::Status status = processManager->run(workingDirectory, args);

    if (status == ExeCall::OK) {

        runButton->setText(RUNNING); // TODO Wrap up

        runButton->setDisabled(true);
    }
}

void Runner::finished(bool success, const QString& errorMsg) {

    // TODO Call global MsgBox to display errors, if any

    runButton->setText(RUN); // TODO Wrap up

    runButton->setEnabled(true);
}
