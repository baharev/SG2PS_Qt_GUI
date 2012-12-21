// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include "GUISettings.hpp"
#include "GlobalSettings.hpp"

namespace {

const GUISettings* options;

}

void initGlobalSettings(const GUISettings *settings) {

    options = settings;

}

const GUISettings& opts() {

    return *options;
}
