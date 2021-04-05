//----------------------------------------------------------------------------------
// CRenderManager class
// Author: Marco Torres
//
// Description:
// blablabla...
//----------------------------------------------------------------------------------
#pragma once

#ifndef INC_STATIC_MESH_H_
#define INC_STATIC_MESH_H_

#include <vector>
#include <string>

// forward declarations
class CRenderableVertexs;
class CTexture;
class CRenderManager;
// end forward declarations

class CStaticMesh
{
protected:
  std::vector<CRenderableVertexs*> m_RVs;
  std::vector<std::vector<CTexture *>> m_Textures;
  std::string m_FileName;
  unsigned int m_NumVertexs, m_NumFaces;
public:
  CStaticMesh();
  ~CStaticMesh();
  bool Load (const std::string &FileName);
  bool ReLoad ();
  void Render (CRenderManager *RM) const;
  void Release ();
};

#endif //INC_STATIC_MESH_H_