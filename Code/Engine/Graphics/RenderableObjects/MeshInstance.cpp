#include "MeshInstance.h"
#include "RenderManager.h"
#include "StaticMeshes/StaticMeshManager.h"

#if defined( _DEBUG )
 #include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )


CInstanceMesh::CInstanceMesh(const std::string &Name, const std::string &CoreName)
{
  m_StaticMesh = NULL;
  m_bIsOk = true;

  CStaticMeshManager *sm = CORE->GetStaticMeshManager();
  m_StaticMesh = sm->GetResource(CoreName);
  if(m_StaticMesh == NULL)
  {
    m_bIsOk = false;
  }
  else
  {
    SetName(Name);
    SetPitch(0.0);
    SetPosition(0.0);
    SetRoll(0.0);
    SetVisible(false);
    SetYaw(0.0);
  }
}

CInstanceMesh::~CInstanceMesh()
{
  
}

void CInstanceMesh::Render(CRenderManager *RM)
{
  m_StaticMesh->Render(RM);
}

/*void CInstanceMesh::Update(float ElapsedTime)
{
  ElapsedTime = 0.f;
}
*/
//----------------------------------------------------------------------------
// Init data
//----------------------------------------------------------------------------
bool CInstanceMesh::Init()
{
  m_bIsOk = true;



  if (!m_bIsOk){
    Release();
  }

  return m_bIsOk;
}

//----------------------------------------------------------------------------
// Finalize data
//----------------------------------------------------------------------------
void CInstanceMesh::Done(){
  if (IsOk())
  {
    Release();
    m_bIsOk = false;
  }
}

//----------------------------------------------------------------------------
// Free memory
//----------------------------------------------------------------------------
void CInstanceMesh::Release(){
//free memory
}



//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------