#include "CClass.h"

//----------------------------------------------------------------------------
// Init data
//----------------------------------------------------------------------------
bool 
CProcess::Init(){
	m_bIsOk = Inherited::Init();

  if (!m_bIsOk){
    Done();								//We call Done()  to release before the parent class
  }

  return m_bIsOk;
}

//----------------------------------------------------------------------------
// Finalize data
//----------------------------------------------------------------------------
void
CProcess::Done(){
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
CProcess::Release(){
//free memory
}


void
CVideogameProcess::Update(){

}
void 
CVideogameProcess::Render(){


}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------