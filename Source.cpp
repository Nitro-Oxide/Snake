#include <iostream>
#include "raylib.h"
#include <string>
#include <list>
#include <algorithm>
struct position {
	int posX;
	int posY;
};



void Movement(int direction, Rectangle &HEAD);
int WinMain(){
	Rectangle head = { 1,1,10,10 };
	Rectangle point = { 300, 200, 10,10 };
	position headpos = { head.x,head.y };
	position* looker_of_head = &headpos;
	int score = 0;
	int collisions = 0;
	std::list<position> MoveHist;
	int direction, defDir = KEY_RIGHT;
	bool LoseState = false;
	InitWindow(600, 400, "Snake");
	while (!WindowShouldClose()) {
			ClearBackground(BLACK);
			BeginDrawing();
			SetTargetFPS(24);

			if (!LoseState) {
				DrawRectangleRec(head, BLUE);
				DrawRectangleRec(point, RED);
				//points to pick up
				if (CheckCollisionRecs(head, point)) {
					score++;
					point.x = GetRandomValue(10, 59) * 10;
					point.y = GetRandomValue(10, 39) * 10;
				}
				//Movement of Snake
				direction = GetKeyPressed();
				
				if (direction == 0) {
					direction = defDir;
				}
				else if(defDir == KEY_UP && direction == KEY_DOWN) {
					defDir == KEY_UP;
				} 
				else if (defDir == KEY_DOWN && direction == KEY_UP) {
					defDir == KEY_DOWN;
				}
				else if (defDir == KEY_RIGHT && direction == KEY_LEFT) {
					defDir == KEY_RIGHT;
				}
				else if (defDir == KEY_LEFT && direction == KEY_RIGHT) {
					defDir == KEY_LEFT;
				}
				else {
					defDir = direction;
				}


				Movement(defDir, head);
				headpos = { (int)head.x, (int)head.y };

				for (std::list<position>::iterator it = MoveHist.begin(); it != MoveHist.end(); it++) {
					DrawRectangle(it->posX, it->posY, 10, 10, BLUE);
					if (it->posX == headpos.posX && it->posY == headpos.posY) {
						LoseState = true;
					}

				}


				MoveHist.push_front(headpos);

				//body of snake

				if (MoveHist.size() > score) {
					MoveHist.pop_back();
				}

				for (std::list<position>::iterator it = MoveHist.begin(); it != MoveHist.end(); it++) {
					DrawRectangle(it->posX, it->posY, 10, 10, BLUE);

				}


				//loops to beginning
				if (head.y < 1) head.y = 400;
				if (head.y > 400) head.y = 0;
				if (head.x > 600) head.x = 0;
				if (head.x < 1) head.x = 600;

				//Debug Tools
				DrawText(TextFormat("Position: (%d,%d)", headpos.posX, headpos.posY), 200, 0, 10, WHITE);
			}
			else {
				DrawText("Game Over, Press R to try again", 50, 200, 25, WHITE);
				DrawText(TextFormat("Score :%d", score), 75, 250, 10, WHITE);
				direction = GetKeyPressed();
				if (direction == KEY_R) {
					LoseState = false;
					score = 0;
					MoveHist.clear();
					head.x = 1;
					head.y = 1;
					point.x = GetRandomValue(1, 60) * 10;
					point.y = GetRandomValue(1, 40) * 10;
				}
			}
			EndDrawing();
		}
		

	CloseWindow();
	std::cout << "score is " << score << std::endl;
	std::cout << "Final Position was " << headpos.posX << ',' << headpos.posY << std::endl;
	return 0;
}

void Movement(int direction, Rectangle &HEAD) {
	switch(direction) {
	case(KEY_UP):
		HEAD.y-= 10;
		break;
	case(KEY_DOWN):
		HEAD.y+=10;
		break;
	case(KEY_RIGHT):
		HEAD.x+=10;
		break;
	case(KEY_LEFT):
		HEAD.x-=10;
		break;


	};
}