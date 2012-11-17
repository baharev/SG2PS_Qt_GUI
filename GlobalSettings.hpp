#ifndef GLOBALSETTINGS_HPP
#define GLOBALSETTINGS_HPP

#include <QString>

class GUISettings;

QString getStrOption(const QString& key);

void initGlobalSettings(const GUISettings* settings);

#endif // GLOBALSETTINGS_HPP
