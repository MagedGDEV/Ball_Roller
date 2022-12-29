#include "collision.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Reads linearVelocity & angularVelocity from the given json object
    void CollisionComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        radius = data["radius"].get<float>();
        center = data.value("center", center);
    }
}