// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDir>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>

#include "InputWidget.hpp"
#include "LayoutConstants.hpp"

namespace {

const char FILE_NAME[] = "(please create a new / load an existing file)";

}


InputWidget::InputWidget(QWidget* parent)
:
    QFrame(parent)
{

    fileNameFrame = new QFrame;

    fileNameLabel = new QLabel(FILE_NAME);

    QHBoxLayout* fileNameLayout = new QHBoxLayout(fileNameFrame);

    fileNameLayout->addWidget(fileNameLabel, 1);

    fileNameFrame->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);



    fileSelectLayout = new QHBoxLayout;

    fileSelectLayout->setMargin(MARGIN);

    fileSelectLayout->setSpacing(SPACING);

    fileSelectLayout->addWidget(fileNameFrame);

    //fileSelectLayout->addStretch(1);

    setLayout(fileSelectLayout);

    //setFrameStyle(QFrame::WinPanel | QFrame::Raised);

}

void InputWidget::freezeLabelSize() {

        fileNameFrame->setFixedWidth(fileNameFrame->width());
}

void InputWidget::newProjectSelected(const QString& newProjectPath, const QString& newProjectName) {

    projectPath = newProjectPath;

    projectName = newProjectName;

    fileNameLabel->setText("Project: <b>"+projectName+"</b>,  path: "+QDir::toNativeSeparators(projectPath));
}
