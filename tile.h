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
    int value;//0-8 or 9 for mine
    void draw(QPainter *) const;//draws the tile depending on the value and the state of the tile
    bool isRevealed;//isRevealed is true if the tile is revealed
    bool isFlag;//isFlag is true if the right mouse button was pressed
    bool isOver;//isOver is true when mouse is pressed and over the tile
};

#endif // TILE_H
