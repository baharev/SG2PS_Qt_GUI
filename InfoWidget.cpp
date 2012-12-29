// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QBoxLayout>
#include <QDir>
#include <QFileInfo>
#include <QLabel>
#include "InfoWidget.hpp"

namespace {

}

InfoWidget::InfoWidget(QWidget *parent) : QFrame(parent) {

    projectLabel = new QLabel("(please create / edit / select a file above)", this);

    projectLabel->setAlignment(Qt::AlignHCenter);


    rgfLabel = new QLabel(this);

    setLabel = new QLabel(this);

    xyLabel = new QLabel(this);


    hboxLayout = new QHBoxLayout(this);

    hboxLayout->addWidget(rgfLabel, 1);

    hboxLayout->addWidget(setLabel, 1);

    hboxLayout->addWidget( xyLabel, 1);


    vboxLayout = new QVBoxLayout(this);

    vboxLayout->addWidget(projectLabel);

    QWidget* dummy = new QWidget(this);

    dummy->setLayout(hboxLayout);

    vboxLayout->addWidget(dummy);


    setLayout(vboxLayout);

    setFrameStyle(QFrame::WinPanel | QFrame::Raised);
}

void InfoWidget::newProjectSelected(const QString& newProjectPath, const QString& newProjectName) {

    projectPath = newProjectPath;

    projectName = newProjectName;

    projectLabel->setText("Project: <b>"+projectName+"</b>,  path: "+QDir::toNativeSeparators(projectPath));

    updateRgfLabel();

    updateSetLabel();

    updateXyLabel();
}

bool InfoWidget::fileExists(const char extension[]) {

    QFileInfo finfo(projectPath+"/"+projectName+extension);

    return (finfo.exists() && finfo.isFile()) ? true : false;
}

QString InfoWidget::okText(const QString& msg) {

    return "<font style=\"background: #33FF00; color: black;\">"+msg+"</font>";
}

QString InfoWidget::warnText(const QString& msg) {

    return "<font style=\"background: #FFFF00; color: black;\">"+msg+"</font>";
}

QString InfoWidget::errorText(const QString& msg) {

    return "<font style=\"background: #FF0000; color: black;\">"+msg+"</font>";
}

void InfoWidget::updateRgfLabel() {

    if (fileExists(".rgf")) {

        rgfLabel->setText(okText("Data file found"));
     }
    else {

        rgfLabel->setText(errorText("Don\'t forget to create the data file!"));
    }
}

void InfoWidget::updateSetLabel() {

    if (fileExists(".set")) {

        setLabel->setText(okText("Settings have been checked"));
    }
    else {

        setLabel->setText(warnText("The settings below need your attention"));
    }
}

void InfoWidget::updateXyLabel() {

    if (fileExists(".xy")) {

        xyLabel->setText(okText("Coordinate file found"));
    }
    else {

        xyLabel->setText(warnText("Not using any coordinate file"));
    }
}


void InfoWidget::freezeLabelSize() {

    rgfLabel->setFixedSize(rgfLabel->size());
    setLabel->setFixedSize(setLabel->size());
     xyLabel->setFixedSize( xyLabel->size());

}
