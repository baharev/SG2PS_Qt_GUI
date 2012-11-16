#ifndef OPTION_HPP
#define OPTION_HPP

struct Option {

    Option(const QString& key_str) : key(key_str) { }

    Option& operator<<(const QString& value_str) { values.append(value_str); return *this; }

    QString key;

    QStringList values;
};

Option opts[] = {

    Option("color") << "red" << "green" << "blue",

    Option("type") << "fast" << "medium" << "slow",

    Option("line width") << "0.3",

};

#endif // OPTION_HPP
