// Copyright (C) 2016, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QStringList>
#include "ConcatPdfs.hpp"
#include "GlobalSettings.hpp"

ConcatPdfs::ConcatPdfs(QObject *parent) : QObject(parent) {

    pdf_concat = new QProcess(this);

    connect(pdf_concat, SIGNAL(error(QProcess::ProcessError)),
                        SLOT(onError(QProcess::ProcessError)));

    connect(pdf_concat, SIGNAL(finished(int , QProcess::ExitStatus )),
                        SLOT(onFinished(int , QProcess::ExitStatus )));
}

ConcatPdfs::~ConcatPdfs() { }

void ConcatPdfs::run(const QString& directory, const QString& projectName) {

    QString program_name = opts().getPdfConcat();

    QStringList args;

    args << directory << (projectName + ".pdf");

    pdf_concat->setWorkingDirectory(directory);

    pdf_concat->start(program_name, args);
}

void ConcatPdfs::onError(QProcess::ProcessError ) {

    emit finished(false);
}

void ConcatPdfs::onFinished(int exitCode, QProcess::ExitStatus exitStatus) {

    if (exitStatus==QProcess::CrashExit) {
        // Also handled in onError, apperantly
        return;
    }

    bool success = (exitCode==0)? true : false;

    emit finished(success);
}
