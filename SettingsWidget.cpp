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

    int n_groups = numberOfGroups();
    int left_size = n_groups / 2;

    fillColumn(leftColumn,          0, left_size);
    fillColumn(rightColumn, left_size, n_groups);

    left->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    right->setFrameStyle(QFrame::WinPanel | QFrame::Raised);

    panel = new QHBoxLayout(this);
    panel->addWidget(left);
    panel->addWidget(right);
    panel->addStretch(1);
    setLayout(panel);
}

void SettingsWidget::fillColumn(QVBoxLayout* col, int group_first, int group_end) {

    const QVector<OptionGroup>& optionGroups = getOptionGroups();

    for (int i=group_first; i<group_end; ++i) {

        QString name = optionGroups.at(i).first;
        col->addWidget(new QLabel("<b>"+name+"</b><hr/>"));

        QVector<Option> options = optionGroups.at(i).second;
        foreach (Option opt, options) {
            OptionWidget* optWidget = new OptionWidget(this, opt);
            optionWidgets.push_back(optWidget);
            col->addWidget(optWidget);
        }

        if (i!=group_end-1) {
            QFrame* hline = new QFrame();
            hline->setFrameShape(QFrame::HLine);
            col->addWidget(hline);
        }
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
