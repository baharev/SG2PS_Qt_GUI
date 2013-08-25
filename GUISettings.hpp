// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifndef GUISETTINGS_HPP
#define GUISETTINGS_HPP

template <class Key, class T> class QMap;
template <typename T> class QVector;
class QString;
class GUISettings;
class QTextStream;
struct Pair;

void initGlobalSettings(GUISettings* settings);

class GUISettings {

public:

    GUISettings();

    void readSettings();

    QString getSettingsFileName() const;

    QString getExecutableName() const;

    QString getEps2PdfConverter() const;

    QString getStartBrowsingFromDirectory() const;

    QString getTextEditor() const;

    QString getFileManager() const;

    bool getConvertToPdf() const;

    bool getDeleteEpsOnSuccess() const;

    bool getShowLogfile() const;

    bool getShowResultDirectory() const;

    QString getPdfViewer() const;

    QString getSpreadsheet() const;

    QString getSpreadsheetFlag() const;

    bool hasDefinedPdfViewer() const;

    bool hasDefinedSpreadsheet() const;

    ~GUISettings();

private:

    void setValue(const QString& key, const QString& value);

    QString executable_name() const;

    QString eps2pdf_converter() const;

    QString start_browsing_from_directory() const;

    QString text_editor() const;

    QString file_manager() const;

    QString convert_to_pdf() const;

    QString delete_eps_on_success() const;

    QString show_logfile() const;

    QString show_result_directory() const;

    QString pdf_viewer() const;

    QString spreadsheet() const;

    QString spreadsheet_flag() const;

    QString getStrOption(const QString& key) const;

    void errorKeyNotFound(const QString& key) const;

    void showError(const QString& what) const;

    QVector<Pair> readPairs() const;

    void parseSettingsFile(QTextStream& in, QVector<Pair>& userOptions) const;

    void dumpSettings() const;

    QString removeComment(const QString& origLine) const;

    QMap<QString,QString>& strOptions;

};

#endif // GUISETTINGS_HPP
