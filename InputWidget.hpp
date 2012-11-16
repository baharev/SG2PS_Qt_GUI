#ifndef INPUTWIDGET_HPP
#define INPUTWIDGET_HPP

#include <QWidget>

class HandleSelectedFile;
class QHBoxLayout;
class QPushButton;
class QLabel;
class QFileDialog;

class HandleSelectedFile;

class InputWidget : public QWidget {

    Q_OBJECT

public:

    explicit InputWidget(HandleSelectedFile* input_handler, QWidget* parent = 0);

private slots:

    void showSelectFileDialog();

private:

    HandleSelectedFile* input_handler;

    QHBoxLayout* fileSelectLayout;

    QPushButton* selectButton;

    QLabel* fileNameLabel;

    QFileDialog* dialog;

    QString filePath;

    QString startDir;
};


#endif // INPUTWIDGET_HPP
