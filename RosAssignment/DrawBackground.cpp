#include "DxLib.h"
#include "ResorceHandles.h"

void DrawBackground()
{
	SetUseLighting(FALSE);
	MV1SetScale(ResourceHandles::getResourceHandles().SkyHandle, VGet(500, 500, 500));
	MV1DrawModel(ResourceHandles::getResourceHandles().SkyHandle);

	SetUseLighting(FALSE);
	MV1SetScale(ResourceHandles::getResourceHandles().CloudHandle, VGet(550, 40, 550));
	MV1DrawModel(ResourceHandles::getResourceHandles().CloudHandle);
}