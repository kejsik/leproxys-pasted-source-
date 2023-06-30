#pragma once
#include <d3d9.h>
#include <vector>
#include <iostream>
#include "../interface/driver.h"
#include "../stdafx/structs.h" // pp

enum offsets : ptrdiff_t
{
	Gworld = 0xF1BEEE8, // 0xF1BEEE8
	WorldSettings = 0x150,
	OwningGameInstance = 0x1b8,
	PlayerCameraManager = 0x340,
	AcknowledgedPawn = 0x330,
	PlayerState = 0x2A8,
	PlayerArray = 0x2A0,
	RootComponent = 0x190,
	RelativeLocation = 0x2E8,
	CurrentWeapon = 0x908, // 0x8F8
	WeaponData = 0x410, // 0x8F8
	mesh = 0x310,
	levels = 0x170,
	Tier = 0x73,
	TeamID = 0x10b8,
	GameStates = 0x158,
};

struct Camera
{
	Vector3 Location;
	Vector3 Rotation;
	float FieldOfView;
	char Useless[0x18];
};

Camera GetCamera();
std::string GetObjectName(int key);

class ARootComponent
{
public:

	Vector3 RelativeLocation()
	{
		return communication->read_physical_memory<Vector3>((uintptr_t)this + offsets::RelativeLocation);
	}

};

class APlayerState
{
public:

	int TeamIndex()
	{
		return communication->read_physical_memory<int>((uintptr_t)this + offsets::TeamID);
	}

	std::string GetPlatformName()
	{
		if (!(uintptr_t)this) 
			return "";

		uintptr_t pNameStructure = communication->read_physical_memory<uintptr_t>((uintptr_t)this + 0x430);
		auto pNameLength = communication->read_physical_memory<int>(pNameStructure + 0x10);
		if (pNameLength <= 0) return "";

		wchar_t* pNameBuffer = new wchar_t[pNameLength];
		communication->read_physical_memory(pNameStructure, &pNameBuffer, pNameLength * sizeof(wchar_t));
		std::wstring temp_wstring(pNameBuffer);
		return std::string(temp_wstring.begin(), temp_wstring.end());
	}

	std::string GetPlayerName()
	{
		if (!(uintptr_t)this) 
			return "";

		int pNameLength; // rsi
		char v21; // al
		int v22; // r8d
		int i; // ecx
		int v25; // eax
		_WORD* v23;

		__int64 pNameStructure = communication->read_physical_memory<__int64>((uintptr_t)this + 0xAC8);
		pNameLength = communication->read_physical_memory<int>(pNameStructure + 16);
		__int64 v6 = pNameLength;
		if (!v6) return std::string("bot");

		wchar_t* pNameBuffer = new wchar_t[pNameLength];
		uintptr_t pNameEncryptedBuffer = communication->read_physical_memory<__int64>(pNameStructure + 8);
		communication->read_physical_memory(pNameEncryptedBuffer, &pNameBuffer, pNameLength * sizeof(wchar_t));

		v21 = v6 - 1;
		if (!(_DWORD)v6)
			v21 = 0;
		v22 = 0;
		v23 = (_WORD*)pNameBuffer;

		for (i = (v21) & 3; ; *v23++ += i & 7)
		{
			v25 = v6 - 1;
			if (!(_DWORD)v6)
				v25 = 0;

			if (v22 >= v25)
				break;

			i += 3;
			++v22;
		}

		std::wstring Temp{ pNameBuffer };
		return std::string(Temp.begin(), Temp.end());
	}
};

class APlayerCameraManager {
public:
	Camera GetCameraCache() const {
		if (!(uintptr_t)this) return GetCamera();
		return communication->read_physical_memory<Camera>((uintptr_t)this + 0x2A80 + 0x10);
	}

	float GetDefaultFOV() const {
		if (!(uintptr_t)this) return 0.f;
		return communication->read_physical_memory<float>((uintptr_t)this + 0x29c);
	}

	//float GetViewAngles() const {
	//	if (!(uintptr_t)this) return 0.f;
	//	float ViewRollMax = communication->read_physical_memory<float>((uintptr_t)this + 0x3328);
	//	float ViewRollMin = communication->read_physical_memory<float>((uintptr_t)this + 0x331c);
	//	float ViewYawMax = communication->read_physical_memory<float>((uintptr_t)this + 0x3320);
	//	float ViewYawMin = communication->read_physical_memory<float>((uintptr_t)this + 0x331c);
	//	float ViewPitchMin = communication->read_physical_memory<float>((uintptr_t)this + 0x3318);
	//	float ViewPitchMax = communication->read_physical_memory<float>((uintptr_t)this + 0x3314);
	//}

};

class AFortWeapon {
public:
	std::string GetWeaponName() const {
		if (!(uintptr_t)this) return "";

		auto itemdef = communication->read_physical_memory<uint64_t>((uintptr_t)this + offsets::WeaponData); // WeaponData		
		if (!itemdef) return "";
		auto DisplayName = communication->read_physical_memory<uint64_t>(itemdef + 0x98); // FText->DisplayName FText
		if (!DisplayName) return "";
		auto WeaponLength = communication->read_physical_memory<uint32_t>(DisplayName + 0x40); // FText->Length
		wchar_t* WeaponName = new wchar_t[uint64_t(WeaponLength) + 1];

		communication->read_physical_memory((ULONG64)communication->read_physical_memory<PVOID>(DisplayName + 0x38), WeaponName, WeaponLength * sizeof(wchar_t));

		std::wstring wWeaponName(WeaponName);
		return std::string(wWeaponName.begin(), wWeaponName.end());
	}
};

class AFortPawn
{
public:
	uint64_t Mesh()
	{
		return communication->read_physical_memory<uint64_t>((uintptr_t)this + offsets::mesh);
	}

	std::string ActorFName()
	{
		if (!(uintptr_t)this) return "";
		INT32 ObjectID = communication->read_physical_memory<int>((uintptr_t)this + 0x18);
		return GetObjectName(ObjectID);
	}

	auto WasRecentlyRendered(float Tolerance = 0.015f) -> bool
	{
		auto fLastSubmitTime = communication->read_physical_memory<float>(this->Mesh() + 0x360);
		auto fLastRenderTimeOnScreen = communication->read_physical_memory<float>(this->Mesh() + 0x368);
		bool OverlappingBuildings = communication->read_physical_memory<BYTE>((uintptr_t)this + 0x1b10);
		return fLastRenderTimeOnScreen + Tolerance >= fLastSubmitTime && !OverlappingBuildings;
	}

	Vector3 GetBone(int id)
	{
		int is_cached = communication->read_physical_memory<int>(this->Mesh() + 0x648);
		auto bone_transform = communication->read_physical_memory<FTransform>(communication->read_physical_memory<uintptr_t>(this->Mesh() + 0x10 * is_cached + 0x600) + 0x60 * id);

		FTransform ComponentToWorld = communication->read_physical_memory<FTransform>(this->Mesh() + 0x240); //0x240 = ComponentToWorldOffset, doesnt change a lot

		D3DMATRIX Matrix;
		Matrix = MatrixMultiplication(bone_transform.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

		return Vector3(Matrix._41, Matrix._42, Matrix._43);
	}

	APlayerState* PlayerState()
	{
		if (!(uintptr_t)this) return 0;
		return (APlayerState*)communication->read_physical_memory<uintptr_t>((uintptr_t)this + offsets::PlayerState);
	}

	AFortWeapon* CurrentWeapon()
	{
		if (!(uintptr_t)this) return 0;
		return communication->read_physical_memory<AFortWeapon*>((uintptr_t)this + offsets::CurrentWeapon);
	}

	ARootComponent* RootComponent()
	{
		if (!(uintptr_t)this) return 0;
		return (ARootComponent*)communication->read_physical_memory<uintptr_t>((uintptr_t)this + offsets::RootComponent);
	}
};

class APlayerController
{
public:
	AFortPawn* AcknowledgedPawn()
	{
		if (!(uintptr_t)this) return 0;
		return (AFortPawn*)communication->read_physical_memory<uintptr_t>((uintptr_t)(this + offsets::AcknowledgedPawn));
	}

	APlayerCameraManager* PlayerCameraManager() {
		if (!(uintptr_t)this) return 0;
		return (APlayerCameraManager*)communication->read_physical_memory<uintptr_t>((uintptr_t)this + offsets::PlayerCameraManager);
	}

};

class ULocalPlayer {
public:
	Vector3 W2S(Vector3 WorldLocation)
	{
		Camera ViewPoint = GetCamera();

		D3DMATRIX tempMatrix = Matrix(ViewPoint.Rotation);

		Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

		Vector3 vDelta = WorldLocation - ViewPoint.Location;
		Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.z < 1.f)
			vTransformed.z = 1.f;

		return Vector3((Width / 2.0f) + vTransformed.x * (((Width / 2.0f) / tanf(ViewPoint.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, (Height / 2.0f) - vTransformed.y * (((Width / 2.0f) / tanf(ViewPoint.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, 0);
	}

	APlayerController* PlayerController()
	{
		return (APlayerController*)communication->read_physical_memory<uintptr_t>((uintptr_t)this + 0x30);
	}
};

class ULocalPlayers {
public:
	ULocalPlayer* LocalPlayer()
	{
		return (ULocalPlayer*)communication->read_physical_memory<uintptr_t>((uintptr_t)this);
	}
};

class ULevel {
public:
	uintptr_t AWorldSettings() {
		return communication->read_physical_memory<uintptr_t>((uintptr_t)this + offsets::WorldSettings);
	}
};

class UGameInstance {
public:
	ULocalPlayers* LocalPlayers()
	{
		return (ULocalPlayers*)communication->read_physical_memory<uintptr_t>((uintptr_t)this + 0x38);
	}
};

class AGameStateBase {
public:
	uintptr_t PlayerArray()
	{
		return (communication->read_physical_memory<uintptr_t>((uintptr_t)this + offsets::GameStates));
	}

	int GetPlayerCount()
	{
		return (communication->read_physical_memory<int>((uintptr_t)this + (0x2A0 + sizeof(uintptr_t))));
	}

};

class UWorld
{
public:
	UGameInstance* GameInstance()
	{
		return (UGameInstance*)communication->read_physical_memory<uintptr_t>((uintptr_t)this + offsets::OwningGameInstance);
	}

	AGameStateBase* GameSate()
	{
		return (AGameStateBase*)communication->read_physical_memory<uintptr_t>((uintptr_t)this + offsets::GameStates);
	}

	ULevel* PersistentLevel()
	{
		return (ULevel*)communication->read_physical_memory<uintptr_t>((uintptr_t)this + 0x30);
	}

};

UWorld* GWorld;
std::vector<AFortPawn*> playerList;
AFortPawn* LocalPawn;
ULocalPlayer* Localplayer;
APlayerController* PlayerController;
AGameStateBase* GameState;
int Players;

void actor_cache() 
{
	using namespace std::chrono;
	std::vector<AFortPawn*> temp_array;
	temp_array.reserve(Players);

	while (true)
	{
		temp_array.clear();
		GWorld = communication->read_physical_memory<UWorld*>(hook::base_address + offsets::Gworld);
		auto Gameinstance = GWorld->GameInstance();
		GameState = GWorld->GameSate();
		Localplayer = Gameinstance->LocalPlayers()->LocalPlayer();
		PlayerController = Localplayer->PlayerController();
		LocalPawn = PlayerController->AcknowledgedPawn();

		Players = GameState->GetPlayerCount();
		for (int i = 0; i < Players; i++)
		{
			APlayerState* PlayerState = communication->read_physical_memory<APlayerState*>((uintptr_t)GameState->PlayerArray() + (i * sizeof(uintptr_t)));
			AFortPawn* CurrentActor = communication->read_physical_memory<AFortPawn*>((uintptr_t)PlayerState + 0x300);
			if (!CurrentActor || CurrentActor == LocalPawn) 
				continue;

			uintptr_t mesh = communication->read_physical_memory<uintptr_t>((uintptr_t)CurrentActor + 0x310);
			if (!mesh) continue;

			uintptr_t playerRoot = communication->read_physical_memory<uintptr_t>((uintptr_t)CurrentActor + offsets::RootComponent);
			Vector3 distance = communication->read_physical_memory<Vector3>(playerRoot + offsets::RelativeLocation);
			double PlayerDistance = LocalPawn->RootComponent()->RelativeLocation().Distance(distance);
			if (PlayerDistance >= LeProxy::settings::MaxDistance)
				continue;

			temp_array.push_back(CurrentActor);
		}

		playerList = std::move(temp_array);  
		if (LeProxy::settings::PreformenceMode)
			std::this_thread::sleep_for(milliseconds(5));
	}

}

Camera GetCamera()
{
	char v1; // r8
	Camera ViewPoint = communication->read_physical_memory<Camera>(hook::base_address + 0xF0E8BD0); 
	BYTE* v2 = (BYTE*)&ViewPoint;
	int i; // edx
	__int64 result; // rax

	v1 = 0x40;
	for (i = 0; i < 0x40; ++i)
	{
		*v2 ^= v1;
		result = (unsigned int)(i + 0x17);
		v1 += i + 0x17;
		v2++;
	}

	return ViewPoint;
}

std::string GetNameFromFName(int key)
{
	uint64_t NamePoolChunk = communication->read_physical_memory<uint64_t>(hook::base_address + 0xf226880 + (8 * (uint32_t)((int)(key) >> 16)) + 16) + (unsigned int)(4 * (uint16_t)key);
	uint16_t nameEntry = communication->read_physical_memory<uint16_t>(NamePoolChunk);
	char buff[1024];

	int nameLength = nameEntry >> 6;

	if ((uint32_t)nameLength)
	{
		for (int x = 0; x < nameLength; ++x)
		{

		}

		char* v2; // rdi
		int v4; // ebx
		int v5; // edx
		int v6; // ecx
		int v7; // ecx
		__int16 v8; // ax

		v2 = buff;
		v4 = nameLength;
		v8 = communication->read_physical_memory<_QWORD>(hook::base_address + 0x3022da8);
		v5 = 0;
		v6 = 38;
		if (v4)
		{
			do
			{
				v7 = v5++ | v6;
				v8 = v7;
				v6 = 2 * v7;
				*v2++ ^= ~v8;
			} while (v5 < v4);
		}

		buff[nameLength] = '\0';
		return std::string(buff);
	}
	else {
		return "";
	}
}

std::string GetObjectName(int key)
{
	uint64_t NamePoolChunk = communication->read_physical_memory<uint64_t>(hook::base_address + 0xf226880 + (8 * (uint32_t)((int)(key) >> 16)) + 16) + (unsigned int)(4 * (uint16_t)key);
	if (communication->read_physical_memory<uint16_t>(NamePoolChunk) < 64)
	{
		auto a1 = communication->read_physical_memory<DWORD>(NamePoolChunk + 4);
		return GetNameFromFName(a1);
	}
	else
	{
		return GetNameFromFName(key);
	}
}

 bool IsInScreen(Vector3 pos, int over = 30) {
	if (pos.x > -over && pos.x < Width + over && pos.y > -over && pos.y < Height + over) {
		return true;
	}
	else {
		return false;
	}
}