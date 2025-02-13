#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cputest.h"
#include "ramtest.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void cpuResult(QString finalResult);
    void ramResult(QString result);



private:
    Ui::MainWindow *ui;
    CPUTest *cpuTest;
    RAMTest *ramTest;
};

#endif // MAINWINDOW_H
