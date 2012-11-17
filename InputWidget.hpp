#ifndef INPUTWIDGET_HPP
#define INPUTWIDGET_HPP

#include <QFrame>

class HandleSelectedFile;
class QHBoxLayout;
class QPushButton;
class QFrame;
class QLabel;
class QFileDialog;

class InputWidget : public QFrame {

    Q_OBJECT

public:

    explicit InputWidget(QWidget* parent = 0);

    void freezeLabelSize();

signals:

    void inputFileSelected(const QString& fileNameWithPath);

private slots:

    void showSelectFileDialog();

private:

    HandleSelectedFile* input_handler;

    QHBoxLayout* fileSelectLayout;

    QPushButton* selectButton;

    QFrame* fileNameFrame;

    QLabel* fileNameLabel;

    QFileDialog* dialog;

    QString filePath;

    QString startDir;
};


#endif // INPUTWIDGET_HPP
