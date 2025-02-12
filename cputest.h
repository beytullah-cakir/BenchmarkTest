#ifndef CPUTEST_H
#define CPUTEST_H

#include <QObject>
#include <QThread>
#include <QString>
#include <chrono>
#include <cmath>

class CPUTest : public QThread {
    Q_OBJECT
public:
    explicit CPUTest(QObject *parent = nullptr);
    void runTest(int durationSeconds);

signals:
    void updateResult(QString result);



private:
    int testDuration;
};

#endif // CPUTEST_H
