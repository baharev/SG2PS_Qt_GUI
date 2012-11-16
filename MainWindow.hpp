#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "HandleSelectedFile.hpp"

class QVBoxLayout;

class InputWidget;
class SettingsWidget;
class Runner;


class MainWindow : public QMainWindow, HandleSelectedFile
{
    Q_OBJECT
    
public:

    explicit MainWindow(const QRect& screen_size, QWidget *parent = 0);

    void printSize();

    ~MainWindow();

private:

    void handleSelectedFile(const QString &file);

    void set_appearance();

    void connect_signal_slots();

    void add_elements();

    InputWidget* inputWidget;

    SettingsWidget* settingsWidget;

    Runner* runner;

    QVBoxLayout* mainLayout;

    const QRect screen_size;
};

#endif // MAINWINDOW_HPP
