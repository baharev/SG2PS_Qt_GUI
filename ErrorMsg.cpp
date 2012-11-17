#include <QMessageBox>
#include <QString>
#include "ErrorMsg.hpp"

void showErrorMsg(const QString& what) {

    QMessageBox mbox;

    mbox.setText("Error: "+what+"!");

    mbox.setIcon(QMessageBox::Critical);

    mbox.exec();
}
