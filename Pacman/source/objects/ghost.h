#ifndef GHOST_H
#define GHOST_H

/* Pacman - Objects */
#include "object.h"
#include "pacman.h"
#include "graph.h"
#include "map.h"

using namespace std;

class Ghost: public Object {

	private:

		bool _released;

		int _id;
		int _type;

	public:

		Ghost();
		~Ghost();

		void init();
		void initGraph(Map *map);

		void adjustVelocity();

		void calculateMovement(Pacman *pacman);
		void continueMovement(int direction, int node);
		bool newMovement(int direction1, int direction2, int node);		

		int caughtPacman(Pacman *pacman);

		void update(Pacman *pacman);
		void draw();

		int getId();
		bool getReleased();
		array<int,3> getVelocity();

		void setId(int id);
		void setReleased(bool release);
		void setVelocity(array<int,3> velocity);

		void setMovement(int direction);
};

#endif