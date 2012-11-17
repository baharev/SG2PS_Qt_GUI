#include "GUISettings.hpp"
#include "GlobalSettings.hpp"

namespace {

const GUISettings* options;

}

void initGlobalSettings(const GUISettings *settings) {

    options = settings;
}

QString getStrOption(const QString& key) {

    return ::options->getStrOption(key);
}

