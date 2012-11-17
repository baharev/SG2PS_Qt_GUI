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
}

void Runner::inputFileSelected(const QString& name) {

    QFileInfo file(name);

    workingDirectory = file.absolutePath();

    fileName = file.fileName();
}

void Runner::runButtonClicked() {

    QStringList args;

    args.append(fileName);

    processManager->run(workingDirectory, args);
}
