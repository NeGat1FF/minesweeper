#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include "tile.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MineSweeper; }
QT_END_NAMESPACE

class MineSweeper : public QMainWindow
{
    Q_OBJECT

public:
    MineSweeper(QWidget *parent = nullptr);
    void checkWin();
    void showField();
    void reveal(int,int);
    void create(int,int,int);
    void resizeAll(int,int,int);
    void generateField(int, int);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    ~MineSweeper();

public slots:
    void newGame();
    void beginner();
    void intermediate();
    void expert();
    void custom();

private:
    const static QImage faces[4];

    bool win;
    bool lose;
    bool pressed;
    bool firstClick;
    int rows;
    int columns;
    int mines;
    int minesCnt;
    int displayMines;
    int timerID;
    int seconds;
    QLine dark[19];
    QLine light[5];
    QLine white[12];
    QRect Button;
    QElapsedTimer timer;
    QVector<QVector<Tile>> fl;
    Ui::MineSweeper *ui;
};
#endif // MINESWEEPER_H
