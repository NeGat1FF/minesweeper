#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include "field.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MineSweeper; }
QT_END_NAMESPACE

class MineSweeper : public QMainWindow
{
    Q_OBJECT

public:
    MineSweeper(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
    void resizeAll();
    ~MineSweeper();

public slots:
    void newGame();
    void beginner();
    void intermediate();
    void expert();
    void custom();

private:
    bool win;
    bool lose;
    field fl;
    int rows;
    int columns;
    int mines;
    int timerID;
    Ui::MineSweeper *ui;
};
#endif // MINESWEEPER_H
