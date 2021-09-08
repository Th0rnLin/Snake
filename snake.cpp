#include <iostream>
#include <conio.h>

using namespace std;

bool game_over;
int weigh=20;
int height=20;
int x, y, xfruit, yfruit, score, ntail;
int xtail[100], ytail[100];
enum Direction {STOP, UP, DOWN, LEFT, RIGHT};
Direction dir;

void Setup(){
	x=weigh/2;
	y=height/2;
	xfruit=rand()%weigh;
	yfruit=rand()%height;
	score=0;
	dir=STOP;
	game_over=false;
}

void Input(){
	if(_kbhit()){
		switch(_getch()){
			case 'w': dir=UP; break;
			case 's': dir=DOWN; break;
			case 'a': dir=LEFT; break;
			case 'd': dir=RIGHT; break;
			case 'x': game_over=true; break;
		}	
	}
}

void Draw(){
	system("cls");
	for(int i=0; i<weigh+2; i++){cout << "#";} cout << endl;
	for(int i=0; i<height; i++){
		for(int j=0; j<weigh+2; j++){
			if(j==0 || j==weigh+1){cout << "#";}
			else if(i==y && j==x){cout << "O";}
			else if(i==yfruit && j==xfruit){cout << "F";}
			else{
				bool is_print=true;
				for(int k=0; k<ntail; k++){if(i==ytail[k] && j==xtail[k]){cout << "o"; is_print=false;}}
				if(is_print){cout << " ";}
			}
		}
		cout << endl;
	}
	for(int i=0; i<weigh+2; i++){cout << "#";} cout << endl;
}

void Algorithm(){
	int xtmp=xtail[0], ytmp=ytail[0];
	int xtmp2, ytmp2;
	xtail[0]=x;
	ytail[0]=y;
	for(int i=1; i<ntail; i++){
		xtmp2=xtail[i];
		ytmp2=ytail[i];
		xtail[i]=xtmp;
		ytail[i]=ytmp;
		xtmp=xtmp2;
		ytmp=ytmp2;
	}
	
	switch(dir){
		case UP: y--; break;
		case DOWN: y++; break;
		case LEFT: x--; break;
		case RIGHT: x++; break;
	}
	
	if(x==xfruit && y==yfruit){
		score+=10;
		xfruit=rand()%weigh;
		yfruit=rand()%height;
		ntail++;
	}
	
	if(x<1 || x>weigh || y<0 || y>height-1){game_over=true;}
	for(int i=0; i<ntail; i++){if(x==xtail[i] && y==ytail[i]){game_over=true;}}
}

int main(){
	Setup();
	while(!game_over){
		Draw();
		Input();
		Algorithm();
		cout << score << endl;
	}
	return 0;
}
