#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cpuTest(new CPUTest(this)) // CPU test nesnesini oluşturur
    , ramTest(new RAMTest(this)) // Ram test nesnesini oluşturur

{
    ui->setupUi(this);

    // sinyal slot bağlantıları sağlanır
    connect(cpuTest, &CPUTest::cpuResult, this, &MainWindow::cpuResult);
    connect(ramTest, &RAMTest::ramResult, this, &MainWindow::ramResult);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Kullanıcı başlat butonuna tıkladığında çağrılır
void MainWindow::on_startButton_clicked()
{


    ramTest->runTest();
    cpuTest->startTests();

}

// CPU testi tamamlandığında çağrılır
void MainWindow::cpuResult(QString finalResult)
{
    ui->cpuResult->setText(finalResult);
}
// Ram testi tamamlandığında çağrılır
void MainWindow::ramResult(QString finalResult)
{
    ui->ramResult->setText(finalResult);
}


