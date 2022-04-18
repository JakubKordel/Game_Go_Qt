#ifndef GOENGINECONTROLLER_H
#define GOENGINECONTROLLER_H

#include <QObject>
#include "goengine.h"

class GoEngineController : public QObject {
    Q_OBJECT
public:
    GoEngineController();

    void setEngine(GoEngine * engine);

public slots:
    void move(int x, int y);
    void pass();
    void resign();

signals:
    void gameStarted();
    void whiteToMove();
    void blackToMove();
    void blackWon();
    void whiteWon();
    void arenaChanged(Position pos);
    void gameEnded();

private:
    GoEngine * engine;

};

#endif // GOENGINECONTROLLER_H
