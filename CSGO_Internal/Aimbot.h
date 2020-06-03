#pragma once
#include "MainHeader.h"
#include "CBaseEntity.h"

class Aimbot
{
public:
	CBaseEntity* GetClosestEnemyToCrosshair(CBaseEntity* localPlayer, QAngle& viewAngles);
	bool Aim(CBaseEntity* localPlayer, CUserCmd* cmd);
	void SmoothAim(QAngle &viewAngle, QAngle &angle, float smoothValue);
};

extern Aimbot* aimbot;