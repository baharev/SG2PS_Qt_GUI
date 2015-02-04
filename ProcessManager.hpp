// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef PROCESSMANAGER_HPP
#define PROCESSMANAGER_HPP

#include <QProcess>

class QMutex;

const bool SUCCESS = true;

const bool FAILED = false;

class ProcessManager : public QObject {

    Q_OBJECT

public:

    explicit ProcessManager(QObject* parent);

    void run(const QString& workingDirectory, const QStringList& args, const QString &logFile);

    ~ProcessManager();

signals:

    void runStarted();

    void runFinished(bool success, const QString& errorMsg);

private slots:

    void exeStarted();

    void exeError(QProcess::ProcessError errorCode);

    void exeFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:

    void init();

    void cleanUp();

    void callExecutable(const QString& workingDirectory, const QStringList& args, const QString &logFile);

    struct Lock { enum Status { OK, FAILED };  };

    Lock::Status getLock();

    void emitFinished(bool success, const QString &message);

    QMutex* mutex; // TODO Do we need mutex at all? As at SO

    QProcess* executable;
};

#endif // PROCESSMANAGER_HPP
