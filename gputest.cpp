#include "gpuTest.h"  // GPUTest sınıfının başlık dosyasını içerir.
#include <QOpenGLShaderProgram>  // OpenGL shader programları için gerekli başlık dosyası.


// GPUTest sınıfının kurucu metodu. QWidget'i temel alır ve OpenGL bileşeni olarak kullanılır.
GPUTest::GPUTest(QWidget *parent)
    : QOpenGLWidget(parent), frameCount(0), rotationAngle(0.0f),isStarted(false) { // Başlangıç değerlerini ayarlar.

    // updateTimer zamanlayıcısını updateScene fonksiyonuna bağlar.
    connect(&updateTimer, &QTimer::timeout, this, &GPUTest::updateScene);

    // Zamanlayıcıyı başlatır ve her 16 milisaniyede bir sahneyi günceller (yaklaşık 60 FPS).
    updateTimer.start(16);

    // FPS hesaplaması için süreölçeri başlatır.
    fpsTimer.start();
}

// GPUTest sınıfının yıkıcı metodu. Ekstra temizlik gerektirmiyor.
GPUTest::~GPUTest() {}

// OpenGL bağlamını başlatan fonksiyon.
void GPUTest::initializeGL() {
    initializeOpenGLFunctions(); // OpenGL işlevlerini başlatır.
    glEnable(GL_DEPTH_TEST); // Derinlik testini etkinleştirerek 3D çizimleri doğru şekilde işler.
}

// OpenGL görünüm alanını pencere boyutuna göre ayarlar.
void GPUTest::resizeGL(int w, int h) {
    glViewport(0, 0, w, h); // Çizim alanını pencerenin boyutlarına göre ayarlar.
}

// OpenGL sahnesini çizen fonksiyon.
void GPUTest::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Ekranı ve derinlik arabelleğini temizler.

    glMatrixMode(GL_MODELVIEW); // Modelleme ve görüntüleme dönüşümleri için matrisi ayarlar.
    glLoadIdentity(); // Varsayılan (birim) matrise sıfırlar.
    glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f); // Modeli x, y, z eksenlerinde döndürür.

    // Küpün ön yüzünü çizen dörtgenleri başlatır.
    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f); // Kırmızı renkli köşe.
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f); // Yeşil renkli köşe.
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f); // Mavi renkli köşe.
    glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-0.5f,  0.5f, -0.5f); // Sarı renkli köşe.

    glEnd(); // OpenGL çizimi sonlandırır.

    // FPS hesaplaması için çerçeve sayısını artırır.
    frameCount++;

    // Eğer 1 saniye (1000 ms) geçtiyse FPS değerini konsola yazdırır.
    if (fpsTimer.elapsed() >= 1000) {
        emit gpuResult(QString("FPS: %1").arg(frameCount)); // FPS değerini yazdırır.
        frameCount = 0; // Çerçeve sayacını sıfırlar.
        fpsTimer.restart(); // FPS hesaplaması için süreölçeri yeniden başlatır.
    }
}

// Sahneyi güncelleyen fonksiyon.
void GPUTest::updateScene() {
    rotationAngle += 1.0f; // Döndürme açısını artırır.

    // Eğer dönüş açısı 360°'yi geçerse, 0'dan tekrar başlatır.
    if (rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }

    update(); // OpenGL sahnesini yeniden çizmek için sinyal gönderir.
}
