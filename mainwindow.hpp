#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui>
#include "HandleSelectedFile.hpp"

class InputWidget;

class MainWindow : public QMainWindow, HandleSelectedFile
{
    Q_OBJECT
    
public:

    MainWindow(const QRect& screen_size, QWidget *parent = 0);

    ~MainWindow();

private:

    void handleSelectedFile(const QString &file);

    void set_appearance();

    void connect_signal_slots();

    void add_elements();

    InputWidget* inputWidget;

    QVBoxLayout* mainLayout;

    const QRect screen_size;
};

#endif // MAINWINDOW_HPP
