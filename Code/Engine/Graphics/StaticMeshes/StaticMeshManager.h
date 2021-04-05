//----------------------------------------------------------------------------------
// CStaticMeshManager class
// Author: Miquel Rojas
//
// Description:
// clase que controla todas las mallas (cores) del juego, se introducen dentro de un
// mapa, con load se lee el StaticMeshManager.xml donde estan todas las cores
//----------------------------------------------------------------------------------
#pragma once
#ifndef INC_MESH_MANAGER_H_
#define INC_MESH_MANAGER_H_

#include "MapManager/MapManager.h"
#include "StaticMeshes/StaticMesh.h"
#include <string>

class CStaticMeshManager : public CMapManager<CStaticMesh>
{
protected:
  std::string m_FileName;
public:
  CStaticMeshManager():m_FileName ("") {}
  ~CStaticMeshManager (){}
  bool Load(const std::string &FileName);
  bool Reload();
};

#endif //INC_RENDER_MANAGER_H_