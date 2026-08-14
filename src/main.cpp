#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

// Noclip para PlayerObject.
// Cuando el toggle está ON, ignoramos las colisiones.
class $modify(NoclipPlayerObject, PlayerObject) {
    bool collidedWithObject(float dt, GameObject* object) {
        if (Mod::get()->getSettingValue<bool>("noclip")) {
            return false;
        }

        return PlayerObject::collidedWithObject(dt, object);
    }

    bool collidedWithObject(
        float dt,
        GameObject* object,
        cocos2d::CCRect rect,
        bool skipCheck
    ) {
        if (Mod::get()->getSettingValue<bool>("noclip")) {
            return false;
        }

        return PlayerObject::collidedWithObject(
            dt,
            object,
            rect,
            skipCheck
        );
    }

    bool collidedWithObjectInternal(
        float dt,
        GameObject* object,
        cocos2d::CCRect rect,
        bool skipCheck
    ) {
        if (Mod::get()->getSettingValue<bool>("noclip")) {
            return false;
        }

        return PlayerObject::collidedWithObjectInternal(
            dt,
            object,
            rect,
            skipCheck
        );
    }
};

// Evita que el jugador muera por daño cuando Noclip está ON.
class $modify(NoclipPlayLayer, PlayLayer) {
    void playerTookDamage(PlayerObject* player) {
        if (Mod::get()->getSettingValue<bool>("noclip")) {
            return;
        }

        PlayLayer::playerTookDamage(player);
    }
};
