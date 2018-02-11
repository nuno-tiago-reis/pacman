#include "quadric.h"

using namespace std;

int texture;

Quadric::Quadric() {

	init();
}

Quadric::~Quadric() {

}

void Quadric::init() {

	_visible = true;
	_direction = 1;
	_position[2] = 25;
}

void Quadric::draw() {

	if(texture == 0)
		texture = SOIL_load_OGL_texture("textures/floor.png", SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_DDS_LOAD_DIRECT);

	glPushMatrix();

		glEnable(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

		/* comment the material*/
		GLfloat amb[]={0.05375f,0.05f,0.06625f,1.0f};
		GLfloat diff[]={0.18275f,0.17f,0.22525f,1.0f};
		GLfloat spec[]={0.332741f,0.328634f,0.346435f,1.0f};
		GLfloat shine=38.4f;

		glMaterialfv(GL_FRONT,GL_AMBIENT,amb);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diff);
		glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
		glMaterialf(GL_FRONT,GL_SHININESS,shine);

		glBindTexture(GL_TEXTURE_2D,texture);
		glBegin(GL_QUADS);
			glNormal3f(0,0,1);
			glTexCoord2d(0,1);	glVertex3f(-BLOCK_SIZE/2, BLOCK_SIZE/2, 0);
			glTexCoord2d(1,1);	glVertex3f (BLOCK_SIZE/2, BLOCK_SIZE/2, 0);
			glTexCoord2d(1,0);	glVertex3f( BLOCK_SIZE/2,-BLOCK_SIZE/2, 0);	
			glTexCoord2d(0,0);	glVertex3f(-BLOCK_SIZE/2,-BLOCK_SIZE/2, 0);	
		glEnd();

		glDisable(GL_TEXTURE_2D);

		switch(_type) {

			case 1:	if(!USING_MODELS) {

						glTranslatef(0,0,25);
				
						glMaterialfv(GL_FRONT,GL_AMBIENT,_ambient);
						glMaterialfv(GL_FRONT,GL_DIFFUSE,_diffuse);
						glMaterialfv(GL_FRONT,GL_SPECULAR,_specular);
						glMaterialf(GL_FRONT,GL_SHININESS,_shininess);
				
						glutSolidCube(_size);
					}
					break;

			case 2:	if(_visible) {

						glTranslatef(0.0f,0.0f, (GLfloat)_position[2]);

						glMaterialfv(GL_FRONT,GL_AMBIENT,_ambient);
						glMaterialfv(GL_FRONT,GL_DIFFUSE,_diffuse);
						glMaterialfv(GL_FRONT,GL_SPECULAR,_specular);
						glMaterialf(GL_FRONT,GL_SHININESS,_shininess);

						glutSolidSphere(10,8,8);
					}
					break;

			case 3:	if(_visible) {

						if(_position[2] > 50 && _direction == 1)
							_direction = -1;
						else if(_position[2] < 25 && _direction == -1)
							_direction = 1;

						_position[2] += _direction;

						glTranslatef(0.0f,0.0f,(GLfloat)_position[2]);

						glMaterialfv(GL_FRONT,GL_AMBIENT,_ambient);
						glMaterialfv(GL_FRONT,GL_DIFFUSE,_diffuse);
						glMaterialfv(GL_FRONT,GL_SPECULAR,_specular);
						glMaterialf(GL_FRONT,GL_SHININESS,_shininess);

						glutSolidSphere(15.0f,8,8);
					}
					break;

			case 4:	if(!USING_MODELS) {

						glTranslatef(0,0,25);
				
						glMaterialfv(GL_FRONT,GL_AMBIENT,_ambient);
						glMaterialfv(GL_FRONT,GL_DIFFUSE,_diffuse);
						glMaterialfv(GL_FRONT,GL_SPECULAR,_specular);
						glMaterialf(GL_FRONT,GL_SHININESS,_shininess);
				
						glutSolidCube(_size);
					}
					break;
		}

	glPopMatrix();
}

bool Quadric::visit(Pacman *pacman) {

	array<int,3> position = pacman->getPosition();

	switch(_type) {

		case 2:		if(_visible && (position[0]-_position[0]) == 0 && (position[1]-_position[1]) == 0) {

						pacman->addScore(BALL_SCORE);

						_visible = false;

						return true;
					}
					break;

		case 3:		if(_visible && (position[0]-_position[0]) == 0 && (position[1]-_position[1]) == 0) {

						pacman->setMode(2);
						pacman->setRemaining(GHOST_TIME_2);
						pacman->addScore(BIG_BALL_SCORE);

						_visible = false;

						return true;
					}
					break;
	}
	return false;
}

bool Quadric::canMoveInto(Object *object, bool velMode) {

	array<int,3> velocity = object->getVelocity();
	array<int,3> position = object->getPosition();

	switch(_type) {

		case 1:		if(velMode) 
						return false;
		
					for(int i=0; i<3; i++)
						velocity[i] = 0;

					object->setVelocity(velocity);
					return false;

		case 4:		if(velMode) 
						return false;
			
					for(int i=0; i<3; i++)
						velocity[i] = 0;
					
					object->setVelocity(velocity);
					return false;

		case 5:		if(_index[1] == 0 && velocity[0] == -VELOCITY && position[0] < 0) {
						position[0] = BLOCK_SIZE*(MAP_X-1) + BLOCK_SIZE/2;
					}	
					else if(_index[1] == MAP_X-1 && velocity[0] == VELOCITY && position[0] > MAP_X*BLOCK_SIZE) {
						position[0] = BLOCK_SIZE/2;
					}	
					object->setPosition(position);
					return true;
	}

	return true;
}

char Quadric::getType() {

	return _type;
}

array<int,2> Quadric::getIndex() {

	return _index;
}

array<int,3> Quadric::getPosition() {

	return _position;
}

void Quadric::setType(char type) {

	_type = type;

	switch(_type) {

		case 1:	_ambient[0] = 0.0f;
				_ambient[1] = 0.0f;
				_ambient[2] = 0.0f;
				_ambient[3] = 1.0f;

				_diffuse[0] = 0.0f;
				_diffuse[1] = 0.0f;
				_diffuse[2] = 1.0f;
				_diffuse[3] = 1.0f;

				_specular[0] = 0.5f;
				_specular[1] = 0.5f;
				_specular[2] = 0.5f;
				_specular[3] = 1.0f;

				_shininess = 12.0f;
					
				_size = 25;
				break;

		case 2:	_ambient[0] = 0.0f;
				_ambient[1] = 0.0f;
				_ambient[2] = 0.0f;
				_ambient[3] = 1.0f;

				_diffuse[0] = 0.4f;
				_diffuse[1] = 0.4f;
				_diffuse[2] = 0.4f;
				_diffuse[3] = 1.0f;

				_specular[0] = 0.7f;
				_specular[1] = 0.7f;
				_specular[2] = 0.7f;
				_specular[3] = 1.0f;

				_shininess = 52.8f;
				break;

		case 3:	_ambient[0] = 0.0f;
				_ambient[1] = 0.0f;
				_ambient[2] = 0.0f;
				_ambient[3] = 1.0f;

				_diffuse[0] = 0.75164f;
				_diffuse[1] = 0.60648f;
				_diffuse[2] = 0.22648f;
				_diffuse[3] = 1.0f;

				_specular[0] = 0.628281f;
				_specular[1] = 0.555802f;
				_specular[2] = 0.366065f;
				_specular[3] = 1.0f;

				_shininess = 52.8f;
				break;

		case 4:	_ambient[0] = 0.0f;
				_ambient[1] = 0.0f;
				_ambient[2] = 0.0f;
				_ambient[3] = 1.0f;

				_diffuse[0] = 0.0f;
				_diffuse[1] = 0.0f;
				_diffuse[2] = 1.0f;
				_diffuse[3] = 1.0f;

				_specular[0] = 0.5f;
				_specular[1] = 0.5f;
				_specular[2] = 0.5f;
				_specular[3] = 1.0f;

				_shininess = 12.0f;

				_size = 15;
				break;
	}
}

void Quadric::setIndex(array<int,2> index) {

	for(int i=0; i<2; i++)
		_index[i] = index[i];
}

void Quadric::setPosition(array<int,3> position) {

	for(int i=0; i<3; i++)
		_position[i] = position[i];
}