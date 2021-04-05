#include "Texture.h"
#include "RenderManager.h"

CTexture::~CTexture()
{
	Unload();
}
const std::string & CTexture::GetFileName() const
{
	return m_FileName;
}
bool CTexture::Load(const std::string &FileName)
{
	m_FileName = FileName;
	return LoadFile();
}
bool CTexture::Reload()
{
	Unload();
	return LoadFile();
}
void CTexture::Activate(size_t StageId)
{
	CORE->GetRenderManager()->GetDevice()->SetTexture(StageId, m_Texture);

}
bool CTexture::LoadFile()
{
	LPDIRECT3DDEVICE9 l_device = CORE->GetRenderManager()->GetDevice();
	return (D3DXCreateTextureFromFile(l_device, m_FileName.c_str(), &m_Texture)==D3D_OK);
}
void CTexture::Unload()
{
	CHECKED_RELEASE(m_Texture);
}