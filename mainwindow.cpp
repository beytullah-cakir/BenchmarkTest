#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cpuTest(new CPUTest(this)) // CPU Test nesnesini oluştur
{
    ui->setupUi(this);

    // Sinyal-Slot bağlantıları
    connect(cpuTest, &CPUTest::updateResult, this, &MainWindow::updateCpuResult);

}

MainWindow::~MainWindow()
{
    delete ui;
}


// CPU sonuçlarını anlık olarak günceller
void MainWindow::updateCpuResult(QString result)
{
    bool ok;
    int duration = ui->timeInput->text().toInt(&ok);
    if (ok && duration > 0) {
        ui->resultLabel->setText("Test başlatılıyor...");
        cpuTest->runTest(duration);
    } else {
        ui->resultLabel->setText("Lütfen geçerli bir süre girin.");
    }
}

