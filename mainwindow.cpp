#include <QWidget>
#include <QDebug>
#include "mainwindow.hpp"

namespace {

const char SELECT_FILE_TEXT[] = "Select .rgf file";

}

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


    selectFileButton.setText(SELECT_FILE_TEXT);

    QFontMetrics fontMetrics(selectFileButton.font());

    selectFileButton.setMinimumWidth(1);

    selectFileButton.resize(fontMetrics.width(SELECT_FILE_TEXT), selectFileButton.height());

}

void MainWindow::connect_signal_slots() {

     connect(&selectFileButton, SIGNAL(clicked()), SLOT(showSelectFileDialog()));
}

void MainWindow::add_elements() {

    layoutSelectFile.addWidget(&selectFileButton);

    layoutSelectFile.addStretch();



    QWidget* fileSelectPanel = new QWidget();

    fileSelectPanel->setLayout(&layoutSelectFile);



    mainLayout.addWidget(fileSelectPanel); // FIXME Write wrapper for this

    mainLayout.addStretch();



    QWidget* mainPanel = new QWidget();

    mainPanel->setLayout(&mainLayout);

    setCentralWidget(mainPanel);
}

void MainWindow::showSelectFileDialog() {

    qDebug() << "Button clicked!";
}

MainWindow::~MainWindow()
{
    
}
