/*

Author:		Thomas Bolden
Project:	Project 08
Date:		November 07, 2016
Section:	001

*/

#include <iostream>
using std::cout; using std::endl; using std::cin; using std::ostream;
using std::boolalpha;

#include <string>
using std::string;

#include <algorithm>
using std::find; using std::distance;

//  Grid class
// 	has attributes:
//		size_t dim_    ~ the dimensions of the grid (square) / tiles in each direction 
//		size_t goal_x_ ~ the x position of the goal
//		size_t goal_y_ ~ the y position of the goal
//  and grants access to these attributes to the friendly bot
class Grid{
private:
	size_t dim_;
	size_t goal_x_;
	size_t goal_y_;

public:
  	Grid()=default;
  	Grid(size_t, size_t, size_t);
  	friend class Bot;
};

//  Grid constructor
//  unlike the last project, there doesnt really need to be a physical grid per-se
//  because we only need to know its dimensions and goal position for the bot
Grid::Grid(size_t dimensions, size_t x, size_t y){
	dim_    = dimensions;
	goal_x_ = x;
	goal_y_ = y;
}

//  Bot class
//
//  has attributes:
//		size_t x_pos_   ~ the x position of the bot in the grid
//      size_t y_pos_   ~ the y position of the bot in the grid
//		dir_		    ~ the compass direction the bot is facing in the grid
//		string command_ ~ a string of commands telling the bot how to move
//						  the string is repeated when commands are complete
//		Grid grid_		~ the grid that the bot will move on
//
//  and has the following member functions:
//		void rotate() 			~ changes the direction of the bot 90deg clockwise
//		void forward(); 		~ moves the bot one space in the directions it's facing
//  	void back();			~ moves the bot back one space keeing it's direction
//  	void left();			~ turns the bot 270deg clockwise to face left
//  	void right();			~ turns the bot 90deg clockwise to face right
//  	void execute_command(); ~ takes the command string and moves bot accordingly
//  	bool at_goal();			~ checks whether the (x,y) coords of bot == (x,y) of goal
class Bot{
private:
	size_t x_pos_;
	size_t y_pos_;
	char   dir_;
	string command_;
	Grid   grid_;

public:
  	Bot()=default;
  	Bot(size_t, size_t, char, string, Grid&);
  	void rotate();
  	void forward();
  	void back();
  	void left();
  	void right();
  	void execute_command();
  	bool at_goal();
  	friend ostream& operator << (ostream&,Bot&);  
};

//setup the bot
Bot::Bot(size_t x,size_t y, char facing, string command, Grid& grid){
	x_pos_   = x;
	y_pos_   = y;
	dir_     = facing;
	command_ = command;
	grid_    = grid;
}

// rotate the bots face 90 degrees clockwise
void Bot::rotate(){
	char directions[5] = {'n','e','s','w','n'};
	int index_of_dir = distance(directions, find(directions, directions+4, dir_));
	dir_ = directions[index_of_dir+1];
}

//  move the bot one space in the direction it's facing 
//  except if the bot is facing a wall
void Bot::forward(){
	if     ((y_pos_ == grid_.dim_-1) && (dir_ == 'n')){return;}
	else if((x_pos_ == grid_.dim_-1) && (dir_ == 'e')){return;}
	else if((y_pos_ == 0)            && (dir_ == 's')){return;}
	else if((x_pos_ == 0)            && (dir_ == 'w')){return;}
	else if(dir_ == 'n'){y_pos_ += 1;}
	else if(dir_ == 'e'){x_pos_ += 1;}
	else if(dir_ == 's'){y_pos_ -= 1;}
	else if(dir_ == 'w'){x_pos_ -= 1;}
}


//rotate, rotate, forward
void Bot::back(){
	rotate();
	rotate();
	forward();
	rotate();
	rotate(); // because back should make bot move back keeping face
}

//rotate rotate rotate 
void Bot::left(){
	rotate();
	rotate();
	rotate();
	//forward(); <- misread instructions, rotate but dont move bot
}

// rotate 
void Bot::right(){
	rotate();
	//forward();
}

//  function that
string newstring;
void Bot::execute_command(){
	if     (command_.size() == 0){command_ = newstring;}
	char ch = command_[0];
	if     (ch == 'f'){forward();}
	else if(ch == 'b'){back();}
	else if(ch == 'r'){right();}
	else if(ch == 'l'){left();}
	newstring += ch;
	command_.erase(0,1); // get rid of executed commands from string
						 // so that only unperformed commands remain
}

//  pretty straightforward... if the bot is at the goal, return true. else false
bool Bot::at_goal(){
	bool GoalMet = false;
	if(x_pos_ == grid_.goal_x_ && y_pos_ == grid_.goal_y_){GoalMet = true;}
	return GoalMet;
}

// output should be like this:
// 		(x position, y position) facing:direction (char)
ostream& operator << (ostream& os, Bot& outbot){
	os << '(';
	os << outbot.x_pos_ << ',';
	os << outbot.y_pos_;
	os << ')' << ' ' << "facing:";
	os << outbot.dir_;
	return os;
}

int main(){

	cout << boolalpha;
	size_t dim, goal_x, goal_y;
	cin >> dim >> goal_x >> goal_y;

	size_t bot_x, bot_y;
	char bot_dir;
	string command_str;
	cin >> bot_x >> bot_y >> bot_dir >> command_str;

	long limit;
	cin >> limit;
	  
	Grid g(dim, goal_x, goal_y);
	Bot b(bot_x, bot_y, bot_dir, command_str ,g);
	int cnt=0;

	while(!b.at_goal() && cnt < limit){
		//cout << b << endl;
	  	b.execute_command();
	    ++cnt;
	}
	cout << b << endl;
	cout << b.at_goal();

	return 0;
}