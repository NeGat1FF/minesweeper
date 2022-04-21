#include "minesweeper.h"
#include "./ui_minesweeper.h"

const QImage MineSweeper::faces[4] = {QImage(":/img/face_happy.png")
                                     ,QImage(":/img/face_win.png")
                                     ,QImage(":/img/face_lose.png")
                                     ,QImage(":/img/face_O.png")};

MineSweeper::MineSweeper(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MineSweeper)
{
    ui->setupUi(this);
    rows = 9;
    columns = 9;
    mines = 10;
    int x = 10;
    int y = 84+25;
    fl.resize(rows);
    for(int i = 0;i < rows;i++){
        fl[i].append(QVector<Tile> ());
        for(int j = 0;j < columns;j++){
            fl[i].append(Tile(x,y));
            x=+32;
        }
        x=10;
        y+=32;
    }
    timerID = startTimer(1000);
    Button = QRect(0,0,48,48);
    resizeAll(9,9,10);
}

void MineSweeper::create(int rows, int columns, int mines){
    for(int i = 0;i < this->rows;i++){
        fl[i].clear();
    }
    fl.clear();
    int x = 10;
    int y = 84+25;
    fl.resize(rows);
    for(int i = 0;i < rows;i++){
        fl[i].append(QVector<Tile> ());
        for(int j = 0;j < columns;j++){
            fl[i].append(Tile(x,y));
            x+=32;
        }
        x=10;
        y+=32;
    }
    this->rows = rows;
    this->columns = columns;
    this->displayMines = mines;
    this->minesCnt = displayMines;
    this->mines = mines;
    win = false;
    lose = false;
    firstClick = true;
    pressed = false;
    timer.invalidate();

    dark[0] = QLine(10,31,columns*32+11,31);
    dark[1] = QLine(10,32,columns*32+10,32);
    dark[2] = QLine(8,31,8,rows*32+110);
    dark[3] = QLine(9,31,9,rows*32+109);
    dark[4] = QLine(10,31,10,rows*32+108);
    dark[5] = QLine(19+columns*32,25,19+columns*32,rows*32+118);
    dark[6] = QLine(0,rows*32+118,columns*32+20,rows*32+118);
    dark[7] = QLine(19+columns*32,25,19+columns*32,rows*32+118);
    dark[8] = QLine(10,107,columns*32+10,107);
    dark[9] = QLine(10,106,columns*32+11,106);
    dark[10] = QLine(10,105,columns*32+12,105);
    dark[11] = QLine(15,43,15,88);
    dark[12] = QLine(16,43,16,87);
    dark[13] = QLine(15,41,73,41);
    dark[14] = QLine(15,42,72,42);
    dark[15] = QLine(columns*32-50,41,6+columns*32,41);
    dark[16] = QLine(columns*32-50,42,5+columns*32,42);
    dark[17] = QLine(columns*32-50,43,columns*32-50,88);
    dark[18] = QLine(columns*32-49,43,columns*32-49,87);

    light[0] = QLine(5,27,5,rows*32+114);
    light[1] = QLine(10,rows*32+114,columns*32+10,rows*32+114);
    light[2] = QLine(columns*32+15,27,columns*32+15,rows*32+114);
    light[3] = QLine(6,27,columns*32+15,27);
    light[4] = QLine(5,102,columns*32+10,102);

    white[0] = QLine(9,99,columns*32+11,99);
    white[1] = QLine(10,98,columns*32+11,98);
    white[2] = QLine(17,87,72,87);
    white[3] = QLine(16,88,72,88);
    white[4] = QLine(72,43,72,87);
    white[5] = QLine(73,42,73,88);
    white[6] = QLine(6+columns*32,43,6+columns*32,88);
    white[7] = QLine(5+columns*32,44,5+columns*32,88);
    white[8] = QLine(columns*32-49,87,6+columns*32,87);
    white[9] = QLine(columns*32-50,88,6+columns*32,88);
    white[10] = QLine(columns*32+10,99,columns*32+10,32);
    white[11] = QLine(columns*32+11,99,columns*32+11,31);
}

void MineSweeper::paintEvent(QPaintEvent *e){
    QPainter pp(this);
    pp.setBrush(QColor(192,192,192));
    pp.drawRect(10,25,8+32*columns,75);
    pp.setPen(QPen(QColor(123,123,123),1)); // dark
    pp.drawLines(dark,19);

    pp.setPen(QPen(QColor(192,192,192),6)); //light
    pp.drawLines(light,5);

    pp.setPen(QPen(QColor(255,255,255),1)); //white
    pp.drawLines(white,12);

    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            fl[i][j].draw(&pp);
        }
    }
    QString mines = QString::number(displayMines);
    QString time = QString::number(timer.isValid() ? timer.elapsed()/1000 : 0);
    while(3 != mines.length())mines.insert(0,'0');
    while(3 != time.length())time.insert(0,'0');
    if(win){
        pp.drawImage(Button,faces[1]);
    }
    else if(lose){
        pp.drawImage(Button,faces[2]);
    }
    else{
        if(pressed){
            pp.drawImage(Button,faces[3]);
        }
        else{
            pp.drawImage(Button,faces[0]);
        }
        ui->lcdNumber->display(mines);
        ui->lcdNumber_2->display(time);
    }
}

void MineSweeper::timerEvent(QTimerEvent *t){
    repaint();
}

void MineSweeper::mousePressEvent(QMouseEvent *e){
    if(!firstClick && e->button() == Qt::RightButton && !win && !lose){
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < columns;j++){
                if(fl[i][j].rect.contains(e->pos()) && !fl[i][j].isRevealed){
                    if(fl[i][j].isFlag){
                        if(fl[i][j].value == 9)minesCnt++;
                        fl[i][j].isFlag = false;
                        displayMines++;
                    }
                    else{
                        if(fl[i][j].value == 9)minesCnt--;
                        fl[i][j].isFlag = true;
                        displayMines--;
                    }

                }
            }
        }
    }
    else if(e->button() == Qt::LeftButton && !win && !lose){
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < columns;j++){
                if(fl[i][j].rect.contains(e->pos())){
                    pressed = true;
                    fl[i][j].isOver = true;
                }
            }
        }
    }
    repaint();
}

void MineSweeper::generateField(int thisX,int thisY){
    int minesC = mines;
    int x;
    int y;
    while(minesC != 0){
        x = QRandomGenerator::global()->bounded(rows);
        y = QRandomGenerator::global()->bounded(columns);
        if(fl[x][y].value != 9 && x != thisX && y != thisY){
            fl[x][y].value = 9;
            minesC--;
        }
    }
    for(int k = 0;k < rows;k++){
        for(int l = 0;l < columns;l++){
            int row = k;
            int col = l;
            if(fl[k][l].value != 9){
                int cnt = 0;
                for (int i = row - 1; i <= row + 1; i++) {
                    for (int j = col - 1; j <= col + 1; j++) {
                        if(i >= 0 && i < rows && j >= 0 && j < columns) {
                            if(fl[i][j].value == 9) {
                                cnt++;
                            }
                        }
                    }
                }
                fl[k][l].value = cnt;
            }
        }
    }
}

void MineSweeper::mouseReleaseEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton && !win && !lose){
        pressed = false;
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < columns;j++){
                if(fl[i][j].rect.contains(e->pos())){
                    if(firstClick){
                        generateField(i,j);
                        firstClick = false;
                        timer.restart();
                    }
                    fl[i][j].isOver = false;
                    reveal(i,j);
                }
            }
        }
    }
    if(Button.contains(e->pos()))newGame();
    repaint();
}

void MineSweeper::reveal(int x, int y){
    if(!fl[x][y].isFlag){
        fl[x][y].isRevealed = true;
        if(fl[x][y].value == 0){
            int row = x;
            int col = y;
            for (int i = row - 1; i <= row + 1; i++) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if(i >= 0 && i < rows && j >= 0 && j < columns) {
                        if(fl[i][j].value != 9 && !fl[i][j].isFlag && rows != x && !fl[i][j].isRevealed) {
                            fl[i][j].isRevealed = true;
                            if(fl[i][j].value == 0){
                                reveal(i,j);
                            }
                        }
                    }
                }
            }
        }
        checkWin();
    }
}

void MineSweeper::mouseMoveEvent(QMouseEvent *e){
    if(pressed){
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < columns;j++){
                fl[i][j].isOver = fl[i][j].rect.contains(e->pos());
            }
        }
    }
    repaint();
}

void MineSweeper::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Escape)close();
}

void MineSweeper::resizeAll(int r,int c, int m){
    create(r,c,m);
    Button.moveTo(10+columns*16-24,40);
    ui->lcdNumber_2->move(5+columns*32-54,20);
    resize(32*columns + 20,32*rows + 94+25);
    setFixedSize(32*columns + 20,32*rows + 94+25);
    win = false;
    lose = false;
    repaint();
}

void MineSweeper::showField(){
    if(win){
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < columns;j++){
                if(fl[i][j].value == 9){
                    fl[i][j].isFlag = true;
                }
                else{
                    fl[i][j].isRevealed = true;
                }
            }
        }
    }
    else if(lose){
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < columns;j++){
                if(fl[i][j].value == 9){
                    fl[i][j].isRevealed = true;
                }
            }
        }
    }
}

void MineSweeper::checkWin(){
    int count = 0;
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            if(fl[i][j].isRevealed){
                if(fl[i][j].value == 9){
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

void MineSweeper::newGame(){
    if(!firstClick)resizeAll(rows,columns,mines);
}

void MineSweeper::beginner(){
    ui->actionBeginner->setChecked(true);
    ui->actionIntermediate->setChecked(false);
    ui->actionExpert->setChecked(false);
    ui->actionCustom->setChecked(false);
    resizeAll(9,9,10);
}

void MineSweeper::intermediate(){
    ui->actionBeginner->setChecked(false);
    ui->actionIntermediate->setChecked(true);
    ui->actionExpert->setChecked(false);
    ui->actionCustom->setChecked(false);
    resizeAll(16,16,40);
}

void MineSweeper::expert(){
    ui->actionBeginner->setChecked(false);
    ui->actionIntermediate->setChecked(false);
    ui->actionExpert->setChecked(true);
    ui->actionCustom->setChecked(false);
    resizeAll(16,30,99);
}

void MineSweeper::custom(){
    ui->actionBeginner->setChecked(false);
    ui->actionIntermediate->setChecked(false);
    ui->actionExpert->setChecked(false);
    ui->actionCustom->setChecked(true);
    Dialog *dl = new Dialog(nullptr);
    resizeAll(dl->HEIGHT,dl->WIDTH,dl->MINES);
    delete dl;
}


MineSweeper::~MineSweeper()
{
    delete ui;
}

