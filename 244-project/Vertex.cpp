/*
 * Vertex.cpp
 *
 *  Created on: Mar. 11, 2022
 *      Author: timothymoore
 */

#include <iostream>
#include "Vertex.h"

using namespace std;

int Vertex::id_gen = 1;

Vertex::Vertex(int value) {
	ID = id_gen++;
	this->value = value;
}

int Vertex::getID() const {
	return ID;
}

int Vertex::getValue() const {
	return value;
}

void Vertex::print() const {
	cout << value;
}
