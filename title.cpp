#include "title.h"

title::title(int x,int y)
{
    rect = QRect(x,y,32,32);
    int value = 0;
    isRevealed = false;
    isFlag = false;
    isOver = false;
}

void title::draw(QPainter *p){
    if(isRevealed)p->drawImage(rect,nums[value]);
    else if(isFlag)p->drawImage(rect,nums[11]);
    else if(isOver)p->drawImage(rect,nums[0]);
    else{p->drawImage(rect,nums[10]);}
}

const QImage title::nums[12] ={QImage(":/img/tile_revealed.png"),
                               QImage(":/img/number_1.png"),
                               QImage(":/img/number_2.png"),
                               QImage(":/img/number_3.png"),
                               QImage(":/img/number_4.png"),
                               QImage(":/img/number_5.png"),
                               QImage(":/img/number_6.png"),
                               QImage(":/img/number_7.png"),
                               QImage(":/img/number_8.png"),
                               QImage(":/img/mine.png"),
                               QImage(":/img/tile_hidden.png"),
                               QImage(":/img/flag.png")};
