#ifndef Node_H
#define Node_H

#define UPPER 0
#define LOWER 1
#define LEFT 2
#define RIGHT 3

/* Standard */
#include <stdio.h>
#include <vector>
#include <list>

/* Pacman - Constants */
#include "../constants.h"

using namespace std;

class Node {

	private:
		/* Node Identifier*/
		int _id;
		/* Node Type*/
		int _type;
		/* Node Number of Adjacents */
		int _adjacents;
		/* Node List of Adjacent Node*/
		Node* _adjacentList[4];		

	public:

		Node();
		~Node();

		void init();

		void addAdjacent(Node *v, int position);
		void removeAdjacent(Node *v);
		Node** getAdjacentList();		

		int getId();
		int getType();
		int getAdjacents();

		void setId(int id);
		void setType(int type);
		void setAdjacents(int adjacents);
};

#endif