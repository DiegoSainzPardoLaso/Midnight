#include "Viewport.h"

// Basic Viewport Resizing
//
void fViewport::Update(Vec2 windowDimensions)
{
	glViewport(0, 0, windowDimensions.width, windowDimensions.height);
}
