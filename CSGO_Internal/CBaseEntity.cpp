#include "CBaseEntity.h"
#include "ClassIdManager.h"
#include "NetvarManager.h"
#include "CMath.h"

int CBaseEntity::GetHealth()
{
	return *(int*)((uintptr_t)this + Netvar->DT_BasePlayer.m_iHealth);
}

int CBaseEntity::GetFlags()
{
	return *(int*)((uintptr_t)this + Netvar->DT_BasePlayer.m_fFlags);
}

Vector CBaseEntity::GetOrigin()
{
	return *(Vector*)((uintptr_t)this + Netvar->DT_BaseEntity.m_vecOrigin);
}

QAngle CBaseEntity::GetEyeAngles()
{
	return *(QAngle*)((uintptr_t)this + Netvar->DT_CSPlayer.m_angEyeAngles);
}

bool CBaseEntity::IsPlayer()
{
	if (this->GetClientClass()->m_ClassID == ClassId->CCSPlayer)
		return true;
	return false;
}

bool CBaseEntity::IsAlive()
{
	if (this->GetHealth() < 1 || this->GetHealth() > 100) {
		return false;
	}

	return true;
}

bool CBaseEntity::IsImmune()
{
	return *(bool*)((DWORD)this + Netvar->DT_CSPlayer.m_bGunGameImmunity);
}


Vector CBaseEntity::GetBonePos(int boneID)
{
	matrix3x4_t boneMatrix[128];
	if ((IClientEntity*)this->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, (int)GetTickCount64))
	{
		return Vector( boneMatrix[boneID][0][3], boneMatrix[boneID][1][3], boneMatrix[boneID][2][3]);
	}

	return Vector(0, 0, 0);
}

bool CBaseEntity::IsWeapon()
{
	const int id = this->GetClientClass()->m_ClassID;
	if (id == ClassId->CBaseCombatWeapon ||
		id == ClassId->CAK47 ||
		id == ClassId->CSCAR17 ||
		id == ClassId->CWeaponAug ||
		id == ClassId->CWeaponAWP ||
		id == ClassId->CWeaponBaseItem ||
		id == ClassId->CWeaponBizon ||
		id == ClassId->CWeaponCSBase ||
		id == ClassId->CWeaponCSBaseGun ||
		id == ClassId->CWeaponElite ||
		id == ClassId->CWeaponFamas ||
		id == ClassId->CWeaponFiveSeven ||
		id == ClassId->CWeaponG3SG1 ||
		id == ClassId->CWeaponGalil ||
		id == ClassId->CWeaponGlock ||
		id == ClassId->CWeaponHKP2000 ||
		id == ClassId->CWeaponM249 ||
		id == ClassId->CWeaponM3 ||
		id == ClassId->CWeaponM4A1 ||
		id == ClassId->CWeaponMAC10 ||
		id == ClassId->CWeaponMag7 ||
		id == ClassId->CWeaponMP5Navy ||
		id == ClassId->CWeaponMP7 ||
		id == ClassId->CWeaponMP9 ||
		id == ClassId->CWeaponNegev ||
		id == ClassId->CWeaponNOVA ||
		id == ClassId->CWeaponP228 ||
		id == ClassId->CWeaponP250 ||
		id == ClassId->CWeaponP90 ||
		id == ClassId->CWeaponSawedoff ||
		id == ClassId->CWeaponSCAR20 ||
		id == ClassId->CWeaponScout ||
		id == ClassId->CWeaponSG550 ||
		id == ClassId->CWeaponSG552 ||
		id == ClassId->CWeaponSG556 ||
		id == ClassId->CWeaponSSG08 ||
		id == ClassId->CWeaponTaser ||
		id == ClassId->CWeaponTec9 ||
		id == ClassId->CWeaponTMP ||
		id == ClassId->CWeaponUMP45 ||
		id == ClassId->CWeaponUSP ||
		id == ClassId->CWeaponXM1014)
		return true;
	return false;
}

Vector CBaseEntity::GetEyePos()
{
	return GetOrigin() + GetEyeOffset();
}

int CBaseEntity::GetTeam()
{
	return *(int*)((uintptr_t)this + Netvar->DT_BaseEntity.m_iTeamNum);
}

Vector CBaseEntity::GetEyeOffset()
{
	return *(Vector*)((int)this + Netvar->DT_BasePlayer.m_vecViewOffset);
}

bool CBaseEntity::IsVisible(CBaseEntity* localPlayer)
{
	trace_t trace;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = localPlayer;
	ray.Init(localPlayer->GetEyePos(), this->GetEyePos());
	Interfaces->EngineTrace->TraceRay(ray, MASK_VISIBLE, &filter, &trace);

	if (trace.m_pEnt == this || trace.fraction == 1.f)
	{
		return true;
	}

	return false;
}

bool CBaseEntity::OnTarget(QAngle &viewAngles) {
	Vector vEnd;

	trace_t tr;
	Ray_t ray;

	CTraceFilter filter;
	filter.pSkip = this;

	Math.AngleVectors(viewAngles, vEnd);

	vEnd = vEnd * 8192.0f + this->GetEyePos();

	ray.Init(this->GetEyePos(), vEnd);

	Interfaces->EngineTrace->TraceRay(ray, CONTENTS_SOLID | CONTENTS_GRATE | CONTENTS_HITBOX, &filter, &tr);
	if (!tr.m_pEnt)
		return false;

	if (tr.hitgroup <= 8 && tr.hitgroup > 0) {
		return true;
	}

	return false;
}
