#pragma once

#include "Status.h"
enum SCENE
{
	SCENE_TOP,
	SCENE_PLAY,
	SCENE_MANUAL,
	SCENE_PAUSE
};

class Frame
{
	char buf[256];
	SCENE _scene;
	bool _end;

	void UpdateField();
	void DrawField();

	void Top();
	void Play();
	void Manual();
	void Pause();

	void DrawBackground();

	Frame();
public:
	static Frame& getFrame();
	void Run();
	bool End();
};