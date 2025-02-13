#include "cputest.h"

CPUTest::CPUTest(QObject *parent) : QThread(parent){} // Varsayılan süre 2 saniye

void CPUTest::runTest(int durationSeconds) {
    testDuration = durationSeconds;
    start(); // QThread'in run() fonksiyonunu başlat
}

void CPUTest::run() {
    volatile double result = 0.0;
    long long operations = 0;

    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = startTime + std::chrono::seconds(testDuration);

    while (std::chrono::high_resolution_clock::now() < endTime) {
        result += sqrt(operations) + log(operations + 1) + sin(operations) * cos(operations);
        result += pow(operations, 3) - log10(operations + 1);
        result += tan(operations) + exp(operations / 1000.0);
        operations++;
    }

    double elapsedSeconds = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();

    // GHz hesaplama: (İşlem sayısı / Geçen süre) / 1.000.000.000
    double ghz = (operations / elapsedSeconds) / 1'000'000'000.0;

    emit cpuResult(QString("CPU Hızı: %1 GHz").arg(ghz, 0, 'f', 3)); // 3 basamağa kadar gösterim
}

