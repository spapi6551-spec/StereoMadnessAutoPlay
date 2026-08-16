#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// Estado global del noclip (se podría guardar con Mod::get()->setSavedValue si
// quieres que se recuerde entre partidas)
bool g_noclipEnabled = false;

// Hook al PlayLayer: interceptamos destroyPlayer (se llama cuando el jugador
// choca con algo que lo mataría) y el botón ON/OFF del hub
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

    // destroyPlayer es lo que se llama cuando el jugador choca con algo
    // que normalmente lo mataría (pinchos, bloques, etc.)
    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        if (g_noclipEnabled) {
            // Con noclip activo, ignoramos la destrucción del jugador
            return;
        }
        PlayLayer::destroyPlayer(player, obj);
    }

    void onToggleNoclip(CCObject* sender) {
        g_noclipEnabled = !g_noclipEnabled;
        log::info("Noclip {}", g_noclipEnabled ? "activado" : "desactivado");
    }
};

    
