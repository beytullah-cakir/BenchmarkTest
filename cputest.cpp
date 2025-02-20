#include "cputest.h"


CPUTest::CPUTest(QObject *parent)
    : QThread(parent) {
}


void CPUTest::startTests() {
    start();
}

void CPUTest::run() {
    double total_f = 0.0;
    int processCount = 0;

    std::vector<double> tests = {
        matrixTest(),
        floatingPointTest(),
        memoryTest(),
        threadTest()
    };

    for (const auto& test : tests) {
        total_f += test;
        processCount++;
    }

    double ghz = processCount > 0 ? total_f / processCount : 0.0;
    emit cpuResult(QString("CPU hızı: %1 GHz").arg(ghz, 0, 'f', 3));
}



double CPUTest::matrixTest() {
    const int size = 500;
    const int totalIterations = size * size * size;
    auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::vector<double>> matrix1(size, std::vector<double>(size, 1.0));
        std::vector<std::vector<double>> matrix2(size, std::vector<double>(size, 2.0));
        std::vector<std::vector<double>> result(size, std::vector<double>(size, 0.0));

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
    auto end = std::chrono::high_resolution_clock::now();
    auto timeTaken=std::chrono::duration<double>(end - start).count();
    return totalIterations / timeTaken / 1e9;
}

double CPUTest::floatingPointTest() {
    const int totalIterations = 10000000;
    auto start = std::chrono::high_resolution_clock::now();
        volatile double result = 0.0;
        for (int i = 0; i < totalIterations; i++) {
            result += std::sqrt(i) * std::sin(i) / std::cos(i + 1);
            result += pow(i, 3) - log10(i + 1);
            result += tan(i) + exp(i / 1000.0);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto timeTaken=std::chrono::duration<double>(end - start).count();
        return totalIterations / timeTaken / 1e9;
}

double CPUTest::memoryTest() {
    const size_t size = 10000000;
    auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> data(size);

        // Write test
        for (size_t i = 0; i < size; i++) {
            data[i] = i;
        }

        // Read test
        volatile int sum = 0;
        for (size_t i = 0; i < size; i++) {
            sum += data[i];
        }
        auto end = std::chrono::high_resolution_clock::now();
    auto timeTaken=std::chrono::duration<double>(end - start).count();
    return size * 2 / timeTaken / 1e9;
}

double CPUTest::threadTest() {
    const int numThreads = QThread::idealThreadCount();
    const int totalIterations = numThreads * 1000000;
    auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::thread> threads;
        for (int i = 0; i < numThreads; i++) {
            threads.emplace_back([]() {
                volatile double result = 0.0;
                for (int i = 0; i < 1000000; i++) {
                    result += i * i;
                }
            });
        }

        for (auto& thread : threads) {
            thread.join();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto timeTaken=std::chrono::duration<double>(end - start).count();
    return totalIterations / timeTaken / 1e9;
}
