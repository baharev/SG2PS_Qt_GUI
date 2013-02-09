// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDebug>
#include "ConvertEPS2PDF.hpp"
#include "GlobalSettings.hpp"
#include "ProcessManager.hpp"

ConvertEPS2PDF::ConvertEPS2PDF() {

    eps2pdf = new QProcess(this);

    connect(eps2pdf, SIGNAL(error(QProcess::ProcessError)),
                     SLOT(onError(QProcess::ProcessError)));

    connect(eps2pdf, SIGNAL(finished(int , QProcess::ExitStatus )),
                     SLOT(onFinished(int , QProcess::ExitStatus )));

}

void ConvertEPS2PDF::convert(const QString& directory, const QString &eps_file_name) {

    QString program_name = opts().getEps2PdfConverter();

    QStringList eps_name(eps_file_name);

    eps2pdf->setWorkingDirectory(directory);

    qDebug() << directory <<  ": " << program_name << eps_file_name;

    eps2pdf->start(program_name, eps_name);
}

void ConvertEPS2PDF::onError(QProcess::ProcessError error) {

    qDebug() << "ConvertEPS2PDF::onError  error =" << error;

    emit finished(false);
}

void ConvertEPS2PDF::onFinished(int exitCode, QProcess::ExitStatus exitStatus) {

    if (exitStatus==QProcess::CrashExit) {
        qDebug() << "Also handled in onError, apperantly";
        return;
    }

    bool success = (exitCode==0)? true : false;

    emit finished(success);
}


