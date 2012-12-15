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
#include "GlobalSettings.hpp" // TODO Remove if option is retrieved from InputWidget
#include "InputWidget.hpp"
#include "Launcher.hpp"
#include "Runner.hpp"
#include "SettingsWidget.hpp"

namespace {

const wchar_t TITLE[] = L" — Structural Geology to PostScript";

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QString::fromWCharArray(L"SG2PS")+QString::fromWCharArray(TITLE));

    set_menu();

    add_elements();

    startDir = getStrOption("start_browsing_from_directory"); // TODO Redundant that InputWidget asks for this again

    connect_signal_slots();
}

void MainWindow::connect_signal_slots() {

    // TODO Make it clear at the args that a valid rgf is assumed
    // TODO Combinatorial explosion of the possibilities

    connect(inputWidget, SIGNAL(inputFileSelected(QString)), runner, SLOT(inputFileSelected(QString)));

    connect(inputWidget, SIGNAL(inputFileSelected(QString)), settingsWidget, SLOT(tryLoadSettings(QString)));

    connect(inputWidget, SIGNAL(inputFileSelected(QString)), this, SLOT(inputFileSelected(QString)));


    connect(this,        SIGNAL(fileSelected(QString)), runner, SLOT(inputFileSelected(QString)));

    connect(this,        SIGNAL(fileSelected(QString)), settingsWidget, SLOT(tryLoadSettings(QString)));

    // TODO Perhaps we should only tell inputWidget and then let him call the others.
    connect(this,        SIGNAL(fileSelected(QString)), inputWidget, SLOT(validRgfSelected(QString)));


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

    QAction *showAbout = new QAction("About", this);

    connect(showAbout, SIGNAL(triggered()), SLOT(about()));


    QAction *editSettings = new QAction("Preferences", this);

    connect(editSettings, SIGNAL(triggered()), SLOT(editGUISettings()));


    QAction *manual = new QAction(QIcon(":/images/acroread48.png"), "Manual", this);

    connect(manual, SIGNAL(triggered()), SLOT(showManual()));


    QAction *homepage = new QAction(QIcon(":/images/package_internet48.png"), "Jump to the homepage", this);

    connect(homepage, SIGNAL(triggered()), SLOT(showHomepage()));


    // TODO Connect and implement
    QAction* createRGF = new QAction(QIcon(":/images/insert_table48.png"), "New RGF", this);
    QAction* createXY = new QAction("New XY file", this);
    QAction* loadRGF  = new QAction(QIcon(":/images/document_import48.png"), "Load RGF", this);


    QAction* editRGF = new QAction(QIcon(":/images/spreadsheet48.png"), "Edit RGF", this);

    connect(editRGF, SIGNAL(triggered()), SLOT(editRGFRequested()));


    QAction* editXY = new QAction("Edit existing XY", this);

    connect(editXY, SIGNAL(triggered()), SLOT(editXYRequested()));


    QMenu* file = menuBar()->addMenu("File");

    file->addAction(createRGF);

    file->addAction(editRGF);

    file->addAction(createXY);

    file->addAction(editXY);


    QToolBar* fileToolBar = addToolBar("File");

    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    fileToolBar->addAction(createRGF);

    fileToolBar->addAction(editRGF);

    fileToolBar->addAction(loadRGF);


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

    QString file = QFileDialog::getOpenFileName(this,"Select File",startDir,filter);

    QFileInfo fileInfo(file);

    if (fileInfo.exists() && fileInfo.suffix()==extension) {

        projectPath = fileInfo.absolutePath();

        projectName = fileInfo.fileName();

        projectName.chop(extension.length()+1);

        qDebug() << "New projected selected, file name:" << file;

        newProjectSelected();
    }
    else {

        file = QString();
    }

    return file;
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

        // TODO Tricky emit signal: others are expecting an existing *.rgf

        openSpreadsheet(file);
    }
}

void MainWindow::newProjectSelected() {

    startDir = projectPath;

    inputWidget->newProjectSelected(projectPath, projectName);

    settingsWidget->newProjectSelected(projectPath, projectName);

    runner->newProjectSelected(projectPath, projectName);

    setWindowTitle(projectName + QString::fromWCharArray(TITLE));
}

MainWindow::~MainWindow() {
    
}
