#pragma once

#include "../ecs/component.hpp"
#include <glm/glm.hpp>


namespace our {

    // enum for the type of light
    enum class LightType {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    class LightComponent : public Component {
    public:
    
        LightType lightType; // The type of the light
        glm::vec3 color; // The color of the light
        float attenuationConstant; // The constant attenuation of the light
        float attenuationLinear; // The linear attenuation of the light
        float attenuationQuadratic; // The quadratic attenuation of the light
        float innerAngle; // The inner angle of the light
        float outerAngle; // The outer angle of the light

        // positon and direction are calculated from the entity component

        // The ID of this component type is "Light"
        static std::string getID() { return "Light"; }

        // Reads light parameters from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}