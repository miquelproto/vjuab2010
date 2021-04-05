//----------------------------------------------------------------------------------
// CTexture class
// Author: Marco Torres
//
// Description:
// Texture (Derivada)
//----------------------------------------------------------------------------------
#pragma once
#ifndef INC_TEXTURE_H_
#define INC_TEXTURE_H_

#include "Base.h"
#include "Logger/Logger.h"
#include <string>
#include <map>
#include <d3dx9.h>

class CTexture
{
protected:
	LPDIRECT3DTEXTURE9 m_Texture;
	std::string m_FileName;
	
	//-------------Metodos-------------
	virtual bool LoadFile();
	void Unload();
public:
	CTexture():
		m_Texture(0),
		m_FileName("")
	{}
	~CTexture();
	const std::string & GetFileName() const;
	bool Load(const std::string &FileName);
	bool Reload();
	void Activate(size_t StageId);
};

#endif