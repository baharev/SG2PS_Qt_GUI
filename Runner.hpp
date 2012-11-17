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

public slots:

    void inputFileSelected(const QString& name);

private slots:

    void runButtonClicked();

    void onRunFinished(bool success, const QString& errorMsg);

private:

    QString croppedFileName() const;

    void enableButton();

    void disableButton();

    QPushButton* runButton;

    QHBoxLayout* layout;

    ProcessManager* processManager;

    QString fileName;

    QString workingDirectory;

    QString logFile;
};

#endif // RUNNER_HPP
