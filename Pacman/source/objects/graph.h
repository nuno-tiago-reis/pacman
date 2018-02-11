#ifndef GRAPH_H
#define GRAPH_H

/* Standard */
#include <stdio.h>
#include <list>
#include <set>

/* Pacman - Objects */
#include "node.h"
#include "map.h"

/* Pacman - Constants */
#include "../constants.h"

using namespace std;

class Graph {

	private: 
		/** Graph Node List*/
		Node _nodeList[NODE_NUMBER];
		/** Graph number of Node*/
		int _nodeNumber;
		/** Graph number of Edges*/
		int _edgeNumber;

	public:

		Graph();
		~Graph();

		void init(Map *map);

		Node* getNode(int id);

		void setNode(int id, int type);
};

#endif