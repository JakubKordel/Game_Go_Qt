#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QPushButton>
#include <QGroupBox>

class GameButton : public QPushButton {
    Q_OBJECT
public:
    GameButton(QGroupBox*&);

public slots:
       void enableButton();
       void disableButton();
};

#endif // GAMEBUTTON_H
