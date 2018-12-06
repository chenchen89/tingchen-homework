#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<synchapi.h> 

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

int isChangeDir(int,int); //判断是否转向 
int snakeMove(int,int,int*); //移动 
int output(); //输出矩阵 
int gameover(); //输出游戏结束 

char map[12][13]= 
	{"************",
	"*XXXXH     *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"************"};
	
int snakeX[SNAKE_MAX_LENGTH]={1,2,3,4,5}; //蛇横坐标 
int snakeY[SNAKE_MAX_LENGTH]={1,1,1,1,1}; //蛇纵坐标 
int snakeLength=5; //蛇长度 

int main() {
	int flag=1; //用于判断游戏结束 
	char diretion='d'; //当前方向 
	char preDiretion='d'; //准备方向 
	
	output(); //初始输出 
	while(flag) {
		Sleep(500);
		system("cls"); //清屏 
		
		if(kbhit()) { //有输入键盘时 
			preDiretion=getch(); 
			if(isChangeDir(preDiretion,diretion)) {
				diretion=preDiretion; //改变方向 
			}
		}
		
		switch(diretion) { //向指定方向移动并判断是否修改flag 
			case 'a':snakeMove(-1,0,&flag);break;
			case 'w':snakeMove(0,-1,&flag);break;
			case 's':snakeMove(0,1,&flag);break;
			case 'd':snakeMove(1,0,&flag);break;
		}
		
		output();
	}
	gameover();
	
	return 0;
}

int isChangeDir(int preDiretion,int diretion) {
	int flag=0;
	
	switch(diretion) { //两方向不共线时需要改变当前方向 
		case 'a': case 'd':
			if(preDiretion == 'w' || preDiretion == 's') {
				flag=1;
			}
			break;
		case 'w': case 's':
			if(preDiretion == 'a' || preDiretion == 'd') {
				flag=1;
			}
			break;
	}
	
	return flag;
}

int snakeMove(int x,int y,int *flag) {
	int i;
	
	map[snakeY[0]][snakeX[0]]=BLANK_CELL; //尾巴移动，清空原位 
	
	for(i=0;i<snakeLength-1;i++) { //修改身体坐标 
		snakeX[i]=snakeX[i+1];
		snakeY[i]=snakeY[i+1];
	}
	snakeX[snakeLength-1]+=x; //修改头坐标 
	snakeY[snakeLength-1]+=y;
	
	for(i=0;i<snakeLength-1;i++) {
		map[snakeY[i]][snakeX[i]]=SNAKE_BODY; //身体移动 
	}
	if(map[snakeY[snakeLength-1]][snakeX[snakeLength-1]] == SNAKE_FOOD || map[snakeY[snakeLength-1]][snakeX[snakeLength-1]] == BLANK_CELL) {
		map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]=SNAKE_HEAD; //未死亡，头移动 
	}
	else {
		*flag=0; //头撞墙或咬到身体，游戏结束 
	}
	
	return 0;
}

int output() {
	int i;
	for(i=0;i<12;i++) {
		printf("%s\n",map[i]);
	}
	return 0;
}

int gameover() {
	printf("Game Over!!\n");
	return 0;
}

/*

*/
