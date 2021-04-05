/*----------------------------------------------------------------------------------*\
 * CExamen_Test3D class                                                               *
\*----------------------------------------------------------------------------------*/
#pragma once
#ifndef INC_EXAMEN_SNAKE2D_H_
#define INC_EXAMEN_SNAKE2D_H_

#include "Process.h"
#include "InputManager.h"

//-----------FORWARD DECLARATION-----------
class CObject3D;
class CRenderManager;
//-----------------------------------------

class CExamen_Snake: public CProcess
{
public:
  //Construct
	CExamen_Snake(){m_fPosX=0.0f; m_fPosY=0.0f; m_iDir = 0; m_bLose = false; m_Time = 0; m_Speed = 1;};
  //Destruct
	virtual ~CExamen_Snake();

  //functions
	void	Init						();
	void	Update					(float elapsedTime);
	void	Render					(CRenderManager * rm);
  void	RenderDebugInfo	(CRenderManager * rm, CFontManager* fm, float fps);

private:
	CObject3D*	m_pObject3D;
	float m_fPosX, m_fPosY, m_Time, m_Speed;
	int m_iDir;
	bool m_bLose;
};

#endif