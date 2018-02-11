#include "graph.h"

using namespace std;

Graph::Graph() {

	_edgeNumber = EDGE_NUMBER;
	_nodeNumber = NODE_NUMBER;
}

Graph::~Graph() {

}
	
void Graph::init(Map *map) {

	/* Initialize Graph Nodes*/
	for(int j=0; j<MAP_Y; j++)
		for(int i=0; i<MAP_X; i++)
			setNode(i+j*MAP_X,map->getQuadric(j,i)->getType());

	/* Initialize Graph Edges*/
	int k;

	for(int j=1; j<MAP_Y-1; j++)
		for(int i=1; i<MAP_X-1; i++) {

			k = (i+1) + j*MAP_X;
	
			if(_nodeList[k].getType() != 1 && _nodeList[k].getType() != 4)
				_nodeList[i+j*MAP_X].addAdjacent(&_nodeList[k],RIGHT);

			k = (i-1) + j*MAP_X;
	
			if(_nodeList[k].getType() != 1 && _nodeList[k].getType() != 4)
				_nodeList[i+j*MAP_X].addAdjacent(&_nodeList[k],LEFT);

			k = i + (j+1)*MAP_X;
	
			if(_nodeList[k].getType() != 1 && _nodeList[k].getType() != 4)
				_nodeList[i+j*MAP_X].addAdjacent(&_nodeList[k],UPPER);

			k = i + (j-1)*MAP_X;
	
			if(_nodeList[k].getType() != 1 && _nodeList[k].getType() != 4)
				_nodeList[i+j*MAP_X].addAdjacent(&_nodeList[k],LOWER);
		}
}

Node* Graph::getNode(int id) {

	return &_nodeList[id];
}

void Graph::setNode(int id, int type) {

	_nodeList[id].setId(id);
	_nodeList[id].setType(type);
}