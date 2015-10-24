// Copyright (C) 2012-2015, Ali Baharev
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
        msg = "problems with the data file, please check the log / read the manual";
        break;
    case ExitStatus::SET_ERROR:
        msg = "failed to pass the settings, this is likely to be a bug, please report it at sg2ps@sg2ps.eu";
        break;
    case ExitStatus::XY_ERROR:
        msg = "problems with the coordinate file, please check the log / read the manual";
        break;
    case ExitStatus::TRJ_ERROR:
        msg = "problems with the trajectory file, please check the log / read the manual";
        break;
    case ExitStatus::ARG_ERROR:
        msg = "apparently an argument passing error, please report it at sg2ps@sg2ps.eu";
        break;
    case ExitStatus::BUG:
        msg = "this is a bug, please report it at sg2ps@sg2ps.eu";
        break;
    case ExitStatus::LOGIC_ERROR:
        msg = "a bug has been detected in the external executable, please report it at sg2ps@sg2ps.eu";
        break;
    case ExitStatus::RUNTIME_ERROR:
        msg = "a runtime error has occured, please check the log";
        break;
    case ExitStatus::STD_EXCEPTION:
        msg = "please check the log, not quite clear what happened, please report it at sg2ps@sg2ps.eu";
        break;
    case ExitStatus::UNKNOWN_ERROR:
        msg = "unknown error happened in the external executable, please report it at sg2ps@sg2ps.eu";
        break;
    default:
        msg = "implementation not updated properly, please report it at sg2ps@sg2ps.eu";

    }

    return msg;
}
