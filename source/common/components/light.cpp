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
        attenuation = glm::vec3(data["attenuation"][0], data["attenuation"][1], data["attenuation"][2]);
        coneAngle = glm::vec2(data["coneAngle"][0], data["coneAngle"][1]);
    }

}