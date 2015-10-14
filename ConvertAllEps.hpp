// Copyright (C) 2012-2015, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef CONVERTALLEPS_H
#define CONVERTALLEPS_H

#include <QObject>
#include <QString>

class ConvertEPS2PDF;

class QFileInfo;
template <typename T> class QList;
class QStatusBar;


class ConvertAllEps : public QObject {

    Q_OBJECT

public:

    ConvertAllEps(QObject* parent, QStatusBar* mainWindowStatusBar);

    void run(const QString& project_directory);

    ~ConvertAllEps();

signals:

    void finished(bool done); // false means failed

private slots:

    void onSingleFileConversionFinished(bool success);

private:

    void findAllFiles(const QVector<QString>& dirs);

    void loop();

    QString projectFolder;

    QStatusBar* statusBar;

    QFileInfo* currentFile;

    QList<QFileInfo>* directories;

    QList<QFileInfo>* eps_files;

    ConvertEPS2PDF* converter;

};

#endif // CONVERTALLEPS_H
