// cputest.h
#ifndef CPUTEST_H
#define CPUTEST_H

#include <QObject>
#include <QString>
#include <QThread>
#include <cmath>
#include <QDebug>

class CPUTest : public QThread {
    Q_OBJECT

public:
    explicit CPUTest(QObject *parent = nullptr);
    void startTests();


protected:
    void run() override;

signals:
    void cpuResult(QString result);

private:
    double matrixTest();
    double floatingPointTest();
    double memoryTest();
    double threadTest();
};

#endif // CPUTEST_H
