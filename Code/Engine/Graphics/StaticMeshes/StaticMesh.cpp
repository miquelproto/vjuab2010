#include "StaticMesh.h"
#include "RenderManager.h"
#include "Texture/Texture.h"
#include "Vertex/VertexType.h"
#include "Vertex/IndexedVertex.h"
#include "Core.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define _HEADER 0xFF77
#define _FOOTER 0x77FF

CStaticMesh::CStaticMesh()
{
}
CStaticMesh::~CStaticMesh()
{

}
bool CStaticMesh::Load(const std::string &FileName)
{
  m_FileName = FileName;
  ifstream l_File(m_FileName.c_str(), ios::in|ios::binary);
  if(l_File.is_open())
  {
    unsigned short l_Header = 0;
    unsigned short l_CantMateriales = 0;
    unsigned short l_CantIndices = 0;
    unsigned short l_VertexType = 0;
    unsigned short l_CountTextures = 0;
    unsigned short l_CantVertices = 0;
    unsigned short l_IndexCount = 0;
    unsigned short l_Footer = 0;

    //Lectura del Header
    l_File.read((char *)&l_Header, sizeof(unsigned short));
    if(l_Header != _HEADER)
    {
      LOGGER->AddNewLog(ELL_WARNING, "CStaticMesh::Load Encabezado incorrecto al leer el archivo '%'",m_FileName);
      l_File.close();
      return false;
    }
    //Cantidad de materiales
    l_File.read((char *)&l_CantMateriales, sizeof(unsigned short));

    vector<unsigned short> l_vTiposVertices;

    //ciclo para cada material
    for(int j = 0; j < l_CantMateriales; j++)
    {
      //Lectura del Vertex Type
      l_File.read((char *)&l_VertexType, sizeof(unsigned short));
      l_vTiposVertices.push_back(l_VertexType);
      //Cantidad de texturas
      l_File.read((char *)&l_CountTextures, sizeof(unsigned short));
      //Lectura de materiales. Se leen "l_CountTextures" materiales.
      m_Textures.push_back(std::vector<CTexture *>());
      for(int i = 0; i < l_CountTextures; i++)
      {
        //Path Size
        unsigned short l_pathSize = 0;
        l_File.read((char *)&l_pathSize, sizeof(unsigned short));
        //Reading Path
        char * l_pathMaterial = new char[l_pathSize+1];
        int temp = sizeof(l_pathMaterial);
        l_File.read(l_pathMaterial, sizeof(char) * (l_pathSize+1));
        //l_pathMaterial[l_pathSize]='\0';
        CTexture *l_Texture=new CTexture();
        std::string l_strTexture;
        l_strTexture = "./Data/";
        l_strTexture += l_pathMaterial;
        
        l_Texture->Load(l_strTexture.c_str());

        m_Textures[j].push_back(l_Texture);
        CHECKED_DELETE_ARRAY(l_pathMaterial);
      }
    }//fin de ciclo para cada material

    //l_File.read((char *)&l_CantIndices, sizeof(unsigned short));
    for(int j = 0; j < l_CantMateriales; j++)
    {
      l_File.read((char *)&l_CantVertices, sizeof(unsigned short));
      int l_Size=0;

      l_VertexType = l_vTiposVertices[j];
      if(l_VertexType == TNORMAL_TEXTURE1_VERTEX::GetVertexType())
        l_Size=sizeof(TNORMAL_TEXTURE1_VERTEX);
      else if(l_VertexType == TNORMAL_TEXTURE2_VERTEX::GetVertexType())
        l_Size=sizeof(TNORMAL_TEXTURE2_VERTEX);
      else if(l_VertexType == TNORMAL_COLORED_VERTEX::GetVertexType())
        l_Size=sizeof(TNORMAL_COLORED_VERTEX);
  
      char *l_Vtxs=new char[l_Size*l_CantVertices];
      l_File.read((char *)&l_Vtxs[0],l_Size*l_CantVertices);

      /*for(int i=0;i<l_CantVertices;++i)
      {
        l_Vtxs[i].color=0xffffffff;
      }*/

      l_File.read((char *)&l_IndexCount, sizeof(unsigned short));

      unsigned short *l_Indxs = new unsigned short[l_IndexCount];

      l_File.read((char *)&l_Indxs[0],sizeof(unsigned short)*l_IndexCount);

      CRenderableVertexs * l_RV;
      //-----------------------------------
      if(l_VertexType == TNORMAL_TEXTURE1_VERTEX::GetVertexType())
      {
        l_RV = new CIndexedVertex<TNORMAL_TEXTURE1_VERTEX>(CORE->GetRenderManager(), l_Vtxs, l_Indxs, l_CantVertices, l_IndexCount);
      }
      else if(l_VertexType == TNORMAL_TEXTURE2_VERTEX::GetVertexType())
      {
        l_RV = new CIndexedVertex<TNORMAL_TEXTURE2_VERTEX>(CORE->GetRenderManager(), l_Vtxs, l_Indxs, l_CantVertices, l_IndexCount);
      }
      else if(l_VertexType == TNORMAL_COLORED_VERTEX::GetVertexType())
      {
        l_RV = new CIndexedVertex<TNORMAL_COLORED_VERTEX>(CORE->GetRenderManager(), l_Vtxs, l_Indxs, l_CantVertices, l_IndexCount);
      }
      //-----------------------------------

      //CRenderableVertexs *l_RV = new CIndexedVertex<TNORMAL_COLORED_TEXTURE1_VERTEX>(CORE->GetRenderManager(), l_Vtxs, l_Indxs, l_CantVertices, l_IndexCount);
      CHECKED_DELETE_ARRAY(l_Vtxs);
      CHECKED_DELETE_ARRAY(l_Indxs);
      m_RVs.push_back(l_RV);
    }
    l_File.read((char *)&l_Footer, sizeof(unsigned short));
    if(l_Footer != _FOOTER)
    {
      LOGGER->AddNewLog(ELL_WARNING, "CStaticMesh::Load el archivo '%s' no se encuentra",m_FileName.c_str());
      l_File.close();
      return false;
    }
    l_File.close();
  }
  else
  {
      LOGGER->AddNewLog(ELL_WARNING, "CStaticMesh::Load Pie de archivo incorrecto al leer el archivo '%s'",m_FileName.c_str());
      l_File.close();
      return false;
  }
  return true;
}
bool CStaticMesh::ReLoad()
{
  //Release();
  //Load(m_FileName);
  return true;
}
void CStaticMesh::Render(CRenderManager *RM) const 
{
  vector<CRenderableVertexs*>::const_iterator l_Iter = m_RVs.begin();
  for(int i=0;l_Iter != m_RVs.end();++i, ++l_Iter) 
  {
    for(size_t j=0;j<m_Textures[i].size();++j)
    {
      m_Textures[i][j]->Activate(j);
    }
    (*l_Iter)->Render(RM);
  }
}

void CStaticMesh::Release()
{
  vector<CRenderableVertexs*>::iterator l_Iter = m_RVs.begin();
  while(l_Iter != m_RVs.end()) 
  {
    CHECKED_DELETE(*l_Iter);
    ++l_Iter;
  }
  m_RVs.clear();
}