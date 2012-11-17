#include <QDebug>
#include <QMessageBox>
#include <QMutex>
#include <QProcess>
#include "ProcessManager.hpp"
#include "GlobalSettings.hpp"

ProcessManager::ProcessManager(QWidget *parent)
:   QObject(parent),
    executable(0)
{

    mutex = new QMutex;

}

ProcessManager::~ProcessManager() {

    cleanUp();

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

        showErrorMsg("the executable is already running");

        return Lock::FAILED;
    }

    return Lock::OK;
}

void ProcessManager::exeStarted() {

    // Seems like a useless function
}

void ProcessManager::exeError(QProcess::ProcessError error) {

    if (error == QProcess::FailedToStart) {

        errorMsg += "the executable failed to start";
    }
    else if (error == QProcess::Crashed) {

        errorMsg += "the executable crashed";
    }
    else if (error == QProcess::Timedout) {

        errorMsg += "the executable timed out";
    }
    else if (error == QProcess::ReadError) {

        errorMsg += "when retrieving data from the executable";
    }
    else if (error == QProcess::WriteError) {

        errorMsg += "when passing data to the executable";
    }
    else if (error == QProcess::UnknownError) {

        errorMsg += "unknown error";
    }
    else {

        errorMsg += "unexpected error code received from Qt";
    }

    showErrorMsg();

    releaseLock();
}

void ProcessManager::exeFinished(int exitCode, QProcess::ExitStatus exitStatus) {

    if (exitStatus == QProcess::NormalExit) {

        // TODO check_result(exitCode);
    }
    else if (exitStatus == QProcess::CrashExit) {

        return; // Also handled in exeError
    }
    else {

        showErrorMsg("unexpected error code received from Qt");
    }

    releaseLock();
}

void ProcessManager::releaseLock() { // TODO Name not quite appropriate

    Q_ASSERT(!mutex->tryLock());

    mutex->unlock();

    qDebug() << "External executable has finished!";

    emit finished(true, ""); // TODO Fix it!
}

void ProcessManager::showErrorMsg(const QString& what) {

    errorMsg.append(what+"!");

    QMessageBox mbox;

    mbox.setText(errorMsg);

    mbox.exec();
}

ExeCall::Status ProcessManager::run(const QString& workingDirectory, const QStringList& args) {

    if (getLock()==Lock::FAILED) {

        return ExeCall::FAILED;
    }

    callExecutable(workingDirectory, args);

    return ExeCall::OK;
}

void ProcessManager::callExecutable(const QString& workingDirectory, const QStringList& args) {

    init();

    const QString exeName = getStrOption("exe_name");

    qDebug() << workingDirectory;

    qDebug() << exeName << args;

    executable->setWorkingDirectory(workingDirectory);

    executable->start(exeName, args);

    qDebug() << "Executable called!";
}
