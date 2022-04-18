#ifndef GOSCENE_H
#define GOSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <stonegraphics.h>
#include <QWidget>
#include "goengine.h" //for classes Position and Color

class GoScene : public QGraphicsScene {
    Q_OBJECT
public:
    GoScene();

    ~GoScene();


    void setStone(bool color, int x, int y);

    void clearSpot(int x, int y);

    public slots:

    void updateMap(Position pos);


private:
    QGraphicsScene *game;
    QImage *arenaImg;
    QPixmap * arenaPixmap;
    QGraphicsPixmapItem * arena;
    StoneGraphics * spot[9][9];
};

#endif // GOSCENE_H
