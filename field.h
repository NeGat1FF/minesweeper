#ifndef FIELD_H
#define FIELD_H

#include <QList>
#include <QPainter>
#include <iostream>
#include <QRandomGenerator>
#include <QElapsedTimer>
#include "title.h"

class field
{
public:
    field(int rows = 9,int columns = 9,int mines = 10);
    void showField();
    void press(QPoint,Qt::MouseButton);
    void release(QPoint,Qt::MouseButton);
    void moving(QPoint);
    void draw(QPainter *);
    void generateField(int, int);
    void reveal(int x, int y);
    int getTime();
    int getMines();
    void checkWin();
    bool win;
    bool lose;
private:
    bool firstClick;
    bool pressed;
    QLine dark[19];
    QLine light[5];
    QLine white[12];
    QElapsedTimer timer;
    title*** fl;
    int rows;
    int columns;
    int displayMines;
    int minesCnt;
    int mines;
};

#endif // FIELD_H
