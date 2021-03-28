#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

SceneID scene;
ObjectID start;
ObjectID p[9], original_board[9];
int blank = 8;

bool game = false;

TimerID timer;
int mixCount;


int indexTOx(int i) {
	return 100 + 100 * (i % 3);
}
int indexTOy(int i) {
	return 301 - 100 * (i / 3);
}

int game_index(ObjectID object) {
	for (int i = 0; i, 9; i++) {
		if (p[i] == object) return i;
	}
	return -1;
}

void game_move(int i) {
	ObjectID object = p[i];
	p[i] = p[blank];
	locateObject(p[i], scene, indexTOx(i), indexTOy(i));
	p[blank] = object;
	locateObject(p[blank], scene, indexTOx(blank), indexTOy(blank));
	blank = i; 
}

bool possible_move(int i) {
	if (i % 3 > 0 && blank == i - 1) return true;
	if (i % 3 < 2 && blank == i + 1) return true;
	if (i / 3 > 0 && blank == i - 3) return true;
	if (i / 3 < 2 && blank == i + 3) return true;
	
	return false;
}

int random_move() {
	int i = -1;
	while (i == -1) {
		switch (rand() % 4) {
		case 0:
			if (blank % 3 > 0) {
				i = blank - 1;
			}
			break;
		case 1:
			if (blank % 3 < 2) {
				i = blank + 1;
			}
			break;
		case 2:
			if (blank / 3 > 0) {
				i = blank - 3;
			}
			break;
		case 3:
			if (blank / 3 < 2) {
				i = blank + 3;
			}
			break;
		}
	}
	return i;
}

bool game_end() {
	for (int i = 0; i < 9; i++) {
		if (p[i] != original_board[i]) return false;

	}
	return true;
}

void game_start() {
	blank = 8;
	hideObject(p[blank]);
	

	mixCount = 50;
	setTimer(timer, 0.1f);
	startTimer(timer);
	
	
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (game) {
		int i = game_index(object);
		if (possible_move(i))
			game_move(i);

		if (game_end()) {
			game = false;
			showObject(start);
			showObject(p[blank]);
			showMessage("Completed!");
			}
	}
	else {
		if (object == start) {
			game_start();
		}
	}
}
ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown = true) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if (shown) showObject(object);

	return object;
}

void timerCallback(TimerID timer) {
	game_move(random_move());
	mixCount--;
	if (mixCount > 0) {
		setTimer(timer, 0.1f);
		startTimer(timer);

	}
	else {
		game = true;
		hideObject(start);
	}
	
}

SceneID game_init() {
	scene = createScene("퍼즐 맞추기", "0.png");

	char path[50];
	for (int i = 0; i < 9; i++) {
		sprintf(path, "0%d.png", i + 1);
		p[i] = createObject(path, scene, indexTOx(i), indexTOy(i));
		original_board[i] = p[i];
	}
	start = createObject("start.png", scene, 200, 20);
	
	timer = createTimer(0.1f);
	
	return scene;
}

int main() {
	
	srand(time(NULL));

	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	startGame(game_init());
}