#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

struct InputEvent {
    float time;
    bool pressed;
};

static constexpr InputEvent events[] = {
    {1.00f, true},
    {1.08f, false},
    {2.10f, true},
    {2.18f, false},
    {3.25f, true},
    {3.33f, false},
    {4.45f, true},
    {4.53f, false},
    {5.70f, true},
    {5.78f, false},
    {6.95f, true},
    {7.03f, false},
    {8.20f, true},
    {8.28f, false},
    {9.50f, true},
    {9.58f, false},
    {10.80f, true},
    {10.88f, false},
    {12.10f, true},
    {12.18f, false}
};

class $modify(StereoMadnessAutoPlay, PlayLayer) {
    float m_autoTime = 0.0f;
    int m_nextEvent = 0;
    bool m_autoPlay = false;

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        m_autoTime = 0.0f;
        m_nextEvent = 0;
        m_autoPlay = true;

        log::info("Stereo Madness AutoPlay iniciado");
        return true;
    }

    void postUpdate(float dt) {
        PlayLayer::postUpdate(dt);

        if (!m_autoPlay)
            return;

        m_autoTime += dt;

        while (
            m_nextEvent < static_cast<int>(sizeof(events) / sizeof(events[0])) &&
            m_autoTime >= events[m_nextEvent].time
        ) {
            if (events[m_nextEvent].pressed) {
                if (m_player1)
                    m_player1->pushButton(PlayerButton::Jump);
            } else {
                if (m_player1)
                    m_player1->releaseButton(PlayerButton::Jump);
            }

            m_nextEvent++;
        }
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        m_autoTime = 0.0f;
        m_nextEvent = 0;
        m_autoPlay = true;
    }
};
