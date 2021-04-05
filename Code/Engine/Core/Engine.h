/*----------------------------------------------------------------------------------*\
 * CEngine class                                                                    *
 * Author: Marco Torres                                                             *
 * Last Modification: Marco Torres                                                  *
 * Description:                                                                     *
 * Clase Engine.                                                                    *
 * Motor de videojuego                                                              *
\*----------------------------------------------------------------------------------*/

#pragma once
#ifndef INC_ENGINE_H_
#define INC_ENGINE_H_


#include "Timer/Timer.h"
#include "Math/MathTypes.h"
#include "Base.h"
#include <string>
#include <Windows.h>

using namespace std;

//--- Forward Declaration---
class CProcess;
#include "Core.h"//class CCore;
class CRenderManager;
//--------------------------

//-- Parametros de configuracion por defecto --
#define P_FULLSCREEN    false  
#define P_WIDTHSCREEN   800
#define P_HEIGHTSCREEN  600
//---------------------------------------------

class CEngine{
public:
  //Construct
	CEngine(): m_pProcess(0), m_pCore(0), m_Timer(30){}
  //Destruct
	virtual ~CEngine();
  //functions
  void				Init				(HWND hWnd);
  void        LoadConfig  (const std::string & pathXML);
	void				Update			();
	void				Render			();
  void				SetProcess	(CProcess * process){m_pProcess = process;}
  CProcess *	GetProcess	(){return m_pProcess;}
	void				RenderScene		(CRenderManager* rm);
	void				Release			();
	CTimer			GetTimer		(){return m_Timer;}
  SInitParams GetInitParams(){return m_ConfigParams;}

private:
  CProcess *	m_pProcess;
  CCore *			m_pCore;
	CTimer			m_Timer;
  SInitParams m_ConfigParams;
};

#endif /* INC_ENGINE_H_ */