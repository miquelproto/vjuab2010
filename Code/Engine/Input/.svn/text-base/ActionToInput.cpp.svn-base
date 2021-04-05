#include "ActionToInput.h"
#include "Core.h"
#include "XML/XMLTreeNode.h"
#include "InputDefs.h"
#include "InputManager.h"
#include "../Graphics/FontManager/FontManager.h"
#include "LanguageManager/LanguageManager.h"
#include <stdio.h>



#if defined( _DEBUG )  
#include "Memory/MemLeaks.h" 
#endif

//----------------------------------------------------------------------------
// Init data
//----------------------------------------------------------------------------
bool 
CActionToInput::Init(){
  m_bIsOk = true;

  InitString2Input();
  
  if (!m_bIsOk){
    Release();
  }

  return m_bIsOk;
}

//----------------------------------------------------------------------------
// Finalize data
//----------------------------------------------------------------------------
void
CActionToInput::Done(){
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
CActionToInput::Release(){
//free memory
}

//----------------------------------------------------------------------------
// GET STRING PARAMETER
// Recorre las parejas nombre-codigo hasta dar la cadena que estamos
// buscando segun los parametros.
//----------------------------------------------------------------------------
void CActionToInput::
GetStringParameter(std::string& token_, signed int _paramAction, std::string _text, unsigned int _numCharsToCompare)
{
  std::vector<std::pair<std::string, uint32>>::iterator iter;
  iter = m_String2Code.begin();
  bool flag = false;

  while((iter != m_String2Code.end())&&(flag == false))
  {
    if(iter->second == _paramAction)    //compara las parejas para saber las que tienen el valor numerico correspondiente
    {
      if(!iter->first.compare(0,_numCharsToCompare, _text.c_str(), _numCharsToCompare))//decide que devolver segun el prefijo enviado
      {
        token_ += iter->first;    
        token_ += " ";
        flag = true;
      }
    }
    ++iter;
  } 
}

//----------------------------------------------------------------------------
// GET ACTION CONFIGURATION
// Devuelve los inputs de una accion pasada por parametro, p.ej."Screenshot"
// en forma de cadena preparada para imprimir.
//----------------------------------------------------------------------------
void CActionToInput::GetActionConfig(std::string &config_,  std::string _action)
{
  std::vector<std::pair<std::string, SInput>>::iterator iter;
  iter = m_vInputsPerAction.begin();
  SInput input;
  input.accion = 0; input.dispositivo = 0;input.valor = 0;input.deltaRaton=0.0f;

  std::string l_sConfig="";

  while (m_vInputsPerAction.end() != iter)
  {
    if(iter->first == _action)
    {
      input.accion = 0; input.dispositivo = 0;input.valor = 0;input.deltaRaton=0.0f;
      input = iter->second;
      GetInput(l_sConfig,input);
      l_sConfig += "+";
    }
    iter++;
  }
  config_ = l_sConfig;       //copia la cadena a la pasada por parametro que es la global
}

//----------------------------------------------------------------------------
// GET INPUT
// Recorre toda la estructura input para devolverla en forma de cadena
//----------------------------------------------------------------------------
void CActionToInput::GetInput(std::string& action_, SInput _input)
{
  std::string l_szToken = "";   
  GetStringParameter(l_szToken,_input.dispositivo,"IDV",3); //prefijo device
  if(_input.valor > -1)        //Se ha pulsado tecla o boton del raton por tanto hay un eventtype y no un axistype 
  {
    GetStringParameter(l_szToken,_input.accion,"EVENT",5); //prefijo evento
    if(_input.dispositivo == IDV_KEYBOARD)
    {
      GetStringParameter(l_szToken,_input.valor,"KEY",3); //prefijo tecla
    }
    else if(_input.dispositivo == IDV_MOUSE)
    {
      GetStringParameter(l_szToken,_input.accion,"MOUSE",5);  //prefijo boton raton
    }
  }
  else
  {
    GetStringParameter(l_szToken,_input.accion,"AXIS",4);   //prefijo eje del raton

    char aux[99];
    sprintf(aux,"%f",_input.deltaRaton);            //se añade el delta
    l_szToken += aux;
    l_szToken += " ";

  }
  action_ += l_szToken;       //se añade a la cadena global el input recogido.
}

//----------------------------------------------------------------------------
// GET VALUE
// Recorre las parejas nombre-codigo hasta dar el que estamos buscando segun
// los parametros. hace un find
//----------------------------------------------------------------------------
int CActionToInput::GetValue(std::string _lit)
{
  std::vector<std::pair<std::string, uint32>>::iterator iter;
  iter = m_String2Code.begin();

  int l_iVal = -1;

  while((iter != m_String2Code.end())&&(l_iVal == -1))
  {
    if(!_lit.compare(iter->first))
    {
      l_iVal = iter->second;    
    }
    ++iter;
  } 
  return l_iVal;
}

//----------------------------------------------------------------------------
// DO ACTION
// Se reconoce para cada accion pasada como cadena de texto si se ha pulsado 
// la combinacion correcta
//----------------------------------------------------------------------------
float CActionToInput::DoAction(std::string _myAction)
{
  //recorre las acciones
  TAction::iterator iterActions;               
  
  iterActions = m_vInputsPerAction.begin();
  float l_bInputActivo = 0.0f;//empieza positivo para detectar negativo y salir
  bool l_bEsperaInput = true;
  //bucle acciones
  while (iterActions != m_vInputsPerAction.end())
  {
    SInput l_SInput;
  
    l_SInput  = iterActions->second;

    //----------------INPUT_EVENT_TYPE-----------------//

    if((!(iterActions->first).compare(_myAction) )&&(l_bEsperaInput == true))
    {
    if(((l_SInput.dispositivo == IDV_KEYBOARD)||((l_SInput.dispositivo == IDV_MOUSE)))&&((iterActions->second).valor != -1))
    {
      l_bEsperaInput = false;

      switch(l_SInput.accion)
      {
        case   EVENT_DOWN:
          l_bInputActivo = (float) DEVINPUT->IsDown((INPUT_DEVICE_TYPE)l_SInput.dispositivo, l_SInput.valor);;
          if (l_bInputActivo != 0.f ) 
            l_bEsperaInput = true;
        break;
        case   EVENT_UP_DOWN:
          l_bInputActivo = (float) DEVINPUT->IsUpDown((INPUT_DEVICE_TYPE)l_SInput.dispositivo, l_SInput.valor);                
          if (l_bInputActivo != 0.f ) l_bEsperaInput = true;
        break;
        case   EVENT_DOWN_UP:
          l_bInputActivo = (float) DEVINPUT->IsDownUp((INPUT_DEVICE_TYPE)l_SInput.dispositivo, l_SInput.valor);
          if (l_bInputActivo != 0.f ) l_bEsperaInput = true;
        break;
        case   EVENT_NOTHING:
        break;
      }
    }


    if((l_SInput.dispositivo == IDV_MOUSE)&&(l_bEsperaInput == true))
      //----------------INPUT_AXIS_TYPE-----------------//
    {
      l_bEsperaInput = false;
      switch(l_SInput.accion)
      {
      case AXIS_MOUSE_X:
        l_bInputActivo = DEVINPUT->GetMouseDelta().x;         
        if (l_bInputActivo != 0.f ) 
          l_bEsperaInput = true;
      break;

      case AXIS_MOUSE_Y:
        l_bInputActivo = DEVINPUT->GetMouseDelta().y;         
        if (l_bInputActivo != 0.f ) l_bEsperaInput = true;
      break;
      case   AXIS_MOUSE_Z:
        l_bInputActivo = DEVINPUT->GetMouseDelta().z;         
        if (l_bInputActivo != 0.f ) l_bEsperaInput = true;
      break;
      case   AXIS_LEFT_THUMB_X:
  
        break;
      case   AXIS_LEFT_THUMB_Y:
        break;
      case   AXIS_RIGHT_THUMB_X:
        break;
      case   AXIS_RIGHT_THUMB_Y:
        break;
      case   AXIS_DELTA_TRIGGER_RIGHT:
        break;
      case   AXIS_DELTA_TRIGGER_LEFT:
        break;
      case   AXIS_NOTHING:
        break;
      }     

      }
    }  

    iterActions++;  
  }

  if(l_bEsperaInput)
    return l_bInputActivo; 
  else
    return 0.0f;
}

//----------------------------------------------------------------------------
// UPDATE
//----------------------------------------------------------------------------
void CActionToInput::Update()
{
}

//----------------------------------------------------------------------------
// LOAD
// Si encuentra el archivo de configuracion, la convierte a TreeNode y lo
// recorre para al final introducir cada input junto con su accion en un 
// vector, para luego tratarlo desde la clase.
//----------------------------------------------------------------------------
bool CActionToInput::Load(std::string _file)
{
  CXMLTreeNode l_XMLReadActions;

  if (!l_XMLReadActions.LoadFile(_file.c_str()))
  {
    printf("ERROR loading the file.");
    m_bIsOk = false;
  }
  else
  {
    m_filename = _file;
    
    CXMLTreeNode  act = l_XMLReadActions["Actions"];
    if (act.Exists())
    {
      std::string evt = "" , cod = "" , axs = "" , dlt = "";

      int32 numNodes = act.GetNumChildren();		
      for(int i=0; i < numNodes; i++)
      {
        if (!act(i).IsComment())
        {
          std::string l_szAction = (act(i).GetPszProperty("name"));
          CXMLTreeNode inputs = act(i)["action"];
          if (inputs.Exists())
          {
           int32 numNodesHijo = inputs.GetNumChildren();
           for(int j=0; j < numNodesHijo; j++)
           {
             std::string dev= inputs(j).GetPszProperty("deviceType");        
             if(dev == "IDV_KEYBOARD")
             {
               evt= inputs(j).GetPszProperty("EventType");        
               cod= inputs(j).GetPszProperty("Code");
               axs = "";
             }
             else if(dev == "IDV_MOUSE")
             {
               if(inputs(j).GetPszProperty("EventType")!= NULL) 
               {
                 evt= inputs(j).GetPszProperty("EventType");        
                 cod= inputs(j).GetPszProperty("Code");
                 axs = "";
               }
               if(inputs(j).GetPszProperty("AxisType")!= NULL) 
               {
                 axs= inputs(j).GetPszProperty("AxisType");        
                 dlt= inputs(j).GetPszProperty("Delta");
                 evt = "";
                 cod = "";
               }
             }
             else if(dev == "IDV_GAMEPAD")
             {

             }
             
             signed int l_iDev = GetValue(dev);
             signed int l_iAxi = GetValue(axs);
             float l_fValue = (float)atof(dlt.c_str());
             signed int l_iEvt = -1;
             signed int l_iCod = -1;
             if(l_iAxi == -1)
             {
               l_iEvt = GetValue(evt);
               l_iCod = GetValue(cod);
             }
             

             SInput input;
             input.dispositivo = l_iDev;
             if(l_iEvt != -1)//si hay evento
             {
                input.accion = l_iEvt;
                input.valor = l_iCod;
                input.deltaRaton = 0;
             }
             else
             {
               input.accion = l_iAxi;
               input.valor = -1;
               input.deltaRaton = l_fValue;
             }

             m_vInputsPerAction.push_back(std::pair<std::string, SInput>(l_szAction,input));
           }
         }
       }
     }  
   }
 } 
 return m_bIsOk;
}

//----------------------------------------------------------------------------
// GET STRING PARAMETER
// Recorre las parejas nombre-codigo hasta dar el que estamos buscando segun
// los parametros.
//----------------------------------------------------------------------------
bool CActionToInput::Reload ()
{
  if(Unload())
  {
    Load(m_filename);
    return true;
  }

  return false;
}

//----------------------------------------------------------------------------
// Unload
// Borra el vector de acciones con sus inputs
//----------------------------------------------------------------------------
bool CActionToInput::Unload ()
{
  std::vector<std::pair<std::string, SInput>>::iterator iter;
  iter = m_vInputsPerAction.begin();

  //for(;iter != m_vInputsPerAction.end(); ++iter)
  m_vInputsPerAction.erase(iter, m_vInputsPerAction.end());
  m_vInputsPerAction.clear();

  return true;
}

//----------------------------------------------------------------------------
// Save Actions
// Recorre las parejas nombre-codigo hasta dar el que estamos buscando segun
// los parametros.
//----------------------------------------------------------------------------
bool CActionToInput::SaveActions()
{
  return true;
}

//----------------------------------------------------------------------------
// INIT STRING TO INPUT
// Funcion proporcionada para ayudarnos a hacer el ejercicio.
// Mapea todos los dispositivos, acciones, botones, teclas, etc...
//----------------------------------------------------------------------------
void CActionToInput::InitString2Input ()
{
  typedef std::pair<std::string, uint32> PairString2Code;
  //typedef std::vector<std::pair<std::string, uint32>> VPairString2Code;
  std::vector<std::pair<std::string, uint32>>::iterator iter;
  //VPairString2Code::iter = m_String2Code.begin()ator iter = m_String2Code.begin();
  //iter = m_String2Code.begin();
  //----------------INPUT_DEVICE_TYPE---------------//
//  m_String2Code.insert()
  uint32 A= m_String2Code.max_size();
  uint32 B= m_String2Code.capacity();
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("IDV_KEYBOARD", IDV_KEYBOARD) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("IDV_MOUSE", IDV_MOUSE) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("IDV_GAMEPAD1", IDV_GAMEPAD1) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("IDV_GAMEPAD2", IDV_GAMEPAD2) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("IDV_GAMEPAD3", IDV_GAMEPAD3) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("IDV_GAMEPAD4", IDV_GAMEPAD4) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("IDV_NOTHING", IDV_NOTHING) );

  //----------------INPUT_AXIS_TYPE-----------------//
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("AXIS_MOUSE_X", AXIS_MOUSE_X) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("AXIS_MOUSE_Y", AXIS_MOUSE_Y) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("AXIS_MOUSE_Z", AXIS_MOUSE_Z) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("AXIS_LEFT_THUMB_X", AXIS_LEFT_THUMB_X) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("AXIS_LEFT_THUMB_Y", AXIS_LEFT_THUMB_Y) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("AXIS_RIGHT_THUMB_X", AXIS_RIGHT_THUMB_X) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("AXIS_RIGHT_THUMB_Y", AXIS_RIGHT_THUMB_Y) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("AXIS_DELTA_TRIGGER_RIGHT", AXIS_DELTA_TRIGGER_RIGHT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("AXIS_DELTA_TRIGGER_LEFT", AXIS_DELTA_TRIGGER_LEFT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("AXIS_NOTHING", AXIS_NOTHING) );

  //----------------INPUT_EVENT_TYPE-----------------//
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("EVENT_DOWN", EVENT_DOWN) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("EVENT_UP_DOWN", EVENT_UP_DOWN) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("EVENT_DOWN_UP", EVENT_DOWN_UP) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("EVENT_NOTHING", EVENT_NOTHING) );

  //----------------MOUSE_BUTTON---------------------//
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("MOUSE_BUTTON_LEFT", MOUSE_BUTTON_LEFT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("MOUSE_BUTTON_RIGHT", MOUSE_BUTTON_RIGHT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("MOUSE_BUTTON_MIDDLE", MOUSE_BUTTON_MIDDLE) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("MOUSE_BUTTON_MIDDLE", MOUSE_BUTTON_MIDDLE) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("MOUSE_BUTTON_NOTHING", MOUSE_BUTTON_NOTHING) );


  //----------------Gamepad codes from XInput.h------//
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_DPAD_UP", PAD_DPAD_UP) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_DPAD_DOWN", PAD_DPAD_DOWN) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_DPAD_LEFT", PAD_DPAD_LEFT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_DPAD_RIGHT", PAD_DPAD_RIGHT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_DPAD_START", PAD_DPAD_START) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_DPAD_BACK", PAD_DPAD_BACK) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_BUTTON_LEFT_THUMB", PAD_BUTTON_LEFT_THUMB) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_BUTTON_RIGHT_THUMB", PAD_BUTTON_RIGHT_THUMB) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_BUTTON_LEFT_SHOULDER", PAD_BUTTON_LEFT_SHOULDER) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_BUTTON_RIGHT_SHOULDER",PAD_BUTTON_RIGHT_SHOULDER) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_BUTTON_A", PAD_BUTTON_A) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_BUTTON_B", PAD_BUTTON_B) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_BUTTON_X", PAD_BUTTON_X) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("PAD_BUTTON_Y", PAD_BUTTON_Y) );

  //-----------Keyboard scan codes from dinput.h ------//
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_ESCAPE", KEY_ESCAPE) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_TAB", KEY_TAB) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_SPACE", KEY_SPACE) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_RETURN", KEY_RETURN) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_BACK", KEY_BACK) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_CAPITAL", KEY_CAPITAL) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_MINUS", KEY_MINUS) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_EQUALS", KEY_EQUALS) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_LBRACKET", KEY_LBRACKET) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_RBRACKET", KEY_RBRACKET) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_SEMICOLON", KEY_SEMICOLON) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_APOSTROPHE", KEY_APOSTROPHE) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_GRAVE", KEY_GRAVE) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_BACKSLASH", KEY_BACKSLASH) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_COMMA", KEY_COMMA) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_PERIOD", KEY_PERIOD) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_SLASH", KEY_SLASH) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_A", KEY_A) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_S", KEY_S) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_D", KEY_D) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F", KEY_F) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_G", KEY_G) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_H", KEY_H) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_J", KEY_J) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_K", KEY_K) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_L", KEY_L) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_X", KEY_X) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_C", KEY_C) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_B", KEY_B) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_N", KEY_N) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_M", KEY_M) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_Q", KEY_Q) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_W", KEY_W) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_E", KEY_E) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_R", KEY_R) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_T", KEY_T) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_Y", KEY_Y) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_U", KEY_U) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_I", KEY_I) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_O", KEY_O) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_P", KEY_P) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_1", KEY_1) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_2", KEY_2) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_3", KEY_3) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_4", KEY_4) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_5", KEY_5) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_6", KEY_6) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_7", KEY_7) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_8", KEY_8) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_9", KEY_9) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_0", KEY_0) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F1", KEY_F1) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F2", KEY_F2) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F3", KEY_F3) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F4", KEY_F4) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F5", KEY_F5) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F6", KEY_F6) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F7", KEY_F7) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F8", KEY_F8) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F9", KEY_F9) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F10", KEY_F10) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F11", KEY_F11) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_F12", KEY_F12) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NPPLUS", KEY_NPPLUS) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NPMINUS", KEY_NPMINUS) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NPDECIMAL", KEY_NPDECIMAL) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NPCOMMA", KEY_NPCOMMA) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NPDIVIDE", KEY_NPDIVIDE) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NPMULTIPLY", KEY_NPMULTIPLY) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NPENTER", KEY_NPENTER) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NUMLOCK", KEY_NUMLOCK) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NP1", KEY_NP1) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NP2", KEY_NP2) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NP3", KEY_NP3) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NP4", KEY_NP4) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NP5", KEY_NP5) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NP6", KEY_NP6) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NP7", KEY_NP7) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NP8", KEY_NP8) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NP9", KEY_NP9) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_NP0", KEY_NP0) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_RSHIFT", KEY_RSHIFT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_LSHIFT", KEY_LSHIFT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_RCTRL", KEY_RCTRL) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_LCTRL", KEY_LCTRL) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_RALT", KEY_RALT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_LALT", KEY_LALT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_LWIN", KEY_LWIN) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_RWIN", KEY_RWIN) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_UP", KEY_UP) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_DOWN", KEY_DOWN) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_LEFT", KEY_LEFT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_RIGHT", KEY_RIGHT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_INSERT", KEY_INSERT) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_DELETE", KEY_DELETE) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_HOME", KEY_HOME) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_END", KEY_END) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_PGDOWN", KEY_PGDOWN) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_PGUP", KEY_PGUP) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_PAUSE", KEY_PAUSE) );
  m_String2Code.insert( iter = m_String2Code.begin(), PairString2Code("KEY_SCROLL", KEY_SCROLL) );
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------