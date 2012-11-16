#include <QDebug>
#include <QMessageBox>
#include <QMutex>
#include <QProcess>
#include "ProcessManager.hpp"

ProcessManager::ProcessManager(QWidget *parent)
:   QObject(parent),
    executable(0)
{

    mutex = new QMutex;

}

ProcessManager::~ProcessManager() {

    delete mutex;
}

void ProcessManager::init() {

    cleanUp();

    executable = new QProcess(this);

    connect(executable, SIGNAL(started()), SLOT(exeStarted()) );

    connect(executable, SIGNAL(error(QProcess::ProcessError)), SLOT(exeError(QProcess::ProcessError)) );

    connect(executable, SIGNAL(finished(int, QProcess::ExitStatus)), SLOT(exeFinished(int, QProcess::ExitStatus)) );

}

void ProcessManager::cleanUp() {

    if (executable!=0) {

        executable->disconnect();

        executable->close();

        delete executable;

        executable = 0;
    }

    errorMsg = "Error: ";
}

Lock::Status ProcessManager::getLock() {

    if (!mutex->tryLock()) {

        showErrorMsg("the executable is already running!");

        return Lock::FAILED;
    }

    return Lock::OK;
}

void ProcessManager::exeStarted() {

}

void ProcessManager::exeError(QProcess::ProcessError error) {

}

void ProcessManager::exeFinished(int exitCode, QProcess::ExitStatus exitStatus) {

}

void ProcessManager::showErrorMsg(const QString& what) {

    errorMsg.append(what);

    QMessageBox mbox;

    mbox.setText(errorMsg);

    mbox.exec();
}

ExeCall::Status ProcessManager::run() {

    qDebug() << "Run invoked!";

    return ExeCall::OK;
}
