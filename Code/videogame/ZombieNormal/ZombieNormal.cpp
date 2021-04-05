#include "ZombieNormal.h"
#include "XML\XMLTreeNode.h"

//----------------------------------------------------------------------------
// Init data
//----------------------------------------------------------------------------
bool 
CZombieNormal::Init(const CXMLTreeNode &m){
	bool bIsOk = Inherited::Init(m);

  if (!bIsOk){
		printf("a CZombieNormal instace couldnt allocate memory");
    Done();								//We call Done()  to release before the parent class
	}else{
		this->m_uiAimDistance				=		m.GetIntProperty("aim_distance");
	}

  return bIsOk;
}

//----------------------------------------------------------------------------
// Finalize data
//----------------------------------------------------------------------------
void
CZombieNormal::Done(){
	Inherited::Done();			//Parent class Done
  bool l_bIsOk = true;
  if (l_bIsOk)
  {
    Release();
  }
}

//----------------------------------------------------------------------------
// Free memory
//----------------------------------------------------------------------------
void
CZombieNormal::Release(){
//free memory
}

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------
/*
CZombieNormal::CZombieNormal(CEnemy &e):CEnemy(e){
	m_uiAimDistance = 30;

  this->Init();
}

CZombieNormal::CZombieNormal(CEnemy &e,unsigned int d):CEnemy(e),m_uiAimDistance(d){

	this->Init();
}
*/