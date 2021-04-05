#include "TextureManager.h"

CTextureManager::CTextureManager()
{

}
CTextureManager::~CTextureManager()
{
	Destroy();
}

void CTextureManager::Reload()
{
	//for(TMapResource::iterator l_It=m_Resources.begin();l_It!=m_Resources.end();++l_It)
	TMapResource::iterator l_It=m_Resources.begin();
	while(l_It!=m_Resources.end())
	{
		l_It->second->Reload();
		++l_It;
	}
}