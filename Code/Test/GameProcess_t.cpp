#include "Core.h"
#include "RenderManager.h"
#include "FontManager/FontManager.h"
#include "Timer/Timer.h"
#include "GameProcess_t.h"
#include "Math/Matrix44.h"
#include "Cameras/FPSCamera.h"
#include "Cameras/ThPSCamera.h"
#include "Object3D/Object3D.h"
#include "Texture/Texture.h"
#include "Vertex/IndexedVertexs.h"
#include "Vertex/VertexType.h"
#include "StaticMeshes/StaticMesh.h"
#include "RenderableObjects/RenderableObjectsManager.h"
#include "ActionToInput.h"


#if defined( _DEBUG )
#include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )
CTexture m_Texture;

LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
LPDIRECT3DINDEXBUFFER9 indexBuffer;

TTEXTURE1_VERTEX  m_vTexturasABorrar[6] =
{
  {-2.5f,3.0f,0.0f,0.0f,0.0f},
  {2.5f,3.0f,0.0f,1.0f,0.0f},
  {-2.5f,0.0f,0.0f,0.0f,1.0f},
  {-2.5f,0.0f,0.0f,0.0f,1.0f},
  {2.5f,3.0f,0.0f,1.0f,0.0f},
  {2.5f,0.0f,0.0f,1.0f,1.0f}
};

TTEXTURE1_VERTEX  g_Textures4[4] =
{
  {-2.5f,3.0f,0.0f,0.0f,0.0f},
  {2.5f,3.0f,0.0f,1.0f,0.0f},
  {-2.5f,0.0f,0.0f,0.0f,1.0f},
  {2.5f,0.0f,0.0f,1.0f,1.0f}
};

unsigned short g_index[6] = {0,1,2,2,1,3};

CGameProcess_t::CGameProcess_t()
{
  m_fPosX = 0;
  m_fPosY = 100;
  m_TimerCounter = 0;
  m_iDirection = 100; 
  m_fFPS = 0.f;
  m_fRotacion = 0.f;
  m_bDrawCube = true;
  m_MaxVision = 42.0f;
  m_MinVision = 42.0f;
  m_box = 0;
};

CStaticMesh g_StaticMesh;

CIndexedVertex<TTEXTURE1_VERTEX> * g_pIV = NULL;

void	CGameProcess_t::Init ()
{
  //VOID* pVertices, *pIndices;
  ////VertexBuffer
  //CORE->GetRenderManager()->GetDevice()->CreateVertexBuffer(4*sizeof(TTEXTURE1_VERTEX), 0, TTEXTURE1_VERTEX::GetFVF(), D3DPOOL_DEFAULT, &vertexBuffer, NULL);
  //vertexBuffer->Lock(0, 4*sizeof(TTEXTURE1_VERTEX),&pVertices, 0 );
  //memcpy(pVertices, g_Textures4, 4*sizeof(TTEXTURE1_VERTEX));
  //vertexBuffer->Unlock();
  ////IndexBuffer
  //CORE->GetRenderManager()->GetDevice()->CreateIndexBuffer(6*sizeof(unsigned short), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer, NULL);
  //indexBuffer->Lock(0, 6*sizeof(unsigned short),&pIndices, 0 );
  //memcpy(pIndices, g_index, 6*sizeof(unsigned short));
  //indexBuffer->Unlock();
  g_pIV = new CIndexedVertex<TTEXTURE1_VERTEX>(CORE->GetRenderManager(),g_Textures4,g_index,4,6);

  m_pObject3D = new CObject3D();
  uint32 w,h;
  CORE->GetRenderManager()->GetWandH(w,h);
  float aspectRatio = (float)w/h;

//  float zn, float zf, float fov, /*float aspect,*/ CObject3D* object3D, float zoom;
  m_pCamera = new CThPSCamera(0.1f, 100.f, 45.0f * D3DX_PI / 180.0f, aspectRatio, m_pObject3D, 10.f);
  m_pObject3D->SetPitch(-13.0f);
  m_pObject3D->SetYaw(1.5f);

  //g_StaticMesh.Load("E:/vjuab2010/Run/Test/Data/mi1ermesh.mesh");

  m_Texture.Load("stonewall.jpg");

  //m_box = new CStaticMesh();
  //m_box->Load("./Data/mi1ermesh.mesh");
  //m_box->Load("E:/vjuab2010/Run/Test/Data/mi1ermesh.mesh");

  //CStaticMeshManager *smm = new CStaticMeshManager(->GetStaticMeshManager();

  //932658555 Telepizza
  //+1 808-923-0411 Park Shore Waikiki - Honolulu‎
}

CGameProcess_t::~CGameProcess_t()
{
  CHECKED_DELETE(m_pCamera);
  CHECKED_DELETE(m_pObject3D);
  CHECKED_DELETE(g_pIV);
  //CHECKED_DELETE(m_box);
  //CHECKED_DELETE(m_pAction);
}

void CGameProcess_t::Update(float elapsedTime){
//  int jorls = 0;

  //CheckActionsFromInputs(elapsedTime);
  //m_pFPS = elapsedTime;	//TODO Frame rate en pantalla
  /*m_fPosX += elapsedTime * m_iDirection;

  if(m_fPosX > 480){
  m_iDirection = -120;
  }
  if(m_fPosX < 0){
  m_iDirection = 100;
  }
  m_fRotacion += elapsedTime;*/
  // Si quieres volverlo $%&% descomenta la próxima línea (Prueba de memory leaks)
  //int *p = new int; 

  //CORE->GetInputManager()->IsDownUp(IDV_MOUSE, MOUSE_BUTTON_LEFT);
  Vect3i deltas = CORE->GetInputManager()->GetMouseDelta();

//Estabilizar el Yaw
  m_pObject3D->SetPitch( m_pObject3D->GetPitch() + deltas.y*0.05f );
  m_pObject3D->SetYaw( m_pObject3D->GetYaw() + deltas.x * -0.01f );


  CThPSCamera * cam = (CThPSCamera*) m_pCamera;
  cam->SetZoom( cam->GetZoom() + deltas.z * -0.1f);


  if (CORE->GetInputManager()->IsDownUp(IDV_KEYBOARD, KEY_SPACE))
  {
    m_bDrawCube = !m_bDrawCube;
  }

  //Moverse a travez del escenario
  Vect3f l_vPos = m_pObject3D->GetPosition();
  float l_fVelocity = 5;

  if (CORE->GetInputManager()->IsDown(IDV_KEYBOARD,KEY_LSHIFT))
  {
    l_fVelocity = 10;
  }
  if (CORE->GetInputManager()->IsDown(IDV_KEYBOARD,KEY_LCTRL))
  {
    l_fVelocity = 2;
  }
  if (CORE->GetInputManager()->IsDown(IDV_KEYBOARD,KEY_W))
  {
    l_vPos.x = l_vPos.x + cos(m_pObject3D->GetYaw())*elapsedTime*l_fVelocity;
    l_vPos.z = l_vPos.z + sin(m_pObject3D->GetYaw())*elapsedTime*l_fVelocity;
    m_pObject3D->SetPosition(l_vPos);
  }

  if (CORE->GetInputManager()->IsDown(IDV_KEYBOARD,KEY_S))
  {
    l_vPos.x = l_vPos.x - cos(m_pObject3D->GetYaw())*elapsedTime*l_fVelocity;
    l_vPos.z = l_vPos.z - sin(m_pObject3D->GetYaw())*elapsedTime*l_fVelocity;
    m_pObject3D->SetPosition(l_vPos);
  }

  if (CORE->GetInputManager()->IsDown(IDV_KEYBOARD,KEY_A))
  {
    l_vPos.x = l_vPos.x + cos(m_pObject3D->GetYaw()+FLOAT_PI_VALUE/2)*elapsedTime*l_fVelocity;
    l_vPos.z = l_vPos.z + sin(m_pObject3D->GetYaw()+FLOAT_PI_VALUE/2)*elapsedTime*l_fVelocity;
    m_pObject3D->SetPosition(l_vPos);
  }

  if (CORE->GetInputManager()->IsDown(IDV_KEYBOARD,KEY_D))
  {
    l_vPos.x = l_vPos.x + cos(m_pObject3D->GetYaw()-FLOAT_PI_VALUE/2)*elapsedTime*l_fVelocity;
    l_vPos.z = l_vPos.z + sin(m_pObject3D->GetYaw()-FLOAT_PI_VALUE/2)*elapsedTime*l_fVelocity;
    m_pObject3D->SetPosition(l_vPos);
  }
  //m_pAction->Update(); //InputToActions->Update()
}

void CGameProcess_t::Render(CRenderManager* rm) 
{
  m_Texture.Activate(0);

  //Dibuja un plano con el logo del barça
  g_pIV->Render(rm);

  //CORE->GetRenderManager()->GetDevice()->SetFVF(TTEXTURE1_VERTEX::GetFVF());
  //CORE->GetRenderManager()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, m_vTexturasABorrar, sizeof(TTEXTURE1_VERTEX));
  //CORE->GetRenderManager()->GetDevice()->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, g_index, D3DFMT_INDEX16, g_Textures4, sizeof(TTEXTURE1_VERTEX)); 

  //Usando memoria de video
  //CORE->GetRenderManager()->GetDevice()->SetStreamSource(0,vertexBuffer,0,sizeof(TTEXTURE1_VERTEX));
  //CORE->GetRenderManager()->GetDevice()->SetIndices(indexBuffer);
  //CORE->GetRenderManager()->GetDevice()->SetFVF(TTEXTURE1_VERTEX::GetFVF());
  //CORE->GetRenderManager()->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

  //-------------------3D RENDER---------------------
  //Draw Axis And Grid
  rm->DrawGrid(10);
  rm->DrawAxis(20);

  //rm->DrawSphere(0.5f, colYELLOW,10);
  //Mat44f t,r,r2,total;
  //t.SetIdentity();
  //r.SetIdentity();

  //t.Translate(Vect3f(1.f,0.f,0.f));

  //r.RotByAngleY(m_fRotacion);
  //r2.RotByAngleX(m_fRotacion);

  //total = r*t;		//gira orbitando a Y
  //total = t*r;		//rota sobre su propio eje
  //total = r*t*r;	//rotacion y traslacion sobre el eje Y y su propio eje

  /*if (m_bDrawCube)
  {
  rm->SetTransform(total);
  rm->DrawCube(1.f, colYELLOW );
  }*/

//  m_box->Render(CORE->GetRenderManager());

  CRenderableObjectsManager *renderObjectsManager = CORE->GetRenderableObjectsManager();
  renderObjectsManager->Render(rm);

  //-------------------2D RENDER---------------------
  //Hello world!
  CFontManager *  fm = CORE->GetFontManager();
  uint32 l_iFontId = fm->GetTTF_Id("arial");
  //fm->DrawLiteral(10,10,"HiWorld");
  //fm->DrawText((uint32)m_fPosX,(uint32)m_fPosY,colWHITE,l_iFontId,"Hello World!");

  fm->DrawText(10,55,colWHITE,l_iFontId,"Pitch: %f",m_pObject3D->GetPitch());
  fm->DrawText(10,80,colWHITE,l_iFontId,"Yaw: %f",m_pObject3D->GetYaw());
  fm->DrawText(10,95,colWHITE,l_iFontId,"Position: [%f,%f,%f]",m_pObject3D->GetPosition().x,m_pObject3D->GetPosition().y,m_pObject3D->GetPosition().z);

  //FPS
  l_iFontId = fm->GetTTF_Id("arial");
  fm->DrawText(10,40,colWHITE,l_iFontId,"Press 'ESC' to exit");

}


void	CGameProcess_t::RenderDebugInfo	(CRenderManager * rm, CFontManager* fm, float fps)
{
  CProcess::RenderDebugInfo(rm, fm, fps);
}



void CGameProcess_t::CheckActionsFromInputs(float elapsedTime)
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
    m_pObject3D->SetYaw( m_pObject3D->GetYaw() + delta * -0.01f );
  }

  //MoveZViewerCam
  if((delta = l_pCore->GetInputManager()->GetActionToInput()->DoAction("MoveZViewerCam")) != 0.0f )
  {
    CThPSCamera* cam = (CThPSCamera*) m_pCamera;
    cam->SetZoom( cam->GetZoom() + delta * -0.1f);
  }


  //YawViewerCam
  if((delta = CORE->GetInputManager()->GetActionToInput()->DoAction("YawViewerCam")) != 0.0f )
  {
    m_pObject3D->SetYaw( m_pObject3D->GetYaw() + delta*0.05f );
  }

  //PitchViewerCam
  if((delta = l_pCore->GetInputManager()->GetActionToInput()->DoAction("PitchViewerCam")) != 0.0f )
  {
    m_pObject3D->SetPitch( m_pObject3D->GetPitch() + delta*0.05f );
  }

  //ZoomViewerCam
  if((delta = l_pCore->GetInputManager()->GetActionToInput()->DoAction("ZoomViewerCam")) != 0.0f )
  {
    m_pObject3D->SetPitch( m_pObject3D->GetPitch() + delta*0.05f );
  }

  //SlowZoomViewerCam
  if((delta = l_pCore->GetInputManager()->GetActionToInput()->DoAction("SlowZoomViewerCam")) != 0.0f )
  {
    CActionToInput *i = CORE->GetInputManager()->GetActionToInput();
    i->Reload();
  }
}
