// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef OPTION_HPP
#define OPTION_HPP

#include <QStringList>

struct Default { };

struct Option {

    Option() { }

    Option(const QString& guiKey, const QString& cliKey);

    Option& operator<<(const QString& value);
    Option& operator<<(const Default& );

    void checkConsistency() const;

    QString toCLIString(int i) const;

    QString key;
    QStringList values;

    QString cliKey;
    QStringList cliValues;

    int defaultElem;
};

typedef QPair<QString,QVector<Option> >  OptionGroup;

int numberOfGroups();

const QVector<OptionGroup>& getOptionGroups();

int wellGroupIndex();

#endif // OPTION_HPP
