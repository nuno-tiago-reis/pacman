#include "ghost.h"

using namespace std;

int id = 0;
int ctr = 0;

bool flicker;

Graph graph;

GLMmodel *blueModel;
GLMmodel *whiteModel;

float eyeAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float eyeDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float eyeSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float eyeShininess = 45.0f;

float blackAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float blackDiffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float blackSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float blackShininess = 45.0f;

float whiteAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float whiteDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float whiteSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float whiteShininess = 45.0f;

float blueAmbient[] = { 0.0f, 0.0f, 0.75f, 1.0f };
float blueDiffuse[] = { 0.0f, 0.0f, 0.75f, 1.0f };
float blueSpecular[] = { 0.3f, 0.3f, 0.75f, 1.0f };
float blueShininess = 45.0f;

Ghost::Ghost() {

	setId(id++);

	init();

	switch(_id) {
	
		case 0: _ambient[0] = 1.0f;
				_ambient[1] = 1.0f;
				_ambient[2] = 1.0f;
				_ambient[3] = 1.0f;

				_diffuse[0] = 0.61424f;
				_diffuse[1] = 0.04136f;
				_diffuse[2] = 0.04136f;
				_diffuse[3] = 1.0f;

				_specular[0] = 0.727811f;
				_specular[1] = 0.626959f;
				_specular[2] = 0.626959f;
				_specular[3] = 1.0f;

				_shininess = 76.8f;
				break;

		case 1: _ambient[0] = 1.0f;
				_ambient[1] = 1.0f;
				_ambient[2] = 1.0f;
				_ambient[3] = 1.0f;

				_diffuse[0] = 0.396f;
				_diffuse[1] = 0.74151f;
				_diffuse[2] = 0.69102f;
				_diffuse[3] = 1.0f;

				_specular[0] = 0.297254f;
				_specular[1] = 0.30829f;
				_specular[2] = 0.306678f;
				_specular[3] = 1.0f;

				_shininess = 12.8f;
				break;

		case 2: _ambient[0] = 1.0f;
				_ambient[1] = 1.0f;
				_ambient[2] = 1.0f;
				_ambient[3] = 1.0f;

				_diffuse[0] = 0.75164f;
				_diffuse[1] = 0.60648f;
				_diffuse[2] = 0.22648f;
				_diffuse[3] = 1.0f;

				_specular[0] = 0.628281f;
				_specular[1] = 0.555802f;
				_specular[2] = 0.366065f;
				_specular[3] = 1.0f;

				_shininess = 51.2f;
				break;

		case 3:	_ambient[0] = 1.0f;
				_ambient[1] = 1.0f;
				_ambient[2] = 1.0f;
				_ambient[3] = 1.0f;

				_diffuse[0] = 1.0f;
				_diffuse[1] = 0.829f;
				_diffuse[2] = 0.829f;
				_diffuse[3] = 1.0f;

				_specular[0] = 0.296648f;
				_specular[1] = 0.296648f;
				_specular[2] = 0.296648f;
				_specular[3] = 1.0f;

				_shininess = 12.264f;
				break;
	}
}

Ghost::~Ghost() {

}

void Ghost::init() {

	switch(_id) {
	
		case 0:	_position[0] = 14*BLOCK_SIZE + BLOCK_SIZE/2;
				_position[1] = 17*BLOCK_SIZE + BLOCK_SIZE/2;
				_position[2] = 50;
				break;

		case 1: _position[0] = 12*BLOCK_SIZE;
				_position[1] = 15*BLOCK_SIZE + BLOCK_SIZE/2;
				_position[2] = 50;
				break;

		case 2: _position[0] = 14*BLOCK_SIZE;
				_position[1] = 15*BLOCK_SIZE + BLOCK_SIZE/2;
				_position[2] = 50;
				break;

		case 3: _position[0] = 16*BLOCK_SIZE;
				_position[1] = 15*BLOCK_SIZE + BLOCK_SIZE/2;
				_position[2] = 50;
				break;
	}

	_mode = 0;
	_remaining = 0;
	_rotation = 0;

	_turn = false;
	_released = false;

	for(int i=0; i<2; i++)
		_velocity[i] = 0;

	_velocity[2] = -1;
}

void Ghost::initGraph(Map *map) {

	graph.init(map);
}

void Ghost::update(Pacman *pacman) {

	array<int,3> vector = {0,0,0};
	array<int,3> position = pacman->getPosition();

	/* Ghost Hovering */
	if (_position[2] > 55 && _velocity[2] > 0)
		_velocity[2] = -2;//-2.5f;
	else if (_position[2] < 45 && _velocity[2] < 0)
		_velocity[2] = 2;//2.5f;

	/* Ghost Position Refresh */
	for(int i=0; i<3; i++) {

		if(_mode == 0)
			_position[i] += _velocity[i];
		else
			_position[i] +=  _velocity[i]/2;

		vector[i] = position[i] - _position[i];
	}

	/* Ghost Run Mode flicker indicator */
	if((++ctr % 50) > 25)
		flicker = true;
	else
		flicker = false;

	/* Ghost Teleport - Left and Right*/
	if(_velocity[0] == -VELOCITY && _position[0] < 0)
		_position[0] = BLOCK_SIZE*(MAP_X-1) + BLOCK_SIZE/2;
	else if(_velocity[0] == VELOCITY && _position[0] > MAP_X*BLOCK_SIZE)
		_position[0] = BLOCK_SIZE/2;

	/* Ghost Eye Rotation */
	if(_position[0] < position[0])
		_rotation = (int)(-acos(vector[1]/sqrt((float)vector[0]*vector[0]+vector[1]*vector[1]))*RAD_PI + 180.0f);
	else
		_rotation = (int)(acos(vector[1]/sqrt((float)vector[0]*vector[0]+vector[1]*vector[1]))*RAD_PI + 180.0f);

	/* Fix Ghost Position */
	if(_mode == 0 && _position[0] % 10 == 0)
		_position[0] -= _velocity[0]/2;
	if(_mode == 0 && _position[1] % 10 == 0)
		_position[1] -= _velocity[1]/2;

	/* Ghost Movement */
	if(_released && _position[0] % BLOCK_SIZE == BLOCK_SIZE/2 && _position[1] % BLOCK_SIZE == BLOCK_SIZE/2)
		calculateMovement(pacman);
}

void Ghost::draw() {

	switch(_id) {
	
		case 0:	if (!_model) {

					_model = glmReadOBJ("models/ghost_red.obj");
					if (!_model) 
						exit(0);
				}
				break;

		case 1: if (!_model) {

					_model = glmReadOBJ("models/ghost_blue.obj");
					if (!_model) 
						exit(0);
				}
				break;

		case 2:	if (!_model) {

					_model = glmReadOBJ("models/ghost_orange.obj");
					if (!_model) 
						exit(0);
				}
				break;

		case 3:	if (!_model) {

					_model = glmReadOBJ("models/ghost_pink.obj");
					if (!_model) 
						exit(0);
				}
				break;
	}

	if (!blueModel) {

		blueModel = glmReadOBJ("models/ghost_scared_blue.obj");
		if (!blueModel) 
			exit(0);
	}

	if (!whiteModel) {

		whiteModel = glmReadOBJ("models/ghost_scared_white.obj");
		if (!whiteModel) 
			exit(0);
	}

	glPushMatrix();	

		glMaterialfv(GL_FRONT,GL_AMBIENT,whiteAmbient);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,whiteDiffuse);
		glMaterialfv(GL_FRONT,GL_SPECULAR,whiteSpecular);
		glMaterialf(GL_FRONT,GL_SHININESS,whiteShininess);

		glTranslatef((GLfloat)_position[0], (GLfloat)_position[1], (GLfloat)_position[2]);
		glRotatef((GLfloat)_rotation,0.0f,0.0f,1.0f);
		glScalef(0.4f,0.4f,0.35f);
		glRotatef(90.0f,1.0f,0.0f,0.0f);

		if(_mode == 2) {
				
			glmDraw(whiteModel, GLM_SMOOTH| GLM_TEXTURE);
		}
		else if(_mode == 1) {

			if(flicker)
				glmDraw(blueModel, GLM_SMOOTH| GLM_TEXTURE);
			else
				glmDraw(whiteModel, GLM_SMOOTH| GLM_TEXTURE);
		}
		else {

			glmDraw(_model, GLM_SMOOTH| GLM_TEXTURE);
		}

	glPopMatrix();
}

void Ghost::adjustVelocity() {

	int node = GET_NODE(_position[1]/BLOCK_SIZE,_position[0]/BLOCK_SIZE);
	
	Node *u = graph.getNode(node);
	Node **list = u->getAdjacentList();

	if(_velocity[0] == VELOCITY && list[LEFT] != NULL)
		_velocity[0] = -_velocity[0];
	else if(_velocity[0] == -VELOCITY && list[RIGHT] != NULL)
		_velocity[0] = -_velocity[0];
	else if(_velocity[1] == VELOCITY && list[LOWER] != NULL)
		_velocity[1] = -_velocity[1];
	else if(_velocity[1] == -VELOCITY && list[UPPER] != NULL)
		_velocity[1] = -_velocity[1];
}

void Ghost::calculateMovement(Pacman *pacman) {

	array<int,2> direction;
	array<int,3> absolute;
	array<int,3> distance;
	array<int,3> position = pacman->getPosition();

	int node = GET_NODE(_position[1]/BLOCK_SIZE,_position[0]/BLOCK_SIZE);
	
	Node *u = graph.getNode(node);
	Node **list = u->getAdjacentList();

	if(u->getAdjacents() > 2) {
		
		for(int i=0; i<3; i++) {

			distance[i] = _position[i] - position[i];
			absolute[i] = abs(distance[i]);
		}

		if(_mode == 0) {

			if(rand() % 4 > 0) {

				/* Primary Chase Route */
				if((absolute[0] > absolute[1]) && distance[0] > 0)
					direction[0] = LEFT;
				else if((absolute[0] > absolute[1]) && distance[0] < 0)
					direction[0] = RIGHT;
				else if((absolute[0] < absolute[1]) && distance[1] > 0)
					direction[0] = LOWER;
				else if((absolute[0] < absolute[1]) && distance[1] < 0)
					direction[0] = UPPER;

				/* Secondary Chase Route */
				if(distance[0] > 0 && direction[0] != LEFT)
					direction[1] = LEFT;
				else if(distance[0] < 0 && direction[0] != RIGHT)
					direction[1] = RIGHT;
				else if(distance[1] > 0 && direction[0] != LOWER)
					direction[1] = LOWER;
				else if(distance[1] < 0 && direction[0] != UPPER)
					direction[1] = UPPER;
			}
			else {

				/* Primary Escape Route */
				if((absolute[0] > absolute[1]) && distance[0] > 0)
					direction[0] = RIGHT;
				else if((absolute[0] > absolute[1]) && distance[0] < 0)
					direction[0] = LEFT;
				else if((absolute[0] < absolute[1]) && distance[1] > 0)
					direction[0] = UPPER;
				else if((absolute[0] < absolute[1]) && distance[1] < 0)
					direction[0] = LOWER;
				else 
					printf("ERROR\n");

				/* Secondary Escape Route */
				if(distance[0] > 0 && direction[0] != LEFT)
					direction[1] = RIGHT;
				else if(distance[0] < 0 && direction[0] != RIGHT)
					direction[1] = LEFT;
				else if(distance[1] > 0 && direction[0] != LOWER)
					direction[1] = UPPER;
				else if(distance[1] < 0 && direction[0] != UPPER)
					direction[1] = LOWER;
				else 
					printf("ERROR\n");
			}

			newMovement(direction[0],direction[1],node); 
		}
		else {				

			/* Primary Escape Route */
			if((absolute[0] > absolute[1]) && distance[0] > 0)
				direction[0] = RIGHT;
			else if((absolute[0] > absolute[1]) && distance[0] < 0)
				direction[0] = LEFT;
			else if((absolute[0] < absolute[1]) && distance[1] > 0)
				direction[0] = UPPER;
			else if((absolute[0] < absolute[1]) && distance[1] < 0)
				direction[0] = LOWER;
			else 
				printf("ERROR\n");

			/* Secondary Escape Route */
			if(distance[0] > 0 && direction[0] != LEFT)
				direction[1] = RIGHT;
			else if(distance[0] < 0 && direction[0] != RIGHT)
				direction[1] = LEFT;
			else if(distance[1] > 0 && direction[0] != LOWER)
				direction[1] = UPPER;
			else if(distance[1] < 0 && direction[0] != UPPER)
				direction[1] = LOWER;
			else 
				printf("ERROR\n");

			newMovement(direction[0],direction[1],node); 
		}
	}
	else {

		if(_velocity[0] > 0)
			continueMovement(RIGHT,node);
		else if(_velocity[0] < 0)
			continueMovement(LEFT,node);
		else if(_velocity[1] > 0)
			continueMovement(UPPER,node);
		else if(_velocity[1] < 0) 
			continueMovement(LOWER,node);
	}
}

void Ghost::continueMovement(int direction, int node) {

	Node *u = graph.getNode(node);
	Node **list = u->getAdjacentList();

	//printf("node: %d direction: %d\n",node,direction);

	switch(direction) {
	
		case UPPER:	if(list[UPPER] != NULL) {

						setMovement(UPPER);
						return;
					}
					else if(list[LEFT] != NULL) {

						setMovement(LEFT);
						return;
					}
					else if(list[RIGHT] != NULL) {

						setMovement(RIGHT);
						return;
					}	
					break;

		case LOWER:	if(list[LOWER] != NULL) {

						setMovement(LOWER);
						return;
					}
					else if(list[LEFT] != NULL) {

						setMovement(LEFT);
						return;
					}
					else if(list[RIGHT] != NULL) {

						setMovement(RIGHT);
						return;
					}	
					break;
	
		case LEFT:	if(list[LEFT] != NULL) {

						setMovement(LEFT);
						return;
					}
					if(list[UPPER] != NULL) {

						setMovement(UPPER);
						return;
					}
					else if(list[LOWER] != NULL) {

						setMovement(LOWER);
						return;
					}
					break;
	
		case RIGHT:	if(list[RIGHT] != NULL) {

						setMovement(RIGHT);
						return;
					}			
					if(list[UPPER] != NULL) {

						setMovement(UPPER);
						return;
					}
					else if(list[LOWER] != NULL) {

						setMovement(LOWER);
						return;
					}
					break;
	}
	return;
}

bool Ghost::newMovement(int direction1, int direction2, int node) {

	Node *u = graph.getNode(node);
	Node **list = u->getAdjacentList();

	switch(direction1) {
	
		case UPPER:	if(list[UPPER] != NULL && _velocity[1] != -VELOCITY) {

						setMovement(UPPER);
						return true;
					}	
					break;

		case LOWER:	if(list[LOWER] != NULL && _velocity[1] != VELOCITY) {

						setMovement(LOWER);
						return true;
					}	
					break;
	
		case LEFT:	if(list[LEFT] != NULL && _velocity[0] != VELOCITY) {

						setMovement(LEFT);
						return true;
					}
					break;
	
		case RIGHT:	if(list[RIGHT] != NULL && _velocity[0] != -VELOCITY) {

						setMovement(RIGHT);
						return true;
					}
					break;
	}

	switch(direction2) {
	
		case UPPER:	if(list[UPPER] != NULL && _velocity[1] != -VELOCITY) {

						setMovement(UPPER);
						return true;
					}	
					break;

		case LOWER:	if(list[LOWER] != NULL && _velocity[1] != VELOCITY) {

						setMovement(LOWER);
						return true;
					}	
					break;
	
		case LEFT:	if(list[LEFT] != NULL && _velocity[0] != VELOCITY) {

						setMovement(LEFT);
						return true;
					}
					break;
	
		case RIGHT:	if(list[RIGHT] != NULL && _velocity[0] != -VELOCITY) {

						setMovement(RIGHT);
						return true;
					}
					break;
	}

	if(list[UPPER] != NULL && _velocity[1] != -VELOCITY) {

		setMovement(UPPER);
		return true;
	}
	else if(list[LEFT] != NULL && _velocity[0] != VELOCITY) {

		setMovement(LEFT);
		return true;
	}
	else if(list[RIGHT] != NULL && _velocity[0] != -VELOCITY) {

		setMovement(RIGHT);
		return true;
	}
	else if(list[LOWER] != NULL && _velocity[1] != VELOCITY) {

		setMovement(LOWER);
		return true;
	}
	/* Medida de Segurança */
	array<int,3> velocity = {0,0,0};

	setVelocity(velocity);

	return false;
}

int Ghost::caughtPacman(Pacman *pacman) {

		array<int,2> distance;
		array<int,3> position = pacman->getPosition();

		distance[0] = abs(_position[0] - position[0]);
		distance[1] = abs(_position[1] - position[1]);

		if(distance[0] > 50)
			return 0;

		if(distance[1] > 50)
			return 0;

		if( _position[1] != position[1] &&  _position[0] != position[0])
			return 0;

		if(_mode != 0)
			return 2;
		else
			return 1;
}

int Ghost::getId() {

	return _id;
}

bool Ghost::getReleased() {

	return _released;
}		

array<int,3> Ghost::getVelocity() {

	return _velocity;
}

void Ghost::setId(int id) {

	_id = id;
}

void Ghost::setReleased(bool release) {

	if(!_released) {

		_position[0] = 13*BLOCK_SIZE + BLOCK_SIZE/2;
		_position[1] = 19*BLOCK_SIZE + BLOCK_SIZE/2;
		_position[2] = 50;
		
		_velocity[0] = -VELOCITY;
		_velocity[1] = 0;
	}

	_released = release;
}

void Ghost::setVelocity(array<int,3> velocity) {

	for(int i=0; i<3; i++) {
		_velocity[i] = velocity[i];
		_newVelocity[i] = 0;
	}

	setTurn(false);
}

void Ghost::setMovement(int direction) {

	array<int,3> velocity = getVelocity();

	velocity[0] = velocity[1] = 0;

	switch(direction) {
		
		case UPPER:	velocity[1] = VELOCITY;
					setVelocity(velocity);
					break;

		case LOWER:	velocity[1] = -VELOCITY;
					setVelocity(velocity);
					break;

		case LEFT:	velocity[0] = -VELOCITY;
					setVelocity(velocity);
					break;

		case RIGHT:	velocity[0] = VELOCITY;
					setVelocity(velocity);
					break;
	}
}