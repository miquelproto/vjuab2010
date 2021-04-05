//----------------------------------------------------------------------------------
// Class CZombieRapido
// Author: Miquel Rojas
//
// Description:
// Derives from CZombie and walk faster
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef CZOMBIERAPIDO_H_
#define CZOMBIERAPIDO_H_

// Includes
#include "../Zombie/Zombie.h"

//Class
class CXMLTreeNode;

class CZombieRapido:public CZombie{
public:
	CZombieRapido(){}

  virtual ~CZombieRapido() { Done(); }
	// Init and End protocols

	virtual	bool				Init												(const CXMLTreeNode &m);
	virtual void				Done               					();

  // -----------------------
  // Read functions
  // -----------------------

  // -----------------------
  // Write functions
  // -----------------------

	// member variables
  std::vector<float> m_Path;

private:
  void        				Release   					();


	// Types 
	//uncomment to derived classes
  typedef CZombie Inherited;
};


#endif