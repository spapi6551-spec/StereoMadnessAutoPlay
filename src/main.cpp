#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

// Noclip: evita las colisiones principales
class $modify(NoclipPlayerObject, PlayerObject) {

    bool collidedWithObject(float dt, GameObject* object) {
        if (Mod::get()->getSettingValue<bool>("enabled"))
            return false;

        return PlayerObject::collidedWithObject(dt, object);
    }

    bool collidedWithObject(
        float dt,
        GameObject* object,
        cocos2d::CCRect rect,
        bool skipCheck
    ) {
        if (Mod::get()->getSettingValue<bool>("enabled"))
            return false;

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
        if (Mod::get()->getSettingValue<bool>("enabled"))
            return false;

        return PlayerObject::collidedWithObjectInternal(
            dt,
            object,
            rect,
            skipCheck
        );
    }

    void collidedWithSlope(
        float dt,
        GameObject* object,
        bool skipPre
    ) {
        if (Mod::get()->getSettingValue<bool>("enabled"))
            return;

        PlayerObject::collidedWithSlope(
            dt,
            object,
            skipPre
        );
    }

    void collidedWithSlopeInternal(
        float dt,
        GameObject* object,
        bool forced
    ) {
        if (Mod::get()->getSettingValue<bool>("enabled"))
            return;

        PlayerObject::collidedWithSlopeInternal(
            dt,
            object,
            forced
        );
    }
};

// Noclip: evita que el jugador reciba daño
class $modify(NoclipPlayLayer, PlayLayer) {

    void update(float dt) {
        PlayLayer::update(dt);

        if (!Mod::get()->getSettingValue<bool>("enabled"))
            return;

        if (m_player1)
            m_player1->m_ignoreDamage = true;

        if (m_player2)
            m_player2->m_ignoreDamage = true;
    }
};


