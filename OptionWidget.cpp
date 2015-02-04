// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include "Option.hpp"
#include "OptionWidget.hpp"
#include "LayoutConstants.hpp"


OptionWidget::OptionWidget(QWidget* parent, const Option& option)
    : QWidget(parent), opt(option)
{

    label = new QLabel(opt.key, this);

    comboBox = new QComboBox(this);

    comboBox->addItems(opt.values);

    comboBox->setCurrentIndex(opt.defaultElem);

//    QFont labelFont = label->font();
//    labelFont.setStretch(QFont::SemiCondensed);
//    label->setFont(labelFont);

//    comboBox->setFont(labelFont);


    QHBoxLayout* layout = new QHBoxLayout(this);

    layout->setMargin(0);

    layout->setSpacing(SPACING);

    layout->addWidget(label);

    layout->addWidget(comboBox);

    layout->addStretch(1);

    setLayout(layout);
}

void OptionWidget::selectDefault() {

    comboBox->setCurrentIndex(opt.defaultElem);
}

QString OptionWidget::selection2CLI() const {

    int i = comboBox->currentIndex();

    return opt.toCLIString(i);
}

void OptionWidget::set(const QString& cliLine) {

    int i = opt.toIndex(cliLine);

    comboBox->setCurrentIndex(i);
}
