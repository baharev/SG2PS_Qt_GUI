#include <QString>
#include "ResolveExitCode.hpp"
#include "ExitStatus.hpp"

QString resolveExitCode(int exitCode) {

    QString msg;

    switch (exitCode) {

    case ExitStatus::OK:
        break;
    case ExitStatus::CONFIG_ERROR:
        msg = "error in the .set file";
        break;
    case ExitStatus::FAILURE:
        msg = "the executable failed";
        break;
    case ExitStatus::BUG:
        msg = "this is a bug, please report it";
        break;
    case ExitStatus::UNKNOWN_ERROR:
        msg = "unknown error happened in the external executable";
        break;
    default:
        msg = "implementation not updated properly";

    }

    return msg;
}

