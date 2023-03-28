#pragma once

#include "Mesh.h"

class Torus : public Mesh {

private:

	int gDu = 36;
	int gDv = 36;

public:

	Torus();
	void generate();

};