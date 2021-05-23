
typedef struct _MEMORY_STRUCT
{
	BYTE type;
	LONG usermode_pid;
	LONG target_pid;
	ULONG64 base_address;
	void* address;
	LONG size;
	void* output;
} MEMORY_STRUCT, * PMEMORY_STRUCT;
template<typename ... A>
uint64_t call_driver_control(void* control_function, const A ... arguments)
{
	if (!control_function)
		return 0;

	using tFunction = uint64_t(__stdcall*)(A...);
	const auto control = static_cast<tFunction>(control_function);

	return control(arguments ...);
}
void* kernel_control_function()
{
	HMODULE hModule = LoadLibrary((L"win32u.dll"));

	if (!hModule)
		return nullptr;

	void* func = reinterpret_cast<void*>(GetProcAddress(hModule, ("NtDxgkGetTrackedWorkloadStatistics")));
	return func;
}

void* m_driver_control;
DWORD64 m_pid;
DWORD64 usermode_pid;
DWORD64 m_base;
DWORD64 m_unityplayer;
DWORD64 m_gameassembly;

DWORD64 GetBaseAddress()
{
	Protect(_ReturnAddress());

	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 16;
	memory_struct.usermode_pid = m_pid;

	int result = call_driver_control(m_driver_control, &memory_struct);

	Unprotect(_ReturnAddress());

	return result == 0 ? memory_struct.base_address : 0;
}

static ULONG64 UnityPlayer(const char* moduleName)
{
	Protect(_ReturnAddress());

	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 14;
	memory_struct.usermode_pid = m_pid;

	int result = call_driver_control(m_driver_control, &memory_struct);

	Unprotect(_ReturnAddress());

	return result == 0 ? memory_struct.base_address : 0;
}
static ULONG64 GameAssembly(const char* moduleName)
{
	Protect(_ReturnAddress());

	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 15;
	memory_struct.usermode_pid = m_pid;

	int result = call_driver_control(m_driver_control, &memory_struct);

	Unprotect(_ReturnAddress());

	return result == 0 ? memory_struct.base_address : 0;
}

template <typename T>
T read(uintptr_t address)
{
	Protect(_ReturnAddress());

	T buffer{ };
	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 3;
	memory_struct.usermode_pid = usermode_pid;
	memory_struct.target_pid = m_pid;
	memory_struct.address = reinterpret_cast<void*>(address);
	memory_struct.output = &buffer;
	memory_struct.size = sizeof(T);
	int result = call_driver_control(m_driver_control, &memory_struct);

	Unprotect(_ReturnAddress());

	return buffer;
}

template<typename T>
bool write(uint64_t address, T buffer)
{
	Protect(_ReturnAddress());
	
	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 7;
	memory_struct.usermode_pid = usermode_pid;
	memory_struct.target_pid = m_pid;
	memory_struct.address = reinterpret_cast<void*>(address);
	memory_struct.size = sizeof(T);
	memory_struct.output = &buffer;

	int result = call_driver_control(m_driver_control, &memory_struct);

	if (result != 0)
		return false;

	Unprotect(_ReturnAddress());

	return true;
}

bool readwtf(uintptr_t Address, void* Buffer, SIZE_T Size)
{
	Protect(_ReturnAddress());

	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 3;
	memory_struct.usermode_pid = usermode_pid;
	memory_struct.target_pid = m_pid;
	memory_struct.address = reinterpret_cast<void*>(Address);
	memory_struct.output = Buffer;
	memory_struct.size = Size;

	int result = call_driver_control(m_driver_control, &memory_struct);

	Unprotect(_ReturnAddress());

	return true;
}

std::string read_ascii(const std::uintptr_t address, std::size_t size)
{
	std::unique_ptr<char[]> buffer(new char[size]);
	readwtf(address, buffer.get(), size);
	return std::string(buffer.get());
}

std::wstring read_unicode(const std::uintptr_t address, std::size_t size)
{
	const auto buffer = std::make_unique<wchar_t[]>(size);
	readwtf(address, buffer.get(), size * 2);
	return std::wstring(buffer.get());
}

uint64_t ReadChain(uint64_t base, const std::vector<uint64_t>& offsets) {
	uint64_t result = read<uint64_t>(base + offsets.at(0));
	for (int i = 1; i < offsets.size(); i++) {
		result = read<uint64_t>(result + offsets.at(i));
	}
	return result;
}
