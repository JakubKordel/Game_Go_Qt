#include "goenginecontroller.h"

GoEngineController::GoEngineController(){
  engine = nullptr;
}

void GoEngineController::setEngine(GoEngine * e){
    if (engine != nullptr)
        delete engine;
    engine = e;
    emit gameStarted();
    emit blackToMove();
    emit arenaChanged(engine->getCurr());
}

void GoEngineController::move(int x, int y){
    MoveTryResult res = engine ->place(x, y);
    if (res == MoveTryResult::Success){
        emit arenaChanged(engine->getCurr());
        if (engine->getWinner() == Color::Empty){
            if (engine->getOnMove() == Color::BlackStone){
                emit blackToMove();
            } else {
                emit whiteToMove();
            }
        } else if (engine ->getWinner() == Color::BlackStone){
            emit gameEnded();
            emit blackWon();
        } else {
            emit gameEnded();
            emit whiteWon();
        }
    } else if (res == MoveTryResult::KO){
        //If ever need of adding functionality
    } else if (res == MoveTryResult::Occupied){
        //If ever need of adding functionality
    } else if (res == MoveTryResult::Suicide){
        //If ever need of adding functionality
    } else {
        //If ever need of adding functionality
    }
}

void GoEngineController::pass(){
    engine ->pass();
    if (engine ->getWinner() == Color::Empty){
        if (engine->getOnMove() == Color::BlackStone){
            emit whiteToMove();
        } else {
            emit blackToMove();
        }
    } else if (engine ->getWinner() == Color::BlackStone){
        emit gameEnded();
        emit blackWon();
    } else {
        emit gameEnded();
        emit whiteWon();
    }
}

void GoEngineController::resign(){
    engine ->resign();
    if (engine ->getWinner() == Color::BlackStone){
            emit blackWon();
            emit gameEnded();
    } else {
            emit whiteWon();
            emit gameEnded();
    }
}
