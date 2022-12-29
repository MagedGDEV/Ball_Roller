#pragma once

#include "../ecs/world.hpp"
#include "../components/collision.hpp"
#include "../components/free-camera-controller.hpp"
#include "../components/camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <iostream>

namespace our
{
    class CollisionSystem
    {
        public:
        //check if our entity is colliding with another entity, make the other entity disappear
            bool CheckCollision(World *world, Entity *mainEntity)
            {
                CollisionComponent *mainEntityCollision = mainEntity->getComponent<CollisionComponent>();
                if (mainEntityCollision)
                {
                    // Loop over each entity in the world and check if it has collided with our main entity
                    for (auto worldEntity : world->getEntities())
                    {
                        CollisionComponent *worldEntityCollision = worldEntity->getComponent<CollisionComponent>(); 
                        // Check if the other entity is the cube and has a collision component
                        if (worldEntityCollision)                                        
                        {
                            // We need to get the collision parameters of the other entity, which are its center and its radius
                            // Get the radius of the other entity
                            float worldEntityRadius = worldEntityCollision->radius;
                            // find the center of the other entity in the world space
                            glm::vec4 worldEntityCenter = worldEntity->getLocalToWorldMatrix() * worldEntityCollision->center;
                            // Get the center of our main entity in the world space
                            glm::vec4 mainEntityCenter = mainEntity->getLocalToWorldMatrix() * mainEntityCollision->center;
                            // Get the radius of our main entity
                            float mainEntityRadius = mainEntityCollision->radius;
                            // Get the distance between the two entities
                            float distance = glm::distance(mainEntityCenter, worldEntityCenter);
                            if (worldEntity->name == "cube")
                            {
                                // Check if the distance is less than the sum of the two radii
                                if (distance < mainEntityRadius + worldEntityRadius)
                                {
                                    // Here, the two entities are colliding, so we mark the main entity for removal
                                    // This is where the game ends (we will remove the main entity for now)
                                    world->markForRemoval(mainEntity);
                                    return true;
                                }
                            }

                            if(worldEntity->name == "transparentBlock")
                            {
                                //get parent
                                Entity *parent = worldEntity->parent;
                                // Check if the distance is less than the sum of the two radii
                                if (distance < mainEntityRadius + worldEntityRadius)
                                {
                                    // Here, the two entities are colliding, so we mark the other entity for removal
                                    world->markForRemoval(worldEntity);
                                    world->markForRemoval(parent);
                                    return true;
                                }
                            }

                        }
                    } 
                }
                return false;  
            } 
    };
}