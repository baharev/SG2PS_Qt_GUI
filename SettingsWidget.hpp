// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef SETTINGSWIDGET_HPP
#define SETTINGSWIDGET_HPP

#include <QWidget>
#include <QString>
#include <QVector>
#include <QHash>

class QHBoxLayout;
class QVBoxLayout;
class OptionWidget;

class SettingsWidget: public QWidget {

    Q_OBJECT

public:

    explicit SettingsWidget(QWidget* mainWindow);

    void newProjectSelected(const QString& newProjectPath, const QString& newProjectName);

public slots:

    void writeSettings();

    void setRunMode(bool isWell);

signals:

    void newSettingsFileLoaded(bool isWell, bool loadedCleanly);

private:

    void fillColumn(QVBoxLayout* col, int row_beg, int row_end);
    void reset_defaults();
    bool tryLoadSettings();
    bool loadSettings();

    void addInvisibleRunModeWidget();
    void collectWellGroupWidgets();
    void disableWellGroup(bool flag);
    bool isWell() const;

    QString setFileName;
    QHBoxLayout* panel;
    QVBoxLayout* leftColumn;
    QVBoxLayout* rightColumn;
    QVector<OptionWidget*> optionWidgets;
    QString projectPath;
    QString projectName;

    QHash<QString,OptionWidget*> cliKeyToOptionWidget;
    QVector<OptionWidget*> wellGroup;
};

#endif // SETTINGSWIDGET_HPP
