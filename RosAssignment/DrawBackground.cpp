#include "DxLib.h"
#include "ObjectField.h"

void DrawBackground()
{
	SetUseLighting(FALSE);
	MV1SetScale(ObjectField::getInstance().SkyHandle, VGet(500, 500, 500));
	MV1DrawModel(ObjectField::getInstance().SkyHandle);

	SetUseLighting(FALSE);
	MV1SetScale(ObjectField::getInstance().CloudHandle, VGet(550, 40, 550));
	MV1DrawModel(ObjectField::getInstance().CloudHandle);
}