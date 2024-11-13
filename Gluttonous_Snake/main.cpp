//引入图形头文件
#include<graphics.h>
//C语言标准输入输出头文件
#include<stdio.h>


//宏定义窗口长度为640像素
#define WIN_WIDTH	640
//宏定义窗口高度为480像素
#define WIN_HEIGHT	480
//宏定义蛇的最大长度为500
#define MAX_SNAKE	500

//记录游戏运行状态，默认为真
bool running = true;
//记录键盘消息结构体
ExMessage msg;

//蛇身体坐标的结构体
struct Position
{
	int x;			//定义身体的X坐标
	int y;			//定义身体的Y坐标
	DWORD color;	//定义身体的颜色
};

//存储蛇的相关数据的结构体
struct Snake
{
	int num;		//定义蛇的长度的变量
	int dir;		//定义蛇头的朝向的变量
	int score;		//定义玩家分数的变量(每吃一个食物加10分)
	int size;		//定义蛇身的大小，宽和高
	int speed;		//定义蛇行走的速度
	struct Position body[MAX_SNAKE];		//定义蛇各个身体的坐标
}snake;

//定义食物结构体
struct Food
{
	int x;			//食物的x坐标
	int y;			//食物的y坐标
	DWORD color;	//食物的颜色
	bool flag;		//食物标志，看其是否存在
}food;

//枚举出蛇头朝向的各个方向
enum DIRECTION
{
	UP,			//朝上
	DOWN,		//朝下
	LEFT,		//朝左
	RIGHT		//朝右
};
//游戏初始化
void Game_Init()
{
	srand(GetTickCount());			//设置随机种子(不理解也没关，先这样写)
	snake.num = 3;					//初始化蛇的长度为3
	snake.dir = RIGHT;				//初始化蛇的朝向为右
	snake.score = 0;				//初始化玩家分数为0
	snake.size = 10;				//初始化蛇的大小为10*10
	snake.speed = 10;				//初始化蛇的速度为10
	snake.body[0].x = 20;			//初始化蛇头的X坐标为20
	snake.body[0].y = 0;			//初始化蛇头的Y坐标为0
	//初始化蛇头的颜色，颜色随机，绘制出彩色的一条蛇
	snake.body[0].color = RGB(rand() % 256, rand() % 256, rand() % 256);

	snake.body[1].x = 10;			//初始化蛇身1的X坐标为10
	snake.body[1].y = 0;			//初始化蛇身1的Y坐标为0
	//初始化蛇身1的颜色，颜色随机，绘制出彩色的一条蛇
	snake.body[1].color = RGB(rand() % 256, rand() % 256, rand() % 256);

	
	snake.body[2].x = 0;			//初始化蛇身2的X坐标为0
	snake.body[2].y = 0;			//初始化蛇身2的Y坐标为0
	//初始化蛇身2的颜色，颜色随机，绘制出彩色的一条蛇
	snake.body[2].color = RGB(rand() % 256, rand() % 256, rand() % 256);

	//初始化食物
	food.x = rand() % (WIN_WIDTH / 10) * 10;						//食物的x坐标，确保坐标是速度的整数倍
	food.y = rand() % (WIN_HEIGHT / 10) * 10;						//食物的y坐标，确保坐标是速度的整数倍
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);		//产生一个颜色
	food.flag = true;												//初始化食物存在
}
//绘制游戏函数
void Game_Draw()
{
	cleardevice();
	//遍历蛇的身体，绘画每一个身体
	for (int i = 0; i < snake.num; i++)
	{
		//设置蛇身的填充颜色
		setfillcolor(snake.body[i].color);
		//将蛇身以矩形的方式绘画出来
		fillrectangle(snake.body[i].x, snake.body[i].y, snake.body[i].x + snake.size, snake.body[i].y + snake.size);
	}
	//如果食物存在，绘画食物
	if (food.flag)
	{	
		//设置食物的颜色
		setfillcolor(food.color);									
		//画食物，这个函数绘画的是一个圆，输入是左上和右下的坐标，圆在这个正方形里
		solidellipse(food.x, food.y, food.x + 10, food.y + 10);		
	}
	
	//绘制分数
	TCHAR temp[20];											//定义一个字符串，用来记录分数
	_stprintf_s(temp, _T("玩家分数：%d"), snake.score);		//将分数与固定字符拼接
	outtextxy(520, 13, temp);								//将文字绘制在游戏中
}
//让小蛇动起来
void Game_Move() 
{
	//从最后一个身体开始遍历
	for (int i = snake.num - 1; i > 0; i--)
	{
		//将后一个身体的坐标改为前一个身体，整体就向前运动起来了
		snake.body[i].x = snake.body[i - 1].x;
		snake.body[i].y = snake.body[i - 1].y;
	}
	//根据不同的方向移动蛇头的位置
	switch (snake.dir)
	{
	case UP:								//如果是向上
		snake.body[0].y -= snake.speed;		//蛇头的y坐标减去速度
		break;								//退出
	case DOWN:								//如果是向下
		snake.body[0].y += snake.speed;		//蛇头的y坐标加上速度
		break;								//退出
	case LEFT:								//如果是向左
		snake.body[0].x -= snake.speed;		//蛇头的x坐标减去速度
		break;								//退出
	case RIGHT:								//如果是向右
		snake.body[0].x += snake.speed;		//蛇头的x坐标加上速度
		break;								//退出
	default:
		break;
	}
}

//游戏判断
void Game_Judge()
{
	//如果蛇头的x，y坐标与食物的相同，则表示吃到食物了
	if (snake.body[0].x == food.x && snake.body[0].y == food.y)
	{
		food.x = rand() % (WIN_WIDTH / 10) * 10;						//重新绘制食物的x坐标
		food.y = rand() % (WIN_HEIGHT / 10) * 10;						//重新绘制食物的y坐标
		snake.num++;													//蛇的长度加一
		snake.body[snake.num - 1].x = snake.body[snake.num - 2].x;		//新增加的蛇的x坐标和之前最好一个身体的x坐标相同
		snake.body[snake.num - 1].y = snake.body[snake.num - 2].y;		//新增加的蛇的y坐标和之前最好一个身体的x坐标相同
		snake.score += 10;												//玩家分数加10
	}
	//判断蛇是否吃到自己，用来判断是否结束游戏
	for (int i = 1; i < snake.num; i++)									//遍历蛇的身体
	{
		//如果存在一个身体的与蛇头坐标一样，结束游戏
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
			running = false;											//设置running为false，结束while循环
	}
}

//游戏控制函数
void Game_Cotrol(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		switch (msg.vkcode)
		{
		case VK_UP:							//上箭头
			if (snake.dir != DOWN)			//如果此时小蛇的朝向不为下
				snake.dir = UP;				//则可以修改为朝上
			break;							//退出
		case VK_DOWN:						//下箭头
			if (snake.dir != UP)			//如果此时小蛇的朝向不为上
				snake.dir = DOWN;			//则可以修改为朝下
			break;							//退出
		case VK_LEFT:						//左箭头
			if (snake.dir != RIGHT)			//如果此时小蛇的朝向不为右
				snake.dir = LEFT;			//则可以修改为朝左
			break;							//退出
		case VK_RIGHT:						//右箭头
			if (snake.dir != LEFT)			//如果此时小蛇的朝向不为左
				snake.dir = RIGHT;			//则可以修改为朝右
			break;							//退出
		default:
			break;
		}
	}
}
//main主程序
int main() {
	//初始化一个长度为640高度为480的窗口
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	//设置窗口颜色		选择的是天蓝色的RGB
	setbkcolor(RGB(135, 206, 250));
	//这个函数使用当前背景色清空绘图设备
	cleardevice();
	//游戏初始化
	Game_Init();
	//定义双缓冲，用来解决闪烁问题(不用理解原理，先这样写就好)
	BeginBatchDraw();
	//主程序在while里一直循环
	while (running)
	{
		//不停调用绘画函数
		Game_Draw();
		//让小蛇动起来
		Game_Move();
		//按键控制
		while (peekmessage(&msg))
		{
			Game_Cotrol(msg);
		}
		//游戏判断
		Game_Judge();
		//执行未完成的绘制任务，与BeginBatchDraw函数对应
		FlushBatchDraw();
		//延时0.1s每1秒移动100的像素
		Sleep(100);
	}
	return 0;
}