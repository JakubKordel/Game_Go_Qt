#include "gamebutton.h"


GameButton::GameButton(QGroupBox*& qgp) : QPushButton(qgp)  {

}

void GameButton::enableButton(){
    setEnabled(true);

}

void GameButton::disableButton(){
    setEnabled(false);
}
