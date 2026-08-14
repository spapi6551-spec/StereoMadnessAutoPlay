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

No cambies el "mod.json" que ya te compiló en verde. Este código utiliza el ajuste que ya tienes, ""enabled"".

Después:

Commit changes → Actions → espera 🟢 → descarga el nuevo ".geode" → reemplaza el anterior.

Con Noclip OFF → juego normal.
Con Noclip ON → las funciones de colisión principales devuelven inmediatamente y el jugador debería poder atravesar bloques/obstáculos.

Si el build vuelve a rojo, no cambies nada: mándame la captura del error.
