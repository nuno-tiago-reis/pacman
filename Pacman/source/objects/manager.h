#ifndef MANAGER_H
#define MANAGER_H

/* OpenGL */
#include <GL/glut.h>

/* Standard */
#include <array>

/* Pacman - Objects */
#include "camera.h"
#include "pacman.h"
#include "ghost.h"
#include "light.h"
#include "map.h"

/* Pacman - Constants */
#include "../constants.h"

using namespace std;

class Manager {

	private:

		int _level;

		float _releaseTime[4];

		bool _ghostsCaptured[4];

	public:

		Manager();
		~Manager();

		void restart(Pacman *pacman, Ghost *ghosts, Map *map);

		void update(Pacman *pacman, Ghost *ghosts, Map *map, float elapsedTime);

		int getLevel();

		void setLevel(int level);

		void addLevel();
};

#endif