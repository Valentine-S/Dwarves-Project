//C
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

double changingRow;
double sectorCols[8];
Dir dirs[8];
bool walked[8];

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

  if(NUM == 6){
    sectorCols[0] = 1/3;
    sectorCols[1] = 2/3;
    sectorCols[2] = 1;
    sectorCols[3] = 1/3;
    sectorCols[4] = 2/3;
    sectorCols[5] = 1; 
  }
  if(NUM == 7){
    sectorCols[0] = 1/3;
    sectorCols[1] = 2/3;
    sectorCols[2] = 1;
    sectorCols[3] = 1/3;
    sectorCols[4] = 2/3;
    sectorCols[5] = 1; 
  }
  if(NUM == 8){
    sectorCols[0] = 1/4;
    sectorCols[1] = 1/2;
    sectorCols[2] = 3/4;
    sectorCols[3] = 1;
    sectorCols[4] = 1/4;
    sectorCols[5] = 1/2;
    sectorCols[6] = 3/4;
    sectorCols[7] = 1;
  }
  
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

  if(day < 3){
    if(dwarf.name() > (NUM/2 -1)){
      changingRow = 0.5;
    }

    if(walked[dwarf.name()] == false){
      //log << "Test1" << endl;
      for(int row = changingRow * ROWS; row < (int)(ROWS * (0.5 + changingRow)); row++){//Tell dwarfs where to walk to get PINE_TREE
	for(int col = (int)(sectorCols[dwarf.name()%(NUM/2)] * COLS); col < (int) (sectorCols[dwarf.name()%(NUM/2) + 1] * COLS); col++){
	 
	  if(isNextToAPineTree(dwarf,row,col) == true){
	   
	    if(dwarf.look(r,c+1) == PINE_TREE){
	      dirs[dwarf.name()] == EAST;
	    }
	    if(dwarf.look(r+1,c) == PINE_TREE){
	      dirs[dwarf.name()] == SOUTH;
	    }
	    if(dwarf.look(r-1,c) == PINE_TREE){
	      dirs[dwarf.name()] == NORTH;
	    }
	    if(dwarf.look(r,c-1) == PINE_TREE){
	      dirs[dwarf.name()] == WEST;
	    }
	    
	    log << "Found tree -- walking NAME:" << dwarf.name() << endl;
	    dwarf.start_walk(row,col);
	    walked[dwarf.name()] = true;
	    return;
	  }
	}
      }
    }
    else{//if walked is true
      
      log << "Chop" << " Name: " << dwarf.name() << endl;
      dwarf.start_chop(dirs[dwarf.name()]);
      walked[dwarf.name()] = false;
      return;
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
