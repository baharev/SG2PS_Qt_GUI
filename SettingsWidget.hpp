// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef SETTINGSWIDGET_HPP
#define SETTINGSWIDGET_HPP

#include <QWidget>
#include <QString>
#include <QVector>

class QHBoxLayout;
class QVBoxLayout;
class OptionWidget;


class SettingsWidget: public QWidget {

    Q_OBJECT

public:

    explicit SettingsWidget(QWidget* parent);

public slots:

    void tryLoadSettings(const QString& rgfFileName);

    void writeSettings();

private:

    void fillColumn(QVBoxLayout* col, int row_beg, int row_end);

    void reset_defaults();

    void loadSettings();

    QString setFileName;

    QHBoxLayout* panel;

    QVBoxLayout* leftColumn;

    QVBoxLayout* rightColumn;

    QVector<OptionWidget*> optionWidgets;
};

#endif // SETTINGSWIDGET_HPP
