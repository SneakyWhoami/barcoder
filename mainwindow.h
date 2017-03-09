#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

typedef struct {
   char *inputPath;
   char *outputPath;
   char *format;
   int codewords;
   int marginSize;
   int moduleSize;
   int scheme;
   int preview;
   int rotate;
   int sizeIdx;
   int color[3];
   int bgColor[3];
   int mosaic;
   int dpi;
   int verbose;
} UserOptions;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
