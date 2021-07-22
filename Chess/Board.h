// This class will create a board object which will "hopefully" do a lot of the behind the scenes work for the
// chess program

// I need to 1) initialize the board with all of the pieces and 2) have a separate
// function to refresh and board
#ifndef BOARD_H
#define BOARD_H

#include <ctype.h>
#include <map>
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cstdlib>
#include <set>

#include "chessLord.h"

std::vector<std::string> whiteprint, middleline, blackprint, theLetters;
std::map<int, std::string> numToPiece;
std::map<std::string, int> pieceToNum;
std::ifstream pol;
std::set<Space> allSpaces;

Space WhiteOrBlack(int x, int y) {
  if ((x%2 == 0 && y%2 == 0) || (x%2 == 1 && y%2 == 1)){ // empty white space   

    Space helper = *(WhiteEmptySpace().getInstance());
    return *(WhiteEmptySpace().getInstance()); // must dereference the instance (see header)   
  }
  else { // empty black space 
    return *(BlackEmptySpace().getInstance());
  }
}


// Can't return NULL when expecting an object so 
Space const Board::findByIndex(int x, int y) {
  std::cout <<"l";
  for(std::set<Space>::iterator iter = allSpaces.begin(); iter != allSpaces.end(); iter++) {
    if ((iter -> getXcor() == x) && (iter -> getYcor() == y)) {
      return *iter; // must dereference
    }
  }
  return (WhiteOrBlack(x, y)); //  didn't find it, so
}

void Board::printPiece(std::string team, int pieceNum ) {
  if (team.compare("red") == 0 ) // was red team                                                                           
    std::cout << "\033[1;31m" // this makes them red 
	      << numToPiece[pieceNum]
	      << "\033[0m";
  else if (team.compare("blue") == 0)// was blue team    
    std::cout << "\033[1;34m" // this makes them red                                                                                  
	      << numToPiece[pieceNum]
	      << "\033[0m";
  else
    throw "Team not red or blue";
}

// overloaded function for empty middle space
void EmptySpace:: middlespace(int a, char wOrb) {
  if (wOrb == 'w') { // if a white middle space
    std::cout << middleline[0]
	      << numToPiece[a]
	      << middleline[1]; // finish line
  }
  else if (wOrb == 'b') {
    std::cout << middleline[2]
	      << numToPiece[a]
	      << middleline[3]; // finish line
  }
  else
    throw "Space not w or b";
}

// This should be passed a space object, the appropriate space such that I can grab the data from it
void Space:: middlespace(int a, char wOrb) {
  if (wOrb == 'w') { // if a white middle space                                   
    std::cout << middleline[0];
    Board::printPiece(this -> getTeam(), this -> getType());
    std::cout << middleline[1];
  }
  else if (wOrb == 'b') { // black middle space
    std::cout << middleline[2];
    Board::printPiece(this -> getTeam(), this -> getType());
    std::cout << middleline[3]; // finish the line
  }
  else 
    throw "Space not w or b";
}

void Board::whitespace(int a, Space item) {
  // check to see where i is 
  //  std::cout << " here";
  if (a == 0 )
    std::cout << whiteprint[0];
  else if (a != 2 )
    std::cout << whiteprint[1];
  else {
    std::cout << "m";
    item.middlespace(item.getType(), 'w');
  }
}

void Board::blackspace(int a, Space item) {
  // check to see where i is
  if (a == 0 )
    std::cout << blackprint[0];
  else if (a != 2 )
    std::cout << blackprint[1];
  else {
    item.middlespace(item.getType(), 'b'); // item.getType returns the integer representation of the piece
  }
}


void Board::displayBoard( ) {
  bool flag;
  std::string line;
  //Load vector for Letters on side 
  pol.open("alpha.txt");
  while ( getline(pol, line) )
    theLetters.push_back( line );
  pol.close();
  
  //Load vectors for tiles                             
  whiteprint.push_back("______ ");
  whiteprint.push_back("|     |");
  blackprint.push_back("______ ");
  blackprint.push_back("|+++++|");
  middleline.push_back("|  ");
  middleline.push_back("  |");
  middleline.push_back("|+ ");
  middleline.push_back(" +|");
  
  // This is for each individual tile             
  // To print 8 rows                                                                                                   
  for (int h = 0; h < 8; h++)
    {
      std::cout << h << "\n";
      // To print 5 lines per row                                     
      for(int i = 0; i < 4; i++)
        {
	  std::cout << i;
          if (i == 2)
	    std::cout << "\033[1m" << (8 - h) << "\033[0m\t";
          else
	    std::cout << " \t";
	  // To print 8 columns    
          for (int j = 0; j < 8; j++)
            {
	      std::cout << j;
              // Alternate B/W spaces               
              if (!flag) {
		std::cout << "w" << std::endl;
		whitespace(i, findByIndex(h, j)); // findByIndex returns the Space object or an EmptySpaceObject
	      }  
	      else {
		std::cout << "b";
		blackspace(i, findByIndex(h, j)); 
	      }
	      flag = !flag;
	    }
	  std::cout << std::endl;
	}
      flag = !flag;
    }
  std::cout << "\n\n\t   ";
  for (int k = 0; k < theLetters.size(); k++)
    std::cout << "\033[1m" << theLetters[k] << "\033[0m      ";
  std::cout << std::endl;
}



// Must call this before DisplayBoard
// This will set up the board originally
void Board::fillInBoard() {
  bool flip = false;
  
  //Fill in the Maps  
  int cntr = -1;
  std::string line;
  pol.open("chesspieces.txt");
  while ( getline(pol, line) )
    {
      numToPiece[cntr] = line;
      pieceToNum[line] = cntr;
      cntr++;
    }
  std::cout << "num to piece size is " << numToPiece.size() <<std::endl;
  pol.close();
  
  // Fill board in upsidown
  // this just sets the spaces to be white or black
  for (int i = 7; i >= 0; i--)
    {
      for (int j = 7; j >= 0; j--)
        {
          if(flip)
            board[i][j] = -1;
          else
            board[i][j] = 0;
          flip = !flip;
        }
      flip = !flip;
    }
  
  // This will set the red team
  pol.open("START.txt");
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 7; j++) {
      getline(pol, line);
      allSpaces.insert(Space(j, i, pieceToNum[line], "red", true)); // see chessLord.h for the Space class definition
    }
  pol.close();

  // This will set the blue team
  pol.open("START.TXT");
  for (int i = 6; i < 8; i++)
    for (int j = 0; j < 7; j++) {
      getline(pol, line);
      allSpaces.insert(Space(j, i, pieceToNum[line], "blue", true)); // see chessLord.h for the Space class definition 
    }
  pol.close();

  // I need to assign every other space to an emptySpace object
  // Do I? If i don't, i won't fi
  for (int i = 2; i < 6; i++)
    for (int j = 0; j < 7; j++) {
      allSpaces.insert(WhiteOrBlack(i, j));
    }
  std::cout << allSpaces.size() << std::endl;
  std::cout << "done" << std::endl;
}

// Move the Piece    
// Move the isMoveValid call to a separate thing  
// Will need to 1) change the coordinates of the piece being moved 2) add a new one with the old coordinates  
// 3) But it needs to be properly white of black so call WhiteOrBlack
void Board::Move() {
  findByIndex(moveInfo.pos0, moveInfo.pos1).Move(); // this calls the appropriate move bc find can return either Space or emptySpace
  
}

#endif
