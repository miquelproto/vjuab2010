//----------------------------------------------------------------------------------
// CZombieManager Class
// Author: Miquel Rojas
//
// Description:
// Manages the zombies and hold them in vectors
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef CZOMBIEMANAGER_H
#define CZOMBIEMANAGER_H

//forward declarations
class CZombieRapido;
class CZombieNormal;
class CZombieVomitador;



// Includes
#include <string.h>
#include <vector>


//Class
class CZombieManager
{
public:
  // Init and End protocols
  CZombieManager() : m_bIsOk(false){}
  virtual ~CZombieManager() { Done(); }

  virtual bool				Init								(const char* file);
  virtual void				Done               	();
  //comment if is child
  bool								IsOk               	() const { return m_bIsOk; }

  std::vector<CZombieNormal*> m_vecZombiesNormales;
  std::vector<CZombieRapido*> m_vecZombiesRapidos;
  std::vector<CZombieVomitador*> m_vecZombiesVomitadores;

private:
  void        				Release   					();

  // member variables
  //comment if is child
  bool                m_bIsOk;          // Initialization boolean control

  // Types 
  //uncomment to derived classes
  //typedef CProcess Inherited;
};


#endif