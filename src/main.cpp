#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(NoclipPlayLayer, PlayLayer) {
    void update(float dt) {
        PlayLayer::update(dt);

        bool noclip = Mod::get()->getSettingValue<bool>("enabled");

        if (!noclip)
            return;

        if (m_player1)
            m_player1->m_ignoreDamage = true;

        if (m_player2)
            m_player2->m_ignoreDamage = true;
    }
};
