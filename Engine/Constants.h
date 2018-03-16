#pragma once

namespace Constants
{
	const int MAX_MODELS = 15;

	const char* const CUBE = "../Engine/data/Models/cube.txt";
	const int CUBE_MORE_INSTANCES = 0;
	const char* const SPHERE = "../Engine/data/Models/sphere.txt";
	const int SPHERE_MORE_INSTANCES = 0;

	const WCHAR* const WALL01 = L"../Engine/data/Textures/wall01.dds";
	const WCHAR* const WALL02 = L"../Engine/data/Textures/wall02.dds";
	const WCHAR* const ICE = L"../Engine/data/Textures/ice.dds";
	const WCHAR* const METAL = L"../Engine/data/Textures/metal.dds";
	const WCHAR* const TERRAIN = L"../Engine/data/Textures/terrain.dds";
	const WCHAR* const MARBLE = L"../Engine/data/Textures/marble.dds";
	const WCHAR* const STAR = L"../Engine/data/Textures/star.dds";

	const int SHADOWMAP_WIDTH = 1024;
	const int SHADOWMAP_HEIGHT = 1024;
	const float SHADOWMAP_DEPTH = 50.0f;
	const float SHADOWMAP_NEAR = 1.0f;

	const int SCREEN_WIDTH = 1024;
	const int  SCREEN_HEIGHT = 768;
	const bool FULL_SCREEN = false;
	const bool VSYNC_ENABLED = true;
	const float SCREEN_DEPTH = 100.0f;
	const float SCREEN_NEAR = 1.0f;

	const float PARTICLE_DEVIATIONX = 0.5f;
	const float PARTICLE_DEVIATIONY = 0.1f;
	const float PARTICLE_DEVIATIONZ= 2.0f;
	const float PARTICLE_VELOCITY = 1.0f;
	const float PARTICLE_VELOCITY_VARIATION = 0.2f;
	const float PARTICLE_SIZE = 0.2f;
	const float PARTICLE_PER_SECOND = 250.0f;
	const int PARTICLE_MAX_NUMBERS = 5000;
}
