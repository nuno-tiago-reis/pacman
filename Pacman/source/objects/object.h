#ifndef OBJECT_H
#define OBJECT_H

/* OpenGL */
#include <GL/glut.h>

/* Standard */
#include <array> 
#include <stdio.h>

/* Models - Loading */
#include "../models/glm.h"

/* Pacman - Constants */
#include "../constants.h"

using namespace std;

class Object {

	protected:

		GLMmodel* _model;

		bool _turn;
		int _mode;
		int _node;
		int _rotation;
		float _remaining;

		float _ambient[4];
		float _diffuse[4];
		float _specular[4];
		float _shininess;

		array<int,3> _velocity;
		array<int,3> _position;
		array<int,3> _newVelocity;

	public:

		Object();
		~Object();

		bool getTurn();
		int getMode();
		int getNode();
		int getRotation();
		float getRemaining();
		array<int,3> getVelocity();
		array<int,3> getPosition();	
		array<int,3> getNewVelocity();

		void setTurn(bool turn);
		void setMode(int mode);
		void setNode(int node);
		void setRotation(int rotation);
		void setRemaining(float remaining);
		void setVelocity(array<int,3> velocity);
		void setPosition(array<int,3> position);
		void setNewVelocity(array<int,3> velocity);
};

#endif