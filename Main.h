#define WIN32_LEAN_AND_MEAN

#pragma warning(disable : 4311)
#pragma warning(disable : 4302)
#pragma warning(disable : 4267)

#include <windows.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <array>
#include <sstream>
#include <thread>
#include <chrono>
#include <fcntl.h>
#include <io.h>
#include <cstdint>
#include <cstdlib>
#include <dwmapi.h>
#include <comdef.h> 
#include <winternl.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <Psapi.h>
#include <intrin.h>
#include <math.h>
#include <dwmapi.h>
#include <comdef.h> 
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

#include "glm/glm.hpp"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx9.h"
#include "Imgui/imgui_impl_win32.h"

#include "Protect.h"
#include "font.h"
#include "driver.h"
#include "process.h"
#include "vars.h"

#include "Text.h"
#include "function.h"

ImFont* SkeetFont;
IDirect3D9Ex* p_Object = NULL;
IDirect3DDevice9Ex* p_Device = NULL;
D3DPRESENT_PARAMETERS p_Params = { NULL };

const MARGINS Margin = { -1 };

#define M_Name L" "
HWND MyWnd = NULL;
HWND GameWnd = NULL;
RECT GameRect = { NULL };
MSG Message = { NULL };

bool showimgui = true;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define TopWindowGame 11
#define TopWindowMvoe 22

HRESULT DirectXInit(HWND hWnd);
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
void SetupWindow();
WPARAM MainLoop();
void CleanuoD3D(); void ChangeClickability(bool canclick, HWND ownd);

int isTopwin();
void Render(int Topwin, bool showimgui);
void SetWindowToTarget();