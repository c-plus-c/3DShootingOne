#pragma once

enum SCENE
{
	SCENE_TOP,
	SCENE_PLAY,
	SCENE_MANUAL,
	SCENE_PAUSE
};

#define ADDITION_CYCLE 60*7

class Frame
{
	char buf[256];
	long _count;
	SCENE _scene;
	bool _end;

	void UpdateField();
	void DrawField();
	void AddNewObjects();

	void Top();
	void Play();
	void Manual();
	void Pause();

	void DrawBackground();
	void DrawRadar();

	Frame();
public:
	static Frame& getFrame();
	void Run();
	bool End();
};