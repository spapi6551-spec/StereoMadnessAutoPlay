#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

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
        bool 


