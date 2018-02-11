#ifndef HUD_H
#define HUD_H

/* OpenGL */
#include <GL/glut.h>

/* Textures - Loading */
#include "../soil/soil.h"
#pragma comment(lib,"F:/BitBucket/pacman/Pacman/source/soil/lib/libSOIL.a")

/* Pacman - Objects */
#include "pacman.h"
#include "manager.h"

/* Pacman - Constants */
#include "../constants.h"

using namespace std;

#define LIFE 0
#define SCORE 1
#define LEVEL 2
#define TITLE 3
#define PACMAN 4

class Hud {

	private:	

		int _level;
		int _lives;
		int _score;

		int _textures[5];

		//Pacman *pacman;
		//Manager *manager;

	public:

		Hud();
		~Hud();

		void init();

		void update(Pacman *pacman, Manager *manager);
		void draw(int width, int height);

		void testing();

		int getScore();
		int getLives();

		void setScore(int score);
		void setLives(int lives);

		void message(std::string message, void * font, int x, int y);
};

#endif