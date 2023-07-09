#include "BuffersArray_AOS.h"
#include "glad/glad.h"

namespace Engine{

    BuffersArray_AOS::BuffersArray_AOS() {
        glGenVertexArrays(1, &ID);
    }


    BuffersArray_AOS::~BuffersArray_AOS() {
        glDeleteVertexArrays(1, &ID);
        for (auto a : buffers) {
            glDeleteBuffers(1, &a);
        }
        glDeleteBuffers(1, &indicesBuffer);
    }


    void BuffersArray_AOS::createElementBuffer() {
        glGenBuffers(1, &indicesBuffer);
    }

    void BuffersArray_AOS::writeElementBuffer(const void *data, long dataSize) const {
        bind();
        //prepare and write indices buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

        unbind();
    }

    unsigned int BuffersArray_AOS::createBuffer() {
        glGenBuffers(1, &currentBuffer);
        buffers.push_back(currentBuffer);
        return buffers.size() - 1;
    }

//TODO optimize buffer to efficiently load non texture data
    void BuffersArray_AOS::writeBuffer(unsigned int location, unsigned int bufferIndex, const void* data, long dataSize, int bufferSize) {
        bind();

        glBindBuffer(GL_ARRAY_BUFFER, buffers[bufferIndex]);
        glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
        glVertexAttribPointer(location, bufferSize, GL_FLOAT, GL_FALSE, bufferSize * sizeof(float), (void*)0);
        glEnableVertexAttribArray(location);

        unbind();
    }

    void BuffersArray_AOS::bind() const {
        glBindVertexArray(ID);
    }

    void BuffersArray_AOS::unbind() const {
        glBindVertexArray(0);
    }

}