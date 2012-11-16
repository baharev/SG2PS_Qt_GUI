#include <QVBoxLayout>
#include "MainWindow.hpp"
#include "InputWidget.hpp"
#include "SettingsWidget.hpp"


MainWindow::MainWindow(const QRect& screen_size, QWidget *parent)
    : QMainWindow(parent), screen_size(screen_size)
{
    set_appearance();

    connect_signal_slots();

    add_elements();
}

void MainWindow::set_appearance() {


    setWindowTitle("SG2PS");

    setGeometry(0, 0, screen_size.width()/2, screen_size.height()/2);




}

void MainWindow::handleSelectedFile(const QString &file) {

}

void MainWindow::connect_signal_slots() {

}

void MainWindow::add_elements() {

    QWidget* centralWidget = new QWidget(this);

    mainLayout = new QVBoxLayout;



    inputWidget = new InputWidget(this);

    mainLayout->addWidget(inputWidget);



    settingsWidget = new SettingsWidget(this);

    mainLayout->addWidget(settingsWidget);



    mainLayout->addStretch();

    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    
}
