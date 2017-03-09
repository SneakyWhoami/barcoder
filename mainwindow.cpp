#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QClipboard>
#include "qqrencode.h"
#include <dmtx.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint/*|Qt::X11BypassWindowManagerHint|Qt::FramelessWindowHint*/);
    /*this->setWindowState(Qt::WindowFullScreen);*/

    // the text that I want encoded
    QString inputText;
    if (QApplication::arguments().length() > 1) {
        inputText = QApplication::arguments().last();
    } else {
        inputText = QGuiApplication::clipboard()->text();
    }

    // DATAMATRIX STUFF START
    DmtxEncode *enc;
    int err = 0;

    enc = dmtxEncodeCreate();
    /* Read input data into buffer */
    err = dmtxEncodeDataMatrix(enc, inputText.length(), (unsigned char*)inputText.toLocal8Bit().data());
    QImage dmatrix(enc->image->pxl, enc->image->width, enc->image->height, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(dmatrix).scaled(240,240));
    dmtxEncodeDestroy(&enc);
    // DATAMATRIX STUFF END


    // QRCODE STUFF START
    QQREncode encoder;
    encoder.encode(inputText);
    QImage qrcode = encoder.toQImage().scaled(240,240);
    ui->label_2->setPixmap(QPixmap::fromImage(qrcode));
    // QRCODE STUFF END

    // COMPENSATE FOR DMATRIX FAILURE USING INVERTED QRCODE START
    if (err == 0) {
        qrcode.invertPixels();
        ui->label->setPixmap(QPixmap::fromImage(qrcode));
    }
    // COMPENSATE FOR DMATRIX FAILURE USING INVERTED QRCODE END


    this->updateGeometry();
}

void MainWindow::mousePressEvent ( QMouseEvent * event )
{
    QApplication::quit();
}

MainWindow::~MainWindow()
{
    delete ui;
}
