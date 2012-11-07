#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui/QMainWindow>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    MainWindow(const QRect& screen_size, QWidget *parent = 0);

    ~MainWindow();

public slots:

    void showSelectFileDialog();

private:

    void set_appearance();

    void connect_signal_slots();

    void add_elements();

    QVBoxLayout mainLayout;

    QHBoxLayout layoutSelectFile;

    QPushButton selectFileButton;

    QFileDialog dialog;

    const QRect screen_size;
};

#endif // MAINWINDOW_HPP
