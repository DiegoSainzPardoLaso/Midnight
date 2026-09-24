#include "Grid.h"

Grid* fGrid::Initialize()
{
	Grid* grid     = new Grid();
	grid->size     = 10;
	grid->units    = 1;	

	grid->material = fMaterial_OGL::Create("C:/Midnight/shaders/glsl/Grid/Grid.shader");

	return grid;
}

void fGrid::Update(Grid*& grid)
{
	fShader::Update(grid->material.shader);
}
