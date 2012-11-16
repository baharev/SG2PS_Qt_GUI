#ifndef SETTINGSWIDGET_HPP
#define SETTINGSWIDGET_HPP

#include <QWidget>

class QHBoxLayout;
class QVBoxLayout;


class SettingsWidget: public QWidget {

    Q_OBJECT

public:

    explicit SettingsWidget(QWidget* parent);

    void tryLoadSettings(const QString& rgfFileName);

private:

    void fillColumn(QVBoxLayout* col, int row_beg, int row_end);

    QHBoxLayout* panel;

    QVBoxLayout* leftColumn;

    QVBoxLayout* rightColumn;
};

#endif // SETTINGSWIDGET_HPP
