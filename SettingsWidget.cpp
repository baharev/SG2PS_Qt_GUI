// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "SettingsWidget.hpp"
#include "OptionWidget.hpp"
#include "Option.hpp"
#include "LayoutConstants.hpp"

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent) {

    QFrame* left = new QFrame(this);

    leftColumn = new QVBoxLayout(left);

    QFrame* right = new QFrame(this);

    rightColumn = new QVBoxLayout(right);


    leftColumn->addWidget(new QLabel("Settings"));

    rightColumn->addWidget(new QLabel(""));


    int n_opts = sizeof(opts) / sizeof(opts[0]);

    int left_size = (n_opts+1) / 2;

    fillColumn(leftColumn,          0, left_size);
    //fillColumn(leftColumn,          0, n_opts);

    fillColumn(rightColumn, left_size, n_opts);



    left->setFrameStyle(QFrame::WinPanel | QFrame::Raised);

    right->setFrameStyle(QFrame::WinPanel | QFrame::Raised);



    panel = new QHBoxLayout(this);

    panel->addWidget(left);

    panel->addWidget(right);

    panel->addStretch(1);

    setLayout(panel);

}

void SettingsWidget::fillColumn(QVBoxLayout* col, int opt_first, int opt_last) {

    for (int i=opt_first; i<opt_last; ++i) {

        const QString& key = opts[i].key;

        const QStringList& values = opts[i].values;

        col->addWidget(new OptionWidget(this, key, values));
    }

    col->addStretch(1);

    col->setMargin(MARGIN);

    col->setSpacing(SPACING);
}
