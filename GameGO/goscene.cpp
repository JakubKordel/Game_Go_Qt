#include "goscene.h"

GoScene::GoScene() : QGraphicsScene(0,0,500,500) {
    arenaImg = new QImage();
    arenaImg->load("C:\\Users\\jakub\\Documents\\GameGO\\img\\field.png");
    arenaPixmap = new QPixmap();
    arenaPixmap->convertFromImage(*arenaImg);
    *arenaPixmap = arenaPixmap->scaled(500,500);
    arena = new QGraphicsPixmapItem(*arenaPixmap);

    for (int i = 0; i < 9 ; ++i){
        for (int j = 0; j < 9 ; ++j){
            spot[i][j] = nullptr;
        }
    }

    this->addItem(arena);
}


GoScene::~GoScene(){
    delete arenaImg;
    delete arenaPixmap;
    delete arena;

    for (int i = 0 ; i<8;++i){
        for (int j = 0; j < 8; ++j){
            clearSpot(i, j);
        }
    }

}

void GoScene::setStone(bool color, int x, int y){
    clearSpot(x, y);

    spot[x][y] = new StoneGraphics(color);
    spot[x][y]->setPos((x+1)*50,(y+1)*50);
    this->addItem(spot[x][y]);
}

void GoScene::clearSpot(int x, int y){
    if (spot[x][y]){
        this->removeItem(spot[x][y]);
        delete(spot[x][y]);
        spot[x][y] = nullptr;
    }
}

void GoScene::updateMap(Position pos){
    for (int i = 0; i < 9; ++i ){
        for (int j = 0; j < 9; ++j){
            if (pos.field[i][j] == Color::BlackStone){
                setStone(0, i, j);
            } else if (pos.field[i][j] == Color::WhiteStone){
                setStone(1, i, j);
            } else {
                clearSpot(i, j);
            }
        }
    }
}
