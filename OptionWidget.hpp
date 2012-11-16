#ifndef OPTIONWIDGET_HPP
#define OPTIONWIDGET_HPP

#include <QStringList>
#include <QWidget>

class QComboBox;
class QLabel;

class OptionWidget : public QWidget {

    Q_OBJECT

public:

    OptionWidget(QWidget* parent, const QString& key, const QStringList& values);

    QString value() const;

private:

    QComboBox* comboBox;

    QLabel* label;
};

#endif // OPTIONWIDGET_HPP
