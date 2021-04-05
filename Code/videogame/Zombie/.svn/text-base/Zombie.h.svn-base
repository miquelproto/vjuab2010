//----------------------------------------------------------------------------------
// Class CZombie
// Author: Miquel Rojas
//
// Description:
// Class Base with properties about enemies like his position, rotation, health,etc...
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef CZOMBIE_H_
#define CZOMBIE_H_

// Includes
#include <vector>
#include "Math\Vector3.h"
#include "..\ZombieResources\ZombieResources.h"

//Class
class CXMLTreeNode;

class CZombie
{
public:
  // Init and End protocols
	CZombie():m_bIsOk(false){}

	virtual ~CZombie() { Done(); }

	virtual	bool				Init								(const CXMLTreeNode &m);
  virtual void				Done               	();
  bool								IsOk               	() const { return m_bIsOk; }

  // -----------------------
  // Logic functions
  // -----------------------
	int DoDamage(unsigned int _damage);
	void MoveTo(Vector3<float> _mypos);

	//member variables
	Vector3<float> m_V3Pos;
  Vector3<float> m_V3Rot;
	float m_fMoveSpeed;
	float m_fRotSpeed;
	unsigned int m_uiHealth;
	std::string m_sMesh;

private:
  void        				Release   					();

  // member variables
  bool                m_bIsOk;          // Initialization boolean control

	// Types 
	//uncomment to derived classes
  //typedef CProcess Inherited;
};


#endif
