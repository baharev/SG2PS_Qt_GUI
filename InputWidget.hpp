// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef INPUTWIDGET_HPP
#define INPUTWIDGET_HPP

#include <QFrame>

class HandleSelectedFile;
class QHBoxLayout;
class QPushButton;
class QFrame;
class QLabel;
class QFileDialog;

class InputWidget : public QFrame {

    Q_OBJECT

public:

    explicit InputWidget(QWidget* parent);

    void freezeLabelSize();

    void newProjectSelected(const QString& newProjectPath, const QString& newProjectName);

private:

    HandleSelectedFile* input_handler;

    QHBoxLayout* fileSelectLayout;

    QPushButton* selectButton;

    QFrame* fileNameFrame;

    QLabel* fileNameLabel;

    QString projectPath;

    QString projectName;
};


#endif // INPUTWIDGET_HPP
