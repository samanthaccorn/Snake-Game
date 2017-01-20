//Samantha Corn
//Final Project
//board.cpp

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include"board.h"
#include"gfxnew.h"
using namespace std;

Board::Board()
{
	srand(time(NULL));
	width = 30;
	height = 20;
	reset();
}

Board::Board(int w,int h)
{
	srand(time(NULL));
	width = w;
	height = h;
	reset();
}

Board::~Board() { }

void Board::reset()
{
	//Resets the board arrays to nothing. Places the snake in the middle of the board. 
	direction = 'S'; //Snake starts moving to the right
	gameOver = false;
	for (int i=0;i<width;i++) {
		for (int j=0;j<height;j++) {
			board[i][j] = 'b';	//'b' means blank
			snakeDirection[i][j] = ' ';
		}
	}
	int middlex = width/2;	//Snake's starting x
	int middley = width/2;	//Snake's starting y
	moves = 0;
	headx = middlex;
	heady = middley;
	tailx = middlex;
	taily = middley;
	board[middlex][middley] = 's';	//'s' means snake
	snakeDirection[middlex][middley] = direction;
	placeApple();
}

int Board::getWidth() { return width; }

int Board::getHeight() { return height; }

char Board::getBoardSpot(int x,int y) { return board[x][y]; }

int Board::getHeadX() { return headx; }

int Board::getHeadY() { return heady; }

int Board::getTailX() { return tailx; }

int Board::getTailY() { return taily; }

void Board::move(char uInput)
{
	//Takes the input of the user. Changes the direction if the input is relevent. Then places the snake.
	moves++;
	switch (uInput) {
		case 'T':
		case 'R':
		case 'S':
		case 'Q':
			setDirection(uInput);
			break;
	}

	placeSnake();
}

void Board::setDirection(char newD){ direction = newD; }

void Board::placeSnake()
{
	//Erases the current tail position and resets it. Places the head in the next spot according to the current direction.
	snakeDirection[headx][heady] = direction;
	
	switch (direction) {
		case 'R':	//Snake is moving up
			heady--;			
			break;
		case 'T':	//Snake is moving down
			heady++;
			break;
		case 'S':	//Snake is moving to the right
			headx++;
			break;
		case 'Q':	//Snake is moving to the left
			headx--;
			break;
	}

	//Checking to make sure the move is valid:
	if ((headx < 0)||(headx >= width)) {	//Snake has hit right or left wall
		gameOver = true;
	}

	if ((heady < 0)||(heady >= height)) { 	//Snake has hit the bottom or top wall
		gameOver = true;
	}

	if (board[headx][heady] == 's') {	//Snake crashed into itself
		gameOver = true;
	} else if (board[headx][heady] == 'a') {	//Snake ate the apple
		board[headx][heady] = 's';	
		placeApple();
	} else {
		board[headx][heady] = 's'; //Sets where the head goes next to a snake space
		char nextSnakeDir = snakeDirection[tailx][taily]; //Gets the direction of the next snake body piece

		board[tailx][taily] = 'b'; //Resets the last place the snake was to blank
		snakeDirection[tailx][taily] = ' '; //Resets the direction to nothing

		switch (nextSnakeDir) {
			case 'R':	//Above
				taily--;
				break;
			case 'T':	//Below
				taily++;
				break;
			case 'S':	//To the right
				tailx++;
				break;
			case 'Q':	//To the left
				tailx--;
				break;
		}
	}
}

void Board::placeApple()
{
	//Picks a random x or y until it finds one that the snake isn't occupying.
	int x = rand() % width;
	int y = rand() % width;
	while (board[x][y] == 's') {
		x = rand() % width;
		y = rand() % width;
	}
	board[x][y] = 'a';
}

bool Board::getGameOver() { return gameOver; }
