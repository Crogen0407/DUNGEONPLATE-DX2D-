#pragma once
#include "Geometry.h"
class VertexTextureData;
class VertexColorData;
class GeometryHelper
{
public:
	static void CreateRectangle(std::shared_ptr<Geometry<VertexColorData>> geometry, XMFLOAT4 color);
	static void CreateRectangle(std::shared_ptr<Geometry<VertexTextureData>> geometry);
};

