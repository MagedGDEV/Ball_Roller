#pragma once

#include <glad/gl.h>
#include <glm/vec4.hpp>
#include <json/json.hpp>

namespace our {
    // There are some options in the render pipeline that we cannot control via shaders
    // such as blending, depth testing and so on
    // Since each material could require different options (e.g. transparent materials usually use blending),
    // we will encapsulate all these options into a single structure that will also be responsible for configuring OpenGL's pipeline
    struct PipelineState {
        // This set of pipeline options specifies whether face culling will be used or not and how it will be configured
        struct {
            bool enabled = false;
            GLenum culledFace = GL_BACK;
            GLenum frontFace = GL_CCW;
        } faceCulling;

        // This set of pipeline options specifies whether depth testing will be used or not and how it will be configured
        struct {
            bool enabled = false;
            GLenum function = GL_LEQUAL;
        } depthTesting;

        // This set of pipeline options specifies whether blending will be used or not and how it will be configured
        struct {
            bool enabled = false;
            GLenum equation = GL_FUNC_ADD;
            GLenum sourceFactor = GL_SRC_ALPHA;
            GLenum destinationFactor = GL_ONE_MINUS_SRC_ALPHA;
            glm::vec4 constantColor = {0, 0, 0, 0};
        } blending;

        // These options specify the color and depth mask which can be used to
        // prevent the rendering/clearing from modifying certain channels of certain targets in the framebuffer
        glm::bvec4 colorMask = {true, true, true, true}; // To know how to use it, check glColorMask
        bool depthMask = true; // To know how to use it, check glDepthMask


        // This function should set the OpenGL options to the values specified by this structure
        // For example, if faceCulling.enabled is true, you should call glEnable(GL_CULL_FACE), otherwise, you should call glDisable(GL_CULL_FACE)
        void setup() const {
            //TODO: (Req 4) Write this function
            // Note: You can use the following functions to configure OpenGL's pipeline:
            // glEnable, glDisable, glCullFace, glFrontFace, glDepthFunc, glBlendEquation, glBlendFunc, glBlendColor, glColorMask, glDepthMask

            // check if face culling is enabled
            if (faceCulling.enabled) 
            {
                // enable face culling
                glEnable(GL_CULL_FACE);
                // set the culled face
                glCullFace(faceCulling.culledFace);
                // set the front face
                glFrontFace(faceCulling.frontFace);
            }
            else 
            {
                // disable face culling if it is not enabled
                glDisable(GL_CULL_FACE);
            }

            // check if depth testing is enabled
            if (depthTesting.enabled) 
            {
                // enable depth testing
                glEnable(GL_DEPTH_TEST);
                // set the depth function
                glDepthFunc(depthTesting.function);
            }
            else
            {
                // disable depth testing if it is not enabled
                glDisable(GL_DEPTH_TEST);
            }

            if (blending.enabled) 
            {
                // enable blending
                glEnable(GL_BLEND);
                // set the blending equation
                glBlendEquation(blending.equation);
                // set the blending factors
                glBlendFunc(blending.sourceFactor, blending.destinationFactor);
                // set the blending constant color
                glBlendColor(blending.constantColor.r, blending.constantColor.g, blending.constantColor.b, blending.constantColor.a);
            }
            else 
            {
                // disable blending if it is not enabled
                glDisable(GL_BLEND);
            }

            // set the color mask according to the color mask specified in the pipeline state
            glColorMask(colorMask.r, colorMask.g, colorMask.b, colorMask.a);
            // set the depth mask according to the depth mask specified in the pipeline state
            glDepthMask(depthMask);
        }

        // Given a json object, this function deserializes a PipelineState structure
        void deserialize(const nlohmann::json& data);
    };

}