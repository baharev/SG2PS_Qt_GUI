// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef GUISETTINGS_HPP
#define GUISETTINGS_HPP

template <class Key, class T> class QMap;
template <typename T> class QVector;
class QString;
class GUISettings;
struct Pair;

void initGlobalSettings(const GUISettings* settings);

class GUISettings {

public:

    GUISettings();

    void readSettings();

    QString getStrOption(const QString& key) const;

    ~GUISettings();

private:

    void errorKeyNotFound(const QString& key) const;

    void showError(const QString& what) const;

    void setValue(const QString& key, const QString& value);

    void readPairs();

    void dumpSettings();

    QString removeComment(const QString& origLine);

    QMap<QString,QString>& strOptions;

    QVector<Pair>& userOptions;

};

#endif // GUISETTINGS_HPP
