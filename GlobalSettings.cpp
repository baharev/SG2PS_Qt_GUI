// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include "GUISettings.hpp"
#include "GlobalSettings.hpp"

namespace {

GUISettings* options;

}

void initGlobalSettings(GUISettings *settings) {

    options = settings;

}

const GUISettings& opts() {

    return *options;
}

void reloadGlobalSettings() {

    options->readSettings();
}
