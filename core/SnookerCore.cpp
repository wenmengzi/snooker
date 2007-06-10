// SnookerCore.cpp: implementation of the CSnookerCore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "core.h"
#include "SnookerCore.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// Physical Argments
float GAMEOBJECT::u1=0.000001f;
float GAMEOBJECT::u2=1.0f;
float GAMEOBJECT::k1=0.05f;
float GAMEOBJECT::k2=0.04f;
FRECT GAMEOBJECT::tableface={-1.085f,0.53f,1.085f,-0.53f};
float GAMEOBJECT::alpha1=0.00001f;
float GAMEOBJECT::alpha2=0.000009f;
float GAMEOBJECT::auz=0.0005f;
float GAMEOBJECT::vmax=0.006f;
int GAMEOBJECT::PPF=8;

CSnookerCore::CSnookerCore()
{
	tableimage=new BYTE[1572864];
	FILE *ftable=fopen("table3.bmp","rb");
	if(ftable)
	{
		fseek(ftable,54,SEEK_SET);
		fread(tableimage,sizeof(BYTE),1572864,ftable);
	}
	fclose(ftable);
	ResetObject();
	startTime=lastTime=GetTickCount();
	frames=0;
}

CSnookerCore::~CSnookerCore()
{
	delete[] tableimage;
}

LRESULT CSnookerCore::PostGameMessage(UINT GMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

void CSnookerCore::OnCreate()
{
	glClearColor(0.0f,0.2f,0.0f,1.0f);
	int listi=glGenLists(2);
	glListBase(listi);
	glNewList(listi,GL_COMPILE);
		//glScalef(BALL_RAD,BALL_RAD,BALL_RAD);
		const float pi=3.14159265359f;
		//glColor4f(0.0f,0.0f,1.0f,1.0f);
		float r=0.0f,nr=0.0f,q=0.0f,x,y,z;
		for(int i=1;i<=6;++i)
		{
			r=nr;
			nr=pi*i/6;
			glBegin(GL_QUAD_STRIP);
			for(int j=0;j<=10;++j)
			{
				q=pi*j/10;
				
				glNormal3f(x=sinf(r)*cosf(q),
					y=cosf(r),
					z=sinf(r)*sinf(q));
				glVertex3f(x,y,z);
				
				glNormal3f(x=sinf(nr)*cosf(q),
					y=cosf(nr),
					z=sinf(nr)*sinf(q));
				glVertex3f(x,y,z);
			}
			glEnd();
		}
	glEndList();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexImage2D(GL_TEXTURE_2D,0,3,1024,512,
			0,GL_BGR_EXT,GL_UNSIGNED_BYTE,tableimage);

		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,
			GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,
			GL_NEAREST);
	
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
		
	
	glNewList(listi+1,GL_COMPILE);
		//glDrawPixels(774,415,GL_BGR_EXT,GL_UNSIGNED_BYTE,tableimage);
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.810546875f);		glVertex3f(-1.194567f,0.639744f,0.0f);
		glTexCoord2f(0.0f,0.0f);			glVertex3f(-1.194567f,-0.639744f,0.0f);
		glTexCoord2f(0.755859375f,0.0f);		glVertex3f(1.194567f,-0.639744f,0.0f);
		glTexCoord2f(0.755859375f,0.810546875f);	glVertex3f(1.194567f,0.639744f,0.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glEndList();
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//	DrawTable();
}

void CSnookerCore::OnPaint()
{
	int i;
	DWORD now=GetTickCount();
	int PPF=GAMEOBJECT::PPF*(now-lastTime)/14;
	for(i=0;i<PPF;++i)
		PhysicalProcess();
	lastTime=now;
	++frames;
	glTranslatef(0.0f,0.0f,-6.0f);
	glEnable(GL_LINE_SMOOTH);
	SetLight();
	DrawTable();
	glPushMatrix();
		for(i=0;i<22;++i)
		{
			glPushMatrix();
			DrawBall(gobject+i);
			glPopMatrix();
		}
	glPopMatrix();
}

void CSnookerCore::ResetObject()
{
	int i,t;
	float tmp;
	FILE *finit=fopen("init.txt","r");
	if(!finit)
	{
		return;
	}
	for(i=0;i<22;++i)
	{
		gobject[i].type=TP_BALL;
		gobject[i].radius=0.029f;
		fscanf(finit,"%f",&tmp);
		gobject[i].color_r=tmp;
		fscanf(finit,"%f",&tmp);
		gobject[i].color_g=tmp;
		fscanf(finit,"%f",&tmp);
		gobject[i].color_b=tmp;
		fscanf(finit,"%f",&tmp);
		gobject[i].color_a=tmp;
		fscanf(finit,"%f",&tmp);
		gobject[i].x=tmp;
		fscanf(finit,"%f",&tmp);
		gobject[i].y=tmp;
		fscanf(finit,"%d",&t);
		gobject[i].score=t;
		gobject[i].alive=TRUE;
	}
	fclose(finit);
	for(;i<MAX_NUM_OBJ;++i)
	{
		gobject[i].type=TP_HOLE;
		gobject[i].radius=0;
		gobject[i].x=1.2f;
		gobject[i].y=0.7f;
	}
	for(i=0;i<MAX_NUM_OBJ;++i)
	{
//		gobject[i].alive=TRUE;
//		gobject[i].x=0;//1.085f;
//		gobject[i].y=0;//0.530f;
		gobject[i].vx=0;
		gobject[i].vy=0;
		gobject[i].ax=0;
		gobject[i].ay=0;
		gobject[i].rvx=0;
		gobject[i].rvy=0;
		gobject[i].rvz=0;
	}
}

void CSnookerCore::SetLight()
{
	GLfloat		lAmb[4];
	GLfloat		lDif[4];
	GLfloat		lSpe[4];
	GLfloat		lPos[4];

	GLfloat		mAmb[4];
	GLfloat		mDif[4];
	GLfloat		mSpe[4];
	GLfloat		mEmi[4];
//	GLfloat		mEmi[4]={0.0f,1.0f,0.0f,1.0f};
	GLfloat		mShininess;

	lAmb[0]=0.0f;	lAmb[1]=0.0f;
	lAmb[2]=0.0f;	lAmb[3]=1.0f;

	lDif[0]=1.0f;	lDif[1]=1.0f;
	lDif[2]=1.0f;	lDif[3]=1.0f;

	lSpe[0]=1.0f;	lSpe[1]=1.0f;
	lSpe[2]=1.0f;	lSpe[3]=1.0f;

	lPos[0]=-4.0f;	lPos[1]=0.0f;
	lPos[2]=3.0f;	lPos[3]=1.0f;

	mAmb[0]=0.2f;	mAmb[1]=0.2f;
	mAmb[2]=0.2f;	mAmb[3]=1.0f;
	 
	mDif[0]=0.8f;	mDif[1]=0.8f;
	mDif[2]=0.8f;	mDif[3]=1.0f;

	mSpe[0]=1.0f;	mSpe[1]=1.0f;
	mSpe[2]=1.0f;	mSpe[3]=1.0f;
	
	mEmi[0]=0.0f;	mEmi[1]=0.0f;
	mEmi[2]=0.0f;	mEmi[3]=1.0f;

	mShininess=20.80f;	

	glLightfv(GL_LIGHT1,GL_AMBIENT,lAmb);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,lDif);
	glLightfv(GL_LIGHT1,GL_SPECULAR,lSpe);
	glLightfv(GL_LIGHT1,GL_POSITION,lPos);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mAmb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mDif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mSpe);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mEmi);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,mShininess);
}

inline void CSnookerCore::DrawBall(const GAMEOBJECT *pgo)
{
	glTranslatef(pgo->x,pgo->y,0.0f);
	glScalef(pgo->radius,pgo->radius,pgo->radius);
	glColor4f(pgo->color_r,pgo->color_g,pgo->color_b,pgo->color_a);
	glCallList(1);
}

inline void CSnookerCore::DrawTable()
{
	glCallList(2);
}

float CSnookerCore::PhysicalProcess()
{
	int i,j;
	float sigmav=0.0f;
	for(i=0;i<22;++i)
	{
		// 平动摩擦阻力
		float v=sqrtf(gobject[i].vx*gobject[i].vx+gobject[i].vy*gobject[i].vy);
		if(v<GAMEOBJECT::alpha1)
		{
			gobject[i].vx=0;
			gobject[i].vy=0;
		}
		else
		{
			float dvx=gobject[i].vx*(1.0f-GAMEOBJECT::u1/v);
			float dvy=gobject[i].vy*(1.0f-GAMEOBJECT::u1/v);
			if(gobject[i].vx*dvx>0.0f)
				gobject[i].vx=dvx;
			else
				gobject[i].vx=0;
			if(gobject[i].vy*dvy>0.0f)
				gobject[i].vy=dvy;
			else
				gobject[i].vy=0;
			sigmav+=v;
		}
		gobject[i].ax=0.0f;
		gobject[i].ay=0.0f;
		// 滚动摩擦阻力
		float vrx=gobject[i].vx-gobject[i].rvy;
		float vry=gobject[i].vy+gobject[i].rvx;
		float vr=sqrtf(vrx*vrx+vry*vry);
		if(vr<GAMEOBJECT::alpha2)
		{
			// 加塞消失
			gobject[i].rvy=gobject[i].vx;
			gobject[i].rvx=gobject[i].vy;
		}
		else
		{
			float au2x=vrx*GAMEOBJECT::u2*vr;
			float au2y=vry*GAMEOBJECT::u2*vr;
			gobject[i].ax-=au2x;
			gobject[i].ay-=au2y;
			// 力矩作用
			gobject[i].rvx-=au2y;
			gobject[i].rvy+=au2x;
			if(gobject[i].rvz>=GAMEOBJECT::alpha1)
				gobject[i].rvz-=GAMEOBJECT::auz;
			sigmav+=vr;
		}
	}
	// 碰撞过程
	for(i=0;i<22;++i)
	{
		//球与球的碰撞
		for(j=0;j<34;++j)
		{
			if(j==i)
				continue;
			float dx=gobject[j].x-gobject[i].x;
			float dy=gobject[j].y-gobject[i].y;
			float ds=sqrtf(dx*dx+dy*dy);
			float dc=gobject[i].radius+gobject[j].radius-ds;
			if(dc>0.0f)
			{
				float ak1x=dx*GAMEOBJECT::k1*dc/ds;
				float ak1y=dy*GAMEOBJECT::k1*dc/ds;
				gobject[i].ax-=ak1x;
				gobject[i].ay-=ak1y;
				//碰撞对滚动的影响
				//gobject[i].rvx+=ak1y/2;
				//gobject[i].rvy+=ak1x/2;
			}
		}
		//球与桌边的碰撞
		if(gobject[i].x<GAMEOBJECT::tableface.left)
		{
			gobject[i].x=GAMEOBJECT::tableface.left;
			gobject[i].rvy-=1.5f*gobject[i].vx;
			gobject[i].vx=-0.8f*gobject[i].vx;
			//碰撞对滚动的影响
			gobject[i].vy+=gobject[i].rvz;
		}
		else if(gobject[i].x>GAMEOBJECT::tableface.right)
		{
			gobject[i].x=GAMEOBJECT::tableface.right;
			gobject[i].rvy-=1.5f*gobject[i].vx;
			gobject[i].vx=-0.8f*gobject[i].vx;
			//碰撞对滚动的影响
			gobject[i].vy-=gobject[i].rvz;
		}
		if(gobject[i].y>GAMEOBJECT::tableface.top)
		{
			gobject[i].y=GAMEOBJECT::tableface.top;
			gobject[i].rvx+=1.5f*gobject[i].vy;
			gobject[i].vy=-0.8f*gobject[i].vy;
			//碰撞对滚动的影响
			gobject[i].vx+=gobject[i].rvz;
		}
		else if(gobject[i].y<GAMEOBJECT::tableface.bottom)
		{
			gobject[i].y=GAMEOBJECT::tableface.bottom;
			gobject[i].rvx+=1.5f*gobject[i].vy;
			gobject[i].vy=-0.8f*gobject[i].vy;
			//碰撞对滚动的影响
			gobject[i].vx-=gobject[i].rvz;
		}
	}
	for(i=0;i<22;++i)
	{
		// 力对速度的改变
		gobject[i].vx+=gobject[i].ax;
		gobject[i].vy+=gobject[i].ay;
		// 速度对位置的改变
		gobject[i].x+=gobject[i].vx;
		gobject[i].y+=gobject[i].vy;
	}
	return sigmav;
}