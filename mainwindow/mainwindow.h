#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main_window_labels.h"


#include <QMainWindow>
#include <QApplication>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    // declaring buttons:
    QPushButton *setConnectionButton = nullptr;
    QPushButton *eraseMemoryButton   = nullptr;
    QPushButton *writeMemoryButton   = nullptr;
    QPushButton *setCoeffsButton     = nullptr;
    QPushButton *closeButton         = nullptr;

private:

    void setupUi();
    void setupConnections();

    void setupLayouts(QWidget *parentWidget);

    void setupButtonLayout();
    void setupConsoleLayout();

    QHBoxLayout *mainLayout = nullptr;
    QVBoxLayout *buttonLayout = nullptr;
    QVBoxLayout *consoleLayout = nullptr;

};

#endif // MAINWINDOW_H
