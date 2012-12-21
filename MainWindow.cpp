// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QMenuBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QDebug>
#include "MainWindow.hpp"
#include "GlobalSettings.hpp"
#include "InputWidget.hpp"
#include "Launcher.hpp"
#include "Runner.hpp"
#include "SettingsWidget.hpp"

namespace {

const char TITLE[] = " - Structural Geology to PostScript";

const char RGF_HEADER[] = "DATA_ID\tGC\tCOLOR\tLOC\tLOCX\tLOCY\tFORMATION\t"
                          "DATATYPE\tcorrDIPDIR\tcorrDIP\tcorrLDIR\tcorrLDIP\t"
                          "SENSE\tPALEONORTH\tCOMMENT";

const char  XY_HEADER[] = "NAME\tLATTITUDE\tLONGITUDE";

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), fileDialog(new QFileDialog(this))
{
    setWindowTitle(QString("SG2PS")+TITLE);

    set_menu();

    add_elements();

    startDir = opts().getStartBrowsingFromDirectory();

    connect_signal_slots();
}

void MainWindow::connect_signal_slots() {

    connect(runner, SIGNAL(generateSetFile()), settingsWidget, SLOT(writeSettings()));
}

void MainWindow::add_elements() {

    QWidget* centralWidget = new QWidget(this);

    mainLayout = new QVBoxLayout;



    inputWidget = new InputWidget(this);

    mainLayout->addWidget(inputWidget);



    settingsWidget = new SettingsWidget(this);

    mainLayout->addWidget(settingsWidget);


    runner = new Runner(this);

    mainLayout->addWidget(runner);



    mainLayout->addStretch(1);

    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
}

void MainWindow::fixSize() {

    setFixedSize(width(), height());

    inputWidget->freezeLabelSize();

    qDebug() << "Size: " << width() << "x" << height();
}

void MainWindow::set_menu() {

    QAction *showAbout = new QAction("About SG2PS", this);

    connect(showAbout, SIGNAL(triggered()), SLOT(about()));


    QAction *editSettings = new QAction("Preferences", this);

    connect(editSettings, SIGNAL(triggered()), SLOT(editGUISettings()));


    QAction *manual = new QAction(QIcon(":/images/acroread48.png"), "Manual", this);

    connect(manual, SIGNAL(triggered()), SLOT(showManual()));


    QAction *homepage = new QAction(QIcon(":/images/package_internet48.png"), "Jump to the homepage", this);

    connect(homepage, SIGNAL(triggered()), SLOT(showHomepage()));


    QAction* createRGF = new QAction(QIcon(":/images/insert_table48.png"), "New RGF", this);

    connect(createRGF, SIGNAL(triggered()), SLOT(newRGFRequested()));


    QAction* createXY = new QAction(QIcon(":/images/document_new48.png"), "New XY file", this);

    connect(createXY, SIGNAL(triggered()), SLOT(newXYRequested()));


    QAction* editRGF = new QAction(QIcon(":/images/spreadsheet48.png"), "Edit RGF", this);

    connect(editRGF, SIGNAL(triggered()), SLOT(editRGFRequested()));


    QAction* editXY = new QAction(QIcon(":/images/spreadsheetB48.png"), "Edit XY", this);

    connect(editXY, SIGNAL(triggered()), SLOT(editXYRequested()));


    QAction* loadRGF  = new QAction(QIcon(":/images/document_import48.png"), "Select RGF", this);

    connect(loadRGF, SIGNAL(triggered()), SLOT(loadRGFRequested()));


    QMenu* file = menuBar()->addMenu("File");

    file->addAction(createRGF);

    file->addAction(editRGF);

    file->addAction(loadRGF);

    file->addAction(createXY);

    file->addAction(editXY);


    QToolBar* fileToolBar = addToolBar("File");

    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    fileToolBar->addAction(createRGF);

    fileToolBar->addAction(editRGF);

    fileToolBar->addAction(loadRGF);

    fileToolBar->addAction(createXY);

    fileToolBar->addAction(editXY);


    QMenu* settingsMenu = menuBar()->addMenu("Options");

    settingsMenu->addAction(editSettings);



    QMenu* help = menuBar()->addMenu("Help");

    help->addAction(manual);

    help->addAction(homepage);

    help->addAction(showAbout);
}

void MainWindow::about() {

    QMessageBox::about(this, "About SG2PS", QString::fromWCharArray(

                       L"SG2PS — Structural Geology to PostScript\n\n"

                       L"Built on " __DATE__ " at " __TIME__ "\n\n"

                       L"The heavy lifting is done by the back end, the external "
                       L"command line application sg2ps, written and maintened by "
                       L"Ágoston Sasvári.\n\n"

                       L"This grapical front end is written and mainted by Ali Baharev "
                       L"and is based on Qt " QT_VERSION_STR ".\n\n"

                       L"The program is provided AS IS with NO WARRANTY OF ANY KIND, "
                       L"INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS "
                       L"FOR A PARTICULAR PURPOSE.")
                       );

    qDebug() << "Built on " << __DATE__ << " at " << __TIME__;
}

void MainWindow::editGUISettings() {

    // TODO Reload it automatically instead!
    QMessageBox::information(this, "Reminder", "After editing the options, don\'t forget "
                             "to restart the application!");

    QString path = QDir::currentPath();

    openInTextEditor(path+"/settings.txt");
}

void MainWindow::showHomepage() {

    openWithDefaultApp("http://www.sg2ps.eu/"); // TODO ?gui=201212081605
}

void MainWindow::showManual() {

    QString path = QDir::currentPath();

    openPDF(path+"/manual.pdf");
}

QString MainWindow::selectFile(const QString& extension) {

    QString filter = "*."+extension+" (*."+extension+")";

    QString file = fileDialog->getOpenFileName(this,"Select File",startDir,filter);

    return tryToSetFileAsProject(file, extension);
}

void MainWindow::editRGFRequested() {

    QString file = selectFile("rgf");

    if (!file.isEmpty()) {

        openSpreadsheet(file);
    }
}

void MainWindow::loadRGFRequested() {

    selectFile("rgf");
}

void MainWindow::editXYRequested() {

    QString file = selectFile("xy");

    if (!file.isEmpty()) {

        openSpreadsheet(file);
    }
}

QString MainWindow::saveFileAsDialog(const QString& extension) {

    QString filter = "*."+extension+" (*."+extension+")";

    return fileDialog->getSaveFileName(this, "Create file", startDir, filter);
}

QString MainWindow::newFileRequested(const QString& extension, const char header[]) {

    QString newFile = saveFileAsDialog(extension);

    if (newFile.isEmpty()) {

        return QString();
    }

    dumpHeader(newFile, header);

    return tryToSetFileAsProject(newFile, extension);
}

void MainWindow::newRGFRequested() {

    QString file = newFileRequested("rgf", RGF_HEADER);

    if (!file.isEmpty()) {

        openSpreadsheet(file);
    }
}

void MainWindow::newXYRequested() {

    QString file = newFileRequested("xy", XY_HEADER);

    if (!file.isEmpty()) {

        openSpreadsheet(file);
    }
}

// TODO All file IO should be moved to a separate class, widgets should not deal with files
// TODO Remove duplication, file IO fits a pattern
void MainWindow::dumpHeader(const QString& newFile, const char header[]) {

    QFile file(newFile);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        return;
    }

    QTextStream out(&file);

    out << header << '\n';
}

QString MainWindow::tryToSetFileAsProject(const QString& file, const QString& extension) {

    QFileInfo fileInfo(file);

    if (fileInfo.exists() && fileInfo.isFile() && fileInfo.suffix()==extension) {

        projectPath = fileInfo.absolutePath();

        projectName = fileInfo.fileName();

        projectName.chop(extension.length()+1);

        qDebug() << "New projected selected, file name:" << file;

        newProjectSelected();

        return file;
    }
    else {

        return QString();
    }
}

void MainWindow::newProjectSelected() {

    startDir = projectPath;

    inputWidget->newProjectSelected(projectPath, projectName);

    settingsWidget->newProjectSelected(projectPath, projectName);

    runner->newProjectSelected(projectPath, projectName);

    setWindowTitle(projectName + TITLE);
}

MainWindow::~MainWindow() {
    
}
