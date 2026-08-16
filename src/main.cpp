#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

class $modify(NoclipGameLayer, GJBaseGameLayer) {
    int checkCollisions(
        PlayerObject* player,
        float dt,
        bool ignoreDamage
    ) {
        if (Mod::get()->getSettingValue<bool>("enabled")) {
            // Ignorar el procesamiento de daño/colisión.
            return 0;
        }

        return GJBaseGameLayer::checkCollisions(
            player,
            dt,
            ignoreDamage
        );
    }
};


