#pragma once

class Status
{
	Status()
	{
		Score = 0;
		Count = 0;
		Level = 1;
	}
public:
	static Status& getStatus()
	{
		static Status objectField;
		return objectField;
	}
	int Score;
	int Count;
	int Level;

	void Initialize()
	{
		Score = 0;
		Count = 0;
		Level = 1;
	}
};