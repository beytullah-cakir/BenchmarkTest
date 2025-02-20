#ifndef GPUTEST_H
#define GPUTEST_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QElapsedTimer>

class GPUTest : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit GPUTest(QWidget *parent = nullptr);
    ~GPUTest();
    bool isStarted;


protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    QTimer updateTimer;
    QElapsedTimer fpsTimer;
    int frameCount;
    float rotationAngle;


signals:
    void gpuResult(QString result);

private slots:
    void updateScene();
};

#endif // GPUTEST_H
