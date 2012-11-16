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



    layout->addWidget(runButton);

    layout->addStretch(1);



    processManager = new ProcessManager(this);
}

void Runner::runButtonClicked() {

    processManager->run();
}
