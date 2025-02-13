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
            result += sqrt(operations) + log(operations + 1) + sin(operations);
            operations++;

            // Her saniyede bir sonucu güncelle
            if (operations % 10'000'000 == 0) {
                double elapsedSeconds = std::chrono::duration<double>(
                                            std::chrono::high_resolution_clock::now() - startTime
                                            ).count();

                double mips = (operations / 1'000'000.0) / elapsedSeconds;

            }
        }

        double elapsedSeconds = std::chrono::duration<double>(
                                    std::chrono::high_resolution_clock::now() - startTime
                                    ).count();
        double mips = (operations / 1'000'000.0) / elapsedSeconds;

        emit cpuResult(QString("CPU Hızı: %1 MIPS").arg(mips));

}
