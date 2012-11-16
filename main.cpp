#include <QtGui/QApplication>
#include <QDesktopWidget>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QRect screen_size = QApplication::desktop()->screenGeometry();

    MainWindow w(screen_size);

    w.show();

    w.printSize();
    
    return app.exec();
}
