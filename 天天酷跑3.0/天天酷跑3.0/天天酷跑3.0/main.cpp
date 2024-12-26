#pragma once
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <vector>
#include "tools.h"
#include<time.h>
#include<windows.h>//gotoxy
#include<string.h>//strcmp
#include <math.h>
#include <string.h>

using namespace std;
/*
* ���gameover����
* ��ӽ�Ҽӷ֣����Ļ�Ѫ
* ���±���ͼƬ
*/

//�궨�壬����ά���͸��ģ�
#define WIN_SCORE  100//�ж�ʤ����־//֮����Խ�ϰ�ťѡ����ѡ�����ѳ̶�
#define WIN_WIDTH 1012
#define WIN_HEIGHT 396	
#define OBSTACLE_COUNT 12//�궨���ϰ��������
#define Hard 2//��������Ѷ�
#define ROW 14
#define COL 14
void gamestart(int f);//�����������������
void writeMaxScore();
void writeScore();
char user[64];
//int WIN_WIDTH = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
//int WIN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */
int flag = 1;//�����ж���Ϸ����
int F = 0;//�����л�������Ч
int prescore;//��¼������߷�
char grade[64];
IMAGE imgUI;//�û���¼���汳��
IMAGE imgBgs[3];	//(ȫ������)��ű���ͼƬ
IMAGE imgBgg;//����������ͼƬ
int bgX[3];		//����ͼƬ��x����
int bggx = 0;
int bgSpeed[3] = { 2, 3, 5 };		//����ͼ��ͬ���ٶ�
IMAGE imgHeros[12];		//��Ž�ɫ����ͼƬ
int heroX;	//��ɫ��x����
int heroY;	//��ɫ��y����
int heroIndex;	//��ɫ���ܵ�ͼƬ֡���

bool heroJump;	//��ʾ��ɫ������Ծ����
int jumpHeighetMax;	//��Ծ�����ֵ
int heroJumpOff;	//��ʾƫ����
int update;	//��ʾ�Ƿ�����ˢ�»���

//	IMAGE imgTortoise[7];	//С�ڹ�
//	int torToiseX;	//С�ڹ��ˮƽ����
//	int torToiseY;	//С�ڹ�Ĵ�ֱ����
//	bool torToiseExist;	//��ǰ�����Ƿ����С�ڹ�
//	int tortoiseIndex;//С�ڹ���ת��ͼƬ֡���

int heroBlood;	//���Ѫ��
int score;	//�÷�

//ö�ٷ�װ�ϰ��������
typedef enum {
	TORTOISE,	//�ڹ� 0
	LION,	//ʨ�� 1
	HOOK1,	//�ĸ������ϰ���
	HOOK2,
	HOOK3,
	HOOK4,
	FIRE1,//���������ϰ���
	FIRE2,
	FIRE3,
	COIN,
	LOVE,
	OBSTACLE_TYPE_CONST // 11 ���ڲ鿴ö����
}obstacle_type;

vector<vector<IMAGE>>obstacleImgs;//c++��������ϰ���ĸ���ͼƬ
//�൱��c�У�IMAGE obstacleImgs[3][12]

//�ṹ���װ�ϰ���
typedef struct obstacle {
	int type;	//�ϰ��������
	int imgIndex;	//��ǰ��ʾͼƬ�����
	int x, y;	//�ϰ�������e
	int speed;	//�ϰ����ٶ�
	int power;	//�ϰ���ɱ����
	bool exist;	//�ϰ������
	bool hited;	//��ʾ�Ƿ��Ѿ�������ײ
	bool passed;//��ʾ�Ƿ�ͨ��
	bool goodflag;//�жϺû�
	bool r;//��Ѫ
}obstacle_t;

obstacle_t obstacles[OBSTACLE_COUNT];	//�����ϰ����
int lastObsIndex;	//��¼��һ���ϰ���

IMAGE imgHeroDown[2];	//��ɫ�¶�
bool heroDown;	//��ʾ��������¶׿���

IMAGE imgSZ[10];//�÷�����ͼƬ

int r[3][4] = { {30,20,130,60},{170,20,220,60},{260,20,310,60} };//������ť�Ķ�ά����

int button_judge(int x, int y)
{
	if (x > r[0][0] && x<r[0][2] && y>r[0][1] && y < r[0][3])return 1;
	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3])return 2;
	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3])return 3;
	return 0;
}
//��ʼ��ͼ��
void init_figure()
{
	int i;
	setrop2(R2_COPYPEN);//��ǰ��ɫ
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID);//ʵ��
	rectangle(30, 100, 420, 330);//�����
	setlinestyle(PS_DOT);//����
	for (i = 30 + 39; i < 420; i += 39)
	{
		line(i, 100, i, 330);//��ֱ������
	}
	for (i = 100 + 23; i < 330; i += 23)
	{
		line(30, i, 420, i);//ˮƽ������
	}
}

void button() {//ʵ������ѡ����
	int i, event = 0;
	char s[30];//�����ַ�������
	short win_width, win_height;//���崰�ڵĿ�Ⱥ͸߶�
	win_width = 1012; win_height = 396;
	initgraph(win_width, win_height);//��ʼ�����ڣ�������
	for (i = 0; i < 256; i += 5)
	{
		setbkcolor(RGB(i, i, i));//���ñ���ɫ��ԭ��Ĭ�Ϻ�ɫ
		cleardevice();//������ȡ���ڱ���ɫ��
		Sleep(30);//��ʱ30ms
	}
	IMAGE button_bk;
	loadimage(0, "res/ui.jpg", 0, 0, true);	//���ؽ���ͼƬ��0��ʾ���ص�����
	putimagePNG2(0, 0, &button_bk);
	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	LOGFONT f;//������ʽָ��
	gettextstyle(&f);					//��ȡ������ʽ
	_tcscpy(f.lfFaceName, _T("����"));	//��������Ϊ����
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&f);                     // ����������ʽ
	settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
	drawtext("�ϸ�", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext("С˧", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R2���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext("С��", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R3���������֣�ˮƽ���У���ֱ���У�������ʾ
	setlinecolor(BLACK);

	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	MOUSEMSG m;//���ָ��

	while (true)
	{
		int flag = 0;//�����ж��Ƿ��˳�ѭ����������Ϸ�˳�
		m = GetMouseMsg();//��ȡһ�������Ϣ

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//������ɫΪ����ɫ
			setlinestyle(PS_SOLID, 3);//���û�����ʽΪʵ�֣�10��
			setfillcolor(WHITE);//�����ɫΪ��ɫ
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//��¼��һ�δ����İ�ť
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//�п������Σ�X1,Y1,X2,Y2��
				}
			}
			else
			{
				if (event != 0)//�ϴδ����İ�ťδ������Ϊԭ������ɫ
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//����ͬ��Ϊԭ����ɫ
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
				circle(m.x, m.y, 2 * i);
				Sleep(20);//ͣ��30ms
				circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
			}
			//���հ�ť�ж����������Ĳ���
			switch (button_judge(m.x, m.y))
			{
				//��ԭ��ťԭ��
			case 1:
				gamestart(1);
				flag = 1;
				InputBox(s, 30, "���������������");
				sscanf(s, "%s", user);//�������ַ�������ɨ�赽ȫ�ֱ�������
				sprintf(grade, "       %d", score);
				writeMaxScore();

				//	system("pause");
				break;
			case 2:
				gamestart(2);
				flag = 1;
				InputBox(s, 30, "���������������");
				sscanf(s, "%s", user);//�������ַ�������ɨ�赽ȫ�ֱ�������
				
				sprintf(grade, "       %d", score);
				writeMaxScore();
				break;
			case 3:
				gamestart(3);
				flag = 1;
				InputBox(s, 30, "���������������");
				sscanf(s, "%s", user);//�������ַ�������ɨ�赽ȫ�ֱ�������
				
				sprintf(grade, "       %d", score);
				writeMaxScore();
				break;
			default:
				FlushMouseMsgBuffer();//�����¼�����������Ϣ
				//printf("\r\n(%d,%d)",m.x,m.y);//��ӡ������꣬�������ʱȷ������
				break;
			}
			break;
		}
		if (flag == 1) {
			break;
		}

	}
}


void full_screen()
{
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* ��ȡ������Ϣ */
	/* ���ô�����Ϣ ��� ȡ�����������߿� */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}

//��Ϸ��ʼ��
void init(int f)

{

	initgraph(WIN_WIDTH, WIN_HEIGHT);	//������Ϸ����

	//���ر�����Դ
	char name[64];
	if (f != 1) {
		for (int i = 0; i < 2; i++) {
			//"res/bg001.png"   "res/bg002.png"   "res/bg003.png"   
			sprintf(name, "res/bg%03d.png", i + 1);
			loadimage(&imgBgs[i], name);
			bgX[i] = 0;
		}
		loadimage(&imgBgs[2], "res/bgg0004.png");
	}
	else {
		for (int i = 0; i < 3; i++) {
			//"res/bg001.png"   "res/bg002.png"   "res/bg003.png"   
			sprintf(name, "res/bg%03d.png", i + 1);
			loadimage(&imgBgs[i], name);
			bgX[i] = 0;
		}
	}



	if (f == 1) {
		F = 1;//���ں������Ч����
		//����Hero���ܵ�ͼƬ�ز�
		for (int i = 0; i < 12; i++) {
			//	"res/hero1.png"	...	"res/hero12.png"
			sprintf(name, "res/gua/hero%d.png", i + 1);
			loadimage(&imgHeros[i], name);
		}
		//�����¶��ز�
		loadimage(&imgHeroDown[0], "res/gua/d1.png");
		loadimage(&imgHeroDown[1], "res/gua/d2.png");
		heroDown = false;
	}
	else if (f == 2) {
		//����Hero���ܵ�ͼƬ�ز�
		for (int i = 0; i < 12; i++) {
			//	"res/hero1.png"	...	"res/hero12.png"
			sprintf(name, "res/bark/hero%d.png", i + 1);
			loadimage(&imgHeros[i], name);
		}
		//�����¶��ز�
		loadimage(&imgHeroDown[0], "res/herodown003.png");
		loadimage(&imgHeroDown[1], "res/herodown004.png");
		heroDown = false;
	}
	else if (f == 3) {
		//����Hero���ܵ�ͼƬ�ز�
		for (int i = 0; i < 12; i++) {
			//	"res/hero1.png"	...	"res/hero12.png"
			sprintf(name, "res/hero%d.png", i + 1);
			loadimage(&imgHeros[i], name);
		}
		//�����¶��ز�
		loadimage(&imgHeroDown[0], "res/d1.png");
		loadimage(&imgHeroDown[1], "res/d2.png");
		heroDown = false;
	}





	//���ý�ɫ�ĳ�ʼλ��
	heroX = WIN_WIDTH * 0.5 - imgHeros[0].getwidth() * 0.5;
	heroY = 355 - imgHeros[0].getheight();
	heroIndex = 0;

	heroJump = false;
	jumpHeighetMax = 355 - imgHeros[0].getheight() - 120;
	heroJumpOff = -10;

	update = true;

	//�ýṹ�����С�ڹ��ز�
	IMAGE imgTort;
	vector<IMAGE> imgTortArray;
	for (int i = 0; i < 7; i++) {
		//	"res/t1.png" ... "res/t7.png"
		sprintf(name, "res/t%d.png", i + 1);
		loadimage(&imgTort, name);
		imgTortArray.push_back(imgTort);	//��ŵ�һά
	}
	obstacleImgs.push_back(imgTortArray);	//��ŵ���ά

	//�ýṹ�����ʨ���ز�
	IMAGE imgLion;
	vector<IMAGE> imgLionArray;
	for (int i = 0; i < 6; i++) {
		//	"res/p1.png" ... "res/p6.png"
		sprintf(name, "res/p%d.png", i + 1);
		loadimage(&imgLion, name);
		imgLionArray.push_back(imgLion);	//��ŵ�һά
	}
	obstacleImgs.push_back(imgLionArray);	//��ŵ���ά

	//��ʼ���ϰ����
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		obstacles[i].exist = false;
	}



	//���������ز�
	IMAGE imgH;
	for (int i = 0; i < 4; i++) {
		vector<IMAGE> imgHookArray;
		sprintf(name, "res/h%d.png", i + 1);
		loadimage(&imgH, name, 63, 260, true);
		imgHookArray.push_back(imgH);
		obstacleImgs.push_back(imgHookArray);
	}
	//���ػ����ز�
	IMAGE imgF;
	vector<IMAGE> imgFire;
	for (int i = 0; i < 3; i++) {
		sprintf(name, "res/fire%d.png", 1);
		loadimage(&imgF, name);
		imgFire.push_back(imgF);
		obstacleImgs.push_back(imgFire);
	}
	//���ؽ��																					
	IMAGE imgC;
	vector<IMAGE>imgCion;
	loadimage(&imgC, "res/coin.png");
	imgCion.push_back(imgC);
	obstacleImgs.push_back(imgCion);
	//���ذ���
	IMAGE imgL;
	vector<IMAGE>imgLove;
	loadimage(&imgL, "res/ai.png");
	imgLove.push_back(imgL);
	obstacleImgs.push_back(imgLove);

	//���Ѫ��
	heroBlood = 100;

	//Ԥ������Ч
	preLoadSound("res/hit.mp3");
	preLoadSound("res/res2/Assets/Resources/dead.mp3");
	preLoadSound("res/res2/Assets/Resources/jump.mp3");
	//���ű�������
	//if (F != 1)
		mciSendString("play res/bg.mp3 repeat", 0, 0, 0);

	lastObsIndex = -1;
	score = 0;

	//���ص÷�����ͼƬ
	for (int i = 0; i < 10; i++) {
		sprintf(name, "res/sz/%d.png", i);
		loadimage(&imgSZ[i], name);
	}
}

//�����ϰ���ĸ�������
void createObstacle() {
	int i;
	for (i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist == false) {
			break;
		}
	}
	if (i >= OBSTACLE_COUNT) {
		return;
	}

	obstacles[i].exist = true;
	obstacles[i].hited = false;
	obstacles[i].goodflag = false;
	obstacles[i].imgIndex = 0;

	//obstacles[i].type = (obstacle_type)(rand() % OBSTACLE_TYPE_CONST);	//ʹ�ϰ����������
	obstacles[i].type = (obstacle_type)((rand()) % 11);	//���ѡ���ϰ���
	//obstacles[i].type = (obstacle_type)COIN;	//��3ȡ�ཱུ�����ӳ��ָ���
	if (lastObsIndex >= 0 &&
		obstacles[lastObsIndex].type >= HOOK1 &&
		obstacles[lastObsIndex].type <= HOOK4 &&
		obstacles[i].type == LION &&
		obstacles[lastObsIndex].x > (WIN_WIDTH - 500)) {
		int f = (int)rand() % 3;
		if (f == 1)
			obstacles[i].type = COIN;
		else if (f == 2) obstacles[i].type = TORTOISE;
		else obstacles[i].type = LOVE;
	}
	lastObsIndex = i;

	//if (obstacles[i].type >= HOOK1&&obstacles[i].type<=HOOK4) {
	//	obstacles[i].type += rand() % 4;	//0...3
	//}


	obstacles[i].x = WIN_WIDTH;
	obstacles[i].y = 355 - obstacleImgs[obstacles[i].type][0].getheight();
	//�ڹ����ֵ
	if (obstacles[i].type == TORTOISE) {
		obstacles[i].speed = 4;	//�ڹ��ٶ�ֵ
		obstacles[i].power = 10;	//�ڹ��˺�ֵ
	}

	else if (obstacles[i].type == COIN) {
		obstacles[i].speed = 0;
		obstacles[i].goodflag = true;
	}

	//ʨ����ֵ
	else if (obstacles[i].type == LION) {
		obstacles[i].speed = 8;	//ʨ���ٶ�ֵ
		obstacles[i].power = 20;	//ʨ���˺�ֵ
	}
	else if (obstacles[i].type >= HOOK1 && obstacles[i].type <= HOOK4) {
		obstacles[i].speed = 0;		//�����ٶ�ֵ
		obstacles[i].power = 50;	//�����˺�ֵ
		obstacles[i].y = 40;
	}
	else if (obstacles[i].type == FIRE2) {
		obstacles[i].speed = 0;
		obstacles[i].power = 10;
	}
	else if (obstacles[i].type == LOVE) {
		obstacles[i].speed = 0;
		obstacles[i].goodflag = true;
		obstacles[i].r = true;
	}


	obstacles[i].passed = false;
}

//��ײ���
void checkHit() {
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist && obstacles[i].hited == false) {
			int a1x, a1y, a2x, a2y;		//a1x,a1yΪ���Ͻ����꣺a2x,a2yΪ���½�����
			int off = 30;	//ƫ����
			//��ɫ��ײ���
			if (!heroDown) {	//���¶�״̬�����ܣ���Ծ״̬��
				a1x = heroX + off;
				a1y = heroY + off;
				a2x = heroX + imgHeros[heroIndex].getwidth() - off;
				a2y = heroY + imgHeros[heroIndex].getheight();
			}
			else {
				a1x = heroX + off;
				a1y = 385 - imgHeroDown[heroIndex].getheight();
				a2x = heroX + imgHeroDown[heroIndex].getwidth() - off;
				a2y = 385;
			}

			//�ϰ�����ײ���
			IMAGE img = obstacleImgs[obstacles[i].type][obstacles[i].imgIndex];
			int b1x = obstacles[i].x + off;
			int b1y = obstacles[i].y + off;
			int b2x = obstacles[i].x + img.getwidth() - off;
			int b2y = obstacles[i].y + img.getheight() - 10;


			//����ɫ���ϰ����Ƿ��ཻ
			if (rectIntersect(a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y)) {
				if (obstacles[i].goodflag == false) {
					heroBlood -= obstacles[i].power;	//��ҵ�Ѫ��
					printf("Ѫ��ʣ�� %d\n", heroBlood);
					if (F != 1) {
						mciSendString("play res/hit.mp3", 0, 0, 0);
						//playSound("res/hit.mp3");	//��ײ����

					}
					else {
						int music_rand = (int)(rand() % 2);
						if (music_rand == 0) {
							//playSound("res/ss1.mp3");
							mciSendString("play res/ss1.mp3", 0, 0, 0);
						}
						else if (music_rand == 1) {
							//playSound("res/srl2.mp3");
							mciSendString("play res/srl2.mp3", 0, 0, 0);
						}



					}
					obstacles[i].hited = true;
				}
			
				else {
					mciSendString("play res/���.mp3", 0, 0, 0);
					obstacles[i].hited = true;
				}
					

			}
		}
	}
}

//����Ч��
void go()
{
	for (int i = 0; i < 3; i++) {//����ͼ���ƶ�
		bgX[i] -= bgSpeed[i];
		if (bgX[i] < -WIN_WIDTH) {
			bgX[i] = 0;		//ѭ��ʵ��
		}
	}

	//ʵ����Ծ
	if (heroJump) {

		if (heroY < jumpHeighetMax) {
			heroJumpOff = 10;
		}

		heroY += heroJumpOff;

		if (heroY > 355 - imgHeros[0].getheight()) {
			heroJump = false;
			heroJumpOff = -10;
		}
	}
	else if (heroDown) {	//ʵ���¶�
		static int count = 0;
		int delays[2] = { 4,16 };
		count++;
		if (count >= delays[heroIndex]) {
			count = 0;
			heroIndex++;
			if (heroIndex >= 2) {
				heroIndex = 0;
				heroDown = false;
			}
		}
	}
	else {	//����Ծ
		heroIndex = (heroIndex + 1) % 12;	//ʵ�ֽ�ɫ�ܶ�Ч��
	}

	//�����ϰ���
	static int frameCount = 0;
	static int enemyFre = 50;	//С�ڹ����Ƶ��
	frameCount++;
	if (frameCount > enemyFre) {		//25msˢ��һ�Σ�ˢ��һ���ϰ���
		frameCount = 0;
		enemyFre = 50 + rand() % 50;	//�ϰ�����50 ~ 99�������
		createObstacle();
	}
	//���������ϰ��������
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist) {
			obstacles[i].x -= obstacles[i].speed + bgSpeed[2];	//�ϰ���λ��=�ϰ���λ��-�ϰ����ٶ�+�����ٶ�
			if (obstacles[i].x < -obstacleImgs[obstacles[i].type][0].getwidth() * 2) {	//���ϰ����Ƴ����ں���ʧ
				obstacles[i].exist = false;
			}

			//ʵ���ϰ��ﶯ̬Ч��
			int len = obstacleImgs[obstacles[i].type].size();	//ȡ�����ϰ����еĳ�Ա����ֵ
			obstacles[i].imgIndex = (obstacles[i].imgIndex + 1) % len;
		}
	}

	//	6.1 ����С�ڹ�
		//if (!torToiseExist) {
		//	torToiseExist = true;
		//	torToiseX = WIN_WIDTH;	//С�ڹ�Ӵ��ڿ�ȱ�Ե����
		//	enemyFre = 200 + rand() % 300;	//С�ڹ���200 ~ 500��2s~5s���������
		//}
	//	6.1 ʵ��С�ڹ�ˮƽ�ƶ�
	//	if (torToiseExist) {
	//	tortoiseIndex = (tortoiseIndex + 1) % 7;	//ʵ���ڹ���תЧ��
	//	torToiseX -= bgSpeed[2];
	//	if (torToiseX < -imgTortoise[0].getwidth()) {	//��С�ڹ��Ƴ����ں���ʧ
	//		torToiseExist = false;
	//	}
	//}

	//��Һ��ϰ���ġ���ײ��⡱����
	checkHit();

}

//��Ⱦ��Ϸ����
void updateBg()
{
	putimagePNG2(bgX[0], 0, &imgBgs[0]);
	putimagePNG2(bgX[1], 119, &imgBgs[1]);
	putimagePNG2(bgX[2], 330, &imgBgs[2]);
	putimagePNG2(bggx, 330, &imgBgg);
}

void jump() {
	//playSound("res/res2/Assets/Resources/jump.mp3");
	mciSendString("play res/res2/Assets/Resources/jump.mp3", 0, 0, 0);	
	heroJump = true;	//����Ծ����
	update = true;
}

void down() {
	if (F == 1) {
		//playSound("res/ss3.mp3");
		mciSendString("play res/ss3.mp3", 0, 0, 0);	
	}

	heroDown = true;	//���¶׿���
	update = true;
	heroIndex = 0;
}

//�����û�����İ���
void keyEvent()
{
	char ch;

	if (_kbhit()) {		//����а������£�kbhit�������� ture
		ch = _getch();		//_getch����Ҫ���س�����ֱ�Ӷ�ȡ
		if (ch == 'w') {
			jump();
		}
		else if (ch == 's') {	//��z�¶�
			down();
		}
	}
}

void updateEnemy() {
	//��Ⱦ�����ϰ���
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist) {
			putimagePNG2(obstacles[i].x, obstacles[i].y, WIN_WIDTH,
				&obstacleImgs[obstacles[i].type][obstacles[i].imgIndex]);
		}
	}
}
//	6.1 ��ȾС�ڹ�
//	if (torToiseExist) {
//		putimagePNG2(torToiseX, torToiseY, WIN_WIDTH, &imgTortoise[tortoiseIndex]);
//	}

//������Ծ���¶�
void updateHero() {
	if (!heroDown) {
		putimagePNG2(heroX, heroY, &imgHeros[heroIndex]);
	}
	else {
		int y = 355 - imgHeroDown[heroIndex].getheight();
		putimagePNG2(heroX, y, &imgHeroDown[heroIndex]);
	}


}
//���Ѫ��
void updateBloodBar() {
	drawBloodBar(10, 10, 200, 10, 2, BLUE, DARKGRAY, RED, heroBlood / 100.0);
}

//�ж���Ϸ����
void checkOver() {
	if (heroBlood <= 0) {
		loadimage(0, "res/gameover.png", 0, 0, true);	//���ؽ���ͼƬ��0��ʾ���ص�����
		playSound("res/res2/Assets/Resources/dead.mp3");	//��Ϸ������Ч
		FlushBatchDraw();

		mciSendString("stop res/bg.mp3", 0, 0, 0);	//	 �ձ�������
		system("pause");	//��Ϸ��ͣ
		flag = 0;

		//��ͣ�Ժ�ֱ�ӿ�ʼ��һ��
		//heroBlood = 100;
		//score = 0;
		//mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	}
}

//��ӳ�ʼ����
void checkStart() {
	loadimage(0, "res/bg1003.png");
	system("pause");
}

//Խ���ϰ����Զ��÷ֻ���+��Ѫ����
void checkScore() {
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].x + obstacleImgs[obstacles[i].type][0].getwidth() < heroX&&obstacles[i].passed == false && obstacles[i].exist && obstacles[i].goodflag == true && obstacles[i].hited == true) {
			score++;
			obstacles[i].exist = false;
			obstacles[i].x = 0;
			if (obstacles[i].r == true) {
				heroBlood += 30;
				obstacles[i].x = 0;
				obstacles[i].exist = false;

			}
		}
		if (obstacles[i].exist &&
			obstacles[i].passed == false &&
			obstacles[i].hited == false &&
			obstacles[i].x + obstacleImgs[obstacles[i].type][0].getwidth() < heroX) {
			score++;
			obstacles[i].passed = true;
			printf("score: %d\n", score);
			if (score > Hard) {  //�÷ֳ���Hard���Ӵ���Ϸ�Ѷ�:�����ٶȺ��˺�ֵ

				for (int i = 0; i < OBSTACLE_COUNT; i++) {
					obstacles[i].hited += 10;
				}
			}
		}
	}
}

//��ʾ����
void updateScore() {
	//ʵ�ַ�����50 =>'50' '5'   '5'-'0'=5
	char str[8];
	sprintf(str, "%d", score);

	int x = 20;
	int y = 25;

	for (int i = 0; str[i]; i++) {
		int sz = str[i] - '0';
		putimagePNG(x, y, &imgSZ[sz]);
		x += imgSZ[sz].getwidth() + 5;
	}
}

//���ʤ��
void checkWin() {
	if (score >= WIN_SCORE) {
		FlushBatchDraw();	//�ֶ�ˢ��ʤ��ǰ���һ��
		mciSendString("play res/win.mp3", 0, 0, 0);
		Sleep(2000);
		loadimage(0, "res/win.png", 0, 0, true);//  ��ԭresͼƬ����û��
		FlushBatchDraw();	//ˢ�½���	
		mciSendString("stop res/bg.mp3", 0, 0, 0);
		system("pause");

		heroBlood = 100;
		//score = 0;
		mciSendString("play res/bg.mp3", 0, 0, 0);
		flag = 0;
	}
}

void gamestart(int f) {

	init(f);
	checkStart();

	int timer = 0;
	while (1) {
		keyEvent();
		timer += getDelay();	//���ؾ�����һ�ε��ü����ʱ�䣨��λ��ms)����һ�ε���ʱ����0
		if (timer > 25) {		//ʵ��sleep25msѭ��Ч��
			timer = 0;
			update = true;
		}

		if (update) {	//���û��30ms����������ֱ��ˢ��
			update = false;
			BeginBatchDraw();	//˫������ƣ�������������
			updateBg();
			//putimagePNG2(heroX, heroY, &imgHeros[heroIndex]);
			updateHero();
			updateEnemy();
			updateBloodBar();
			updateScore();
			checkWin();
			EndBatchDraw();

			checkOver();
			checkScore();
			go();
			if (flag == 0) {
				return;
			}
		}
		//Sleep(25);	//��������

	}


	system("pause");

}
void gotoxy(int x, int y)//�β�
{
	HANDLE hOut;
	COORD pos = { x,y };
	// ������ʼλ����1�У���3�У� 0�ǵ�1�� 2�ǵ�3��
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
	//printf("��λ���λ������(%d,%d)\n",pos.X,pos.Y);
}

void paintWindow()       //�û���¼����
{
	int startX = 6;
	int startY = 5;
	int width = 20;
	int height = 20;
	int i = 0;
	//��ӡ����   
	//��궨λ �ҹ��� ��  �� �� �� �� ��
	//���� y���� x �ڱ� (x-x+w)
	gotoxy(startX, startY);
	printf("��");
	for (i = 0; i < width - 2; i++)  //����ѭ������width-2��
	{
		printf("�� ");
	}
	printf("��");
	//��� x���� y�ڱ� (y��y+height)
	for (i = 1; i <= height - 2; i++)
	{
		gotoxy(startX, startY + i);
		printf("��");
	}

	//�ұ� x���� =startx+width-1  y�ڱ� y �� y+height
	for (i = 1; i <= height - 2; i++)
	{
		gotoxy(startX + width * 2 - 3, startY + i);
		printf("��");
	}
	//�ײ� x�ڱ仯    y���� ��x��x+width�� �� 
	gotoxy(startX, startY + height - 1);
	printf("��");
	for (i = 0; i < width - 2; i++)
	{
		printf("�� ");
	}
	printf("��");

	gotoxy(startX, startX + height);
}

void login()     //�û���¼����
{
	full_screen();
	//loadimage(&imgBgs[i], name);//
	//loadimage(&imgUI, "res/ui.png");
	//putimagePNG2(0, 0, &imgUI);������ͬʱ����ͼƬ���û���¼��Ľ�
	char ch = 0;
	int i = 0;
	char name[9] = { 0 };//�ַ����鲿�ֳ�ʼ��
	char pwd[9] = { 0 };//�ַ����鲿�ֳ�ʼ��
	//����һ������
	paintWindow();
	//���Ʊ��� ��ǩ
	gotoxy(21, 9);
	printf("��¼����");

	gotoxy(6 + 5, 12);
	printf("�˺ţ�");

	gotoxy(6 + 5, 16);
	printf("���룺");

	gotoxy(18, 12);//��궨λ���û��������λ��
	//�û��������� �洢
	while (1)
	{
		ch = getch();
		if (ch == '\r' && i == 0)  //�κ����ݶ�û��
		{
			continue;
		}
		if (ch == '\r' && i > 0 || i == 8)  //��������λ
		{
			break;
		}
		if (ch == '\b') {
			printf("\b");
			printf(" ");
			printf("\b");
			i--;
			name[i] = '\0';
		}
		if (ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
		{
			putch(ch);
			name[i] = ch;
			++i;

		}
	}

	gotoxy(18, 16); //��궨λ�����������λ��
	i = 0;//ʹ��ͬһ�������� ��Ҫ����
	//�������� �洢
	while (1)
	{
		ch = getch();
		if (ch == '\r' && i == 0)  //�κ����ݶ�û��
		{
			continue;
		}
		if (ch == '\r' && i > 0 || i == 8)  //��������λ
		{
			break;
		}
		if (ch == '\b') {
			printf("\b");
			printf(" ");
			printf("\b");
			i--;
			pwd[i] = '\0';
		}
		if (ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
		{
			putch('*');
			pwd[i] = ch;
			++i;
		}
	}

	gotoxy(15, 18);  //��ʾ��¼�ɹ� ��¼ʧ��
	if (strcmp(name, "3group") == 0 && strcmp(pwd, "12345678") == 0 || strcmp(name, "123") == 0 && strcmp(pwd, "123") == 0 || strcmp(name, "user") == 0 && strcmp(pwd, "123456") == 0)
	{
		printf("��¼�ɹ�\n");
		button();
	}
	else
	{
		printf("��¼ʧ��\n");
	}

	gotoxy(0, 27);

	//��¼��֤  admin 123456
}

//��¼��߷�
void writeMaxScore() {
	FILE* fp;
	char record[64] = "0";
	char record_user[64] = "������";
	fp = fopen("record/MaxScore.txt", "r");
	if (fp == NULL) {
		fp = fopen("record/MaxScore.txt", "w");
		fprintf(fp, "%s %d",user,score);
	}
	else {
		fscanf(fp, "%s %d",record_user,&prescore);
		if (prescore <= score) {
			fp = fopen("record/MaxScore.txt", "w");
			prescore = score;
			sprintf(record, "       %d", prescore);
			fprintf(fp, "%s %d",user,score);
			strcpy(record_user, user);

		}
		else {
			sprintf(record, "       %d", prescore);
		}
	}
	fclose(fp);
	MessageBoxA(0, strcat(user, grade), "���ճɼ�", MB_SYSTEMMODAL);
	MessageBoxA(0,  strcat(record_user,record),"��ߵ÷ּ�¼", MB_SYSTEMMODAL);

	

}

int main() {
	srand((int)time(0));
	login();
	return 0;
}
