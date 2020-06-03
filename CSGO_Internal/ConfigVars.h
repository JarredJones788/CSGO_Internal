#pragma once
class ConfigVars
{
	/*Add config varibles in this class*/
public:
	bool enableAutoShoot = true;
	float autoShootDelay = 20;

	float aimbotFOV = 360;
	float aimbotSmoothAim = 1;

	bool bhop = false;
	bool esp = true;
};

extern ConfigVars Config;