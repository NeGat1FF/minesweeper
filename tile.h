#ifndef TILE_H
#define TILE_H

#include <QImage>
#include <QRect>
#include <QPainter>


class Tile
{
public:
    Tile(int x,int y);
    QRect rect;
    int value;
    void draw(QPainter *);
    bool isRevealed;
    bool isFlag;
    bool isOver;
    static const QImage nums[12];
};

#endif // TILE_H
