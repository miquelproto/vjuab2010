//----------------------------------------------------------------------------------
// CRenderableObjectsManager class
// Author: Andrea Cristobo
// modificacion: Miquel Rojas 07/01/2010 
// Description:
// Clase que controla todas los elementos renderizables del videojuego
//----------------------------------------------------------------------------------

#pragma once
#ifndef INC_RENDER_OBJECTS_MANAGER_H_
#define INC_RENDER_OBJECTS_MANAGER_H_

//------Forward declarations---------
class CRenderableObject;
class CRenderableVertexs;
//----------------------------------

#include "Base.h"
#include "MapManager/MapManager.h"
#include <vector>
#include "Math/Vector3.h"
#include <string>

class CRenderableObjectsManager : CMapManager<CRenderableObject *>
{
	public:
		CRenderableObjectsManager(): m_RenderableObjects(0){};
		~CRenderableObjectsManager();

		void																Update								(float ElapsedTime);
		void																Render								(CRenderManager *RM);
		CRenderableObject *									AddMeshInstance				(const std::string &CoreMeshName, const std::string &InstanceName, const Vect3f &Position, const float &Yaw, const float &Pitch, const float &Roll);
		void																AddResource						(const std::string &Name, CRenderableObject *RenderableObject);
		void																CleanUp								();
		bool																Load									(const std::string &FileName);
		CRenderableObject *									GetInstance						(const std::string &Name) const;
		bool                                Reload                ();

	protected:
		std::vector<CRenderableObject *>		m_RenderableObjects;
    std::string m_FileName;
};

#endif
