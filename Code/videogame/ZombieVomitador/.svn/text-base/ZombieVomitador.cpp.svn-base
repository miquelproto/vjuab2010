#include "ZombieVomitador.h"
#include "XML\XMLTreeNode.h"

//----------------------------------------------------------------------------
// Init data
//----------------------------------------------------------------------------
bool 
CZombieVomitador::Init(const CXMLTreeNode &m){
	bool bIsOk = Inherited::Init(m);

  if (!bIsOk){
		printf("a CZombieVomitador instace couldnt allocate memory");
    Done();								//We call Done()  to release before the parent class
	}else{
		m_V3MinAngle						=		m.GetVect3fProperty("min_angle", NULL);
		m_V3MaxAngle						=		m.GetVect3fProperty("max_angle", NULL);	
	}

  return bIsOk;
}

//----------------------------------------------------------------------------
// Finalize data
//----------------------------------------------------------------------------
void
CZombieVomitador::Done(){
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
CZombieVomitador::Release(){
//free memory
}	

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------
/*CZombieVomitador::CZombieVomitador(CEnemy &e):CEnemy (e){
	this->m_V3MinAngle(10,0,0);
	this->m_V3MaxAngle(170,0,0);
    

	this->Init();
}

CZombieVomitador::CZombieVomitador(CEnemy &e,Vector3<float> _min, Vector3<float> _max):CEnemy(e){
	this->m_V3MinAngle(_min.x,_min.y,_min.z);
	this->m_V3MaxAngle(_max.x,_max.y,_max.z);


	this->Init();
}
*/