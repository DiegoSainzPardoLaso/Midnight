#pragma once


#include <iostream>

#include "../GUI/MGUI.h"
#include "../Rendering/Material.h"
#include "../Rendering/OpenGL/OGLUtilities.hpp"

#include "../Time/Time.h"
#include "../Inputs/Inputs.h"
#include "../Types/Mesh.h"
#include "../Types/Vertex.h"
#include "../Types/SSTransform.h"

#include "../Engine/EngineConfig.h"



inline const char* CONSOLE_COMMANDS[20] =
{
	"dir",
	"play_animation"
};

enum ConsoleState
{
	CLOSED,
	CLOSING,
	OPENING,
	OPEN,	
};

struct Console
{
	const char*   command;
	Text*         inputText;
	
	GUIMesh       mesh;
	SS_Transform  transform;
	Material_OGL      material;

	ConsoleState  state;

	float         displayAlpha;
	float         openingSpeed;	
	float         closingSpeed;
};

namespace fConsole
{
	Console* Initialize();
	void     Update(Console*& console, Vec2 windowDimensions);


	namespace Internal
	{		
		void StickConsoleToWindowEdge(Console*& console, Vec2& windowDimensions);
		void DisplayConsole(Console*& console);
		void InputCommand(Console*& console);


		#define CONSOLE_BACK_BUFFER_HEIGHT		         HEIGHT / 2.0f - 43.0f
		#define CONSOLE_DECORATION_LINE_SEPARATOR        3.0f
		#define CONSOLE_INPUT_BUFFER_HEIGHT		         40.0f
		#define CONSOLE_HEIGHT				             CONSOLE_BACK_BUFFER_HEIGHT + CONSOLE_DECORATION_LINE_SEPARATOR + CONSOLE_INPUT_BUFFER_HEIGHT

		#define CONSOLE_OPEN_SMALL_HEIGHT				 HEIGHT / 2.0f - 43.0f
		#define CONSOLE_OPEN_BIG_HEIGHT				     HEIGHT / 1.5f - 43.0f

		#define CONSOLE_MESH_VERTEX_COUNT				 12
		#define CONSOLE_MESH_INDEX_COUNT				 18

		#define BACK_BUFFER_COLOR						 0.13f,  0.12f,  0.20f
		#define DECORATION_LINE_COLOR					 0.20f,  0.20f,  0.20f
		#define INPUT_BUFFER_COLOR					     0.01f,  0.01f,  0.01f		
		
		inline gVertex consoleMesh[CONSOLE_MESH_VERTEX_COUNT] =
		{
			{  0.0f ,   0.0f,																						0.0f,      BACK_BUFFER_COLOR,      0.0f,  0.0f }, // Body // Top    Left				0
			{  WIDTH,   0.0f,																						0.0f,      BACK_BUFFER_COLOR,      0.0f,  0.0f }, // Body // Top    Right				1
			{  0.0f ,   CONSOLE_BACK_BUFFER_HEIGHT,																	0.0f,      BACK_BUFFER_COLOR,      0.0f,  0.0f }, // Body // Bottom Left				2
			{  WIDTH,   CONSOLE_BACK_BUFFER_HEIGHT,																	0.0f,      BACK_BUFFER_COLOR,      0.0f,  0.0f }, // Body // Bottom Right				3

			{  0.0f ,   CONSOLE_BACK_BUFFER_HEIGHT,																	0.0f,      DECORATION_LINE_COLOR,  0.0f,  0.0f }, // Line // Bottom Left				4
			{  WIDTH,   CONSOLE_BACK_BUFFER_HEIGHT,																	0.0f,      DECORATION_LINE_COLOR,  0.0f,  0.0f }, // Line // Bottom Right				5
			{  0,       CONSOLE_BACK_BUFFER_HEIGHT + CONSOLE_DECORATION_LINE_SEPARATOR,								0.0f,      DECORATION_LINE_COLOR,  0.0f,  0.0f }, // Line // Top Left					6
			{  WIDTH,   CONSOLE_BACK_BUFFER_HEIGHT + CONSOLE_DECORATION_LINE_SEPARATOR,								0.0f,      DECORATION_LINE_COLOR,  0.0f,  0.0f }, // Line // Top Right					7

			{  0.0f,    CONSOLE_BACK_BUFFER_HEIGHT+CONSOLE_DECORATION_LINE_SEPARATOR,								0.0f,      INPUT_BUFFER_COLOR,     0.0f,  0.0f }, // Input Field // Top Left			8
			{  WIDTH,   CONSOLE_BACK_BUFFER_HEIGHT+CONSOLE_DECORATION_LINE_SEPARATOR,								0.0f,      INPUT_BUFFER_COLOR,     0.0f,  0.0f }, // Input Field // Top Right			9
			{  0.0f,    CONSOLE_BACK_BUFFER_HEIGHT+CONSOLE_DECORATION_LINE_SEPARATOR+CONSOLE_INPUT_BUFFER_HEIGHT,   0.0f,      INPUT_BUFFER_COLOR,     0.0f,  0.0f }, // Input Field // Bottom Left			10
			{  WIDTH,   CONSOLE_BACK_BUFFER_HEIGHT+CONSOLE_DECORATION_LINE_SEPARATOR+CONSOLE_INPUT_BUFFER_HEIGHT,   0.0f,      INPUT_BUFFER_COLOR,     0.0f,  0.0f }, // Input Field // Bottom Right		11

		};

		inline int consoleMeshIndices[CONSOLE_MESH_INDEX_COUNT] =
		{
			0, 1, 2,
			1, 2, 3,

			4, 5, 6,
			6, 5, 7,

			8, 9, 10,
			10, 9, 11
		};
		
	}

}