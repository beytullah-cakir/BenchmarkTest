#ifndef RAMTEST_H
#define RAMTEST_H

#include <QThread>
#include <chrono>
#include <vector>
#include <QString>

class RAMTest : public QThread {
    Q_OBJECT

public:
    explicit RAMTest(QObject *parent = nullptr);
    void runTest(size_t dataSizeMB); // RAM testini başlat

signals:
    void ramResult(const QString &finalResult); // Test tamamlandığında sinyal

protected:
    void run() override; // QThread'in çalıştıracağı fonksiyon

private:
    size_t dataSizeMB; // Test edilecek veri miktarı (MB)
};

#endif // RAMTEST_H
