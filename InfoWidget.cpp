// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QBoxLayout>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QLabel>
#include "InfoWidget.hpp"
#include "LayoutConstants.hpp"

namespace {

const char GREEN[]  = "QLabel { background-color : #33FF00; }";
const char YELLOW[] = "QLabel { background-color : #FFFF00; }";
const char RED[]    = "QLabel { background-color : #FF0000; }";

}

InfoWidget::InfoWidget(QWidget *parent) : QFrame(parent) {

    projectLabel = new QLabel("Please create new or edit / select an existing file by clicking on one of icons above!", this);

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

    setFrameStyle(QFrame::Box | QFrame::Raised);
}

void InfoWidget::checkSetFile() {

    updateSetLabel();
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

void InfoWidget::setOkText(QLabel* lbl, const QString& msg) {

    lbl->setText(msg);

    lbl->setStyleSheet(GREEN);
}

void InfoWidget::setWarnText(QLabel* lbl, const QString& msg) {

    lbl->setText(msg);

    lbl->setStyleSheet(YELLOW);
}

void InfoWidget::setErrorText(QLabel* lbl, const QString& msg) {

    lbl->setText(msg);

    lbl->setStyleSheet(RED);
}

void InfoWidget::updateRgfLabel() {

    if (fileExists(".rgf")) {

        setOkText(rgfLabel, "Data file found");

    }
    else {

        setErrorText(rgfLabel, "Don\'t forget to create the data file!");
    }
}

void InfoWidget::updateSetLabel() {

    if (fileExists(".set")) {

        setOkText(setLabel, "Settings from a previous run found");
    }
    else {

        setWarnText(setLabel, "The settings below need your attention");
    }
}

void InfoWidget::updateXyLabel() {

    if (fileExists(".xy")) {

        setOkText(xyLabel, "Coordinate file found");
    }
    else {

        setWarnText(xyLabel, "Not using any coordinate file");
    }
}

void InfoWidget::freezeLabelSize() {

    freezeWidth(projectLabel);
    freezeWidth(rgfLabel);
    freezeWidth(setLabel);
    freezeWidth(xyLabel);

}

void InfoWidget::freezeWidth(QLabel* lbl) {

    lbl->setFixedWidth(lbl->width());
}
