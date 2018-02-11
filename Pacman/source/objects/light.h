#ifndef LIGHT_H
#define LIGHT_H

/* OpenGL */
#include <GL/glut.h>

/* Pacman - Objects */
#include "pacman.h"

/* Pacman - Constants */
#include "../constants.h"

using namespace std;

class Light {

	private:

		int _mode;

		float _globalAmbient[4];
		/* Light0 - Directional Light */
		float _ambientLight0[4];
		float _diffuseLight0[4];
		float _specularLight0[4];
		float _positionLight0[4];
		/* Light1 - SpotLight */
		int _rotationLight1;
		float _ambientLight1[4];
		float _diffuseLight1[4];
		float _specularLight1[4];
		float _positionLight1[4];
		float _directionLight1[4];
		/* Light2 - SpotLight */
		float _positionLight2[4];
		float _directionLight2[4];
		/* Light3 - SpotLight */
		float _positionLight3[4];
		float _directionLight3[4];
		/* Light4 - SpotLight */
		float _positionLight4[4];
		float _directionLight4[4];
		/* Light5 - SpotLight */
		float _positionLight5[4];
		float _directionLight5[4];
	public:

		Light();
		~Light();

		void update(Pacman *pacman);
		void draw();

		int getMode();
		int getRotation();

		void setMode(int mode);
		void setRotation(int rotation);
};

#endif