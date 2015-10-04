// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef INFOWIDGET_HPP
#define INFOWIDGET_HPP

#include <QFrame>
#include <QString>

class QLabel;

class InfoWidget : public QFrame {

     Q_OBJECT

public:

    explicit InfoWidget(QWidget* parent);

    void freezeLabelSize();

    void newProjectSelected(const QString& newProjectPath, const QString& newProjectName);

    void setMode(const QString& mode);

public slots:

    void checkSetFile();

private:

    void updateRgfLabel();

    void updateSetLabel();

    void updateXyLabel();

    bool fileExists(const char extension[]);

    void setOkText(QLabel* lbl, const QString& msg);

    void setWarnText(QLabel* lbl, const QString& msg);

    void setErrorText(QLabel* lbl, const QString& msg);

    void freezeWidth(QLabel* lbl);

    QLabel* projectLabel;

    QLabel* rgfLabel;

    QLabel* setLabel;

    QLabel* xyLabel;

    QLabel* modeLabel;

    QLabel* trjLabel;

    QString projectPath;

    QString projectName;

};

#endif // INFOWIDGET_HPP
