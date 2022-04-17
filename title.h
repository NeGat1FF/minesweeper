#ifndef TITLE_H
#define TITLE_H

#include <QImage>
#include <QRect>
#include <QPainter>


class title
{
public:
    title(int x,int y);
    QRect rect;
    int value;
    void draw(QPainter *);
    bool isRevealed;
    bool isFlag;
    bool isOver;
    static const QImage nums[12];

};

#endif // TITLE_H
