#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace our {

    class ShaderProgram {

    private:
        //Shader Program Handle (OpenGL object name)
        GLuint program;

    public:
        ShaderProgram(){
            //TODO: (Req 1) Create A shader program
            // Create an empty shader program (OpenGL object name) where shaders can be attached to
            program = glCreateProgram();
        }
        ~ShaderProgram(){
            //TODO: (Req 1) Delete a shader program
            // Delete the shader program (OpenGL object name) and all the attached shaders
            // to free the memory
            if (program != 0)
            glDeleteProgram(program);
        }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use() { 
            glUseProgram(program);
        }

        GLuint getUniformLocation(const std::string &name) {
            //TODO: (Req 1) Return the location of the uniform with the given name

            // Specify the location of a specific uniform variable for the current program object (shader program)
            // The location of a uniform is the index of the uniform in the array of uniforms in the shader program
            // The index returned is used to specify the uniform when we want to set its value
            // If uniform doesn't exist, glGetUniformLocation returns -1
            return glGetUniformLocation(program, name.c_str());
        }

        void set(const std::string &uniform, GLfloat value) {
            //TODO: (Req 1) Send the given float value to the given uniform

            // Get the location of the uniform with the given name
            GLuint location = getUniformLocation(uniform);
            // check if the uniform exists
            if (location != -1) {
                // Set the value of the uniform and change it to the given value (float)
                glUniform1f(location, value);
            }
        }

        void set(const std::string &uniform, GLuint value) {
            //TODO: (Req 1) Send the given unsigned integer value to the given uniform
            
            // Get the location of the uniform with the given name
            GLuint location = getUniformLocation(uniform);
            // // check if the uniform exists
            if (location != -1) {
                // Set the value of the uniform and change it to the given value (unsigned integer)
                glUniform1ui(location, value);
            }
        }

        void set(const std::string &uniform, GLint value) {
            //TODO: (Req 1) Send the given integer value to the given uniform

            // Get the location of the uniform with the given name
            GLuint location = getUniformLocation(uniform);
            //check if the uniform exists
            if (location != -1) {
                // Set the value of the uniform and change it to the given value (integer)
                glUniform1i(location, value);
            }
        }

        void set(const std::string &uniform, glm::vec2 value) {
            //TODO: (Req 1) Send the given 2D vector value to the given uniform

            // Get the location of the uniform with the given name
            GLuint location = getUniformLocation(uniform);
            //check if the uniform exists
            if (location != -1) {
                // Set the value of the uniform and change it to the given value (2D float vector)
                glUniform2f(location, value.x, value.y);
            }
        }

        void set(const std::string &uniform, glm::vec3 value) {
            //TODO: (Req 1) Send the given 3D vector value to the given uniform

            // Get the location of the uniform with the given name
            GLuint location = getUniformLocation(uniform);
            //check if the uniform exists
            if (location != -1) {
                // Set the value of the uniform and change it to the given value (3D float vector)
                glUniform3f(location, value.x, value.y, value.z);
            }
        }

        void set(const std::string &uniform, glm::vec4 value) {
            //TODO: (Req 1) Send the given 4D vector value to the given uniform

            // Get the location of the uniform with the given name
            GLuint location = getUniformLocation(uniform);
            //check if the uniform exists
            if (location != -1) {
                // Set the value of the uniform and change it to the given value (4D float vector)
                glUniform4f(location, value.x, value.y, value.z, value.w);
            }
        }

        void set(const std::string &uniform, glm::mat4 matrix) {
            //TODO: (Req 1) Send the given matrix 4x4 value to the given uniform

            // Get the location of the uniform with the given name
            GLuint location = getUniformLocation(uniform);
            //check if the uniform exists
            if (location != -1) {
                // Set the value of the uniform and change it to the given value (matrix float 4x4)
                // Second parameter is the number of matrices to be modified which is 1 because 
                // we are sending only one matrix and the uniform is not an array of matrices
                // Third parameter is GL_FALSE because we don't want to transpose the matrix
                // Fourth parameter is the pointer to the matrix
                glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
            }
        }

        //TODO: (Req 1) Delete the copy constructor and assignment operator.
        //Question: Why do we delete the copy constructor and assignment operator?
        
        //Answer: Because we don't want to copy the shader program because it is a resource
        // and we don't want to have two shader programs with the same OpenGL object name
        // because it will cause problems when we try to delete the shader program
        // since this will lead to  deleting the same OpenGL object name twice
        ShaderProgram(ShaderProgram const &) = delete;
        ShaderProgram &operator=(ShaderProgram  const &) = delete;
    };

}

#endif