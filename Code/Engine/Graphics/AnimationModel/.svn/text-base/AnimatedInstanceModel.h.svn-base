//----------------------------------------------------------------------------------
// CAnimatedInstanceModel class
// Author: 
//
// Description:
// Esta clase encapsulará a la clase CalModel del Cal3D.
//----------------------------------------------------------------------------------

#pragma once
#ifndef INC_ANIMATED_INSTANCE_MODEL_H_
#define INC_ANIMATED_INSTANCE_MODEL_H_

//------Forward declarations---------
class CAnimatedCoreModel;
class CRenderManager;
//----------------------------------

#include "Base.h"
//Revisar si son estas librerias
#include "cal3d/cal3d.h"
#include "Texture/Texture.h"

#include <string>

class CAnimatedInstanceModel
{
	private:
		CalModel *								m_CalModel;
		CAnimatedCoreModel *			m_AnimatedCoreModel;
		std::vector<CTexture *>		m_TextureList;
		int												m_CurrentCycle;
		int												m_CurrentAnimationId;
		float											m_CurrentAnimationTime;
		LPDIRECT3DVERTEXBUFFER9		m_pVB;
		LPDIRECT3DINDEXBUFFER9		m_pIB;
		int												m_NumVtxs;
		int												m_NumFaces;
		bool											LoadVertexBuffer									(CRenderManager *RM);
		void											LoadTextures											();

	public:
		CAnimatedInstanceModel();
		~CAnimatedInstanceModel();

		void											Render														(CRenderManager *RM);
		void											RenderModelBySoftware							(CRenderManager *RM);
		void											Update														(float ElapsedTime);
		void											Initialize												(CAnimatedCoreModel *AnimatedCoreModel);
		void											InitD3D														(CRenderManager *RM);
		void											Destroy														();
		void											ExecuteAction											(int Id, float Time);
		void											BlendCycle												(int Id, float Time);
		void											ClearCycle												(float Time);
		int												GetCurrentCycle										() const;
		int												GetCurrentAction									() const;
};

#endif

