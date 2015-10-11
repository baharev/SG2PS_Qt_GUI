// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QString>
#include "InfoSettingsWire.hpp"

class QVBoxLayout;
class QFileDialog;

class InfoSettingsWire;
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

    void showPaper();

    void showManual();

    void runDemo();

    void editRGFRequested();

    void editXYRequested();

    void editTRJRequested();

    void loadRGFRequested();

    void newRGFRequested();

    void newXYRequested();

    void newTRJRequested();

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

    bool copyDemoRgf(const QString& src);

    QFileDialog* fileDialog;

    InfoWidget* infoWidget;

    SettingsWidget* settingsWidget;

    InfoSettingsWire infoSettingsWire;

    Runner* runner;

    QStatusBar* statusBar;

    QVBoxLayout* mainLayout;

    QString startDir;

    QString projectPath;

    QString projectName;

};

#endif // MAINWINDOW_HPP
