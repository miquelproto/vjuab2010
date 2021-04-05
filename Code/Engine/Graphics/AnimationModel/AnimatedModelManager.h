//----------------------------------------------------------------------------------
// CRenderableObjectsManager class
// Author: Andrea Cristobo
//
// Description:
// Mánager de Modelos Animados que deriva de CMapManager
//----------------------------------------------------------------------------------

#pragma once
#ifndef INC_ANIMATED_MODEL_MANAGER_H_
#define INC_ANIMATED_MODEL_MANAGER_H_

//------Forward declarations---------
class CAnimatedCoreModel;
class CAnimatedInstanceModel;
//----------------------------------

#include "Base.h"
#include "MapManager/MapManager.h"
#include <string>

class CAnimatedModelManager : public CMapManager<CAnimatedCoreModel>
{
	public:
		CAnimatedModelManager();
		~CAnimatedModelManager();

		CAnimatedCoreModel *				GetCore						(const std::string &Name, const std::string &Path);
		CAnimatedInstanceModel *			GetInstance					(const std::string &Name);

};

#endif
