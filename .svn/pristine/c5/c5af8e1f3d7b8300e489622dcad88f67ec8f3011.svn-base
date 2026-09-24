#include "MGUI.h"                    

#pragma region LEGACY

void fMGUI::Update()
{    
    for (unsigned int i = 0; i < screenSpaceText.size(); i++)
    {        
        if (screenSpaceText[i]->kind == STATIC_TEXT)
            fShader::Update(screenSpaceText[i]->font.material.shader);
        else
            fInputText::Update(screenSpaceText[i]);
    }
    

}

//==========================================================================================//
// Text
//==========================================================================================//

Text* fText::Create(const char* sentence, float fontSize, float maxLineWidth, float x, float y, Vec3 color)
{
	int sizeOf				= sizeof(gVertex);
	int characterCount      = fUtil::GetSequenceOfCharactersLength(sentence);
	int indexCount			= characterCount * 6;									 // One quad can be represented by 6 indices
	int vertex_count				= characterCount * 4;

	Text* text				= reinterpret_cast<Text*>(malloc(sizeof(Text)));
	text					= new(text) Text();										 // Way to initialize members of void memory
    text->kind              = TextType::STATIC_TEXT;
	text->id				= (int)screenSpaceText.size();
    text->sentence          = (char*)malloc(characterCount);
	strcpy(text->sentence, sentence);
	text->sentenceLength    = characterCount;
	text->font				= fFont::Load(DEFAULT_FONT_FNT, DEFAULT_FONT_ATLAS, "C:/Midnight/shaders/GUI/defaultTextGUI.shader");
    text->font.size         = fontSize;
	text->lineCount		    = 0;

	text->maxLineWidth		= maxLineWidth;	
	text->mesh.total_vertices_byte_size        = vertex_count * sizeOf;
	text->mesh.vertex_count       = vertex_count;
	text->mesh.index_count		= indexCount; 
	text->mesh.vertices		= reinterpret_cast<gVertex*>(malloc(sizeof(gVertex) * text->mesh.vertex_count));
	text->mesh.indices   	= reinterpret_cast<int*>(malloc(sizeof(int)	* indexCount));

	text->transform         = { x, y };	    

	fFont::SetSize(text->font, fontSize);

	float cursorOffsetX     = 0;
	float cursorOffsetY     = 0;	

	for (int v = 0; v < vertex_count; v+=4)
	{
		char      character	    = *text->sentence++;
		char      nextCharacter = *text->sentence;
		Character currentCharacter;

		if (text->font.characters.count(character)) { currentCharacter = text->font.characters.at(character); }
		else										{ continue; }

		if (character == '\n' || cursorOffsetX > text->maxLineWidth) 
		{ 
			cursorOffsetY += (int)text->font.lineHeight; 
			cursorOffsetX  = 0;
			text->lineCount++;
		}

		float textureAtlasWidth  = (float)text->font.material.textures[0].width;
		float textureAtlasHeight = (float)text->font.material.textures[0].height;

		float x0 = cursorOffsetX + currentCharacter.xOffset;		
        float y0 = cursorOffsetY + currentCharacter.yOffset;
		float x1 = x0	         + currentCharacter.width;
		float y1 = y0	         + currentCharacter.height;

		float u0 = currentCharacter.U0 / textureAtlasWidth;
		float v0 = currentCharacter.V0 / textureAtlasHeight;
		float u1 = currentCharacter.U1 / textureAtlasWidth;
		float v1 = currentCharacter.V1 / textureAtlasHeight;

		// Top Left	    0
		//
		text->mesh.vertices[v].position	  = { x0,  y0 };  
		text->mesh.vertices[v].color		  = color;
		text->mesh.vertices[v].uv			  = { u0,  v0 };	
		// Bottom Left  1
		//
		text->mesh.vertices[v + 1].position = { x0,  y1 };
		text->mesh.vertices[v + 1].color	  = color;
		text->mesh.vertices[v + 1].uv		  = { u0,  v1 };

		// Top Right    2
		//
		text->mesh.vertices[v + 2].position = { x1,  y0 };
		text->mesh.vertices[v + 2].color	  = color;
		text->mesh.vertices[v + 2].uv		  = { u1,  v0 };

		// Bottom Right 3
		//
		text->mesh.vertices[v + 3].position = { x1,  y1 };
		text->mesh.vertices[v + 3].color	  = color;
		text->mesh.vertices[v + 3].uv		  = { u1,  v1 };			
		

		short kerningAmount = 0;
		if (currentCharacter.kernings.contains(nextCharacter)) 
        {
            kerningAmount = (short)currentCharacter.kernings.at(nextCharacter); 
        }

		cursorOffsetX += currentCharacter.xAdvance + kerningAmount;
		text->lineCount > 0 ? text->lineWidth = text->maxLineWidth : text->lineWidth = cursorOffsetX;
	}
	

    // 0 1 2
    // 2 1 3
    // . . .
    //
    for (int i = 0; i < indexCount / 6; i++)
    {
        int base = i * 4;
        int idx  = i * 6;

        text->mesh.indices[idx + 0] = base + 0;
        text->mesh.indices[idx + 1] = base + 1;
        text->mesh.indices[idx + 2] = base + 2;
        text->mesh.indices[idx + 3] = base + 2;
        text->mesh.indices[idx + 4] = base + 1;
        text->mesh.indices[idx + 5] = base + 3;
    }
	
	OGL_Util::Create_VAO_VBO_EBO
	(
		text->id, 
		text->mesh.VAO, 
		text->mesh.VBO, 
		text->mesh.EBO, 
		text->mesh.vertices, 
		text->mesh.total_vertices_byte_size, 
		text->mesh.indices, 
		text->mesh.index_count,
		OGL_Util::Integrants::POSITION_COLOR_UV,
		GL_DYNAMIC_DRAW
	);

	screenSpaceText.emplace_back(text);

	return text;
}

void fText::SetPosition(Text*& text, float x, float y)
{
	text->transform.x = x;
	text->transform.y = y;
}

void fText::Test()
{
    Text* text0 = fText::Create("load_scene 'test'", 16, 4080, 10, 450, {1,0,1});
	//Text* text1 = CreateText("Yet he yielded little ground.",									2, 4080);
	//Text* text2 = CreateText("Ahead, straightforward majority mistaking alternatively",			2, 4080);
	//Text* text3 = CreateText("Available withdraw maximum displaying crazy",					   2, 4080);
	//Text* text4 = CreateText("Rubbish, deliberately responsibility. Objections... submitting.",  2, 4080);
	//Text* text5 = CreateText("T.,:;-F.,:;-Y.,:;-V.,W.,L' ,-P.,R.,Q.,A-,T aTeTiToYaYeYi.",		  32, 4080);
}


//==========================================================================================//
// Input Text
//==========================================================================================//

Text* fInputText::Create(float x, float y)
{
    Text* it = reinterpret_cast<Text*>(malloc(sizeof(Text)));
    it->kind = TextType::INPUT_TEXT;    
    it->transform = { x, y, 100, 50 };    
    it->inptSentChar = 0;
    memset(&it->inputSentence, ' ', 128);
    screenSpaceText.emplace_back(it);

    return it;
}

void fInputText::Update(Text*& inputText)
{    
    static bool editingText;
    static bool releaseKey = false;
    
    //if (Inside (Input::Mouse::X, Input::Mouse::Y, inputText) && Input::Mouse::BUTTON_LEFT) { editingText = true;  }
    //if (!Inside(Input::Mouse::X, Input::Mouse::Y, inputText) && Input::Mouse::BUTTON_LEFT) { editingText = false; }

    // if (!Input::KEYLegacy::ANY_KEY_BEIGN_PRESSED)
    // {
    //     releaseKey = true;
    // }


    // if (editingText && Input::KEYLegacy::ANY_KEY_BEIGN_PRESSED && releaseKey)
    // {
    //     inputText->inputSentence[inputText->inptSentChar] = (char)Input::KEYLegacy::LAST_KEY_PRESSED;
    //     inputText->inptSentChar++;
    //     std::cout << inputText->inputSentence << "\n";
    //     releaseKey = false;
    // }  
}



/*
#pragma region Transformations

inline bool reset        = false;
inline Vec2 pStartOffset = { 0,0 };
inline Vec2 mouseStart   = { 0, 0 };
void MGUI::MovePanel(Panel& panel, Window::Container*& window)
{   
    if (activeResizingPanel) { return; }

    panel.color = Vec4(0.25, 0.25f, 0.25f, 0.75f);
    if ((IsTheCursorOverMyHeader(panel) && Input::Mouse::BUTTON_LEFT && !activeMovingPanel && panel.activeBorder == Border::None) || panel.moving)
    {
        panel.color = Vec4(0.35f, 0.35f, 0.35f, 0.9f);
        activeMovingPanel = &panel;

        if (!reset)
        {
            reset        = true;
            mouseStart   = Vec2((float)Input::Mouse::currentMouseX, (float)Input::Mouse::currentMouseY);
            pStartOffset = { panel.mesh.vertex[0].position.x, panel.mesh.vertex[0].position.y };
        }

        Vec2 currMouse = { (float)Input::Mouse::currentMouseX, (float)Input::Mouse::currentMouseY };
        Vec2 offset    =  pStartOffset + currMouse - mouseStart;

        SetPanelAndItsComponentsPosition(panel, offset.x, offset.y);        

        panel.moving = true;
    }

    if (!Input::Mouse::BUTTON_LEFT) 
    {
        CheckPanelOffBounds(panel, window);
        mouseStart        = { 0, 0 };
        pStartOffset      = { 0,0 };
        panel.moving      = false;
        reset             = false;
        activeMovingPanel = nullptr;
    } 
}



#pragma endregion
*/

#pragma endregion


// Struct 
// Begin
// End
// Draw -> Reset CurrentPanel_beign_created_idx

// @important // @important // @important CHECK INSTANCED ARRAYS FOR PERFORMANCE IMPROVEMENT


// #================================================================#
// # General Functionality
// #================================================================#

void fMGUI::Initialize()
{
    Internal::GLOBAL_MATERIAL = fMaterial_OGL::Create("C:/Midnight/shaders/GUI/gui.shader");
    Internal::PANEL_BEING_CREATED_IDX = 0;
}

void fMGUI::Begin(const char* windowTitle)
{    
    if (Internal::GUI_DATA.panels.contains(Internal::PANEL_BEING_CREATED_IDX))
    {
        Panel& p = Internal::GUI_DATA.panels.at(Internal::PANEL_BEING_CREATED_IDX);
        
        p.x      = Mouse::X;
        p.y      = Mouse::Y;
        p.width  = PANEL_DEFAULT_WIDTH;
        p.height = PANEL_HEADER_HEIGHT;
        p.color  = p.color;
    }   
    else
    {
        Internal::PANEL_BEING_CREATED.id = Internal::PANEL_BEING_CREATED_IDX;
        Internal::PANEL_BEING_CREATED.x = 0;
        Internal::PANEL_BEING_CREATED.y = 0;
        Internal::PANEL_BEING_CREATED.width = PANEL_DEFAULT_WIDTH;
        Internal::PANEL_BEING_CREATED.height = PANEL_HEADER_HEIGHT;
        Internal::PANEL_BEING_CREATED.color = { 0.05f, 0.05f, 0.05f };
        Internal::GUI_DATA.panels.emplace(Internal::PANEL_BEING_CREATED_IDX , Internal::PANEL_BEING_CREATED);
    }
    CreatePopupMenu();
}

void fMGUI::End()
{    
    Panel& p = Internal::GUI_DATA.panels.at(Internal::PANEL_BEING_CREATED_IDX);
    p.geometry = fGeometry::CreateScreenSpaceQuadHeapFree(p.x, p.y, p.width + WIDGET_SEPARATION, p.height + WIDGET_SEPARATION, p.color);
    
    int id = 0;
    OGL_Util::Create_VAO_VBO_EBO(id, p.geometry.VAO, p.geometry.VBO, p.geometry.EBO, p.geometry.vertices, p.geometry.total_vertices_byte_size, p.geometry.indices, p.geometry.index_count, OGL_Util::Integrants::POSITION_COLOR_UV, GL_DYNAMIC_DRAW);
    
    Internal::PANEL_BEING_CREATED_IDX++;
    Internal::PANEL_BEING_CREATED = {0};
}


bool fMGUI::OverMe(float x, float y, float width, float height)
{
    float mX = Mouse::X;
    float mY = Mouse::Y;

    return mX >= x and mX <= x + width and mY >= y and mY <= y + height;
}

bool fMGUI::Clicked(float x, float y, float width, float height)
{    
    //static bool clickedOutside = false;
    static bool clickedDown = false;
    bool overMe = OverMe(x, y, width, height);
    if (Mouse::BUTTON_LEFT and overMe) { clickedDown = true; }

    if (!Mouse::BUTTON_LEFT and overMe and clickedDown)
    {
        clickedDown = false;
        return true;
    }

    // if (!Input::Mouse::BUTTON_LEFT and overMe) { clickedOutside = false; }
    // if (Input::Mouse::BUTTON_LEFT and !overMe) { clickedOutside = true; }
    
    return false;
}

bool fMGUI::OnTheScreen(float x, float y)
{
    return true;
}

// #================================================================#
// # Widgets
// #================================================================#

bool fMGUI::Button(const char* name, Vec3 color)
{    
    Panel& p = Internal::GUI_DATA.panels.at(Internal::PANEL_BEING_CREATED_IDX);
    int id       = 0;
    float x      = p.x + WIDGET_SEPARATION;
    float y      = p.y + p.widgetYOffset + WIDGET_SEPARATION + PANEL_HEADER_HEIGHT;
    float width  = p.width - WIDGET_SEPARATION;
    float height = WIDGET_DEFAULT_HEIGHT;

    if (!OnTheScreen(x, y))return false;
    
    bool clicked = Clicked(x, y, width, height);
    bool overMe  = OverMe(x, y, width, height);

    if (overMe) { color += 0.1f; }
    
    GUI_Widget w =
    {
        x,
        y,
        width,
        height,
        color,
        fGeometry::CreateScreenSpaceQuadHeapFree(x, y, width, height, color)
    };

    OGL_Util::Create_VAO_VBO_EBO(id, w.geometry.VAO, w.geometry.VBO, w.geometry.EBO, w.geometry.vertices, w.geometry.total_vertices_byte_size, w.geometry.indices, w.geometry.index_count, OGL_Util::Integrants::POSITION_COLOR_UV, GL_STATIC_DRAW);
              
    p.widgets.emplace_back(w);
    p.widgetYOffset += height + WIDGET_SEPARATION;
    p.height        += height + WIDGET_SEPARATION;

    return clicked;       
}
 

void fMGUI::Checkbox(const char* name, bool* property, Vec3 color)
{
    Panel& p = Internal::GUI_DATA.panels.at(Internal::PANEL_BEING_CREATED_IDX);

    int id       = 0;
    float x      = p.x + p.width - WIDGET_DEFAULT_HEIGHT;
    float y      = p.y + p.widgetYOffset + WIDGET_SEPARATION + PANEL_HEADER_HEIGHT;
    float width  = WIDGET_DEFAULT_HEIGHT;
    float height = WIDGET_DEFAULT_HEIGHT;

    bool clicked = Clicked(x, y, width, height);
    bool overMe  = OverMe(x, y, width, height);

    if (clicked)   { *property = !*property; }
    if (*property) { color = { 0, 0.8f, 0 }; }
    if (overMe)    { color += 0.1f;          }

    
    GUI_Widget w =
    {
        x,
        y,
        width,
        height,
        color,
        fGeometry::CreateScreenSpaceQuadHeapFree(x, y, width, height, color)
    };

    OGL_Util::Create_VAO_VBO_EBO(id, w.geometry.VAO, w.geometry.VBO, w.geometry.EBO, w.geometry.vertices, w.geometry.total_vertices_byte_size, w.geometry.indices, w.geometry.index_count, OGL_Util::Integrants::POSITION_COLOR_UV, GL_STATIC_DRAW);

    p.widgetYOffset += height + WIDGET_SEPARATION;        
    p.height        += height + WIDGET_SEPARATION;
    p.widgets.emplace_back(w);
}



void fMGUI::Label(const char* expression, ...)
{
    
}


// #================================================================#
// # TEST
// #================================================================#

void fMGUI::TESTGUI()
{             
   
    // auto start = std::chrono::high_resolution_clock::now();

    Begin("Test Window");

    
    if (Button("Button", { 0.5f, 1.5f, 0.5f })) { MessageBox(0, L"Button 1 Pressed", L"Win32 MessageBox", MB_YESNOCANCEL); }
    if (Button("Button", { 0.5f, 0.5f, 0.5f })) { std::cout << "Clicked Button 1\n"; }  
    if (Button("Button", { 0.5f, 0.5f, 0.5f })) { std::cout << "Clicked Button 1\n"; }  
    if (Button("Button", { 0.5f, 1.5f, 0.5f })) { std::cout << "Clicked Button 1\n"; }  

    End();

    Begin("Test Window");


    if (Button("Button", { 1.5f, 1.5f, 0.5f })) { MessageBox(0, L"Button 1 Pressed", L"Win32 MessageBox", MB_YESNOCANCEL); }
    if (Button("Button", { 0.5f, 0.5f, 0.5f })) { std::cout << "Clicked Button 1\n"; }
    if (Button("Button", { 0.5f, 0.5f, 0.5f })) { std::cout << "Clicked Button 1\n"; }


    End();

    // auto end = std::chrono::high_resolution_clock::now();
    // 
    // float duration = std::chrono::duration<float, std::chrono::microseconds::period>(end - start).count();

    // std::cout << "Duration " << duration << "\n";
    
}




void fMGUI::Internal::FreeGeometry(GUI_Mesh_Quad& geometry)
{
    //free(geometry.mesh.vertex);
    //free(geometry.mesh.indices);
    glDeleteVertexArrays(1, &geometry.VAO);
    glDeleteBuffers     (1, &geometry.VBO);
    glDeleteBuffers     (1, &geometry.EBO);
}


void fMGUI::Draw()
{
    GUIData& data = Internal::GUI_DATA;

    for (auto p = data.panels.begin(); p != data.panels.end(); p++)
    {
        Internal::Draw(&p->second.geometry, p->second.x, p->second.y, 1920, 1080);
        Internal::FreeGeometry(p->second.geometry);
        
        for (GUI_Widget& w : p->second.widgets)
        {
            Internal::Draw(&w.geometry, w.x, w.y, 1920, 1080);
            Internal::FreeGeometry(w.geometry);
        }

        p->second.height = 0;
        p->second.widgetYOffset = 0;
        p->second.widgets.clear();
    }

    Internal::PANEL_BEING_CREATED_IDX = 0;
}


void fMGUI::Internal::Draw(GUI_Mesh_Quad* geometry, float x, float y, float windowWidth, float windowHeight)
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
    glUseProgram(Internal::GLOBAL_MATERIAL.shader.program);
    unsigned int resolution = glGetUniformLocation(Internal::GLOBAL_MATERIAL.shader.program, "resolution");
    unsigned int transform = glGetUniformLocation (Internal::GLOBAL_MATERIAL.shader.program, "transform");

    glUniform2f(transform, x, y);
    glUniform2f(resolution, windowWidth, windowHeight);

    glBindVertexArray(geometry->VAO);
    glDrawElements(GL_TRIANGLES, geometry->index_count, GL_UNSIGNED_INT, 0);
            
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}