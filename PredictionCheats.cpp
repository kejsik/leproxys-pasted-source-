#include <Windows.h>
#include <string>
#include <thread>
#include <TlHelp32.h>
#include <iostream>
#include "Game/game.h"
#include "interface/driver.h"
#include "protect/antiDbg.h"
#include "protect/SDK/obsidium64.h"
#include "protect/blowfish/blowfish.h"
#include "PredictionCheats.h"
#include "stdafx/stdafx.h"
#define ulong unsigned long

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)(__DATE__);
const std::string compilation_time = (std::string)(__TIME__);

DWORD FindProcessID(string name) {
    PROCESSENTRY32 ProcessEntry;
    ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &ProcessEntry) == (int)1) {
        while (Process32Next(snapshot, &ProcessEntry) == (int)1) {
            if (string(ProcessEntry.szExeFile) == name)
                return ProcessEntry.th32ProcessID;
        }
    }

    CloseHandle(snapshot);
    return NULL;
}

 int main()
 {
	 OBSIDIUM_VM_START;
	 OBSIDIUM_ENC_START;

	 were();
	 awer();
	 abwe();
	 bart();

	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x2);
	 std::thread(security_loop).detach();
	 LI_FN(SetConsoleTitleA)((""));

	 system_no_output(xorstr("taskkill /F /T /IM FortniteClient-Win64-Shipping.exe"));
	 system_no_output(xorstr("taskkill/F /T /IM EpicGamesLauncher.exe"));

	 WSADATA ws; // checks host connection
	 if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
		 Sleep(2000);
		 exit(-1);
	 }

	 const char* host = "keyauth.win"; // checks keyauths connection
	 struct hostent* host_info = gethostbyname(host);
	 if (!host_info) {
		 cout << xorstr(" No stable internet connection found.") << endl;
		 Sleep(2000);
		 exit(-1);
	 }

	 LI_FN(Sleep)(1000);
	 LI_FN(system)("CLS");
	 KeyAuthApp.init();
	 if (!KeyAuthApp.data.success) {
		 std::cout << xorstr(" Auth Error: Failed to init Keyauth") << endl;
		 LI_FN(Sleep)(2000);
		 return 0;
	 }
	// KeyAuthApp.webhook("", "", "{\"content\": \" Packet Sent \",\"embeds\": null}", "application/json");
	 KeyAuthApp.check();
	 std::cout << xorstr("\n Auth Validation Status : ") << KeyAuthApp.data.message << std::endl;
	 std::cout << xorstr(" Connected to host!") << endl;
	 LI_FN(Sleep)(2000);
	 LI_FN(system)("CLS");
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x5);
	 //ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	 std::ifstream myFile("key.txt");
	 if (!myFile.fail())
	 {
		 if (std::filesystem::exists("key.txt"))
		 {
			 std::cout << xorstr("\n Found a Existing Key");
			 Sleep(1000);

			 std::string regfile("key.txt");
			 std::string license; //get key from txt
			 license = readFileIntoString(regfile);

			 KeyAuthApp.license(license);
			 if (!KeyAuthApp.data.success)
				 DeleteKey(myFile);
		 }
	 }
	 else if (myFile.fail())
	 {
		 std::cout << xorstr("\n Enter license: ");
		 std::string key;
		 std::cin >> key;
		 KeyAuthApp.license(key);
		 if (!KeyAuthApp.data.success)
		 {
			 DeleteKey(myFile);
			 std::cout << xorstr(" Status: ") << KeyAuthApp.data.message;
			 LI_FN(Sleep)(1500);
			 exit(0);
		 }
		 else
		 {
			 std::ofstream myfile;
			 myfile.open("key.txt");
			 myfile << key;
			 myfile.close();
		 }
	 }
	 KeyAuthApp.check();
	 if (!KeyAuthApp.data.success)
	 {
		 DeleteKey(myFile);
		 std::cout << xorstr("\n Status: ") << KeyAuthApp.data.message;
		 LI_FN(Sleep)(1500);
		 exit(0);
	 }
	 LI_FN(Sleep)(2000);
	 LI_FN(system)("CLS");
	 LI_FN(SetConsoleTitleA)(("PredictionCheats"));
	 KeyAuthApp.check();
	 std::cout << xorstr("\n Auth Status : ") << KeyAuthApp.data.message;
	 for (int i = 0; i < KeyAuthApp.data.subscriptions.size(); i++) { // Prompto#7895 was here
		 auto sub = KeyAuthApp.data.subscriptions.at(i); // intended copies
		 std::cout << skCrypt("\n username: ") << sub.name;
		 std::cout << skCrypt("\n expiry: ") << tm_to_readable_time(timet_to_tm(string_to_timet(sub.expiry)));
		 std::cout << skCrypt("\n login date: ") << __DATE__;
	 }
	 LI_FN(Sleep)(5000);
	 LI_FN(system)("CLS");
	 KeyAuthApp.check();
	 if (KeyAuthApp.data.success)
	 {
		 std::string webhook_message = "\" User logged in, License: " + KeyAuthApp.data.username + " | HWID: " + KeyAuthApp.data.hwid + " | IP: " + KeyAuthApp.data.ip + " | Status Validation: " + KeyAuthApp.data.message + "\"";
		 std::string webhook_command = "{\"content\": " + webhook_message + ",\"embeds\": null}";
		 KeyAuthApp.webhook("D1CQsskK06", "", webhook_command, "application/json");
		 if (!KeyAuthApp.data.success)
		 {
			 std::cout << xorstr(" Error fetching data.") << endl;
			 Sleep(1500);
			 exit(-1);
		 }
	 }
	 else
	 {
		 std::cout << xorstr("\n Status: ") << KeyAuthApp.data.message;
		 LI_FN(Sleep)(1500);
		 exit(0);
	 }
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x2);
	 std::cout << xorstr(" Loading driver..") << std::endl;
	 std::vector<std::uint8_t> bytes = KeyAuthApp.download("592139");
	 if (!KeyAuthApp.data.success)
	 {
		 std::cout << xorstr(" Driver Error: Failed to initialize driver") << endl;
		 Sleep(1500);
		 exit(-1);
	 }
	 for (unsigned long i = 0; i < bytes.size(); i++)
	 {
		 auto driver_status = std::search(bytes.begin(), bytes.end(), bytes.begin(), bytes.end());
		 if (driver_status == bytes.begin())
		 {
			 if (!bytes.empty())
			 {
				 if (!MapDriver(bytes.data())) {
					 cout << xorstr(" Failed to load driver.") << endl;
					 Sleep(2000);
					 exit(-2);
				 }
				 LI_FN(Sleep)(200);

				 if (!bytes.empty())
					 bytes.erase(bytes.begin(), bytes.end());

				 auto temp_current_status = std::search(bytes.begin(), bytes.end(), bytes.begin(), bytes.end());
				 if (temp_current_status == bytes.begin()) {
					 if (!bytes.empty())
						 bytes.clear();
				 }

				 KeyAuthApp.check();
				 Sleep(1);
			 }
		 }
		 else
		 {
			 cout << xorstr(" Failed to load driver.") << endl;
			 Sleep(2000);
			 exit(-2);
		 }
	 }
	if (!communication->initialize()) {
		cout << xorstr(" Error: Failed to initialize driver.") << endl;
		Sleep(2000);
		exit(-2);
	}
	cout << endl << xorstr(" Driver is loaded.") << endl;
	LI_FN(Sleep)(2000);
	LI_FN(system)("CLS");

	std::cout << xorstr("\n Waiting for FortniteClient-Win64-Shipping.exe") << std::endl;

	while (true) {
		auto FnCheck = LI_FN(FindWindowA)("UnrealWindow", "Fortnite  ");
		if (FnCheck)
			break;
	}

	hook::process_id = FindProcessID("FortniteClient-Win64-Shipping.exe");
	if (!hook::process_id) {
		std::cout << (" Driver Error: Failed to get games PID please restart and remap driver") << endl;
		LI_FN(Sleep)(2000);
		return 0;
	}

	communication->attach(hook::process_id);
	hook::base_address = communication->get_module_base("FortniteClient-Win64-Shipping.exe");
	if (!hook::base_address) {
		std::cout << xorstr(" Driver Error: Failed to get games base address please restart and remap driver");
		LI_FN(Sleep)(2000);
		return 0;
	}

	std::cout << xorstr(" Hooked to Fortnite! ") << std::endl;
	std::cout << xorstr(" Wait for the Notification. ") << std::endl;
	std::cout << xorstr(" 5.2.0-25909622+++Fortnite+Release-25.00 | ") << std::hex << hook::base_address << std::endl;

	std::thread thread(actor_cache);
	thread.detach();

	//init_interface();
	hijack::hijack_init();
	directx_init();
	render_loop();
	ErasePEHeaderFromMemory();

	OBSIDIUM_VM_END;
	OBSIDIUM_ENC_END;

	return 0;
}
