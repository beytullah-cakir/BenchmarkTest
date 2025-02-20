#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cpuTest(new CPUTest(this)) // CPU test nesnesini oluşturur
    , ramTest(new RAMTest(this)) // Ram test nesnesini oluşturur
    , gpuTest(new GPUTest(this))



{
    ui->setupUi(this);
    gpuTest->setParent(ui->gpuWidget);
    gpuTest->setGeometry(ui->gpuWidget->rect());

    // sinyal slot bağlantıları sağlanır
    connect(cpuTest, &CPUTest::cpuResult, this, &MainWindow::cpuResult);
    connect(ramTest, &RAMTest::ramResult, this, &MainWindow::ramResult);
    connect(gpuTest, &GPUTest::gpuResult, this, &MainWindow::gpuResult);
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
    gpuTest->update();
    gpuTest->isStarted=true;

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

void MainWindow::gpuResult(QString result)
{
    if(gpuTest->isStarted==true)
        ui->gpuResult->setText(result);
}


