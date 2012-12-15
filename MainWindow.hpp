// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QString>

class QVBoxLayout;

class InputWidget;
class SettingsWidget;
class Runner;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow(QWidget *parent = 0);

    void fixSize();

    ~MainWindow();

private slots:

    void about();

    void editGUISettings();

    void showHomepage();

    void showManual();

    void editRGFRequested();

    void editXYRequested();

    void loadRGFRequested();

private:

    void connect_signal_slots();

    void add_elements();

    void set_menu();

    QString selectFile(const QString& extension);

    void newProjectSelected();

    InputWidget* inputWidget;

    SettingsWidget* settingsWidget;

    Runner* runner;

    QVBoxLayout* mainLayout;

    QString startDir;

    QString projectPath;

    QString projectName;

};

#endif // MAINWINDOW_HPP
