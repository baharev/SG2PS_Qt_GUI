#include <QtGui/QApplication>
#include <QDesktopWidget>
#include "MainWindow.hpp"
#include "GUISettings.hpp"
#include "GlobalSettings.hpp"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);


    GUISettings settings;

    settings.readSettings();

    initGlobalSettings(&settings);



    MainWindow w;

    w.show();

    w.fixSize();

    return app.exec();
}
