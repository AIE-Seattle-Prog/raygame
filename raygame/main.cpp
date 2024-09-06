/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <cmath>
#include <iostream>
#include <cassert>

#include "MathUtils.h"

#include "raylib-cpp.hpp"

// FEATURE FLAGS
bool SHOULD_CLIP_VELOCITY = false;
bool SHOULD_GAIN_SPEED_ON_SIDE_BOUNCE = false;

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int ScreenWidth = 800;
	int ScreenHeight = 450;

	raylib::Window Window(ScreenWidth, ScreenHeight, "raylib-cpp - basic window", FLAG_VSYNC_HINT);
	Window.SetMonitor(0);
	Window.ToggleBorderless();

	raylib::Texture DVDLogo("res/aie.png");
	raylib::Color DVDColor = WHITE;

	raylib::Vector2 DVDLocation((int)(Window.GetWidth() / 2), (int)(Window.GetHeight() / 2));
	raylib::Vector2 DVDDirection = { -1, 1 };
	float InitialDVDSpeed = 500.0f;
	float DVDSpeed = InitialDVDSpeed;
	float DVDSpeedGainOnBounce = 10.0f;

	InitAudioDevice();      // Initialize audio device
	raylib::Sound BumpSound("res/pepSound3.wav");
	raylib::Sound CornerSound("res/powerUp2.ogg");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	float DVDValuePeriod = 0.5f;

	// Main game loop
	while (!Window.ShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		if (IsKeyDown('E'))
		{
			DVDSpeed += 500.0f * GetFrameTime();
		}
		if (IsKeyDown('Q'))
		{
			DVDSpeed -= 500.0f * GetFrameTime();
		}
		if (IsKeyDown('R'))
		{
			DVDSpeed = InitialDVDSpeed;
		}

		if (IsKeyDown('W'))
		{
			DVDLocation = { 0,0 };
			DVDDirection = { -1,-1 };
		}

		DVDDirection = DVDDirection.Normalize();
		raylib::Vector2 DVDVelocity = DVDDirection * DVDSpeed;
		raylib::Vector2 DVDDisplacement = DVDVelocity * GetFrameTime();
		
		if (SHOULD_CLIP_VELOCITY)
		{
			raylib::Vector2 EffectiveDisplacement = DVDDisplacement;
			// Find max displacement in direction of travel
			if (DVDVelocity.x > 0)
			{
				float Right = DVDLocation.x + DVDLogo.width;
				float DistToWall = Window.GetWidth() - Right;

				float RealChange = MinSign(DistToWall, DVDDisplacement.x);
				EffectiveDisplacement.x = MinSign(RealChange, EffectiveDisplacement.x);
			}
			else if (DVDVelocity.x < 0)
			{
				float Left = DVDLocation.x;
				float DistToWall = Left;

				float RealChange = MinSign(DistToWall, DVDDisplacement.x);
				EffectiveDisplacement.x = MinSign(RealChange, EffectiveDisplacement.x);
				EffectiveDisplacement.x = copysignf(EffectiveDisplacement.x, DVDVelocity.x);
			}

			if (DVDVelocity.y > 0)
			{
				float Bottom = DVDLocation.y + DVDLogo.height;
				float DistToWall = Window.GetHeight() - Bottom;

				float RealChange = MinSign(DistToWall, DVDDisplacement.y);
				EffectiveDisplacement.y = MinSign(RealChange, EffectiveDisplacement.y);
			}
			else if (DVDVelocity.y < 0)
			{
				float Top = DVDLocation.y;
				float DistToWall = Top;

				float RealChange = MinSign(DistToWall, DVDDisplacement.y);
				EffectiveDisplacement.y = MinSign(RealChange, EffectiveDisplacement.y);
				EffectiveDisplacement.y = copysignf(EffectiveDisplacement.y, DVDVelocity.y);
			}

			if (EffectiveDisplacement.LengthSqr() != 0.0f)
			{
				raylib::Vector2 EffectivePercentages = EffectiveDisplacement / DVDDisplacement;
				float EffectiveRatio = Min(EffectivePercentages.x, EffectivePercentages.y);
				assert(EffectiveRatio <= 1.0f);

				DVDDisplacement *= EffectiveRatio;
			}
		}

		DVDLocation += DVDDisplacement;
		DVDLocation = Vector2Clamp(DVDLocation, { 0,0 }, { (float)(Window.GetWidth() - DVDLogo.width), (float)(Window.GetHeight() - DVDLogo.height) });

		//
		//
		// 

		// right
		int BounceCount = 0;

		if (DVDLocation.x + DVDLogo.width >= Window.GetWidth())
		{
			DVDDirection.x *= -1;
			DVDLocation.x = Window.GetWidth() - DVDLogo.width;
			++BounceCount;
		}
		// left
		else if (DVDLocation.x <= 0.0f)
		{
			DVDDirection.x *= -1;
			DVDLocation.x = 0;
			++BounceCount;
		}

		// top
		if (DVDLocation.y <= 0.0f)
		{
			DVDDirection.y *= -1;
			DVDLocation.y = 0;

			++BounceCount;
		}
		// bottom
		else if (DVDLocation.y + DVDLogo.height >= Window.GetHeight())
		{
			DVDDirection.y *= -1;
			DVDLocation.y = Window.GetHeight() - DVDLogo.height;

			++BounceCount;
		}

		if (SHOULD_GAIN_SPEED_ON_SIDE_BOUNCE)
		{
			DVDSpeed += DVDSpeedGainOnBounce * BounceCount;
		}

		// click to control
		if (IsCursorOnScreen() && IsMouseButtonDown(0))
		{
			DVDLocation = GetMousePosition();
			DVDLocation.x -= DVDLogo.GetWidth() / 2;
			DVDLocation.y -= DVDLogo.GetHeight() / 2;
		}

		// value cycling
		raylib::Vector3 DVDColorHSV = DVDColor.ToHSV();
		DVDColorHSV.z = 0.15 * std::sinf((2 * 3.14f / DVDValuePeriod) + GetTime()) + 0.65;
		DVDColor = raylib::Color::FromHSV(DVDColorHSV.x, DVDColorHSV.y, DVDColorHSV.z);

		// bounce handling
		if (BounceCount > 0)
		{
			DVDColor = raylib::Color::FromHSV((int)(DVDColorHSV.x + 60) % 360, 1.0f, DVDColorHSV.z);

			if (BounceCount > 1)
			{
				CornerSound.Play();
				DVDSpeed = InitialDVDSpeed;
			}
			else
			{
				//BumpSound.Play();
			}
		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		Window.ClearBackground(BLACK);

		DVDLogo.Draw(DVDLocation, DVDColor);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	return 0;
}
