#include "hud.h"

using namespace std;

#define HEIGHT 640
#define WIDTH 480

/* origin is the upper left corner */
unsigned char image[HEIGHT][WIDTH];

Hud::Hud() {

	_level = 1;
	_lives = 3;
}

Hud::~Hud() {

}

void Hud::init() {

	_textures[LIFE] = SOIL_load_OGL_texture("textures/hud/hud_lives.png", SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_DDS_LOAD_DIRECT);
	_textures[SCORE] = SOIL_load_OGL_texture("textures/hud/hud_score.png", SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_DDS_LOAD_DIRECT);
	_textures[LEVEL] = SOIL_load_OGL_texture("textures/hud/hud_level.png", SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_DDS_LOAD_DIRECT);
	_textures[TITLE] = SOIL_load_OGL_texture("textures/hud/hud_title.png", SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_DDS_LOAD_DIRECT);
	_textures[PACMAN] = SOIL_load_OGL_texture("textures/hud/hud_pacman.png", SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_DDS_LOAD_DIRECT);
}

void Hud::update(Pacman *pacman, Manager *manager) {

	_score = pacman->getScore();
	_lives = pacman->getLives();
	_level = manager->getLevel();
}

void Hud::draw(int width, int height) {

	char buffer[256];

	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f,width*2.0f,0.0f,height*2.0f,-50.0f,50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f,0.0f,50.0f);

	glPushMatrix();

		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_QUADS);
			glVertex3f(0.0f,height*2.0f,-5.0f);
			glVertex3f(width*2.0f,height*2.0f,-5.0f);
			glVertex3f(width*2.0f,height*2.0f -130.0f,-5.0f);
			glVertex3f(0.0f,height*2.0f -130.0f,-5.0f);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

		glColor3f(1.0f,1.0f,1.0f);
		glPushMatrix();

			glTranslatef(width-450.0f,height*2.0f -50.0f,0.0f);

			glBindTexture(GL_TEXTURE_2D,_textures[TITLE]);
			glBegin(GL_QUADS);
				glTexCoord2d(0.0f,0.0f);	glVertex3f(  0.0f, 0.0f,0.0f);
				glTexCoord2d(0.0f,1.0f);	glVertex3f(  0.0f,50.0f,0.0f);
				glTexCoord2d(1.0f,1.0f);	glVertex3f(900.0f,50.0f,0.0f);
				glTexCoord2d(1.0f,0.0f);	glVertex3f(900.0f, 0.0f,0.0f);
			glEnd();

		glPopMatrix();

		glPushMatrix();

			glTranslatef(50.0f,height*2.0f -125.0f,0.0f);

			glBindTexture(GL_TEXTURE_2D,_textures[SCORE]);
			glBegin(GL_QUADS);
				glTexCoord2d(0.0f,0.0f);	glVertex3f(  0.0f, 0.0f,0.0f);
				glTexCoord2d(0.0f,1.0f);	glVertex3f(  0.0f,35.0f,0.0f);
				glTexCoord2d(1.0f,1.0f);	glVertex3f(200.0f,35.0f,0.0f);
				glTexCoord2d(1.0f,0.0f);	glVertex3f(200.0f, 0.0f,0.0f);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			_snprintf_s(buffer,sizeof(buffer),256,"%08d",_score);
			message(buffer,GLUT_BITMAP_HELVETICA_18,225,3);

			glEnable(GL_TEXTURE_2D);

		glPopMatrix();

		glPushMatrix();

			glTranslatef(width-100.0f,height*2.0f -125.0f,0.0f);

			glBindTexture(GL_TEXTURE_2D,_textures[LIFE]);
			glBegin(GL_QUADS);
				glTexCoord2d(0.0f,0.0f);	glVertex3f(  0.0f, 0.0f,0.0f);
				glTexCoord2d(0.0f,1.0f);	glVertex3f(  0.0f,35.0f,0.0f);
				glTexCoord2d(1.0f,1.0f);	glVertex3f(200.0f,35.0f,0.0f);
				glTexCoord2d(1.0f,0.0f);	glVertex3f(200.0f, 0.0f,0.0f);
			glEnd();

			glTranslatef(225.0f,-7.0f,0.0f);

			for(int i=0; i<_lives; i++) {
			
				glBindTexture(GL_TEXTURE_2D,_textures[PACMAN]);
				glBegin(GL_QUADS);
					glTexCoord2d(0.0f,0.0f);	glVertex3f( 0.0f, 0.0f,0.0f);
					glTexCoord2d(0.0f,1.0f);	glVertex3f( 0.0f,50.0f,0.0f);
					glTexCoord2d(1.0f,1.0f);	glVertex3f(50.0f,50.0f,0.0f);
					glTexCoord2d(1.0f,0.0f);	glVertex3f(50.0f, 0.0f,0.0f);
				glEnd();		

				glTranslatef(60.0f,0.0f,0.0f);
			}

		glPopMatrix();

		glPushMatrix();

			glTranslatef(width*2.0f -350.0f,height*2.0f -125.0f,0.0f);

			glBindTexture(GL_TEXTURE_2D,_textures[LEVEL]);
			glBegin(GL_QUADS);
				glTexCoord2d(0.0f,0.0f);	glVertex3f(  0.0f, 0.0f,0.0f);
				glTexCoord2d(0.0f,1.0f);	glVertex3f(  0.0f,35.0f,0.0f);
				glTexCoord2d(1.0f,1.0f);	glVertex3f(200.0f,35.0f,0.0f);
				glTexCoord2d(1.0f,0.0f);	glVertex3f(200.0f, 0.0f,0.0f);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			_snprintf_s(buffer,sizeof(buffer),256,"%d",_level);
			message(buffer,GLUT_BITMAP_HELVETICA_18,225,3);

		glPopMatrix();

	glPopMatrix();

	glEnable(GL_LIGHTING);
}

void Hud::message(std::string message, void * font, int x, int y) {

	glRasterPos2i(x,y);
	for(int i=0, j=message.length(); i < j; i++)
		glutBitmapCharacter(font,message[i]);
}

int Hud::getScore() {

	return _score;
}

int Hud::getLives() {

	return _lives;
}

void Hud::setScore(int score) {

	_score = score;
}

void Hud::setLives(int lives) {

	_lives = lives;
}

