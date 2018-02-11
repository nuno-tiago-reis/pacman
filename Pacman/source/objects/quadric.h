#ifndef QUADRIC_H
#define QUADRIC_H

/* OpenGL */
#include <GL/glut.h>

/* Standard */
#include <array> 

/* Textures - Loading */
#include "../soil/soil.h"
#pragma comment(lib,"F:/BitBucket/pacman/Pacman/source/soil/lib/libSOIL.a")

/* Pacman - Objects */
#include "object.h"
#include "pacman.h"

/* Pacman - Constants */
#include "../constants.h"

using namespace std;

class Quadric {

	private:

		int _direction;

		int _size;
		char _type;
		bool _visible;
		array<int,2> _index;
		array<int,3> _position;

		float _ambient[4];
		float _diffuse[4];
		float _specular[4];
		float _shininess;

	public:

		Quadric();
		~Quadric();

		void init();

		void draw();

		bool visit(Pacman *pacman);
		bool canMoveInto(Object *object, bool velMode);
		bool canMoveIntoGhosts(Object *object, bool velMode);

		char getType();
		array<int,2> getIndex();
		array<int,3> getPosition();

		void setType(char type);
		void setIndex(array<int,2> position);
		void setPosition(array<int,3> position);
};

#endif