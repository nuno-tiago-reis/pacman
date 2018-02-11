#include "explosion.h"

using namespace std;

Explosion::Explosion() {
}

Explosion::~Explosion() {
}

void Explosion::init(Pacman *pacman) {

	float p=0,z=0;

	array<int,3> position = pacman->getPosition();

	setTime(3);
	setState(true);

	_size = FRAGMENT_SIZE;
	//_texture[0] = SOIL_load_OGL_texture("textures/yellow_particle.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_DDS_LOAD_DIRECT);
	//_texture[1] = SOIL_load_OGL_texture("textures/red_particle.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_DDS_LOAD_DIRECT);

	for(int i=0; i<PARTICLES; i++) {

		for(int j=0; j<3; j++)
			_particles[i].position[j] = (GLfloat)position[j];
	
		_particles[i].scale = 1.0f;
		_particles[i].lifespan = (GLfloat)(rand()%6+5);

		if(rand()%10 == 0)
			_particles[i].texture = 1;
		else 
			_particles[i].texture = 0;

		if(pacman->getLives() == 3) {

			_particles[i].velocity[0] = sin(p)*cos(z)+(float)2*rand()/RAND_MAX-1;
			_particles[i].velocity[1] = sin(p)*sin(z)+(float)2*rand()/RAND_MAX-1;
			_particles[i].velocity[2] = cos(p)+(float)2*rand()/RAND_MAX-1;
		}
		else {

			_particles[i].velocity[0] = cos(z)+(float)2*rand()/RAND_MAX-1;
			_particles[i].velocity[1] = sin(z)+(float)2*rand()/RAND_MAX-1;
			_particles[i].velocity[2] = cos(p)+(float)2*rand()/RAND_MAX-1;
		}

		_particles[i].color[0] = 1;
		_particles[i].color[1] = 0;
		_particles[i].color[2] = 0;

		_particles[i].lifespan = (GLfloat)(rand()%4);

		z+=THETA;
		p+=PHI;
	}
}

void Explosion::update(Pacman *pacman, float elapsedTime) {

	_time -= elapsedTime;

	fprintf(stdout,"%f\n",_time);

	if(_time < 0)
		setState(false);
	
	pacman->setScale(pacman->getScale()*0.75f);

	for(int i=0; i<PARTICLES; i++) {

		if(_particles[i].lifespan < 0.0f)
			continue;

		if(_particles[i].velocity[2] < 0.5f)
			_particles[i].velocity[2] = -1.0f;

		_particles[i].velocity[0] *= 0.95f;
		_particles[i].velocity[1] *= 0.95f;
		_particles[i].velocity[2] *= 0.95f;

		_particles[i].scale *= 0.95f;
		_particles[i].lifespan -= elapsedTime;

		_particles[i].position[0] += _particles[i].velocity[0]*5.0f;
		_particles[i].position[1] += _particles[i].velocity[1]*5.0f;
		_particles[i].position[2] += _particles[i].velocity[2]*2.0f;
	}
}

void Explosion::draw() {

	if(_time <= 0)
		return;

	glEnable(GL_TEXTURE_2D);

	for(int i=0; i<PARTICLES; i++) {

		if(_particles[i].lifespan < 0 || _particles[i].position[2] < 0)
			continue;

		glPushMatrix();

			glTranslatef(_particles[i].position[0],_particles[i].position[1],_particles[i].position[2]);
			glRotatef((GLfloat)(rand()%180), (GLfloat)(rand()%2), (GLfloat)(rand()%2), (GLfloat)(rand()%2));
			glScalef(_particles[i].scale,_particles[i].scale,_particles[i].scale);

			/* comment the material*/
			GLfloat amb[]={0.0f,0.0f,0.0f,1.0f};
			GLfloat diff[]={0.5f,0.5f,0.0f,1.0f};
			GLfloat spec[]={0.6f,0.6f,0.5f,1.0f};
			GLfloat shine=32.0f;
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diff);
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);

			glutSolidCube(_size*2);

			
			glBindTexture(GL_TEXTURE_2D, _texture[_particles[i].texture]);
			glBegin(GL_QUADS);
				glNormal3f(0,0,-1);
				glTexCoord2d(0.0f,0.0f);	glVertex3f(-_size,-_size,-_size);
				glTexCoord2d(1.0f,0.0f);	glVertex3f( _size,-_size,-_size);
				glTexCoord2d(1.0f,1.0f);	glVertex3f( _size, _size,-_size);
				glTexCoord2d(0.0f,1.0f);	glVertex3f(-_size, _size,-_size);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, _texture[_particles[i].texture]);
			glBegin(GL_QUADS);
				glNormal3f(1,0,0);
				glTexCoord2d(0.0f,0.0f);	glVertex3f(_size,-_size,-_size);
				glTexCoord2d(1.0f,0.0f);	glVertex3f(_size, _size,-_size);
				glTexCoord2d(1.0f,1.0f);	glVertex3f(_size, _size, _size);
				glTexCoord2d(0.0f,1.0f);	glVertex3f(_size,-_size, _size);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, _texture[_particles[i].texture]);
			glBegin(GL_QUADS);
				glNormal3f(0,0,1);
				glTexCoord2d(0.0f,0.0f);	glVertex3f(-_size,-_size, _size);
				glTexCoord2d(1.0f,0.0f);	glVertex3f( _size,-_size, _size);
				glTexCoord2d(1.0f,1.0f);	glVertex3f( _size, _size, _size);
				glTexCoord2d(0.0f,1.0f);	glVertex3f(-_size, _size, _size);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, _texture[_particles[i].texture]);
			glBegin(GL_QUADS);
				glNormal3f(0,1,0);
				glTexCoord2d(0.0f,0.0f);	glVertex3f(-_size,_size,-_size);
				glTexCoord2d(1.0f,0.0f);	glVertex3f( _size,_size,-_size);
				glTexCoord2d(1.0f,1.0f);	glVertex3f( _size,_size, _size);
				glTexCoord2d(0.0f,1.0f);	glVertex3f(-_size,_size, _size);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, _texture[_particles[i].texture]);
			glBegin(GL_QUADS);
				glNormal3f(-1,0,0);
				glTexCoord2d(0.0f,0.0f);	glVertex3f(-_size,-_size,-_size);
				glTexCoord2d(1.0f,0.0f);	glVertex3f(-_size, _size,-_size);
				glTexCoord2d(1.0f,1.0f);	glVertex3f(-_size, _size, _size);
				glTexCoord2d(0.0f,1.0f);	glVertex3f(-_size,-_size, _size);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, _texture[_particles[i].texture]);
			glBegin(GL_QUADS);
				glNormal3f(0,-1,0);
				glTexCoord2d(0.0f,0.0f);	glVertex3f(-_size,-_size,-_size);
				glTexCoord2d(1.0f,0.0f);	glVertex3f( _size,-_size,-_size);
				glTexCoord2d(1.0f,1.0f);	glVertex3f( _size,-_size, _size);
				glTexCoord2d(0.0f,1.0f);	glVertex3f(-_size,-_size, _size);
			glEnd();

			/*
			glTranslatef(_particles[i].position[0],_particles[i].position[1],_particles[i].position[2]);
			glRotatef(rand()%180,rand()%2,rand()%2,rand()%2);
			glScalef(_particles[i].scale,_particles[i].scale,_particles[i].scale);

			glBindTexture(GL_TEXTURE_2D, _texture[_particles[i].texture]);
			glBegin(GL_QUADS);
				glTexCoord2d(0.0f,0.0f);	glVertex3f(-_size,-_size,-_size);
				glTexCoord2d(1.0f,0.0f);	glVertex3f( _size,-_size,-_size);
				glTexCoord2d(1.0f,1.0f);	glVertex3f( _size, _size,-_size);
				glTexCoord2d(0.0f,1.0f);	glVertex3f(-_size, _size,-_size);
			glEnd();
			*/
		glPopMatrix();
	}

	glDisable(GL_TEXTURE_2D);
}

float Explosion::getTime() {

	return _time;
}

bool Explosion::getState() {

	return _state;
}

void Explosion::setTime(float time) {

	_time = time;
}

void Explosion::setState(bool state) {

	_state = state;
}