#include "Aimbot.h"
#include "Interfaces.h"
#include "CMath.h"
#include "ConfigVars.h"

Aimbot* aimbot = nullptr;

float autoShootCount = 0;

CBaseEntity *Aimbot::GetClosestEnemyToCrosshair(CBaseEntity* localPlayer, QAngle &viewAngles)
{

	CBaseEntity* entity = nullptr;

	float closestDelta = FLT_MAX;

	for (size_t i = 1; i <= 64; i++)
	{
		CBaseEntity* e = (CBaseEntity*)Interfaces->ClientEntityList->GetClientEntity(i);

		if (e && !e->IsDormant() && e->GetTeam() != localPlayer->GetTeam() && e->IsAlive() && e->IsVisible(localPlayer) && !e->IsImmune())
		{
			float delta = (Math.CalcAngle(localPlayer->GetEyePos(), e->GetEyePos()).Clamped() - viewAngles).Clamped().Length();

			if (delta < closestDelta && delta < Config.aimbotFOV)
			{
				closestDelta = delta;
				entity = e;
			}
		}
	}
	return entity;
}

bool Aimbot::Aim(CBaseEntity* localPlayer, CUserCmd* cmd)
{

	if (Config.enableAutoShoot || GetAsyncKeyState(VK_CAPITAL))
	{

		QAngle viewAngles;
		Interfaces->EngineClient->GetViewAngles(viewAngles);

		CBaseEntity* entity = GetClosestEnemyToCrosshair(localPlayer, viewAngles);

		if (entity)
		{
			QAngle angle = Math.CalcAngle(localPlayer->GetEyePos(), entity->GetBonePos(8));

			SmoothAim(viewAngles, angle, Config.aimbotSmoothAim);

			Interfaces->EngineClient->SetViewAngles(angle);

			if (Config.enableAutoShoot && autoShootCount >= Config.autoShootDelay && localPlayer->OnTarget(viewAngles))
			{
				cmd->buttons |= IN_ATTACK;
				autoShootCount = 0;
			}
		}
	}

	if (Config.enableAutoShoot)
	{
		autoShootCount++;
	}

	return true;
}

void Aimbot::SmoothAim(QAngle &viewAngle, QAngle &angle, float smoothValue)
{
	angle = (viewAngle + (angle - viewAngle).Clamped() / smoothValue).Clamped();

}
