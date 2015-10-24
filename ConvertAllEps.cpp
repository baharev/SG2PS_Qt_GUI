// Copyright (C) 2012-2015, Ali Baharev
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

    // TODO Another magic constant

    QVector<QString> dirs = QVector<QString>();

    dirs.append(projectFolder+"/5_PS_SEPARATED/");

    dirs.append(projectFolder+"/6_WELL_PS_SEPARATED/");

    findAllFiles(dirs);

    loop();
}

void ConvertAllEps::findAllFiles(const QVector<QString>& dirs) {

    directories->clear();

    eps_files->clear();

    foreach(QString dirName, dirs) {

        qDebug() << "Searching" << dirName << "for subdirectories";

        QDir dir = QDir(dirName);

        *directories = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

        for (QList<QFileInfo>::iterator subdir=directories->begin(); subdir!=directories->end(); ++subdir) {

            QString subDirPath = subdir->filePath();

            qDebug() << "Searching" << subDirPath << "for eps files";

            eps_files->append( QDir(subDirPath).entryInfoList(QStringList("*.eps"), QDir::Files, QDir::Name)  );
        }

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

    // Compare with MainWindow closeEvent(), checking for this message
    statusBar->showMessage("Converting "+eps_file_name, 0);

    converter->convert(directory, eps_file_name);

}

void ConvertAllEps::onSingleFileConversionFinished(bool success) {

    success = success && doubleCheckPdfExistence();

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

bool ConvertAllEps::doubleCheckPdfExistence() const {

    const QString epsName = currentFile->filePath();

    const QString pdfName = epsName.left(epsName.size()-4) + ".pdf";

    qDebug() << "PDF name:" << pdfName;

    return QFile::exists(pdfName);
}
