#include "goengine.h"

#include <iostream>

int Position::stonesNum(Color col){
    int counter = 0;
    for (int i = 0 ; i < 9 ; ++i){
        for (int j = 0; j < 9 ; ++j){
            if (field[i][j] == col){
                ++counter;
            }
        }
    }
    return counter;
}

int Position::calcEmptyAreas(Color col){
    int counter = 0;
    std::vector<Group> emptyGroups = createGroups(Color::Empty);
    for (auto it = emptyGroups.begin() ; it != emptyGroups.end(); ++it){
        if (it->checkIfBelongs(col, *this)){
            counter += it->members.size();
        }
    }
    return counter;
}

std::vector<Group> Position::createGroups(Color col){
    std::vector<Group> groups;

    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9  ; ++j){
            bool wasUsed = false;
            if (field[i][j] == col ){
                for (auto it = groups.begin() ; it != groups.end(); ++it){
                    if (it->isMember(i, j)){
                        wasUsed = true;
                        break;
                    }
                }
                if (!wasUsed){
                    Group group;
                    group.col = col;
                    group.expand(i, j, *this);
                    groups.push_back(group);
                }
            }
        }
    }

    return groups;
}



bool Position::hasBreath(int x, int y) const {

    if (x > 0 && field[x-1][y] == Color::Empty){
        return true;
    }

    if (x < 8 && field[x+1][y] == Color::Empty){
        return true;
    }
    if (y > 0 && field[x][y-1] == Color::Empty){
        return true;
    }

    if (y < 8 && field[x][y+1] == Color::Empty){
        return true;
    }
    return false;
}


bool Group::checkIfBelongs(Color col, Position pos){
    Color opposite;
    if (col == Color::WhiteStone){
        opposite = Color::BlackStone;
    } else if (col == Color::BlackStone){
        opposite = Color::WhiteStone;
    } else return false;

    for (auto it = members.begin() ; it != members.end(); ++it){
        int x = (*it)[0];
        int y = (*it)[1];
        if (x > 0 && pos.field[x-1][y] == opposite){
            return false;
        }

        if (x < 8 && pos.field[x+1][y] == opposite){
            return false;
        }
        if (y > 0 && pos.field[x][y-1] == opposite){
            return false;
        }

        if (y < 8 && pos.field[x][y+1] == opposite){
            return false;
        }
    }
    return true;
}

bool Group::hasBreath(const Position &pos) const {
    for (auto it = members.begin() ; it != members.end(); ++it){
        if (pos.hasBreath((*it)[0], (*it)[1])){
            return true;
        }
    }
    return false;

}

bool Group::isMember(std::vector<int> xy ){
    for (auto it = members.begin() ; it != members.end(); ++it){
        if ((*it)[0] == xy[0] && (*it)[1] == xy[1]){
            return true;
        }
    }
    return false;
}

bool Group::isMember(int x, int y ){
    std::vector<int> xy;
    xy.push_back(x);
    xy.push_back(y);
    return isMember(xy);
}

void Group::addMember(std::vector<int> xy ){
    members.push_back(xy);
}


void Group::addMember(int x, int y){
    std::vector<int> v;
    v.push_back(x);
    v.push_back(y);
    members.push_back(v);
}

void Group::expand(const int x, const int y, const Position pos){
    if (pos.field[x][y] == col && !isMember(x,y)){
        addMember(x,y);
        if (x > 0 ){
            expand(x-1, y, pos);
        }

        if (x < 8 ){
            expand(x+1, y, pos);
        }
        if (y > 0 ){
            expand(x, y-1, pos);
        }

        if (y < 8 ){
            expand(x, y+1, pos);
        }
    }
}

Position::Position(){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            field[i][j] = Color::Empty;
        }
    }
}

Position::Position(const Position &pos){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            field[i][j] = pos.field[i][j];
        }
    }
}

bool Position::operator==(const Position &pos){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            if (field[i][j] != pos.field[i][j]){
                return false;
            }
        }
    }
    return true;
}

void Position::operator=(const Position &pos){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            field[i][j] = pos.field[i][j];
        }
    }

}

void Position::removeGroup(Group group){
    for (auto it = group.members.begin() ; it != group.members.end(); ++it){
        field[(*it)[0]][(*it)[1]] = Color::Empty;
    }
}

GoEngine::GoEngine(){
    onMove = Color::BlackStone;
    curr = Position();
    winner = Color::Empty;
}

MoveTryResult GoEngine::place(int x, int y){

    if (winner != Color::Empty){
        return MoveTryResult::GameEnded;
    }

    Color stone = onMove;

    if (curr.field[x][y] != Color::Empty){
        return MoveTryResult::Occupied;
    }

    Position posCopy(curr);
    posCopy.field[x][y] = stone;

    bool flag = false;
    int removedStonesCounter = 0;

    if (onMove == Color::WhiteStone){
        std::vector<Group> blackGroups = posCopy.createGroups(Color::BlackStone);



        for (auto it = blackGroups.begin() ; it != blackGroups.end(); ++it){
            if (!it->hasBreath(posCopy)){
                removedStonesCounter += it->members.size();
                posCopy.removeGroup(*it);
                flag = true;
            }
        }

        if (flag){
            if (didHappen(posCopy)){
                return MoveTryResult::KO;
            } else {
                history.push_back(curr);
                curr = posCopy;
                swapOnMove();
                passes = 0;
                whitePoints += removedStonesCounter;
                return MoveTryResult::Success;
            }

        } else {
            std::vector<Group> whiteGroups = posCopy.createGroups(Color::WhiteStone);


            for (auto it = whiteGroups.begin() ; it != whiteGroups.end(); ++it){
                if (!it->hasBreath(posCopy)){
                    flag = true;
                }
            }

            if (flag){
                return MoveTryResult::Suicide;
            } else {
                if (didHappen(posCopy)){
                    return MoveTryResult::KO;
                } else {
                    history.push_back(curr);
                    curr = posCopy;
                    swapOnMove();
                    passes = 0;
                    return MoveTryResult::Success;
                }

            }
        }


    } else {

        std::vector<Group> whiteGroups = posCopy.createGroups(Color::WhiteStone);


        for (auto it = whiteGroups.begin() ; it != whiteGroups.end(); ++it){
            if (!it->hasBreath(posCopy)){
                removedStonesCounter += it->members.size();
                posCopy.removeGroup(*it);
                flag = true;
            }
        }


        if (flag){
            if (didHappen(posCopy)){
                return MoveTryResult::KO;
            } else {
                history.push_back(curr);
                curr = posCopy;
                swapOnMove();
                passes = 0;
                blackPoints += removedStonesCounter;
                return MoveTryResult::Success;
            }

        } else {

            std::vector<Group> blackGroups = posCopy.createGroups(Color::BlackStone);

            for (auto it = blackGroups.begin() ; it != blackGroups.end(); ++it){
                if (!it->hasBreath(posCopy)){
                    flag = true;
                }
            }

            if (flag){
                return MoveTryResult::Suicide;
            } else {
                if (didHappen(posCopy)){
                    return MoveTryResult::KO;
                } else {
                    history.push_back(curr);

                    curr = posCopy;
                    swapOnMove();
                    passes = 0;
                    return MoveTryResult::Success;
                }
            }
        }
    }
}

bool GoEngine::didHappen(Position pos){
    for (auto it = history.begin() ; it != history.end(); ++it){
        if(*it == pos ){
            return true;
        }
    }
    return false;
}

Color GoEngine::getOnMove(){
    return onMove;
}

void GoEngine::swapOnMove(){
    if (onMove == Color::WhiteStone){
        onMove = Color::BlackStone;
    } else {
        onMove = Color::WhiteStone;
    }
}

Color GoEngine::getSpot(int x, int y){
    return curr.field[x][y];
}

void GoEngine::calculateWinner(){
    int whiteTotalPoints = whitePoints + curr.stonesNum(Color::WhiteStone) + curr.calcEmptyAreas(Color::WhiteStone);
    int blackTotalPoints = blackPoints + curr.stonesNum(Color::BlackStone) + curr.calcEmptyAreas(Color::BlackStone);

    if (whiteTotalPoints >= blackTotalPoints){
        winner = Color::WhiteStone;
    } else {
        winner = Color::BlackStone;
    }
}

void GoEngine::pass(){
    if (passes == 1){
        calculateWinner();
    } else {
        ++passes;
        swapOnMove();
    }
}

void GoEngine::resign(){
    if (onMove == Color::BlackStone){
        winner = Color::WhiteStone;
    } else {
        winner = Color::BlackStone;
    }
}

Position GoEngine::getCurr(){
    return curr;
}

Color GoEngine::getWinner(){
    return winner;
}


