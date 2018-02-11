#ifndef EXPLOSION_H
#define EXPLOSION_H

/* OpenGL */
#include <GL/glut.h>

/* Standard */
#include <math.h>
#include <array>

/* Textures - Loading */
#include "../soil/soil.h"
#pragma comment(lib,"F:/BitBucket/pacman/Pacman/source/soil/lib/libSOIL.a")

/* Pacman - Objects */
#include "pacman.h"

/* Pacman - Constants */
#include "../constants.h"

typedef struct Particle Particle;

struct Particle {

	array<float,3> position;
	array<float,3> velocity;
	array<int,3> color;

	int texture;

	float scale;
	float lifespan;	
};

class Explosion {

	private:

		Particle _particles[PARTICLES];

		bool _state;

		float _size;
		int _texture[2];

		float _time;

	public:

		Explosion();
		~Explosion();

		void init(Pacman *pacman);

		void update(Pacman *pacman, float elapsedTime);
		void draw();

		float getTime();
		bool getState();

		void setTime(float time);
		void setState(bool state);
};

#endif