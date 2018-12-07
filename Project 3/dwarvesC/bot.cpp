
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS;  // global variables
int COLS;
int NUM;
bool walked, walked1, walked2, walked3, walked4, walked5;
int increment, increment1, increment2, increment3, increment4, increment5;
bool TimeToBuild;
bool Active;
double changingRow;


//isNextToAtree
//Returns true if there is atleast one tree adjacent to the location

bool isNextToAPineTree(Dwarf & dwarf, int r, int c){
  Place temp1 = dwarf.look(r+1,c); 
  Place temp2 = dwarf.look(r-1,c);
  Place temp3 = dwarf.look(r,c+1);
  Place temp4 = dwarf.look(r,c-1);
  Place temp5 = dwarf.look(r,c);
  if((temp1 == PINE_TREE) || (temp2 == PINE_TREE) || (temp3 == PINE_TREE) || (temp4 == PINE_TREE)){
    if(temp5 == EMPTY){
      return true;
    }
  }
  return false;
}

/*
  Dir isNextToAPineTree(Dwarf & dwarf, int r, int c){
  Place temp1 = dwarf.look(r+1,c); 
  Place temp2 = dwarf.look(r-1,c);
  Place temp3 = dwarf.look(r,c+1);
  Place temp4 = dwarf.look(r,c-1);
  if(temp1 == PINE_TREE){
  return SOUTH;
  }
  if(temp2 == PINE_TREE){
  return NORTH;
  }
  if(temp3 == PINE_TREE){
  return EAST;
  }
  if(temp4 == PINE_TREE){
  return WEST;
  }
  return NULL;
  }
*/

/* onStart: 
   An Initialization procedure called at the start of the game.
   You can use it to initialize certain global variables, or do 
   something else before the actual simulation starts.
   Parameters:
   rows: number of rows
   cols: number of columns
   num:  number of dwarfs
   log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << endl; // Print a greeting message

  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;

  
  
}

/* onAction: 
   A procedure called each time an idle dwarf is choosing 
   their next action.
   Parameters:
   dwarf:   dwarf choosing an action
   day:     day (1+)
   hours:   number of hours in 24-hour format (0-23)
   minutes: number of minutes (0-59)
   log:     a cout-like log  */

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();

  if(day == 1){
    if(hours < 21){//First DayTime
      
    }
    else{//First NightTime
      
    }
  }


  if(day < 3){
    if(dwarf.name() > (num/2 -1)){
      changingRow = 0.5;
    }

    for(int row = changingRow * ROWS; i < (int)(rows * (0.5 + changingRow)); i++){
      for(int col = 
    }


    
  }

  











  
}


 


/*
// Look if there is a tree on the right from the dwarf
if (dwarf.look(r, c+1) == PINE_TREE) {
// If there is a pine tree, chop it
log << "Found a tree -- chop" << endl;
dwarf.start_chop(EAST);
return;
}
else if (dwarf.look(r+1, c) == PINE_TREE) {
// If there is a pine tree, chop it
log << "Found a tree -- chop" << endl;
dwarf.start_chop(SOUTH);
return;
}
else if (dwarf.look(r, c-1) == PINE_TREE) {
// If there is a pine tree, chop it
log << "Found a tree -- chop" << endl;
dwarf.start_chop(WEST);
return;
}
else if (dwarf.look(r-1, c) == PINE_TREE) {
// If there is a pine tree, chop it
log << "Found a tree -- chop" << endl;
dwarf.start_chop(NORTH);
return;
}
else {
// Otherwise, move to a random location
for(int row = 0; row < ROWS; row++){
for(int col = 0; col < COLS; col++){
if(isNextToAPineTree(dwarf,row,col)){
log << "Walk to " << row << " " << col << endl;
dwarf.start_walk(row, col);
return;
}
}
}
}
}

*/
