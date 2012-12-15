// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
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

    void newProjectSelected(const QString& newProjectPath, const QString& newProjectName);

signals:

    void generateSetFile();

private slots:

    void runButtonClicked();

    void onRunStarted();

    void onRunFinished(bool success, const QString& errorMsg);

private:

    void showLog() const;

    void showResultDir() const;

    QPushButton* runButton;

    QHBoxLayout* layout;

    ProcessManager* processManager;

    QString logFile;

    QString projectPath;

    QString projectName;
};

#endif // RUNNER_HPP
