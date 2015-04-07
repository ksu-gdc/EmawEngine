// EMAW_ENGINE.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "EmawEngine.h"
#include "Texture.h"
#include "FrameCounter.h"
#include "Test.h"
#include "AssetManager.h"
#include "GameNode.h"
#include "ModelNode.h"
#include "PlayerObject.h"
#include "CollisionObject.h"
#include "InputManager.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
HWND hWnd;										// window handle
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
GraphicsDeviceInterface gdi;					// the Graphics Device Inteface
WindowSize wind;								// window size object

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_EMAW_ENGINE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Perform graphics initialization
	if (!gdi.Initialize(hWnd, &wind))
	{
		return FALSE;
	}

	// Perform frame count initialization
	FrameCounter fc;
	unsigned int fps = 0;

	// Perform AssetManager initialization
	AssetManager* assetManager = AssetManager::getInstance();

	// TEST CODE!!!
	// =========================================================================
	
	// Create the root node of the Scene Graph.
	GameNode* root = new GameNode();
	root->setGraphicsDeviceInterface(&gdi);

	// Create an entity.
	Entity* e = new Entity();
	
	// Create a node for the floor.
	ModelNode* base = new ModelNode(e->getModel());
	base->setGraphicsDeviceInterface(&gdi);
	base->scale(100, 1, 100);

	root->addChild(base);
	
	GameObject* plane = new GameObject();
	*plane->_scale->x = 100;
	*plane->_scale->y = 1;
	*plane->_scale->z = 100;

	PlayerObject* player = new PlayerObject();
	Camera* camera = new Camera();
	camera->setPositionPointers(player->_position->x, player->_position->y, player->_position->z);

	gdi.SetSceneGraphRoot(root);
	gdi.SetCamera(camera);

	Transform* identity = new Transform();

	CollisionObject* playerCollision = new CollisionObject();
	CollisionObject* planeCollision = new CollisionObject();

	VERTEX* origin = new VERTEX();
	origin->X = 0;
	origin->Y = 0;
	origin->Z = 0;


	playerCollision->m_GameObject = player;
	planeCollision->m_GameObject = plane;


	planeCollision->calculateCollisionBox(origin, &e->getModel()->getVertexBuffer());
	playerCollision->center->X = *player->_position->x;
	playerCollision->center->Y = *player->_position->y;
	playerCollision->center->Z = *player->_position->z;
	playerCollision->lengthX = 2;
	playerCollision->lengthY = 6;
	playerCollision->lengthZ = 2;

	// =========================================================================
	// TEST CODE!!!

	// Perform InputManager initialization
	InputManager* inputManager = InputManager::getInstance();
	inputManager->registerWindow(hWnd);

	player->setInputManager(inputManager);
	player->setCamera(camera);

	//Perform sound initialization
	AudioManager* am = AudioManager::getInstance();
	(AudioRenderer::Instance())->setSoundSystem(am);
	//Main game loop:
	while(true)
	{
		
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
			else {
				switch (msg.message) {
					// Keyboard messages
					case WM_KEYDOWN:
						inputManager->handleKeyDownMessage(msg.wParam);
						break;
					case WM_KEYUP:
						inputManager->handleKeyUpMessage(msg.wParam);
						break;
					// Mouse button messages
					case WM_LBUTTONDOWN:
						inputManager->handleMouseDownMessage(msg.wParam, MOUSEBUTTON_LEFT);
						break;
					case WM_LBUTTONUP:
						inputManager->handleMouseUpMessage(msg.wParam, MOUSEBUTTON_LEFT);
						break;
					case WM_MBUTTONDOWN:
						inputManager->handleMouseDownMessage(msg.wParam, MOUSEBUTTON_MID);
						break;
					case WM_MBUTTONUP:
						inputManager->handleMouseUpMessage(msg.wParam, MOUSEBUTTON_MID);
						break;
					case WM_RBUTTONDOWN:
						inputManager->handleMouseDownMessage(msg.wParam, MOUSEBUTTON_RIGHT);
						break;
					case WM_RBUTTONUP:
						inputManager->handleMouseUpMessage(msg.wParam, MOUSEBUTTON_RIGHT);
						break;
					// Mouse move messages
					case WM_MOUSEMOVE:
						inputManager->handleMouseMoveMessage(msg.lParam);
				}
			}
		}
		else
		{
			playerCollision->center->X = *player->_position->x;
			playerCollision->center->Y = *player->_position->y;
			playerCollision->center->Z = *player->_position->z;

			playerCollision->hasCollision(*planeCollision, 1.0);

			player->update(0.0);

			root->update(identity->getTransformMatrix());
			//base->rotateY(0.0005);

			// TODO: Update
			gdi.NextFrame();

			// Update frame counter
			fc.Update();
			wstring test = fc.GetFps();
			SetWindowText(hWnd, (LPCWSTR)&test[0]);

			// Update the input
			inputManager->update();
		}
	}

	// Perform graphics cleanup
	gdi.Shutdown();

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EMAW_ENGINE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_EMAW_ENGINE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   // using windows size object to create correctly sized window
   // removed thick frame so window is not resizable
   RECT wr = { 0, 0, wind.getWidth(), wind.getHeight() };
   AdjustWindowRect(&wr, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, FALSE);

   hWnd = CreateWindow(
	   szWindowClass,
	   szTitle,
	   WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
	   CW_USEDEFAULT,
	   0,
	   wr.right - wr.left,
	   wr.bottom - wr.top,
	   NULL,
	   NULL,
	   hInstance,
	   NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//	WM_KEYDOWN	- process keydown events
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	// Handles keydown messages - currently used for testing resolution changes
#pragma region KEYDOWN message
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 96: // Num-0
			OutputDebugString(CString("0\n"));
			OutputDebugString(CString((to_string(wind.getWidth()) + " " + to_string(wind.getHeight()) + "\n").c_str()));
			break;
		case 49: // Num-1
			wind.setSize(hWnd, &gdi, LOW_4_3);
			OutputDebugString(CString((to_string(wind.getWidth()) + " " + to_string(wind.getHeight()) + "\n").c_str()));
			break;
		case 50: // Num-2
			wind.setSize(hWnd, &gdi, HIGH_4_3);
			OutputDebugString(CString((to_string(wind.getWidth()) + " " + to_string(wind.getHeight()) + "\n").c_str()));
			break;
		case 51: // Num-3
			wind.setSize(hWnd, &gdi, LOW_16_9);
			OutputDebugString(CString((to_string(wind.getWidth()) + " " + to_string(wind.getHeight()) + "\n").c_str()));
			break;
		case 52: // Num-4
			wind.setSize(hWnd, &gdi, HIGH_16_9);
			OutputDebugString(CString((to_string(wind.getWidth()) + " " + to_string(wind.getHeight()) + "\n").c_str()));
			break;
		case 70: // 'f' keypress
			wind.setWindowed(hWnd, &gdi, FALSE);
			OutputDebugString(CString("fullscreen mode\n"));
			break;
		case 87: // 'w' keypress
			wind.setWindowed(hWnd, &gdi, TRUE);
			OutputDebugString(CString("windowed mode\n"));
			break;
		default:
			OutputDebugString(CString((to_string(wParam) + "\n").c_str()));
			break;
		}
		break;
#pragma endregion
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
