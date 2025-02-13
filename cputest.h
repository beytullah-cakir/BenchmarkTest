#ifndef CPUTEST_H
#define CPUTEST_H

#include <QObject>
#include <QThread>
#include <QString>
#include <cmath>

class CPUTest : public QThread {
    Q_OBJECT
public:
    explicit CPUTest(QObject *parent = nullptr);
    void runTest(int durationSeconds);

signals:
    //void updateResult(QString result);
    void cpuResult(QString finalResult);

protected:
    void run() override; // QThread'den türeyen sınıf

private:
    int testDuration;
};

#endif // CPUTEST_H
