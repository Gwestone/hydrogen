#ifndef HYDROGEN_BUFFERSARRAY_AOS_H
#define HYDROGEN_BUFFERSARRAY_AOS_H


#include <vector>

namespace Engine{
    class BuffersArray_AOS {
    private:
    public:
        BuffersArray_AOS (const BuffersArray_AOS&) = delete;
        BuffersArray_AOS& operator= (const BuffersArray_AOS&) = delete;

        BuffersArray_AOS();
        ~BuffersArray_AOS();
        unsigned int createBuffer();
        void writeBuffer(unsigned int location, unsigned int bufferIndex, const void* data, long dataSize, int bufferSize);
        void createElementBuffer();
        void writeElementBuffer(const void* data, long dataSize) const;
        void bind() const;
        void unbind() const;
    private:
        unsigned int ID;
        unsigned int lastBufferIndex = 0;
        unsigned int currentBuffer;
        std::vector<unsigned int> buffers;
        unsigned int indicesBuffer;
    };
}


#endif //HYDROGEN_BUFFERSARRAY_AOS_H
