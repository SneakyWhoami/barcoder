#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap p;
    // if more than one argument, assume last argument is a string to encode
    //!! NOTE this may not work in Windows depending how app is started!
    if (QApplication::arguments().length() > 1) {
       // qDebug() << QApplication::arguments().last();
        QProcess dmtx;
        dmtx.start("dmtxwrite", QStringList() << "-s" << "40x40");
        dmtx.waitForStarted();

        dmtx.write(QApplication::arguments().last().toUtf8());
        dmtx.closeWriteChannel();
        dmtx.waitForFinished();

        QByteArray result = dmtx.readAll();
        p.loadFromData(result,"PNG");
        ui->label->setPixmap(p);

        ////////////////////////////////////////////////////
        dmtx.start("qrencode", QStringList() << "-o" << "-");
        dmtx.waitForStarted();

        dmtx.write(QApplication::arguments().last().toUtf8());
        dmtx.closeWriteChannel();
        dmtx.waitForFinished();

        result = dmtx.readAll();
        p.loadFromData(result,"PNG");
        ui->label_2->setPixmap(p);
//        ui->label->setPixmap();
    } else {
        QClipboard *clipboard = QGuiApplication::clipboard();
      //  qDebug() << clipboard->text();
        QProcess dmtx;
        dmtx.start("dmtxwrite", QStringList() << "-s" << "40x40");
        dmtx.waitForStarted();

        dmtx.write(clipboard->text().toUtf8());
        dmtx.closeWriteChannel();
        dmtx.waitForFinished();

        QByteArray result = dmtx.readAll();
        p.loadFromData(result,"PNG");
        ui->label->setPixmap(p);

        ////////////////////////////////////////////////////
        dmtx.start("qrencode", QStringList() << "-o" << "-");
        dmtx.waitForStarted();

        dmtx.write(clipboard->text().toUtf8());
        dmtx.closeWriteChannel();
        dmtx.waitForFinished();

        result = dmtx.readAll();
        p.loadFromData(result,"PNG");
        ui->label_2->setPixmap(p);
    }
    this->updateGeometry();
    //connect(ui->centralWidget, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void MainWindow::mousePressEvent (QMouseEvent * event)
{
    QApplication::quit();
}

MainWindow::~MainWindow()
{
    delete ui;
}
