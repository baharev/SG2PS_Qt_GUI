// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef SETTINGSWIDGET_HPP
#define SETTINGSWIDGET_HPP

#include <QWidget>
#include <QString>
#include <QVector>

class QHBoxLayout;
class QVBoxLayout;
class InfoSettingsWire;
class OptionWidget;

class SettingsWidget: public QWidget {

    Q_OBJECT

public:

    explicit SettingsWidget(QWidget* mainWindow);

    void setWire(InfoSettingsWire* wire);

    void newProjectSelected(const QString& newProjectPath, const QString& newProjectName);

    void setRunMode(bool isWell);

public slots:

    void writeSettings();

private:

    void fillColumn(QVBoxLayout* col, int row_beg, int row_end);
    void reset_defaults();
    bool tryLoadSettings();
    bool loadSettings();

    QString setFileName;
    QHBoxLayout* panel;
    QVBoxLayout* leftColumn;
    QVBoxLayout* rightColumn;
    QVector<OptionWidget*> optionWidgets;
    QString projectPath;
    QString projectName;

    InfoSettingsWire* wire;
};

#endif // SETTINGSWIDGET_HPP
