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


SettingsWidget::SettingsWidget(QWidget* mainWindow) : QWidget(mainWindow) {

    QFrame* left  = new QFrame(this);
    QFrame* right = new QFrame(this);
    leftColumn  = new QVBoxLayout(left);
    rightColumn = new QVBoxLayout(right);

    int n_groups = numberOfGroups();
    int left_size = (n_groups+1) / 2;

    addInvisibleRunModeWidget();

    fillColumn(leftColumn,          1, left_size); // Skip the run mode group
    fillColumn(rightColumn, left_size,  n_groups);

    left->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    right->setFrameStyle(QFrame::WinPanel | QFrame::Raised);

    panel = new QHBoxLayout(this);
    panel->addWidget(left);
    panel->addWidget(right);
    panel->addStretch(1);
    setLayout(panel);

    foreach (OptionWidget* widget, optionWidgets)
        cliKeyToOptionWidget[widget->cliKey()] = widget;

    // FIXME The well group hack: disabled these options
    // in field mode.
    collectWellGroupWidgets();
    disableWellGroup(true);

    setFocusPolicy(Qt::StrongFocus);
}

void SettingsWidget::fillColumn(QVBoxLayout* col, int group_first, int group_end) {

    const QVector<OptionGroup>& optionGroups = getOptionGroups();

    for (int i=group_first; i<group_end; ++i) {

        QString name = optionGroups.at(i).first;
        col->addWidget(new QLabel("<b>"+name+"</b><hr/>"));

        QVector<Option> options = optionGroups.at(i).second;
        foreach (Option opt, options) {
            opt.checkConsistency();
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

//-----------------------------------------------------------------------------
// Hacks concerning the run mode

void SettingsWidget::addInvisibleRunModeWidget() {
    OptionWidget* optWidget = new OptionWidget(this, getOptionGroups().at(0).second.at(0));
    optWidget->setVisible(false);
    Q_ASSERT(optionWidgets.empty());
    optionWidgets.push_back(optWidget);
}

void SettingsWidget::collectWellGroupWidgets() {
    // count the first and the last index of the well
    // group options in optionWidgets
    const QVector<OptionGroup>& optionGroups = getOptionGroups();
    int begin = 0;
    int well_group_index = wellGroupIndex();
    for (int i=0; i<well_group_index; ++i)
        begin += optionGroups.at(i).second.size();

    int end = begin + optionGroups.at(well_group_index).second.size();

    for (int i=begin; i<end; ++i)
        wellGroup.push_back(optionWidgets.at(i));
}

void SettingsWidget::setRunMode(bool isWell) {
    // Assumes that index 0 is no, and 1 is yes, compare with
    // Option.cpp mode_opts[]
    optionWidgets.at(0)->setCurrentIndex(isWell ? 1 : 0);
    disableWellGroup(!isWell);
}

bool SettingsWidget::isWell() const {
    // Assumes the command line key Y if we are in well mode
    return optionWidgets.at(0)->getCurrentIndex() == 1;
}

void SettingsWidget::disableWellGroup(bool flag) {
    foreach (OptionWidget* widget , wellGroup) {
        widget->setForbidden(flag);
    }
}

//-----------------------------------------------------------------------------

void SettingsWidget::newProjectSelected(const QString& newProjectPath,
                                        const QString& newProjectName)
{
    projectPath = newProjectPath;
    projectName = newProjectName;
    bool loadedCleanly = tryLoadSettings();

    emit newSettingsFileLoaded(isWell(), loadedCleanly);
}

// returns: loadedCleanly
bool SettingsWidget::tryLoadSettings() {

    reset_defaults();

    setFileName = projectPath + "/" + projectName + ".set";
    QFileInfo setFile = QFileInfo(setFileName);
    if (setFile.exists() && setFile.isFile()) {
        qDebug() << "Corresponding .set file found";
        return loadSettings();
    }
    else {
        qDebug() << setFileName << " not found";
        return false;
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

// return: loadedCleanly
bool SettingsWidget::loadSettings() {

    QFile file(setFileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open " << setFileName;
        return false;
    }

    bool isOK = true;
    QTextStream in(&file);
    while (!in.atEnd()) {
        // Compare with Option::toCLIString() where the file is written
        QString line = in.readLine();
        const QStringList opt = line.split(":\t", QString::SkipEmptyParts);
        if (opt.size()!=2) {
            isOK = false;
            qDebug() << "Failed to split into key-value pair:" << line;
            continue;
        }
        const QString& cliKey = opt.at(0);
        if (!cliKeyToOptionWidget.contains(cliKey)) {
            isOK = false;
            qDebug() << "Key" << cliKey << "not found for line:" << line;
            continue;
        }
        OptionWidget* widget = cliKeyToOptionWidget.value(cliKey);
        const QString& value = opt.at(1);
        int pos = widget->indexOf(value);
        if (pos >= 0)
            widget->setCurrentIndex(pos);
        else {
            isOK = false;
            qDebug() << "Value" << value << "not found for line:" << line;
        }
    }

    if (isOK)
        qDebug() << "The file" << setFileName << "loaded cleanly";

    return isOK;
}
