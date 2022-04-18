#include "stonegraphics.h"

StoneGraphics::StoneGraphics(bool color){
    stoneImg = new QImage();
    if (color){
        stoneImg->load("C:\\Users\\jakub\\Documents\\GameGO\\img\\white_stone.png");
    } else {
        stoneImg->load("C:\\Users\\jakub\\Documents\\GameGO\\img\\black_stone.png");
    }

    stonePixmap = new QPixmap();
    stonePixmap->convertFromImage(*stoneImg);
    *stonePixmap = stonePixmap->scaled(size,size);
    this->setPixmap(*stonePixmap);
    this->setOffset(-size/2, -size/2);
}

StoneGraphics::~StoneGraphics(){
    //delete stoneImg;
    //delete stonePixmap;
}
