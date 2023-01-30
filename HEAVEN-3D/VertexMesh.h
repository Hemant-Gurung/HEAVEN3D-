#pragma once
#include "Vector3D.h"
#include "Vector2D.h"

class VertexMesh
{
public:
	VertexMesh() :
		m_position(),
		m_texcoord()
	{

	}

	VertexMesh(Vector3D position, Vector2D texcoord) :
		m_position(position),
		m_texcoord(texcoord)

	{

	}
	VertexMesh(const VertexMesh& vector) :
		m_position(vector.m_position),
		m_texcoord(vector.m_texcoord)
	{

	}

	~VertexMesh()
	{

	}


	Vector3D m_position;
	Vector2D m_texcoord;

};