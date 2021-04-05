//----------------------------------------------------------------------------------
// CObject3D class
// Author: Marco Torres
//
// Description:
// Esta clase será la base de toda instancia que pueda existir en la escena
//----------------------------------------------------------------------------------
#pragma once
#ifndef INC_IND_VERTEX_H_
#define INC_IND_VERTEX_H_

#include "Math\MathTypes.h"
#include "Math\Vector3.h"
#include "RenderManager.h"
#include "Vertex/RenderableVertex.h"


template<class T>
class CIndexedVertex : public CRenderableVertexs
{
protected:
	inline size_t GetVertexSize() const {return sizeof(T);}
	inline size_t GetIndexSize() const {return sizeof(unsigned short);}
public:
	CIndexedVertex(CRenderManager * RM, void *VertexAddress, void *IndexAddres, size_t VertexCount, size_t IndexCount)
	{
		m_IndexCount = IndexCount;
		m_VertexCount = VertexCount;

		VOID * pVertices, * pIndices;

		//VertexBuffer
		RM->GetDevice()->CreateVertexBuffer(VertexCount*GetVertexSize(), 0, T::GetFVF(), D3DPOOL_DEFAULT, &m_VB, NULL);
		m_VB->Lock(0, VertexCount*GetVertexSize(),&pVertices, 0 );
		memcpy(pVertices, VertexAddress, VertexCount*GetVertexSize());
		m_VB->Unlock();

		//IndexBuffer
		RM->GetDevice()->CreateIndexBuffer(IndexCount*GetIndexSize(), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_IB, NULL);
		m_IB->Lock(0, IndexCount*GetIndexSize(),&pIndices, 0 );
		memcpy(pIndices, IndexAddres, IndexCount*GetIndexSize());
		m_IB->Unlock();
	};
	~CIndexedVertex()
  {
    CHECKED_RELEASE(m_IB);
    CHECKED_RELEASE(m_VB);
  }
	bool Render(CRenderManager *RM) const {
    bool l_bIsOk = true;
    l_bIsOk = RM->GetDevice()->SetStreamSource(0,m_VB,0, GetVertexSize());
		l_bIsOk = RM->GetDevice()->SetIndices(m_IB);
	  l_bIsOk = RM->GetDevice()->SetFVF(T::GetFVF());
	  l_bIsOk = RM->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_VertexCount, 0, GetFacesCount());
    
    return l_bIsOk;
	}
	virtual inline unsigned short GetVertexType() const
	{
		return T::GetVertexType();
	}
};

#endif