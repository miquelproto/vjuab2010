#include "AnimatedInstanceModel.h"
#include "AnimatedCoreModel.h"
#include "Vertex/VertexType.h"
#include "AnimatedInstanceModel.h"
#include "RenderManager.h"
#include <string>

#if defined( _DEBUG )
#include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )

void CAnimatedInstanceModel::Render(CRenderManager *RM)
{
  RenderModelBySoftware(RM);
}
void CAnimatedInstanceModel::RenderModelBySoftware(CRenderManager *RM)
{
  //leer renderModel
  LPDIRECT3DDEVICE9 l_pDevice = RM->GetDevice();

  // get the renderer of the model
  CalRenderer * pCalRenderer;
  pCalRenderer = m_CalModel->getRenderer();

  // begin the rendering loop
  if(!pCalRenderer->beginRendering()) return;

  int l_iVBCursor=0;
  int l_iIBCursor=0;

  DWORD dwVBLockFlags=D3DLOCK_NOOVERWRITE;
  DWORD dwIBLockFlags=D3DLOCK_NOOVERWRITE;

  l_pDevice->SetStreamSource( 0, m_pVB, 0,  sizeof(TNORMAL_TEXTURE1_VERTEX) );
  l_pDevice->SetFVF(TNORMAL_TEXTURE1_VERTEX::GetFVF());
  l_pDevice->SetIndices(m_pIB);
  
  // get the number of meshes
  int l_iMeshCount;
  l_iMeshCount = pCalRenderer->getMeshCount();

  // render all meshes of the model
  int l_iMeshId;
  for(l_iMeshId = 0; l_iMeshId < l_iMeshCount; l_iMeshId++)
  {
    // get the number of submeshes
    int l_iSubmeshCount;
    l_iSubmeshCount = pCalRenderer->getSubmeshCount(l_iMeshId);

    // render all submeshes of the mesh
    int l_iSubmeshId;
    for(l_iSubmeshId = 0; l_iSubmeshId < l_iSubmeshCount; l_iSubmeshId++)
    {
      // select mesh and submesh for further data access
      if(pCalRenderer->selectMeshSubmesh(l_iMeshId, l_iSubmeshId))
      {
		   
		    // Get vertexbuffer from the model		  		  
		    TNORMAL_TEXTURE1_VERTEX* l_pVertices;

		    m_pVB->Lock(l_iVBCursor*sizeof(TNORMAL_TEXTURE1_VERTEX), pCalRenderer->getVertexCount()*sizeof(TNORMAL_TEXTURE1_VERTEX), (void**)&l_pVertices, dwVBLockFlags);

        int l_iVertexCount = pCalRenderer->getVerticesNormalsAndTexCoords((float*)l_pVertices);
		    m_pVB->Unlock();
		  
		    CalIndex *meshFaces;

        int l_iFaceCount;

		    m_pIB->Lock(l_iIBCursor* 3*sizeof(CalIndex), pCalRenderer->getFaceCount()*3* sizeof(CalIndex), (void**)&meshFaces,dwIBLockFlags);

		    l_iFaceCount = pCalRenderer->getFaces(meshFaces);
		    m_pIB->Unlock();


        l_pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
        l_pDevice->SetTexture(0,(LPDIRECT3DTEXTURE9)pCalRenderer->getMapUserData(0));
          
		    l_pDevice->DrawIndexedPrimitive(
			    D3DPT_TRIANGLELIST,
			    l_iVBCursor,
			    0,
			    l_iVertexCount,
			    l_iIBCursor*3,
			    l_iFaceCount
			  );

		    l_iVBCursor+=l_iVertexCount;
		    l_iIBCursor+=l_iFaceCount;

		    dwIBLockFlags=D3DLOCK_NOOVERWRITE;
		    dwVBLockFlags=D3DLOCK_NOOVERWRITE;

      }
    }
  }
  // end the rendering
  pCalRenderer->endRendering();
}
void CAnimatedInstanceModel::Update(float ElapsedTime)
{
  m_CalModel->update(ElapsedTime);
}
void CAnimatedInstanceModel::Initialize(CAnimatedCoreModel *AnimatedCoreModel)
{
  m_AnimatedCoreModel = AnimatedCoreModel;
  m_CalModel = new CalModel(m_AnimatedCoreModel->GetCoreModel());
}
void CAnimatedInstanceModel::InitD3D(CRenderManager *RM)
{
  int l_Indx = 0;
  int l_Vrtx = 0;
  for(int i = 0; i < m_CalModel->getCoreModel()->getCoreMeshCount(); i++)
  {
    for(int j = 0; j < m_CalModel->getCoreModel()->getCoreMesh(i)->getCoreSubmeshCount(); i++)
    {
      l_Indx += m_CalModel->getMesh(i)->getSubmesh(j)->getFaceCount()*3;
      l_Vrtx += m_CalModel->getMesh(i)->getSubmesh(j)->getVertexCount();
    }
  }
    // Create vertex buffer
  RM->GetDevice()->CreateVertexBuffer(l_Vrtx*sizeof(TNORMAL_TEXTURE1_VERTEX),
    D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, TNORMAL_TEXTURE1_VERTEX::GetFVF(), 
    D3DPOOL_DEFAULT , &m_pVB, NULL);
  // Create index buffer
  if(sizeof(CalIndex)==2)
  {
    RM->GetDevice()->CreateIndexBuffer(l_Indx*sizeof(CalIndex),
      D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC,D3DFMT_INDEX16,
      D3DPOOL_DEFAULT ,&m_pIB, NULL);
  }
  else
  {
    RM->GetDevice()->CreateIndexBuffer(l_Indx*sizeof(CalIndex),
      D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC,D3DFMT_INDEX32,
      D3DPOOL_DEFAULT ,&m_pIB, NULL);
  }
}
void CAnimatedInstanceModel::Destroy()
{
  CHECKED_DELETE(m_CalModel);
  CHECKED_RELEASE(m_pVB);
  CHECKED_RELEASE(m_pIB);
}
void CAnimatedInstanceModel::ExecuteAction(int Id, float Time)
{
  m_CalModel->getMixer()->executeAction(Id, 0.0f, Time);
}
void CAnimatedInstanceModel::BlendCycle(int Id, float Time)
{
  m_CalModel->getMixer()->blendCycle(Id, 1.0f, Time);
}
void CAnimatedInstanceModel::ClearCycle(float Time)
{
  m_CalModel->getMixer()->clearCycle(m_CurrentCycle, Time);
}
int CAnimatedInstanceModel::GetCurrentCycle() const
{
  return m_CurrentCycle;
}
int CAnimatedInstanceModel::GetCurrentAction() const
{
  return m_CurrentAnimationId;
}