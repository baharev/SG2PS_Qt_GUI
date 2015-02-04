// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDebug>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QFileInfo>
#include "SettingsWidget.hpp"
#include "OptionWidget.hpp"
#include "Option.hpp"
#include "LayoutConstants.hpp"

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent) {

    QFrame* left  = new QFrame(this);
    QFrame* right = new QFrame(this);
    leftColumn  = new QVBoxLayout(left);
    rightColumn = new QVBoxLayout(right);
    leftColumn->addWidget(new QLabel("Settings"));
    rightColumn->addWidget(new QLabel(""));

    int n_opts = Option::getOptSize();
    int left_size = (n_opts+1) / 2;

    fillColumn(leftColumn,          0, left_size);
    fillColumn(rightColumn, left_size, n_opts);

    left->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    right->setFrameStyle(QFrame::WinPanel | QFrame::Raised);

    panel = new QHBoxLayout(this);
    panel->addWidget(left);
    panel->addWidget(right);
    panel->addStretch(1);
    setLayout(panel);
}

void SettingsWidget::fillColumn(QVBoxLayout* col, int opt_first, int opt_last) {

    const Option* opts = Option::getOpts();

    for (int i=opt_first; i<opt_last; ++i) {
        OptionWidget* optWidget = new OptionWidget(this, opts[i]);
        optionWidgets.push_back(optWidget);
        col->addWidget(optWidget);
    }
    col->addStretch(1);
}

void SettingsWidget::reset_defaults() {

    foreach (OptionWidget* widget , optionWidgets) {
        widget->selectDefault();
    }
}

void SettingsWidget::newProjectSelected(const QString& newProjectPath,
                                        const QString& newProjectName)
{
    projectPath = newProjectPath;
    projectName = newProjectName;
    tryLoadSettings();
}

void SettingsWidget::tryLoadSettings() {

    setFileName = projectPath + "/" + projectName + ".set";
    QFileInfo setFile = QFileInfo(setFileName);
    if (setFile.exists() && setFile.isFile()) {
        qDebug() << "Corresponding .set file found";
        loadSettings();
    }
    else {
        qDebug() << setFileName << " not found";
        reset_defaults();
    }
}

void SettingsWidget::writeSettings() {

    QFile setFile(setFileName);

    if (!setFile.open(QIODevice::WriteOnly | QIODevice::Text)) {

        return;
    }

    QTextStream out(&setFile);

    foreach (OptionWidget* widget , optionWidgets) {
        QString line = widget->selection2CLI();
        out << line << '\n';
    }
    qDebug() << "Settings dumped";
}

void SettingsWidget::loadSettings() {

    QFile file(setFileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open " << setFileName;
        return;
    }

    QTextStream in(&file);

    int n = optionWidgets.size();

    for (int i=0; (!in.atEnd()) && i<n; ++i) {
        QString line = in.readLine();
        optionWidgets.at(i)->set(line);
    }
}
