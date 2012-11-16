#include "InputWidget.hpp"


namespace {

const char SELECT_FILE_TEXT[] = "Select .rgf file";

const char FILE_NAME[] = "(No file selected)";


}


InputWidget::InputWidget(HandleSelectedFile* input_handler, QWidget* parent)
:
    QWidget(parent),
    input_handler(input_handler)
{

    selectButton = new QPushButton(SELECT_FILE_TEXT);

    QFontMetrics fontMetrics(selectButton->font());

    selectButton->setMinimumWidth(1);

    selectButton->resize(fontMetrics.width(SELECT_FILE_TEXT), selectButton->height());

    connect(selectButton, SIGNAL(clicked()), SLOT(showSelectFileDialog()));



    fileNameLabel = new QLabel(FILE_NAME);

    fileNameLabel->setAlignment(Qt::AlignRight);


    fileSelectLayout = new QHBoxLayout;

    fileSelectLayout->setMargin(10);

    fileSelectLayout->setSpacing(10);

    fileSelectLayout->addWidget(selectButton);

    fileSelectLayout->addWidget(fileNameLabel);

    fileSelectLayout->addStretch();

    setLayout(fileSelectLayout);


    dialog = new QFileDialog(this);

    startDir = QDir::homePath();
}

void InputWidget::showSelectFileDialog() {

    filePath = dialog->getOpenFileName(this, "Open File", startDir, "*.rgf (*.rgf *.set)");

    QFileInfo finfo(filePath);

    if (finfo.exists() && finfo.suffix()=="rgf") {

        startDir = finfo.absolutePath();

        fileNameLabel->setText(filePath);
    }
}
