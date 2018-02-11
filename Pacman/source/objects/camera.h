#ifndef CAMERA_H
#define CAMERA_H

/* OpenGL */
#include <GL/glut.h>

/* Standard */
#include <array>

/* Pacman - Objects */
#include "pacman.h"

/* Pacman - Constants */
#include "../constants.h"

using namespace std;

class Camera {

	private:

		int _mode;
		int _rotation;
		array<int,3> _position;

	public:

		Camera();
		~Camera();

		void update(Pacman *pacman);
		void reshape(int width, int height);
		void draw(int width, int height);

		int getMode();
		int getRotation();
		array<int,3> getPosition();

		void setMode(int mode);
		void setRotation(int rotation);
		void setPosition(array<int,3> position);
};

#endif