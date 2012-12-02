// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef OPTION_HPP
#define OPTION_HPP



struct Default { };

const Default setDefault;

struct Option {

    Option(const QString& key_str);

    Option& operator<<(const QString& value_str);

    Option& operator<<(const Default& );

    static const Option* getOpts();

    static int getOptSize();

    QString key;

    QStringList values;

    int defaultElem;

};



#endif // OPTION_HPP
