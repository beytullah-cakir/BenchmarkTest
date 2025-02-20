#include "ramtest.h"

/*
Ramdan 100 MB lik yer ayırıyoruz
bu yere veri yazıp sonrasında okuyoruz
yazma ve okuma hızlarının ortalamasını alarak genel ram hızını belirliyoruz
*/

RAMTest::RAMTest(QObject *parent) : QThread(parent) {}

void RAMTest::runTest() {
    start();
}

void RAMTest::run() {
    size_t dataSize = 100 * 1024 * 1024; // MB -> Bayt çevirme
    std::vector<int> buffer(dataSize, 0); // RAM'de alan ayır

    // Yazma hızını hesaplar
    auto startTime = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < dataSize; i++) {
        buffer[i] = rand(); // Rastgele veri yaz
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    double writeTime = std::chrono::duration<double>(endTime - startTime).count();
    double writeSpeedMT = (dataSize / writeTime) / 1'000'000.0;



    // Okuma hızını hesaplar
    volatile int temp;
    startTime = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < dataSize; i++) {
        temp = buffer[i]; // Veriyi RAM den okur
    }
    endTime = std::chrono::high_resolution_clock::now();
    double readTime = std::chrono::duration<double>(endTime - startTime).count();
    double readSpeedMT = (dataSize / readTime) / 1'000'000.0; // Okuma hızı (MT/s)

    // Ortalama hızı hesaplar
    double avgSpeedMT = (writeSpeedMT + readSpeedMT) / 2.0;
    emit ramResult(QString("RAM Hızı: %1 MT/s").arg(avgSpeedMT, 0, 'f', 3));
}

