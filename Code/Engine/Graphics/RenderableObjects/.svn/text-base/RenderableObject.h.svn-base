//----------------------------------------------------------------------------------
// RenderableObject Class
// Author: Jordi Arnal
//
// Description:
// 
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef RENDERABLEOBJECT_H_
#define RENDERABLEOBJECT_H_

// Includes
#include "Object3D/Object3D.h"
#include "Named/Named.h"

//Class
class CRenderManager;

class CRenderableObject : public CObject3D, public CNamed
{
public:
  CRenderableObject():m_bIsOk(0){;}
  virtual ~CRenderableObject() { Done(); }
  virtual void Update(float ElapsedTime);
  virtual void Render(CRenderManager *RM) = 0;

  // Init and End protocols

	virtual	bool				Init								();
  virtual void				Done               	();
  bool								IsOk               	() const { return m_bIsOk; }

  // -----------------------
  // Read functions
  // -----------------------

  // -----------------------
  // Write functions
  // -----------------------

private:
  void        				Release   					();

  // member variables
  bool                m_bIsOk;          // Initialization boolean control

	// Types 
	//uncomment to derived classes
  //typedef CProcess Inherited;
};


#endif