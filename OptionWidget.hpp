// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef OPTIONWIDGET_HPP
#define OPTIONWIDGET_HPP

#include <QWidget>

class QComboBox;
class QLabel;
class Option;

class OptionWidget : public QWidget {

    Q_OBJECT

public:

    OptionWidget(QWidget* parent, const Option& opt);

    QString value() const;

    void selectDefault();

private:

    QComboBox* comboBox;

    QLabel* label;

    int defaultElem;
};

#endif // OPTIONWIDGET_HPP
