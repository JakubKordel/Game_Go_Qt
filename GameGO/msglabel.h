#ifndef MSGLABEL_H
#define MSGLABEL_H

#include <QLabel>
#include <QGroupBox>

class MsgLabel : public QLabel{

Q_OBJECT

public:
    MsgLabel(QGroupBox*&);

public slots:
    void setWhiteWon();
    void setBlackWon();
    void setWhiteToMove();
    void setBlackToMove();
};

#endif // MSGLABEL_H
