#include "Engine.h"
#include "Process.h"
#include "RenderManager.h"
#include "Core.h"
#include "Logger/Logger.h"
#include "Timer/Timer.h"
#include "XML/XMLTreeNode.h"
#include "Exceptions/Exception.h"

#if defined( _DEBUG )
 #include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )

CEngine::~CEngine(void)
{
  CHECKED_DELETE(m_pProcess);
  CHECKED_DELETE(m_pCore);

	CLogger * p = LOGGER;
	CHECKED_DELETE(p);
}

void CEngine::Init(HWND hWnd)
{
	new CLogger(); //Creacion por primera vez del LOGGER

  m_pCore = new CCore();

  //le tenemos que pasar los parametros de inicio
  m_pCore->Init(m_ConfigParams, hWnd);
	
	m_pProcess->Init();
}

void CEngine::LoadConfig(const std::string & pathXML){
  //--- Carga del XML con los parametros de inicio ---
  //SInitParams l_params;
  CXMLTreeNode parser;

  if (parser.LoadFile(pathXML.c_str())) {
    CXMLTreeNode  p = parser["Parameters"];
    if (p.Exists())	{
      m_ConfigParams.m_bFullScreen    = p(0).GetBoolProperty("fullscreen", P_FULLSCREEN);
      m_ConfigParams.m_uWidthScreen   = p(0).GetIntProperty("widthscreen", P_WIDTHSCREEN);
      m_ConfigParams.m_uHeightScreen  = p(0).GetIntProperty("heightscreen", P_HEIGHTSCREEN);

      //string msg_info = "CEngine::Init->Se cargo con exito el campo del XML";
      //LOGGER->AddNewLog(ELL_INFORMATION, msg_info.c_str());
    }
    else {
      m_ConfigParams.m_bFullScreen    = P_FULLSCREEN;
      m_ConfigParams.m_uWidthScreen   = P_WIDTHSCREEN;
      m_ConfigParams.m_uHeightScreen  = P_HEIGHTSCREEN;
      
      //string msg_error = "CEngine::Init->Error al intentar leer el campo Parameters del archivo de configuracion";
      //LOGGER->AddNewLog(ELL_ERROR, msg_error.c_str());
    }
  }
  else { // si no pudo cargar el archivo XML
    m_ConfigParams.m_bFullScreen    = P_FULLSCREEN;
    m_ConfigParams.m_uWidthScreen   = P_WIDTHSCREEN;
    m_ConfigParams.m_uHeightScreen  = P_HEIGHTSCREEN;	  

    //string msg_error = "CEngine::Init->Error al intentar leer el archivo de configuracion: " + pathXML;
    //LOGGER->AddNewLog(ELL_ERROR, "CEngine::Init->Error al intentar leer el archivo de configuracion: %s", pathXML.c_str());
  }
  //-- END XML
}

void CEngine::Update() 
{
	m_Timer.Update();
	float elapsedTime = m_Timer.GetElapsedTime();
	m_pCore->Update(elapsedTime);
	m_pProcess->Update(elapsedTime);
}

void CEngine::Render() {
 	CRenderManager * rm = m_pCore->GetRenderManager();
	rm->BeginRendering();

	CCamera* camera = m_pProcess->GetCamera();
	rm->SetupMatrices(camera);
	{
		RenderScene(rm);
	}
	rm->EndRendering();
}


void CEngine::RenderScene (CRenderManager* rm)
{
	if(m_pProcess != NULL)
	{
		m_pProcess->Render(rm);

		float elapsedTime = m_Timer.GetElapsedTime();
		CFontManager* fm = m_pCore->GetFontManager();
		m_pProcess->RenderDebugInfo(rm, fm, elapsedTime);
	}
}

void CEngine::Release()
{
	CHECKED_DELETE(m_pCore);
	CLogger* logger = LOGGER;
	delete logger;
}