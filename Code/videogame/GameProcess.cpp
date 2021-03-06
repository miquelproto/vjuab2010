#include "Core.h"
#include "RenderManager.h"
#include "FontManager/FontManager.h"
#include "Timer/Timer.h"
#include "GameProcess.h"
#include "Math/Matrix44.h"
#include "Cameras/FPSCamera.h"
#include "Cameras/ThPSCamera.h"
#include "Object3D/Object3D.h"
#include "Texture/Texture.h"
#include "Vertex/IndexedVertexs.h"
#include "Vertex/VertexType.h"
#include "StaticMeshes/StaticMesh.h"
#include "ActionToInput.h"


#if defined( _DEBUG )
#include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )

CGameProcess::CGameProcess()
{
};


void	CGameProcess::Init ()
{
}

CGameProcess::~CGameProcess()
{
}

void CGameProcess::Update(float elapsedTime){


  CheckActionsFromInputs(elapsedTime);
}

void CGameProcess::Render(CRenderManager* rm) 
{
  //-------------------3D RENDER---------------------
  //Draw Axis And Grid
  rm->DrawGrid(10);
  rm->DrawAxis(20);


  //-------------------2D RENDER---------------------
}


void	CGameProcess::RenderDebugInfo	(CRenderManager * rm, CFontManager* fm, float fps)
{
  CProcess::RenderDebugInfo(rm, fm, fps);
}



void CGameProcess::CheckActionsFromInputs(float elapsedTime)
{
  float delta = 0.0;
  CCore *l_pCore = CORE;

  if((delta = l_pCore->GetInputManager()->GetActionToInput()->DoAction("ProcessInfo")) != 0.0f )
  {
    RenderDebugInfo(CORE->GetRenderManager(),CORE->GetFontManager(),  elapsedTime);
  }

  ////ScreenShot
  //if(GetInputManager()->GetActionToInput()->DoAction("SaveLogsInFile") != 0.0f)
  //{
  //  CRenderManager *rm = CORE->GetRenderManager();
  //  rm->GetWindowRect()
  //}

  //MoveXViewerCam
  if((delta = l_pCore->GetInputManager()->GetActionToInput()->DoAction("MoveXViewerCam")) != 0.0f )
  {
//    m_pObject3D->SetYaw( m_pObject3D->GetYaw() + delta * -0.01f );
  }

  //MoveZViewerCam
  if((delta = l_pCore->GetInputManager()->GetActionToInput()->DoAction("MoveZViewerCam")) != 0.0f )
  {
    //CThPSCamera* cam = (CThPSCamera*) m_pCamera;
    //cam->SetZoom( cam->GetZoom() + delta * -0.1f);
  }


  //YawViewerCam
  if((delta = CORE->GetInputManager()->GetActionToInput()->DoAction("YawViewerCam")) != 0.0f )
  {
//    m_pObject3D->SetYaw( m_pObject3D->GetYaw() + delta*0.05f );
  }

  //PitchViewerCam
  if((delta = l_pCore->GetInputManager()->GetActionToInput()->DoAction("PitchViewerCam")) != 0.0f )
  {
//    m_pObject3D->SetPitch( m_pObject3D->GetPitch() + delta*0.05f );
  }

  //ZoomViewerCam
  if((delta = l_pCore->GetInputManager()->GetActionToInput()->DoAction("ZoomViewerCam")) != 0.0f )
  {
//    m_pObject3D->SetPitch( m_pObject3D->GetPitch() + delta*0.05f );
  }

  //SlowZoomViewerCam
  if((delta = l_pCore->GetInputManager()->GetActionToInput()->DoAction("SlowZoomViewerCam")) != 0.0f )
  {
    //CActionToInput *i = CORE->GetInputManager()->GetActionToInput();
    //i->Reload();
  }
}
