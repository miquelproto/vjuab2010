/*----------------------------------------------------------------------------------*\
 * CProcess class                                                                   *
 * Author: Marco Torres                                                             *
 * Last Modification: Marco Torres                                                  *
 * Description:                                                                     *
 * Clase Engine.                                                                    *
 * Descripcion aqui                                                                 *
\*----------------------------------------------------------------------------------*/
#pragma once
#ifndef INC_PROCESS_H_
#define INC_PROCESS_H_


//---Forward Declarations---
class CCamera;
class CRenderManager;
class CFontManager;
class CObject3D;
//--------------------------

class CProcess{
public:
  //Consruct
  CProcess(){m_pCamera = 0; m_pDummyCamera3D = 0;};
  //Destruct
	virtual ~CProcess(){;};

  //functions
	virtual void	Update					(float elapsedTime) = 0;
	virtual void	Render					(CRenderManager * rm) = 0;
	virtual void	Init						() = 0;
	virtual void	RenderDebugInfo	(CRenderManager * rm, CFontManager* fm, float fps);
	CCamera *			GetCamera				() {return m_pCamera;}
  void          SetDummyCamera  (CObject3D* );
  CObject3D*    GetDummyCamera  (void) {return m_pDummyCamera3D;}

protected:
  CCamera* m_pCamera;
  CObject3D*	m_pDummyCamera3D;
};

#endif