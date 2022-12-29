#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {

    class CollisionComponent : public Component {
    public:
        glm::vec4 center = {0, 0, 0, 1}; // The center of the collision sphere
        float radius = 0.5;           // The radius of the collision sphere

        // The ID of this component type is "Collision"
        static std::string getID() { return "Collision"; }

        // Reads linearVelocity & angularVelocity from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}