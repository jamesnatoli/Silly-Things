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
#include "Board.h"
// the 2 .h files include the class and function definitions for the Space and Board class
// allSpaces is a set of 64 spaces filled by the call to Board::FillInBoard
// I need to create 1 Board Object, and use it to do everything
// This file should only have the string methods which extract the move and such


//Make these available to all functions
//"Pieces" has the numbers as a key and the letters as the value

int board[8][8];
int cntr;
std::string line, beep;
std::fstream hey;
std::map<int, std::string> convert;
bool flag, flip;
// These hold the locations of the pieces
std::set<int> red, blue;

// Check the rules
// Necessary***
bool isMoveValid( )
{
  // save typing
  int pos0 = moveInfo.pos0;
  int pos1 = moveInfo.pos1;
  int pos2 = moveInfo.pos2;
  int pos3 = moveInfo.pos3;

  char *plop = new char(1);
  strcpy( plop, moveInfo.thePiece.c_str() );
  
  switch( plop[0] )
    {
      // Pawns
    case 'P' : 
      {
	std::cout << "Entered switch Pawn" << std::endl;
	//If NOT in same column
	if (pos0 != pos2){
	  std:: cout << "Was not in the same column" << std::endl;
	  return 0;
	}
	//If backwards or more than one forwards
	else if ( pos3 > (1 + pos1) || (pos3 <= pos1) ) {
	  std:: cout << "was bckwrds/more than 1 forwards" << std::endl;
	  return 0;
	}
	break;
      }
      //Rook
    case 'R' :
      {
	std::cout << "Entered switch Rook" << std::endl;
	//If NOT in same column/row
        if (pos0 != pos2 && pos1 != pos3)
	  return 0;
	break;
      }
      //Bishop
    case 'B' :
      {
	std::cout << "Entered switch Bishop" << std::endl;
	//must be on diagonal
	if (std::abs(pos3 - pos1) != std::abs(pos2 - pos0))
	  return 0;
	break;
      }
      //Queen
    case 'Q' :
      {
	std::cout << "Entered switch Queen" << std::endl;
	//Same as Rook && Bishop
	if ((pos0 != pos2) && (pos1 != pos3) && (std::abs(pos3 - pos1) != std::abs(pos2 - pos0)))
          return 0;
	break;
      }
      //King
    case 'K' :
      {
	std::cout << "Entered switch King" << std::endl;
	//Can move anywhere ONLY 1 away
	if (( std::abs(pos3 - pos1) > 1 ) || (std::abs(pos2 - pos0) > 1))
	  return 0;
	break;
      }
      //Night
    case 'N' :
      {
	std::cout << "Entered switch Knight" << std::endl;
	//Can only move in "L" shape
	//There are only 8 possible move squares
	if (std::abs(pos3 - pos1) > 2 || std::abs(pos2 - pos0) > 2)
	  return 0;
	// Now that we've confined it to only moving 2 spaced in any given direction...
	// we can use the same restrictions as the queen, but opposite
	if ((pos0 == pos2) || (pos1 == pos3) || (std::abs(pos3 - pos1) == std::abs(pos2 - pos0)))
	  return 0;
	break;
      }
    }
  std::cout << "About to return true... move is valid" << std::endl;
  return 1;
}

// Determine if there is a piece in the way...
// For this i will need to know which team the piece is on... yikes D: 
// Can this be a Board functions?
void isPathClear() {


}

// Move the Piece
// This can be a Board:: function
// Move the isMoveValid call to a separate thing
// Will need to 1) change the coordinates of the piece being moved 2) add a new one with the old coordinates
// 3) But it needs to be properly white of black so call WhiteOrBlack
void Move()
{
  std::string thePiece = moveInfo.thePiece;
  // Make sure there is a piece there
  // To do this, I need to iterate over the allSpaces set
  // Use Board::FindByIndex
  if ( numToPiece [ board[ 7 - moveInfo.pos1 ][ moveInfo.pos0 ] ] != thePiece )
    std::cout << "There is no " << thePiece << " at "
              << (char)(moveInfo.pos0 + 97) << (moveInfo.pos1 + 1)<< std::endl;
  // Move the piece
  // Will need to access the proper Space object 
  else
    {
      board[ 7 - moveInfo.pos3 ][ moveInfo.pos2 ] = pieceToNum[thePiece];
      board[ 7 - moveInfo.pos1 ][ moveInfo.pos0 ] = 0;
    }
  return;
}

void extractMove(std::string a)
{
  //Stay Alive printout
  std::cout << "Your move is being processed" << std::endl;
  int length = a.length();

  //Check for valid input                                                                                       
  if (length != 9)
    {
      std::cout << "Invalid input... Try agian please :)" << std::endl;
      return;
    }

  std::vector<int> theInts;
  std::vector<char> theChars;
  int pos = a.find(" to ");

  //Split the input up                                                                                          
  moveInfo.thePiece = a.substr(0, 1);
  std::string s1 = a.substr(1, pos);
  std::string s2 = a.substr( pos + 4, (length - 1) ) ;

  //Pass the strings to arrays of chars                                           
  char *uno = new char[ s1.length() + 1 ];
  char *dos = new char[ s2.length() + 1 ];
  strcpy( uno, s1.c_str() );
  strcpy( dos, s2.c_str() );

  //Put the individal chars* in to a char
  char eins = uno[0];
  char zwei = uno[1];
  char drei = dos[0];
  char vier = dos[1];
  
  //Get the coordinates of the positions         
  moveInfo.pos0 = tolower( eins ) - 97; //letter
  moveInfo.pos1 = zwei - 49; //number
  moveInfo.pos2 = tolower( drei ) - 97; //letter
  moveInfo.pos3 = vier - 49; //number

  std::cout << "pos0 = " << moveInfo.pos0 << std::endl
	    << "pos1 = " << moveInfo.pos1 << std::endl
	    << "pos2 = " << moveInfo.pos2 << std::endl
	    << "pos3 = " << moveInfo.pos3 << std::endl;
}


// this will be v hard
bool isGameOver( int[8][8] )
{
  //for (int i = 0; i < 8; i++)
  {
  }
  return 1;
}

// I need a way to know where it is, so I can pass that to the set.find()
void middlespace(int a, char b)
{
  if (b == 'w') { // if a white middle space
    std::cout << middleline[0];
    if ( a >= 1 ) {
      if ( red.find(0) == red.end() ) // didn't find it
	std::cout << "\033[1;31m" // this makes them red
		  << numToPiece[a]
		  << "\033[0m";
      else // did find it
	std::cout << "\033[1;34m" // this makes them red
                  << numToPiece[a]
		  << "\033[0m";
    }
    else
      std::cout << numToPiece[a];
    std::cout << middleline[1];
  }
  else
    {
      std::cout << middleline[2];
      if( a >= 1 ) {
	if ( red.find(0) == red.end() ) // didn't find it
	  std::cout << "\033[1;31m" // this makes them blue
		    << numToPiece[a]
		    << "\033[0m";
	else // did find it
	  std::cout << "\033[1;34m"
		    << numToPiece[a]
		    << "\033[0m";
      }
      else
	std::cout << numToPiece[a];
      std::cout << middleline[3];
    }
}
void whitespace(int a, int piece)
{
  //check to see where i is                                                                                
  if (a == 0 )
    std::cout << whiteprint[0];
  else if (a != 2 )
    std::cout << whiteprint[1];
  else
    middlespace(piece, 'w');
}

void blackspace(int a, int piece) {
  //check to see where i is          
  if (a == 0 )
    std::cout << blackprint[0];
  else if (a != 2 )
    std::cout << blackprint[1];
  else
    middlespace(piece, 'b');
}

/*
void displayBoard( int pop[8][8] ) {
  //Load vector for Letters on side
  pol.open("alpha.txt");
  while ( getline(pol, line) )
    theLetters.push_back( line );
  
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
      // To print 5 lines per row
      for(int i = 0; i < 4; i++)
	{
	  if (i == 2)
	    std::cout << "\033[1m" << (8 - h) << "\033[0m\t";
	  else
	    std::cout << " \t";
	  // To print 8 columns
	  for (int j = 0; j < 8; j++)
	    {
	      // Alternate B/W spaces
	      if (!flag)
		whitespace(i, pop[h][j]); // i need to pass the current location in this call
	      else
		blackspace(i, pop[h][j]); // this one too ^^
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

*/
int main()
{
  /*////////////////
  //PIECE CODES/////
  //////////////////
  PAWN = 1
  BISHOP = 2
  KNIGHT = 3
  ROOK = 4
  QUEEN = 5
  KING = 6
  ////////////////*/

  // This works :D 
  Board *workHorse = new Board();
  workHorse -> fillInBoard();

  //Print instructions
  pol.open( "INSTRUCTIONS.txt" );
  while ( getline( pol, line ) )
    std::cout << line << "\n";
  std::cout << "\n\n";
  pol.close();
  
  int stop = 0;
  //The Workhorse                                             
  while ( isGameOver( board ) && ( stop < 3 ) )
    {
      //stop++;
      std::cout << "entered while" << std:: endl;
      workHorse->displayBoard( );
      //std::cout << "\033[0m"; 
      std::cout << "Your move: \t" << std::endl;
      std::getline( std::cin, beep);
      std::cin.clear();
      std::cout << "\n";
      std::cout << "Your move was " << beep << std::endl;
      if (!isMoveValid())
	std::cout << "Move not vald :(" << std::endl;
      extractMove( beep );
      workHorse->Move();
    }
}
//WhoWon

//One for each player

//updateBoard

