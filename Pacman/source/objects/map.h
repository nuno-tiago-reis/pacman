#ifndef MAP_H
#define MAP_H

/* OpenGL */
#include <GL/glut.h>

/* Standard */
#include <array> 
#include <fstream>
#include <iostream>

/* Textures - Loading */
#include "../soil/soil.h"
#pragma comment(lib,"F:/BitBucket/pacman/Pacman/source/soil/lib/libSOIL.a")

/* Sounds - Loading */
#include <fmod.hpp>
#include <fmod.h>

/* Pacman - Objects*/
#include "object.h"
#include "quadric.h"

/* Pacman - Constants */
#include "../constants.h"

using namespace std;

class Map {

	private:

		int _ballCount;

		GLMmodel* _model;

		Quadric _quadrics[MAP_Y][MAP_X];

	public:

		Map();
		~Map();

		void init();

		void draw();
		bool update(Object *object);

		void setBallCount(int ballCount);

		int getBallCount();

		void removeBall();
		array<int,2> testMove(Object *object,array<int,2> type);

		Quadric *getQuadric(int line, int column);
};

#endif