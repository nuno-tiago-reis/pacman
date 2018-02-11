#include "object.h"

using namespace std;

Object::Object() {

}

Object::~Object() {

}

bool Object::getTurn() {

	return _turn;
}

int Object::getMode() {

	return _mode;
}

int Object::getNode() {

	return _node;
}

int Object::getRotation() {

	return _rotation;
}

float Object::getRemaining() {

	return _remaining;
}

array<int,3> Object::getVelocity() {

	return _velocity;
}

array<int,3> Object::getPosition() {

	return _position;
}

array<int,3> Object::getNewVelocity() {

	return _newVelocity;
}

void Object::setTurn(bool turn) {

	_turn = turn;
}

void Object::setMode(int mode) {

	_mode = mode;
}

void Object::setNode(int node) {

	_node = node;
}

void Object::setRemaining(float remaining) {

	_remaining = remaining;
}

void Object::setVelocity(array<int,3> velocity) {

	for(int i=0; i<3; i++) {
		_velocity[i] = velocity[i];
		_newVelocity[i] = 0;
	}

	setTurn(false);

	if(_velocity[0] == -VELOCITY) 
		_rotation = 90;
	else if(_velocity[0] == VELOCITY) 
		_rotation = 270;
	else if(_velocity[1] == -VELOCITY) 
		_rotation = 180;
	else if(_velocity[1] == VELOCITY) 
		_rotation = 0;
}

void Object::setPosition(array<int,3> position) {

	for(int i=0; i<3; i++)
		_position[i] = position[i];
}

void Object::setNewVelocity(array<int,3> velocity) {

	for(int i=0; i<3; i++)
		_newVelocity[i] = velocity[i];

	setTurn(true);
}