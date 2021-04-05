//----------------------------------------------------------------------------------
// Class ZombieNormal
// Author: Miquel Rojas
//
// Description:
// Derived from CEnemy, only walk and attack
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef CZOMBIENORMAL_H_
#define CZOMBIENORMAL_H_

// Includes
#include "../Zombie/Zombie.h"
//Class


class CZombieNormal:public CZombie{
public:
	CZombieNormal(){}
  virtual ~CZombieNormal() { Done(); }
	// Init and End protocols

  virtual	bool				Init								(const CXMLTreeNode &m);
  virtual void				Done               	();

  // -----------------------
  // Read functions
  // -----------------------

  // -----------------------
  // Write functions
  // -----------------------


	// member variables
  unsigned int m_uiAimDistance;

private:
  void        				Release   					();


	// Types 
	//uncomment to derived classes
  typedef CZombie Inherited;
};

#endif