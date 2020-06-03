#pragma once
#include "MainHeader.h"
#include "CBaseEntity.h"

struct surfacephysicsparams_t
{
	float friction;
	float elasticity;
	float density;
	float thickness;
	float dampening;
};

struct surfaceaudioparams_t
{
	float reflectivity;
	float hardnessFactor;
	float roughnessFactor;
	float roughThreshold;
	float hardThreshold;
	float hardVelocityThreshold;
};

struct surfacesoundnames_t
{
	unsigned short walkStepLeft;
	unsigned short walkStepRight;
	unsigned short runStepLeft;
	unsigned short runStepRight;
	unsigned short impactSoft;
	unsigned short impactHard;
	unsigned short scrapeSmooth;
	unsigned short scrapeRough;
	unsigned short bulletImpact;
	unsigned short rolling;
	unsigned short breakSound;
	unsigned short strainSound;
};

struct surfacesoundhandles_t
{
	short walkStepLeft;
	short walkStepRight;
	short runStepLeft;
	short runStepRight;
	short impactSoft;
	short impactHard;
	short scrapeSmooth;
	short scrapeRough;
	short bulletImpact;
	short rolling;
	short breakSound;
	short strainSound;
};

struct surfacegameprops_t
{
public:
	float maxSpeedFactor;
	float jumpFactor;
	char pad00[0x4];
	float flPenetrationModifier;
	float flDamageModifier;
	unsigned short material;
	char pad01[0x3];
};

struct surfacedata_t
{
	surfacephysicsparams_t physics;
	surfaceaudioparams_t audio;
	surfacesoundnames_t sounds;
	surfacegameprops_t game;
	surfacesoundhandles_t soundhandles;
};

class WeaponInfo_t {
public:
	char pad_0x0000[0x4]; //0x0000
	char* m_WeaponName; //0x0004 
	char pad_0x0008[0xC]; //0x0008
	__int32 m_MaxClip; //0x0014 
	char pad_0x0018[0xC]; //0x0018
	__int32 m_MaxReservedAmmo; //0x0024 
	char pad_0x0028[0x4]; //0x0028
	char* m_WeaponMdlPath; //0x002C 
	char pad_0x0030[0x4]; //0x0030
	char* m_DropWeaponMdlPath; //0x0034 
	char pad_0x0038[0x48]; //0x0038
	char* m_BulletType; //0x0080 
	char pad_0x0084[0x4]; //0x0084
	char* m_WeaponHudName; //0x0088 
	char pad_0x008C[0x40]; //0x008C
	__int32 m_WeaponType; //0x00CC 
	__int32 m_WeaponPrice; //0x00D0 
	__int32 m_WeaponReward; //0x00D4 
	char* m_WeaponGroupName; //0x00D8 
	char pad_0x00DC[0x10]; //0x00DC
	unsigned char m_FullAuto; //0x00EC 
	char pad_0x00ED[0x3]; //0x00ED
	__int32 iDamage; //0x00F0 
	float flArmorRatio; //0x00F4 
	__int32 m_iBullets;
	float flPenetration; //0x00F8
	char pad_0x00F8[0x8]; //0x00FC
	float flRange; //0x0108 
	float flRangeModifier; //0x010C 
	char pad_0x0110[0x10]; //0x0110
	unsigned char m_HasSilencer; //0x0120 
	char pad_0x0121[0xF]; //0x0121
	float m_MaxSpeed; //0x0130 
	float m_MaxSpeed2; //0x0134 
	char pad_0x0138[0x4C]; //0x0138
	__int32 m_RecoilSeed; //0x0184 
	char pad_0x0188[0x68]; //0x0188
	char* m_WeaponTracesType; //0x01F0 
	char pad_0x01F4[0x638]; //0x01F4
};// Size=0x082C


class CMisc
{
public:
	void Bhop(CBaseEntity * local , CUserCmd * cmd);
};


extern CMisc * Misc;