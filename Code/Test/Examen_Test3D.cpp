#include "Examen_Test3D.h"
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

CExamen_Test3D::CExamen_Test3D()
{
	m_fRotacion = 0.f;
};

void	CExamen_Test3D::Init ()
{
	//Configuramos la camara y creamos un objeto dummy para seterle a la camara.
	m_pObject3D = new CObject3D();
	uint32 w,h;
	CORE->GetRenderManager()->GetWandH(w,h);
	float aspectRatio = (float)w/h;
	//float zn, float zf, float fov, float aspect, CObject3D* object3D, float zoom);
	m_pCamera = new CThPSCamera(0.1f, 100.f, 45.0f * D3DX_PI / 180.0f, aspectRatio, m_pObject3D, 10.f);
}

CExamen_Test3D::~CExamen_Test3D()
{
	CHECKED_DELETE(m_pCamera);
	CHECKED_DELETE(m_pObject3D);
}

void CExamen_Test3D::Update(float elapsedTime)
{
	//-----CONTROLADOR DE LA CÁMARA---------------------------
	Vect3i deltas = CORE->GetInputManager()->GetMouseDelta();
	m_pObject3D->SetYaw( m_pObject3D->GetYaw() + deltas.x*0.05f );
	m_pObject3D->SetPitch( m_pObject3D->GetPitch() + deltas.y*0.05f );

	CThPSCamera * cam = (CThPSCamera*) m_pCamera;
	cam->SetZoom( cam->GetZoom() + deltas.z * -0.1f);
	//------------------------------------------------------------
	m_fRotacion += elapsedTime;

	//Presione la tecla F1 para releer las fuentes
	if (CORE->GetInputManager()->IsDownUp(IDV_KEYBOARD, KEY_F1))
	{
		CORE->GetFontManager()->ReloadTTFs();
	}

}



void CExamen_Test3D::Render(CRenderManager * rm) 
{

	//-------------------3D RENDER---------------------
	//Draw Axis And Grid
	rm->DrawGrid(10);
	rm->DrawAxis(20);

	rm->DrawSphere(0.5f, colYELLOW,10);

	Mat44f t,r,r2,t2,total;
	t.SetIdentity();
	r.SetIdentity();
	r2.SetIdentity();
	t2.SetIdentity();

	t.Translate(Vect3f(6.f,0.f,0.f));

	r.RotByAngleY(m_fRotacion);
	r2.RotByAngleZ(m_fRotacion);

	total = r*t*(r/3);	//rotacion y traslacion sobre el eje Y y su propio eje

	rm->SetTransform(total);
	rm->DrawSphere(0.3f, colWHITE, 10);

  t.SetIdentity();
  r.SetIdentity();
  r2.SetIdentity();
  t2.SetIdentity();

  t2.Translate(Vect3f(0.f,3.f,0.f));

  rm->SetTransform(total);

  total = r*t*t2*(r/2);
  
  rm->DrawSphere(0.3f, colWHITE, 10);

	//-------------------2D RENDER---------------------
	// blabla...
	CFontManager *  fm = CORE->GetFontManager();
	uint32 l_iFontId = fm->GetTTF_Id("arial");
	fm->DrawText(10,25,colWHITE,l_iFontId,"Presione la tecla F1 para releer las fuentes");

}


void	CExamen_Test3D::RenderDebugInfo	(CRenderManager * rm, CFontManager* fm, float fps)
{
	CProcess::RenderDebugInfo(rm, fm, fps);
  //Asignacion de FPS a variable de renderizado.
}