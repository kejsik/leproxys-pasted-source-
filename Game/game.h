#pragma once
#include <dwmapi.h>
#include <stdio.h>
#include <string>
#include "../Gui/DrawMenu.h"
#include "../interface/aimbot.h"
#include "../stdafx/stdafx.h"
#include "../stdafx/overlay.h" // PP
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx9.h"
#include "ida.h"
#include "FortniteSDK.h"
#include "../interface/driver.h"
//#include "../stdafx/structs.hpp"

using namespace std;

Vector3 TargetPrediction(Vector3 target, uintptr_t RootComponent, float targetDistance, float projectileGravity, float projectileVelocity)
{
	Vector3 targetVelocity = communication->read_physical_memory<Vector3>(RootComponent + 0x170);

	//float gravity = fabs(projectileGravity);
	//Vector3 delta = target - origin;
	//double time = delta.Magnitude() / projectileVelocity;
	float time = targetDistance / fabs(projectileVelocity); // floating decimal value, should maybe just use it raw
	//float bulletDrop = (gravity / 2) * time * time; // 250

	return target + targetVelocity * time - Vector3(0, 0, projectileGravity * 0.5 * time * time); // bulletDrop 

	//float gravity = fabs(projectileGravity);
	//float time = targetDistance / fabs(projectileVelocity);

	/* Bullet drop correction */
	//float bulletDrop = (gravity / 2) * time * time;

	/* Player movement correction */
//	target.x += time * (targetVelocity.x);
//	target.y += time * (targetVelocity.y);
//	//target.z += time * (targetVelocity.z);
//	target.z += bulletDrop * 100;
//
//	return target;
}


VOID SkeletonESP(AFortPawn* temp_actor, ImColor SkeletonColor)
{
	Vector3 crown, head, neck, chest, leftshoulder, leftbicep, leftelbow, leftwrist, lefthand, rightshoulder, rightbicep, rightelbow, rightwrist, righthand, penis, leftthigh, lefthip, leftcalf, leftjoint, leftfoot, righthip, rightthigh, rightcalf, rightjoint, rightfoot;
	crown = Localplayer->W2S(temp_actor->GetBone(106));
	head = Localplayer->W2S(temp_actor->GetBone(68));
	neck = Localplayer->W2S(temp_actor->GetBone(67));
	chest = Localplayer->W2S(temp_actor->GetBone(7));
	leftshoulder = Localplayer->W2S(temp_actor->GetBone(38));
	leftbicep = Localplayer->W2S(temp_actor->GetBone(65));
	leftelbow = Localplayer->W2S(temp_actor->GetBone(39));
	leftwrist = Localplayer->W2S(temp_actor->GetBone(62));
	lefthand = Localplayer->W2S(temp_actor->GetBone(53));
	rightshoulder = Localplayer->W2S(temp_actor->GetBone(9));
	rightbicep = Localplayer->W2S(temp_actor->GetBone(35));
	rightelbow = Localplayer->W2S(temp_actor->GetBone(10));
	rightwrist = Localplayer->W2S(temp_actor->GetBone(34));
	righthand = Localplayer->W2S(temp_actor->GetBone(16));
	penis = Localplayer->W2S(temp_actor->GetBone(2));
	lefthip = Localplayer->W2S(temp_actor->GetBone(78));
	leftthigh = Localplayer->W2S(temp_actor->GetBone(84));
	leftcalf = Localplayer->W2S(temp_actor->GetBone(79));
	leftjoint = Localplayer->W2S(temp_actor->GetBone(87));
	leftfoot = Localplayer->W2S(temp_actor->GetBone(83));
	righthip = Localplayer->W2S(temp_actor->GetBone(71));
	rightthigh = Localplayer->W2S(temp_actor->GetBone(71));
	rightcalf = Localplayer->W2S(temp_actor->GetBone(86));
	rightjoint = Localplayer->W2S(temp_actor->GetBone(75));
	rightfoot = Localplayer->W2S(temp_actor->GetBone(76));

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(crown.x, crown.y), ImVec2(head.x, head.y), SkeletonColor, 2.f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(head.x, head.y), ImVec2(neck.x, neck.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(neck.x, neck.y), ImVec2(chest.x, chest.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(chest.x, chest.y), ImVec2(leftshoulder.x, leftshoulder.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftshoulder.x, leftshoulder.y), ImVec2(leftbicep.x, leftbicep.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftbicep.x, leftbicep.y), ImVec2(leftelbow.x, leftelbow.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftelbow.x, leftelbow.y), ImVec2(leftwrist.x, leftwrist.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftwrist.x, leftwrist.y), ImVec2(lefthand.x, lefthand.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(chest.x, chest.y), ImVec2(rightshoulder.x, rightshoulder.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightshoulder.x, rightshoulder.y), ImVec2(rightbicep.x, rightbicep.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightbicep.x, rightbicep.y), ImVec2(rightelbow.x, rightelbow.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightelbow.x, rightelbow.y), ImVec2(rightwrist.x, rightwrist.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightwrist.x, rightwrist.y), ImVec2(righthand.x, righthand.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(chest.x, chest.y), ImVec2(penis.x, penis.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(penis.x, penis.y), ImVec2(lefthip.x, lefthip.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(lefthip.x, lefthip.y), ImVec2(leftthigh.x, leftthigh.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftthigh.x, leftthigh.y), ImVec2(leftcalf.x, leftcalf.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftcalf.x, leftcalf.y), ImVec2(leftjoint.x, leftjoint.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(leftjoint.x, leftjoint.y), ImVec2(leftfoot.x, leftfoot.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(penis.x, penis.y), ImVec2(righthip.x, righthip.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(righthip.x, righthip.y), ImVec2(rightthigh.x, rightthigh.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightthigh.x, rightthigh.y), ImVec2(rightcalf.x, rightcalf.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightcalf.x, rightcalf.y), ImVec2(rightjoint.x, rightjoint.y), SkeletonColor, 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(rightjoint.x, rightjoint.y), ImVec2(rightfoot.x, rightfoot.y), SkeletonColor, 2.0f);
}

void game_loop()
{

	auto player = playerList;
	Camera TempCamera = GetCamera();

	if (LeProxy::settings::show_fov)
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(Width / 2, Height / 2), (LeProxy::settings::fov * center_x / TempCamera.FieldOfView), ImColor(0, 0, 0, 255), 2000, 0.9f);

	for (unsigned long i = 0; i < player.size(); ++i)
	{
		AFortPawn* entity = player[i];
		uint64_t mesh = entity->Mesh();
		if (!mesh) continue;

		int MyTeamId = LocalPawn->PlayerState()->TeamIndex();
		int ActorTeamId = entity->PlayerState()->TeamIndex();
		bool IsVisible = entity->WasRecentlyRendered();

		if (LeProxy::settings::CurrWeapon)
		{
			if ((uintptr_t)LocalPawn->CurrentWeapon())
			{
				std::string WeaponName = LocalPawn->CurrentWeapon()->GetWeaponName();
				if (WeaponName.find(TEXT("Assault")) != std::string::npos || WeaponName.find(TEXT("Thermal")) != std::string::npos)
				{
					std::cout << "Assault" << std::endl;
				}
				else if (WeaponName.find(TEXT("SMG")) != std::string::npos)
				{
					std::cout << "SMG" << std::endl;
				}
				else if (WeaponName.find(TEXT("Shotgun")) != std::string::npos)
				{
					std::cout << "Shotgun" << std::endl;
				}
				else if (WeaponName.find(TEXT("Sniper")) != std::string::npos)
				{
					std::cout << "Sniper" << std::endl;
				}
				else if (WeaponName.find(TEXT("Pistol")) != std::string::npos)
				{
					std::cout << "Pistol" << std::endl;
				}
				else
				{
					std::cout << " Unknown Weapon" << WeaponName << std::endl;
				}
			}
		}

		if (entity->ActorFName().find(TEXT("PlayerPawn")) != string::npos ||
			entity->ActorFName().find(TEXT("BP_PlayerPawn")) != string::npos ||
			entity->ActorFName().find(TEXT("PlayerPawn_Athena_C")) != string::npos ||
			entity->ActorFName().find(TEXT("PlayerPawn_Athena_Phoebe_C")) != string::npos) {
			std::cout << " Found fortnite player!" << std::endl;
		}

		float KillScore = communication->read_physical_memory<float>((uintptr_t)LocalPawn + 0x288); // entity 0x58a4
		std::cout << " KillScore " << KillScore << std::endl;

		if (LeProxy::settings::BulletTraces && LocalPawn->CurrentWeapon()) {
			Vector3 LastFiredLocation = communication->read_physical_memory<Vector3>((uintptr_t)LocalPawn + 0x50C8); // 0x4f38
			Vector3 LastFiredDirection = communication->read_physical_memory<Vector3>((uintptr_t)LocalPawn + 0x50E0); // 0x4f50
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LastFiredLocation.x, LastFiredLocation.y), ImVec2(LastFiredDirection.x, LastFiredDirection.y), ImColor(255, 0, 0), 1.0f);
		}

		if (LeProxy::settings::TPose && LocalPawn->Mesh()) {
			communication->write_physical_memory<char>((LocalPawn->Mesh() + 0xa6a) & 0x8, true);
		}

		if (LeProxy::settings::MagicBullet && LocalPawn->Mesh()) {
			uintptr_t UCapsuleComponent = communication->read_physical_memory<uintptr_t>((uintptr_t)entity + 0x320);
			communication->write_physical_memory<Vector3>(UCapsuleComponent + 0x158, Vector3(15, 15, 15));
			communication->write_physical_memory<Vector3>(entity->Mesh() + 0x158, Vector3(1, 1, 1));
		}

		if (LeProxy::settings::Allow_Jump_Shoot && LocalPawn->Mesh()) {
			communication->write_physical_memory<bool>((uintptr_t)LocalPawn + 0x4dd6, true);
		}

		if (LeProxy::settings::bFullAuto && LocalPawn->CurrentWeapon()) {
			uintptr_t UFortWeaponItemDefinition = communication->read_physical_memory<uintptr_t>((uintptr_t)LocalPawn->CurrentWeapon() + offsets::WeaponData);
			int TriggerType = communication->read_physical_memory<int>(UFortWeaponItemDefinition + 0xbfc);
			if (TriggerType != 1) 
				communication->write_physical_memory<int>(UFortWeaponItemDefinition + 0xbfc, 1); // 4 - legendary
		}

		if (LeProxy::settings::bFastWeapons && LocalPawn->CurrentWeapon())
		{
			communication->write_physical_memory<float>(GWorld->PersistentLevel()->AWorldSettings() + 0x390, LeProxy::settings::fWeaponSpeed);
		}

		if (LeProxy::settings::bRapidFire && LocalPawn->CurrentWeapon())
		{
			float LastFireTime, LastFireTimeVerified = 0;
			LastFireTime = communication->read_physical_memory<float>((uintptr_t)LocalPawn->CurrentWeapon() + 0xaf0);
			LastFireTimeVerified = communication->read_physical_memory<float>((uintptr_t)LocalPawn->CurrentWeapon() + 0xaf4);
			communication->write_physical_memory<float>((uintptr_t)LocalPawn->CurrentWeapon() + 0xaf0, LastFireTime + LastFireTimeVerified - 0.333);
		}

		if (LeProxy::settings::InstaReload && LocalPawn->CurrentWeapon()) {
			// Empty
		}



		if (LeProxy::settings::bIgnoreTeam) {
			if (MyTeamId == ActorTeamId) 
				continue;
		}

		if (LeProxy::settings::bIgnoreBots) {
			bool IsBot = communication->read_physical_memory<BYTE>((uintptr_t)entity + 0x292);
			if (!IsBot)
				continue;
		}

		if (LeProxy::settings::bIgnoreDead) {
			bool bIsDying = (communication->read_physical_memory<BYTE>((uintptr_t)entity + 0x710) & 0x10);
			bool bisDBNO = (communication->read_physical_memory<BYTE>((uintptr_t)entity + 0x832) & 0x10);
			if (bisDBNO || bIsDying)
				continue;
		}

		if (LeProxy::settings::bIgnoreAFK) {
			bool bIsInactive = (communication->read_physical_memory<BYTE>((uintptr_t)entity->PlayerState() + 0x292) & 0x20);
			if (!bIsInactive)
				continue;
		}

		if (LeProxy::settings::bIgnoreHidden) {
			if (IsVisible)
				continue;
		}

		Vector3 head3d = entity->GetBone(106);
		Vector3 head2d = Localplayer->W2S(head3d);
		Vector3 bottom3d = entity->GetBone(88); // 0
		Vector3 bottom2d = Localplayer->W2S(bottom3d);
		Vector3 Headbox = Localplayer->W2S(Vector3(head3d.x, head3d.y, head3d.z + 19));
		Vector3 Rootbox = Localplayer->W2S(Vector3(bottom3d.x, bottom3d.y, bottom3d.z - 10));

		double distance = LocalPawn->RootComponent()->RelativeLocation().Distance(bottom3d) / 100;

		if (distance <= LeProxy::settings::MaxDistance)
		{
			if (IsInScreen(bottom2d))
			{

				auto ColorBox = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
				auto ColorSkeleton = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
				auto ColorSnapline = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

				if (MyTeamId != ActorTeamId)
					ColorBox = IsVisible ? ImVec4(LeProxy::settings::color::PlayerboxVisible[0], LeProxy::settings::color::PlayerboxVisible[1], LeProxy::settings::color::PlayerboxVisible[2], 1.0f) : ImVec4(LeProxy::settings::color::PlayerboxNotVisible[0], LeProxy::settings::color::PlayerboxNotVisible[1], LeProxy::settings::color::PlayerboxNotVisible[2], 1.0f);
				else if (MyTeamId == ActorTeamId)
					ColorBox = IsVisible ? ImVec4(LeProxy::settings::color::TeamboxVisible[0], LeProxy::settings::color::TeamboxVisible[1], LeProxy::settings::color::TeamboxVisible[2], 1.0f) : ImVec4(LeProxy::settings::color::TeamboxNotVisible[0], LeProxy::settings::color::TeamboxNotVisible[1], LeProxy::settings::color::TeamboxNotVisible[2], 1.0f);

				ColorSkeleton = IsVisible ? ImVec4(LeProxy::settings::color::SkeletonVisible[0], LeProxy::settings::color::SkeletonVisible[1], LeProxy::settings::color::SkeletonVisible[2], 1.0f) : ImVec4(LeProxy::settings::color::SkeletonNotVisible[0], LeProxy::settings::color::SkeletonNotVisible[1], LeProxy::settings::color::SkeletonNotVisible[2], 1.0f);
				ColorSnapline = IsVisible ? ImVec4(LeProxy::settings::color::SnaplinesVisible[0], LeProxy::settings::color::SnaplinesVisible[1], LeProxy::settings::color::SnaplinesVisible[2], 1.0f) : ImVec4(LeProxy::settings::color::SnaplinesNotVisible[0], LeProxy::settings::color::SnaplinesNotVisible[1], LeProxy::settings::color::SnaplinesNotVisible[2], 1.0f);

				if (LeProxy::settings::box)
				{
					float BoxHeight = Rootbox.y - Headbox.y;
					float BoxWidth = BoxHeight / 1.9f;
					box_esp(4, 4, Rootbox.x - (BoxWidth / 2), Headbox.y,
						BoxWidth, BoxHeight, ImGui::GetColorU32(ColorBox), 1.f,
						LeProxy::settings::fill, LeProxy::settings::outline);

				}
				else if (LeProxy::settings::cornered_box)
				{
					float BoxHeight = Rootbox.y - Headbox.y;
					float BoxWidth = BoxHeight / 1.9f;
					corner_esp(4, 4, Rootbox.x - (BoxWidth / 2), Headbox.y,
						BoxWidth, BoxHeight, ImGui::GetColorU32(ColorBox), 1.f,
						LeProxy::settings::fill, LeProxy::settings::outline);
				}
				else if (LeProxy::settings::threed)
				{
					Vector3 bottom1 = Localplayer->W2S(Vector3(bottom3d.x + 40, bottom3d.y - 40, bottom3d.z));
					Vector3 bottom2 = Localplayer->W2S(Vector3(bottom3d.x - 40, bottom3d.y - 40, bottom3d.z));
					Vector3 bottom3 = Localplayer->W2S(Vector3(bottom3d.x - 40, bottom3d.y + 40, bottom3d.z));
					Vector3 bottom4 = Localplayer->W2S(Vector3(bottom3d.x + 40, bottom3d.y + 40, bottom3d.z));

					Vector3 top1 = Localplayer->W2S(Vector3(head3d.x + 40, head3d.y - 40, head3d.z + 15));
					Vector3 top2 = Localplayer->W2S(Vector3(head3d.x - 40, head3d.y - 40, head3d.z + 15));
					Vector3 top3 = Localplayer->W2S(Vector3(head3d.x - 40, head3d.y + 40, head3d.z + 15));
					Vector3 top4 = Localplayer->W2S(Vector3(head3d.x + 40, head3d.y + 40, head3d.z + 15));

					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), ImGui::GetColorU32(ColorBox), 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), ImGui::GetColorU32(ColorBox), 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(top3.x, top3.y), ImGui::GetColorU32(ColorBox), 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(top4.x, top4.y), ImGui::GetColorU32(ColorBox), 0.1f);

					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), ImGui::GetColorU32(ColorBox), 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(bottom3.x, bottom3.y), ImGui::GetColorU32(ColorBox), 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(bottom4.x, bottom4.y), ImGui::GetColorU32(ColorBox), 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(bottom1.x, bottom1.y), ImGui::GetColorU32(ColorBox), 0.1f);

					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), ImGui::GetColorU32(ColorBox), 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top2.x, top2.y), ImVec2(top3.x, top3.y), ImGui::GetColorU32(ColorBox), 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top3.x, top3.y), ImVec2(top4.x, top4.y), ImGui::GetColorU32(ColorBox), 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top4.x, top4.y), ImVec2(top1.x, top1.y), ImGui::GetColorU32(ColorBox), 0.1f);
				}

				if (LeProxy::settings::distance)
				{
					std::string text_distance = "(" + std::to_string(distance) + "m)";
					ImVec2 text_size = ImGui::CalcTextSize(text_distance.c_str());
					ADrawText(ESPFont, ImVec2(Headbox.x - (text_size.x / 2), Headbox.y - 20), ImColor(255, 255, 255), text_distance.c_str(), LeProxy::settings::size, false);
				}

				if (LeProxy::settings::WeaponESP)
				{
					std::string WeaponName = entity->CurrentWeapon()->GetWeaponName();
					int AmmoCount = communication->read_physical_memory<int>((uintptr_t)entity->CurrentWeapon() + 0xba4);
					bool bIsReloadingWeapon = communication->read_physical_memory<bool>((uintptr_t)entity->CurrentWeapon() + 0x348);

					std::string text_weapon = bIsReloadingWeapon ? ("reloading") : (WeaponName + " (" + std::to_string(AmmoCount) + ")");

					ImVec2 Textsize = ImGui::CalcTextSize(text_weapon.c_str());
					ADrawText(ESPFont, ImVec2(Rootbox.x - (Textsize.x / 2), Rootbox.y + 10), ImColor(255, 255, 255), text_weapon.c_str(), LeProxy::settings::size, false);
				}

				if (LeProxy::settings::name)
				{
					std::string name_buff = entity->PlayerState()->GetPlayerName();
					if (!name_buff.empty() || name_buff.length() < FLT_MAX) {
						ImVec2 text_size = ImGui::CalcTextSize(name_buff.c_str());
						ADrawText(ESPFont, ImVec2(Rootbox.x - (text_size.x / 2), Rootbox.y + 10), ImColor(255, 255, 255), name_buff.c_str(), LeProxy::settings::size, false);
					}
				}

				if (LeProxy::settings::console)
				{
					std::string str_platform = entity->PlayerState()->GetPlatformName();
					ImVec2 TextSize = ImGui::CalcTextSize(str_platform.c_str());

					if (!str_platform.empty() || str_platform.length() < FLT_MAX && strstr(str_platform.c_str(), ("WIN"))) {
						ADrawText(ESPFont, ImVec2((Rootbox.x) - (TextSize.x / 2), (Rootbox.y - 20)), ImColor(255, 255, 255), "Windows");
					}
					else if (!str_platform.empty() || str_platform.length() < FLT_MAX && strstr(str_platform.c_str(), ("XBL")) || strstr(str_platform.c_str(), ("XSX"))) {
						ADrawText(ESPFont, ImVec2((Rootbox.x) - (TextSize.x / 2), (Rootbox.y - 20)), ImColor(255, 255, 255), "Xbox");
					}
					else if (!str_platform.empty() || str_platform.length() < FLT_MAX && strstr(str_platform.c_str(), ("PSN")) || strstr(str_platform.c_str(), ("PS5"))) {
						ADrawText(ESPFont, ImVec2((Rootbox.x) - (TextSize.x / 2), (Rootbox.y - 20)), ImColor(255, 255, 255), "PlayStation");
					}
					else if (!str_platform.empty() || str_platform.length() < FLT_MAX && strstr(str_platform.c_str(), ("SWT"))) {
						ADrawText(ESPFont, ImVec2((Rootbox.x) - (TextSize.x / 2), (Rootbox.y - 20)), ImColor(255, 255, 255), "NintendoSwitch");
					}
					else if (!str_platform.empty() || str_platform.length() < FLT_MAX && strstr(str_platform.c_str(), ("MAC"))) {
						ADrawText(ESPFont, ImVec2((Rootbox.x) - (TextSize.x / 2), (Rootbox.y - 20)), ImColor(255, 255, 255), "MacOS");
					}
					else if (!str_platform.empty() || str_platform.length() < FLT_MAX && strstr(str_platform.c_str(), ("LNX"))) {
						ADrawText(ESPFont, ImVec2((Rootbox.x) - (TextSize.x / 2), (Rootbox.y - 20)), ImColor(255, 255, 255), "Linux");
					}
					else if (!str_platform.empty() || str_platform.length() < FLT_MAX && strstr(str_platform.c_str(), ("IOS"))) {
						ADrawText(ESPFont, ImVec2((Rootbox.x) - (TextSize.x / 2), (Rootbox.y - 20)), ImColor(255, 255, 255), "IOS");
					}
					else if (!str_platform.empty() || str_platform.length() < FLT_MAX && strstr(str_platform.c_str(), ("AND"))) {
						ADrawText(ESPFont, ImVec2((Rootbox.x) - (TextSize.x / 2), (Rootbox.y - 20)), ImColor(255, 255, 255), "Android");
					}
				}

				if (LeProxy::settings::gayskeleton)
				{
					SkeletonESP(entity, ImGui::GetColorU32(ColorSkeleton));
				}

				if (LeProxy::settings::line)
				{
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center_x, Height), ImVec2(bottom2d.x, bottom2d.y), ImColor(255, 255, 255), 0.5f);
				}

			}

		}

		if (LeProxy::settings::bWeapon) {
			if (LocalPawn->CurrentWeapon())
				continue;
		}

		if (LeProxy::settings::bOnlyMale)
		{
			bool bIsMale = communication->read_physical_memory<BYTE>((uintptr_t)entity + 0x5A24); // 0x58a4
			if (!bIsMale)
				continue;
		}

		Vector3 rootHeadOut = { Vector3(0, 0, 0) };
		static int BindedKey = 0;

		if (LeProxy::settings::Head)
			Vector3 rootHead = Localplayer->W2S(entity->GetBone(106));
		else if (LeProxy::settings::Neck)
			Vector3 rootHead = Localplayer->W2S(entity->GetBone(66));
		else if (LeProxy::settings::Chest)
			Vector3 rootHead = Localplayer->W2S(entity->GetBone(7));
		else if (LeProxy::settings::Belly)
			Vector3 rootHead = Localplayer->W2S(entity->GetBone(3));

		if (LeProxy::settings::RMouse)
			BindedKey = VK_RBUTTON;
		else if (LeProxy::settings::LMouse)
			BindedKey = VK_LBUTTON;
		else if (LeProxy::settings::LShift)
			BindedKey = VK_LSHIFT;
		else if (LeProxy::settings::LCtrl)
			BindedKey = VK_LCONTROL;

		if (LeProxy::settings::prediction)
		{
			rootHeadOut = TargetPrediction(rootHeadOut, (uintptr_t)entity->RootComponent(), distance, 35, -504);
		}

		double dx = rootHeadOut.x - center_x;
		double dy = rootHeadOut.y - center_y;
		auto dist = sqrtf(dx * dx + dy * dy);

		if (LeProxy::settings::bAimbot)
		{
			if (LeProxy::settings::Aimline && bIsInRectangle(center_x, center_y, (float)(LeProxy::settings::fov * center_x / TempCamera.FieldOfView), rootHeadOut.x, rootHeadOut.y))
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center_x, center_y), ImVec2(rootHeadOut.x, rootHeadOut.y), ImColor(255, 0, 0), 0.5f);

			if (GetAsyncKeyState(BindedKey)) {
				if ((int)rootHeadOut.x != 0 && (int)rootHeadOut.y != 0) {
					if (bIsInRectangle(center_x, center_y, (float)(LeProxy::settings::fov * center_x / TempCamera.FieldOfView), rootHeadOut.x, rootHeadOut.y)) {
						if (dist <= LeProxy::settings::fov * 2) {
							if (GetDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, center_x, center_y) <= LeProxy::settings::fov) {
								mouse(rootHeadOut.x, rootHeadOut.y, LeProxy::settings::smoothness);
								if (LeProxy::settings::Backtrack)
									communication->write_physical_memory<float>((uintptr_t)entity + 0x64, 0);
							}
						}
					}
				}
			}

			if (!LeProxy::settings::Backtrack)
				communication->write_physical_memory<float>((uintptr_t)entity + 0x64, 1);
		}

		if (LeProxy::settings::triggerbot)
		{
			if (entity->WasRecentlyRendered()) {
				if ((int)rootHeadOut.x != 0 && (int)rootHeadOut.y != 0) {
					if (bIsInRectangle(center_x, center_y, (float)(LeProxy::settings::fov * center_x / TempCamera.FieldOfView), rootHeadOut.x, rootHeadOut.y)) {
						if (dist <= LeProxy::settings::fov * 2) {
							if (GetDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, center_x, center_y) <= LeProxy::settings::fov) {
								//PostMessageA(render::hijacked_hwnd, MOUSEEVENTF_LEFTDOWN, NULL, NULL);
								//PostMessageA(render::hijacked_hwnd, MOUSEEVENTF_LEFTUP, NULL, NULL);
								mouse_event(MOUSEEVENTF_LEFTDOWN, DWORD(NULL), DWORD(NULL), DWORD(0x0002), ULONG_PTR(NULL));
								mouse_event(MOUSEEVENTF_LEFTUP, DWORD(NULL), DWORD(NULL), DWORD(0x0004), ULONG_PTR(NULL));
							}
						}
					}
				}
			}
		}
	}
}

VOID WorldESP()
{
	DWORD itemCount = communication->read_physical_memory<DWORD>((uintptr_t)GWorld + (offsets::levels + sizeof(PVOID)));
	ImDrawList* Draw = ImGui::GetBackgroundDrawList();

	for (int i = 0; i < itemCount; i++)
	{
		uintptr_t levels_array = communication->read_physical_memory<uintptr_t>((uintptr_t)GWorld + 0x170);// iterating uworld->ulevels

		if (levels_array)
		{

			for (auto i = 0UL; i < communication->read_physical_memory<DWORD>((uintptr_t)GWorld + (0x170 + sizeof(PVOID))); ++i)
			{
				if (i >= communication->read_physical_memory<int>((uintptr_t)GWorld + 0x170))
					break;

				uintptr_t persistent_level = communication->read_physical_memory<uintptr_t>(levels_array + (i * sizeof(uintptr_t)));

				if (persistent_level)
				{
					if (communication->read_physical_memory<int>(persistent_level + 0xA0) <= 0x2328)
					{
						for (int j = 0; communication->read_physical_memory<DWORD>(persistent_level + (0xA0 + sizeof(PVOID))); ++j)
						{
							if (j >= communication->read_physical_memory<int>(persistent_level + 0xA0))
								break;

							uintptr_t actor_array = communication->read_physical_memory<uintptr_t>(persistent_level + 0x98);
							if (actor_array)
							{
								uintptr_t actor_addr = communication->read_physical_memory<uintptr_t>(actor_array + (j * sizeof(uintptr_t)));
								if (actor_addr)
								{
									INT32 objectID = communication->read_physical_memory<int>(actor_addr + 0x18);
									std::string ItemFName = GetObjectName(objectID);

									uintptr_t actor_rootcomponent = communication->read_physical_memory<uintptr_t>(offsets::RootComponent + actor_addr);
									if (actor_rootcomponent)
										break;

									Vector3 Location = communication->read_physical_memory<Vector3>(actor_rootcomponent + 0x128);
									Vector3 ScreenPosition = Localplayer->W2S(Location);

									if (strstr(ItemFName.c_str(), ("FortPickupAthena")) || strstr(ItemFName.c_str(), ("Tiered_Chest")) || strstr(ItemFName.c_str(), ("Tiered_Ammo")) || strstr(ItemFName.c_str(), ("Vehicle")))
									{
										std::string DisplayName = "Object";
										auto Size = ImGui::CalcTextSize(DisplayName.c_str());
										int ScreenX = ScreenPosition.x - (Size.x / 2);
										int ScreenY = ScreenPosition.y;

										Draw->AddText(ImVec2(ScreenX, ScreenY), ImColor(255, 255, 255), DisplayName.c_str());
										Draw->AddLine(ImVec2(center_x, center_y), ImVec2(ScreenPosition.x, ScreenPosition.y + 14), ImColor(255, 255, 255), 1.f);
									}

								}
							}
						}
					}
				}

			}

		}


	}

}

VOID render_loop()
{
	static RECT old_rc;
	RtlSecureZeroMemory(&DirectX9Interface::message, sizeof(MSG));
	while (DirectX9Interface::message.message != WM_QUIT)
	{
		if (PeekMessageA(&DirectX9Interface::message, DirectX9Interface::hijacked_hwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&DirectX9Interface::message);
			DispatchMessageA(&DirectX9Interface::message);
		}

		RECT rc;
		POINT xy;
		RtlSecureZeroMemory(&rc, sizeof(RECT));
		RtlSecureZeroMemory(&xy, sizeof(POINT));
		GetClientRect(DirectX9Interface::game_wnd, &rc);
		ClientToScreen(DirectX9Interface::game_wnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = DirectX9Interface::game_wnd;
		Width = io.DisplaySize.x;
		Height = io.DisplaySize.y;
		center_x = io.DisplaySize.x / 2;
		center_y = io.DisplaySize.y / 2;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(0x1))
		{
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
		{
			io.MouseDown[0] = false;
		}
		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;
			DirectX9Interface::p_params.BackBufferWidth = Width;
			DirectX9Interface::p_params.BackBufferHeight = Height;
			SetWindowPos(DirectX9Interface::hijacked_hwnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			DirectX9Interface::p_device->Reset(&DirectX9Interface::p_params);
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		gui::render();
		game_loop();

		ImGui::EndFrame();

		DirectX9Interface::p_device->SetRenderState(D3DRS_ZENABLE, false);
		DirectX9Interface::p_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		DirectX9Interface::p_device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		DirectX9Interface::p_device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
		if (DirectX9Interface::p_device->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			DirectX9Interface::p_device->EndScene();
		}
		HRESULT result = DirectX9Interface::p_device->Present(NULL, NULL, NULL, NULL);
		if (result == D3DERR_DEVICELOST && DirectX9Interface::p_device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			DirectX9Interface::p_device->Reset(&DirectX9Interface::p_params);
			ImGui_ImplDX9_CreateDeviceObjects();
		}

	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	if (DirectX9Interface::p_device != NULL)
	{
		DirectX9Interface::p_device->EndScene();
		DirectX9Interface::p_device->Release();
	}
	if (DirectX9Interface::p_object != NULL)
	{
		DirectX9Interface::p_object->Release();
	}
	DestroyWindow(DirectX9Interface::hijacked_hwnd);
}