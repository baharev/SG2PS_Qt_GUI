#include <QtGui/QApplication>
#include <QDesktopWidget>
#include "MainWindow.hpp"
#include "GUISettings.hpp"
#include "GlobalSettings.hpp"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    QRect screen_size = QApplication::desktop()->screenGeometry();



    GUISettings settings;

    settings.readSettings();

    initGlobalSettings(&settings);



    MainWindow w(screen_size);

    w.show();

    w.fixSize();

    return app.exec();
}
