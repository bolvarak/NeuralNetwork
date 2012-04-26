// Application Headers
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "GeneticAlgorithm.h"
#include "GeneticAlgorithmMap.h"
#include "Definitions.h"
// Namespace definition
using namespace std;
// Global Definitions
char*             gsApplicationName = "Genetic Algorithm";
char*             gsWindowClassName = "GeneticAlgorithmClass";
GeneticAlgorithm* cGeneticAlgorithm;
// Window Process Definition
LRESULT CALLBACK WindowProc(HWND hWindow, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	// Device context for our window
	HDC         hdcWindow;
	PAINTSTRUCT psWindow;
	// Client window are dimension placeholders
	static int cxClient, cyClient;
	// Back buffer
	static HDC     hdcBackBuffer;
	static HBITMAP hBitmap;
	static HBITMAP hOldBitmap;
	// Determine the message that was sent
	switch (iMessage) {
		case WM_CREATE : {
			// Seed the random number generator
			srand((unsigned) time(NULL));
			// Create the Genetic Algorithm Class
			cGeneticAlgorithm = new GeneticAlgorithm(CROSSOVER_RATE, MUTATION_RATE, POPULATION_SIZE, CHROMOSOME_LENGTH, GENE_LENGTH);
			// Grab the size of the client window
			RECT cRect;
			GetClientRect(hWindow, &cRect);
			// Set the dimensions
			cxClient      = cRect.right;
			cyClient      = cRect.bottom;
			// Generate the backbuffer
			hdcBackBuffer = CreateCompatibleDC(NULL);
			HDC hdcWindow = GetDC(hWindow);
			// Generate the bitmap
			hBitmap       = CreateCompatibleBitmap(hdcBackBuffer, cxClient, cyClient);
			// Release the device context
			ReleaseDC(hWindow, hdcWindow);
			// Fill the old bitmap
			hOldBitmap    = (HBITMAP) SelectObject(hdcBackBuffer, hBitmap);
		}
		// Done
		break;
		// Keypress
		case WM_KEYUP : {
			// Determine the key that was pressed
			switch (wParam) {
				// Enter Key
				case VK_RETURN : {
					// Execute the Genetic Algorithm
					cGeneticAlgorithm->Execute(hWindow);
				}
				// Done
				break;
				// ESC Key
				case VK_ESCAPE : {
					// Kill the application
					PostQuitMessage(0);
				}
				// Done
				break;
				// Spacebar
				case VK_SPACE : {
					// Stop the Genetic Algorithm
					cGeneticAlgorithm->Stop();
				}
				// Done
				break;
			}
		}
		// Done
		break;
		// Window Resize
		case WM_SIZE : {
			// Grab the new dimensions
			cxClient      = LOWORD(lParam);
			cyClient      = HIWORD(lParam);
			// Resize the back buffer
			SelectObject(hdcBackBuffer, hOldBitmap);
			// Grab a new device context
			HDC hdcWindow = GetDC(hWindow);
			// Set the new bitmap
			hBitmap       = CreateCompatibleBitmap(hdcWindow, cxClient, cyClient);
			// Release the device context
			ReleaseDC(hWindow, hdcWindow);
			// Reset the old bitmap
			hOldBitmap    = (HBITMAP) SelectObject(hdcBackBuffer, hBitmap);
		}
		// Done
		break;
		// Paint Window
		case WM_PAINT : {
			// Start painting
			hdcWindow = BeginPaint(hWindow, &psWindow);
			// Fill the backbuffer with white
			BitBlt(hdcBackBuffer, 0, 0, cxClient, cyClient, NULL, NULL, NULL, WHITENESS);
			// Render the map and best route
			cGeneticAlgorithm->Render(cxClient, cyClient, hdcBackBuffer);
			// Bring the backbuffer to the front
			BitBlt(hdcWindow, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY);
			// Release the device context
			ReleaseDC(hWindow, hdcWindow);
			// Finish painting
			EndPaint(hWindow, &psWindow);
		}
		// Done
		break;
		// Window Close & Destruction
		case WM_DESTROY : {
			// Grab the old bitmap from the back buffer
			SelectObject(hdcBackBuffer, hOldBitmap);
			// Clean up the back buffer objects
			DeleteDC(hdcBackBuffer);
			// Delete the bitmap
			DeleteObject(hBitmap);
			// Delete the Genetic Algorithm object
			delete cGeneticAlgorithm;
			// Kill the application
			PostQuitMessage(0);
		}
		// Done
		break;
		// Default
		default : break;
	}
	// Return the default message handler
	return DefWindowProc(hWindow, iMessage, wParam, lParam);
};
// Main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Create our window class
	WNDCLASSEX cWindowClass;
	// Create our window
	HWND       hWindow;
	// Create our message object
	MSG        cMessage;
	// Setup the window class structure
	cWindowClass.cbSize        = sizeof(WNDCLASSEX);
	cWindowClass.style         = CS_HREDRAW | CS_VREDRAW;
	cWindowClass.lpfnWndProc   = WindowProc;
	cWindowClass.cbClsExtra    = 0;
	cWindowClass.cbWndExtra    = 0;
	cWindowClass.hInstance     = hInstance;
	cWindowClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	cWindowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	cWindowClass.hbrBackground = NULL;
	cWindowClass.lpszMenuName  = NULL;
	cWindowClass.lpszClassName = gsWindowClassName;
	cWindowClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
	// Register the window class
	if (!RegisterClassEx(&cWindowClass)) {
		// Return failure
		return 0;
	}
	// Create the window
	hWindow = CreateWindowEx(NULL, gsWindowClassName, gsApplicationName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
	// Check for the window
	if (!hWindow) {
		// Return failure
		return 0;
	}
	// Display the window
	ShowWindow(hWindow, nCmdShow);
	// Update the window
	UpdateWindow(hWindow);
	// Enter the message loop
	bool bDone = false;
	// Loop
	while (!bDone) {
		// Loop through the messages
		while (PeekMessage(&cMessage, NULL, 0, 0, PM_REMOVE)) {
			// Check for a quit command
			if (cMessage.message == WM_QUIT) {
				// Stop the loop
				bDone = true;
			} else {
				// Translate the message
				TranslateMessage(&cMessage);
				// Dispatch the message
				DispatchMessage(&cMessage);
			}
		}
		// Check to see if the Genetic Algorithm has begun execution
		if (cGeneticAlgorithm->Started()) {
			// Update
			cGeneticAlgorithm->Epoch();
			// Re-Render
			InvalidateRect(hWindow, NULL, TRUE);
			// Update the window
			UpdateWindow(hWindow);
		}
	}
	// Unregister the window class
	UnregisterClass(gsWindowClassName, cWindowClass.hInstance);
	// Return
	return 0;
}
