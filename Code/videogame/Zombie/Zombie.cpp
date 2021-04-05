#include "Zombie.h"
#include "XML\XMLTreeNode.h"

//----------------------------------------------------------------------------
// Init data
//----------------------------------------------------------------------------
bool 
CZombie::Init(const CXMLTreeNode &m ){
  m_bIsOk = true;
  if (!m_bIsOk){
		printf("a CCZombie instace couldnt allocate memory");
		Release();
	}else{
		m_V3Pos 						=		m.GetVect3fProperty("pos",NULL);
		m_V3Rot							=		m.GetVect3fProperty("rot",NULL);
		m_fMoveSpeed				=		m.GetFloatProperty("move_speed");
		m_fRotSpeed					=		m.GetFloatProperty("rotate_speed");
		m_uiHealth					=		m.GetIntProperty("health");	
	}

  return m_bIsOk;
}

//----------------------------------------------------------------------------
// Finalize data
//----------------------------------------------------------------------------
void
CZombie::Done(){
  if (IsOk())
  {
    Release();
    m_bIsOk = false;
  }
}

//----------------------------------------------------------------------------
// Free memory
//----------------------------------------------------------------------------
void
CZombie::Release(){
//free memory
}

//----------------------------------------------------------------------------
// Read Functions
//----------------------------------------------------------------------------
int
CZombie::DoDamage(unsigned int _damage){
	return (m_uiHealth - _damage);
}

