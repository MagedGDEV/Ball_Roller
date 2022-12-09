#include "shader.hpp"

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

//Forward definition for error checking functions
std::string checkForShaderCompilationErrors(GLuint shader);
std::string checkForLinkingErrors(GLuint program);

bool our::ShaderProgram::attach(const std::string &filename, GLenum type) const {
    // Here, we open the file and read a string from it containing the GLSL code of our shader
    std::ifstream file(filename);
    if(!file){
        std::cerr << "ERROR: Couldn't open shader file: " << filename << std::endl;
        return false;
    }
    std::string sourceString = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    const char* sourceCStr = sourceString.c_str();
    file.close();

    //TODO: Complete this function
    
    // Create a shader object of the given type (as vertex, fragment, etc.)
    GLuint shader = glCreateShader(type);
    // Set the source code of the shader to the source code of the shader file
    // First parameter is the shader object to set the source code to
    // Second parameter is the number of strings to set the source code to
    // Third parameter is the source code of the shader
    // Fourth parameter is the length of the source code of the shader
    glShaderSource(shader, 1, &sourceCStr, NULL);
    // Compile the shader object
    glCompileShader(shader);
    
    //Note: The function "checkForShaderCompilationErrors" checks if there is
    // an error in the given shader. You should use it to check if there is a
    // compilation error and print it so that you can know what is wrong with
    // the shader. The returned string will be empty if there is no errors.

    // Get the error message from the compilation process
    std::string error = checkForShaderCompilationErrors(shader);
    // Check if there is an error
    if (!error.empty()) {
        // Print the error message
        std::cout << "ERROR: Couldn't compile shader: " << error << std::endl;
        // Return false to indicate that the compilation process failed
        return false;
    }


    // Attach the shader to the program
    glAttachShader(program, shader);
    // Delete the shader object since it is already attached to the shader program and we don't need it anymore
    glDeleteShader(shader);

    //We return true if the compilation succeeded
    return true;
}



bool our::ShaderProgram::link() const {
    //TODO: Complete this function

    // Link the shader program
    glLinkProgram(program);

    //Note: The function "checkForLinkingErrors" checks if there is
    // an error in the given program. You should use it to check if there is a
    // linking error and print it so that you can know what is wrong with the
    // program. The returned string will be empty if there is no errors.

    // Get the error message from the linking process
    std::string error = checkForLinkingErrors(program);
    // Check if there is an error
    if (!error.empty()) {
        // Print the error message
        std::cout << "ERROR: Couldn't link shader program: " << error << std::endl;
        // Return false to indicate that the linking process failed
        return false;
    }
    // We return true if the linking succeeded
    return true;
}

////////////////////////////////////////////////////////////////////
// Function to check for compilation and linking error in shaders //
////////////////////////////////////////////////////////////////////

std::string checkForShaderCompilationErrors(GLuint shader){
     //Check and return any error in the compilation process
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *logStr = new char[length];
        glGetShaderInfoLog(shader, length, nullptr, logStr);
        std::string errorLog(logStr);
        delete[] logStr;
        return errorLog;
    }
    return std::string();
}

std::string checkForLinkingErrors(GLuint program){
     //Check and return any error in the linking process
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *logStr = new char[length];
        glGetProgramInfoLog(program, length, nullptr, logStr);
        std::string error(logStr);
        delete[] logStr;
        return error;
    }
    return std::string();
}