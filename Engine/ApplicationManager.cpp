#include "ApplicationManager.h"


ApplicationManager::ApplicationManager()
{
	m_Input = 0;
	m_D3D = 0;
	m_Camera = 0;
	m_Graphic = 0;
	m_Position = 0;
	m_Timer = 0;
}


ApplicationManager::ApplicationManager(const ApplicationManager& other){}


ApplicationManager::~ApplicationManager(){}


bool ApplicationManager::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	float cameraX, cameraY, cameraZ;
	DirectX::XMMATRIX baseViewMatrix;
	float screenratio = static_cast<float>(screenWidth) / (screenHeight);
	
	// Create and Initialize the Input object.
	m_Input = new InputManager;
	if (!m_Input){ return false; }
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize InputKeyboardSetup", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the DirectX object.
	m_D3D = new(16) DXManager;
	if (!m_D3D) { return false; }
	result = m_D3D->Initialize(screenWidth, screenHeight, Constants::VSYNC_ENABLED, hwnd, Constants::FULL_SCREEN, Constants::SCREEN_DEPTH, Constants::SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the Camera object.
	m_Camera = new(16) Camera;
	if (!m_Camera)
	{
		MessageBox(hwnd, L"Could not initialize Camera", L"Error", MB_OK);
		return false;
	}
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	cameraX = 50.0f;
	cameraY = 2.0f;
	cameraZ = -7.0f;
	m_Camera->SetPosition(cameraX, cameraY, cameraZ);

	// Create and Initialize the timer object.
	m_Timer = new Timer;
	if (!m_Timer)	{	return false;	}
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the fps object.
	m_Fps = new FpsMonitor;
	if (!m_Fps)	{	return false;	}
	m_Fps->Initialize();

	// Create and Initialize the cpu object.
	m_Cpu = new CpuMonitor;
	if (!m_Cpu)	{	return false;	}
	m_Cpu->Initialize();

	// Create and Initialize the position object.
	m_Position = new PositionManager;
	if (!m_Position)	{	return false;	}
	m_Position->SetPosition(cameraX, cameraY, cameraZ);

	//create phisics
	m_physic = new Physic();
	if (!m_physic) { return false; }


	//Create and Initialize the Graphic Manager Object.
	m_Graphic = new MyApplication();
	if (!m_Graphic) { return false; }
	result = m_Graphic->Initialize(m_D3D, hwnd, m_Camera, m_physic);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Graphic Manager Object", L"Error", MB_OK);
		return false;
	}

	return true;
}


void ApplicationManager::Shutdown()
{
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}
	if (m_Graphic)
	{
		m_Graphic->Shutdown();
		delete m_Graphic;
		m_Graphic = 0;
	}
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}
	if (m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}
	if (m_physic)
	{
		delete m_physic;
		m_physic = 0;
	}
	return;
}


bool ApplicationManager::Frame()
{
	bool result;

	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)	{	return false;	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)	{	return false;	}

	// Do the frame input processing.
	result = HandleInput(m_Timer->GetTime());
	if (!result)	{	return false;	}

	// Render the graphics.
	result = RenderGraphics();
	if (!result)	{	return false;	}

	return result;
}


bool ApplicationManager::HandleInput(float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	return true;
}


bool ApplicationManager::RenderGraphics()
{
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 0.0f);

	m_Graphic->Frame(m_Timer->GetTime(), m_Fps->GetFps(), m_Cpu->GetCpuPercentage());

	m_D3D->EndScene();

	return true;
}
