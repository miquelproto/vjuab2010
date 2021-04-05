#include "Process.h"
#include "Core.h"
#include "InputManager.h"
#include "ActionToInput.h"
#include "FontManager/FontManager.h"
#include "Cameras/Camera.h"
#include "Object3D/Object3D.h"

#if defined( _DEBUG )
 #include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )

void CProcess::Init()
{
  
}

void CProcess::Update(float elapsedTime) 
{
}
void CProcess::Render(CRenderManager * rm)
{

}
void CProcess::RenderDebugInfo	(CRenderManager * rm, CFontManager* fm, float fps)
{
  uint32 tmp = fm->GetTTF_Id("arial");
  fm->DrawText(10,10,colWHITE,tmp,"%f",fps);
}
