// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef RUNNER_HPP
#define RUNNER_HPP

#include <QWidget>

class QPushButton;
class QHBoxLayout;
class QStatusBar;
class ProcessManager;
class ConvertAllEps;

class Runner : public QWidget {

    Q_OBJECT

public:

    explicit Runner(QWidget* parent, QStatusBar* mainWindowStatusBar);

    void newProjectSelected(const QString& newProjectPath, const QString& newProjectName);

signals:

    void generateSetFile();

private slots:

    void runButtonClicked();

    void onRunStarted();

    void onRunFinished(bool success, const QString& errorMsg);

    void onConversionFinished(bool done);

private:

    void convertEps2Pdf();

    void showLog() const;

    void showResultDir() const;

    QString dirToShow(bool& pointerToFolderOK) const;

    QPushButton* runButton;

    QHBoxLayout* layout;

    ProcessManager* processManager;

    ConvertAllEps* converter;

    QStatusBar* statusBar;

    QString logFile;

    QString projectPath;

    QString projectName;

    QString finalProjectFolder;
};

#endif // RUNNER_HPP
