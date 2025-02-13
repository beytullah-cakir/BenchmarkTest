#include "ramtest.h"

RAMTest::RAMTest(QObject *parent) : QThread(parent){}

void RAMTest::runTest(size_t sizeMB) {
    dataSizeMB = sizeMB;
    start(); // QThread'in run() fonksiyonunu başlatır
}

void RAMTest::run() {
    size_t dataSize = dataSizeMB * 1024 * 1024; // MB'dan bayta çevir
    std::vector<char> buffer(dataSize, 0); // RAM'de büyük bir alan ayır



    // **Yazma Hızı Testi**
    auto startTime = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < dataSize; i++) {
        buffer[i] = static_cast<char>(i % 256); // Rastgele veri yaz
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    double writeTime = std::chrono::duration<double>(endTime - startTime).count();
    double writeSpeed = (dataSizeMB / writeTime); // MB/s cinsinden hız



    // **Okuma Hızı Testi**
    volatile char temp;
    startTime = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < dataSize; i++) {
        temp = buffer[i]; // RAM'den okuma işlemi yap
    }
    endTime = std::chrono::high_resolution_clock::now();
    double readTime = std::chrono::duration<double>(endTime - startTime).count();
    double readSpeed = (dataSizeMB / readTime); // MB/s cinsinden hız

    //emit updateResult(QString("RAM Okuma Hızı: %1 MB/s").arg(readSpeed));
    emit ramResult(QString("RAM Okuma Hızı: %1 MB/s").arg(readSpeed));
}
