//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CCore.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include	"CCore.h"

extern	CCore			* g_pCore;
bool					g_bDeviceLost = false;

DWORD WINAPI WaitForGame(LPVOID lpParam)
{
	return 1;
}

CCore::CCore(void)
{
	// Mark as not initialised
	m_bInitialised = false;

	// Mark the game as not loaded
	SetGameLoaded(false);

	// Reset instances
	m_pGame = NULL;
	m_pGraphics = NULL;
	m_pChat = NULL;
}

CCore::~CCore()
{
	CLogFile::Printf("CCore::~CCore");
}

bool CCore::Initialise()
{
	// Are we already initialsed?
	if(m_bInitialised)
		return false;

	CLogFile::Printf("CCore::Initialize");

	// Get the applicatin base address
	m_uiBaseAddress = (unsigned int)GetModuleHandle(NULL);

	// Subtract the image size from the base address
	m_uiBaseAddress -= 0x400000;

	// Open the settings file
	CSettings::Open( SharedUtility::GetAbsolutePath("IVMP-Client.xml"), true, false );

	// Parse the command line
	CSettings::ParseCommandLine(GetCommandLine());

	/* // Set the info
	SetNick(CVAR_GET_STRING("nick"));
	SetHost(CVAR_GET_STRING("ip"));
	SetPort(CVAR_GET_INTEGER("port"));
	SetPass(CVAR_GET_STRING("pass"));*/

	// Create the game instance
	m_pGame = new CGame;

	// Create the graphics instance
	m_pGraphics = new CGraphics;

	// Create the chat instance
	m_pChat = new CChat(30, 30);

	// Unprotect memory before starting addressing
	m_pGame->UnprotectMemory();

	// Intialize the offsets instance
	COffsets::Initialize(m_uiBaseAddress);

	// Apply hook's to game
	CHooks::Intialize();

	// Patch game addresses
	CPatches::Initialize();

	// Install the XLive hook
	CXLiveHook::Install();

	// Install the RAGEScriptThread hook..
	CIVScriptingHook::InstallScriptHooks();

	CLogFile::Printf("Done!");
	return true;
}

void CCore::OnGameLoad()
{
	// Is the game already loaded?
	if(IsGameLoaded())
		return;

	// Mark the game as loaded
	SetGameLoaded(true);

	m_pChat->SetVisible(true);

	m_pChat->Output( "%s %s started!", MOD_NAME, MOD_VERSION_STRING );

	// Create Instances
	// Startup the network module
	// Connect to the network
}

void CCore::OnGamePreLoad()
{
	// Is the game loaded?
	if(IsGameLoaded())
		return;

	// Create a thread to wait for the game
	CreateThread(0, 0, WaitForGame, 0, 0, 0); // Remove thread ? 
}

void CCore::OnDeviceCreate(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters)
{
	// Initialise the graphics module

	// Setup the chat

	// Create the gui instance
}

void CCore::OnDeviceLost(IDirect3DDevice9 * pDevice)
{
	// Let the graphics module know the device is lost

	// Release the saved stateblock

	// Mark as lost device
	g_bDeviceLost = true;
}

void CCore::OnDeviceReset(IDirect3DDevice9 * pDevice)
{
	// Let the graphics module know the device is reset

	// Mark as not lost device
	g_bDeviceLost = false;
}

void CCore::OnDevicePreRender()
{
	// Is the scripting manager active?
	if(true)
	{
		// Call the script event
		
	}
}

void CCore::OnDeviceRender(IDirect3DDevice9 * pDevice)
{
	// Has the device been lost?
	if(g_bDeviceLost || !m_pGraphics)
		return;

	m_pGraphics->DrawText( 5.0f, 5.0f, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("IV:Multiplayer" MOD_VERSION_STRING).Get() );

	if(m_pChat)
		m_pChat->Render();
	
	pDevice->Present(NULL,NULL,NULL,NULL);
}

void CCore::OnGameProcess()
{
	// Is the network module instance valid?
	if(true)
	{
		// Pulse the network
	}

	// Is the timer manager instance valid?
	if(true)
	{
		// Pulse the timer manager
	}

	// Is the file transfer instance valid?
	if(true)
	{
		// Pulse the file transfer
	}


	// Is the scripting manager active?
	if(true)
	{
		// Call the script event
	}
}