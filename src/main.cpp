#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

// Estado global del noclip (se podría guardar con Mod::get()->setSavedValue si
// quieres que se recuerde entre partidas)
bool g_noclipEnabled = false;

// Hook al PlayerObject: interceptamos la colisión con obstáculos/pinchos
class $modify(NoclipPlayer, PlayerObject) {
    void queueInMainThread(std::function<void()> func) {
        PlayerObject::queueInMainThread(func);
    }

    // checkCollisions es lo que decide si el jugador muere al tocar un objeto
    void checkCollisions(PlayerObject* player, float dt) {
        if (g_noclipEnabled) {
            // Con noclip activo, no dejamos que se procesen las colisiones letales
            return;
        }
        PlayerObject::checkCollisions(player, dt);
    }

    // Refuerzo extra: si algo llega a llamar a la muerte del jugador, la cancelamos
    void playerDestroyed(bool p0) {
        if (g_noclipEnabled) {
            return;
        }
        PlayerObject::playerDestroyed(p0);
    }
};

// Hook al PlayLayer: aquí añadimos el botón ON/OFF en el hub
class $modify(NoclipPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

        // Creamos el menú donde va a vivir el botón
        auto menu = CCMenu::create();
        menu->setPosition({0, 0});
        this->addChild(menu, 100);

        // Sprites ON / OFF para el toggle (puedes cambiar los frames por los tuyos)
        auto onSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
        auto offSprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

        auto toggler = CCMenuItemToggler::create(
            offSprite, onSprite,
            this, menu_selector(NoclipPlayLayer::onToggleNoclip)
        );
        toggler->setPosition({40, 40}); // ajusta la posición a tu gusto
        toggler->toggle(g_noclipEnabled);
        menu->addChild(toggler);

        return true;
    }

    void onToggleNoclip(CCObject* sender) {
        g_noclipEnabled = !g_noclipEnabled;

        auto toggler = static_cast<CCMenuItemToggler*>(sender);
        log::info("Noclip {}", g_noclipEnabled ? "activado" : "desactivado");
    }
};


