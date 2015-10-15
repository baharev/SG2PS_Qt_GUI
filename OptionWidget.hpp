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

    OptionWidget(QWidget* parent, const Option& option);

    QString selection2CLI() const;

    const QString& cliKey() const;

    void selectDefault();

    int indexOf(const QString& s);

    void setCurrentIndex(int i);

    void setForbidden(bool flag);

private:

    QComboBox* comboBox;

    QLabel* label;

    const Option opt;
};

#endif // OPTIONWIDGET_HPP
