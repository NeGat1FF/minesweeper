#include "field.h"

field::field(int rows, int columns, int mines)
{
    this->rows = rows;
    this->columns = columns;
    displayMines = mines;
    this->minesCnt = displayMines;
    this->mines = mines;
    win = false;
    lose = false;
    firstClick = true;
    pressed = false;
    fl = new title**[rows];
    for(int i = 0;i < rows;i++){
        fl[i] = new title*[columns];
    }
    int x = 10;
    int y = 84+25;
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            fl[i][j] = new title(x,y);
            x+=32;
        }
        x=10;
        y+=32;
    }
}



int field::getMines(){
    return displayMines;
}

void field::generateField(int thisX, int thisY){
    int minesC = mines;
    int x;
    int y;
    while(minesC != 0){
        x = QRandomGenerator::global()->bounded(rows);
        y = QRandomGenerator::global()->bounded(columns);
        if(fl[x][y]->value != 9 && x != thisX && y != thisY){
            fl[x][y]->value = 9;
            minesC--;
        }
    }
    for(int k = 0;k < rows;k++){
        for(int l = 0;l < columns;l++){
            int row = k;
            int col = l;
            if(fl[k][l]->value != 9){
                int cnt = 0;
                for (int i = row - 1; i <= row + 1; i++) {
                    for (int j = col - 1; j <= col + 1; j++) {
                        if(i >= 0 && i < rows && j >= 0 && j < columns) {
                            if(fl[i][j]->value == 9) {
                                cnt++;
                            }
                        }
                    }
                }
                fl[k][l]->value = cnt;
            }
        }
    }
}

void field::showField(){
    if(win){
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < columns;j++){
                if(fl[i][j]->value == 9){
                    fl[i][j]->isFlag = true;
                }
                else{
                    fl[i][j]->isRevealed = true;
                }
            }
        }
    }
    else if(lose){
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < columns;j++){
                if(fl[i][j]->value == 9){
                    fl[i][j]->isRevealed = true;
                }
            }
        }
    }
}

void field::draw(QPainter *p){
    p->setBrush(QBrush(QColor(192,192,192)));
    p->drawRect(0,25,columns*32+20,84);
    p->drawImage(0,25,QImage(":/img/left_top_2.png"));
    p->drawImage(10+32*columns,25,QImage(":/img/right_top_2.png"));
    //    p->drawImage(0,25,QImage(":/img/left_top.png"));
    //    p->drawImage(10+32*columns,25,QImage(":/img/right_top.png"));
    //    p->drawImage(0,74+25,QImage(":/img/left_mid.png"));
    //    p->drawImage(10+32*columns,74+25,QImage(":/img/right_mid.png"));
    p->drawImage(0,84+32*rows+25,QImage(":/img/left_bottom.png"));
    p->drawImage(10+32*columns,84+32*rows+25,QImage(":/img/right_bottom.png"));
    int x = 10;
    int y = 25;
    for(int i = 0;i < columns*3;i++){
        p->drawImage(x,y,QImage(":/img/bottom.png"));
        x+=32;
        if(i == columns-1){
            x=10;
            y+=74;
        }
        if(i == columns*2-1){
            x=10;
            y+=rows*32+10;
        }
    }
    x=0;
    y=84+25;
    for(int i = 0;i < rows*2;i++){
        p->drawImage(x,y,QImage(":/img/left.png"));
        y+=32;
        if(i == rows-1){
            y=84+25;
            x=10+columns*32;
        }
    }
    p->drawImage(0,10+25,QImage(":/img/left.png"));
    p->drawImage(0,42+25,QImage(":/img/left.png"));
    p->drawImage(10+columns*32,10+25,QImage(":/img/left.png"));
    p->drawImage(10+columns*32,42+25,QImage(":/img/left.png"));
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            fl[i][j]->draw(p);
        }
    }
}

void field::moving(QPoint point){
    if(pressed){
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < columns;j++){
                fl[i][j]->isOver = fl[i][j]->rect.contains(point);
            }
        }
    }
}

int field::getTime(){
    if(firstClick){
        return 0;
    }
    else{
        return timer.elapsed()/1000;
    }
}

void field::release(QPoint point,Qt::MouseButton bt){
    if(bt == Qt::LeftButton){
        pressed = false;
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < columns;j++){
                if(fl[i][j]->rect.contains(point)){
                    if(firstClick){
                        generateField(i,j);
                        timer.restart();
                        firstClick = false;
                    }
                    fl[i][j]->isOver = false;
                    reveal(i,j);
                }
            }
        }
    }
}

void field::press(QPoint point,Qt::MouseButton bt){
    if(!firstClick && bt == Qt::RightButton){
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < columns;j++){
                if(fl[i][j]->rect.contains(point)){

                    if(fl[i][j]->isFlag){
                        if(fl[i][j]->value == 9)minesCnt++;
                        fl[i][j]->isFlag = false;
                    }
                    else{
                        if(fl[i][j]->value == 9)minesCnt--;
                        fl[i][j]->isFlag = true;
                    }

                }
            }
        }
    }
    else if(bt == Qt::LeftButton){
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < columns;j++){
                if(fl[i][j]->rect.contains(point)){
                    pressed = true;
                    fl[i][j]->isOver = true;
                }
            }
        }
    }
}

void field::reveal(int x, int y){
    fl[x][y]->isRevealed = true;
    if(fl[x][y]->value == 0){
        int row = x;
        int col = y;
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
                if(i >= 0 && i < rows && j >= 0 && j < columns) {
                    if(fl[i][j]->value != 9 && !fl[i][j]->isFlag && rows != x && !fl[i][j]->isRevealed) {
                        fl[i][j]->isRevealed = true;
                        if(fl[i][j]->value == 0){
                            reveal(i,j);
                        }
                    }
                }
            }
        }
    }
    checkWin();
}


void field::checkWin(){
    int count = 0;
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            if(fl[i][j]->isRevealed){
                if(fl[i][j]->value == 9){
                    lose = true;
                }
                else{
                    count++;
                }
            }
        }
    }
    if(count == rows * columns - mines || minesCnt == 0){
        win = true;
    }
    showField();
}
