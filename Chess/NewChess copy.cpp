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

//Make these available to all functions
//"Pieces" has the numbers as a key and the letters as the value
std::map<int, std::string> numToPiece;
std::map<std::string, int> pieceToNum;
int board[8][8];
int cntr, pos, length, pos0, pos1, pos2, pos3;
std::string line, beep, thePiece;
std::ifstream pol;
std::fstream hey;
std::map<int, std::string> convert;
std::vector<std::string> whiteprint, middleline, blackprint, theLetters;
bool flag, flip;

//Check the rules                                           
bool isMoveValid( )
{
  char *plop = new char(1);
  strcpy( plop, thePiece.c_str() );

  switch( plop[0] )
    {
      // Pawns
    case 'P' : 
      {
	std::cout << "Entered switch" << std::endl;
	//If NOT in same column
	if (pos0 != pos2)
	    return 0;
	//If backwards or more than one forwards
	else if ( pos3 > (1 + pos1) || (pos3 <= pos1) )
	    return 0;
      }
      //Rook
    case 'R' :
      {
	//If NOT in same column                                                                                            
        if (pos0 != pos2 || pos1 != pos3)
	  return 0;
      }
      //Bishop
    case 'B' :
      {
	//must be on diagonal
	if (std::abs(pos3 - pos1) != std::abs(pos2 - pos0))
	  return 0;
      }
      //Queen
    case 'Q' :
      {
	//Same as Rook || Bishop
	if ((pos0 != pos2) || (pos1 != pos3) || (std::abs(pos3 - pos1) != std::abs(pos2 - pos0)))
          return 0;
      }
      //King
    case 'K' :
      {
	//Can move anywhere ONLY 1 away
	if (( std::abs(pos3 - pos1) > 1 ) || (std::abs(pos2 - pos0) > 1))
	  return 0;
      }
      //Night
    case 'N' :
      {
	//Can only move in "L" shape
	//There are only 8 possible move squares
	if (std::abs(pos3 - pos1) > 2 || std::abs(pos2 - pos0) > 2)
	  return 0;
	// Now that we've confined it to only moving 2 spaced in any given direction...
	// we can use the same restrictions as the queen, but opposite
	if ((pos0 == pos2) || (pos1 == pos3) || (std::abs(pos3 - pos1) == std::abs(pos2 - pos0)))
	  return 0;
      }
    }

  return 1;
}

//Move the Piece
void Move()
{
  //Check validity of Move
  if ( !isMoveValid() )
    {
      std::cout << "Move not valid" << std::endl;
      return;
    }

  //Make sure there is a piece there                                                     
  if ( numToPiece [ board[ 7 - pos1 ][ pos0 ] ] != thePiece )
    std::cout << "There is no " << thePiece << " at "
              << (char)(pos0 + 97) << (pos1 + 1)<< std::endl;

  //Move the piece                                              
  else
    {
      board[ 7 - pos3 ][ pos2 ] = pieceToNum[thePiece];
      board[ 7 - pos1 ][ pos0 ] = 0;
    }
  return;
}

void extractMove(std::string a)
{
  //Stay Alive printout
  std::cout << "Your move is being processed" << std::endl;
  length = a.length();

  //Check for valid input                                                                                       
  if (length != 9)
    {
      std::cout << "Invalid input... Try agian please :)" << std::endl;
      return;
    }

  std::vector<int> theInts;
  std::vector<char> theChars;
  pos = a.find(" to ");

  //Split the input up                                                                                          
  thePiece = a.substr(0, 1);
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
  pos0 = tolower( eins ) - 97; //letter
  pos1 = zwei - 49; //number
  pos2 = tolower( drei ) - 97; //letter
  pos3 = vier - 49; //number

  std::cout << "pos0 = " << pos0 << std::endl
	    << "pos1 = " << pos1 << std::endl
	    << "pos2 = " << pos2 << std::endl
	    << "pos3 = " << pos3 << std::endl;
  //Actually move the piece
  Move();
}

bool isGameOver( int[8][8] )
{
  //for (int i = 0; i < 8; i++)
  {
  }
  return 1;
}

void middlespace(int a, char b)
{
  if (b == 'w')
    {
      std::cout << middleline[0];
      if ( a >= 1 )
	std::cout << "\033[1;31m"
		  << numToPiece[a]
		  << "\033[0m";
      else
	std::cout << numToPiece[a];
      std::cout << middleline[1];
    }
  else
    {
      std::cout << middleline[2];
      if( a >= 1 )	
	std::cout << "\033[1;31m"
		  << numToPiece[a]
		  << "\033[0m";
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

void blackspace(int a, int piece)
{
  //check to see where i is          
  if (a == 0 )
    std::cout << blackprint[0];
  else if (a != 2 )
    std::cout << blackprint[1];
  else
    middlespace(piece, 'b');
}

void displayBoard( int pop[8][8] )
{
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

  //To print 8 rows
  for (int h = 0; h < 8; h++)
    {
      //To print 5 lines per row
      for(int i = 0; i < 4; i++)
	{
	  if (i == 2)
	    std::cout << "\033[1m" << (8 - h) << "\033[0m\t";
	  else
	    std::cout << " \t";
	  //To print 8 columns
	  for (int j = 0; j < 8; j++)
	    {
	      //Alternate B/W spaces
	      if (!flag)
		whitespace(i, pop[h][j]);
	      else
		blackspace(i, pop[h][j]);
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


  //Print instructions
  pol.open( "INSTRUCTIONS.txt" );
  while ( getline( pol, line ) )
    std::cout << line << "\n";
  std::cout << "\n\n";
  pol.close();

  flip = false;
  //Fill board in upsidown
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

  //Fill in the Maps
  cntr = -1;
  pol.open("chesspieces.txt");
  while ( getline(pol, line) )
    {
      numToPiece[cntr] = line;
      pieceToNum[line] = cntr;
      cntr++;
    }
  pol.close();
  
  //Set starting positions
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
	{
	  //Not Pawns
	  if ( j == 0 || j == 7 )
	    {
	      //Rooks
	      if ( i == 0 || i == 7 ) 
		board[j][i] = 4;
	      //Knights
	      else if ( i == 1 || i == 6 )
		board[j][i] = 3;
	      //Bishops
	      else if ( i == 2 || i == 5 )
		board[j][i] = 2;
	      //Queen
	      else if ( i == 3 )
		board[j][i] = 5;
	      //King
	      else if ( i == 4 )
		board[j][i] = 6;
	    }
	  //Pawns
	  else if (j == 1 || j == 6 )
	    board[j][i] = 1;
	}
    }
  int stop;
  //The Workhorse                                             
  while ( isGameOver( board ) && ( stop < 3 ) )
    {
      //stop++;
      displayBoard( board );
      //std::cout << "\033[0m"; 
      std::cout << "Your move: \t" << std::endl;
      std::getline( std::cin, beep);
      std::cin.clear();
      std::cout << "\n";
      std::cout << "Your move was " << beep << std::endl;
      extractMove( beep );
    }
}
//WhoWon

//One for each player

//updateBoard

