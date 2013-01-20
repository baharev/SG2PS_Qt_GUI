// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

class QString;

bool openWithDefaultApp(const QString& file);

void openDirectoryWithFileManager(const QString& directory);

void openInTextEditor(const QString& fileName);

void openPDF(const QString& fileName);

void showInFileManager(const QString& directory);

void openSpreadsheet(const QString& file);

QString back_end_version();

QString back_end_version_id();

#endif // LAUNCHER_HPP
