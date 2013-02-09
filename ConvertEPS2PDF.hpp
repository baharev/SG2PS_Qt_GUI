// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef CONVERTEPS2PDF_HPP
#define CONVERTEPS2PDF_HPP

#include <QObject>
#include <QProcess>

class ConvertEPS2PDF : public QObject {

    Q_OBJECT

public:

    ConvertEPS2PDF();

    void convert(const QString& directory, const QString& eps_file_name);

signals:

    void finished(bool success);

private slots:

    void onError(QProcess::ProcessError error);

    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:

    QProcess* eps2pdf;

};

#endif // CONVERTEPS2PDF_HPP
