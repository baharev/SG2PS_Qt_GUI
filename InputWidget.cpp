// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>

#include "InputWidget.hpp"
#include "LayoutConstants.hpp"
#include "GlobalSettings.hpp"


namespace {

const char SELECT_FILE_TEXT[] = "Select .rgf file";

const char FILE_NAME[] = "(please create new / load existing *.rgf file)";

}


InputWidget::InputWidget(QWidget* parent)
:
    QFrame(parent),
    input_handler(input_handler)
{

    selectButton = new QPushButton(SELECT_FILE_TEXT);

    QFontMetrics fontMetrics(selectButton->font());

    selectButton->setMinimumWidth(fontMetrics.width(SELECT_FILE_TEXT)*1.5);

    // TODO Remove hack
    selectButton->hide();

    connect(selectButton, SIGNAL(clicked()), SLOT(showSelectFileDialog()));


    fileNameFrame = new QFrame;

    fileNameLabel = new QLabel(FILE_NAME);

    QHBoxLayout* fileNameLayout = new QHBoxLayout(fileNameFrame);

    fileNameLayout->addWidget(fileNameLabel, 1);

    fileNameFrame->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);



    fileSelectLayout = new QHBoxLayout;

    fileSelectLayout->setMargin(MARGIN);

    fileSelectLayout->setSpacing(SPACING);

    fileSelectLayout->addWidget(selectButton);

    fileSelectLayout->addWidget(fileNameFrame);

    //fileSelectLayout->addStretch(1);

    setLayout(fileSelectLayout);

    //setFrameStyle(QFrame::WinPanel | QFrame::Raised);



    dialog = new QFileDialog(this);

    startDir = getStrOption("start_browsing_from_directory");
}

void InputWidget::freezeLabelSize() {

        fileNameFrame->setFixedWidth(fileNameFrame->width());
}

void InputWidget::showSelectFileDialog() {

    filePath = dialog->getOpenFileName(this, "Select File", startDir, "*.rgf (*.rgf)");

    QFileInfo fileInfo(filePath);

    if (fileInfo.exists() && fileInfo.suffix()=="rgf") {

        startDir = fileInfo.absolutePath();

        fileNameLabel->setText(QDir::toNativeSeparators(filePath));

        emit inputFileSelected(filePath);
    }
}

void InputWidget::validRgfSelected(const QString& file) { // TODO Remove duplication

    QFileInfo fileInfo(file);

    startDir = fileInfo.absolutePath();

    fileNameLabel->setText(QDir::toNativeSeparators(file));
}

