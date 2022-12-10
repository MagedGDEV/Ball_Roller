#pragma once

#include <glad/gl.h>
#include "vertex.hpp"

namespace our {

    #define ATTRIB_LOC_POSITION 0
    #define ATTRIB_LOC_COLOR    1
    #define ATTRIB_LOC_TEXCOORD 2
    #define ATTRIB_LOC_NORMAL   3

    class Mesh {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex array object, A vertex buffer and an element buffer
        unsigned int VBO, EBO;
        unsigned int VAO;
        // We need to remember the number of elements that will be draw by glDrawElements 
        GLsizei elementCount;
    public:

        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each rectangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering 
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& elements)
        {
            //TODO: (Req 2) Write this function
            // remember to store the number of elements in "elementCount" since you will need it for drawing
            // For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc
            
            // Create the vertex array object
            // First parameter is the number of vertex array object to create
            // Second parameter is the address of the variable that will store the name of the vertex array object
            glGenVertexArrays(1, &VAO);
            // Bind the vertex array object with the name: VAO
            glBindVertexArray(VAO);

            // Create the buffer object
            // First parameter is the number of buffer objects to create
            // Second parameter is the address of the variable that will store the name of the buffer object
            glGenBuffers(1, &VBO);
            // Bind the buffer object with the name: VBO
            // First parameter is the type of the buffer object
            // GL_ARRAY_BUFFER is used for vertex attributes
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            // Create the element buffer object
            glGenBuffers(1, &EBO);
            // Bind the buffer object with the name: EBO
            // GL_ELEMENT_ARRAY_BUFFER is used for vertex array (element) indices
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            // Set the elementCount
            elementCount = elements.size();
            
            // Copy the vertex data to the buffer object on the VRAM
            // First parameter is the type of the buffer object (Vertex attribute)
            // Second parameter is the size of the data in bytes
            // Third parameter is the address of the data
            // Fourth parameter is the usage of the buffer object (static -> data will not be changed)
            // vertices.data() returns the address of the first element of the vector
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

            // Define the layout of the vertex buffer
            // First parameter is the index of the vertex attribute to be modified
            // Second parameter is the number of components per vertex attribute
            // Third parameter is the data type of each component in the array
            // Fourth parameter is whether the data should be normalized or not 
            // Fifth parameter is the stride (byte offset between consecutive vertex attributes) 
            // which is the bytes skiped to reach the next vertex attribute
            // Sixth parameter is the offset of the first component of the vertex attribute 
            // which is the bytes skiped to reach the first component of the vertex attribute
            
            // Then enable the vertex attribute as it is disabled by default

            glVertexAttribPointer(ATTRIB_LOC_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            glEnableVertexAttribArray(ATTRIB_LOC_POSITION);

            glVertexAttribPointer(ATTRIB_LOC_COLOR, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
            glEnableVertexAttribArray(ATTRIB_LOC_COLOR);

            glVertexAttribPointer(ATTRIB_LOC_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
            glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORD);

            glVertexAttribPointer(ATTRIB_LOC_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
            glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);

            // Copy the element data to the buffer object on the VRAM
            // First parameter is the type of the buffer object (Element array)
            // Second parameter is the size of the data in bytes
            // Third parameter is the address of the data
            // Fourth parameter is the usage of the buffer object (static -> data will not be changed)
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), elements.data(), GL_STATIC_DRAW);
        }

        // this function should render the mesh
        void draw() 
        {
            //TODO: (Req 2) Write this function
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh(){
            //TODO: (Req 2) Write this function
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}