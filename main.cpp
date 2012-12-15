// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QtGui/QApplication>
#include <QDesktopWidget>
#include "MainWindow.hpp"
#include "GUISettings.hpp"
#include "GlobalSettings.hpp"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    Q_INIT_RESOURCE(resources);

    GUISettings settings;

    settings.readSettings();

    initGlobalSettings(&settings);



    MainWindow w;

    w.show();

    w.fixSize();

    return app.exec();
}
