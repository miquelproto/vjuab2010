//----------------------------------------------------------------------------------
// CInstanceMesh Class
// Author: Miquel Rojas
//
// Description:
// Como instancia se busca su core y se dibuja
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef MESHINSTANCE_H_
#define MESHINSTANCE_H_

// Includes
#include "Base.h"
#include "RenderableObject.h"
#include "StaticMeshes/StaticMesh.h"
#include <string>
//Class
class CRenderManager;

class CInstanceMesh : public CRenderableObject
{
private:
  bool m_bIsOk;
  CStaticMesh *m_StaticMesh;
public:
  bool Init();
  void Done();
  void Release();
  CInstanceMesh(const std::string &Name, const std::string &CoreName);
  ~CInstanceMesh();
  void Render(CRenderManager *RM);
//  void Update(float ElapsedTime);
};

#endif