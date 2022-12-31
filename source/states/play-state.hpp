#pragma once

#include <application.hpp>

#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <systems/free-camera-controller.hpp>
#include <systems/movement.hpp>
#include <asset-loader.hpp>
#include <systems/collision.hpp>

// This state shows how to use the ECS framework and deserialization.
class Playstate: public our::State {

    our::World world;
    our::ForwardRenderer renderer;
    our::FreeCameraControllerSystem cameraController;
    our::MovementSystem movementSystem;
    our::CollisionSystem collisionSystem;
    our::Entity *player;
    

    void onInitialize() override {
        // First of all, we get the scene configuration from the app config
        auto& config = getApp()->getConfig()["scene"];
        // If we have assets in the scene config, we deserialize them
        if(config.contains("assets")){
            our::deserializeAllAssets(config["assets"]);
        }
        // If we have a world in the scene config, we use it to populate our world
        if(config.contains("world")){
            world.deserialize(config["world"]);
        }
        // We initialize the camera controller system since it needs a pointer to the app
        cameraController.enter(getApp());
        // Then we initialize the renderer
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);
    }

    void onDraw(double deltaTime) override {
        // Here, we just run a bunch of systems to control the world logic
        movementSystem.update(&world, (float)deltaTime);
        cameraController.update(&world, (float)deltaTime);
        
        // And finally we use the renderer system to draw the scene
        renderer.render(&world);

        // Get a reference to the keyboard object
        auto& keyboard = getApp()->getKeyboard();

        if(keyboard.justPressed(GLFW_KEY_ESCAPE)){
            // If the escape  key is pressed in this frame, go to the play state
            getApp()->changeState("menu");
        }
        // Check if the player is still alive using a boolean flag
        bool deadFlag = false;
        // check if player won or got out of  the ground of the game
        bool winLoseFlag = true;
        // Iterate through all the entities in the world, check if any of them is the player
        for(auto entity : world.getEntities())
        {
            // If the entity is the player, set the flag to true and break the loop
            if(entity->name == "player")
            {
                // check if player passed the finish line (z = -40)
                // win condition
                if(entity->getLocalToWorldMatrix()[3][2] <= -40)
                {
                    // go to menu state
                    deadFlag = false;
                    break;
                }
                // lose condition (x <= -9.5) | (x >= -0.5)
                else if (entity->getLocalToWorldMatrix()[3][0] <= -9.5 || entity->getLocalToWorldMatrix()[3][0] >= -0.5)
                {
                    // go to menu state
                    deadFlag = false;
                    break;
                }

                deadFlag = true;
                break;
            }
        }
        //If the player is dead/won/passed the ground, go to the menu state
        if(!deadFlag || !winLoseFlag)
        {
            getApp()->changeState("menu");
        }
    }

    void onDestroy() override {
        // Don't forget to destroy the renderer
        renderer.destroy();
        // On exit, we call exit for the camera controller system to make sure that the mouse is unlocked
        cameraController.exit();
        // Clear the world
        world.clear();
        // and we delete all the loaded assets to free memory on the RAM and the VRAM
        our::clearAllAssets();
    }
};