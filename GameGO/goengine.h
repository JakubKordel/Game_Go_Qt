#ifndef GOENGINE_H
#define GOENGINE_H

#include <vector>

enum class Color {Empty, WhiteStone, BlackStone};

enum class MoveTryResult {Success, KO, Occupied, Suicide, GameEnded };

class Position;

class Group {
public:
    Color col;
    std::vector<std::vector<int>> members;

    bool hasBreath(const Position &pos) const ; //intended for only black/white group
    bool isMember(std::vector<int> xy );
    bool isMember(int x, int y );
    void addMember(std::vector<int> xy );
    void addMember(int x, int y);

    void expand(const int x, const int y, const Position pos);

    bool checkIfBelongs(Color col, Position pos); //intended only for empty spots group

};


class Position {
public:

     Position();
     Position(const Position &pos);

     bool operator==(const Position &pos);

     void operator=(const Position &pos);

     Color field[9][9];

     bool hasBreath(int x, int y) const ;

     void removeGroup(Group group);

     std::vector<Group> createGroups(Color col);

     int calcEmptyAreas(Color col);

     int stonesNum(Color col);

};



class GoEngine{
public:
    GoEngine();



    MoveTryResult place(int x, int y);

    Color getOnMove();

    Color getSpot(int x, int y);

    void pass();

    void resign();

    Color getWinner();

    Position getCurr();

private:

    void calculateWinner();

    Color onMove;

    Position curr;

    std::vector<Position> history;

    void swapOnMove();

    bool didHappen(Position pos);

    int blackPoints = 0;

    int whitePoints = 0;

    Color winner;

    int passes = 0;

};

#endif // GOENGINE_H
