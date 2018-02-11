#include "pacman.h"

using namespace std;

Pacman::Pacman() {

	init();

	setLives(3);
	setAlive();

	_ambient[0] = 1.0;
	_ambient[1] = 1.0;
	_ambient[2] = 1.0;
	_ambient[3] = 1.0;

	_diffuse[0] = 1.0;
	_diffuse[1] = 1.0;
	_diffuse[2] = 1.0;
	_diffuse[3] = 1.0;

	_specular[0] = 1.0;
	_specular[1] = 1.0;
	_specular[2] = 1.0;
	_specular[3] = 1.0;
}

Pacman::~Pacman() {

}

void Pacman::init() {

	_position[0] = 14 * BLOCK_SIZE + BLOCK_SIZE/2;
	_position[1] = 7 * BLOCK_SIZE + BLOCK_SIZE/2;
	_position[2] = 37;


	_mode = 0;
	_scale = 1;
	_turn = false;
	_alive = true;
	_remaining = 0;
	_rotation = 180;

	_velocity[0] = _velocity[1] = _velocity[2] = 0; 
}

void Pacman::update(float elapsedTime) {

	for(int i=0; i<2; i++)
		_position[i] += _velocity[i];

	if(_mode > 0)
		setRemaining(_remaining-elapsedTime);
	
	if(_remaining < GHOST_TIME_1 && _mode == 2)
		setMode(1);	
	else if(_remaining < GHOST_TIME_0 && _mode == 1) {
		setMode(0);
		setRemaining(0);
	}

	if(_mouthRotation != 0 || _velocity[0] != 0 || _velocity[1] != 0) {

		if(_mouthDirection == 0) {

			if(_mouthRotation < 30) {

				_mouthRotation += 6.0f;
			}
			else{	

				_mouthDirection = 1;
			}
		}
		if(_mouthDirection == 1) {

			if(_mouthRotation > 0){

				_mouthRotation -= 6.0f;
			}
			else{	

				_mouthDirection = 0;
			}
		}
	}
}

void Pacman::draw() {

	if (!_model) {

		_model = glmReadOBJ("models/pacman.obj");	
		if (!_model)
			exit(0);
	}
	if (!_modelUp) {

		_modelUp = glmReadOBJ("models/pacman_half_up.obj");
		if (!_modelUp)
			exit(0);
	}
	if (!_modelDown) {

		_modelDown = glmReadOBJ("models/pacman_half_down.obj");
		if (!_modelUp)
			exit(0);
	}

	if (!_modelNight) {

		_modelNight = glmReadOBJ("models/pacman_miner.obj");
		if (!_modelNight)
			exit(0);
	}
	if (!_modelPickaxe) {

		_modelPickaxe = glmReadOBJ("models/pacman_pickaxe.obj");
		if (!_modelPickaxe)
			exit(0);
	}
		 
	glPushMatrix();

		glMaterialfv(GL_FRONT,GL_AMBIENT,_ambient);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,_diffuse);
		glMaterialfv(GL_FRONT,GL_SPECULAR,_specular);
		glMaterialf(GL_FRONT,GL_SHININESS,_shininess);
		 
		glTranslatef((GLfloat)_position[0], (GLfloat)_position[1], (GLfloat)_position[2]);
		glRotatef(_rotation-180.0f,0.0f,0.0f,1.0f);
		glScaled(0.5f*_scale,0.5f*_scale,0.5f*_scale);
		glRotatef(90.0f,1.0f,0.0f,0.0f);

		/* Pacman Body */
		glmDraw(_model, GLM_SMOOTH| GLM_TEXTURE);

		/* Pacman Body */
		if(_modelNumber == 0)
			glmDraw(_model, GLM_SMOOTH| GLM_TEXTURE);
		else if(_modelNumber == 1)
			glmDraw(_modelNight, GLM_SMOOTH| GLM_TEXTURE);

		glPushMatrix();

			glRotatef(_mouthRotation,1.0f,0.0f,0.0f);
			
			glPushMatrix();

				glTranslatef(50.0f,0.0f,0.0f);
				if(_modelNumber == 1)
					glmDraw(_modelPickaxe, GLM_SMOOTH| GLM_TEXTURE);

			glPopMatrix();
			/* Pacman Upper Lip */
			glmDraw(_modelUp, GLM_SMOOTH| GLM_TEXTURE);

		glPopMatrix();

		glPushMatrix();

			glRotatef(-_mouthRotation,1.0f,0.0f,0.0f);
			/* Pacman Lower Lip */
			glmDraw(_modelDown, GLM_SMOOTH| GLM_TEXTURE);
	
		glPopMatrix();

	glPopMatrix();
}

float Pacman::getScale() {

	return _scale;
}

int Pacman::getScore() {

	return _score;
}

int Pacman::getLives() {

	return _lives;
}

void Pacman::setScale(float scale) {

	_scale = scale;
}

void Pacman::setScore(int score) {

	_score = score;
}

void Pacman::setLives(int lives) {

	_lives = lives;
}

void Pacman::addScore(int score) {

	_score += score;
}

void Pacman::setModel(int model) {

	_modelNumber = model;
}

void Pacman::setDead() {

	_alive = false;
}

void Pacman::setAlive() {

	_alive = true;
}

bool Pacman::isAlive() {

	return _alive;
}