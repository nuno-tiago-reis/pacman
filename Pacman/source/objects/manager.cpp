#include "manager.h"

using namespace std;

Manager::Manager() {

	_level = 1;

	for(int i=0; i<4; i++)
		_releaseTime[i] = (GLfloat)(10.0f*i);
}

Manager::~Manager() {

}

void Manager::restart(Pacman *pacman, Ghost *ghosts, Map *map) {

	/* In case the Level was cleared or Gameover, Reinitialize the Map */
	if(map != NULL)
		map->init();
	
	/* Reinitialize Pacman's Position and Velocity */
	pacman->init();
	/* Reinitialize Ghosts' Position and Velocity */
	for(int j=0; j<4; j++)
		ghosts[j].init();

	/* Release the first Ghost from it's cage */
	ghosts[0].setReleased(true);
	/* Reset the Release timer */
	for(int i=0; i<4; i++) {
		_releaseTime[i] = (GLfloat)(10.0f*i);
		_ghostsCaptured[i] = 0;
	}
}

void Manager::update(Pacman *pacman, Ghost *ghosts, Map *map, float elapsedTime) {

	/* If Pacman ate all the Balls */
	if(map->getBallCount() == 0) {

		restart(pacman,ghosts,map);

		addLevel();
			
		return;
	}

	if(!pacman->isAlive()) {

		if(pacman->getLives()-1 == 0) {

			/* Reset the Game */
			restart(pacman,ghosts,map);

			setLevel(1);
			pacman->setScore(0);
			pacman->setLives(3);
		}
		else {

			/* Reset Current Level */
			restart(pacman,ghosts,NULL);

			/* Decrement Pacmans Lives */
			pacman->setLives(pacman->getLives()-1);
		}

		return;
	}

	for(int i=0; i<4; i++) {

		/* If Pacman ate a Big Ball, change Ghosts to Scatter Mode and Swap their Velocity */
		if(pacman->getMode() != ghosts[i].getMode())
			ghosts[i].adjustVelocity();

		/* If the Ghost is inside the Cage */
		if(!ghosts[i].getReleased()) {
			
			_releaseTime[i] -= elapsedTime;
		
			if(_releaseTime[i] < 0) {

				_ghostsCaptured[i] = false;
				ghosts[i].setReleased(true);
			}
		}
		else 
			ghosts[i].setMode(pacman->getMode());

		switch(ghosts[i].caughtPacman(pacman)) {
		
			case 1:	pacman->setDead();
					break;
					
			case 2:	int score = GHOST_SCORE/2;
				
					_ghostsCaptured[i] = true;
					_releaseTime[i] = 5;

					for(int j=0; j<4; j++)
						if(_ghostsCaptured[j])
							score *= 2;

					ghosts[i].init();

					pacman->addScore(score);
					break;
		}
	}
}

int Manager::getLevel() {

	return _level;
}

void Manager::setLevel(int level) {

	_level = level;
}

void Manager::addLevel() {

	_level++;
}