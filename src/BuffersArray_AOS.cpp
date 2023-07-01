#include "BuffersArray_AOS.h"
#include "glad/glad.h"

BuffersArray_AOS::BuffersArray_AOS() {
    glGenVertexArrays(1, &ID);
}

void BuffersArray_AOS::createElementBuffer() {
    glGenBuffers(1, &indicesBuffer);
}

void BuffersArray_AOS::writeElementBuffer(const void *data, long dataSize) const {
    glBindVertexArray(ID);
    //prepare and write indices buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

unsigned int BuffersArray_AOS::createBuffer() {
    glGenBuffers(1, &currentBuffer);
    buffers.push_back(currentBuffer);
    return buffers.size() - 1;
}

//TODO optimize buffer to efficiently load non texture data
void BuffersArray_AOS::writeBuffer(unsigned int location, unsigned int bufferIndex, const void* data, long dataSize, int bufferSize) {
    glBindVertexArray(ID);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[bufferIndex]);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glVertexAttribPointer(location, bufferSize, GL_FLOAT, GL_FALSE, bufferSize * sizeof(float), (void*)0);
    glEnableVertexAttribArray(location);

    glBindVertexArray(0);
}

void BuffersArray_AOS::bind() const {
    glBindVertexArray(ID);
}

void BuffersArray_AOS::unbind() const {
    glBindVertexArray(0);
}

