#include "node.h"

using namespace std;

Node::Node() {

	setAdjacents(0);
}

Node::~Node() {
}

void Node::addAdjacent(Node *v, int position) {

	_adjacents++;

	_adjacentList[position] = v;
}

void Node::removeAdjacent(Node *v) {
			
	for(int i=0; i<4; i++) 
		if(_adjacentList[i]->getId() == v->getId())
			_adjacentList[i] = NULL;
}

Node** Node::getAdjacentList() {

	return _adjacentList;
}

int Node::getId() {

	return _id;
}

int Node::getType() {

	return _type;
}

int Node::getAdjacents() {

	return _adjacents;
}

void Node::setId(int id) {

	_id = id;
}

void Node::setType(int type) {

	_type = type;
}

void Node::setAdjacents(int adjacents) {

	_adjacents = adjacents;
}