// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

class QString;

bool openWithDefaultApp(const QString& file);

bool openWithAppAssoc(const QString& file, const QString& extension);

bool openWithShortAppname(const QString& nativeFilename, const QString& shortAppName, const QString& flag);

bool hasAssociatedApp(const wchar_t* extension);

void openDirectoryWithFileManager(const QString& directory);

void openInTextEditor(const QString& fileName);

bool openPDF(const QString& fileName);

void showInFileManager(const QString& directory);

bool openSpreadsheet(const QString& file);

bool isInstalledSoftwareOK();

QString back_end_was_built_on();

QString version_id_of_back_end();

#endif // LAUNCHER_HPP
