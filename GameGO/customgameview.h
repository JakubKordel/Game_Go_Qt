#ifndef CUSTOMGAMEVIEW_H
#define CUSTOMGAMEVIEW_H

#include <QGraphicsView>
#include "goscene.h"

class CustomGameView : public QGraphicsView {

    Q_OBJECT
public:
    CustomGameView(QWidget * & qwidget);

    void mousePressEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void setScene(GoScene * s);

signals:
    void spotClicked(int x, int y);

private:

     GoScene * scene;

};

#endif // CUSTOMGAMEVIEW_H
