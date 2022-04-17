#include "minesweeper.h"
#include "./ui_minesweeper.h"

MineSweeper::MineSweeper(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MineSweeper)
    , fl(9,9,10)
{
    ui->setupUi(this);
    rows = 9;
    columns = 9;
    mines = 10;
    timerID = startTimer(1000);
    resizeAll();
}

void MineSweeper::paintEvent(QPaintEvent *e){
    QPainter pp(this);
    fl.draw(&pp);
    win = fl.win;
    lose = fl.lose;
    QString mines = QString::number(fl.getMines());
    QString time = QString::number(fl.getTime());
    while(3 != mines.length())mines.insert(0,'0');
    while(3 != time.length())time.insert(0,'0');
    if(win){
        ui->pushButton->setStyleSheet("QPushButton {"
                                      "image:url(:/img/face_win.png);}");
    }
    else if(lose){
        ui->pushButton->setStyleSheet("QPushButton {"
                                      "image:url(:/img/face_lose.png);}");
    }
    else{
        ui->lcdNumber->display(mines);
        ui->lcdNumber_2->display(time);
    }
}

void MineSweeper::timerEvent(QTimerEvent *t){
    repaint();
}

void MineSweeper::mousePressEvent(QMouseEvent *e){
    ui->pushButton->setStyleSheet("QPushButton {"
                                  "image:url(:/img/face_O.png);}");
    if(!win && !lose){
        fl.press(e->pos(),e->button());
    }
    repaint();
}

void MineSweeper::mouseReleaseEvent(QMouseEvent *e){
    ui->pushButton->setStyleSheet("QPushButton {"
                                  "image:url(:/img/face_happy.png);}");
    if(!win && !lose){
        fl.release(e->pos(),e->button());
    }
    repaint();
}

void MineSweeper::mouseMoveEvent(QMouseEvent *e){
    if(!win && !lose){
        fl.moving(e->pos());
    }
    repaint();
}

void MineSweeper::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Escape)close();
}

void MineSweeper::resizeAll(){
    ui->pushButton->move(10+columns*16-24,20);
    ui->pushButton->setStyleSheet("QPushButton {"
                                  "image:url(:/img/face_happy.png);}");
    QPalette palette = ui->lcdNumber->palette();
    palette.setColor(palette.Light, QColor(255, 0, 0));
    ui->lcdNumber_2->setPalette(palette);
    ui->lcdNumber_2->move(5+columns*32-54,20);
    ui->lcdNumber_2->setPalette(palette);
    resize(32*columns + 20,32*rows + 94+25);
    setFixedSize(32*columns + 20,32*rows + 94+25);
    fl = field(rows,columns,mines);
    win = false;
    lose = false;
}

void MineSweeper::newGame(){
    resizeAll();
}

void MineSweeper::beginner(){
    ui->actionBeginner->setChecked(true);
    ui->actionIntermediate->setChecked(false);
    ui->actionExpert->setChecked(false);
    ui->actionCustom->setChecked(false);
    rows = 9;
    columns = 9;
    mines = 10;
    resizeAll();
}

void MineSweeper::intermediate(){
    ui->actionBeginner->setChecked(false);
    ui->actionIntermediate->setChecked(true);
    ui->actionExpert->setChecked(false);
    ui->actionCustom->setChecked(false);
    rows = 16;
    columns = 16;
    mines = 40;
    resizeAll();
}

void MineSweeper::expert(){
    ui->actionBeginner->setChecked(false);
    ui->actionIntermediate->setChecked(false);
    ui->actionExpert->setChecked(true);
    ui->actionCustom->setChecked(false);
    rows = 16;
    columns = 30;
    mines = 99;
    resizeAll();
}

void MineSweeper::custom(){
    ui->actionBeginner->setChecked(false);
    ui->actionIntermediate->setChecked(false);
    ui->actionExpert->setChecked(false);
    ui->actionCustom->setChecked(true);
    Dialog *dl = new Dialog(nullptr);
    rows = dl->HEIGHT;
    columns = dl->WIDTH;
    mines = dl->MINES;
    delete dl;
    resizeAll();

}


MineSweeper::~MineSweeper()
{
    delete ui;
}

