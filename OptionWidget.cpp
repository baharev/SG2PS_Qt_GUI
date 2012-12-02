// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include "Option.hpp"
#include "OptionWidget.hpp"
#include "LayoutConstants.hpp"


OptionWidget::OptionWidget(QWidget* parent, const Option& opt)
    : QWidget(parent)
{

    label = new QLabel(opt.key, this);

    comboBox = new QComboBox(this);

    comboBox->addItems(opt.values);

    defaultElem = opt.defaultElem;

    comboBox->setCurrentIndex(defaultElem);

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
