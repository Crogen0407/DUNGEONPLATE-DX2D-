#include "pch.h"
#include "GeometryHelper.h"
#include "VertexData.h"

void GeometryHelper::CreateRectangle(std::shared_ptr<Geometry<VertexColorData>> geometry, XMFLOAT4 color)
{
	vector<VertexColorData> vertices;

	vertices.resize(4);
	{
		vertices[0].position = { -0.5f, -0.5f, 0 };
		vertices[0].color = color;

		vertices[1].position = { -0.5f, 0.5f, 0 };
		vertices[1].color = color;

		vertices[2].position = { 0.5f, -0.5f, 0 };
		vertices[2].color = color;

		vertices[3].position = { 0.5f, 0.5f, 0 };
		vertices[3].color = color;
	}
	geometry->SetVertices(vertices);

	vector<UINT> indices = { 0, 1, 2, 2, 1, 3 };
	geometry->SetIndices(indices);
}

void GeometryHelper::CreateRectangle(std::shared_ptr<Geometry<VertexTextureData>> geometry)
{
	vector<VertexTextureData> vertices;

	vertices.resize(4);
	{
		vertices[0].position = { -0.5f, -0.5f, 0 };
		vertices[0].uv = { 0.f, 1.f };

		vertices[1].position = { -0.5f, 0.5f, 0 };
		vertices[1].uv = { 0.f, 0.f };

		vertices[2].position = { 0.5f, -0.5f, 0 };
		vertices[2].uv = { 1.f, 1.f };

		vertices[3].position = { 0.5f, 0.5f, 0 };
		vertices[3].uv = { 1.f, 0.f };
	}
	geometry->SetVertices(vertices);

	vector<UINT> indices = { 0, 1, 2, 2, 1, 3 };
	geometry->SetIndices(indices);
}
