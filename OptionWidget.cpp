#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include "OptionWidget.hpp"
#include "LayoutConstants.hpp"


OptionWidget::OptionWidget(QWidget* parent, const QString& key, const QStringList& values)
    : QWidget(parent)
{

    label = new QLabel(key, this);

    comboBox = new QComboBox(this);

    comboBox->addItems(values); // TODO Add QLineEdit to custom values?

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
