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
#include "InputManager.h"
#include "VoxelMap.h"
#include "AudioEasyAccess.h"
#include <DirectXMath.h>
#define MAX_LOADSTRING 100

void LoadTieFighter(GameNode* root);
void LoadShip(GameNode* root);

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

	// Perform InputManager initialization
	InputManager* inputManager = InputManager::getInstance();
	inputManager->registerWindow(hWnd);

	//Perform sound initialization
	AudioManager* am = AudioManager::getInstance();
	(AudioRenderer::Instance())->setSoundSystem(am);
	//AudioEasyAccess::getInstance()->playMusic("background", "music/Tictac_-_Estrade.mp3");

	// make mouse invisible
	ShowCursor(false);

	bool paused = false;

	// TEST CODE!!!
	// =========================================================================
	VoxelMap* worldGenerator = new VoxelMap("testmap","blarghle", 5, 5);
	

	GameNode* root = new GameNode();
	root->setGraphicsDeviceInterface(&gdi);
	bool renderVoxels = false;
	if (renderVoxels) {
		VoxelChunkNode* world[5][5];
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				world[i][j] = new VoxelChunkNode(i, j);
				world[i][j]->setGraphicsDeviceInterface(&gdi);
				world[i][j]->loadChunkBuffer(worldGenerator);
				root->addChild(world[i][j]);
			}
		}
	}

	Model* cube = new Model();
	cube->load("models/obj-models/cube-transforms.obj");

	ModelNode* cubeNode = new ModelNode(cube);
	cubeNode->setGraphicsDeviceInterface(&gdi);

	root->addChild(cubeNode);

	//Controls the camera, WASD to move along the xz plane, Space and Ctrl to move up and down.
	Player* player = new Player();

	gdi.SetSceneGraphRoot(root);
	gdi.SetCamera(player->getCamera());
//	camera->setPosition(0.0f, 0.0f, -10.0f);


	Transform* identity = new Transform();

	// =========================================================================
	// TEST CODE!!!

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
			if (inputManager->keyPressed(Esc)) {
				paused = !paused;
				if (paused) {
					ShowCursor(true);
				}
				else {
					ShowCursor(false);
				}
			}
			if (paused) {
				
			} else {
				//base->resetTransformMatrix();
				player->updatePlayer(hWnd);
				root->update(identity->getTransformMatrix());

				//base2->rotateX(0.0005);
				//base->rotateY(0.0005);
			}


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
		case 90: // 'z' keypress
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

/*
void LoadTieFighter(GameNode* root){

	Model* tieModel1 = new Model();
	tieModel1->load("models/tie1.fbx");

	ModelNode* floorNode1 = new ModelNode(tieModel1);
	floorNode1->setGraphicsDeviceInterface(&gdi);

	root->addChild(floorNode1);

	Model* tieModel2 = new Model();
	tieModel2->load("models/tie2.fbx");

	ModelNode* tieNode2 = new ModelNode(tieModel2);
	tieNode2->setGraphicsDeviceInterface(&gdi);

	root->addChild(tieNode2);

	Model* tieModel3 = new Model();
	tieModel3->load("models/tie3.fbx");

	ModelNode* tieNode3 = new ModelNode(tieModel3);
	tieNode3->setGraphicsDeviceInterface(&gdi);

	root->addChild(tieNode3);

	Model* tieModel4 = new Model();
	tieModel4->load("models/tie4.fbx");

	ModelNode* tieNode4 = new ModelNode(tieModel4);
	tieNode4->setGraphicsDeviceInterface(&gdi);

	root->addChild(tieNode4);

	Model* tieModel5 = new Model();
	tieModel5->load("models/tie5.fbx");

	ModelNode* tieNode5 = new ModelNode(tieModel5);
	tieNode5->setGraphicsDeviceInterface(&gdi);

	root->addChild(tieNode5);

	Model* tieModel6 = new Model();
	tieModel6->load("models/tie6.fbx");

	ModelNode* tieNode6 = new ModelNode(tieModel6);
	tieNode6->setGraphicsDeviceInterface(&gdi);

	root->addChild(tieNode6);

	Model* tieModel7 = new Model();
	tieModel7->load("models/tie7.fbx");

	ModelNode* tieNode7 = new ModelNode(tieModel7);
	tieNode7->setGraphicsDeviceInterface(&gdi);

	root->addChild(tieNode7);

}

void LoadShip(GameNode* root){

	Model* shipExteriorModel = new Model();
	shipExteriorModel->load("models/Ship-Exterior.fbx");

	ModelNode* shipExteriorNode = new ModelNode(shipExteriorModel);
	shipExteriorNode->setGraphicsDeviceInterface(&gdi);

	root->addChild(shipExteriorNode);

	Model* shipInteriorModel = new Model();
	shipInteriorModel->load("models/Ship-Interior.fbx");

	ModelNode* shipInteriorNode = new ModelNode(shipInteriorModel);
	shipInteriorNode->setGraphicsDeviceInterface(&gdi);

	root->addChild(shipInteriorNode);

}
*/
