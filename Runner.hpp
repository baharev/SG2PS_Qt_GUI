#ifndef RUNNER_HPP
#define RUNNER_HPP

#include <QWidget>

class QPushButton;
class QHBoxLayout;
class ProcessManager;

class Runner : public QWidget {

    Q_OBJECT

public:

    explicit Runner(QWidget* parent);

public slots:

    void inputFileSelected(const QString& name);

private slots:

    void runButtonClicked();

    void finished(bool success, const QString& errorMsg);

private:

    QString croppedFileName() const;

    QPushButton* runButton;

    QHBoxLayout* layout;

    ProcessManager* processManager;

    QString fileName;

    QString workingDirectory;

};

#endif // RUNNER_HPP
