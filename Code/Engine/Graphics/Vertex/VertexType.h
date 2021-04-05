#pragma once
#ifndef INC_VERTEX_TYPE_H_
#define INC_VERTEX_TYPE_H_

#include <d3dx9.h>

#define VERTEX_TYPE_GEOMETRY 0x0001
#define VERTEX_TYPE_NORMAL 0x0002
#define VERTEX_TYPE_TANGENT 0x0004
#define VERTEX_TYPE_BINORMAL 0x0008
#define VERTEX_TYPE_TEXTURE1 0x0010
#define VERTEX_TYPE_TEXTURE2 0x0020
#define VERTEX_TYPE_DIFFUSE 0x0040

//Geometr�a y Color
struct TCOLORED_VERTEX
{
	float x, y, z;
	unsigned long color;
	static inline unsigned short GetVertexType()
	{
		return VERTEX_TYPE_GEOMETRY|VERTEX_TYPE_DIFFUSE;
	}
	static inline unsigned int GetFVF()
	{
		return D3DFVF_XYZ|D3DFVF_DIFFUSE;
	}
};

//Geometr�a, Normal y Color
struct TNORMAL_COLORED_VERTEX
{
	float x, y, z; // geometr�a
	float nx, ny, nz; // normal
	unsigned long color; // color
	static inline unsigned short GetVertexType()
	{
		return VERTEX_TYPE_GEOMETRY|VERTEX_TYPE_NORMAL|VERTEX_TYPE_DIFFUSE;
	}
	static inline unsigned int GetFVF()
	{
		return D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE;
	}
};

//Geometr�a, Normal, Color, Textura1
struct TNORMAL_COLORED_TEXTURE1_VERTEX
{
	float x, y, z; // geometr�a
	float nx, ny, nz; // normal
	unsigned long color; // color
	float u1, v1; // textura1

	static inline unsigned short GetVertexType()
	{
		return VERTEX_TYPE_GEOMETRY|VERTEX_TYPE_NORMAL|VERTEX_TYPE_DIFFUSE|VERTEX_TYPE_TEXTURE1;
	}
	static inline unsigned int GetFVF()
	{
		return D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1;
	}
};

//Geometr�a, Normal, Color, Textura1, Textura2
struct TNORMAL_COLORED_TEXTURE1_TEXTURE2_VERTEX
{
	float x, y, z; // geometr�a
	float nx, ny, nz; // normal
	unsigned long color; // color
	float u1, v1; // textura1
	float u2, v2; // textura2

	static inline unsigned short GetVertexType()
	{
		return VERTEX_TYPE_GEOMETRY|VERTEX_TYPE_NORMAL|VERTEX_TYPE_DIFFUSE|VERTEX_TYPE_TEXTURE2;
	}
	static inline unsigned int GetFVF()
	{
		return D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX2;
	}
};


//Geometr�a, Textura1
struct TTEXTURE1_VERTEX
{
	float x, y, z; // geometr�a
	float u1, v1; // textura1
	static inline unsigned short GetVertexType()
	{
		return VERTEX_TYPE_GEOMETRY|VERTEX_TYPE_TEXTURE1;
	}
	static inline unsigned int GetFVF()
	{
		return D3DFVF_XYZ|D3DFVF_TEX1;
	}
};

//Geometr�a, Textura1, Textura2
struct TTEXTURE2_VERTEX
{
	float x, y, z; // geometr�a
	float u1, v1; // textura1
	float u2, v2; // textura2
	static inline unsigned short GetVertexType()
	{
		return VERTEX_TYPE_GEOMETRY|VERTEX_TYPE_TEXTURE2;
	}
	static inline unsigned int GetFVF()
	{
		return D3DFVF_XYZ|D3DFVF_TEX2;
	}
};

//Geometr�a, Normal, Textura1
struct TNORMAL_TEXTURE1_VERTEX
{
	float x, y, z; // geometr�a
	float nx, ny, nz; // normal
	float u1, v1; // textura1
	static inline unsigned short GetVertexType()
	{
		return VERTEX_TYPE_GEOMETRY|VERTEX_TYPE_NORMAL|VERTEX_TYPE_TEXTURE1;
	}
	static inline unsigned int GetFVF()
	{
		return D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1;
	}
};

//Geometr�a, Normal, Textura1, Textura2
struct TNORMAL_TEXTURE2_VERTEX
{
	float x, y, z; // geometr�a
	float nx, ny, nz; // normal
	float u1, v1; // textura1
	float u2, v2; // textura2
	static inline unsigned short GetVertexType()
	{
		return VERTEX_TYPE_GEOMETRY|VERTEX_TYPE_NORMAL|VERTEX_TYPE_TEXTURE2;
	}
	static inline unsigned int GetFVF()
	{
		return D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2;
	}
};

#endif