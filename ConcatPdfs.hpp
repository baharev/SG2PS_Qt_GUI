// Copyright (C) 2016, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef CONCATPDFS_HPP
#define CONCATPDFS_HPP

#include <QObject>
#include <QProcess>
#include <QString>

class ConcatPdfs : public QObject {

    Q_OBJECT

public:

    ConcatPdfs(QObject* parent);

    void run(const QString& directory, const QString& projectName);

    ~ConcatPdfs();

signals:

    void finished(bool success);

private slots:

    void onError(QProcess::ProcessError error);

    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:

    QProcess* pdf_concat;
};

#endif // CONCATPDFS_H
