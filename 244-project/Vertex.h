/*
 * Vertex.h
 *
 *  Created on: Mar. 11, 2022
 *      Author: timothymoore
 */

#ifndef VERTEX_H_
#define VERTEX_H_
#include <iostream>

using namespace std;

class Vertex {
private:
	static int id_gen;
	int ID;
	int value;
public:
	Vertex(int = 0);
	int getID() const;
	int getValue() const;
	void print() const;
};


#endif /* VERTEX_H_ */
