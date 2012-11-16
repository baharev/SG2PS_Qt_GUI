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

    comboBox->addItems(values);


    QHBoxLayout* layout = new QHBoxLayout(this);

    layout->setMargin(0);

    layout->setSpacing(SPACING);

    layout->addWidget(label);

    layout->addWidget(comboBox);

    layout->addStretch(1);

    setLayout(layout);
}
