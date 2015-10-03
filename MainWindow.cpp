// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QVector>
#include <string>
#include <vector>
#include "MainWindow.hpp"
#include "ErrorMsg.hpp"
#include "GlobalSettings.hpp"
#include "InfoWidget.hpp"
#include "Launcher.hpp"
#include "ReservedColumnNames.hpp"
#include "Runner.hpp"
#include "SettingsWidget.hpp"

namespace {

const char TITLE[] = " - Structural Geology to PostScript";

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

    connect(runner, SIGNAL(generateSetFile()), infoWidget, SLOT(checkSetFile()));
}

void MainWindow::add_elements() {

    QWidget* centralWidget = new QWidget(this);

    mainLayout = new QVBoxLayout;



    infoWidget = new InfoWidget(this);

    mainLayout->addWidget(infoWidget);


    settingsWidget = new SettingsWidget(this);

    mainLayout->addWidget(settingsWidget);



    statusBar = new QStatusBar;

    statusBar->setStyleSheet("QStatusBar { border: 1px solid grey; border-radius: 3px; } ");

    statusBar->showMessage("Ready", 2000);

    setStatusBar(statusBar);



    runner = new Runner(this, statusBar);

    mainLayout->addWidget(runner);



    mainLayout->addStretch(1);

    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
}

void MainWindow::fixSize() {

    setFixedSize(width(), height());

    infoWidget->freezeLabelSize();

    qDebug() << "Size: " << width() << "x" << height();
}

void MainWindow::set_menu() {

    QAction *showAbout = new QAction("About SG2PS", this);

    connect(showAbout, SIGNAL(triggered()), SLOT(about()));


    QAction *showAboutQt = new QAction("About Qt", this);

    connect(showAboutQt, SIGNAL(triggered()), SLOT(aboutQt()));


    QAction *editSettings = new QAction("GUI Settings", this);

    connect(editSettings, SIGNAL(triggered()), SLOT(editGUISettings()));


    QAction *manual = new QAction(QIcon(":/images/acroread48.png"), "Manual", this);

    connect(manual, SIGNAL(triggered()), SLOT(showManual()));


    QAction* demo = new QAction(QIcon(":/images/blockdevice-cubes-icon.png"), "Demo", this) ;

    connect(demo, SIGNAL(triggered()), SLOT(runDemo()));


    QAction *homepage = new QAction(QIcon(":/images/package_internet48.png"), "Jump to the homepage", this);

    connect(homepage, SIGNAL(triggered()), SLOT(showHomepage()));


    QAction *paper = new QAction("Jump to the paper", this);

    connect(paper, SIGNAL(triggered()), SLOT(showPaper()));


    QAction* createRGF = new QAction(QIcon(":/images/insert_table48.png"), "New Data", this);

    connect(createRGF, SIGNAL(triggered()), SLOT(newRGFRequested()));


    QAction* createXY = new QAction(QIcon(":/images/document_new48.png"), "New Coordinate", this);

    connect(createXY, SIGNAL(triggered()), SLOT(newXYRequested()));


    QAction* editRGF = new QAction(QIcon(":/images/spreadsheet48.png"), "Edit Data", this);

    connect(editRGF, SIGNAL(triggered()), SLOT(editRGFRequested()));


    QAction* editXY = new QAction(QIcon(":/images/spreadsheetB48.png"), "Edit Coordinate", this);

    connect(editXY, SIGNAL(triggered()), SLOT(editXYRequested()));


    QAction* loadRGF  = new QAction(QIcon(":/images/document_import48.png"), "Select Data", this);

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

    fileToolBar->addAction(manual);

    fileToolBar->addAction(demo);


    QMenu* settingsMenu = menuBar()->addMenu("Advanced");

    settingsMenu->addAction(editSettings);



    QMenu* help = menuBar()->addMenu("Help");

    help->addAction(manual);

    help->addAction(demo);

    help->addAction(homepage);

    help->addAction(paper);

    help->addAction(showAboutQt);

    help->addAction(showAbout);
}

void MainWindow::about() {

    QString msg("SG2PS "+QString::fromStdWString(L"—") +" Structural Geology to PostScript\n\n");

    msg.append( "Please cite us!\n\n" +
                QString::fromStdWString(L"Á. Sasvári, ") +
                "A. Baharev. SG2PS (structural geology to postscript "
                "converter) " + QString::fromStdWString(L" — ")+
                "A graphical solution for brittle structural data "
                "evaluation and paleostress calculation. "
                "Computers and Geosciences. 66, 81-93, 2014\n\n"

                "http://dx.doi.org/10.1016/j.cageo.2013.12.010\n\n");

    msg.append("Command line application built on ");

    msg.append(back_end_was_built_on()+"\n");

    msg.append( "GUI built on " __DATE__ " at " __TIME__ "\n\n");

    msg.append( "The heavy lifting is done by the back end, the external "
                "command line application sg2ps, written and maintained by ");

    msg.append(QString::fromStdWString(L"Ágoston Sasvári.\n\n"));

    msg.append( "This graphical front end is written and maintained by Ali Baharev "
                "and is based on Qt " QT_VERSION_STR ".\n\n"

                "The final PDF files are generated by GPL Ghostscript which comes "
                "with GNU General Public License.\n\n"

                "The SG2PS program is provided AS IS with NO WARRANTY OF ANY KIND, "
                "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS "
                "FOR A PARTICULAR PURPOSE.");

    QMessageBox::about(this, "About SG2PS", msg);

    qDebug() << "Built on " << __DATE__ << " at " << __TIME__;
}

void MainWindow::aboutQt() {

    QMessageBox::about(this, "About Qt",

                       "This program uses Qt version " QT_VERSION_STR ".\n\n"

                       "Qt is a C++ toolkit for cross-platform application development.\n\n"

                       "Qt provides single-source portability across MS Windows, Mac OS X, "
                       "Linux, and all major commercial Unix variants. Qt is also available "
                       "for embedded devices as Qt for Embedded Linux and Qt for Windows CE.\n\n"

                       "Qt is available under three different licensing options designed to "
                       "accommodate the needs of our various users.\n\n"

                       "Qt licensed under our commercial license agreement is appropriate for "
                       "development of proprietary/commercial software where you do not want "
                       "to share any source code with third parties or otherwise cannot "
                       "comply with the terms of the GNU LGPL version 2.1 or GNU GPL version "
                       "3.0.\n\n"

                       "Qt licensed under the GNU LGPL version 2.1 is appropriate for the "
                       "development of Qt applications (proprietary or open source) provided "
                       "you can comply with the terms and conditions of the GNU LGPL version "
                       "2.1.\n\n"

                       "Qt licensed under the GNU General Public License version 3.0 is "
                       "appropriate for the development of Qt applications where you wish to "
                       "use such applications in combination with software subject to the "
                       "terms of the GNU GPL version 3.0 or where you are otherwise willing "
                       "to comply with the terms of the GNU GPL version 3.0.\n\n"

                       "Please see qt.nokia.com/products/licensing for an overview of Qt "
                       "licensing.\n\n"

                       "Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).\n\n"

                       "Qt is a Nokia product. See qt.nokia.com for more information.\n\n");
}

void MainWindow::editGUISettings() {

    QString path = QDir::currentPath();

    openInTextEditor(path+"/"+opts().getSettingsFileName());

    QMessageBox mbox;

    mbox.setWindowTitle("Information");

    mbox.setText("Only if you are done editing the settings file, hit the button below!");

    mbox.setIcon(QMessageBox::Information);

    mbox.setButtonText(QMessageBox::Ok, "OK, I am done, reload the settings now!");

    mbox.exec();

    reloadGlobalSettings(); // I don't like it, global settings are now mutable
}

void MainWindow::showHomepage() {

    openWithDefaultApp("http://www.sg2ps.eu/index.htm?version="+version_id_of_back_end());
}

void MainWindow::showPaper() {

    openWithDefaultApp("http://dx.doi.org/10.1016/j.cageo.2013.12.010");
}

void MainWindow::showManual() {

    QString path = QDir::currentPath();

    openPDF(path+"/manual.pdf");
}

void MainWindow::runDemo() {

    if (!isInstalledSoftwareOK()) {
        return;
    }

    if (!setupDemoRgf()) {
         return;
    }

    QMessageBox mbox;
    mbox.setText("Hit the <b>Run</b> button at the bottom of the main window. Let\'s hope everthing works.");
    mbox.exec();
}

bool MainWindow::setupDemoRgf() {

    QString src = QCoreApplication::applicationDirPath()+"/demo.rgf";

    src  = QDir::toNativeSeparators(src);

    if (!QFileInfo(src).exists()) {
        showErrorMsg("problems with installation, the demo.rgf file is missing");
        return false;
    }

    return copyDemoRgf(src);
}

bool MainWindow::copyDemoRgf(const QString& src) {

    QMessageBox mbox;
    mbox.setText("You will be asked to save the demo data file somewhere.\n"
                 "Choose a directory at your convenience.");
    mbox.exec();

    QString dest = fileDialog->getSaveFileName(this, "Select where you wish to place the demo file",
                                               startDir+"/demo.rgf", "*.rgf (*.rgf)");
    if (dest.isEmpty()) {
        return false;
    }

    dest = QDir::toNativeSeparators(dest);

    if (src!=dest) { // stupid but legal to overwrite the file with itself

        QFile::remove(dest); // User already confirmed forced overwrite

        if (!QFile::copy(src,dest)) {
            showErrorMsg("copying "+src+" to "+dest+" failed");
            return false;
        }
    }

    if (tryToSetFileAsProject(dest, "rgf").isEmpty()) {
        return false;
    }

    return true;
}

QString MainWindow::selectFile(const QString& extension) {

    QString filter = "*."+extension+" (*."+extension+")";

    QString file = fileDialog->getOpenFileName(this,"Select an existing file",suggestedFileName(extension),filter);

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

    bool read_only = false;

    return fileDialog->getSaveFileName(this, "Create a new empty file", suggestedFileName(extension, read_only), filter);
}

QString MainWindow::suggestedFileName(const QString& extension, bool read_only) const {

    if (projectName.isEmpty()) {

        return startDir;
    }

    QString suggest_file = startDir+"/"+projectName+"."+extension;

    bool exists = QFile::exists(suggest_file);

    qDebug() << "File" << suggest_file << (exists?"exists":"doesn't exist");

    // XOR
    return ( (exists&&read_only) || (!exists&&!read_only) ) ? suggest_file : startDir;
}

QString MainWindow::newFileRequested(const QString& extension, const QVector<QString>& header) {

    QString newFile = saveFileAsDialog(extension);

    if (newFile.isEmpty()) {

        return QString();
    }

    dumpHeader(newFile, header);

    return tryToSetFileAsProject(newFile, extension);
}

void MainWindow::newRGFRequested() {

    QVector<QString> rgf_header;

    const std::vector<std::string>& header = reserved_column_names();

    for (std::size_t i=0; i<header.size(); ++i) {

        rgf_header.append(header.at(i).c_str());
    }

    QString file = newFileRequested("rgf", rgf_header);

    if (!file.isEmpty()) {

        openSpreadsheet(file);
    }
}

void MainWindow::newXYRequested() {

    // TODO Duplication: These are the same column names also apperaring in the reserved column names
    const QVector<QString> XY_HEADER = QVector<QString>() << "LOCATION" << "LOC_X" << "LOC_Y" << "FORMATION";

    QString file = newFileRequested("xy", XY_HEADER);

    if (!file.isEmpty()) {

        openSpreadsheet(file);
    }
}

// TODO All file IO should be moved to a separate class, widgets should not deal with files
// TODO Remove duplication, file IO fits a pattern
void MainWindow::dumpHeader(const QString& newFile, const QVector<QString>& header) {

    QFile file(newFile);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        return;
    }

    QTextStream out(&file);

    for (int i=0; i<header.size(); ++i) {

        out << header.at(i) << ((i==header.size()-1)?'\n':'\t');
    }
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

        qDebug() << "File: " << file;

        return QString();
    }
}

void MainWindow::newProjectSelected() {

    startDir = projectPath;

    infoWidget->newProjectSelected(projectPath, projectName);

    settingsWidget->newProjectSelected(projectPath, projectName);

    runner->newProjectSelected(projectPath, projectName);

    setWindowTitle(projectName + TITLE);
}

MainWindow::~MainWindow() {
    
}
