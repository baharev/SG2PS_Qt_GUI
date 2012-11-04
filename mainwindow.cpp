#include "mainwindow.hpp"

MainWindow::MainWindow(const QRect& screen_size, QWidget *parent)
    : QMainWindow(parent), screen_size(screen_size)
{
    set_appearance();
}

void MainWindow::set_appearance() {

    setWindowTitle("SG2PS");

    setGeometry(0, 0, screen_size.width()/2, screen_size.height()/2);
}

MainWindow::~MainWindow()
{
    
}
