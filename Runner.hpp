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

private slots:

    void runButtonClicked();

private:

    QPushButton* runButton;

    QHBoxLayout* layout;

    ProcessManager* processManager;

};

#endif // RUNNER_HPP
