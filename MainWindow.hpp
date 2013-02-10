// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QString>

class QVBoxLayout;
class QFileDialog;

class InfoWidget;
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

    void aboutQt();

    void editGUISettings();

    void showHomepage();

    void showManual();

    void runDemo();

    void editRGFRequested();

    void editXYRequested();

    void loadRGFRequested();

    void newRGFRequested();

    void newXYRequested();

private:

    void connect_signal_slots();

    void add_elements();

    void set_menu();

    QString selectFile(const QString& extension);

    QString saveFileAsDialog(const QString& extension);

    QString suggestedFileName(const QString& extension, bool read_only = true) const;

    void newProjectSelected();

    QString newFileRequested(const QString& extension, const QVector<QString>& header);

    void dumpHeader(const QString& newFile, const QVector<QString>& header);

    QString tryToSetFileAsProject(const QString& file, const QString& extension);

    bool setupDemoRgf();

    QFileDialog* fileDialog;

    InfoWidget* infoWidget;

    SettingsWidget* settingsWidget;

    Runner* runner;

    QStatusBar* statusBar;

    QVBoxLayout* mainLayout;

    QString startDir;

    QString projectPath;

    QString projectName;

};

#endif // MAINWINDOW_HPP
