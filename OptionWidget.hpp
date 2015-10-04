// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef OPTIONWIDGET_HPP
#define OPTIONWIDGET_HPP

#include <QWidget>
#include <Option.hpp>

class QComboBox;
class QLabel;
class Option;

class OptionWidget : public QWidget {

    Q_OBJECT

public:

    OptionWidget(QWidget* parent, const Option& option, QWidget* mainWindow);

    QString selection2CLI() const;

    void set(const QString& cliLine);

    void selectDefault();

private:

    QComboBox* comboBox;

    QLabel* label;

    const Option opt;
};

#endif // OPTIONWIDGET_HPP
