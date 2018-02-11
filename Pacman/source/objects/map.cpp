#include "map.h"

using namespace std;

Map::Map() {
	
	int i = MAP_Y-1, j = 0;
	char output = 0;
	array<int,2> index = {0,0};
	array<int,3> position = {0,0,0};

	freopen ("matrix.txt","r",stdin);

	while(output != EOF) {

		output = getchar();

		if(output != '\t'  && output != '\n') {

			index[0] = i;
			index[1] = j;

			position[0] = index[1]*BLOCK_SIZE+BLOCK_SIZE/2;
			position[1] = index[0]*BLOCK_SIZE+BLOCK_SIZE/2;
			position[2] = 25;
			
			_quadrics[i][j].setType(output-'0');
			_quadrics[i][j].setIndex(index);
			_quadrics[i][j].setPosition(position);

			if(++j == MAP_X) {

				if(--i == -1 )
					break;
				j=0;
			}
		}
	}

	_ballCount = BALL_NUMBER;

	freopen("/dev/stdin","r",stdin);
}

Map::~Map() {
}

void Map::init() {

	for(int i=0; i<MAP_Y; i++)
		for(int j=0; j<MAP_X; j++)
			_quadrics[i][j].init();

	_ballCount = BALL_NUMBER;
}

void Map::draw() {

	glPushMatrix();	

		glTranslatef(BLOCK_SIZE/2,BLOCK_SIZE/2,12.5);

		/*Sphere Drawing*/
		for(int i=0; i<MAP_Y; i++) {
		
			for(int j=0; j<MAP_X; j++) {

				_quadrics[i][j].draw();
				glTranslatef(BLOCK_SIZE,0,0);
			}
			glTranslatef(-BLOCK_SIZE*MAP_X,BLOCK_SIZE,0);
		}
	glPopMatrix();

	if(USING_MODELS) {

		/*Walls Drawing*/
		glPushMatrix();	

			GLfloat amb[]={0.5f,0.5f,0.5f,1.0f};
			GLfloat diff[]={0.5f,0.5f,1.0f,1.0f};
			GLfloat spec[]={1.0f,1.0f,1.0f,1.0f};
			GLfloat shine=46.3f;
			glMaterialfv(GL_FRONT,GL_AMBIENT,amb);
			glMaterialfv(GL_FRONT,GL_DIFFUSE,diff);
			glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
			glMaterialf(GL_FRONT,GL_SHININESS,shine);

			glTranslatef(BLOCK_SIZE*13.5,BLOCK_SIZE*16.5,25);
			glRotatef(90,1,0,0);
			glScalef(2,2,2);
			glTranslatef(12,0,340);

			if (!_model)
				_model = glmReadOBJ("MAPAFINAL.obj");

			glmDraw(_model, GLM_SMOOTH | GLM_TEXTURE);

		glPopMatrix();
	}
}

bool Map::update(Object *object) {

	array<int,2> index;
	array<int,3> position = object->getPosition();
	array<int,3> velocity = object->getVelocity();
	array<int,3> newVelocity = object->getNewVelocity();

	index[0] = position[1]/BLOCK_SIZE;
	index[1] = position[0]/BLOCK_SIZE;
	
	if(_quadrics[index[0]][index[1]].visit((Pacman*)object))
		removeBall();

	if(object->getTurn()) {
	
		if(newVelocity[1] != 0 && position[0] % BLOCK_SIZE == BLOCK_SIZE/2) {

			if(newVelocity[1] == VELOCITY)
				index[0] = (position[1]+BLOCK_SIZE/2)/BLOCK_SIZE;
			else
				index[0] = (position[1]-BLOCK_SIZE/2-VELOCITY)/BLOCK_SIZE;

			index[1] = position[0]/BLOCK_SIZE;

			if(_quadrics[index[0]][index[1]].canMoveInto(object,true)) {
				object->setVelocity(newVelocity);
				return true;
			}
		}
		else if(newVelocity[0] != 0 && position[1] % BLOCK_SIZE == BLOCK_SIZE/2) {

			if(newVelocity[0] == VELOCITY)
				index[1] = (position[0]+BLOCK_SIZE/2)/BLOCK_SIZE;
			else
				index[1] = (position[0]-BLOCK_SIZE/2-VELOCITY)/BLOCK_SIZE;
			
			index[0] = position[1]/BLOCK_SIZE;

			if(_quadrics[index[0]][index[1]].canMoveInto(object,true)) {
				object->setVelocity(newVelocity);
				return true;
			}
		}
	}
	
	if(velocity[1] != 0) {

		if(velocity[1] == VELOCITY)
			index[0] = (position[1]+BLOCK_SIZE/2)/BLOCK_SIZE;
		else
			index[0] = (position[1]-BLOCK_SIZE/2-VELOCITY)/BLOCK_SIZE;

		index[1] = position[0]/BLOCK_SIZE;
	}
	else if(velocity[0] != 0) {

		if(velocity[0] == VELOCITY)
			index[1] = (position[0]+BLOCK_SIZE/2)/BLOCK_SIZE;
		else
			index[1] = (position[0]-BLOCK_SIZE/2-VELOCITY)/BLOCK_SIZE;

		index[0] = position[1]/BLOCK_SIZE;
	}
	else return false;

	if(index[1] < 0)
		index[1] = 0;
	else if(index[1] > MAP_X-1)
		index[1] = MAP_X-1;

	return _quadrics[index[0]][index[1]].canMoveInto(object,false);
}

int Map::getBallCount() {

	return _ballCount;
}

void Map::setBallCount(int ballCount) {

	_ballCount = ballCount;
}

void Map::removeBall() {

	_ballCount--;
}

Quadric *Map::getQuadric(int line, int column) {

	return &_quadrics[line][column];
}