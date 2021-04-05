/*----------------------------------------------------------------------------------*\
 * CGameProcess class                                                               *
 * Author: Marco Torres                                                             *
 * Last Modification: Marco Torres                                                  *
 * Description:                                                                     *
 * Clase GameProcess.                                                              *
 * No se muy bien cual es la funcion asi que si alguien lo sabe lo puede arreglar   *
\*----------------------------------------------------------------------------------*/
#pragma once
#ifndef INC_TEST_PROCESS_H_
#define INC_TEST_PROCESS_H_

#include "Process.h"
#include "InputManager.h"
#include "TexturedVertex.h"
#include "StaticMeshes/StaticMesh.h"


//-----------FORWARD DECLARATION-----------
class CObject3D;
class CRenderManager;
class CActionToInput;
//-----------------------------------------

class CGameProcess_t: public CProcess
{
public:
  //Construct
	CGameProcess_t();
  //Destruct
	virtual ~CGameProcess_t();

  //functions
	void	Init						      ();
	void	Update					      (float elapsedTime);
	void	Render					      (CRenderManager * rm);
  void	RenderDebugInfo	      (CRenderManager * rm, CFontManager* fm, float fps);
  void  CheckActionsFromInputs(float elapsedTime);
private:
	float				m_fPosX, m_fPosY, m_TimerCounter, m_iDirection, m_fFPS;
	float 			m_fRotacion;
	float				m_MaxVision, m_MinVision;
	bool				m_bDrawCube;
	CObject3D*	m_pObject3D;
  CActionToInput* m_pAction;
  CStaticMesh * m_box;
};

#endif

