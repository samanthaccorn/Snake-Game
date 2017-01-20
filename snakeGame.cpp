//Samantha Corn
//Final Project
//snakeGame.cpp

#include<iostream>
#include<unistd.h>
#include"gfxnew.h"
#include"board.h"
using namespace std;

int main() {
	Board b;
	int headx,heady,tailx,taily,titlex,titley;

	bool gameOver = false,play = true,apple = false;
	int width = b.getWidth();
	int height = b.getHeight();
	char direction,c = ' ';

	gfx_open((width+2)*30,(height+2)*30,"Play Snake");
	gfx_clear();
	gfx_flush();

	titlex = (width+2)*30/2-75;
	titley = (height+2)*30/2-30;

	while (play) {
		gfx_color(255,255,255);
		gfx_text(titlex,titley,"Play Snake!");
		gfx_text(titlex,titley+15,"Press 'p' to play or 'q' to quit");

		while (c !='q') {
			c = gfx_wait();
			if (c == 'p') {
				gameOver = false;
				b.reset();
				break;
			}
		}
		if (c == 'q') {
			play = false;
			break;
		}

		gfx_clear();
		gfx_flush();

		//Drawing the walls:
		gfx_color(150,0,150); //purple
		gfx_fill_rectangle(0,0,(width+2)*30,30); //Top border
		gfx_fill_rectangle(0,0,30,(height+2)*30); //Left wall
		gfx_fill_rectangle((width+1)*30,0,30,(height+2)*30); //Right wall
		gfx_fill_rectangle(0,(height+1)*30,(width+2)*30,30); //Bottom Wall

		while (!gameOver) {
			apple = false;
			for (int i=0;i<width;i++) {
				for (int j=0;j<height;j++) {
					if (b.getBoardSpot(i,j) == 'a') {	//tile is an apple
						apple = true;
						gfx_color(255,0,0);	//red
						gfx_fill_rectangle(i*30+30,j*30+30,30,30);
					}
				}
			}

			if (apple == false) {
				b.placeApple();
			}

			direction = ' ';
			if (gfx_event_waiting()) {
				direction = gfx_wait();
				cout << direction << endl;
			}
			b.move(direction);

			headx = b.getHeadX();
			heady = b.getHeadY();
			tailx = b.getTailX();
			taily = b.getTailY();

			gfx_color(0,255,0); //Green
			gfx_fill_rectangle(headx*30+30,heady*30+30,30,30);
			gfx_color(0,0,0); //Black
			gfx_fill_rectangle(tailx*30+30,taily*30+30,30,30);
			gameOver = b.getGameOver();
			usleep(100000);
		}

		//On Game Over:
		gfx_clear();
		gfx_flush();
		gfx_color(255,255,255); //White
		gfx_text(titlex,titley,"Game Over!");
		gfx_text(titlex,titley+15,"Enter 'c' to continue");

		c = gfx_wait();

		while(c!='c') { c = gfx_wait(); }
		gfx_clear();
	}


	return 0;
}


