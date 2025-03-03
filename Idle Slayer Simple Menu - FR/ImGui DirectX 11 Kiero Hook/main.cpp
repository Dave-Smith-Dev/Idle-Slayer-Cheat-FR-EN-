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
	ImGui::Begin("					Idle Slayer - jxst_kifoxxxxe - Version FR");
	{
	
		if (ImGui::Button("Pieces"))
		{
			tab = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button("Divers"))
		{
			tab = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button("Info"))
		{
			tab = 2;
		}
		ImGui::Separator();


		if (tab == 0)
		{

			if (ImGui::InputDouble(("Valeur De Vos Pieces"), &ValeurPieces))
			{
				*(double*)FindAddress(moduleBase + 0x01EA6E28, { 0x78, 0xB8, 0x20, 0x20 }) = ValeurPieces;
			}

		}

		if (tab == 1)
		{
			ImGui::Text("Salut / J'ai Fait Se Menu En Genre 25 Min Y'a Jute Une Fonction");
			ImGui::Text("Celle Des Pieces Mais Bont Si Vous L'aimer Je Vais Faire Une PT2 Du Cheat");
			ImGui::Text("Si Tu A Payer Pour Se Cheat Tu Tai Fais Scame Tres Fort");
			ImGui::Text("POV: Je Sais Meme Pas Pourquoi Je Fait Ses Text Car Tu Va Le Suprimer Dans La Source Code");
			ImGui::Text("Bon Bref Profite Bien Et Fait Pas De Coneri Avec 😜");
			ImGui::Separator();
			ImGui::Text("Fait Par jxst_kifoxxxxe");
		}
		if (tab == 2)
		{
			ImGui::Text("Voici Se Que J'ai Utiliser Pour Faire Se Menu:");
			ImGui::Text("Pour L'interface J'ai Utiliser ImGui");
			ImGui::Text("Pour Hook L'interface Du Jeux J'ai Utiliser Kiero Hook");
			ImGui::Text("Pour Trouver Les Address / Offsets Du Jeux J'ai Utiliser Cheat Engine");

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

			if (ImGui::Button("Fermer Le Menu"))
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