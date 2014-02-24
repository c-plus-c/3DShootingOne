#include "dxlib.h"

#include "ObjectField.h"

extern void DrawBackground();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	
	
	ChangeWindowMode(TRUE);
	SetGraphMode(800, 600, 32);
	if (DxLib_Init()<0) return -1;

	SetDrawScreen(DX_SCREEN_BACK);
	SetUseZBuffer3D(TRUE);


	ObjectField::getInstance().PlayerHandle = MV1LoadModel("plane3.x");
	ObjectField::getInstance().SkyHandle = MV1LoadModel("sky.x");
	ObjectField::getInstance().CloudHandle = MV1LoadModel("bottomcloud.x");

	char buf[256];
	Player player = Player(VGet(0, 100, 0), 0, 0, 0);

	//SetGlobalAmbientLight(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
	SetLightEnable(TRUE);
	ChangeLightTypePoint(VGet(0, 100, 0), 10000, 1, 0, 0);
	SetLightAmbColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
	while (ProcessMessage() == 0)
	{
		ClsDrawScreen();

		GetHitKeyStateAll(buf);

		DrawBox(0, 0, 800, 600, GetColor(0, 0, 0), 1);

		DrawBackground();

		player.Update(buf);

		player.Draw();

		if (buf[KEY_INPUT_ESCAPE]) break;
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}
