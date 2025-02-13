#include "ramtest.h"

RAMTest::RAMTest(QObject *parent) : QThread(parent) {}

void RAMTest::runTest(size_t sizeMB) {
    dataSizeMB = sizeMB;
    start(); // QThread'in run() fonksiyonunu başlatır
}

void RAMTest::run() {
    size_t dataSize = dataSizeMB * 1024 * 1024; // MB -> Bayt çevirme
    std::vector<char> buffer(dataSize, 0); // RAM'de alan ayır

    // yazma hızı
    auto startTime = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < dataSize; i++) {
        buffer[i] = static_cast<char>(i % 256); // Rastgele veri yaz
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    double writeTime = std::chrono::duration<double>(endTime - startTime).count();
    double writeSpeedMT = (dataSize / writeTime) / 1'000'000.0; // Yazma hızı (MT/s)



    // okuma hızı
    volatile char temp;
    startTime = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < dataSize; i++) {
        temp = buffer[i]; // Veriyi RAM'den oku
    }
    endTime = std::chrono::high_resolution_clock::now();
    double readTime = std::chrono::duration<double>(endTime - startTime).count();
    double readSpeedMT = (dataSize / readTime) / 1'000'000.0; // Okuma hızı (MT/s)

    // ortalamayız hesaplar
    double avgSpeedMT = (writeSpeedMT + readSpeedMT) / 2.0;



    emit ramResult(QString("RAM Hızı: %1 MT/s").arg(avgSpeedMT, 0, 'f', 3));
}

