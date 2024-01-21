//---------------------------------------------------------------------------------
// App.cpp
// Implementation of the calls that are exposed via the App namespace.
//---------------------------------------------------------------------------------
#include "stdafx.h"
//---------------------------------------------------------------------------------
#include <string>
#include "main.h"
#include "app.h"
#include "SimpleSound.h"
#include "SimpleController.h"
#include "SimpleSprite.h"

//---------------------------------------------------------------------------------
// Utils and externals for system info.

namespace App
{	
	void DrawLine(float sx, float sy, float ex, float ey, float r, float g, float b)
	{
#if APP_USE_VIRTUAL_RES		
		APP_VIRTUAL_TO_NATIVE_COORDS(sx, sy);
		APP_VIRTUAL_TO_NATIVE_COORDS(ex, ey);
#endif
		glBegin(GL_LINES);
		glColor3f(r, g, b); 
		glVertex2f(sx, sy);
		glVertex2f(ex, ey);

		glEnd();
	}

	void DrawCircle(MATH::Vec2 centre, float radius, float numOfLines, float r, float g, float b)
	{
		float angleIncrement = 2.0f * PI / numOfLines;
		

#if APP_USE_VIRTUAL_RES		
		APP_VIRTUAL_TO_NATIVE_COORDS(centre.x, centre.y);
		radius =   2.0f * radius / APP_VIRTUAL_HEIGHT;
		

#endif
	

	for (int i = 0; i < numOfLines; ++i) {
		glBegin(GL_TRIANGLES);
		glColor3f(r, g, b);
		float angleStart = i * angleIncrement;
		float angleEnd = (i + 1) * angleIncrement;

		float startX = centre.x + radius * std::cos(angleStart);
		float startY = centre.y + radius * std::sin(angleStart);

		float endX = centre.x + radius * std::cos(angleEnd);
		float endY = centre.y + radius * std::sin(angleEnd);

		glVertex2f(startX, startY);
		glVertex2f(endX, endY);
		glVertex2f(centre.x, centre.y);
		glEnd();
	}

	}

	void DrawRect(MATH::Vec2 centre, MATH::Vec2 dimensions, bool fill, float r, float g, float b)
	{

		// no fill
		if (!fill) {
			DrawLine(centre.x - (0.5f * dimensions.x), centre.y + (0.5f * dimensions.y),
				centre.x + (0.5f * dimensions.x), centre.y + (0.5f * dimensions.y), r, g, b);

			DrawLine(centre.x - (0.5f * dimensions.x), centre.y + (0.5f * dimensions.y),
				centre.x - (0.5f * dimensions.x), centre.y - (0.5f * dimensions.y), r, g, b);

			DrawLine(centre.x - (0.5f * dimensions.x), centre.y - (0.5f * dimensions.y),
				centre.x + (0.5f * dimensions.x), centre.y - (0.5f * dimensions.y), r, g, b);

			DrawLine(centre.x + (0.5f * dimensions.x), centre.y + (0.5f * dimensions.y),
				centre.x + (0.5f * dimensions.x), centre.y - (0.5f * dimensions.y), r, g, b);
			return;
		}


		// fill

#if APP_USE_VIRTUAL_RES		
		APP_VIRTUAL_TO_NATIVE_COORDS(centre.x, centre.y);
		dimensions.x = 2.0f * dimensions.x / APP_VIRTUAL_WIDTH;
		dimensions.y = 2.0f * dimensions.y / APP_VIRTUAL_HEIGHT;

		
#endif
		

		if (fill) {

			glBegin(GL_TRIANGLES);
			glColor3f(r, g, b);
			glVertex2f(centre.x - (0.5f * dimensions.x), centre.y + (0.5f * dimensions.y));
			glVertex2f(centre.x + (0.5f * dimensions.x), centre.y + (0.5f * dimensions.y));
			glVertex2f(centre.x + (0.5f * dimensions.x), centre.y - (0.5f * dimensions.y));
			glEnd();

			glBegin(GL_TRIANGLES);
			glColor3f(r, g, b);
			glVertex2f(centre.x - (0.5f * dimensions.x), centre.y + (0.5f * dimensions.y));
			glVertex2f(centre.x + (0.5f * dimensions.x), centre.y - (0.5f * dimensions.y));
			glVertex2f(centre.x - (0.5f * dimensions.x), centre.y - (0.5f * dimensions.y));
			glEnd();
		}
		
	}
	

	
	CSimpleSprite *CreateSprite(const char *fileName, int columns, int rows)
	{
		return new CSimpleSprite(fileName, columns, rows);
	}

	bool IsKeyPressed(int key)
	{
		return ((GetAsyncKeyState(key) & 0x8000) != 0);
	}


	void GetMousePos(float &x, float &y)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);	// Get the mouse cursor 2D x,y position			
		ScreenToClient(MAIN_WINDOW_HANDLE, &mousePos);
		x = (float)mousePos.x;
		y = (float)mousePos.y;
		x = (x * (2.0f / WINDOW_WIDTH) - 1.0f);
		y = -(y * (2.0f / WINDOW_HEIGHT) - 1.0f);

#if APP_USE_VIRTUAL_RES		
		APP_NATIVE_TO_VIRTUAL_COORDS(x, y);
#endif
	}
	void PlaySound(const char *fileName, bool looping)
	{
		DWORD flags = (looping) ? DSBPLAY_LOOPING : 0;
		CSimpleSound::GetInstance().PlaySound(fileName, flags);
	}
	void StopSound(const char *fileName)
	{
		CSimpleSound::GetInstance().StopSound(fileName);
	}
	bool IsSoundPlaying(const char *fileName)
	{
		return CSimpleSound::GetInstance().IsPlaying(fileName);
	}
	// This prints a string to the screen
	void Print(float x, float y, const char *st, float r, float g, float b, void *font)
	{
#if APP_USE_VIRTUAL_RES		
		APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
#endif		
		// Set location to start printing text
		glColor3f(r, g, b); // Yellow
		glRasterPos2f(x, y);
		int l = (int)strlen(st);
		for (int i = 0; i < l; i++)
		{
			glutBitmapCharacter(font, st[i]); // Print a character on the screen
		}
	}
	const CController &GetController( int pad )
	{
		return CSimpleControllers::GetInstance().GetController(pad);
	}
}