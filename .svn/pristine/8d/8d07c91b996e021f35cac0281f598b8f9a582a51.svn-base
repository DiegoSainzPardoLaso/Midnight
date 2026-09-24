#include "Console.h"

Console* fConsole::Initialize()
{
	Console* console      = reinterpret_cast<Console*>(malloc(sizeof(Console)));		
	console->command      = "no_command";
	console->mesh         = fMesh::Create<GUIMesh, gVertex>(CONSOLE_MESH_VERTEX_COUNT, CONSOLE_MESH_INDEX_COUNT, Internal::consoleMesh, Internal::consoleMeshIndices);
	console->material     = fMaterial_OGL::Create("C:/Midnight/shaders/glsl/console.shader");
	console->transform    = { 0, -CONSOLE_HEIGHT, WIDTH, HEIGHT };
	console->openingSpeed = 4.0f;	
	console->closingSpeed = 5.0f;
	console->displayAlpha = 0.0f;
	console->state		  = ConsoleState::CLOSED;
	

	int id = 0;
	OGL_Util::Create_VAO_VBO_EBO
	(
		id, 
		console->mesh.VAO,    
		console->mesh.VBO,    
		console->mesh.EBO,    
		console->mesh.vertices, 
		console->mesh.total_vertices_byte_size,  
		console->mesh.indices,
		console->mesh.index_count, 
		OGL_Util::Integrants::POSITION_COLOR_UV, 
		GL_DYNAMIC_DRAW
	);

	return console;
}

//
// @todo 
// 1. Move The edges of the console to the left and right window edge __DONE__
// 2. Toggle the console visibility									  __DONE__					  
// 3. Input Commands
// 4. Accept Input
// 5. Add Command to command queue
//
void fConsole::Update(Console*& console, Vec2 wDim)
{
	fShader::Update(console->material.shader);
	
	Internal::StickConsoleToWindowEdge(console, wDim);
	Internal::DisplayConsole(console);
}

void fConsole::Internal::StickConsoleToWindowEdge(Console*& console, Vec2& window)
{	
	console->mesh.vertices[1].position.x  = (float)window.width;
	console->mesh.vertices[3].position.x  = (float)window.width;
									    
	console->mesh.vertices[5].position.x  = (float)window.width;
	console->mesh.vertices[7].position.x  = (float)window.width;

	console->mesh.vertices[9].position.x  = (float)window.width;
	console->mesh.vertices[11].position.x = (float)window.width;

	console->transform.width = (float)window.width;

	OGL_Util::UpdateVBO(GL_ARRAY_BUFFER, console->mesh.total_vertices_byte_size, console->mesh.VBO, console->mesh.vertices, GL_DYNAMIC_DRAW);
}

void fConsole::Internal::DisplayConsole(Console*& console)
{
	static bool canIPressTheKeyAgain = false;

	if (Input::Key_Tilde && canIPressTheKeyAgain && console->state == ConsoleState::CLOSED)
	{
		console->state = ConsoleState::OPENING;						
		canIPressTheKeyAgain = false;
	}
	
	if (Input::Key_Tilde && canIPressTheKeyAgain && console->state == ConsoleState::CLOSING)
	{
		console->state = ConsoleState::OPENING;
		console->displayAlpha = 1.0f - console->displayAlpha;
		canIPressTheKeyAgain = false;
	}
	
	if (Input::Key_Tilde && canIPressTheKeyAgain && console->state == ConsoleState::OPEN)
	{
		console->state = ConsoleState::CLOSING;		
		canIPressTheKeyAgain = false;
	}
	
	if (Input::Key_Tilde && canIPressTheKeyAgain && console->state == ConsoleState::OPENING)
	{
		console->state = ConsoleState::CLOSING;
		console->displayAlpha = 1.0f - console->displayAlpha;
		canIPressTheKeyAgain = false;
	}
	
	
	if (!Input::Key_Tilde)
	{
		canIPressTheKeyAgain = true;  
	}	
 
	if (console->state == ConsoleState::OPENING)
	{				
		console->displayAlpha += console->openingSpeed * Time::DeltaTime();      
		console->displayAlpha = std::clamp(console->displayAlpha, 0.0f, 1.0f);
		
		Vec3 startingPosition = { 0, -CONSOLE_HEIGHT };
		Vec3 targetPosition   = { console->transform.y, 0.0f };

		console->transform.y = Lerp(startingPosition, targetPosition, console->displayAlpha).y;
		
		if (console->displayAlpha >= 1.0f)
		{				
			console->displayAlpha = 0.0f;
			console->state = ConsoleState::OPEN;			
		}
	}	

	if (console->state == ConsoleState::CLOSING)
	{
		console->displayAlpha += console->closingSpeed * Time::DeltaTime();
		console->displayAlpha  = std::clamp(console->displayAlpha, 0.0f, 1.0f);

		Vec3 startingPosition = { console->transform.x, 0.0f };
		Vec3 targetPosition   = { console->transform.x, -CONSOLE_HEIGHT };		
		console->transform.y  = Lerp(startingPosition, targetPosition, console->displayAlpha).y;

		if (console->displayAlpha >= 1.0f)
		{			
			console->displayAlpha = 0.0f;
			console->state = ConsoleState::CLOSED;
		}
	}	 
}

void fConsole::Internal::InputCommand(Console*& console)
{

}