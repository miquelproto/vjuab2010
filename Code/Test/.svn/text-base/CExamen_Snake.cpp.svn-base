#include "CExamen_Snake.h"
#include "Core.h"
#include "RenderManager.h"
#include "FontManager/FontManager.h"
#include "Timer/Timer.h"
#include "Math/Matrix44.h"
#include "Cameras/FPSCamera.h"
#include "Cameras/ThPSCamera.h"
#include "Object3D/Object3D.h"

#if defined( _DEBUG )
 #include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )

void	CExamen_Snake::Init ()
{
	//Configuramos la camara y creamos un objeto dummy para seterle a la camara.
	m_pObject3D = new CObject3D();
	uint32 w,h;
	CORE->GetRenderManager()->GetWandH(w,h);
	float aspectRatio = (float)w/h;
	//float zn, float zf, float fov, float aspect, CObject3D* object3D, float zoom);
	m_pCamera = new CThPSCamera(0.1f, 100.f, 45.0f * D3DX_PI / 180.0f, aspectRatio, m_pObject3D, 10.f);
}

CExamen_Snake::~CExamen_Snake()
{
	CHECKED_DELETE(m_pCamera);
	CHECKED_DELETE(m_pObject3D);
}

void CExamen_Snake::Update(float elapsedTime)
{
	//-----CONTROLADOR DE LA CÁMARA---------------------------
	//Vect3i deltas = CORE->GetInputManager()->GetMouseDelta();
	//m_pObject3D->SetYaw( m_pObject3D->GetYaw() + deltas.x*0.05f );
	//m_pObject3D->SetPitch( m_pObject3D->GetPitch() + deltas.y*0.05f );
	//CThPSCamera * cam = (CThPSCamera*) m_pCamera;
	//cam->SetZoom( cam->GetZoom() + deltas.z * -0.1f);
	//------------------------------------------------------------

	if(m_iDir == 0){//Vaya a la derecha
		m_fPosX += elapsedTime*50;
	}
	if(m_iDir == 1){//Vaya hacia abajo
		m_fPosY += elapsedTime*50;
	}
	if(m_iDir == 2){//Vaya a la izquierda
		m_fPosX += elapsedTime*-50;
	}
	if(m_iDir == 3){//Vaya hacia arriba
		m_fPosY += elapsedTime*-50;
	}

	//Cambio de direccion del snake
	if (CORE->GetInputManager()->IsDownUp(IDV_KEYBOARD, KEY_RIGHT))
	{
		m_iDir = 0;
	}
	if (CORE->GetInputManager()->IsDownUp(IDV_KEYBOARD, KEY_DOWN))
	{
		m_iDir = 1;
	}
	if (CORE->GetInputManager()->IsDownUp(IDV_KEYBOARD, KEY_LEFT))
	{
		m_iDir = 2;
	}
	if (CORE->GetInputManager()->IsDownUp(IDV_KEYBOARD, KEY_UP))
	{
		m_iDir = 3;
	}
	if(m_fPosX < 0){
		m_bLose = true;
	}
	if(m_fPosY < 0){
		m_bLose = true;
	}
	if(m_fPosY > 800){
		m_bLose = true;
	}
	if(m_fPosY > 600){
		m_bLose = true;
	}
	if(m_bLose){
		m_fPosX = 0;
		m_fPosY = 0;
	}
	if(!m_bLose){
		m_Time += elapsedTime;
		if(m_Time > 60.0f){
			m_Speed = m_Speed*2;
		}
	}
}



void CExamen_Snake::Render(CRenderManager * rm) 
{

	//-------------------3D RENDER---------------------
	//Draw Axis And Grid
	//rm->DrawGrid(10);
	//rm->DrawAxis(20);

	//rm->DrawSphere(0.5f, colYELLOW,10);

	//Mat44f t,r,r2,total;
	//t.SetIdentity();
	//r.SetIdentity();
	//r2.SetIdentity();
	
	//t.Translate(Vect3f(6.f,0.f,0.f));

	//r.RotByAngleY(m_fRotacion);
	//r2.RotByAngleZ(m_fRotacion);
	//total = r*t*(r/3);	//rotacion y traslacion sobre el eje Y y su propio eje

	//rm->SetTransform(total);
	//rm->DrawSphere(0.3f, colWHITE, 10);


	//-------------------2D RENDER---------------------
	// blabla...
	CFontManager *  fm = CORE->GetFontManager();
	uint32 l_iFontId = fm->GetTTF_Id("arial");
	fm->DrawText((uint32)m_fPosX,(uint32)m_fPosY,colWHITE,l_iFontId,"X");
	fm->DrawText(0,500,colWHITE,l_iFontId,"Time: %f",m_Time);

	if(m_bLose){
		fm->DrawText(200,200,colWHITE,l_iFontId,"GAME OVER");
	}
}


void	CExamen_Snake::RenderDebugInfo	(CRenderManager * rm, CFontManager* fm, float fps)
{
	//CProcess::RenderDebugInfo(rm, fm, fps);
  //Asignacion de FPS a variable de renderizado.
}