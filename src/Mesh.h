#ifndef HYDROGEN_MESH_H
#define HYDROGEN_MESH_H


#include <vector>

struct Mesh {
private:
public:
    Mesh(const std::vector<float>& _vertices, const std::vector<unsigned int>& _indices, const std::vector<float>& _uv);
    ~Mesh();
    void setVertices(const std::vector<float>& _vertices);
    void setIndices(const std::vector<unsigned int>& _indices);
    void setUV(const std::vector<float>& _uv);

    float* getRawVertices();
    unsigned int getVerticesSize();

    unsigned int* getRawIndices();
    unsigned int getIndicesSize();

    float* getRawUV();
    unsigned int getUVSize();

private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> uv;
};


#endif //HYDROGEN_MESH_H
