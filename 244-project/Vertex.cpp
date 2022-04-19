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

Vertex::Vertex(int value, string airport) {
	ID = id_gen++;
	this->value = value;
	this->airport = airport;
}

int Vertex::getID() const {
	return ID;
}

int Vertex::getValue() const {
	return value;
}

string Vertex::getAirport() const {
	return airport;
}

void Vertex::print() const {
	cout << value << ", " << airport;
}
