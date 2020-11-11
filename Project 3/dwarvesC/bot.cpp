//Valentine Shidlovskiy
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
bool pickNeeded[8];
bool walkedToApple[8];
bool hidden[8];
bool emptyPump;
int increment[8];
int colInc[8] = {0,1,2,3,4,5,6,7};

bool isDayTime(int hours, int min){
  int temp = (hours * 60) + min;
  if (temp > 360 && temp < 1230){
    return true;
  }
  else{
    return false;
  }
}

//Is not used in this code. Thought it may be useful, turned out
//Not to be needed.
Loc closestApple(Dwarf &dwarf){
  Loc ans;
  int distance = 9999;
  for(int r = 0; r < ROWS; r++){
    for(int c = 0; c < COLS; c++){
      if(dwarf.look(r,c) == APPLE_TREE){
	if(distance > sqrt(pow(dwarf.row()-r,2)+pow(dwarf.col()-c,2))){
	  distance = sqrt(pow(dwarf.row()-r,2)+pow(dwarf.col()-c,2));
	  ans.r = r;
	  ans.c = c;
	}
      }
    }
  }
  return ans;
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
  changingRow = 0; //resets the changing row

  
  if(day < 3 && isDayTime(hours,minutes)){//First 2 days, Chop Pine

    if(chopNeeded[dwarf.name()] == true && walked[dwarf.name()] == true){//Chop Pine
      log << "Chop" << endl;
      dwarf.start_chop(dirs[dwarf.name()]);
      walked[dwarf.name()] = false;
      chopNeeded[dwarf.name()] = false;
      return;
    }
    
    if(dwarf.name() > (NUM/2 - 1)){//Set the Changing Row for the nested for loop
      changingRow = 0.5;
    }
    if(emptyPine[dwarf.name()] == false){//Find a Pine and walk there
      for(int row = changingRow * ROWS; row < (int)(ROWS * (0.5 + changingRow)); row++){
	for(int col = (int)(sectorCols[dwarf.name()%(NUM/2)] * COLS); col < (int) (sectorCols[dwarf.name()%(NUM/2) + 1] * COLS); col++){
	  if(dwarf.look(row,col) == EMPTY){
	    if(dwarf.look(row,col+1) == PINE_TREE){
	      dirs[dwarf.name()] = EAST;
	      log << "Found tree -- walking" << endl;
	      walked[dwarf.name()] = true;
	      chopNeeded[dwarf.name()] = true;
	      dwarf.start_walk(row,col);
	      return;
	    }
	    if(dwarf.look(row+1,col) == PINE_TREE){
	      dirs[dwarf.name()] = SOUTH;
	      log << "Found tree -- walking" << endl;
	      walked[dwarf.name()] = true;
	      chopNeeded[dwarf.name()] = true;
	      dwarf.start_walk(row,col);
	      return;
	    }
	    if(dwarf.look(row-1,col) == PINE_TREE){
	      dirs[dwarf.name()] = NORTH;
	      log << "Found tree -- walking" << endl;
	      walked[dwarf.name()] = true;
	      chopNeeded[dwarf.name()] = true;
	      dwarf.start_walk(row,col);
	      return;
	    }
	    if(dwarf.look(row,col-1) == PINE_TREE){
	      dirs[dwarf.name()] = WEST;
	      log << "Found tree -- walking" << endl;
	      walked[dwarf.name()] = true;
	      chopNeeded[dwarf.name()] = true;
	      dwarf.start_walk(row,col);
	      return;
	    }
	  }
	}
      }
      emptyPine[dwarf.name()] = true;// true when the dwarfs sector has no more pine trees
      return;
    }
  }
  
  if(walkedToApple[dwarf.name()] == false && isDayTime(hours,minutes) == false){
    if(dwarf.name() > (NUM/2 - 1)){//Set the Changing Row for the nested for loop
      changingRow = 0.5;
    }
    for(int row = changingRow * ROWS; row < (int)(ROWS * (0.5 + changingRow)); row++){//Find an apple tree and walk there
      for(int col = (int)(sectorCols[dwarf.name()%(NUM/2)] * COLS); col < (int) (sectorCols[dwarf.name()%(NUM/2) + 1] * COLS); col++){//This nested for loop splits the board up into 6 sections and assigns a dwarf to each
	if(dwarf.look(row,col) == EMPTY){
	  if(dwarf.look(row,col+1) == APPLE_TREE){
	    dirs[dwarf.name()] = EAST;
	    log << "Found Apple -- Walking" << endl;
	    walkedToApple[dwarf.name()] = true;
	    dwarf.start_walk(row,col);
	    return;
	  }
	  if(dwarf.look(row+1,col) == APPLE_TREE){
	    dirs[dwarf.name()] = SOUTH;
	    log << "Found Apple -- Walking" << endl;
	    walkedToApple[dwarf.name()] = true;
	    dwarf.start_walk(row,col);
	    return;
	  }
	  if(dwarf.look(row-1,col) == APPLE_TREE){
	    dirs[dwarf.name()] = NORTH;
	    log << "Found Apple -- Walking" << endl;
	    walkedToApple[dwarf.name()] = true;
	    dwarf.start_walk(row,col);
	    return;
	  }
	  if(dwarf.look(row,col-1) == APPLE_TREE){
	    dirs[dwarf.name()] = WEST;
	    log << "Found Apple -- Walking" << endl;
	    walkedToApple[dwarf.name()] = true;
	    dwarf.start_walk(row,col);
	    return;
	  }
	}
      }
    }    
  }

  //Build hiding spots for the night
  if(walkedToApple[dwarf.name()] && isDayTime(hours,minutes) == false){ //&& hidden[dwarf.name()] == false
    
    if(dwarf.look(dwarf.row(),dwarf.col()+1) == EMPTY){
      dwarf.start_build(EAST);
      return;
    }
    if(dwarf.look(dwarf.row()+1,dwarf.col()) == EMPTY){
      dwarf.start_build(SOUTH);
      return;
    }
    if(dwarf.look(dwarf.row()-1,dwarf.col()) == EMPTY){
      dwarf.start_build(NORTH);
      return;
    }
    if(dwarf.look(dwarf.row(),dwarf.col()-1) == EMPTY){
      dwarf.start_build(WEST);
      return;
    }
    hidden[dwarf.name()] = true;
    return;
  }

  //Free all the dwarves on the last day
  if(hidden[dwarf.name()] && day == 7 && isDayTime(hours,minutes)){
    if(dwarf.look(dwarf.row()+1,dwarf.col()) == FENCE){
      dwarf.start_chop(SOUTH);
      return;
    }
    if(dwarf.look(dwarf.row(),dwarf.col()+1) == FENCE){
      dwarf.start_chop(EAST);
      return;
    }
    if(dwarf.look(dwarf.row(),dwarf.col()-1) == FENCE){
      dwarf.start_chop(WEST);
      return;
    }
    if(dwarf.look(dwarf.row()-1,dwarf.col()) == FENCE){
      dwarf.start_chop(NORTH);
      return;
    }
    hidden[dwarf.name()] = false;
    emptyPump = false;
    pickNeeded[dwarf.name()] = false;
    walked[dwarf.name()] = false;
    return;
  }

  //Build the final Structure
  if(day == 7 && hours > 12 && hours < 20 && dwarf.lumber() > NUM*25){
    if(walked[dwarf.name()] == true && dwarf.look(ROWS/2 + increment[dwarf.name()],COLS/2 + colInc[dwarf.name()]) == EMPTY){
      dwarf.start_build(NORTH);
      walked[dwarf.name()] = false;
      return;
    }
    else if(walked[dwarf.name()] && dwarf.look(ROWS/2 + increment[dwarf.name()],COLS/2 + colInc[dwarf.name()]) != EMPTY){
      if(dwarf.look(ROWS/2 + increment[dwarf.name()],COLS/2 + colInc[dwarf.name()]) == PUMPKIN){
	log << "Found a Pumpkin" << endl;
	dwarf.start_pick(SOUTH);				 
	return;
      }
      else{
	log << "CHOP" << endl;
	dwarf.start_chop(SOUTH);
	return;
      }
    }
    else{
      log << "Walk to " << ROWS/2 + increment[dwarf.name()] << " " << COLS/2 + colInc[dwarf.name()] << endl;
      dwarf.start_walk(ROWS/2 + increment[dwarf.name()], COLS/2 + colInc[dwarf.name()]);
      (increment[dwarf.name()])++;
      walked[dwarf.name()] = true;
      return;
    }
  }

  
  //Free the last 2 dwaves during the day
  if(hidden[dwarf.name()] && day > 4 && day < 7 && isDayTime(hours, minutes) && dwarf.name() > (NUM - 3)){
    if(dwarf.look(dwarf.row()+1,dwarf.col()) == FENCE){
      dwarf.start_chop(SOUTH);
      return;
    }
    if(dwarf.look(dwarf.row(),dwarf.col()+1) == FENCE){
      dwarf.start_chop(EAST);
      return;
    }
    if(dwarf.look(dwarf.row(),dwarf.col()-1) == FENCE){
      dwarf.start_chop(WEST);
      return;
    }
    if(dwarf.look(dwarf.row()-1,dwarf.col()) == FENCE){
      dwarf.start_chop(NORTH);
      return;
    }
    hidden[dwarf.name()] = false;
    emptyPump = false;
    return;
  }

  //Tell the dwarves to pick pumpkins after they walked to one
  if(dwarf.name() > (NUM -3) && isDayTime(hours,minutes) && walked[dwarf.name()] && pickNeeded[dwarf.name()]){
    log << "Pick Pumpkin" << endl;
    dwarf.start_pick(dirs[dwarf.name()]);
    walked[dwarf.name()] = false;
    pickNeeded[dwarf.name()] = false;
    return;
  }

  
  //Send the last two dwarves to look for pumpkins during the day
  if(emptyPump == false && walked[dwarf.name()] == false && day > 4 && isDayTime(hours,minutes) && hidden[dwarf.name()] == false && pickNeeded[dwarf.name()] == false){
    //log << "TEST" << endl;
    if(dwarf.name() == NUM-1){//Divide into 2 sections so that the dwarves dont collide
      for(int row = 1; row < ROWS/2; row++){
	for(int col = 1; col < COLS-1; col++){
	  if(dwarf.look(row,col) == EMPTY){
	    if(dwarf.look(row,col+1) == PUMPKIN){
	      dirs[dwarf.name()] = EAST;
	      log << "Found Pumpkin -- walking" << endl;
	      walked[dwarf.name()] = true;
	      pickNeeded[dwarf.name()] = true;
	      dwarf.start_walk(row,col);
	      return;
	    }
	    if(dwarf.look(row+1,col) == PUMPKIN){
	      dirs[dwarf.name()] = SOUTH;
	      log << "Found Pumpkin -- walking" << endl;
	      walked[dwarf.name()] = true;
	      pickNeeded[dwarf.name()] = true;
	      dwarf.start_walk(row,col);
	      return;
	    }
	    if(dwarf.look(row-1,col) == PUMPKIN){
	      dirs[dwarf.name()] = NORTH;
	      log << "Found Pumpkin -- walking" << endl;
	      walked[dwarf.name()] = true;
	      pickNeeded[dwarf.name()] = true;
	      dwarf.start_walk(row,col);
	      return;
	    }
	    if(dwarf.look(row,col-1) == PUMPKIN){
	      dirs[dwarf.name()] = WEST;
	      log << "Found Pumpkin -- walking" << endl;
	      walked[dwarf.name()] = true;
	      pickNeeded[dwarf.name()] = true;
	      dwarf.start_walk(row,col);
	      return;
	    }
	  }
	}
      }
    }
    if(dwarf.name() == NUM-2){
      for(int row = ROWS/2; row < ROWS-1; row++){
	for(int col = 1; col < COLS-1; col++){
	  if(dwarf.look(row,col) == EMPTY){
	    if(dwarf.look(row,col+1) == PUMPKIN){
	      dirs[dwarf.name()] = EAST;
	      log << "Found Pumpkin -- walking" << endl;
	      walked[dwarf.name()] = true;
	      pickNeeded[dwarf.name()] = true;
	      dwarf.start_walk(row,col);
	      return;
	    }
	    if(dwarf.look(row+1,col) == PUMPKIN){
	      dirs[dwarf.name()] = SOUTH;
	      log << "Found Pumpkin -- walking" << endl;
	      walked[dwarf.name()] = true;
	      pickNeeded[dwarf.name()] = true;
	      dwarf.start_walk(row,col);
	      return;
	    }
	    if(dwarf.look(row-1,col) == PUMPKIN){
	      dirs[dwarf.name()] = NORTH;
	      log << "Found Pumpkin -- walking" << endl;
	      walked[dwarf.name()] = true;
	      pickNeeded[dwarf.name()] = true;
	      dwarf.start_walk(row,col);
	      return;
	    }
	    if(dwarf.look(row,col-1) == PUMPKIN){
	      dirs[dwarf.name()] = WEST;
	      log << "Found Pumpkin -- walking" << endl;
	      walked[dwarf.name()] = true;
	      pickNeeded[dwarf.name()] = true;
	      dwarf.start_walk(row,col);
	      return;
	    }
	  }
	}
      }
    }
    // emptyPump = true;//true when the dwarfs sector has no pumpkins
  }

  


  
  
  if(walkedToApple[dwarf.name()] && hidden[dwarf.name()]){//Tell dwarfs to pick apples all day and night
    dwarf.start_pick(dirs[dwarf.name()]);
    return;
  }


  

}