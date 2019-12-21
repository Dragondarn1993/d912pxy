/*
MIT License

Copyright(c) 2019 megai2

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#pragma once
#include "stdafx.h"

#define PXY_INNER_EXTRA_FPS_GRAPH_PTS 256

class d912pxy_extras : public d912pxy_noncom
{
public:
	d912pxy_extras();
	~d912pxy_extras();	
	void Init();
	void UnInit();

	void OnPresent();
	void OnReset();

	void WaitForTargetFrameTime();

	bool WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	void ImGUI_Render_Start();
	void ImGUI_Render_End();
	void OnHotkeyTriggered();
	void DrawOverlay();

	//config state

	UINT32 bShowFps;
	UINT32 bShowDrawCount;
	UINT32 bShowFpsGraph;
	UINT32 bShowTimings;
	UINT32 bShowPSOCompileQue;
	UINT32 bShowGCQue;

	//gpu exec + sync time
	Stopwatch syncNexecTime;
	
	//frame limiter & frame time

	INT64 activeTargetFrameTime;
	INT64 inactiveTargetFrameTime;

	INT64 targetFrameTimeDelay;
	Stopwatch frameTime;
	INT64 frTimeMs;
	bool gameActive;

	HANDLE waitEvent;

	//fps graph

	struct {
		d912pxy_ringbuffer<float>* Data;
		UINT w, h;
		UINT min, max;
	} fpsGraph;

	//overlay toggle controls
	enum overlayShowModeValues {
		eoverlay_hide = 0,
		eoverlay_show = 1,
		eoverlay_edit = 2,
		eoverlay_modes_count = 3
	};

	UINT overlayShowMode;
	bool hkDetected;
	UINT hkVKeyCode;
};