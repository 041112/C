//����ͼ��ͷ�ļ�
#include<graphics.h>
//C���Ա�׼�������ͷ�ļ�
#include<stdio.h>


//�궨�崰�ڳ���Ϊ640����
#define WIN_WIDTH	640
//�궨�崰�ڸ߶�Ϊ480����
#define WIN_HEIGHT	480
//�궨���ߵ���󳤶�Ϊ500
#define MAX_SNAKE	500

//��¼��Ϸ����״̬��Ĭ��Ϊ��
bool running = true;
//��¼������Ϣ�ṹ��
ExMessage msg;

//����������Ľṹ��
struct Position
{
	int x;			//���������X����
	int y;			//���������Y����
	DWORD color;	//�����������ɫ
};

//�洢�ߵ�������ݵĽṹ��
struct Snake
{
	int num;		//�����ߵĳ��ȵı���
	int dir;		//������ͷ�ĳ���ı���
	int score;		//������ҷ����ı���(ÿ��һ��ʳ���10��)
	int size;		//��������Ĵ�С����͸�
	int speed;		//���������ߵ��ٶ�
	struct Position body[MAX_SNAKE];		//�����߸������������
}snake;

//����ʳ��ṹ��
struct Food
{
	int x;			//ʳ���x����
	int y;			//ʳ���y����
	DWORD color;	//ʳ�����ɫ
	bool flag;		//ʳ���־�������Ƿ����
}food;

//ö�ٳ���ͷ����ĸ�������
enum DIRECTION
{
	UP,			//����
	DOWN,		//����
	LEFT,		//����
	RIGHT		//����
};
//��Ϸ��ʼ��
void Game_Init()
{
	srand(GetTickCount());			//�����������(�����Ҳû�أ�������д)
	snake.num = 3;					//��ʼ���ߵĳ���Ϊ3
	snake.dir = RIGHT;				//��ʼ���ߵĳ���Ϊ��
	snake.score = 0;				//��ʼ����ҷ���Ϊ0
	snake.size = 10;				//��ʼ���ߵĴ�СΪ10*10
	snake.speed = 10;				//��ʼ���ߵ��ٶ�Ϊ10
	snake.body[0].x = 20;			//��ʼ����ͷ��X����Ϊ20
	snake.body[0].y = 0;			//��ʼ����ͷ��Y����Ϊ0
	//��ʼ����ͷ����ɫ����ɫ��������Ƴ���ɫ��һ����
	snake.body[0].color = RGB(rand() % 256, rand() % 256, rand() % 256);

	snake.body[1].x = 10;			//��ʼ������1��X����Ϊ10
	snake.body[1].y = 0;			//��ʼ������1��Y����Ϊ0
	//��ʼ������1����ɫ����ɫ��������Ƴ���ɫ��һ����
	snake.body[1].color = RGB(rand() % 256, rand() % 256, rand() % 256);

	
	snake.body[2].x = 0;			//��ʼ������2��X����Ϊ0
	snake.body[2].y = 0;			//��ʼ������2��Y����Ϊ0
	//��ʼ������2����ɫ����ɫ��������Ƴ���ɫ��һ����
	snake.body[2].color = RGB(rand() % 256, rand() % 256, rand() % 256);

	//��ʼ��ʳ��
	food.x = rand() % (WIN_WIDTH / 10) * 10;						//ʳ���x���꣬ȷ���������ٶȵ�������
	food.y = rand() % (WIN_HEIGHT / 10) * 10;						//ʳ���y���꣬ȷ���������ٶȵ�������
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);		//����һ����ɫ
	food.flag = true;												//��ʼ��ʳ�����
}
//������Ϸ����
void Game_Draw()
{
	cleardevice();
	//�����ߵ����壬�滭ÿһ������
	for (int i = 0; i < snake.num; i++)
	{
		//��������������ɫ
		setfillcolor(snake.body[i].color);
		//�������Ծ��εķ�ʽ�滭����
		fillrectangle(snake.body[i].x, snake.body[i].y, snake.body[i].x + snake.size, snake.body[i].y + snake.size);
	}
	//���ʳ����ڣ��滭ʳ��
	if (food.flag)
	{	
		//����ʳ�����ɫ
		setfillcolor(food.color);									
		//��ʳ���������滭����һ��Բ�����������Ϻ����µ����꣬Բ�������������
		solidellipse(food.x, food.y, food.x + 10, food.y + 10);		
	}
	
	//���Ʒ���
	TCHAR temp[20];											//����һ���ַ�����������¼����
	_stprintf_s(temp, _T("��ҷ�����%d"), snake.score);		//��������̶��ַ�ƴ��
	outtextxy(520, 13, temp);								//�����ֻ�������Ϸ��
}
//��С�߶�����
void Game_Move() 
{
	//�����һ�����忪ʼ����
	for (int i = snake.num - 1; i > 0; i--)
	{
		//����һ������������Ϊǰһ�����壬�������ǰ�˶�������
		snake.body[i].x = snake.body[i - 1].x;
		snake.body[i].y = snake.body[i - 1].y;
	}
	//���ݲ�ͬ�ķ����ƶ���ͷ��λ��
	switch (snake.dir)
	{
	case UP:								//���������
		snake.body[0].y -= snake.speed;		//��ͷ��y�����ȥ�ٶ�
		break;								//�˳�
	case DOWN:								//���������
		snake.body[0].y += snake.speed;		//��ͷ��y��������ٶ�
		break;								//�˳�
	case LEFT:								//���������
		snake.body[0].x -= snake.speed;		//��ͷ��x�����ȥ�ٶ�
		break;								//�˳�
	case RIGHT:								//���������
		snake.body[0].x += snake.speed;		//��ͷ��x��������ٶ�
		break;								//�˳�
	default:
		break;
	}
}

//��Ϸ�ж�
void Game_Judge()
{
	//�����ͷ��x��y������ʳ�����ͬ�����ʾ�Ե�ʳ����
	if (snake.body[0].x == food.x && snake.body[0].y == food.y)
	{
		food.x = rand() % (WIN_WIDTH / 10) * 10;						//���»���ʳ���x����
		food.y = rand() % (WIN_HEIGHT / 10) * 10;						//���»���ʳ���y����
		snake.num++;													//�ߵĳ��ȼ�һ
		snake.body[snake.num - 1].x = snake.body[snake.num - 2].x;		//�����ӵ��ߵ�x�����֮ǰ���һ�������x������ͬ
		snake.body[snake.num - 1].y = snake.body[snake.num - 2].y;		//�����ӵ��ߵ�y�����֮ǰ���һ�������x������ͬ
		snake.score += 10;												//��ҷ�����10
	}
	//�ж����Ƿ�Ե��Լ��������ж��Ƿ������Ϸ
	for (int i = 1; i < snake.num; i++)									//�����ߵ�����
	{
		//�������һ�����������ͷ����һ����������Ϸ
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
			running = false;											//����runningΪfalse������whileѭ��
	}
}

//��Ϸ���ƺ���
void Game_Cotrol(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		switch (msg.vkcode)
		{
		case VK_UP:							//�ϼ�ͷ
			if (snake.dir != DOWN)			//�����ʱС�ߵĳ���Ϊ��
				snake.dir = UP;				//������޸�Ϊ����
			break;							//�˳�
		case VK_DOWN:						//�¼�ͷ
			if (snake.dir != UP)			//�����ʱС�ߵĳ���Ϊ��
				snake.dir = DOWN;			//������޸�Ϊ����
			break;							//�˳�
		case VK_LEFT:						//���ͷ
			if (snake.dir != RIGHT)			//�����ʱС�ߵĳ���Ϊ��
				snake.dir = LEFT;			//������޸�Ϊ����
			break;							//�˳�
		case VK_RIGHT:						//�Ҽ�ͷ
			if (snake.dir != LEFT)			//�����ʱС�ߵĳ���Ϊ��
				snake.dir = RIGHT;			//������޸�Ϊ����
			break;							//�˳�
		default:
			break;
		}
	}
}
//main������
int main() {
	//��ʼ��һ������Ϊ640�߶�Ϊ480�Ĵ���
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	//���ô�����ɫ		ѡ���������ɫ��RGB
	setbkcolor(RGB(135, 206, 250));
	//�������ʹ�õ�ǰ����ɫ��ջ�ͼ�豸
	cleardevice();
	//��Ϸ��ʼ��
	Game_Init();
	//����˫���壬���������˸����(�������ԭ��������д�ͺ�)
	BeginBatchDraw();
	//��������while��һֱѭ��
	while (running)
	{
		//��ͣ���û滭����
		Game_Draw();
		//��С�߶�����
		Game_Move();
		//��������
		while (peekmessage(&msg))
		{
			Game_Cotrol(msg);
		}
		//��Ϸ�ж�
		Game_Judge();
		//ִ��δ��ɵĻ���������BeginBatchDraw������Ӧ
		FlushBatchDraw();
		//��ʱ0.1sÿ1���ƶ�100������
		Sleep(100);
	}
	return 0;
}