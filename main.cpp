#include <QtGui/QApplication>
#include <QDesktopWidget>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QRect screen_size = QApplication::desktop()->screenGeometry();

    MainWindow w(screen_size);

    w.show();
    
    return app.exec();
}
