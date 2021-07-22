#ifndef CHESSLORD_H
#define CHESSLORD_H


#include <vector>
#include <string>

// This will hold all of the info about the move                                                                                                     
struct moveInfo {
  int pos0, pos1, pos2, pos3;
  std::string thePiece;
} moveInfo;

// this class will now represent an individual space                          
// there will be 64 of them in all????
class Space {

 protected:

  int xcor, ycor;
  int type;
  std::string team;
  bool aliveOrDead;
  
 public:
  
  // setters and getters
  int getXcor() const;
  void setXcor(int x);
  int getYcor() const;
  void setYcor(int x);
  int getType() const;
  void Move() const;

  std::string getTeam() const;

  bool isAlive();
  void setAlive(bool pig);

  // Must do this because you're putting it in a set
  bool operator <(const Space &other) const;

  // others
   void middlespace(int a, char b);
  
  // Constructors
  Space(int x, int y, int typ, std::string tem, bool isAlive);
  Space();
};

int Space::getXcor() const {
  return xcor;
}

void Space::setXcor(int x) {
  xcor = x;
}

int Space::getYcor() const {
  return ycor;
}

void Space::setYcor(int y) {
  ycor = y;
}

int Space::getType() const{
  return type;
}

std::string Space::getTeam() const{
  return team;
}

bool Space::isAlive() {
  return aliveOrDead;
}

void Space::setAlive(bool pig) {
  aliveOrDead = pig;
}

void Space::Move() const {
  setXcor(moveInfo.pos2);
  setYcor(moveInfo.pos3);
}

bool Space::operator <(const Space &right) const{
  if ((getXcor() < right.getXcor()) || (getYcor() < right.getYcor()))
    return true;
  else
    return false;
}

// Constructor
Space::Space(int x, int y, int beep1, std::string beep2, bool door) {
  xcor = x;
  ycor = y;
  type = beep1;
  team = beep2;
  aliveOrDead = door;
}

// Overloaded Constructor necessary because it is called in the subclass
Space::Space() { }

class EmptySpace: public Space {
 protected:
  static EmptySpace* theOne; // the Singleton
 public:
  void middlespace(int a, char wOrb);
  void Move();
  // Must do this because you're putting it in a set  
  bool operator <(const Space &other) const;
  static EmptySpace* getInstance();
  // also inherits all Space methods
};

EmptySpace* EmptySpace::getInstance() {
  return theOne;
}

void EmptySpace::Move() {
  std::cout << "There was no "<< moveInfo.thePiece << " at " << moveInfo.pos0 << moveInfo.pos1 << std::endl;
}

EmptySpace* EmptySpace::theOne = 0;

bool EmptySpace::operator <(const Space &right) const {

}

class WhiteEmptySpace: public EmptySpace {
 public:
  static WhiteEmptySpace* theOne;
  static EmptySpace* getInstance(); // this overrides the EmptySpace Method
  WhiteEmptySpace();
};

EmptySpace* WhiteEmptySpace::getInstance() {
  if (theOne == 0)
    theOne = new WhiteEmptySpace;
  return theOne;
}

// Constructor
WhiteEmptySpace::WhiteEmptySpace() { 
  type = 0;
}

WhiteEmptySpace* WhiteEmptySpace::theOne = 0;

class BlackEmptySpace: public EmptySpace {
 public:
  // the only instance
  static BlackEmptySpace* theOne;
  static EmptySpace* getInstance();
  BlackEmptySpace();
};

EmptySpace* BlackEmptySpace::getInstance() {
  if (theOne == 0)
    theOne = new BlackEmptySpace;
  return theOne;
}

// Constructor
BlackEmptySpace::BlackEmptySpace() {
  type = 1;
}

BlackEmptySpace* BlackEmptySpace::theOne = 0;

class Board {
  
 public:
  
  int board[8][8];
  std::vector<std::string> whiteprint, middleline, blackprint, theLetters;

  void initializeBoard();
  void displayBoard();
  void middlespace(int a, char wOrB);
  void whitespace(int a, Space item);
  void blackspace(int a, Space item);
  void fillInBoard();
  void Move();
  static void printPiece(std::string team, int pieceNum);
  Space const findByIndex(int x, int y);
};

#endif
