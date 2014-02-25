#include "Status.h"

#include "ObjectField.h"
#include "ResorceHandles.h"
#include "Player.h"
void DrawRadar()
{
	DrawExtendGraph(601, 401, 601 + 184, 401 + 184, ResourceHandles::getResourceHandles().RadarPictureHandle, 1);

	{
		VECTOR ptrans = ObjectField::getObjectField().player.GetTranslation();
		VECTOR pdir = ObjectField::getObjectField().player.GetDirection();

		DrawRotaGraph(692 + 92 * (ptrans.x / ACTIVE_RADIUS), 493 - 92 * (ptrans.z / ACTIVE_RADIUS), 0.45, atan2(-pdir.z, pdir.x) + DX_PI / 2, ResourceHandles::getResourceHandles().playerIconHandle, 1);
		DrawFormatString(692 + 92 * (ptrans.x / ACTIVE_RADIUS) - 25, 493 - 92 * (ptrans.z / ACTIVE_RADIUS) - 25, GetColor(255, 255, 255), "%d", (int) ptrans.y);
	}

	auto &enemies = ObjectField::getObjectField().Enemies;
	for (auto ite = enemies.begin(); ite != enemies.end(); ++ite)
	{
		VECTOR ptrans = ite->GetTranslation();
		DrawRotaGraph(692 + 92 * (ptrans.x / ACTIVE_RADIUS), 493 - 92 * (ptrans.z / ACTIVE_RADIUS), 0.45, 0, ResourceHandles::getResourceHandles().playerIconHandle, 1);
		DrawFormatString(692 + 92 * (ptrans.x / ACTIVE_RADIUS) - 25, 493 - 92 * (ptrans.z / ACTIVE_RADIUS) - 25, GetColor(255, 255, 255), "%d", (int) ptrans.y);
	}
}