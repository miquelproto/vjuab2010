#include "AnimatedModelManager.h"
#include "MapManager/MapManager.h"
#include "AnimatedCoreModel.h"
#include "AnimatedInstanceModel.h"
#include <string>
#include <vector>

#if defined( _DEBUG )
 #include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )


//Cargar un CAnimatedCoreModel en caso de no existir y devolver su dirección de memoria. 
//Utilizaremos el mapa de la clase CmapManager para guardar la estructura.
CAnimatedCoreModel * CAnimatedModelManager::GetCore(const std::string &Name, const std::string &Path)
{
	
	CAnimatedCoreModel* l_AnimatedCoreModel= NULL;
	l_AnimatedCoreModel = GetResource(Name);
	if(l_AnimatedCoreModel==NULL)
	{
		if(Path != "")
		{   
			
		
			//l_AnimatedCoreModel = new CAnimatedCoreModel(Name)
			l_AnimatedCoreModel = new CAnimatedCoreModel();

			//crear el core
			l_AnimatedCoreModel->Load(Path);

			//meter core
			if(l_AnimatedCoreModel != NULL)
			{
				AddResource(Name,l_AnimatedCoreModel);
			}
		}
	}

   return l_AnimatedCoreModel; 
	
}

//Devolverá una instancia de tipo CAnimatedInstanceModel según el nombre de la core cargada previamente.
CAnimatedInstanceModel * CAnimatedModelManager::GetInstance(const std::string &Name)
{
	CAnimatedCoreModel *l_AnimatedCoreModel=GetCore(Name,"");
	if(l_AnimatedCoreModel!=NULL)
	{
		CAnimatedInstanceModel *l_AnimatedInstanceModel= new CAnimatedInstanceModel();
		l_AnimatedInstanceModel->Initialize(l_AnimatedCoreModel);
		l_AnimatedInstanceModel->InitD3D(CORE->GetRenderManager());
		return l_AnimatedInstanceModel;
	}
	return NULL;
}
