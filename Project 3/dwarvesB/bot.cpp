
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

  if(TimeToBuild == false){
    if(dwarf.name() == 0){//Top Left Section
      if(walked == true){
	// Look if there is a tree on the right from the dwarf
	if (dwarf.look(r, c+1) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(EAST);
	  walked = false;
	  return;
	}
	else if (dwarf.look(r+1, c) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(SOUTH);
	  walked = false;
	  return;
	}
	else if (dwarf.look(r, c-1) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(WEST);
	  walked = false;
	  return;
	}
	else if (dwarf.look(r-1, c) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(NORTH);
	  walked = false;
	  return;
	}
      }
      for(int row = 1; row < ROWS/2; row++){
	for(int col = 1; col < COLS/3; col++){
	  if(isNextToAPineTree(dwarf,row,col)){
	    log << "Walk to " << row << " " << col << endl;
	    dwarf.start_walk(row, col);
	    walked = true;
	    return;
	  }
	}
      }
    }

    if(dwarf.name() == 1){//Top Middle Section
      if(walked1 == true){
	// Look if there is a tree on the right from the dwarf
	if (dwarf.look(r, c+1) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(EAST);
	  walked1 = false;
	  return;
	}
	else if (dwarf.look(r+1, c) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(SOUTH);
	  walked1 = false;
	  return;
	}
	else if (dwarf.look(r, c-1) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(WEST);
	  walked1 = false;
	  return;
	}
	else if (dwarf.look(r-1, c) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(NORTH);
	  walked1 = false;
	  return;
	}
      }
      for(int row = 1; row < ROWS/2; row++){
	for(int col = COLS/3; col < (2*COLS)/3; col++){
	  if(isNextToAPineTree(dwarf,row,col)){
	    log << "Walk to " << row << " " << col << endl;
	    dwarf.start_walk(row, col);
	    walked1 = true;
	    return;
	  }
	}
      }
    }
    if(dwarf.name() == 2){//Top Right Section
      if(walked2 == true){
	// Look if there is a tree on the right from the dwarf
	if (dwarf.look(r, c+1) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(EAST);
	  walked2 = false;
	  return;
	}
	else if (dwarf.look(r+1, c) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(SOUTH);
	  walked2 = false;
	  return;
	}
	else if (dwarf.look(r, c-1) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(WEST);
	  walked2 = false;
	  return;
	}
	else if (dwarf.look(r-1, c) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(NORTH);
	  walked2 = false;
	  return;
	}
      }
      for(int row = 1; row < ROWS/2; row++){
	for(int col = 2*COLS/3; col < COLS-1; col++){
	  if(isNextToAPineTree(dwarf,row,col)){
	    log << "Walk to " << row << " " << col << endl;
	    dwarf.start_walk(row, col);
	    walked2 = true;
	    return;
	  }
	}
      }
    }
    if(dwarf.name() == 3){//Bottom Left Section
      if(walked3 == true){
	// Look if there is a tree on the right from the dwarf
	if (dwarf.look(r, c+1) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(EAST);
	  walked3 = false;
	  return;
	}
	else if (dwarf.look(r+1, c) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(SOUTH);
	  walked3 = false;
	  return;
	}
	else if (dwarf.look(r, c-1) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(WEST);
	  walked3 = false;
	  return;
	}
	else if (dwarf.look(r-1, c) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(NORTH);
	  walked3 = false;
	  return;
	}
      }
      for(int row = ROWS/2; row < ROWS-1; row++){
	for(int col = 1; col < COLS/3; col++){
	  if(isNextToAPineTree(dwarf,row,col)){
	    log << "Walk to " << row << " " << col << endl;
	    dwarf.start_walk(row, col);
	    walked3 = true;
	    return;
	  }
	}
      }
    }
    if(dwarf.name() == 4){//Bottom Middle Section
      if(walked4 == true){
	// Look if there is a tree on the right from the dwarf
	if (dwarf.look(r, c+1) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(EAST);
	  walked4 = false;
	  return;
	}
	else if (dwarf.look(r+1, c) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(SOUTH);
	  walked4 = false;
	  return;
	}
	else if (dwarf.look(r, c-1) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(WEST);
	  walked4 = false;
	  return;
	}
	else if (dwarf.look(r-1, c) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(NORTH);
	  walked4 = false;
	  return;
	}
      }
      for(int row = ROWS/2; row < ROWS-1; row++){
	for(int col = COLS/3; col < 2*COLS/3; col++){
	  if(isNextToAPineTree(dwarf,row,col)){
	    log << "Walk to " << row << " " << col << endl;
	    dwarf.start_walk(row, col);
	    walked4 = true;
	    return;
	  }
	}
      }
    }
    if(dwarf.name() == 5){//Bottom Right Section
      if(walked5 == true){
	// Look if there is a tree on the right from the dwarf
	if (dwarf.look(r, c+1) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(EAST);
	  walked5 = false;
	  return;
	}
	else if (dwarf.look(r+1, c) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(SOUTH);
	  walked5 = false;
	  return;
	}
	else if (dwarf.look(r, c-1) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(WEST);
	  walked5 = false;
	  return;
	}
	else if (dwarf.look(r-1, c) == PINE_TREE) {
	  // If there is a pine tree, chop it
	  log << "Found a tree -- chop" << endl;
	  dwarf.start_chop(NORTH);
	  walked5 = false;
	  return;
	}
      }
      for(int row = 2*ROWS/3; row < ROWS-1; row++){
	for(int col = COLS/2; col < COLS-1; col++){
	  if(isNextToAPineTree(dwarf,row,col)){
	    log << "Walk to " << row << " " << col << endl;
	    dwarf.start_walk(row, col);
	    walked5 = true;
	    return;
	  }
	}
      }
    }
  }

  if(dwarf.lumber() >= 330 && !Active){
    TimeToBuild = true;
    walked = false;
    walked1 = false;
    walked2 = false;
    walked3 = false;
    walked4 = false;
    walked5 = false;
    Active = true;
  }
  
  if(TimeToBuild){
    if(dwarf.name() == 0){
      if(walked == true && dwarf.look(ROWS/2 + increment,COLS/2) == EMPTY){
	dwarf.start_build(NORTH);
	walked = false;
	return;
      }
      if(walked == true && dwarf.look(ROWS/2 + increment,COLS/2) != EMPTY){
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(SOUTH);
      return;
      }
      else{
	log << "Walk to " << ROWS/2 + increment << " " << COLS/2 << endl;
	dwarf.start_walk(ROWS/2 + increment, COLS/2);
	increment++;
	walked = true;
	return;
      }
    }
    if(dwarf.name() == 1){
      if(walked1 == true){
	dwarf.start_build(NORTH);
	walked1 = false;
	return;
      }
      else{
	log << "Walk to " << ROWS/2 + increment1 << " " << COLS/2+1 << endl;
	dwarf.start_walk(ROWS/2 + increment1, COLS/2+1);
	increment1++;
	walked1 = true;
	return;
      }
    }
    if(dwarf.name() == 2){
      if(walked2 == true){
	dwarf.start_build(NORTH);
	walked2 = false;
	return;
      }
      else{
	log << "Walk to " << ROWS/2 + increment2 << " " << COLS/2+2 << endl;
	dwarf.start_walk(ROWS/2 + increment2, COLS/2+2);
	increment2++;
	walked2 = true;
	return;
      }
    }
    if(dwarf.name() == 3){
      if(walked3 == true){
	dwarf.start_build(NORTH);
	walked3 = false;
	return;
      }
      else{
	log << "Walk to " << ROWS/2 + increment3 << " " << COLS/2+3 << endl;
	dwarf.start_walk(ROWS/2 + increment3, COLS/2+3);
	increment3++;
	walked3 = true;
	return;
      }
    }
    if(dwarf.name() == 4){
      if(walked4 == true){
	dwarf.start_build(NORTH);
	walked4 = false;
	return;
      }
      else{
	log << "Walk to " << ROWS/2 + increment4 << " " << COLS/2+4 << endl;
	dwarf.start_walk(ROWS/2 + increment4, COLS/2+4);
	increment4++;
	walked4 = true;
	return;
      }
    }
    if(dwarf.name() == 5){
      if(walked5 == true){
	dwarf.start_build(NORTH);
	walked5 = false;
	return;
      }
      else{
	log << "Walk to " << ROWS/2 + increment5 << " " << COLS/2+5 << endl;
	dwarf.start_walk(ROWS/2 + increment5, COLS/2+5);
	increment5++;
	walked5 = true;
	return;
      }
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
