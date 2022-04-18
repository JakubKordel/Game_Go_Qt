#include "customgameview.h"
#include <QMouseEvent>
#include <QPoint>
#include <QtMath>

CustomGameView::CustomGameView(QWidget * & qwidget) : QGraphicsView(qwidget){

}

void CustomGameView::setScene(GoScene * s){
    this->QGraphicsView::setScene(s);
    scene = s;
}

void CustomGameView::mousePressEvent(QMouseEvent *event){

    QPointF mapped = mapToScene(event->pos());

    float precission = 0.5;

    float helpX = (mapped.rx()-50+precission/2*50)/50 ;
    int x = qFloor(helpX);

    float helpY = (mapped.ry()-50+precission/2*50)/50 ;
    int y = qFloor(helpY);

    if (x >= 0 && y >= 0 && x <= 8 && y <= 8 && helpX - x < precission && helpY - y < precission ){
        emit spotClicked(x, y);
    }
}

void CustomGameView::resizeEvent(QResizeEvent *event){
    this->fitInView(0,0, 500, 500, Qt::KeepAspectRatio);
}
