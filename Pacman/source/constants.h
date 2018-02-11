#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Map Size Constants */
#define MAP_X 28
#define MAP_Y 31
#define BLOCK_SIZE 50

/* Object Velocity Constant */
#define VELOCITY 10

/* Ghost Release Time Constants */
#define GHOST_TIME_0 0.0f
#define GHOST_TIME_1 5.0f
#define GHOST_TIME_2 10.0f

/* Trigonometric Constants */
#define PI 3.14159265f
#define PI_RAD PI/180.0f
#define RAD_PI 180.0f/PI

/* Graph Handling Constants */
#define NODE_NUMBER MAP_X*MAP_Y
#define EDGE_NUMBER 0
/* Node Identifying Constant */
#define GET_NODE(X,Y) X*MAP_X+Y

/* Map Model Flag */
#define USING_MODELS false
/* Map Ball Number */
#define BALL_NUMBER 244
/* Ball Score Constant */
#define BALL_SCORE 10
#define BIG_BALL_SCORE 50
/* Ghost Score Constant */
#define GHOST_SCORE 200

/* Particle System Constants */
#define PARTICLES 1000
/* Sine & Cosine Variation Constants */
#define PHI 2.0f*PI/PARTICLES
#define THETA PI/PARTICLES*10.0f
/* Explosion Type Flag */
#define EXPLOSION_1 false
#define EXPLOSION_2 false
#define EXPLOSION_3 true
/* Explosion Fragment Size */
#define FRAGMENT_SIZE 7.5

#define GLUT_KEY_ESC 27

#endif