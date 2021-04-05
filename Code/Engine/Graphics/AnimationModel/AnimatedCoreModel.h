//----------------------------------------------------------------------------------
// CRenderableObjectsManager class
// Author: Andrea Cristobo
//
// Description:
// Mánager de Modelos Animados que deriva de CMapManager
//----------------------------------------------------------------------------------

#pragma once
#ifndef INC_ANIMATED_CORE_MODEL_H_
#define INC_ANIMATED_CORE_MODEL_H_

//------Forward declarations---------
class CCalCoreModel;
class CAnimatedInstanceModel;
//----------------------------------

#include "Base.h"
#include "MapManager/MapManager.h"
#include <string>
#include "cal3d/cal3d.h"

class CAnimatedCoreModel
{
	private:
		CalCoreModel * m_CalCoreModel;
		std::string m_Name;
		std::string m_MeshFilename;
		std::string m_SkeletonFilename;
		std::vector<std::string> m_TextureFilenameList;
		std::string m_Path;

		bool														LoadMesh								();
		bool														LoadSkeleton						();
		bool														LoadAnimation						(const std::string &Name, const std::string &Filename);

	public:
		CAnimatedCoreModel();
		~CAnimatedCoreModel();

		CalCoreModel *									GetCoreModel						();
		const std::string &							GetTextureName					(size_t id);
		size_t													GetNumTextures					() const{ return m_TextureFilenameList.size(); }
		void														Load										(const std::string &Path);
};

#endif
