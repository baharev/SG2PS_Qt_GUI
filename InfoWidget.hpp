// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef INFOWIDGET_HPP
#define INFOWIDGET_HPP

#include <QFrame>
#include <QString>

class QLabel;
class QHBoxLayout;
class QVBoxLayout;

class InfoWidget : public QFrame {

     Q_OBJECT

public:

    explicit InfoWidget(QWidget* parent);

    void freezeLabelSize();

    void newProjectSelected(const QString& newProjectPath, const QString& newProjectName);

private:

    void updateRgfLabel();

    void updateSetLabel();

    void updateXyLabel();

    bool fileExists(const char extension[]);

    QString okText(const QString& msg);

    QString warnText(const QString& msg);

    QString errorText(const QString& msg);

    QLabel* projectLabel;

    QLabel* rgfLabel;

    QLabel* setLabel;

    QLabel* xyLabel;

    QVBoxLayout* vboxLayout;

    QHBoxLayout* hboxLayout;

    QString projectPath;

    QString projectName;

};

#endif // INFOWIDGET_HPP
