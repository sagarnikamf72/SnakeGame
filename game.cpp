#include<bits/stdc++.h>
#include <unistd.h>
#include<curses.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;


//  CODE FOR kbhit() TAKEN FROM : 
//		  https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
int kbhit();


bool is_tail(int , int );
void move_tail();
enum dir{STOP, LEFT, RIGHT, DOWN, UP};
const int height = 10, width = 30;
bool gameOver;
int dc = 2e4, x_snake, y_snake, x_fruit, y_fruit, score, tt = 2e5 ;
dir snake_dir;
vector<pair<int, int> > tail;


//RETURNS A NUMBER IN RANGE [a,b] 
int rand(int a, int b){
	return a + (rand()%(b-a+1));
}


void init(){
	system("clear");
	score = 0;
	gameOver = false;
	snake_dir = STOP;
	x_snake = width/2;
	y_snake = height/2;
	x_fruit = rand(1,width);
	y_fruit = rand(1,height);
}

void Draw(){
	system("clear");
	// TOP - BOUNDARY
	for(int j = 1; j <= width + 2; j++){
				cout << "!";
	}
	cout << endl;
	// SIDE BOUNDARIES
	for(int i = 1; i <= height; i++){
		cout << "!";
		for(int j = 1; j <= width; j++) {
			if(i == y_snake && j == x_snake){
				cout << "O";
			}
			else if(is_tail(j, i)){
				cout << "o";
			}
			else if(i == y_fruit && j == x_fruit)
				cout << "#";
			else  
				cout << " " ;
		}
		cout << "!" << endl;
	}
	// BOTTOM - BOUNDARY
	for(int j = 1; j <= width + 2; j++){
				cout << "!";
	}
	cout << endl;
	
	cout << "SCORE - " << score << endl;
	cout << "TIME  - " << tt << endl;

}

void Input(){
	if(kbhit()){
		char a;
		cin >> a;
		switch(a){
			case 'w':
					if(snake_dir != DOWN)
						snake_dir = UP;
					break;
			case 's':
					if(snake_dir != UP)
						snake_dir = DOWN;
					break;
			case 'a':
					if(snake_dir != RIGHT)
						snake_dir = LEFT;
					break;
			case 'd':
					if(snake_dir != LEFT)
						snake_dir = RIGHT;
					break;
			default:break;
		}
	}
}

void Logic(){
	move_tail();
	switch(snake_dir){
		case UP:y_snake--;
				break;
		case DOWN:y_snake++;
				break;
		case LEFT:x_snake--;
				break;
		case RIGHT:x_snake++;
				break;
		default:
				break;
	}
	
	
	if(x_snake == x_fruit && y_snake == y_fruit){
		tt -= dc;
		score += 10;
		x_fruit = rand(1,width);
		y_fruit = rand(1,height);
		tail.insert(tail.begin(),{x_snake, y_snake});
		switch(snake_dir){
		case UP:y_snake--;
				break;
		case DOWN:y_snake++;
				break;
		case LEFT:x_snake--;
				break;
		case RIGHT:x_snake++;
				break;
		default:
				break;
		}
	}
	
	if(is_tail(x_snake, y_snake)){
		gameOver = true;
	}
	if(y_snake < 1 || y_snake > height + 1){
		gameOver = true;
	}
	if(x_snake < 1 || x_snake > width + 1){
		gameOver = true;
	}
	
	return ;
}


int main(){
	init();
	srand(time(0));
	while(!gameOver){
		Draw();
		Input();
		Logic();
		usleep(tt);
	}
	cout << "G A M E - O V E R\n";
	cout << "SCORE - " << score << endl;
	return 0;
}


void move_tail(){
	if(tail.empty())
		return ;
	for(int i = tail.size() - 1; i > 0; i--){
		tail[i].first = tail[i-1].first;
		tail[i].second = tail[i-1].second;
	}
	tail[0].first = x_snake;
	tail[0].second = y_snake;
	return ;
}

bool is_tail(int x, int y){
	for(auto e : tail){
		if(e.first == x && e.second == y)
			return true;
	}
	return false;
}


//  CODE FOR kbhit() TAKEN FROM : 
//		  https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;

}

