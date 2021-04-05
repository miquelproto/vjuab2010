#include "ZombieManager.h"
#include "XML/XMLTreeNode.h"
//#include "Math/Vector3.h"

#include "../ZombieResources/ZombieResources.h"
//#include "Zombie/Zombie.h"
#include "../ZombieRapido/ZombieRapido.h"
#include "../ZombieNormal/ZombieNormal.h"
#include "../ZombieVomitador/ZombieVomitador.h"

//----------------------------------------------------------------------------
// Init data
//----------------------------------------------------------------------------
bool
CZombieManager::Init(const char* file){
  m_bIsOk = true;

  if (!m_bIsOk){
    Release();
  }else
  {
    CXMLTreeNode newFile;

    if (!newFile.LoadFile(file))
    {
      printf("ERROR loading the file.");
      return false;
    }

    CXMLTreeNode  t = newFile["templates"];
    CXMLTreeNode  m = newFile["instances"];

    if (t.Exists())
    {

      int count = t.GetNumChildren();
      for (int i = 0; i < count; ++i)
      {
        const char* szId			=		t(i).GetPszProperty("id");																//read CEnemyResources properties 
        const char* szMesh		=		t(i).GetPszProperty("mesh");														

        if (m.Exists())
        {

          int count = m.GetNumChildren();
          for (int i = 0; i < count; ++i)
          {
            const char* szType	=	m(i).GetPszProperty("type");															//read CEnemy properties 

            if ((!strcmp(szId, szType))&&(!strcmp(szType, "ZOMBIE_NORMAL"))){ 						//read CZombieNormal properties 
              CZombieNormal *zombieNormal = new CZombieNormal();																//Exemple de Gabriel
              zombieNormal->Init(m(i));																									//Exemple de Gabriel
              zombieNormal->m_sMesh = szMesh;
              this->m_vecZombiesNormales.push_back(zombieNormal);

            }else if ((!strcmp(szId, szType))&&(!strcmp(szType, "ZOMBIE_RAPIDO"))){					//read CSniper properties 
              CZombieRapido *zombieRapido = new CZombieRapido();
              zombieRapido->Init(m(i));
              zombieRapido->m_sMesh = szMesh;
              this->m_vecZombiesRapidos.push_back(zombieRapido);

            }else if ((!strcmp(szId, szType))&&(!strcmp(szType, "ZOMBIE_VOMITADOR"))){				//read CTurret properties 
              CZombieVomitador *zombieVomitador = new CZombieVomitador();
              zombieVomitador->Init(m(i));
              zombieVomitador->m_sMesh = szMesh;
              this->m_vecZombiesVomitadores.push_back(zombieVomitador);

            }else if ((!strcmp(szId, szType))&&(!strcmp(szType, "CAMERA"))){

            }

          }

        }

      }

    }

    m_bIsOk = true;		//Init OK!
  }

  return m_bIsOk;
}

//----------------------------------------------------------------------------
// Finalize data
//----------------------------------------------------------------------------
void
CZombieManager::Done(){
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
CZombieManager::Release(){
  //free memory
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------