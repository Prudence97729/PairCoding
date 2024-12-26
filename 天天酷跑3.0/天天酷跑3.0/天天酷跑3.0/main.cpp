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
* 添加gameover音乐
* 添加金币加分，爱心回血
* 更新背景图片
*/

//宏定义，便于维护和更改：
#define WIN_SCORE  100//判断胜利标志//之后可以结合按钮选择功能选择困难程度
#define WIN_WIDTH 1012
#define WIN_HEIGHT 396	
#define OBSTACLE_COUNT 12//宏定义障碍物池数量
#define Hard 2//用于提高难度
#define ROW 14
#define COL 14
void gamestart(int f);//声明函数，方便调用
void writeMaxScore();
void writeScore();
char user[64];
//int WIN_WIDTH = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
//int WIN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */
int flag = 1;//用于判断游戏结束
int F = 0;//方便切换人物音效
int prescore;//记录以来最高分
char grade[64];
IMAGE imgUI;//用户登录界面背景
IMAGE imgBgs[3];	//(全局数组)存放背景图片
IMAGE imgBgg;//第三个背景图片
int bgX[3];		//背景图片的x坐标
int bggx = 0;
int bgSpeed[3] = { 2, 3, 5 };		//三张图不同的速度
IMAGE imgHeros[12];		//存放角色奔跑图片
int heroX;	//角色的x坐标
int heroY;	//角色的y坐标
int heroIndex;	//角色奔跑的图片帧序号

bool heroJump;	//表示角色正在跳跃开关
int jumpHeighetMax;	//跳跃的最大值
int heroJumpOff;	//表示偏移量
int update;	//表示是否马上刷新画面

//	IMAGE imgTortoise[7];	//小乌龟
//	int torToiseX;	//小乌龟的水平坐标
//	int torToiseY;	//小乌龟的垂直坐标
//	bool torToiseExist;	//当前窗口是否存在小乌龟
//	int tortoiseIndex;//小乌龟旋转的图片帧序号

int heroBlood;	//玩家血量
int score;	//得分

//枚举封装障碍物的类型
typedef enum {
	TORTOISE,	//乌龟 0
	LION,	//狮子 1
	HOOK1,	//四个柱子障碍物
	HOOK2,
	HOOK3,
	HOOK4,
	FIRE1,//三个火焰障碍物
	FIRE2,
	FIRE3,
	COIN,
	LOVE,
	OBSTACLE_TYPE_CONST // 11 便于查看枚举数
}obstacle_type;

vector<vector<IMAGE>>obstacleImgs;//c++存放所用障碍物的各个图片
//相当于c中：IMAGE obstacleImgs[3][12]

//结构体封装障碍物
typedef struct obstacle {
	int type;	//障碍物的类型
	int imgIndex;	//当前显示图片的序号
	int x, y;	//障碍物坐标e
	int speed;	//障碍物速度
	int power;	//障碍物杀伤力
	bool exist;	//障碍物存在
	bool hited;	//表示是否已经发生碰撞
	bool passed;//表示是否被通过
	bool goodflag;//判断好坏
	bool r;//加血
}obstacle_t;

obstacle_t obstacles[OBSTACLE_COUNT];	//定义障碍物池
int lastObsIndex;	//记录上一次障碍物

IMAGE imgHeroDown[2];	//角色下蹲
bool heroDown;	//表示玩家正在下蹲开关

IMAGE imgSZ[10];//得分数字图片

int r[3][4] = { {30,20,130,60},{170,20,220,60},{260,20,310,60} };//三个按钮的二维数组

int button_judge(int x, int y)
{
	if (x > r[0][0] && x<r[0][2] && y>r[0][1] && y < r[0][3])return 1;
	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3])return 2;
	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3])return 3;
	return 0;
}
//初始化图像
void init_figure()
{
	int i;
	setrop2(R2_COPYPEN);//当前颜色
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID);//实线
	rectangle(30, 100, 420, 330);//外框线
	setlinestyle(PS_DOT);//点线
	for (i = 30 + 39; i < 420; i += 39)
	{
		line(i, 100, i, 330);//竖直辅助线
	}
	for (i = 100 + 23; i < 330; i += 23)
	{
		line(30, i, 420, i);//水平辅助线
	}
}

void button() {//实现人物选择功能
	int i, event = 0;
	char s[30];//输入字符串变量
	short win_width, win_height;//定义窗口的宽度和高度
	win_width = 1012; win_height = 396;
	initgraph(win_width, win_height);//初始化窗口（黑屏）
	for (i = 0; i < 256; i += 5)
	{
		setbkcolor(RGB(i, i, i));//设置背景色，原来默认黑色
		cleardevice();//清屏（取决于背景色）
		Sleep(30);//延时30ms
	}
	IMAGE button_bk;
	loadimage(0, "res/ui.jpg", 0, 0, true);	//加载结束图片，0表示加载到界面
	putimagePNG2(0, 0, &button_bk);
	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	LOGFONT f;//字体样式指针
	gettextstyle(&f);					//获取字体样式
	_tcscpy(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量
	drawtext("瓜哥", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext("小帅", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
	drawtext("小美", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R3内输入文字，水平居中，垂直居中，单行显示
	setlinecolor(BLACK);

	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	MOUSEMSG m;//鼠标指针

	while (true)
	{
		int flag = 0;//用于判断是否退出循环，控制游戏退出
		m = GetMouseMsg();//获取一条鼠标消息

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(WHITE);//填充颜色为白色
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(20);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}
			//按照按钮判断左键单击后的操作
			switch (button_judge(m.x, m.y))
			{
				//复原按钮原型
			case 1:
				gamestart(1);
				flag = 1;
				InputBox(s, 30, "请大侠留下姓名：");
				sscanf(s, "%s", user);//将输入字符串依次扫描到全局变量里面
				sprintf(grade, "       %d", score);
				writeMaxScore();

				//	system("pause");
				break;
			case 2:
				gamestart(2);
				flag = 1;
				InputBox(s, 30, "请大侠留下姓名：");
				sscanf(s, "%s", user);//将输入字符串依次扫描到全局变量里面
				
				sprintf(grade, "       %d", score);
				writeMaxScore();
				break;
			case 3:
				gamestart(3);
				flag = 1;
				InputBox(s, 30, "请大侠留下姓名：");
				sscanf(s, "%s", user);//将输入字符串依次扫描到全局变量里面
				
				sprintf(grade, "       %d", score);
				writeMaxScore();
				break;
			default:
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				//printf("\r\n(%d,%d)",m.x,m.y);//打印鼠标坐标，方便调试时确定区域
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
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* 获取窗口信息 */
	/* 设置窗口信息 最大化 取消标题栏及边框 */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}

//游戏初始化
void init(int f)

{

	initgraph(WIN_WIDTH, WIN_HEIGHT);	//创建游戏窗口

	//加载背景资源
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
		F = 1;//用于后面的音效处理
		//加载Hero奔跑的图片素材
		for (int i = 0; i < 12; i++) {
			//	"res/hero1.png"	...	"res/hero12.png"
			sprintf(name, "res/gua/hero%d.png", i + 1);
			loadimage(&imgHeros[i], name);
		}
		//加载下蹲素材
		loadimage(&imgHeroDown[0], "res/gua/d1.png");
		loadimage(&imgHeroDown[1], "res/gua/d2.png");
		heroDown = false;
	}
	else if (f == 2) {
		//加载Hero奔跑的图片素材
		for (int i = 0; i < 12; i++) {
			//	"res/hero1.png"	...	"res/hero12.png"
			sprintf(name, "res/bark/hero%d.png", i + 1);
			loadimage(&imgHeros[i], name);
		}
		//加载下蹲素材
		loadimage(&imgHeroDown[0], "res/herodown003.png");
		loadimage(&imgHeroDown[1], "res/herodown004.png");
		heroDown = false;
	}
	else if (f == 3) {
		//加载Hero奔跑的图片素材
		for (int i = 0; i < 12; i++) {
			//	"res/hero1.png"	...	"res/hero12.png"
			sprintf(name, "res/hero%d.png", i + 1);
			loadimage(&imgHeros[i], name);
		}
		//加载下蹲素材
		loadimage(&imgHeroDown[0], "res/d1.png");
		loadimage(&imgHeroDown[1], "res/d2.png");
		heroDown = false;
	}





	//设置角色的初始位置
	heroX = WIN_WIDTH * 0.5 - imgHeros[0].getwidth() * 0.5;
	heroY = 355 - imgHeros[0].getheight();
	heroIndex = 0;

	heroJump = false;
	jumpHeighetMax = 355 - imgHeros[0].getheight() - 120;
	heroJumpOff = -10;

	update = true;

	//用结构体加载小乌龟素材
	IMAGE imgTort;
	vector<IMAGE> imgTortArray;
	for (int i = 0; i < 7; i++) {
		//	"res/t1.png" ... "res/t7.png"
		sprintf(name, "res/t%d.png", i + 1);
		loadimage(&imgTort, name);
		imgTortArray.push_back(imgTort);	//存放到一维
	}
	obstacleImgs.push_back(imgTortArray);	//存放到二维

	//用结构体加载狮子素材
	IMAGE imgLion;
	vector<IMAGE> imgLionArray;
	for (int i = 0; i < 6; i++) {
		//	"res/p1.png" ... "res/p6.png"
		sprintf(name, "res/p%d.png", i + 1);
		loadimage(&imgLion, name);
		imgLionArray.push_back(imgLion);	//存放到一维
	}
	obstacleImgs.push_back(imgLionArray);	//存放到二维

	//初始化障碍物池
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		obstacles[i].exist = false;
	}



	//加载柱子素材
	IMAGE imgH;
	for (int i = 0; i < 4; i++) {
		vector<IMAGE> imgHookArray;
		sprintf(name, "res/h%d.png", i + 1);
		loadimage(&imgH, name, 63, 260, true);
		imgHookArray.push_back(imgH);
		obstacleImgs.push_back(imgHookArray);
	}
	//加载火焰素材
	IMAGE imgF;
	vector<IMAGE> imgFire;
	for (int i = 0; i < 3; i++) {
		sprintf(name, "res/fire%d.png", 1);
		loadimage(&imgF, name);
		imgFire.push_back(imgF);
		obstacleImgs.push_back(imgFire);
	}
	//加载金币																					
	IMAGE imgC;
	vector<IMAGE>imgCion;
	loadimage(&imgC, "res/coin.png");
	imgCion.push_back(imgC);
	obstacleImgs.push_back(imgCion);
	//加载爱心
	IMAGE imgL;
	vector<IMAGE>imgLove;
	loadimage(&imgL, "res/ai.png");
	imgLove.push_back(imgL);
	obstacleImgs.push_back(imgLove);

	//玩家血量
	heroBlood = 100;

	//预加载音效
	preLoadSound("res/hit.mp3");
	preLoadSound("res/res2/Assets/Resources/dead.mp3");
	preLoadSound("res/res2/Assets/Resources/jump.mp3");
	//播放背景音乐
	//if (F != 1)
		mciSendString("play res/bg.mp3 repeat", 0, 0, 0);

	lastObsIndex = -1;
	score = 0;

	//加载得分数字图片
	for (int i = 0; i < 10; i++) {
		sprintf(name, "res/sz/%d.png", i);
		loadimage(&imgSZ[i], name);
	}
}

//创建障碍物的各个参数
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

	//obstacles[i].type = (obstacle_type)(rand() % OBSTACLE_TYPE_CONST);	//使障碍物随机出现
	obstacles[i].type = (obstacle_type)((rand()) % 11);	//随机选择障碍物
	//obstacles[i].type = (obstacle_type)COIN;	//对3取余降低柱子出现概率
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
	//乌龟的数值
	if (obstacles[i].type == TORTOISE) {
		obstacles[i].speed = 4;	//乌龟速度值
		obstacles[i].power = 10;	//乌龟伤害值
	}

	else if (obstacles[i].type == COIN) {
		obstacles[i].speed = 0;
		obstacles[i].goodflag = true;
	}

	//狮子数值
	else if (obstacles[i].type == LION) {
		obstacles[i].speed = 8;	//狮子速度值
		obstacles[i].power = 20;	//狮子伤害值
	}
	else if (obstacles[i].type >= HOOK1 && obstacles[i].type <= HOOK4) {
		obstacles[i].speed = 0;		//柱子速度值
		obstacles[i].power = 50;	//柱子伤害值
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

//碰撞检测
void checkHit() {
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist && obstacles[i].hited == false) {
			int a1x, a1y, a2x, a2y;		//a1x,a1y为左上角坐标：a2x,a2y为右下角坐标
			int off = 30;	//偏移量
			//角色碰撞检测
			if (!heroDown) {	//非下蹲状态（奔跑，跳跃状态）
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

			//障碍物碰撞检测
			IMAGE img = obstacleImgs[obstacles[i].type][obstacles[i].imgIndex];
			int b1x = obstacles[i].x + off;
			int b1y = obstacles[i].y + off;
			int b2x = obstacles[i].x + img.getwidth() - off;
			int b2y = obstacles[i].y + img.getheight() - 10;


			//检测角色与障碍物是否相交
			if (rectIntersect(a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y)) {
				if (obstacles[i].goodflag == false) {
					heroBlood -= obstacles[i].power;	//玩家掉血、
					printf("血量剩余 %d\n", heroBlood);
					if (F != 1) {
						mciSendString("play res/hit.mp3", 0, 0, 0);
						//playSound("res/hit.mp3");	//碰撞声音

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
					mciSendString("play res/金币.mp3", 0, 0, 0);
					obstacles[i].hited = true;
				}
					

			}
		}
	}
}

//滚动效果
void go()
{
	for (int i = 0; i < 3; i++) {//背景图的移动
		bgX[i] -= bgSpeed[i];
		if (bgX[i] < -WIN_WIDTH) {
			bgX[i] = 0;		//循环实现
		}
	}

	//实现跳跃
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
	else if (heroDown) {	//实现下蹲
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
	else {	//不跳跃
		heroIndex = (heroIndex + 1) % 12;	//实现角色跑动效果
	}

	//出现障碍物
	static int frameCount = 0;
	static int enemyFre = 50;	//小乌龟出现频率
	frameCount++;
	if (frameCount > enemyFre) {		//25ms刷新一次，刷新一个障碍物
		frameCount = 0;
		enemyFre = 50 + rand() % 50;	//障碍物在50 ~ 99随机出现
		createObstacle();
	}
	//更新所有障碍物的坐标
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist) {
			obstacles[i].x -= obstacles[i].speed + bgSpeed[2];	//障碍物位移=障碍物位移-障碍物速度+背景速度
			if (obstacles[i].x < -obstacleImgs[obstacles[i].type][0].getwidth() * 2) {	//当障碍物移出窗口后消失
				obstacles[i].exist = false;
			}

			//实现障碍物动态效果
			int len = obstacleImgs[obstacles[i].type].size();	//取各个障碍物中的成员个数值
			obstacles[i].imgIndex = (obstacles[i].imgIndex + 1) % len;
		}
	}

	//	6.1 出现小乌龟
		//if (!torToiseExist) {
		//	torToiseExist = true;
		//	torToiseX = WIN_WIDTH;	//小乌龟从窗口宽度边缘出现
		//	enemyFre = 200 + rand() % 300;	//小乌龟在200 ~ 500（2s~5s）随机出现
		//}
	//	6.1 实现小乌龟水平移动
	//	if (torToiseExist) {
	//	tortoiseIndex = (tortoiseIndex + 1) % 7;	//实现乌龟旋转效果
	//	torToiseX -= bgSpeed[2];
	//	if (torToiseX < -imgTortoise[0].getwidth()) {	//当小乌龟移出窗口后消失
	//		torToiseExist = false;
	//	}
	//}

	//玩家和障碍物的“碰撞检测”处理
	checkHit();

}

//渲染游戏背景
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
	heroJump = true;	//打开跳跃开关
	update = true;
}

void down() {
	if (F == 1) {
		//playSound("res/ss3.mp3");
		mciSendString("play res/ss3.mp3", 0, 0, 0);	
	}

	heroDown = true;	//打开下蹲开关
	update = true;
	heroIndex = 0;
}

//处理用户输入的按键
void keyEvent()
{
	char ch;

	if (_kbhit()) {		//如果有按键按下，kbhit（）返回 ture
		ch = _getch();		//_getch不需要按回车即可直接读取
		if (ch == 'w') {
			jump();
		}
		else if (ch == 's') {	//按z下蹲
			down();
		}
	}
}

void updateEnemy() {
	//渲染所有障碍物
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist) {
			putimagePNG2(obstacles[i].x, obstacles[i].y, WIN_WIDTH,
				&obstacleImgs[obstacles[i].type][obstacles[i].imgIndex]);
		}
	}
}
//	6.1 渲染小乌龟
//	if (torToiseExist) {
//		putimagePNG2(torToiseX, torToiseY, WIN_WIDTH, &imgTortoise[tortoiseIndex]);
//	}

//更新跳跃和下蹲
void updateHero() {
	if (!heroDown) {
		putimagePNG2(heroX, heroY, &imgHeros[heroIndex]);
	}
	else {
		int y = 355 - imgHeroDown[heroIndex].getheight();
		putimagePNG2(heroX, y, &imgHeroDown[heroIndex]);
	}


}
//添加血条
void updateBloodBar() {
	drawBloodBar(10, 10, 200, 10, 2, BLUE, DARKGRAY, RED, heroBlood / 100.0);
}

//判断游戏结束
void checkOver() {
	if (heroBlood <= 0) {
		loadimage(0, "res/gameover.png", 0, 0, true);	//加载结束图片，0表示加载到界面
		playSound("res/res2/Assets/Resources/dead.mp3");	//游戏结束音效
		FlushBatchDraw();

		mciSendString("stop res/bg.mp3", 0, 0, 0);	//	 闭背景音乐
		system("pause");	//游戏暂停
		flag = 0;

		//暂停以后，直接开始下一局
		//heroBlood = 100;
		//score = 0;
		//mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	}
}

//添加初始界面
void checkStart() {
	loadimage(0, "res/bg1003.png");
	system("pause");
}

//越过障碍物自动得分机制+回血机制
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
			if (score > Hard) {  //得分超过Hard，加大游戏难度:增加速度和伤害值

				for (int i = 0; i < OBSTACLE_COUNT; i++) {
					obstacles[i].hited += 10;
				}
			}
		}
	}
}

//显示分数
void updateScore() {
	//实现方法：50 =>'50' '5'   '5'-'0'=5
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

//检测胜利
void checkWin() {
	if (score >= WIN_SCORE) {
		FlushBatchDraw();	//手动刷新胜利前最后一分
		mciSendString("play res/win.mp3", 0, 0, 0);
		Sleep(2000);
		loadimage(0, "res/win.png", 0, 0, true);//  ！原res图片库里没有
		FlushBatchDraw();	//刷新界面	
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
		timer += getDelay();	//返回距离上一次调用间隔的时间（单位：ms)，第一次调用时返回0
		if (timer > 25) {		//实现sleep25ms循环效果
			timer = 0;
			update = true;
		}

		if (update) {	//如果没到30ms触发按键，直接刷新
			update = false;
			BeginBatchDraw();	//双缓冲机制（防背景闪屏）
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
		//Sleep(25);	//导致休眠

	}


	system("pause");

}
void gotoxy(int x, int y)//形参
{
	HANDLE hOut;
	COORD pos = { x,y };
	// 光标的起始位（第1列，第3行） 0是第1列 2是第3行
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
	//printf("定位光标位置搜索(%d,%d)\n",pos.X,pos.Y);
}

void paintWindow()       //用户登录窗口
{
	int startX = 6;
	int startY = 5;
	int width = 20;
	int height = 20;
	int i = 0;
	//打印顶部   
	//光标定位 找规律 ┗  ┛ ┏ ┓ ┃ ━
	//顶部 y不变 x 在变 (x-x+w)
	gotoxy(startX, startY);
	printf("┏");
	for (i = 0; i < width - 2; i++)  //控制循环次数width-2次
	{
		printf("━ ");
	}
	printf("┓");
	//左边 x不变 y在变 (y到y+height)
	for (i = 1; i <= height - 2; i++)
	{
		gotoxy(startX, startY + i);
		printf("┃");
	}

	//右边 x不变 =startx+width-1  y在变 y 到 y+height
	for (i = 1; i <= height - 2; i++)
	{
		gotoxy(startX + width * 2 - 3, startY + i);
		printf("┃");
	}
	//底部 x在变化    y不变 （x到x+width） ━ 
	gotoxy(startX, startY + height - 1);
	printf("┗");
	for (i = 0; i < width - 2; i++)
	{
		printf("━ ");
	}
	printf("┛");

	gotoxy(startX, startX + height);
}

void login()     //用户登录界面
{
	full_screen();
	//loadimage(&imgBgs[i], name);//
	//loadimage(&imgUI, "res/ui.png");
	//putimagePNG2(0, 0, &imgUI);？不能同时加载图片，用户登录需改进
	char ch = 0;
	int i = 0;
	char name[9] = { 0 };//字符数组部分初始化
	char pwd[9] = { 0 };//字符数组部分初始化
	//绘制一个窗口
	paintWindow();
	//绘制标题 标签
	gotoxy(21, 9);
	printf("登录窗口");

	gotoxy(6 + 5, 12);
	printf("账号：");

	gotoxy(6 + 5, 16);
	printf("密码：");

	gotoxy(18, 12);//光标定位在用户名输入的位置
	//用户名的输入 存储
	while (1)
	{
		ch = getch();
		if (ch == '\r' && i == 0)  //任何内容都没输
		{
			continue;
		}
		if (ch == '\r' && i > 0 || i == 8)  //长度最多八位
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

	gotoxy(18, 16); //光标定位在密码输入的位置
	i = 0;//使用同一个计数器 需要重置
	//密码输入 存储
	while (1)
	{
		ch = getch();
		if (ch == '\r' && i == 0)  //任何内容都没输
		{
			continue;
		}
		if (ch == '\r' && i > 0 || i == 8)  //长度最多八位
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

	gotoxy(15, 18);  //显示登录成功 登录失败
	if (strcmp(name, "3group") == 0 && strcmp(pwd, "12345678") == 0 || strcmp(name, "123") == 0 && strcmp(pwd, "123") == 0 || strcmp(name, "user") == 0 && strcmp(pwd, "123456") == 0)
	{
		printf("登录成功\n");
		button();
	}
	else
	{
		printf("登录失败\n");
	}

	gotoxy(0, 27);

	//登录验证  admin 123456
}

//记录最高分
void writeMaxScore() {
	FILE* fp;
	char record[64] = "0";
	char record_user[64] = "无名氏";
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
	MessageBoxA(0, strcat(user, grade), "最终成绩", MB_SYSTEMMODAL);
	MessageBoxA(0,  strcat(record_user,record),"最高得分纪录", MB_SYSTEMMODAL);

	

}

int main() {
	srand((int)time(0));
	login();
	return 0;
}
