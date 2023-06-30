#pragma once
inline ImFont* ESPFont;
inline ImFont* bold_segu;
inline ImFont* titleicon;
inline ImFont* subtitle;


namespace LeProxy
{
	namespace settings
	{
		inline bool crosshair = true;
		inline bool loot = false;
		inline bool testing = false;
		inline float MaxItemDistance = 100.f;
		inline float MaxDistance = 100.f;
		inline bool WeaponESP = false;
		inline bool CurrWeapon = false;
		inline float size = 18.0f;
		inline bool box = false;
		inline bool cornered_box = false;
		inline bool threed = false;
		inline bool distance = false;
		inline bool name = false;
		inline bool console = false;
		inline bool b2Dhead = false;
		inline bool b3Dhead = false;
		inline bool line = false;
		inline bool bAimbot = true;
		inline bool gayskeleton = false;
		inline bool triggerbot = false;
		inline int smoothness = 6;
		inline bool fill = false;
		inline bool show_fov = true;
		inline bool outline = false;
		inline float fov = 80.f;
		inline float AimDistance = 100.f;
		inline int hitbox = 0;
		inline bool prediction = true;
		inline int keybind = 0;
		inline bool Aimline = false;
		inline bool bWeapon = true;
		inline bool humanization = true;
		inline bool bIgnoreDead = false;
		inline bool bIgnoreHidden = false;
		inline bool bIgnoreTeam = false;
		inline bool bIgnoreBots = false;
		inline bool bIgnoreAFK = false;
		inline bool StreamProof = false;
		inline bool ExitThread1 = false;
		inline bool PreformenceMode = false;
		inline bool baboons = false;

		inline bool BulletTraces = false;
		inline bool TPose = false;
		inline bool Allow_Jump_Shoot = false;
		inline bool MagicBullet = false;
		inline bool Backtrack = false;
		inline bool InstaReload = false;
		inline bool bFullAuto = false;
		inline bool bRapidFire = false;
		inline bool bFastWeapons = false;
		inline float fWeaponSpeed = 10.f;
		inline bool bOnlyMale = false;


		inline bool LMouse = false;
		inline bool RMouse = false;
		inline bool LShift = false;
		inline bool LCtrl = false;

		inline bool Head = false;
		inline bool Neck = false;
		inline bool Chest = false;
		inline bool Belly = false;


		namespace color
		{

			//namespace loot {
			//	float lines[3] = { colors.Red[0], colors.Red[1], colors.Red[2] };
			//	float Searchables[3] = { colors.Red[0], colors.Red[1], colors.Red[2] };
			//	float Pickups[3] = { colors.Red[0], colors.Red[1], colors.Red[2] };
			//	float Vehicles[3] = { colors.Red[0], colors.Red[1], colors.Red[2] };
			//}

			inline  float PlayerboxNotVisible[3] = { 1.0f , 1.0f , 1.0f };
			inline  float TeamboxNotVisible[3] = { 1.0f , 1.0f , 1.0f };
			inline  float SkeletonNotVisible[3] = { 1.0f , 1.0f , 1.0f };
			inline  float SnaplinesNotVisible[3] = { 1.0f , 1.0f , 1.0f };

			inline  float PlayerboxVisible[3] = { 1.0f , 1.0f , 1.0f };
			inline  float TeamboxVisible[3] = { 1.0f , 1.0f , 1.0f };
			inline  float SkeletonVisible[3] = { 1.0f , 1.0f , 1.0f };
			inline  float SnaplinesVisible[3] = { 1.0f , 1.0f , 1.0f };
		}
	}

}