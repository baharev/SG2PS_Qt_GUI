// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef INFOWIDGET_HPP
#define INFOWIDGET_HPP

#include <QFrame>
#include <QString>

class QLabel;
class QRadioButton;


class InfoWidget : public QFrame {

     Q_OBJECT

public:

    explicit InfoWidget(QWidget* parent);

    void freezeLabelSize();

    void newProjectSelected(const QString& newProjectPath, const QString& newProjectName);

    void setFocus(Qt::FocusReason reason);

public slots:

    void checkSetFile();

    void newSettingsFileLoaded(bool isWell, bool loadedCleanly);

signals:

    void runModeChanged(bool isWell);

private slots:

    void updateModePanel();

private:

    void updateRgfLabel();

    void updateSetLabel(bool isOK);

    void updateXyLabel();

    bool fileExists(const char extension[]);

    void setOkText(QLabel* lbl, const QString& msg);

    void setWarnText(QLabel* lbl, const QString& msg);

    void setErrorText(QLabel* lbl, const QString& msg);

    void freezeWidth(QLabel* lbl);

    QString projectPath;
    QString projectName;
    QLabel* projectLabel;

    QRadioButton* fieldRadio;
    QRadioButton* wellRadio;
    QLabel* trjLabel;

    QLabel* rgfLabel;
    QLabel* setLabel;
    QLabel* xyLabel;

};

#endif // INFOWIDGET_HPP
