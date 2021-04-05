#include "ZombieRapido.h"
#include "XML\XMLTreeNode.h"

//----------------------------------------------------------------------------
// Init data
//----------------------------------------------------------------------------
bool 
//CZombieRapido::Init(CXMLTreeNode* _pTreeNode){// Gabriel
CZombieRapido::Init(const CXMLTreeNode &m){
	bool bIsOk = Inherited::Init(m);
	
  // Read all info

  if (!bIsOk){
		printf("a CZombieRapido instace couldnt allocate memory");
    Done();								//We call Done()  to release before the parent class
	}else{

    std::string szPath = m.GetPszProperty("paths");
    std::vector<float> v;
		for(int i=0;i<5;i++)v.push_back(0);
		sscanf_s((const char*)szPath.c_str(),"%f %f %f %f %f",&v[0],&v[1],&v[2],&v[3],&v[4]);
		
		m_Path							=		v;

	}

  return bIsOk;
}

//----------------------------------------------------------------------------
// Finalize data
//----------------------------------------------------------------------------
void
CZombieRapido::Done(){
	Inherited::Done();			//Parent class Done
  if (IsOk())
  {
    Release();
  }
}

//----------------------------------------------------------------------------
// Free memory
//----------------------------------------------------------------------------
void
CZombieRapido::Release(){
//free memory
}


//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
/*
CZombieRapido::CZombieRapido(CEnemy &e):CEnemy(e){

	vector<float> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(1);

	this->m_Path = v;

	this->Init();
}

CZombieRapido::CZombieRapido(CEnemy &e,vector<float> _hispath):CEnemy(e){
	this->m_Path = _hispath;

	this->Init();

}

*/