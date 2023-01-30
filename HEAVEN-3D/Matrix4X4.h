#pragma once
#include <memory>
#include "Vector3D.h"
#include "Vector4D.h"

class Matrix4X4
{
public:
	Matrix4X4()
	{

	}

	void setIdentity()
	{
		// fill matrix with zero
		::memset(m_mat, 0, sizeof(float) * 16);
		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}

	void setTranslation(const Vector3D& translation)
	{
		
		m_mat[3][0] = translation.m_x;
		m_mat[3][1] = translation.m_y;
		m_mat[3][2] = translation.m_z;

	}

	void setScale(const Vector3D& scale)
	{
		
		m_mat[0][0] = scale.m_x;
		m_mat[1][1] = scale.m_y;
		m_mat[2][2] = scale.m_z;

	}

	void setOrthogonalProjectionMatrix(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();
		m_mat[0][0] = 2.0f / width;
		m_mat[1][1] = 2.0f / height;
		m_mat[2][2] = 1.0f / (far_plane - near_plane);
		m_mat[3][2] = -(near_plane / (far_plane - near_plane));
	}

	Vector3D getZDirection()
	{
		return Vector3D(m_mat[2][0], m_mat[2][1], m_mat[2][2]);
	}
	Vector3D getXDirection()
	{
		return Vector3D(m_mat[0][0], m_mat[0][1], m_mat[0][2]);
	}
	Vector3D getTranslation()
	{
		return Vector3D(m_mat[3][0], m_mat[3][1], m_mat[3][2]);
	}

	void setPerspectiveProjectionMatrix(float fov,float aspect_ratio,float znear,float zfar)
	{
		float yscale = 1.0f / (float)tan(fov / 2.f);
		float xscale = yscale / aspect_ratio;
		m_mat[0][0] = xscale;
		m_mat[1][1] = yscale;
		m_mat[2][2] = zfar / (zfar - znear);
		m_mat[2][3] = 1.0f;
		m_mat[3][2] = ( - znear *zfar )/ (zfar - znear);
	}


	void setRotationX(float x)
	{
		m_mat[1][1] = (float)cos(x);
		m_mat[1][2] = (float)sin(x);
		m_mat[2][1] = -(float)sin(x);
		m_mat[2][2] = (float)cos(x);
	}
	void setRotationY(float y)
	{
		m_mat[0][0] = (float)cos(y);
		m_mat[0][2] = -(float)sin(y);
		m_mat[2][0] = (float)sin(y);
		m_mat[2][2] = (float)cos(y);
	}
	void setRotationZ(float z)
	{
		m_mat[0][0] = (float)cos(z);
		m_mat[0][1] = -(float)sin(z);
		m_mat[1][0] = (float)sin(z);
		m_mat[1][1] = (float)cos(z);
	}

	void operator*=(const Matrix4X4& matrix)
	{
		Matrix4X4 output;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				output.m_mat[i][j] =
					m_mat[i][0] * matrix.m_mat[0][j] + m_mat[i][1] * matrix.m_mat[1][j] +
					m_mat[i][2] * matrix.m_mat[2][j] + m_mat[i][3] * matrix.m_mat[3][j];
			}

		}
		::memcpy(m_mat, output.m_mat, sizeof(float) * 16);
	}

	float getDeterminant()
	{
		Vector4D minor, v1, v2, v3;
		float det;

		v1 = Vector4D(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
		v2 = Vector4D(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
		v3 = Vector4D(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->m_mat[0][3] * minor.m_x + this->m_mat[1][3] * minor.m_y + this->m_mat[2][3] * minor.m_z +
			this->m_mat[3][3] * minor.m_w);
		return det;
	}


	void inverse()
	{

		int a, i, j;
		Matrix4X4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].m_x = (this->m_mat[j][0]);
					vec[a].m_y = (this->m_mat[j][1]);
					vec[a].m_z = (this->m_mat[j][2]);
					vec[a].m_w = (this->m_mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.m_mat[0][i] = (float)pow(-1.0f, i) * (float)v.m_x / (float)det;
			out.m_mat[1][i] = (float)pow(-1.0f, i) * (float)v.m_y / (float)det;
			out.m_mat[2][i] = (float)pow(-1.0f, i) * (float)v.m_z / (float)det;
			out.m_mat[3][i] = (float)pow(-1.0f, i) * (float)v.m_w / (float)det;
		}

		this->setMatrix(out);
	}

	void setMatrix(const Matrix4X4& matrix)
	{
		::memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
	}

	~Matrix4X4()
	{
	}

private:
	float m_mat[4][4] = {};

};