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

signals:

    void generateSetFile();

public slots:

    void inputFileSelected(const QString& name);

private slots:

    void runButtonClicked();

    void onRunStarted();

    void onRunFinished(bool success, const QString& errorMsg);

private:

    QString croppedFileName() const;

    void showLog() const;

    void showResultDir() const;

    QPushButton* runButton;

    QHBoxLayout* layout;

    ProcessManager* processManager;

    QString fileName;

    QString workingDirectory;

    QString logFile;
};

#endif // RUNNER_HPP
