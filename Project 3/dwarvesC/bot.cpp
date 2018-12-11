//Csfsdfsdfsdfsdfsd
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
bool emptyPine[8];
Dir buildDirs[8];
bool chopNeeded[8];
bool freed[8];

bool isDayTime(int hours, int min){
  int temp = (hours * 60) + min;
  if (temp > 360 && temp < 1260){
    return true;
  }
  else{
    return false;
  }
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
    sectorCols[0] = 0;
    sectorCols[1] = 1.0/3;
    sectorCols[2] = 2.0/3;
    sectorCols[3] = 1;
  }
  if(NUM == 7){
    sectorCols[0] = 0;
    sectorCols[1] = 1.0/3;
    sectorCols[2] = 2.0/3;
    sectorCols[3] = 1;
  }
  if(NUM == 8){
    sectorCols[0] = 0;
    sectorCols[1] = 1.0/4;
    sectorCols[2] = 1.0/2;
    sectorCols[3] = 3.0/4;
    sectorCols[4] = 1;
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
  changingRow = 0;

  if(isDayTime(hours,minutes) == false){//Night Hiding Spaces
    log << "Build"<< dwarf.name() << "\n";
    if(buildDirs[dwarf.name()] == WEST){
      dwarf.start_build(WEST);
      buildDirs[dwarf.name()] = EAST;
      return;
    }
    if(buildDirs[dwarf.name()] == EAST){
      dwarf.start_build(EAST);
      buildDirs[dwarf.name()] = NORTH;
      return;
    }
    if(buildDirs[dwarf.name()] == NORTH){
      dwarf.start_build(NORTH);
      buildDirs[dwarf.name()] = SOUTH;
      return;
    }
    if(buildDirs[dwarf.name()] == SOUTH){
      dwarf.start_build(SOUTH);
      freed[dwarf.name()] = false;
      buildDirs[dwarf.name()] = WEST;
      return;
    }
  }

  if(isDayTime(hours,minutes) && day > 1 && freed[dwarf.name()] == false){
    dwarf.start_chop(NORTH);
    freed[dwarf.name()] = true;
    return;
  }
  
  if(walked[dwarf.name()] == true && chopNeeded[dwarf.name()] == true && isDayTime(hours,minutes)){
    log << "Chop" << " Name: " << dwarf.name() << endl;
    dwarf.start_chop(dirs[dwarf.name()]);
    walked[dwarf.name()] = false;
    chopNeeded[dwarf.name()] = false;
    return;
  }

  if(emptyPine[dwarf.name()] == false && isDayTime(hours,minutes)){//DayTime Pine Tree. Finding and walking.
    if(dwarf.name() > (NUM/2 -1)){
      changingRow = 0.5;
    }
    for(int row = changingRow * ROWS; row < (int)(ROWS * (0.5 + changingRow)); row++){//Tell dwarfs where to walk to get PINE_TREE
      for(int col = (int)(sectorCols[dwarf.name()%(NUM/2)] * COLS); col < (int) (sectorCols[dwarf.name()%(NUM/2) + 1] * COLS); col++){
	//log << dwarf.name() << " " << changingRow * ROWS << " " << (int)(ROWS * (0.5 + changingRow)) << "\n";
	//log << dwarf.name() << " " << (int)(sectorCols[dwarf.name()%(NUM/2)] * COLS) << " " << (int) (sectorCols[dwarf.name()%(NUM/2) + 1] * COLS) << "\n";
	if(dwarf.look(row,col) == EMPTY){ 
	  if(dwarf.look(row,col+1) == PINE_TREE){
	    dirs[dwarf.name()] = EAST;
	    log << "Found tree -- walking NAME:" << dwarf.name() << endl;
	    walked[dwarf.name()] = true;
	    chopNeeded[dwarf.name()] = true;
	    dwarf.start_walk(row,col);
	    return;
	  }
	  if(dwarf.look(row+1,col) == PINE_TREE){
	    dirs[dwarf.name()] = SOUTH;
	    log << "Found tree -- walking NAME:" << dwarf.name() << endl;
	    walked[dwarf.name()] = true;
	    chopNeeded[dwarf.name()] = true;
	    dwarf.start_walk(row,col);
	    return;
	  }
	  if(dwarf.look(row-1,col) == PINE_TREE){
	    dirs[dwarf.name()] = NORTH;
	    log << "Found tree -- walking NAME:" << dwarf.name() << endl;
	    walked[dwarf.name()] = true;
	    chopNeeded[dwarf.name()] = true;
	    dwarf.start_walk(row,col);
	    return;
	  }
	  if(dwarf.look(row,col-1) == PINE_TREE){
	    dirs[dwarf.name()] = WEST;
	    log << "Found tree -- walking NAME:" << dwarf.name() << endl;
	    walked[dwarf.name()] = true;
	    chopNeeded[dwarf.name()] = true;
	    dwarf.start_walk(row,col);
	    return;
	  }	  
	}
      }
    }
    emptyPine[dwarf.name()] = true;
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
