// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QStatusBar>
#include "ConvertAllEps.hpp"
#include "ConvertEPS2PDF.hpp"
#include "ErrorMsg.hpp"
#include "GlobalSettings.hpp"

ConvertAllEps::ConvertAllEps(QObject *parent, QStatusBar *mainWindowStatusBar)
: QObject(parent),
  statusBar(mainWindowStatusBar)
{
    converter = new ConvertEPS2PDF;
    directories = new QFileInfoList;
    eps_files   = new QFileInfoList;
    currentFile = new QFileInfo;

    connect(converter, SIGNAL(finished(bool)), SLOT(onSingleFileConversionFinished(bool)));
}

ConvertAllEps::~ConvertAllEps() {

    delete converter;
    delete directories;
    delete eps_files;
    delete currentFile;
}

void ConvertAllEps::run(const QString& project_directory) {

    projectFolder = project_directory;

    findAllFiles();

    loop();
}

void ConvertAllEps::findAllFiles() {

    directories->clear();

    eps_files->clear();

    QDir dir = QDir(projectFolder+"/5_ps_separated/");

    *directories = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name); // TODO Another magic constant

    for (QList<QFileInfo>::iterator subdir=directories->begin(); subdir!=directories->end(); ++subdir) {

        QString subDirPath = subdir->filePath();

        eps_files->append( QDir(subDirPath).entryInfoList(QStringList("*.eps"), QDir::Files, QDir::Name)  );
    }

    qDebug() << "Found" << eps_files->size() << "eps files to convert";
}

void ConvertAllEps::loop() {

    if (eps_files->empty()) {

        statusBar->clearMessage();

        emit finished(true);

        return;
    }

    *currentFile = eps_files->first();

    eps_files->removeFirst();

    QString directory = currentFile->canonicalPath();

    QString eps_file_name = currentFile->fileName();

    statusBar->showMessage("Converting "+eps_file_name, 0);

    converter->convert(directory, eps_file_name);

}

void ConvertAllEps::onSingleFileConversionFinished(bool success) {

    if (success) {

        if (opts().getDeleteEpsOnSuccess()) {

            QFile::remove(currentFile->filePath());
        }

        loop();
    }
    else {

        showErrorMsg("converting "+QDir::toNativeSeparators(currentFile->filePath())+" to PDF failed");

        statusBar->clearMessage();

        emit finished(false);
    }
}
