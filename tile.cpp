#include "tile.h"

Tile::Tile(int x,int y)
{
    rect = QRect(x,y,32,32);
    value = 0;
    isRevealed = false;
    isFlag = false;
    isOver = false;
}

void Tile::draw(QPainter *p) const{
    if(isRevealed){
        switch (value) {
            case 0:
                p->drawImage(rect,QImage(":/img/tile_revealed.png"));
                break;
            case 1:
                p->drawImage(rect,QImage(":/img/number_1.png"));
                break;
            case 2:
                p->drawImage(rect,QImage(":/img/number_2.png"));
                break;
            case 3:
                p->drawImage(rect,QImage(":/img/number_3.png"));
                break;
            case 4:
                p->drawImage(rect,QImage(":/img/number_4.png"));
                break;
            case 5:
                p->drawImage(rect,QImage(":/img/number_5.png"));
                break;
            case 6:
                p->drawImage(rect,QImage(":/img/number_6.png"));
                break;
            case 7:
                p->drawImage(rect,QImage(":/img/number_7.png"));
                break;
            case 8:
                p->drawImage(rect,QImage(":/img/number_8.png"));
                break;
            case 9:
                p->drawImage(rect,QImage(":/img/mine.png"));
                break;
        }
    }
    else if(isFlag)p->drawImage(rect,QImage(":/img/flag.png"));
    else if(isOver)p->drawImage(rect,QImage(":/img/tile_revealed.png"));
    else{p->drawImage(rect,QImage(":/img/tile_hidden.png"));}
}



