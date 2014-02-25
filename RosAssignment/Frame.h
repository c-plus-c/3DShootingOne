#pragma once

enum SCENE
{
	SCENE_TOP,
	SCENE_PLAY,
	SCENE_MANUAL,
	SCENE_PAUSE
};

#define ADDITION_CYCLE 60*7

#define DEFEAT_SCORE 100
#define LEVELUP 500

class Frame
{
	char buf[256];
	long _count;
	SCENE _scene;
	bool _end;

	int _score;
	int _level;

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
	void InitializeGame();
};