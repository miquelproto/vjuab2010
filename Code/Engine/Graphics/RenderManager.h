//----------------------------------------------------------------------------------
// CRenderManager class
// Author: Enric Vergara
//
// Description:
// blablabla...
//----------------------------------------------------------------------------------
#pragma once
#ifndef INC_RENDER_MANAGER_H_
#define INC_RENDER_MANAGER_H_

//---Forward declarations---
class CCamera;
//--------------------------

#include <d3dx9.h> 
#include <string>
#include "Base.h"
#include "Math\Color.h"

class CRenderManager
{
 
public:
	CRenderManager(void):	m_bIsOk(false), m_pD3D(0), m_pD3DDevice(0),
												m_uWidth(0), m_uHeight(0) {};

  virtual ~CRenderManager(void) {Done();};

  bool                  Init(SInitParams _params, HWND hWnd);

  void                  Done            ()        {if(IsOk()) Relase(); m_bIsOk=false;};
  bool                  IsOk            () const  {return m_bIsOk;};

  void                  BeginRendering  ();
  void                  EndRendering    ();
  void                  SetupMatrices   (CCamera * camera);

	LPDIRECT3DDEVICE9			GetDevice				() {return m_pD3DDevice;}
	
	//----DebugRender Functions-------------------------------------------
	void									DrawLine				(const Vect3f &PosA, const Vect3f &PosB, CColor Color);
	void									DrawAxis				(float Size);
	void									DrawCube				(float Size, CColor color);
	void									DrawCamera			(CCamera* camera);
	void									DrawSphere			(float Radius, const CColor&  Color, int Aristas);
	void									DrawGrid				(float Size, CColor Color=colWHITE, int GridX=10, int32 GridZ=10 );
	//--------------------------------------------------------------------
	void									SetTransform		(D3DXMATRIX& matrix);
	void									SetTransform    (Mat44f& m);

	void									GetWandH				(uint32& w, uint32& h)  { w = m_uWidth; h = m_uHeight;}

private:
	void                  Relase					();
	void									GetWindowRect		(HWND hWnd);

private:
  bool                  m_bIsOk;
	LPDIRECT3D9						m_pD3D; // direct3d interface
	LPDIRECT3DDEVICE9	  	m_pD3DDevice;	   					 // direct3d device

	uint32								m_uWidth;
	uint32								m_uHeight;
};

#endif //INC_RENDER_MANAGER_H_