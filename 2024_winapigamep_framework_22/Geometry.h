#pragma once

template<typename T>
class Geometry
{
public:
	Geometry() {}
	~Geometry() {}

	UINT GetVertexCount() { return static_cast<UINT>(_vertices.size()); }
	
	void* GetVertexData() { return _vertices.data(); }
	const vector<T>& GetVertices() { return _vertices; }

	UINT GetIndexCount() { return static_cast<UINT>(_indices.size()); }
	void* GetIndexData() { return _indices.data(); }
	const vector<UINT>& GetIndices() { return _indices; }

	void AddVertex(const T& vertex) { _vertices.push_back(vertex); }
	void AddVertices(const vector<T>& vertices) { _vertices.insert(_vertices.end(), vertices.begin(), vertices.end()); }
	void SetVertices(const vector<T>& vertices) { _vertices = vertices; }

	void AddIndex(UINT index) { _indices.push_back(index); }
	void AddIndices(const vector<UINT>& indices) { _indices.insert(_indices.end(), indices.begin(), indices.end()); }
	void SetIndices(const vector<UINT>& indices) { _indices = indices; }

private:
	vector<T> _vertices;
	vector<UINT> _indices;
};