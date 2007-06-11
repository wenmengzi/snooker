// SnookerCore.h: interface for the CSnookerCore class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNOOKERCORE_H__12958B13_01AD_4919_8A8C_06EF23099637__INCLUDED_)
#define AFX_SNOOKERCORE_H__12958B13_01AD_4919_8A8C_06EF23099637__INCLUDED_
#include "GLFrame.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TP_BALL 1
#define TP_HOLE 2
#define TP_STICK 3
#define MAX_NUM_OBJ 42

#define GM_LBUTTONDOWN 1
#define GM_MOUSEMOVE 2

typedef unsigned long GState;
#define GS_RUNNING 0x1

struct FRECT
{
	float left;
	float top;
	float right;
	float bottom;
};
struct GAMEOBJECT
{
	DWORD type;
	BOOL alive;
	FLOAT radius;
	FLOAT color_r,color_g,color_b,color_a;
	FLOAT x,y;
	FLOAT vx,vy;
	FLOAT ax,ay;
	FLOAT rvx,rvy,rvz;
	int score;
	static FRECT tableface;
	static FRECT besidehole[6];
	static FLOAT u1;
	static FLOAT u2;
	static FLOAT k1;
	static FLOAT k2;
	static FLOAT alpha1;
	static FLOAT alpha2;
	static FLOAT auz;
	static FLOAT vmax;
	static int PPF;
	static void LoadPhyArg();
};

class CSnookerCore : public CGLFrame  
{
public:
	void RenewStick();
	void ShootWhiteBall();
	
	void ResetObject();
	CSnookerCore();
	virtual ~CSnookerCore();

	LRESULT PostGameMessage(UINT GMsg, WPARAM wParam, LPARAM lParam);
	void OnCreate();
	void OnPaint();

	GAMEOBJECT gobject[MAX_NUM_OBJ];

	//Game State
	GState m_state;
	// TEST
	int frames;
	DWORD startTime;
	DWORD lastTime;

private:
	inline void DrawBall(const GAMEOBJECT *pball);
	inline void DrawTable();
	inline void DrawStick(const GAMEOBJECT *pstick);
	inline void SetLight();

	float PhysicalProcess();
	BYTE *tableimage;
};

#endif // !defined(AFX_SNOOKERCORE_H__12958B13_01AD_4919_8A8C_06EF23099637__INCLUDED_)
