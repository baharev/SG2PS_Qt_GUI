#include <QDebug>
#include <QMutex>
#include <QProcess>
#include "ProcessManager.hpp"
#include "GlobalSettings.hpp"
#include "ErrorMsg.hpp"
#include "ResolveExitCode.hpp"

ProcessManager::ProcessManager(QObject *parent)
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

    QString errorMsg;

    if (error == QProcess::FailedToStart) {

        errorMsg = "the executable failed to start";
    }
    else if (error == QProcess::Crashed) {

        errorMsg = "the executable crashed";
    }
    else if (error == QProcess::Timedout) {

        errorMsg = "the executable timed out";
    }
    else if (error == QProcess::ReadError) {

        errorMsg = "when retrieving data from the executable";
    }
    else if (error == QProcess::WriteError) {

        errorMsg = "when passing data to the executable";
    }
    else if (error == QProcess::UnknownError) {

        errorMsg = "unknown error";
    }
    else {

        errorMsg = "unexpected error code received from Qt";
    }

    emitFinished(FAILED, errorMsg);
}

void ProcessManager::exeFinished(int exitCode, QProcess::ExitStatus exitStatus) {

    if (exitStatus == QProcess::NormalExit) {

    }
    else if (exitStatus == QProcess::CrashExit) {

        return; // Also handled in exeError
    }
    else {

        showErrorMsg("unexpected error code received from Qt");
    }

    emitFinished(exitCode==0?SUCCESS:FAILED, resolveExitCode(exitCode) );
}

void ProcessManager::emitFinished(bool success, const QString& message) {

    Q_ASSERT(!mutex->tryLock());

    mutex->unlock();

    qDebug() << "External executable has finished!";

    emit finished(success, message);
}

ExeCall::Status ProcessManager::run(const QString& workingDirectory, const QStringList& args, const QString& logFile) {

    if (getLock()==Lock::FAILED) {

        return ExeCall::FAILED;
    }

    callExecutable(workingDirectory, args, logFile);

    return ExeCall::OK;
}

void ProcessManager::callExecutable(const QString& workingDirectory, const QStringList& args, const QString& logFile) {

    init();

    const QString exeName = getStrOption("exe_name");

    qDebug() << workingDirectory;

    qDebug() << exeName << args;

    executable->setWorkingDirectory(workingDirectory);

    executable->setStandardOutputFile(workingDirectory+"/"+logFile);

    executable->start(exeName, args);

    qDebug() << "Executable called!";
}
