#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& _vertices, const std::vector<unsigned int>& _indices, const std::vector<float>& _uv) : vertices(_vertices), indices(_indices), uv(_uv) {

}

Mesh::~Mesh() {

}

void Mesh::setVertices(const std::vector<float>& _vertices) {
    vertices = _vertices;
}

void Mesh::setIndices(const std::vector<unsigned int>& _indices) {
    indices = _indices;
}

void Mesh::setUV(const std::vector<float>& _uv) {
    uv = _uv;
}

float *Mesh::getRawVertices() {
    return vertices.data();
}

unsigned int* Mesh::getRawIndices() {
    return indices.data();
}

float *Mesh::getRawUV() {
    return uv.data();
}

unsigned int Mesh::getVerticesSize() {
    return sizeof(float) * vertices.size();
}

unsigned int Mesh::getIndicesSize() {
    return sizeof(unsigned int) * indices.size();
}

unsigned int Mesh::getUVSize() {
    return sizeof(float) * uv.size();
}
