/*
 * Vertex.h
 *
 *  Created on: Mar. 11, 2022
 *      Author: timothymoore
 */

#ifndef VERTEX_H_
#define VERTEX_H_
#include <iostream>
#include <string>

using namespace std;

class Vertex {
private:
	static int id_gen;
	int ID;
	int value;
	string airport;
public:
	Vertex(int = 0, string = "");
	int getID() const;
	int getValue() const;
	string getAirport() const;
	void print() const;
};


#endif /* VERTEX_H_ */
