#include "MapManager/MapManager.h"
#include "AnimatedCoreModel.h"
#include "AnimatedInstanceModel.h"
#include <string>
#include <vector>
#include "cal3d/cal3d.h"
#include "xml/XMLTreeNode.h"
#include "Exceptions/Exception.h"

#if defined( _DEBUG )
 #include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )


CAnimatedCoreModel::~CAnimatedCoreModel()
{
	CHECKED_DELETE(m_CalCoreModel);
}

CAnimatedCoreModel::CAnimatedCoreModel()
{
  m_CalCoreModel = new CalCoreModel("dummy");
}

//Cargar la malla del modelo animado con los métodos correspondientes del Cal3D.
bool CAnimatedCoreModel::LoadMesh()
{
	LOGGER->AddNewLog(ELL_INFORMATION, "CAnimatedCoreModel::LoadMesh Cargando la Malla \"%s\"", m_MeshFilename.c_str());
	if(!m_CalCoreModel->loadCoreMesh(m_MeshFilename.c_str()))
	{
		LOGGER->AddNewLog(ELL_INFORMATION, "CAnimatedCoreModel::LoadMesh Error Cal3D");
		return false;
	}
	else
	{
		return true;
	}
}

//Cargar el esqueleto del modelo animado.
bool CAnimatedCoreModel::LoadSkeleton()
{
	LOGGER->AddNewLog(ELL_INFORMATION, "CAnimatedCoreModel::LoadSkeleton Cargando el Esqueleto \"%s\"", m_SkeletonFilename.c_str());
	if(!m_CalCoreModel->loadCoreSkeleton(m_SkeletonFilename.c_str()))
	{
		LOGGER->AddNewLog(ELL_INFORMATION, "CAnimatedCoreModel::LoadSkeleton Error Cal3D ");
		return false;
	}
	else
	{
		return true;
	}
}

//Cargar la animación del modelo según el FileName.
bool CAnimatedCoreModel::LoadAnimation(const std::string &Name, const std::string &Filename)
{
  LOGGER->AddNewLog(ELL_INFORMATION, "CAnimatedCoreModel::LoadAnimation Cargando la Animacion \"%s\"", Filename.c_str());
	if(!m_CalCoreModel->loadCoreAnimation(Filename,Name))
	{
    LOGGER->AddNewLog(ELL_INFORMATION, "CAnimatedCoreModel::LoadAnimation Error Cal3D ");
		return false;
	}
	else
	{
		return true;
	}
}

//Devuelve el modelo core del Cal3D.
CalCoreModel * CAnimatedCoreModel::GetCoreModel( )
{
	return m_CalCoreModel;
}

const std::string & CAnimatedCoreModel::GetTextureName(size_t id)
{
	return m_TextureFilenameList[id];
}

//Cargar un fichero xml y todos los elementos de este modelo a partir del path pasado como parámetro.
void CAnimatedCoreModel::Load(const std::string &Path)
{
	bool l_bIsOk = true;
	m_Path = Path;
  CXMLTreeNode filexml;
  if (!filexml.LoadFile(m_Path.c_str()))
  {
		//Guardar el mensaje de error en el LOGGER
    std::string msg_error = "CAnimatedCoreModel::Load->Error al intentar leer el XML: " + m_Path;
		LOGGER->AddNewLog(ELL_ERROR, msg_error.c_str());
		throw CException(__FILE__, __LINE__, msg_error);
    l_bIsOk = false;
  }
  else
  {
		//<actor name="bot" radius_bs="2.0" pos_bs="0.0 1.0 0.0" effect="cal3d" technique="cal3dTechnique">
		//	<skeleton filename="bot.csf"/>
		//	<mesh filename="bot.CMF"/>
		//	<texture filename="rocketl.jpg"/>
		//	<texture filename="ranger.jpg"/>
		//	<texture filename="ranger_h.jpg"/>
		//	<animation name="idle" filename="idle.CAF"/>
		//	<animation name="run" filename="run.CAF"/>
		//	<animation name="hit" filename="hit.CAF"/>
		//	<animation name="die" filename="die.CAF"/>
		//	<animation name="shoot" filename="shoot.CAF"/>
		//</actor>

		CXMLTreeNode animatedModels = filexml["actor"];
    if (animatedModels.Exists())
    {
			m_Name = animatedModels.GetPszProperty("name"); 
			float l_sModelRadio = animatedModels.GetFloatProperty("radius_bs");        
			Vect3f l_sModelPos = animatedModels.GetVect3fProperty("pos_bs", 0);        
			std::string l_sModelEffect = animatedModels.GetPszProperty("effect");
			std::string l_sModelTechnique = animatedModels.GetPszProperty("technique"); 
			
			int32 numNodes = animatedModels.GetNumChildren();	
			
			for(int i=0; i < numNodes; i++)
      {
				CXMLTreeNode linea = animatedModels(i);
				if(strcmp(linea.GetName(),"skeleton") == 0)
				{
					m_SkeletonFilename = linea.GetPszProperty("filename");
					this->LoadSkeleton();
				}
				else if(strcmp(linea.GetName(),"mesh") == 0)
				{
					m_MeshFilename = linea.GetPszProperty("filename");
					this->LoadMesh();
				}
				else if(strcmp(linea.GetName(),"texture") == 0)
				{
					m_TextureFilenameList.push_back(linea.GetPszProperty("filename"));
				}
				else if(strcmp(linea.GetName(),"animation") == 0)
				{
					std::string l_sModelName = linea.GetPszProperty("name"); 
					std::string l_sFileName = linea.GetPszProperty("filename");
					this->LoadAnimation(l_sModelName, l_sFileName);
				}
			}//end for
		}//end if
	}//end else
}


       












