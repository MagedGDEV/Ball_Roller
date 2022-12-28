#include "light.hpp"
#include "../ecs/entity.hpp"
#include <glm/glm.hpp>

namespace our {

    // Reads camera parameters from the given json object
    void LightComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        std::string type = data.value("lightType", "none");
        if(type == "directional")
        {
            lightType = LightType::DIRECTIONAL;
        } 
        else if(type == "point")
        {
            lightType = LightType::POINT;
        } 
        else if(type == "spot")
        {
            lightType = LightType::SPOT;
        }
        else 
        {
            lightType = LightType::DIRECTIONAL;
        }
        
        color = glm::vec3(data["color"][0], data["color"][1], data["color"][2]);
        // attenuation is read as a vector of 3 floats in the json file (constant, linear, quadratic)
        attenuationConstant = data["attenuation"][0];
        attenuationLinear = data["attenuation"][1];
        attenuationQuadratic = data["attenuation"][2];
        // cone angles are read as a vector of 2 floats in the json file (inner, outer)
        innerAngle = glm::radians((float)data["cone_angles"][0]);
        outerAngle = glm::radians((float)data["cone_angles"][1]);
        direction = glm::vec3(data["direction"][0], data["direction"][1], data["direction"][2]);
    }
}