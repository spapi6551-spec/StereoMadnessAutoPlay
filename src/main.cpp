#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

struct InputEvent {
    float time;
    bool pressed;
};

// Eventos de prueba.
// Después podemos poner aquí los eventos reales de Stereo Madness.
static constexpr InputEvent EVENTS[] = {
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

static float g_autoTime = 0.0f;
static std::size_t g_nextEvent = 0;
static bool g_autoPlay = true;

class $modify(StereoMadnessAutoPlay, PlayLayer) {

    bool init(
        GJGameLevel* level,
        bool useReplay,
        bool dontCreateObjects
    ) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        g_autoTime = 0.0f;
        g_nextEvent = 0;
        g_autoPlay = true;

        log::info("StereoMadnessAutoPlay loaded!");

        return true;
    }

    void postUpdate(float dt) {
        PlayLayer::postUpdate(dt);

        if (!g_autoPlay)
            return;

        g_autoTime += dt;

        constexpr std::size_t eventCount =
            sizeof(EVENTS) / sizeof(EVENTS[0]);

        while (
            g_nextEvent < eventCount &&
            g_autoTime >= EVENTS[g_nextEvent].time
        ) {
            auto const& event = EVENTS[g_nextEvent];

            if (m_player1) {
                if (event.pressed) {
                    m_player1->pushButton(PlayerButton::Jump);
                }
                else {
                    m_player1->releaseButton(PlayerButton::Jump);
                }
            }

            ++g_nextEvent;
        }
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        g_autoTime = 0.0f;
        g_nextEvent = 0;
        g_autoPlay = true;
    }
};
