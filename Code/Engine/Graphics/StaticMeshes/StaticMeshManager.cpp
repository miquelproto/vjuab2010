#include "StaticMeshManager.h"
#include "xml/XMLTreeNode.h"
#include <vector>

#if defined( _DEBUG )
#include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )

bool CStaticMeshManager::Load(const std::string &FileName)
{
  bool l_bIsOk = true;
  m_FileName = FileName;
  CXMLTreeNode filexml;
  if (!filexml.LoadFile(m_FileName.c_str()))
  {
    printf("ERROR loading the file.");
    l_bIsOk = false;
  }
  else
  {
    CXMLTreeNode cores = filexml["static_meshes"];
    if (cores.Exists())
    {
      int32 numNodes = cores.GetNumChildren();		
      for(int i=0; i < numNodes; i++)
      {
        //recibe parametros
        std::string l_sCoreName = cores(i).GetPszProperty("name");        
        std::string l_sCorePath = cores(i).GetPszProperty("filename");    
        
        CStaticMesh *l_static_mesh = new CStaticMesh();
        if(l_static_mesh->Load(l_sCorePath))
        {
          this->AddResource(l_sCoreName,l_static_mesh);        
        }
      }
    }
    else
    {
      l_bIsOk = false;
    }
  }//else if (!filexml.LoadFile(m_FileName.c_str()))

  if(l_bIsOk)
  {
  }
  
  return l_bIsOk;
}

bool CStaticMeshManager::Reload()
{
  Destroy();
  return Load(m_FileName);
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------