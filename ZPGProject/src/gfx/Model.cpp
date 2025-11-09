#include "Model.h"

#include <iostream>
#include <stdexcept>

#include "tiny_obj_loader.h"

Model::Model(const float* points, int count, int groupSize)
	: _vb(new VertexBuffer(points, count)), _va(new VertexArray(groupSize)), _vertexCount(count / groupSize)
{
	_va->AddBuffer(*_vb);
}

Model::Model(const std::string& modelName, const std::string& modelExtraPath)
{
	std::string inputFile = "res/assets/models/" + modelExtraPath + modelName;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputFile.c_str(), ("res/assets/models/" + modelExtraPath).c_str());

    if (!warn.empty()) std::cout << "Warn: " << warn << '\n';
    if (!err.empty()) std::cerr << "Err: " << err << '\n';
    if (!ret) throw std::runtime_error("Failed to load OBJ file!");

	std::vector<float> vertices;

    for (const auto& shape : shapes) 
    {
        for (const auto& index : shape.mesh.indices) 
        {
            // Position
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            // Normals (if exist)
            if (index.normal_index >= 0) 
            {
                vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 2]);
            }
            else 
            { 
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }

            //  UV coordinates (if exist)
            if (index.texcoord_index >= 0) 
            {
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            }
            else 
            {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }
        }
    }

	_vb = new VertexBuffer(vertices.data(), static_cast<int>(vertices.size()));
	_va = new VertexArray(8);
    _va->AddBuffer(*_vb);
	_vertexCount = static_cast<int>(vertices.size() / 8);
}

Model::~Model()
{
	delete _vb;
	delete _va;
}

void Model::Draw()
{
	Bind();
	glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
    Unbind();
}

void Model::Bind() const
{
	_va->Bind();
}

void Model::Unbind() const
{
	_va->Unbind();
}
