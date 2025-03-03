#include "includes.h"
#include <windows.h>
#include <shellapi.h>
#include "memory/Offsets.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	
	ImGui::SetNextWindowSize(ImVec2(600, 350));
	ImGui::Begin("					Idle Slayer - jxst_kifoxxxxe - EN Version");
	{

		if (ImGui::Button("Coins"))
		{
			tab = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button("Miscellaneous"))
		{
			tab = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button("Information"))
		{
			tab = 2;
		}
		ImGui::Separator();


		if (tab == 0)
		{

			if (ImGui::InputDouble(("Value of Your Coins"), &ValeurPieces))
			{
				*(double*)FindAddress(moduleBase + 0x01EA6E28, { 0x78, 0xB8, 0x20, 0x20 }) = ValeurPieces;
			}

		}

		if (tab == 1)
		{
			ImGui::Text("Hi / I Made This Menu In Like 25 Min There's Just One Function");
			ImGui::Text("The One Of The Coins But Hey If You Like It I Will Make A PT2 Of The Cheat");
			ImGui::Text("If you pay for This Cheat, you have been scame very hard.");
			ImGui::Text("POV: I Don't Even Know Why I'm Doing This Text Because You're Going To Delete It In The Source Code");
			ImGui::Text("Well anyway, enjoy This Source and don't make any trouble with it 😜");
			ImGui::Separator();
			ImGui::Text("Made by jxst_kifoxxxxe");
		}

		if (tab == 2)
		{
			ImGui::Text("Here is what I used to make this menu:");
			ImGui::Text("For the interface I used ImGui");
			ImGui::Text("For Hook The Game Interface I Used Kiero Hook");
			ImGui::Text("To Find The Address / Offsets Of The Game I Used Cheat Engine");

			if (ImGui::Button("ImGui"))
			{
				ShellExecute(NULL, "open", "https://github.com/ocornut/imgui", 0, 0, SW_SHOWNORMAL);
			}

			if (ImGui::Button("Kiero Hook"))
			{
				ShellExecute(NULL, "open", "https://github.com/rdbo/ImGui-DirectX-11-Kiero-Hook", 0, 0, SW_SHOWNORMAL);
			}

			if (ImGui::Button("Cheat Engine"))
			{
				ShellExecute(NULL, "open", "https://www.cheatengine.org/", 0, 0, SW_SHOWNORMAL);
			}
			ImGui::Separator();

			if (ImGui::Button("Close Menu"))
			{
				kiero::shutdown();
			}

		}

		ImGui::End();
		ImGui::Render();
	}

	// this menu have been make by jxst_kifoxxxxe
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	// this menu have been make by jxst_kifoxxxxe
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}
BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	// this menu have been make by jxst_kifoxxxxe
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}