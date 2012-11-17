// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef GUISETTINGS_HPP
#define GUISETTINGS_HPP

#include <QMap>
#include <QString>

class GUISettings;

void initGlobalSettings(const GUISettings* settings);

class GUISettings {

public:

    GUISettings();

    void readSettings();

    QString getStrOption(const QString& key) const;

private:

    void errorKeyNotFound(const QString& key) const;

    void showError(const QString& what) const;

    void setValue(const QString& key, const QString& value);

    QMap<QString,QString> strOptions;

};

#endif // GUISETTINGS_HPP
