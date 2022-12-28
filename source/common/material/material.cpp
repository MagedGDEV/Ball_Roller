#include "material.hpp"

#include "../asset-loader.hpp"
#include "deserialize-utils.hpp"

namespace our {

    // This function should setup the pipeline state and set the shader to be used
    void Material::setup() const {
        //TODO: (Req 7) Write this function
        //set pipeline state
        pipelineState.setup();
        // set shader
        shader->use();
    
    }

    // This function read the material data from a json object
    void Material::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;

        if(data.contains("pipelineState")){
            pipelineState.deserialize(data["pipelineState"]);
        }
        shader = AssetLoader<ShaderProgram>::get(data["shader"].get<std::string>());
        transparent = data.value("transparent", false);
        isLit = data.value("isLit", false);
    }

    // This function should call the setup of its parent and
    // set the "tint" uniform to the value in the member variable tint 
    void TintedMaterial::setup() const {
        //TODO: (Req 7) Write this function
        Material::setup();
        // set tint uniform
        shader->set("tint", tint);
    }

    // This function read the material data from a json object
    void TintedMaterial::deserialize(const nlohmann::json& data){
        Material::deserialize(data);
        if(!data.is_object()) return;
        tint = data.value("tint", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // This function should call the setup of its parent and
    // set the "alphaThreshold" uniform to the value in the member variable alphaThreshold
    // Then it should bind the texture and sampler to a texture unit and send the unit number to the uniform variable "tex" 
    void TexturedMaterial::setup() const {
        //TODO: (Req 7) Write this function
        TintedMaterial::setup();
        // set alphaThreshold uniform
        // values less than alphaThreshold will be discarded
        shader->set("alphaThreshold", alphaThreshold);

        // set GL_TEXTURE1 as active texture unit
        glActiveTexture(GL_TEXTURE1);
        // bind texture to active texture unit
        texture->bind();
        // bind sampler to active texture unit 
        // if sampler is not null
        if (sampler != nullptr) {
            sampler->bind(1);
        }
        // setting tex uniform
        shader->set("tex", 1);
    }

    // This function read the material data from a json object
    void TexturedMaterial::deserialize(const nlohmann::json& data){
        TintedMaterial::deserialize(data);
        if(!data.is_object()) return;
        alphaThreshold = data.value("alphaThreshold", 0.0f);
        texture = AssetLoader<Texture2D>::get(data.value("texture", ""));
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }

    void LitMaterial::setup() const {
        TexturedMaterial::setup();

        if (albedo != nullptr) {
            glActiveTexture(GL_TEXTURE2);
            albedo->bind();
            sampler->bind(2);
            shader->set("material.albedo", 2);
        }

        if (specular != nullptr) {
            glActiveTexture(GL_TEXTURE3);
            specular->bind();
            sampler->bind(3);
            shader->set("material.specular", 3);
        }

        if (ambientOcclusion != nullptr) {
            glActiveTexture(GL_TEXTURE4);
            ambientOcclusion->bind();
            sampler->bind(4);
            shader->set("material.ambient_occlusion", 4);
        }

        if (emissive != nullptr) {
            glActiveTexture(GL_TEXTURE5);
            emissive->bind();
            sampler->bind(5);
            shader->set("material.emissive", 5);
        }

        if (roughness != nullptr) {
            glActiveTexture(GL_TEXTURE6);
            roughness->bind();
            sampler->bind(6);
            shader->set("material.roughness", 6);
        }
    }

    void LitMaterial::deserialize(const nlohmann::json& data) {
        TexturedMaterial::deserialize(data);
        if (!data.is_object()) return;

        albedo = AssetLoader<Texture2D>::get(data.value("albedo", ""));
        specular = AssetLoader<Texture2D>::get(data.value("specular", ""));
        ambientOcclusion = AssetLoader<Texture2D>::get(data.value("ambient_occlusion", ""));
        emissive = AssetLoader<Texture2D>::get(data.value("emissive", ""));
        roughness = AssetLoader<Texture2D>::get(data.value("roughness", ""));
    }

}