#include "cputest.h"

/*
CPU'nun belirli bir süre içinde yapabileceği işlem sayısını ölçerek
bize CPU hızını veren kod (MHz cinsinde).

Bellek erişimi veya multi-threading kullanmadan saf işlem gücü ölçülüyor.
*/

CPUTest::CPUTest(QObject *parent) : QThread(parent) {}


void CPUTest::runTest() {

    start();
}

void CPUTest::run() {
    volatile double result = 0.0;
    long long operations = 0; //Gerçekleşen işlem sayacı

    auto startTime = std::chrono::high_resolution_clock::now();//Testin başlangıç zamanı


    auto endTime = startTime + std::chrono::seconds(1);//Testin bitiş zamanı


    while (std::chrono::high_resolution_clock::now() < endTime) {

        result += sqrt(operations) + log(operations + 1) + sin(operations) * cos(operations);

        result += pow(operations, 3) - log10(operations + 1);

        result += tan(operations) + exp(operations / 1000.0);

        operations++;
    }

    // Geçen süreyi saniye cinsinden hesaplar.
    double elapsedSeconds = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();


    // MHz hesaplama işlemi
    double mhz = (operations / elapsedSeconds) / 1'000'000.0;


    // CPU hız sonucu
    emit cpuResult(QString("CPU Hızı: %1 MHz").arg(mhz, 0, 'f', 3));
}
