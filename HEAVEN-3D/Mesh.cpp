#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <locale>
#include <codecvt>
#include "VertexMesh.h"
#include "Graphics.h"
#include "Renderer.h"

Mesh::Mesh(const wchar_t* full_path):Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector < tinyobj::shape_t > shapes;
	std::vector < tinyobj::material_t > materials;
	std::string warn;
	std::string error;

	// convert path to ascii 
//	std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(full_path);
	auto inputfile = wide_string_to_string(full_path);
	//std::string inpf = WideCharToMultiByte(CP_UTF8, 0, &full_path[0], (int)sizeof(full_path), NULL, 0,NULL,NULL);
	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &error, inputfile.c_str());

	if(!error.empty()) throw std::exception("Texture not created successfully");
	if (!res) throw std::exception("Texture not created successfully");

	if(shapes.size()>1) throw std::exception("Texture not created successfully");
	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	// get the datas and process
	for(size_t s=0;s<shapes.size();s++)
	{
		size_t index_offset = 0;
		list_vertices.reserve(shapes[s].mesh.indices.size());
		list_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];
			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
				tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];

				VertexMesh mesh;
				mesh.m_position = Vector3D{ vx,vy,vz };
				mesh.m_texcoord = Vector2D{ tx,ty };

				list_vertices.push_back(mesh);
				list_indices.push_back(index_offset + v);
			}

			index_offset += num_face_verts;
		}
	}
	void* shader_byte_code = nullptr;
	size_t shader_size = 0;
	Graphics::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &shader_size);


	m_vertex_buffer =  Graphics::get()->getRenderSystem()->CreateVertexBuffer(
		&list_vertices[0], 
		sizeof(VertexMesh), 
		list_vertices.size(), shader_byte_code, 
		shader_size);


	m_index_buffer = Graphics::get()->getRenderSystem()->createIndexBuffer(
		&list_indices[0], 
		(UINT)list_indices.size());
}

Mesh::~Mesh()
{
}

const sVertexBufferPtr& Mesh::getVertexBuffer()
{
	return m_vertex_buffer;
}

const sIndexBufferPtr& Mesh::getIndexBuffer()
{
	return m_index_buffer;
}

std::string Mesh::wide_string_to_string(const std::wstring& wide_string)
{
	if (wide_string.empty())
	{
		return "";
	}

	const auto size_needed = WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(), nullptr, 0, nullptr, nullptr);
	if (size_needed <= 0)
	{
		throw std::runtime_error("WideCharToMultiByte() failed: " + std::to_string(size_needed));
	}

	std::string result(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(), &result.at(0), size_needed, nullptr, nullptr);
	return result;
}