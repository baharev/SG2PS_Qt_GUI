// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QMessageBox>
#include <QString>
#include "ErrorMsg.hpp"

void showErrorMsg(const QString& what) {

    QMessageBox mbox;

    mbox.setWindowTitle("Error");

    mbox.setText("Error: "+what+"!");

    mbox.setIcon(QMessageBox::Critical);

    mbox.exec();
}
