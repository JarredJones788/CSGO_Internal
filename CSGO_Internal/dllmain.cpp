#include "MainHeader.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include <iostream>

unsigned long __stdcall Setup(void*)
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	while (!(GetModuleHandleA("serverbrowser.dll")))Sleep(200); // This makes sure that all the modules in the game are loaded. serverbrowser.dll is last loaded.

	/*Create instances*/
	{
		Interfaces = new CInterfaces();
		Netvar = new CNetvar();
		ClassId = new ClassIdManager();
		Misc = new CMisc();
		Hooking = new CHooks();
	}
	
	
	while (!(GetAsyncKeyState(VK_END) || G.Exit)); Sleep(1);

	/*Cleanup*/
	{
		delete Hooking;
		Interfaces->Input->m_fMouseInitialized = true; // so we dont break the game
		delete Misc;
		ImGui_ImplDX9_Shutdown();
		if (ImGui::GetCurrentContext()) ImGui::DestroyContext();
		delete ClassId;
		delete Netvar;
		delete Interfaces;
	}

	/* shutdown the console and eject the dll*/
	{
		HWND console = GetConsoleWindow();
		FreeConsole();
		Sleep(100); // Give it time to free the console
		while (!PostMessage(console, WM_CLOSE, 0, 0)) { Sleep(100); }

		FreeLibraryAndExitThread(G.module, NULL);
	}

	return 0;
}



BOOL APIENTRY DllMain( HMODULE hModule,  DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		G.module = hModule , CreateThread(0, 0, &Setup, 0, 0, 0);
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

