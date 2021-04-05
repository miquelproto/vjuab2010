//----------------------------------------------------------------------------------
// Class CZombieVomitador
// Author: Miquel Rojas
//
// Description:
// Derived from CZombie, he is moving and a rotation min and max he can to vomit
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef CZOMBIEVOMITADOR_H_
#define CZOMBIEVOMITADOR_H_

// Includes
#include "../Zombie/Zombie.h"
//Class


class CZombieVomitador:public CZombie
{
public:
	CZombieVomitador(){}
	// Init and End protocols
  
  virtual ~CZombieVomitador() { Done(); }

	virtual	bool				Init								(const CXMLTreeNode &m);
  virtual void				Done               	();

  // -----------------------
  // Read functions
  // -----------------------

  // -----------------------
  // Write functions
  // -----------------------

	// member variables
	Vector3<float> m_V3MinAngle;
	Vector3<float> m_V3MaxAngle;

private:
  void        				Release   					();


	// Types 
	//uncomment to derived classes
  typedef CZombie Inherited;
};
#endif