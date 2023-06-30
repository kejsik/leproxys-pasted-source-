#include <cstdint>
#include <WinUser.h>
#include "../stdafx/settings.h"
#include "../stdafx/stdafx.h"

float powf_(float _X, float _Y) {
	return (_mm_cvtss_f32(_mm_pow_ps(_mm_set_ss(_X), _mm_set_ss(_Y))));
}

double GetDistance(double x1, double y1, double z1, double x2, double y2) {
	return sqrtf(powf((x2 - x1), 2) + powf_((y2 - y1), 2));
}

boolean bIsInRectangle(double centerX, double centerY, double radius, double x, double y) {
	return x >= centerX - radius && x <= centerX + radius &&
		y >= centerY - radius && y <= centerY + radius;
}

float RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void mouse(double x, double y, float smooth)
{
	float ScreenCenterX = center_x;
	float ScreenCenterY = center_y;
	int AimSpeed = smooth;
	float TargetX = 0;
	float TargetY = 0;

	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	if (LeProxy::settings::humanization)
	{
		float targetx_min = TargetX - 1;
		float targetx_max = TargetX + 1;

		float targety_min = TargetY - 1;
		float targety_max = TargetY + 1;

		float offset_x = RandomFloat(targetx_min, targetx_max);
		float offset_y = RandomFloat(targety_min, targety_max);

		mouse_event(MOUSEEVENTF_MOVE, static_cast<int>((float)offset_x), static_cast<int>((float)offset_y / 1), NULL, NULL);
	}
	else
	{
		mouse_event(MOUSEEVENTF_MOVE, TargetX, TargetY, NULL, NULL);
	}

	return;
}