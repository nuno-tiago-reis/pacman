#include "camera.h"

using namespace std;

Camera::Camera() {

	_position[0] = 14 * BLOCK_SIZE+ BLOCK_SIZE/2;
	_position[1] = 7 * BLOCK_SIZE + BLOCK_SIZE/2;
	_position[2] = 37;
}

Camera::~Camera() {

}

void Camera::update(Pacman *pacman) {

	setPosition(pacman->getPosition());
	setRotation(pacman->getRotation());
}

void Camera::reshape(int width, int height) {

	glViewport(0, 0, width, height);
}

void Camera::draw(int width, int height) {

	switch(_mode) {

		case 0:	glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(-BLOCK_SIZE/2, width*2+BLOCK_SIZE/2, -BLOCK_SIZE/2, height*2+BLOCK_SIZE/2, -100, 5);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				break;

		case 1:	glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(60,(float)width/height,50,1500);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt( _position[0],_position[1]-200,200,_position[0],_position[1],0,0,0,1);
				break;

		case 2:	glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(90,(float)width/height,50,1500);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt( _position[0],_position[1]-200,200,_position[0],_position[1],_position[2],0,1,0);
				break;

		case 3:	glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(90,(float)width/height,50,1000);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt( _position[0],_position[1]+200,200,_position[0],_position[1],_position[2],0,-1,0);
				break;

		case 4:	glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(90,(float)width/height,50,1000);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt( _position[0]-200,_position[1],200,_position[0],_position[1],_position[2],1,0,0);
				break;

		case 5:	glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(90,(float)width/height,50,1000);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt( _position[0]+200,_position[1],200,_position[0],_position[1],_position[2],-1,0,0);
				break;

		case 6:	glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(90,(float)width/height,50,1000);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt(_position[0]-100*sin(_rotation*PI_RAD),_position[1]+100*cos(_rotation*PI_RAD),200,
						  _position[0],_position[1],0, 0, 0, 1);
				break;
	}
}

int Camera::getMode() {

	return _mode;
}

int Camera::getRotation() {

	return _rotation;
}

array<int,3> Camera::getPosition() {

	return _position;
}

void Camera::setMode(int mode) {

	_mode = mode;
}

void Camera::setRotation(int rotation) {

	_rotation = rotation;
}

void Camera::setPosition(array<int,3> position) {

	for(int i=0; i<3; i++)
		_position[i] = position[i];
}