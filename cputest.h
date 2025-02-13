#ifndef CPUTEST_H
#define CPUTEST_H

#include <QObject>
#include <QThread>
#include <QString>
#include <cmath>
#include <cmath>
#include <QProcess>
#include <qprocess.h>

class CPUTest : public QThread {
    Q_OBJECT
public:
    explicit CPUTest(QObject *parent = nullptr);
    void runTest();

signals:
    //void updateResult(QString result);
    void cpuResult(QString finalResult);

protected:
    void run() override; // QThread'den türeyen sınıf



};

#endif // CPUTEST_H
