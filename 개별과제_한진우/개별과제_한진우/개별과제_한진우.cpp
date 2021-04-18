#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <bangtal.h>
#include <stdlib.h>
TimerID timer1;
SoundID sound1 = createSound("클릭.mp3");
SoundID sound2 = createSound("박수.mp3");
SceneID scene0;
SceneID scene1;
SceneID scene2;
ObjectID start, restart, end;
ObjectID p[15], o[15], n[15], c[15];
//오브젝트의 좌표값을 배열로 정리
int px[15] = { 485, 545, 600, 685, 785, 870, 479, 720, 794, 879, 549, 670, 769, 844, 523};
int py[15] = { 495, 480, 490, 499, 495, 489, 335, 414, 410, 411, 349, 325, 327, 337, 428};
int ox[15] = {  30,  10, 180, 279, 299, 309, 349, 369,  70,  80, 429, 150, 120,  90, 210};
int oy[15] = { 472, 332, 462, 352, 203, 103, 263,  23,  83, 253, 213, 193, 163,  43, 242};
int nx[15] = {  33,  15, 191, 284, 309, 312, 353, 376,  76,  91, 436, 165, 128, 101, 218};
int ny[15] = { 481, 335, 468, 351, 205, 112, 263,  26,  89, 263, 213, 198, 172,  43, 243};
//bool 타입
bool check[15];
bool asd = false;
//mouseCallback함수 정의
void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	//start버튼 조건식
	if (object == start) enterScene(scene1);	
	//틀린 그림을 클릭했을때의 조건식
	for (int i = 0; i < 15; i++) {
		if ((check[i] == false) && object == n[i]) {
			//오브젝트 변화
			showObject(p[i]);
			showObject(o[i]);
			hideObject(n[i]);
			showObject(c[i]);
			//소리 입력
			playSound(sound1);
			//bool 타입 전환
			check[i] = true;
		}
	}
	//bool 타입  
	bool completed = true;
	//틀린 그림을 찾았을 때 bool 타입 전환
	for (int i = 0; i < 15; i++) {
		if (check[i] == false) {
			completed = false;
		}
	}
	//틀린 그림을 다 찾았을 때 조건식
	if (completed) {
		showMessage("축하합니다!!!");
		playSound(sound2);
		startTimer(timer1);
	}
}
//createObject 함수 정의
ObjectID createObject(const char* image, SceneID scene, int x, int y) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	return object;
}
//timer 함수 정의
void timerCallback(TimerID timer) {
	if (timer == timer1) {
		endGame();
	}
}
//int 함수
int main() {
	//게임 옵션 변경
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	//mouseCallback 함수 호출
	setMouseCallback(mouseCallback);
	//timerCallback 함수 호출
	setTimerCallback(timerCallback);
	//장면 생성
	scene0 = createScene("숨은그림찾기", "문제.png");
	scene1 = createScene("숨은그림찾기", "문제1.png");
	//오브젝트 생성, 위치시키는 함수
	char path[50];
	char fath[50];
	char dath[50];
	for (int i = 0; i < 15; i++) {
		sprintf(path, "0%d.png", i + 1);
		sprintf(fath, "%d-2.png", i + 1);
		sprintf(dath, "%d-1.png", i + 1);
		p[i] = createObject(path, scene1, px[i], py[i]);
		o[i] = createObject(fath, scene1, ox[i], oy[i]);
		n[i] = createObject(dath, scene1, nx[i], ny[i]);
		c[i] = createObject("check.png", scene1, px[i]+10, py[i]+10);
		showObject(n[i]);
		scaleObject(c[i], 0.5);
		start = createObject("start.png", scene0, 650, 100);
		showObject(start);	
	}
	timer1 = createTimer(3.0f);
	startGame(scene0);
}
