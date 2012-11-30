// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QMessageBox>
#include <QDir>
#include <QProcess>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QDebug>
#include "MainWindow.hpp"
#include "InputWidget.hpp"
#include "GlobalSettings.hpp"
#include "SettingsWidget.hpp"
#include "Runner.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("SG2PS Qt Frontend");

    set_menu();

    add_elements();

    connect_signal_slots();
}

void MainWindow::connect_signal_slots() {

    connect(inputWidget, SIGNAL(inputFileSelected(QString)), runner, SLOT(inputFileSelected(QString)));
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

    QAction *editSettings = new QAction("Preferences", this);


    QMenu* menu = menuBar()->addMenu("Misc");

    menu->addAction(showAbout);

    menu->addAction(editSettings);

    connect(showAbout, SIGNAL(triggered()), SLOT(about()));

    connect(editSettings, SIGNAL(triggered()), SLOT(editGUISettings()));
}

void MainWindow::about() {

    QMessageBox::about(this, "About", "Built on " __DATE__ " at " __TIME__ "\n\n"
                       "The program is provided AS IS with NO WARRANTY OF ANY KIND, "
                       "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS "
                       "FOR A PARTICULAR PURPOSE.");

    qDebug() << "Built on " << __DATE__ << " at " << __TIME__;
}

void MainWindow::editGUISettings() {

    // TODO Reload it automatically instead!
    QMessageBox::information(this, "Reminder", "After editing the options, don\'t forget "
                             "to restart the application!");

    QString editor = getStrOption("text_editor");

    QString path = QDir::currentPath();

    QProcess::startDetached(editor+" "+path+"/settings.txt");
}

MainWindow::~MainWindow()
{
    
}
