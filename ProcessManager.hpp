#ifndef PROCESSMANAGER_HPP
#define PROCESSMANAGER_HPP

#include <QProcess>

class QMutex;

struct ExeCall {

    enum Status { OK, FAILED };
};

struct Lock {

    enum Status { OK, FAILED };
};

class ProcessManager : public QObject {

    Q_OBJECT

public:

    explicit ProcessManager(QWidget* parent);

    ExeCall::Status run();

    ~ProcessManager();

private slots:

    void exeStarted();

    void exeError(QProcess::ProcessError error);

    void exeFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:

    void init();

    void cleanUp();

    void showErrorMsg(const QString& what);

    Lock::Status getLock();

    QMutex* mutex;

    QProcess* executable;

    QString errorMsg;

};

#endif // PROCESSMANAGER_HPP
