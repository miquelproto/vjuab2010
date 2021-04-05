//----------------------------------------------------------------------------------
// ActionToInput Class
// Author: Miquel Rojas
//
// Description:
// Lectura y tratamiento de acciones realizadas por dispositivos de entrada.
//----------------------------------------------------------------------------------
#pragma once

#ifndef ACTIONTOINPUT_H_
#define ACTIONTOINPUT_H_

// Includes
#include "Base.h"
#include "MapManager/MapManager.h"
#include <vector>
#include <string>
#include <map>
//Class

typedef struct              //informacion almacenada por cada input del xml
{
  signed short dispositivo; //teclado, raton o gamepad
  signed short accion;//evento o axi
  signed short valor;//tecla
  float deltaRaton;
}SInput;


class CActionToInput
{
public:
  // Init and End protocols
  CActionToInput() : m_bIsOk(false),m_filename(""), m_vInputsPerAction(0){}
  virtual ~CActionToInput () { Done(); }

  virtual	bool				Init								();
  virtual void				Done               	();
  //comment if is child
  bool								IsOk               	() const { return m_bIsOk; }
  bool                Load                (std::string file);//carga el xml y lee/convierte acciones
  bool                Reload              ();             //libera y load
  bool                Unload              ();             //libera
  bool                SaveActions         ();             //graba la configuracion actual

  typedef std::vector<std::pair<std::string, SInput>> TAction;
  std::vector<std::pair<std::string, SInput>>
                      GetActions          ()       {return m_vInputsPerAction;}
  
  void                GetActionConfig     (std::string &config, std::string action);//devuelve la cadena con la configuracion de una accion
  void                Update              ();
  float               DoAction            (std::string _myAction);

private:
  void        				Release   					();
  void                InitString2Input    ();
  int                 GetValue            (std::string lit);//devuelve el valor del literal de m_String2Code
  void                GetInput            (std::string& a, SInput i);
  void                GetStringParameter  (std::string& token_, 
                                            signed int _paramAction, 
                                            std::string _text, 
                                            unsigned int _numCharsToCompare);
  

  std::vector<std::string> 
                      ReceiveActiveActions();

  void ExecuteActiveActions(std::vector<std::string> _act);
  
  // member variables
  std::vector<std::pair<std::string, uint32>>m_String2Code;

  std::string                                 m_filename;               //nombre del fichero
  
  //comment if is child
  std::vector<std::pair<std::string, SInput>>m_vInputsPerAction;

  bool                         m_bIsOk;          // Initialization boolean control

	// Types 
	//uncomment to derived classes
  //typedef CProcess Inherited;
};

#endif