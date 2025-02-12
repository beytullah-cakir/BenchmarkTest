#include "cputest.h" // CPUTest başlık dosyasını içe aktarır

// CPUTest sınıfının yapıcı fonksiyonu
CPUTest::CPUTest(QObject *parent){
    runTest(5);
}

// Testi başlatan fonksiyon
void CPUTest::runTest(int durationSeconds) {
    testDuration = durationSeconds; // Kullanıcıdan alınan süreyi ayarlar
    volatile double result = 0.0; // Matematiksel işlemlerin sonucunu tutan değişken (volatile: optimize edilmesini önler)
    long long operations = 0; // Yapılan işlem sayısını takip eder

    auto startTime = std::chrono::high_resolution_clock::now(); // Başlangıç zamanını alır
    auto endTime = startTime + std::chrono::seconds(testDuration); // Bitiş zamanını hesaplar

    // Belirtilen süre boyunca işlemleri gerçekleştir
    while (std::chrono::high_resolution_clock::now() < endTime) {
        // Matematiksel işlemler (CPU'yu zorlamak için)
        result += sqrt(operations) + log(operations + 1) + sin(operations);
        operations++; // İşlem sayacını artır

        // Her 10 milyon işlemde bir sonucu güncelle
        if (operations % 10'000'000 == 0) {
            double elapsedSeconds = std::chrono::duration<double>(
                                        std::chrono::high_resolution_clock::now() - startTime
                                        ).count(); // Geçen süreyi hesapla

            double mips = (operations / 1'000'000.0) / elapsedSeconds; // MIPS (Milyon İşlem/Saniye) hesapla
            emit updateResult(QString("CPU Hızı: %1 MIPS").arg(mips)); // Sonucu GUI'ye veya konsola gönder
        }
    }

    // Test süresi tamamlandığında son hesaplamayı yap
    double elapsedSeconds = std::chrono::duration<double>(
                                std::chrono::high_resolution_clock::now() - startTime
                                ).count(); // Toplam geçen süreyi hesapla

    double mips = (operations / 1'000'000.0) / elapsedSeconds; // Nihai MIPS değerini hesapla



}

