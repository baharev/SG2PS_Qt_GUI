#include <QVBoxLayout>
#include <QDebug>
#include "MainWindow.hpp"
#include "InputWidget.hpp"
#include "SettingsWidget.hpp"
#include "Runner.hpp"


MainWindow::MainWindow(const QRect& screen_size, QWidget *parent)
    : QMainWindow(parent), screen_size(screen_size)
{
    set_appearance();

    add_elements();

    connect_signal_slots();
}

void MainWindow::set_appearance() {


    setWindowTitle("SG2PS Qt Frontend");

    //setGeometry(0, 0, screen_size.width()/2, screen_size.height()/2)


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

    qDebug() << "Size: " << width() << "x" << height();
}

MainWindow::~MainWindow()
{
    
}
