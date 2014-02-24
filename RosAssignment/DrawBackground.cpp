#include "DxLib.h"

extern int skyHandle;
extern int cloudHandle;

void DrawBackground()
{
	SetUseLighting(FALSE);
	MV1SetScale(skyHandle, VGet(500, 500, 500));
	MV1DrawModel(skyHandle);

	SetUseLighting(FALSE);
	MV1SetScale(cloudHandle, VGet(550, 40, 550));
	MV1DrawModel(cloudHandle);
}