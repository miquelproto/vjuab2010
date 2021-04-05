#include "MapManager/MapManager.h"
#include "RenderableObjectsManager.h"
#include "RenderableObject.h"
#include "MeshInstance.h"
#include "xml/XMLTreeNode.h"
#include "Logger/Logger.h"
#include "Exceptions/Exception.h"
#include <string>
#include <vector>
#include "Vertex/RenderableVertex.h"

#if defined( _DEBUG )
 #include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )


bool CRenderableObjectsManager::Load(const std::string &FileName)
{
	bool l_bIsOk = true;
	m_FileName = FileName;
  CXMLTreeNode filexml;
  if (!filexml.LoadFile(m_FileName.c_str()))
  {
		//Guardar el mensaje de error en el LOGGER
    std::string msg_error = "RenderableObjectsManager::Load->Error al intentar leer el XML: " + m_FileName;
		LOGGER->AddNewLog(ELL_ERROR, msg_error.c_str());
		throw CException(__FILE__, __LINE__, msg_error);
    l_bIsOk = false;
  }
  else
  {
		//<renderable_objs>
		//	<object name="Box01" core="Box01" pos="2.27125 0.0 0.0" yaw="0.0" pitch="-90.0" roll="90.0"  />
		//	<object name="Box02" core="Box02" pos="0.0 0.0 0.0" yaw="0.0" pitch="0.0" roll="0.0"  />
		//</renderable_objs>

    CXMLTreeNode renders = filexml["renderable_objs"];

    if (renders.Exists())
    {
      int32 numNodes = renders.GetNumChildren();		
      for(int i=0; i < numNodes; i++)
      {
        CXMLTreeNode object = renders(i)["object"];
        if (object.Exists())
        {
           //CRenderableObjectsManager l_render_manag_object;
           //recibe parametros
           std::string l_sObjectName = object.GetPszProperty("name");   
					 std::string l_sObjectCore = object.GetPszProperty("core");
           Vect3f l_V3ObjectPos = object.GetVect3fProperty("pos", NULL);    
					 float l_fObjectYaw = object.GetFloatProperty("yaw");        
           float l_fObjectPitch = object.GetFloatProperty("pitch"); 
           float l_fObjectRoll = object.GetFloatProperty("roll"); 
            
           //crea instancia de la core
           CRenderableObject *inst;
           inst = AddMeshInstance(l_sObjectCore, l_sObjectName, l_V3ObjectPos,l_fObjectYaw, l_fObjectPitch, l_fObjectRoll);
           if(inst == 0)
           {
              std::string msg_error = "RenderableObjectsManager::Load->Error al intentar crear la Instancia: " + l_sObjectName;
		          LOGGER->AddNewLog(ELL_ERROR, msg_error.c_str());
		          throw CException(__FILE__, __LINE__, msg_error);
              return false;
           }
        }
        else
        {
          return false;
        }
      }
    }
    else
    {
      return false;
    }
  }
	return l_bIsOk;
}

bool CRenderableObjectsManager::Reload()
{
  Destroy();
  return this->Load(m_FileName);
}

//Llamar al método update de cada uno de los elementos del vector
void CRenderableObjectsManager::Update(float ElapsedTime)
{
	std::vector<CRenderableObject*>::iterator l_Iter;
  
  for(l_Iter = m_RenderableObjects.begin();l_Iter != m_RenderableObjects.end();++l_Iter) 
  {
    //std::string a = (*l_Iter)->GetName();
    (*l_Iter)->Update(ElapsedTime);
  }
}

//Agregar un elemento al mapa
void CRenderableObjectsManager::AddResource(const std::string &Name, CRenderableObject *RenderableObject)
{
//	CMapManager <CRenderableObject> l_temp;
//	l_temp.AddResource(Name, RenderableObject);
  	if (m_Resources.find(Name)==m_Resources.end()) {
//      m_Resources.insert(Name, RenderableObject);
      m_Resources[Name] = &RenderableObject;
      m_RenderableObjects.push_back(RenderableObject);
		}
		else
		{
		//Guardar el mensaje de error en el LOGGER
    std::string msg_error = "RenderableObjectsManager::AddResource->Error al intentar añadir el recurso: " + Name;
		LOGGER->AddNewLog(ELL_ERROR, msg_error.c_str());
		throw CException(__FILE__, __LINE__, msg_error);
		}
}

//Devolver el CORE del elemento a buscar
CRenderableObject * CRenderableObjectsManager::GetInstance(const std::string &Name) const
{
  CRenderableObject *inst = 0;
  std::map<std::string, CRenderableObject*>::const_iterator it;

//  *it = m_Resources.find(Name);
//  it = m_Resources.find(Name);

  //CRenderableObject* inst = GetResource(Name);
/*  
  //  CRenderableObject inst = 0;  
  CMapManager<CRenderableObject*>::GetResource(Name); 
//  std::map<std::string, CRenderableObject*>::const_iterator it = m_Resources.find(Name);
	if (it != m_Resources.end()) 
  {
    CRenderable *inst = it->second;      
    //inst = GetResource(Name);
    //*inst = m_Resources[Name];
	}
  else
  {
    std::string msg_warning = "RenderableObjectsManager::GetInstance->Error al intentar obtener la core: " + Name;
	  LOGGER->AddNewLog(ELL_WARNING, msg_warning.c_str());
	  throw CException(__FILE__, __LINE__, msg_warning);
//  }
*/
//	CMapManager <CRenderableObject> l_temp;
//	return l_temp.GetResource(Name);
  return inst;
}

//Llamar al método render de cada uno de los elementos del vector
void CRenderableObjectsManager::Render(CRenderManager *RM)
{
	std::vector<CRenderableObject*>::const_iterator l_Iter = m_RenderableObjects.begin();
  for(;l_Iter != m_RenderableObjects.end();++l_Iter) 
  {
    (*l_Iter)->Render(RM);
  }
}

//Añadir un CRenderableObject de tipo CMeshInstance que tiene una static mesh con su posición, rotación, etc.
CRenderableObject * CRenderableObjectsManager::AddMeshInstance(const std::string &CoreMeshName, const std::string &InstanceName, const Vect3f &Position, const float &Yaw, const float &Pitch, const float &Roll)
{
   //escribe parametros en la instancia de la malla
   CRenderableObject* inst = new CInstanceMesh(InstanceName, CoreMeshName);
   inst->SetPosition(Position);
   inst->SetYaw(Yaw);
   inst->SetPitch(Pitch);
   inst->SetRoll(Roll);
   inst->SetVisible(true);
   //añade el recurso en el manager
   AddResource(InstanceName, inst);
   return inst;
}

//Limpia el mapa y el vector
//En el mapa están todos ordenados por el nombre y en el vector están todos seguidos en un vector.
void CRenderableObjectsManager::CleanUp()
{
	//eliminar el vector
	m_RenderableObjects.clear();
	//eliminar el mapa
	Destroy();
}




