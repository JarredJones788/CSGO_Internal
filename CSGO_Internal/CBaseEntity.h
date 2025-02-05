#pragma once
#include "IClientUnknown.h"
#include "IClientRenderable.h"
#include "IClientNetworkable.h"
#include "IClientThinkable.h"
#include "Vector.h"
#include "QAngle.h"

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void Release(void) = 0;
	virtual const Vector &GetAbsOrigin(void) const = 0;
	virtual const QAngle &GetAbsAngles(void) const = 0;
};

class CBaseEntity : public IClientEntity
{
public:
	int GetHealth();
	int GetFlags();
	Vector GetOrigin();
	QAngle GetEyeAngles();
	Vector GetBonePos(int boneID);
	bool IsPlayer();
	bool IsImmune();
	bool IsAlive();
	bool IsWeapon();
	bool IsVisible(CBaseEntity* localPlayer);
	bool OnTarget(QAngle &viewAngles);
	Vector GetEyePos();
	int GetTeam();
	Vector GetEyeOffset();
};
class CBaseCombatWeapon : public IClientEntity
{
public:

};