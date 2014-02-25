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
#define LEVELUP_SCORE 500

class Frame
{
	char buf[256];
	long _count;
	SCENE _scene;
	bool _end;

	int _score;
	int _level;
	int _waitCount;

	int _pausePicture;

	void UpdateField();
	void DrawField();
	void AddNewObjects();

	void Top();
	void Play();
	void Manual();
	void Pause();

	void DrawBackground();
	void DrawRadar();
	void DrawStatus();

	Frame();
public:
	static Frame& getFrame();
	void Run();
	bool End();
	void InitializeGame();
};