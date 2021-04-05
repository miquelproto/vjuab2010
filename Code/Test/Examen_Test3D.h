/*----------------------------------------------------------------------------------*\
 * CExamen_Test3D class                                                               *
\*----------------------------------------------------------------------------------*/
#pragma once
#ifndef INC_EXAMEN_TEST3D_H_
#define INC_EXAMEN_TEST3D_H_

#include "Process.h"
#include "InputManager.h"

//-----------FORWARD DECLARATION-----------
class CObject3D;
class CRenderManager;
//-----------------------------------------

class CExamen_Test3D: public CProcess
{
public:
  //Construct
	CExamen_Test3D();
  //Destruct
	virtual ~CExamen_Test3D();

  //functions
	void	Init						();
	void	Update					(float elapsedTime);
	void	Render					(CRenderManager * rm);
  void	RenderDebugInfo	(CRenderManager * rm, CFontManager* fm, float fps);

private:
	CObject3D*	m_pObject3D;
	float m_fRotacion;
};

#endif