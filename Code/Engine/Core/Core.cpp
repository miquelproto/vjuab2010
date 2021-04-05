#include "Core.h"
#include "RenderManager.h"
#include "FontManager/FontManager.h"
#include "LanguageManager/LanguageManager.h"
#include "Timer/Timer.h"
#include "InputManager.h"
#include "ActionToInput.h"
#include "StaticMeshes/StaticMeshManager.h"
#include "RenderableObjects/MeshInstance.h"
#include "RenderableObjects/RenderableObjectsManager.h"
#include "AnimationModel/AnimatedModelManager.h"

#if defined( _DEBUG )
 #include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )

CCore::~CCore()
{
	CHECKED_DELETE(m_pRenderManager);
	CHECKED_DELETE(m_pFontManager);
	CHECKED_DELETE(m_pLanguageManager);
	CHECKED_DELETE(m_pInputManager);
  CHECKED_DELETE(m_pStaticMeshManager);

}


bool CCore::Init(SInitParams _params, HWND hWnd)
{
	bool m_bIsOk = true;
  bool z = _params.m_bFullScreen;
	//---Init del RenderManager---
	if (m_bIsOk)
	{
		m_pRenderManager = new CRenderManager();
		m_bIsOk = m_pRenderManager->Init(_params, hWnd);
	}
	//---Init del LanguageManager---
	if (m_bIsOk)
	{
		m_pLanguageManager = new CLanguageManager();
		/*TODO.. m_pLanguageManager->SetXmlFile("./Data/Language/spanish.xml");
		m_pLanguageManager->SetXmlFile("./Data/Language/english.xml");
		m_pLanguageManager->LoadXMLs();*/
	}
	//---Init del FontManager---
	if (m_bIsOk)
	{
		m_pFontManager = new CFontManager();
		m_bIsOk = m_pFontManager->Init(m_pRenderManager);
		m_pFontManager->LoadTTFs("./Data/Fonts/fonts.xml");
	}
	//---Init del Input---
	if (m_bIsOk)
	{
		//TODO //Input manager
		m_pInputManager = new CInputManager();
    m_bIsOk = m_pInputManager->Init(hWnd, Vect2i(_params.m_uHeightScreen, _params.m_uWidthScreen), false);
	}

  if(m_bIsOk)
  {
    m_pStaticMeshManager = new CStaticMeshManager();
    m_bIsOk = m_pStaticMeshManager->Load("./Data/StaticMeshManager.xml");
  }
  if(m_bIsOk)
  {
    //TODO...
    m_pRenderableObjectsManager = new CRenderableObjectsManager();
    if(!m_pRenderableObjectsManager->Load("./Data/RenderableObjects.xml"))
    {
      m_pRenderableObjectsManager = 0;
      m_bIsOk = false;
    }
  }
  if(m_bIsOk)
  {
//    m_pAnimatedModelManager = new CAnimatedCoreModel();
//    m_pAnimatedModelManager->Load("./Data/actor.xml");
  }
	
  return m_bIsOk;
}

void CCore::Update(float elapsedTime) 
{
	m_pInputManager->Update(); 
  CheckActionsFromInputs();
  if(m_pRenderableObjectsManager != 0){
    m_pRenderableObjectsManager->Update(elapsedTime);
  }
}

void CCore::Render() 
{
//  m_pRenderableObjectsManager->Render(m_pRenderManager);
}

void CCore::CheckActionsFromInputs()
{
  float delta = 0.0;
 
  //logger
  if(GetInputManager()->GetActionToInput()->DoAction("Logger") != 0.0f)
  {
    CLogger *l = LOGGER;
    const std::vector <SLog> &log =  l->GetLogs();
  }
  //console
  if(GetInputManager()->GetActionToInput()->DoAction("Console") != 0.0f)
  {
        //CLogger *l = LOGGER;
        //l->GetLogs();
  }

  //ScreenShot
  if(GetInputManager()->GetActionToInput()->DoAction("ScreenShot") != 0.0f)
  {
    //CLogger *l = LOGGER;
    //l->SaveLogsInFile();
  }

  //SaveLogsInFile
  if(GetInputManager()->GetActionToInput()->DoAction("SaveLogsInFile") != 0.0f)
  {
    CLogger *l = LOGGER;
    l->SaveLogsInFile();
  }

  //ReloadTTFs
  if(GetInputManager()->GetActionToInput()->DoAction("ReloadTTFs") != 0.0f )
  {
    CFontManager *fm = CORE->GetFontManager();
    fm->ReloadTTFs();
  }

  //ReloadLanguageXMLs
  if(GetInputManager()->GetActionToInput()->DoAction("ReloadLanguageXMLs") != 0.0f )
  {
    CLanguageManager *lm = CORE->GetLanguageManager();
    lm->LoadXMLs();
  }

  //ReloadActions
  if(GetInputManager()->GetActionToInput()->DoAction("ReloadActions") != 0.0f )
  {
    CActionToInput *i = CORE->GetInputManager()->GetActionToInput();
    i->Reload();
  }

  //LogRender_PageDown
  if(GetInputManager()->GetActionToInput()->DoAction("LogRender_PageDown") != 0.0f )
  {
    //    CActionToInput *i = CORE->GetInputManager()->GetActionToInput();
    //    i->Reload();
  }

  //LogRender_PageUp
  if(GetInputManager()->GetActionToInput()->DoAction("LogRender_PageUp") != 0.0f )
  {
        //CActionToInput *i = CORE->GetInputManager()->GetActionToInput();
        //i->Reload();
  }
  //LogRender_LogRender_PrevLine
  if(GetInputManager()->GetActionToInput()->DoAction("LogRender_LogRender_PrevLine") != 0.0f )
  {
    //    CActionToInput *i = CORE->GetInputManager()->GetActionToInput();
    //    i->Reload();
  }
  //LogRender_NextLine
  if(GetInputManager()->GetActionToInput()->DoAction("LogRender_NextLine") != 0.0f )
  {
    //    CActionToInput *i = CORE->GetInputManager()->GetActionToInput();
    //    i->Reload();
  }

}

