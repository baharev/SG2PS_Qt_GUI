// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QString>
#include "ResolveExitCode.hpp"
#include "ExitStatus.hpp"

QString resolveExitCode(int exitCode) {

    QString msg;

    switch (exitCode) {

    case ExitStatus::OK:
        break;
    case ExitStatus::RGF_ERROR:
        msg = "failed to read the data file, please check the log";
        break;
    case ExitStatus::RUNTIME_ERROR:
        msg = "runtime error occured in the external executable, please check the log";
        break;
    case ExitStatus::BUG:
        msg = "this is a bug, please report it";
        break;
    case ExitStatus::UNKNOWN_ERROR:
        msg = "unknown error happened in the external executable, please report it";
        break;
    default:
        msg = "implementation not updated properly, please report it";

    }

    return msg;
}
