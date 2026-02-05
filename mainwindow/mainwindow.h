#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main_window_labels.h"


#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    QPushButton *setConnectionButton = nullptr;
    QPushButton *eraseMemoryButton   = nullptr;
    QPushButton *writeMemoryButton   = nullptr;
    QPushButton *setCoeffsButton     = nullptr;
    QPushButton *closeButton         = nullptr;

private:

    void setupUi();
    void setupConnections();

    void setupLayouts(QWidget *widget);

};

#endif // MAINWINDOW_H
