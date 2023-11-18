#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include "tile.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MineSweeper; }
QT_END_NAMESPACE

class MineSweeper : public QMainWindow
{
    Q_OBJECT

public:
    explicit MineSweeper(QWidget *parent = nullptr);
    void checkWin();//checks if all the tiles are revealed except the mines
    void showField();//shows the field
    void reveal(int,int);//reveals the tiles around the tile with the given coordinates
    void create(int,int,int);//creates the field with the given parameters
    void resizeAll(int,int,int);//resizes all the tiles
    void generateField(int, int);//generates the field with the given parameters
    void paintEvent(QPaintEvent *) override;//paints the field
    void timerEvent(QTimerEvent *) override;//updates the timer
    void keyPressEvent(QKeyEvent *) override;//handles the key press
    void mouseMoveEvent(QMouseEvent *) override;//handles the mouse move
    void mousePressEvent(QMouseEvent *) override;//handles the mouse press
    void mouseReleaseEvent(QMouseEvent *) override;//handles the mouse release
    ~MineSweeper() override;

public slots:
    void newGame();//resets the game
    [[maybe_unused]]void beginner();//creates a beginner field
    [[maybe_unused]]void intermediate();//creates an intermediate field
    [[maybe_unused]]void expert();//creates an expert field
    [[maybe_unused]]void custom();//creates a custom field

private:
    bool win;//is true if the player has won
    bool lose;//is true if the player has lost
    bool pressed;//is true if the mouse button is pressed
    bool firstClick;//is false if the first click has been made
    int rows;//number of rows
    int columns;//number of columns
    int mines;//number of mines
    int minesCnt;//number of mines left
    int displayMines;//number of mines to display
    [[maybe_unused]]int timerID;
    [[maybe_unused]]int seconds;
    QLine dark[19];//dark lines
    QLine light[5];//light lines
    QLine white[12];//white lines
    QRect Button;//button
    QElapsedTimer timer;//timer
    QVector<QVector<Tile>> fl;//field
    Ui::MineSweeper *ui;
};
#endif // MINESWEEPER_H
