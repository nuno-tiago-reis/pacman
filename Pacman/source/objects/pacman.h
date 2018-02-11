#ifndef PACMAN_H
#define PACMAN_H

/* Pacman - Objects */
#include "object.h"

using namespace std;

class Pacman: public Object {

	private:

		GLMmodel* _modelNight;
		GLMmodel* _modelDown;
		GLMmodel* _modelUp;
		GLMmodel* _model;
		GLMmodel* _modelPickaxe;

		int _modelNumber;
		int _score;
		int _lives;

		float _scale;
		float _mouthRotation;

		bool _alive;

		bool _mouthDirection;

	public:

		Pacman();
		~Pacman();

		void init();

		void update(float elapsedTime);
		void draw();

		bool getBall();
		int getScore();
		int getLives();
		float getScale();

		void setBall(bool ball);
		void setScore(int score);
		void setLives(int lives);
		void setScale(float scale);

		void addScore(int score);
		void setModel(int model);

		void setDead();
		void setAlive();
		bool isAlive();
};

#endif