/*----------------------------------------------------------------------------------*\
 * CCore class                                                                      *
 * Author: Marco Torres                                                             *
 * Last Modification: 19/12/2010 - CStaticMeshManager -Miquel Rojas                 *
 * Description:                                                                     *
 * Clase Engine.                                                                    *
 * Descripcion aqui                                                                 *
\*----------------------------------------------------------------------------------*/

#pragma once
#ifndef INC_CORE_H_
#define INC_CORE_H_

#include "Base.h"
#include <vector>
#include <Windows.h>
#include "Singleton.h"

//--Forward declaration--
class CRenderManager;
class CFontManager;
class CLanguageManager;
class CInputManager;
class CStaticMeshManager;
class CRenderableObjectsManager;
//class CAnimatedModelManager;
//-----------------------

class CCore: public CSingleton<CCore>{
public:
  //Consruct
  CCore(): m_pRenderManager(0), m_pFontManager(0), m_pLanguageManager(0), m_pInputManager(0), m_pStaticMeshManager(0),m_pRenderableObjectsManager(0) {}
  //Destruct
	virtual ~CCore();

  //functions
  bool	Init		(SInitParams _params, HWND hWnd);
	void	Update	(float elapsedTime);
	void	Render	();
  void  CheckActionsFromInputs();

  //get set
	void								SetRenderManager		(CRenderManager * rm)	{m_pRenderManager = rm;}
  CRenderManager *		GetRenderManager		()										{return m_pRenderManager;}
	CFontManager *			GetFontManager			()										{return m_pFontManager;}
	CLanguageManager *	GetLanguageManager	()										{return m_pLanguageManager;}
	CInputManager *			GetInputManager			()										{return m_pInputManager;}
  CStaticMeshManager* GetStaticMeshManager()                    {return m_pStaticMeshManager;}
  CRenderableObjectsManager* GetRenderableObjectsManager()      {return m_pRenderableObjectsManager;}
//  CAnimatedModelManager* GetAnimatedModelManager()              {return m_pAnimatedModelManager;}
private:
	bool							         m_bIsOk ;
  CRenderManager *	         m_pRenderManager;
	CFontManager*			         m_pFontManager;
	CLanguageManager*	         m_pLanguageManager;
	CInputManager*		         m_pInputManager;
  CStaticMeshManager*        m_pStaticMeshManager;
  CRenderableObjectsManager* m_pRenderableObjectsManager;
  //CAnimatedCoreModel*        m_pAnimatedModelManager
};

#endif //INC_CORE_H_