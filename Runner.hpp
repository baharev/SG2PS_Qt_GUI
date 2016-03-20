// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef RUNNER_HPP
#define RUNNER_HPP

#include <QWidget>

class QPushButton;
class QHBoxLayout;
class QStatusBar;
class ConvertAllEps;
class ConcatPdfs;
class ProcessManager;

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

    void onConversionFinished(bool ok);

    void onConcatFinished(bool ok);

private:

    void convertEps2Pdf();

    void showLog() const;

    void showResultDir() const;

    void showPdfIfDemo() const;

    QString dirToShow(bool& pointerToFolderOK) const;

    QPushButton* runButton;

    QHBoxLayout* layout;

    ProcessManager* processManager;

    ConvertAllEps* converter;

    ConcatPdfs* pdf_concat;

    QStatusBar* statusBar;

    QString logFile;

    QString projectPath;

    QString projectName;

    QString finalProjectFolder;
};

#endif // RUNNER_HPP
