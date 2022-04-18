#ifndef STONEGRAPHICS_H
#define STONEGRAPHICS_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class StoneGraphics : public QGraphicsPixmapItem {
public:
    StoneGraphics(bool color);

    ~StoneGraphics();

private:
    QImage * stoneImg;
    QPixmap * stonePixmap;
    const int size = 40;
};

#endif // STONEGRAPHICS_H
