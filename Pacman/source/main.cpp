/************************************************************************************************************************/
/*																														*/
/*										Pacman 3D - Computação Gráfica 2011/2012										*/
/*																														*/
/*									OpenGL Project developed with Visual Studio 2010									*/
/*																														*/
/************************************************************************************************************************/

/* OpenGL */
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

/* Standard */
#include <iostream>
#include <sstream>
#include <string>

/* FMOD */
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>

/* Objects */
#include "objects/manager.h"
#include "objects/camera.h"
#include "objects/object.h"
#include "objects/pacman.h"
#include "objects/ghost.h"
#include "objects/explosion.h"
#include "objects/light.h"
#include "objects/map.h"
#include "objects/hud.h"

/* Constants */
#include "constants.h"

/* Game Entity Global Variables */
Hud hud;
Map map;
Light light;
Explosion explosion;
Camera camera;
Pacman pacman;
Ghost ghosts[4];
Manager manager;

int frameCount;
float testTime;

/* Viewport Handling Global Variables */
int width = BLOCK_SIZE*MAP_X/2;
int height = BLOCK_SIZE*MAP_Y/2;

/* Time Handling Global Variables */
int startTime = 0;

float time = 0;
float elapsedTime = 0;

/* Game Start Flag */
int start = 0;

/* Keyboard Handling Global Variables */
int pressedKey = 0;
bool specialKey = false;
bool normalKey = false;
bool keyboardEnabled  = true;

/* Sound System Handling Global Variables */
FMOD::System *fmodSystem;
FMOD::Channel* channel[32];
FMOD::Sound *beginning, *eating, *eatingGhosts, *siren, *death;

void FmodErrorCheck(FMOD_RESULT result)	 {

	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n",result,FMOD_ErrorString(result));
		exit(-1);
	}
}

void keyOperations () {  

	int rotation = camera.getRotation();
	array<int,3> velocity = {0,0,0};

	if(!keyboardEnabled)
		return;	

	if(specialKey) {
	
		switch(pressedKey) {
		
			case GLUT_KEY_LEFT:	if(camera.getMode() == 6) {
									velocity[0] = (int)(-VELOCITY*cos(rotation*PI_RAD));
									velocity[1] = (int)(-VELOCITY*sin(rotation*PI_RAD));
									pacman.setNewVelocity(velocity);
								}
								else {	
									velocity[0] = -VELOCITY;
									velocity[1] = 0;
									pacman.setNewVelocity(velocity);
								}
								break;
		
			case GLUT_KEY_RIGHT:if(camera.getMode() == 6) {
									velocity[0] = (int)(VELOCITY*cos(rotation*PI_RAD));
									velocity[1] = (int)(VELOCITY*sin(rotation*PI_RAD));
									pacman.setNewVelocity(velocity);
								}
								else {
									velocity[0] = VELOCITY;
									velocity[1] = 0;
									pacman.setNewVelocity(velocity);
								}
								break;

			case GLUT_KEY_UP:	if(camera.getMode() == 6) {
									velocity[0] = (int)(-VELOCITY*sin(rotation*PI_RAD));
									velocity[1] = (int)(VELOCITY*cos(rotation*PI_RAD));
									pacman.setNewVelocity(velocity);
								}
								else {
									velocity[0] = 0;
									velocity[1] = VELOCITY;
									pacman.setNewVelocity(velocity);
								}
								break;

			case GLUT_KEY_DOWN:	if(camera.getMode() == 6) {
									velocity[0] = (int)(VELOCITY*sin(rotation*PI_RAD));
									velocity[1] = (int)(-VELOCITY*cos(rotation*PI_RAD));
									pacman.setNewVelocity(velocity);
								}
								else {
									velocity[0] = 0;
									velocity[1] = -VELOCITY;
									pacman.setNewVelocity(velocity);
								}
								break;

			case GLUT_KEY_F1:	camera.setMode(0);
								camera.reshape(width,height);
								break;
			case GLUT_KEY_F2:	camera.setMode(1);
								camera.reshape(width,height);
								break;
			case GLUT_KEY_F3:	camera.setMode(2);
								camera.reshape(width,height);
								break;
			case GLUT_KEY_F4:	camera.setMode(3);
								camera.reshape(width,height);
								break;
			case GLUT_KEY_F5:	camera.setMode(4);
								camera.reshape(width,height);
								break;
			case GLUT_KEY_F6:	camera.setMode(5);
								camera.reshape(width,height);
								break;
			case GLUT_KEY_F7:	camera.setMode(6);
								camera.reshape(width,height);
								break;
		}
	}
	if(normalKey) {

		switch(pressedKey) {

			case 'a':	break;
			case 'd':	break;
			case 'w':	break;
			case 's':	break;

			case '1':	light.setMode(0);
						pacman.setModel(0);
						break;
			case '2':	light.setMode(1);
						pacman.setModel(1);
						break;
			case GLUT_KEY_ESC:	exit(1);
								break;
		}
	}
}

void keyPressed (unsigned char key, int x, int y) {  

	normalKey = true;
	pressedKey = key;

	keyOperations();
}  
  
void keyUp (unsigned char key, int x, int y) {  

	normalKey = false;
}

void keySpecialPressed (int key, int x, int y) {  

	specialKey = true;
	pressedKey = key; 

	keyOperations();
}  
  
void keySpecialUp (int key, int x, int y) {  
	
	specialKey = false;
}

void myReshape(int w, int h) {

	camera.reshape(width = w,height = h);
}

void myTimer(int value) {

	elapsedTime = (glutGet(GLUT_ELAPSED_TIME) - startTime) / 1000.0f;
	startTime = glutGet(GLUT_ELAPSED_TIME);
	time += elapsedTime;

	if(testTime > 1) {
		
		std::ostringstream oss;
		oss << "Frame Count: " << frameCount << " FPS @ (" << width << "x" << height << ")";
		std::string s = oss.str();

		glutSetWindowTitle(s.c_str());

		frameCount = 0;
		testTime = 0;
	}
	else {

		frameCount++;
		testTime += elapsedTime;
	}

	/* After initial sound stops playing */
	if(start == 2) {

		if(pacman.isAlive()) {

			/* Verify if Pacman can continue with the current velocity */
			map.update(&pacman);
			/* Update the Pacman's Position */
			pacman.update(elapsedTime);
			/* Update the Camera's Position */
			camera.update(&pacman);
			/* Update the Ghosts's Position */
			for(int i=0; i<4; i++)
				ghosts[i].update(&pacman);
			/* Update the HUD information */
			hud.update(&pacman,&manager);
			/* Update the Light Position and Direction */
			light.update(&pacman);

			/* Update the Game Manager and the Explosion Flag */
			manager.update(&pacman,ghosts,&map,elapsedTime);

			/* Initialize Explosion if Pacman dies */
			if (!pacman.isAlive()) {

				explosion.init(&pacman);
				channel[1]->setPaused(true);
				fmodSystem->playSound(FMOD_CHANNEL_FREE, death, false, &channel[2]);
			}
		}
		else {
	
			/* Update the Explosion Particles */
			explosion.update(&pacman,elapsedTime);

			/* Reset the Game once the Explosion is over */
			if(explosion.getTime() < 0)
				manager.update(&pacman,ghosts,&map,elapsedTime);
				channel[1]->setPaused(false);
		}
	}

	glutPostRedisplay();
	glutTimerFunc(value, myTimer,1);
}

void myIdle() {

	//glutPostRedisplay();
	fmodSystem->update();
}

void myDisplay() {

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/* Draw the HUD*/
	hud.draw(width,height);
	/* Draw the Camera */
	camera.draw(width,height);	
	/* Draw the Lights */
	light.draw();
	/* Draw the Map */
	map.draw();
	/* Draw Pacman */
	pacman.draw();
	/* Draw the Ghosts */
	for(int i=0; i<4; i++)
		ghosts[i].draw();

	/* Draw the Explosion */
	explosion.draw();

	glutSwapBuffers();

	if(start == 0) {

		start = 1;
	
		fmodSystem->playSound(FMOD_CHANNEL_FREE, beginning, false, &channel[0]);
	}
	else if(time > 10 && start == 1) {

		start = 2;

		fmodSystem->playSound(FMOD_CHANNEL_FREE, siren, false, &channel[1]);
	}
}

void main(int argc, char** argv) {

	printf("Loading...\n");

	/* FMOD Sound System Initialization */
	FMOD::System_Create(&fmodSystem);
	fmodSystem->init(32,FMOD_INIT_NORMAL,0);

	/* FMOD Sound Loading */
	fmodSystem->createSound("sounds/start.mp3", FMOD_HARDWARE, 0, &beginning);
	beginning->setMode(FMOD_LOOP_OFF);

	fmodSystem->createSound("sounds/eating.mp3", FMOD_HARDWARE, 0, &eating);
	eating->setMode(FMOD_LOOP_NORMAL);

	fmodSystem->createSound("sounds/eating_ghosts.mp3", FMOD_HARDWARE, 0, &eatingGhosts);
	eatingGhosts->setMode(FMOD_LOOP_OFF);

	fmodSystem->createSound("sounds/death_explosion.mp3", FMOD_HARDWARE, 0, &death);
	//fmodSystem->createSound("sounds/death_original.mp3", FMOD_HARDWARE, 0, &death);
	death->setMode(FMOD_LOOP_OFF);

	fmodSystem->createSound("sounds/siren.mp3", FMOD_HARDWARE, 0, &siren);
	//fmodSystem->createSound("sounds/pacman_dnb.wav", FMOD_HARDWARE, 0, &siren);
	//fmodSystem->createSound("sounds/pacmans_revenge.wav", FMOD_HARDWARE, 0, &siren);
	siren->setMode(FMOD_LOOP_NORMAL);

	/* Glut Initialization */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize (width, height+60);
	glutInitWindowPosition (-1, -1);
	glutCreateWindow("Pacman - CG 2012");

	/* Glut State Initialization */
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/* HUD Initialization */
	hud.init();
	/* Ghost Movement Graph Initialization */
	ghosts[0].initGraph(&map);
	/* Release Red Ghost */
	ghosts[0].setReleased(true);
	
	/* Glut Keyboard Functions Initialization */
	glutKeyboardFunc(keyPressed); 
	glutKeyboardUpFunc(keyUp); 
	glutSpecialFunc(keySpecialPressed);
	glutSpecialUpFunc(keySpecialUp);
	/* Glut Display / Reshape Functions Initialization */
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);	
	/* Glut Timer / Idle Functions Initialization */
	myTimer(40);
	glutIdleFunc(myIdle);

	/* Game Timer Initialization */
	startTime = glutGet(GLUT_ELAPSED_TIME);

	/* Glut Main Loop */
	glutMainLoop();

	/* Sound System Shutdown */
	beginning->release();
	eating->release();
	eatingGhosts->release();
	death->release();
	siren->release();

	fmodSystem->close();
	fmodSystem->release();
}