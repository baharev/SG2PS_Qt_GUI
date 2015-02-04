// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef OPTION_HPP
#define OPTION_HPP

#include <QStringList>

struct Default { };

struct Option {

    // FIXME Remove
    static const Option* getOpts();
    static int getOptSize();

    Option() { }

    Option(const QString& guiKey, const QString& cliKey);

    Option& operator<<(const QString& value);
    Option& operator<<(const Default& );

    void checkConsistency() const;

    QString toCLIString(int i) const;
    int toIndex(const QString& cliLine) const;

    QString key;
    QStringList values;

    QString cliKey;
    QStringList cliValues;

    int defaultElem;
};

#endif // OPTION_HPP
