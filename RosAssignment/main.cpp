#include "dxlib.h"
#include "resource.h"
#include "Frame.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	
	SetWindowIconID(ID_ICON);
	SetOutApplicationLogValidFlag(FALSE);
	SetMainWindowText("Endurance UFOz");
	ChangeWindowMode(TRUE);
	SetGraphMode(800, 600, 32);
	if (DxLib_Init()<0) return -1;

	SetDrawScreen(DX_SCREEN_BACK);
	SetUseZBuffer3D(TRUE);

	SetLightEnable(TRUE);
	ChangeLightTypePoint(VGet(0, 100, 0), 10000, 1, 0, 0);
	SetLightAmbColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

	SetCameraNearFar(0.1, 10000);
	Frame &frame = Frame::getFrame();

	while (ProcessMessage() == 0&&!frame.End())
	{
		ClsDrawScreen();

		frame.Run();

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}
