#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui/QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(const QRect& screen_size, QWidget *parent = 0);
    ~MainWindow();

private:

    const QRect screen_size;
    void set_appearance();
};

#endif // MAINWINDOW_HPP
