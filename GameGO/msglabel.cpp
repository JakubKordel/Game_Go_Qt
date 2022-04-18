#include "msglabel.h"

MsgLabel::MsgLabel(QGroupBox*& qgb) : QLabel(qgb){

}

void MsgLabel::setWhiteWon(){
    this->setText(  "// White Won      //");
}

void MsgLabel::setBlackWon(){
    this->setText(  "// Black Won       //");
}

void MsgLabel::setWhiteToMove(){
    this->setText(  "// White to move  //");

}

void MsgLabel::setBlackToMove(){
    this->setText(  "// Black to move   //");

}
