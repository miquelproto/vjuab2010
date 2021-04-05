#include "RenderManager.h"
#include "Exceptions\Exception.h"
#include "Math\Matrix44.h"
#include "Cameras\Camera.h"
#include "Math/MathUtils.h"
#include "Object3D/Object3D.h"
#include "StaticMeshes/StaticMeshManager.h"

#if defined( _DEBUG )
 #include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)
#define D3DFVF_CUSTOMVERTEX2 (D3DFVF_XYZ|D3DFVF_TEX1)
struct CUSTOMVERTEX
{
	float x, y, z;
	DWORD color;
	static unsigned int getFlags()
	{
		return D3DFVF_CUSTOMVERTEX;
	}
};
struct CUSTOMVERTEX2
{
	D3DXVECTOR3 pos;
	DWORD color;
	static unsigned int getFlags()
	{
		return D3DFVF_CUSTOMVERTEX;
	}
};



bool CRenderManager::Init(SInitParams _params, HWND hWnd)
{

	LOGGER->AddNewLog(ELL_INFORMATION, "RenderManager:: Inicializando la libreria Direct3D");
	//CLogger * logger = CLogger::GetSingletonPtr();
	

	// Create the D3D object.
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	
	m_bIsOk = m_pD3D != NULL;

	if (m_bIsOk) {
		// Set up the structure used to create the D3DDevice
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory( &d3dpp, sizeof(d3dpp) );

		if(_params.m_bFullScreen) {
      d3dpp.Windowed          = FALSE;
			d3dpp.BackBufferWidth   = _params.m_uWidthScreen;
			d3dpp.BackBufferHeight  = _params.m_uHeightScreen;
      d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		}
		else
		{
			d3dpp.Windowed          = TRUE;
      d3dpp.BackBufferFormat	= D3DFMT_UNKNOWN;
		}

		d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
		d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;
		d3dpp.EnableAutoDepthStencil	= TRUE;
		d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;
		d3dpp.Flags						= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
		d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

		// Create the D3DDevice
		m_bIsOk = !FAILED(	m_pD3D->CreateDevice(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
												D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice ) );

		if (!m_bIsOk)
		{
			m_bIsOk = !FAILED(	m_pD3D->CreateDevice(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
													D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice ) );

			if (m_bIsOk)
			{
				LOGGER->AddNewLog(ELL_INFORMATION, "RenderManager:: D3DCREATE_SOFTWARE_VERTEXPROCESSING");
			}
		}
		else
		{
			LOGGER->AddNewLog(ELL_INFORMATION, "RenderManager:: D3DCREATE_HARDWARE_VERTEXPROCESSING");
		}

		if (m_bIsOk) {
			// Turn off culling, so we see the front and back of the triangle
			m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			m_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
			m_pD3DDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			m_pD3DDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			m_pD3DDevice->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

			m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
			m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
			m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
			m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );


			m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW);
			m_pD3DDevice->SetRenderState( D3DRS_ZENABLE,D3DZB_TRUE);
			m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);

			// Turn off D3D lighting, since we are providing our own vertex colors
			m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

		
			if(_params.m_bFullScreen) {
				m_uWidth	= _params.m_uWidthScreen;
        m_uHeight	= _params.m_uHeightScreen;
			}
			else {
				GetWindowRect(hWnd);
			}
			LOGGER->AddNewLog(ELL_INFORMATION, "RenderManager:: La resolucion de pantalla es (%dx%d)",m_uWidth,m_uHeight);			
		}
	}

  if(m_bIsOk)
  {
    CStaticMeshManager *sm = new CStaticMeshManager();
    sm->Load("./Data/StaticMeshManager.xml");
  }

	if (!m_bIsOk) {
		std::string msg_error = "Rendermanager::Init-> Error al inicializar Direct3D";
		LOGGER->AddNewLog(ELL_ERROR, msg_error.c_str());
		Relase();
		throw CException(__FILE__, __LINE__, msg_error);
	}
	
	return m_bIsOk;
}


void CRenderManager::GetWindowRect( HWND hwnd )
{
	RECT rec_window;
	GetClientRect(	hwnd, &rec_window);
	m_uWidth	= rec_window.right - rec_window.left;
	m_uHeight = rec_window.bottom - rec_window.top;
}


void CRenderManager::Relase(void)
{
	//Relase main devices of render
	CHECKED_RELEASE(m_pD3DDevice);
	CHECKED_RELEASE(m_pD3D);
}


// RENDERING STUFF:
void CRenderManager::BeginRendering ()
{

#ifdef _DEBUG // Clear the backbuffer to a blue color in a Debug mode
  //uint32 red		= (uint32) (0.f * 255);
  //uint32 green	= (uint32) (0.f * 255);
  //uint32 blue		= (uint32) (1.f * 255);

  //Light Green
  uint32 red		= (uint32) (1.f * 60);
  uint32 green	= (uint32) (1.f * 250);
  uint32 blue		= (uint32) (1.f * 10);
	m_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(red, green, blue), 1.0f, 0 );
#else // Clear the backbuffer to a black color in a Release mode
	uint32 red		= (uint32) (0.f * 255);
	uint32 green	= (uint32) (0.f * 255);
	uint32 blue		= (uint32) (0.f * 255);
	m_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(red, green, blue), 1.0f, 0 );
#endif


	// Begin the scene
	HRESULT hr = m_pD3DDevice->BeginScene();
	assert( SUCCEEDED( hr ) );
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE,D3DZB_TRUE);
	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE );

	//if(m_bPaintSolid)
	if(true)
	{
		m_pD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID  );
	}
	else
	{
		m_pD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME  );
	}
}

void CRenderManager::EndRendering    ()
{
	m_pD3DDevice->EndScene();
	// Present the backbuffer contents to the display
	m_pD3DDevice->Present( NULL, NULL, NULL, NULL );
}

void CRenderManager::SetupMatrices(CCamera* camera)
{
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProject;

	if(!camera)
	{
		//Set default view and projection matrix

		//Setup Matrix view
		D3DXVECTOR3 l_Eye(0.0f,5.0f,-5.0f), l_LookAt(0.0f,0.0f,0.0f), l_VUP(0.0f,1.0f,0.0f);
		D3DXMatrixLookAtLH( &m_matView, &l_Eye, &l_LookAt, &l_VUP);

		//Setup Matrix projection
		D3DXMatrixPerspectiveFovLH( &m_matProject, 45.0f * D3DX_PI / 180.0f, 1.0f, 1.0f, 100.0f );
	}
	else
	{
		Vect3f eye = camera->GetEye();
		D3DXVECTOR3 l_Eye(eye.x, eye.y, eye.z);
		Vect3f lookat = camera->GetLookAt();
		D3DXVECTOR3 l_LookAt(lookat.x, lookat.y, lookat.z);
		Vect3f vup = camera->GetVecUp();
		D3DXVECTOR3 l_VUP(vup.x, vup.y, vup.z);
		//Setup Matrix view
		D3DXMatrixLookAtLH( &m_matView, &l_Eye, &l_LookAt, &l_VUP);

		//Setup Matrix projection
		D3DXMatrixPerspectiveFovLH(	&m_matProject, camera->GetFov(), camera->GetAspectRatio(),
			camera->GetZn(), camera->GetZf());
	}
	//m_Frustum.Update( m_matView * m_matProject );
	m_pD3DDevice->SetTransform( D3DTS_VIEW, &m_matView );
	m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &m_matProject );
}

void CRenderManager::DrawLine ( const Vect3f &PosA, const Vect3f &PosB, CColor Color)
{
	DWORD color_aux = Color.GetUint32Argb();

	CUSTOMVERTEX v[2] =
	{
		{PosA.x, PosA.y, PosA.z, color_aux},
		{PosB.x, PosB.y, PosB.z, color_aux},
	};

	m_pD3DDevice->SetTexture(0,NULL);
	m_pD3DDevice->SetFVF(CUSTOMVERTEX::getFlags());
	m_pD3DDevice->DrawPrimitiveUP( D3DPT_LINELIST,1, v,sizeof(CUSTOMVERTEX));
}

void CRenderManager::DrawCube (float Size, CColor color)
{
	//suelo
	DrawLine(Vect3f(-Size*0.5f,-Size*0.5f,-Size*0.5f),    Vect3f(Size*0.5f,-Size*0.5f,-Size*0.5f),        color);
	DrawLine(Vect3f(-Size*0.5f,-Size*0.5f,Size*0.5f),    Vect3f(Size*0.5f,-Size*0.5f,Size*0.5f),        color);
	DrawLine(Vect3f(-Size*0.5f,-Size*0.5f,-Size*0.5f),    Vect3f(-Size*0.5f,-Size*0.5f,Size*0.5f),        color);
	DrawLine(Vect3f(Size*0.5f,-Size*0.5f,-Size*0.5f),    Vect3f(Size*0.5f,-Size*0.5f,Size*0.5f),        color);

	//tapa
	DrawLine(Vect3f(-Size*0.5f,Size*0.5f,-Size*0.5f),    Vect3f(Size*0.5f,Size*0.5f,-Size*0.5f),        color);
	DrawLine(Vect3f(-Size*0.5f,Size*0.5f,Size*0.5f),        Vect3f(Size*0.5f,Size*0.5f,Size*0.5f),        color);
	DrawLine(Vect3f(-Size*0.5f,Size*0.5f,-Size*0.5f),    Vect3f(-Size*0.5f,Size*0.5f,Size*0.5f),        color);
	DrawLine(Vect3f(Size*0.5f,Size*0.5f,-Size*0.5f),        Vect3f(Size*0.5f,Size*0.5f,Size*0.5f),        color);

	//lineas laterales
	DrawLine(Vect3f(-Size*0.5f,-Size*0.5f,-Size*0.5f),    Vect3f(-Size*0.5f,Size*0.5f,-Size*0.5f),        color);
	DrawLine(Vect3f(-Size*0.5f,-Size*0.5f,Size*0.5f),    Vect3f(-Size*0.5f,Size*0.5f,Size*0.5f),        color);
	DrawLine(Vect3f(Size*0.5f,-Size*0.5f,-Size*0.5f),    Vect3f(Size*0.5f,Size*0.5f,-Size*0.5f),        color);
	DrawLine(Vect3f(Size*0.5f,-Size*0.5f,Size*0.5f),        Vect3f(Size*0.5f,Size*0.5f,Size*0.5f),        color);
}


void CRenderManager::DrawCamera (CCamera* camera)
{

	D3DXMATRIX matrix;
	D3DXMATRIX translation;
	if (camera->GetTypeCamera() == CCamera::TC_THPS)
	{
		Vect3f camera_CenterPos = camera->GetObject3D()->GetPosition();
		D3DXMatrixTranslation( &translation, camera_CenterPos.x ,camera_CenterPos.y ,camera_CenterPos.z );
		m_pD3DDevice->SetTransform( D3DTS_WORLD, &translation );

		DrawCube(0.5f,colCYAN);
		D3DXMatrixTranslation( &matrix, 0, 0, 0 );
		m_pD3DDevice->SetTransform( D3DTS_WORLD, &matrix );
	}

	//---------PINTAMOS EL FRUSTUM-------------//
	D3DXMATRIX translation2;
	Vect3f eye_aux = camera->GetEye();
	D3DXVECTOR3 eye(eye_aux.x, eye_aux.y, eye_aux.z);
	D3DXMatrixTranslation( &translation, eye.x ,eye.y ,eye.z );

	D3DXMATRIX rotation;
	D3DXMATRIX rotation2;

	float yaw = camera->GetObject3D()->GetYaw();
	float pitch = camera->GetObject3D()->GetPitch();
	D3DXMatrixRotationY ( &rotation,  -yaw);
	D3DXMatrixRotationZ ( &rotation2, +pitch);

	matrix = rotation2 * rotation * translation; ;

	// Cambiar el sistema de coordenadas
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &matrix );
	
	CUSTOMVERTEX2 pts[9];

	float fov = camera->GetFov();
	float aspect = camera->GetAspectRatio();
	float d = camera->GetViewD();
	float zNear = camera->GetZn();
	float zFar = camera->GetZf();



	float h_near = zNear * tan ( fov * 0.5f );
	float k_near = h_near * aspect;

	float h_far = d * tan ( fov * 0.5f );
	float k_far = h_far * aspect;

	pts[ 0 ].pos = D3DXVECTOR3( 0, 0,0 );
	pts[ 0 ].color = 0xffffffff;

	pts[ 1 ].pos = D3DXVECTOR3( d, h_far, k_far );
	pts[ 1 ].color = 0xffffffff;
	pts[ 2 ].pos = D3DXVECTOR3( d, h_far, -k_far );
	pts[ 2 ].color = 0xffffffff;
	pts[ 3 ].pos = D3DXVECTOR3( d,-h_far, -k_far );
	pts[ 3 ].color = 0xffffffff;
	pts[ 4 ].pos = D3DXVECTOR3( d, -h_far, k_far );
	pts[ 4 ].color = 0xffffffff;

	pts[ 5 ].pos = D3DXVECTOR3( zNear, h_near, k_near );
	pts[ 5 ].color = 0xffffffff;
	pts[ 6 ].pos = D3DXVECTOR3( zNear, h_near, -k_near );
	pts[ 6 ].color = 0xffffffff;
	pts[ 7 ].pos = D3DXVECTOR3( zNear,-h_near, -k_near );
	pts[ 7 ].color = 0xffffffff;
	pts[ 8 ].pos = D3DXVECTOR3( zNear, -h_near, k_near );
	pts[ 8 ].color = 0xffffffff;

	// Decimos el tipo de vertice que vamos a proporcionar...
	m_pD3DDevice->SetFVF( CUSTOMVERTEX2::getFlags() );

	// Desactivar la textura
	m_pD3DDevice->SetTexture (0, NULL);

	m_pD3DDevice->DrawPrimitiveUP( D3DPT_POINTLIST, 9, pts, sizeof( CUSTOMVERTEX2 ) );
	static short int indexes[] =  {
		0,1, 0,2, 0,3, 0,4,
		1,2, 2,3, 3,4, 4,1,
		5,6, 6,7, 7,8, 8,5
	};
	m_pD3DDevice->DrawIndexedPrimitiveUP( D3DPT_LINELIST, 0, 9, 12, indexes, D3DFMT_INDEX16, pts, sizeof( CUSTOMVERTEX2 ) );

	D3DXMatrixTranslation( &matrix, 0, 0, 0 );
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &matrix );



	//---------PINTAMOS LA BOX Y LOS EJES------------------//
	D3DXMatrixTranslation( &translation2, -1.0f, 0.0f, 0.0f );
	matrix = translation2 * rotation2 * rotation * translation; 
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &matrix );

	CUSTOMVERTEX v[6] =
	{
		//EJE X
		{0, 0, 0, 0xffff0000},
		{3, 0, 0, 0xffff0000},
		//EJE Y
		{0, 0, 0, 0xff00ff00},
		{0, 3, 0, 0xff00ff00},
		//EJE Z
		{0, 0, 0, 0xff0000ff},
		{0, 0, 3, 0xff0000ff},
	};

	m_pD3DDevice->SetTexture(0,NULL);
	m_pD3DDevice->SetFVF(CUSTOMVERTEX::getFlags());
	m_pD3DDevice->DrawPrimitiveUP( D3DPT_LINELIST, 3, v,sizeof(CUSTOMVERTEX));

	DrawCube(0.5f, colWHITE);

	D3DXMatrixTranslation( &matrix, 0, 0, 0 );
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &matrix );
}

void CRenderManager::SetTransform(D3DXMATRIX& matrix)
{
  m_pD3DDevice->SetTransform(D3DTS_WORLD, &matrix);
}

void CRenderManager::SetTransform(Mat44f& m)
{
	D3DXMATRIX aux(m.m00,m.m10,m.m20,m.m30,m.m01,m.m11,m.m21,m.m31,m.m02,m.m12,m.m22,m.m32,m.m03,m.m13,m.m23,m.m33);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &aux);
}

void CRenderManager::DrawSphere( float Radius, const CColor& Color, int Aristas)
{
	for(int t=0;t<Aristas;++t)
	{
		float l_RadiusRing=Radius*sin(mathUtils::Deg2Rad(180.0f*((float)t))/((float)Aristas));
		for(int b=0;b<Aristas;++b)
		{
			Vect3f l_PosA(	l_RadiusRing*cos(mathUtils::Deg2Rad((float)(360.0f*(float)b)/((float)Aristas))),
											Radius*cos(mathUtils::Deg2Rad((180.0f*((float)t))/((float)Aristas))),
											l_RadiusRing*sin(mathUtils::Deg2Rad(((float)(360.0f*(float)b)/((float)Aristas)))));

			Vect3f l_PosB(	l_RadiusRing*cos(mathUtils::Deg2Rad((float)(360.0f*(float)(b+1))/((float)Aristas))),
											Radius*cos(mathUtils::Deg2Rad((180.0f*((float)t))/((float)Aristas))),
											l_RadiusRing*sin(mathUtils::Deg2Rad(((float)(360.0f*(float)(b+1))/((float)Aristas)))));

			DrawLine(l_PosA,l_PosB,Color);
			
			float l_RadiusNextRing=Radius*sin(mathUtils::Deg2Rad(180.0f*((float)(t+1)))/((float)Aristas));
			
			Vect3f l_PosC(	l_RadiusRing*cos(mathUtils::Deg2Rad((float)(360.0f*(float)b)/((float)Aristas))),
											Radius*cos(mathUtils::Deg2Rad((180.0f*((float)t))/((float)Aristas))),
											l_RadiusRing*sin(mathUtils::Deg2Rad(((float)(360.0f*(float)b)/((float)Aristas)))));
			Vect3f l_PosD(	l_RadiusNextRing*cos(mathUtils::Deg2Rad((float)(360.0f*(float)b)/((float)Aristas))),
											Radius*cos(mathUtils::Deg2Rad((180.0f*((float)(t+1)))/((float)Aristas))),
											l_RadiusNextRing*sin(mathUtils::Deg2Rad(((float)(360.0f*(float)b)/((float)Aristas)))));
			DrawLine(l_PosC,l_PosD,Color);
		}
	}
}

void CRenderManager::DrawGrid (float Size, CColor Color, int GridX, int32 GridZ )
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matrix);		

	//GRID
	//LINEAS EN Z
	//....
	for(int i = (int)(-1*GridZ); i <= (int)(GridZ); i++){
		DrawLine(Vect3f((float)i,0,(-1*Size)),Vect3f((float)i,0,Size), Color);
	}
	//LINEAS EN X
	//....
	for(int i = (int)(-1*GridX); i <= (int)(GridX); i++){
		DrawLine(Vect3f((-1*Size),0,(float)i),Vect3f(Size,0,(float)i), Color);
	}
}

void CRenderManager::DrawAxis (float Size)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matrix);

	DrawLine(Vect3f(0.0f,0.01f,0.0f),Vect3f(Size,0.01f,0.0f),colRED);
	//DrawLine(Vect3f(0.0f,0.0f,0.0f), Vect3f(0.0f,Size,0.0f),colGREEN);
  DrawLine(Vect3f(0.0f,0.0f,0.0f), Vect3f(0.0f,Size,0.0f),colYELLOW);
	DrawLine(Vect3f(0.0f,0.01f,0.0f),Vect3f(0.0f,0.01f,Size),colBLUE);
}