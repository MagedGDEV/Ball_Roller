#include "light.hpp"
#include "../ecs/entity.hpp"
#include <glm/glm.hpp>

namespace our {

    // Reads camera parameters from the given json object
    void CameraComponent::deserialize(const nlohmann::json& data){
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
        
        color = data.value("color", color);
        attenuation = data.value("attenuation", attenuation);
        coneAngle = data.value("coneAngle", coneAngle);
    }

}