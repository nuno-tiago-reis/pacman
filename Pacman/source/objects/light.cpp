#include "light.h"

using namespace std;

Light::Light() {

	_globalAmbient[0] = 0.2f;
	_globalAmbient[1] = 0.2f;
	_globalAmbient[2] = 0.2f;
	_globalAmbient[3] = 1.0f;

	_ambientLight0[0] = 0.5f;
	_ambientLight0[1] = 0.5f;
	_ambientLight0[2] = 0.5f;
	_ambientLight0[3] = 1.0f;

	_diffuseLight0[0] = 1.0f;
	_diffuseLight0[1] = 1.0f;
	_diffuseLight0[2] = 1.0f;
	_diffuseLight0[3] = 1.0f;

	_specularLight0[0] = 1.0f;
	_specularLight0[1] = 1.0f;
	_specularLight0[2] = 1.0f;
	_specularLight0[3] = 1.0f;

	_ambientLight1[0] = 0.3f;
	_ambientLight1[1] = 0.3f;
	_ambientLight1[2] = 0.3f;
	_ambientLight1[3] = 1.0f;

	_diffuseLight1[0] = 0.75f;
	_diffuseLight1[1] = 0.75f;
	_diffuseLight1[2] = 0.75f;
	_diffuseLight1[3] = 1.0f;

	_specularLight1[0] = 0.75f;
	_specularLight1[1] = 0.75f;
	_specularLight1[2] = 0.75f;
	_specularLight1[3] = 1.0f;

	_positionLight0[0] = 0.0f;
	_positionLight0[1] =-1.0f;
	_positionLight0[2] = 1.0f;
	_positionLight0[3] = 0.0f;

	_positionLight2[0] = 26.0f*BLOCK_SIZE + BLOCK_SIZE/2.0f;
	_positionLight2[1] = 27.0f*BLOCK_SIZE + BLOCK_SIZE/2.0f;
	_positionLight2[2] = 150.0f;
	_positionLight2[3] = 1.0f;

	_directionLight2[0] = 0.0f;
	_directionLight2[1] = 0.0f;
	_directionLight2[2] =-1.0f;
	_directionLight2[3] = 1.0f;

	_positionLight3[0] = 26.0f*BLOCK_SIZE + BLOCK_SIZE/2.0f;
	_positionLight3[1] = 8.0f*BLOCK_SIZE + BLOCK_SIZE/2.0f;
	_positionLight3[2] = 150.0f;
	_positionLight3[3] = 1.0f;

	_directionLight3[0] = 0.0f;
	_directionLight3[1] = 0.0f;
	_directionLight3[2] =-1.0f;
	_directionLight3[3] = 1.0f;

	_positionLight4[0] = BLOCK_SIZE + BLOCK_SIZE/2.0f;
	_positionLight4[1] = 27.0f*BLOCK_SIZE + BLOCK_SIZE/2.0f;
	_positionLight4[2] = 150.0f;
	_positionLight4[3] = 1.0f;

	_directionLight4[0] = 0.0f;
	_directionLight4[1] = 0.0f;
	_directionLight4[2] =-1.0f;
	_directionLight4[3] = 1.0f;

	_positionLight5[0] = BLOCK_SIZE + BLOCK_SIZE/2.0f;
	_positionLight5[1] = 8.0f*BLOCK_SIZE + BLOCK_SIZE/2.0f;
	_positionLight5[2] = 150.0f;
	_positionLight5[3] = 1.0f;

	_directionLight5[0] = 0.0f;
	_directionLight5[1] = 0.0f;
	_directionLight5[2] =-1.0f;
	_directionLight5[3] = 1.0f;
}

Light::~Light() {

}

void Light::update(Pacman *pacman) {

	array<int,3> position = pacman->getPosition();

	for(int i=0; i<3; i++)
		_positionLight1[i] = (GLfloat)position[i];

	setRotation(pacman->getRotation());

	_directionLight1[0] = (GLfloat)cos((90+_rotationLight1)*PI_RAD);
	_directionLight1[1] = (GLfloat)sin((90+_rotationLight1)*PI_RAD);
	_directionLight1[2] = -0.5f;
	_directionLight1[3] = 1.0f;

	//printf("direction: %f %f %f\n",_directionLight1[0],_directionLight1[1],_directionLight1[2]);

	_positionLight1[0] -= (GLfloat)sin(_rotationLight1*PI_RAD);
	_positionLight1[1] += (GLfloat)cos(_rotationLight1*PI_RAD);
	_positionLight1[2] += 100.0f;
	_positionLight1[3] = 1.0f;
}

void Light::draw() {

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);

	switch(_mode) {

		case 0:	glEnable(GL_LIGHT0);
				glLightfv(GL_LIGHT0,GL_AMBIENT,_ambientLight0);
				glLightfv(GL_LIGHT0,GL_DIFFUSE,_diffuseLight0);
				glLightfv(GL_LIGHT0,GL_DIFFUSE,_specularLight0);
				glLightfv(GL_LIGHT0,GL_POSITION,_positionLight0);
				break;

		case 1:	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,_globalAmbient);

				/* Pacmans HeadLight */
				glEnable(GL_LIGHT1);
				glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.000001f);
				glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.00000005f);
				glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.000005f);
				glLighti(GL_LIGHT1,GL_SPOT_CUTOFF,45);
				glLightfv(GL_LIGHT1,GL_AMBIENT,_ambientLight1);
				glLightfv(GL_LIGHT1,GL_DIFFUSE,_diffuseLight1);
				glLightfv(GL_LIGHT1,GL_DIFFUSE,_specularLight1);
				glLightfv(GL_LIGHT1,GL_POSITION,_positionLight1);
				glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,_directionLight1);

				/* Ball Light 1 */
				glEnable(GL_LIGHT2);
				glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.001f);
				glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0005f);
				glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.00005f);
				glLighti(GL_LIGHT2,GL_SPOT_CUTOFF,45);
				glLightfv(GL_LIGHT2,GL_AMBIENT,_ambientLight1);
				glLightfv(GL_LIGHT2,GL_DIFFUSE,_diffuseLight1);
				glLightfv(GL_LIGHT2,GL_DIFFUSE,_specularLight1);
				glLightfv(GL_LIGHT2,GL_POSITION,_positionLight2);
				glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,_directionLight2);

				/* Ball Light 2 */
				glEnable(GL_LIGHT3);
				glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.001f);
				glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.0005f);
				glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.00005f);
				glLighti(GL_LIGHT3,GL_SPOT_CUTOFF,45);
				glLightfv(GL_LIGHT3,GL_AMBIENT,_ambientLight1);
				glLightfv(GL_LIGHT3,GL_DIFFUSE,_diffuseLight1);
				glLightfv(GL_LIGHT3,GL_DIFFUSE,_specularLight1);
				glLightfv(GL_LIGHT3,GL_POSITION,_positionLight3);
				glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,_directionLight3);

				/* Ball Light 3 */
				glEnable(GL_LIGHT4);
				glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.001f);
				glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.0005f);
				glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.00005f);
				glLighti(GL_LIGHT4,GL_SPOT_CUTOFF,45);
				glLightfv(GL_LIGHT4,GL_AMBIENT,_ambientLight1);
				glLightfv(GL_LIGHT4,GL_DIFFUSE,_diffuseLight1);
				glLightfv(GL_LIGHT4,GL_DIFFUSE,_specularLight1);
				glLightfv(GL_LIGHT4,GL_POSITION,_positionLight4);
				glLightfv(GL_LIGHT4,GL_SPOT_DIRECTION,_directionLight4);

				/* Ball Light 4 */
				glEnable(GL_LIGHT5);
				glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.001f);
				glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.0005f);
				glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.00005f);
				glLighti(GL_LIGHT5,GL_SPOT_CUTOFF,45);
				glLightfv(GL_LIGHT5,GL_AMBIENT,_ambientLight1);
				glLightfv(GL_LIGHT5,GL_DIFFUSE,_diffuseLight1);
				glLightfv(GL_LIGHT5,GL_DIFFUSE,_specularLight1);
				glLightfv(GL_LIGHT5,GL_POSITION,_positionLight5);
				glLightfv(GL_LIGHT5,GL_SPOT_DIRECTION,_directionLight5);
				break;
	}
}

int Light::getMode() {

	return _mode;
}

int Light::getRotation() {

	return _rotationLight1;
}

void Light::setMode(int mode) {

	_mode = mode;
}

void Light::setRotation(int rotation) {

	_rotationLight1 = rotation;
}