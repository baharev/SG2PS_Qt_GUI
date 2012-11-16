#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "SettingsWidget.hpp"
#include "OptionWidget.hpp"
#include "Option.hpp"

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent) {

    QFrame* left = new QFrame(this);

    leftColumn = new QVBoxLayout(left);

    QFrame* right = new QFrame(this);

    rightColumn = new QVBoxLayout(right);


    QLabel* leftLabel = new QLabel("Settings");

    leftLabel->setMinimumWidth(1);


    leftColumn->addWidget(leftLabel);

    rightColumn->addWidget(new QLabel(""));


    int n_opts = sizeof(opts) / sizeof(opts[0]);

    int left_size = (n_opts+1) / 2;

    fillColumn(leftColumn,          0, left_size);

    fillColumn(rightColumn, left_size, n_opts);


    left->setMinimumWidth(1);

    right->setMinimumWidth(1);

    left->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    right->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);



    panel = new QHBoxLayout(this);

    panel->addWidget(left);

    panel->addWidget(right);

    //panel->addWidget(new QWidget(this));

    panel->addStretch(1);

    setLayout(panel);

}

void SettingsWidget::fillColumn(QVBoxLayout* col, int opt_first, int opt_last) {

    for (int i=opt_first; i<opt_last; ++i) {

        const QString& key = opts[i].key;

        const QStringList& values = opts[i].values;

        col->addWidget(new OptionWidget(this, key, values));
    }

    col->addStretch();
}
