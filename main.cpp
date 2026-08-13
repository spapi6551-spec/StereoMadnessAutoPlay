#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

/*
 * IMPORTANT:
 * This is an experimental controller. It does NOT claim to contain a
 * verified TAS for Stereo Madness. The input table below is deliberately
 * easy to replace with timings extracted from a real replay/video.
 *
 * Time is measured in seconds from the beginning of the level.
 */
struct InputEvent {
    float time;
    bool down;
};

/*
 * Conservative experimental jump schedule.  It is intentionally not
 * advertised as a guaranteed 100% completion macro.
 */
static constexpr InputEvent EVENTS[] = {
    {0.82f, true}, {0.98f, false},
    {1.53f, true}, {1.69f, false},
    {2.16f, true}, {2.32f, false},
    {2.86f, true}, {3.02f, false},
    {3.52f, true}, {3.68f, false},
    {4.20f, true}, {4.36f, false},
    {4.91f, true}, {5.07f, false},
    {5.61f, true}, {5.77f, false},
    {6.30f, true}, {6.46f, false},
    {7.02f, true}, {7.18f, false}
};

class $modify(SMAutoPlay, PlayLayer) {
    struct Fields {
        float elapsed = 0.f;
        size_t nextEvent = 0;
        bool wasEnabled = false;
    };

    bool init(GJGameLevel* level) {
        if (!PlayLayer::init(level))
            return false;

        m_fields->elapsed = 0.f;
        m_fields->nextEvent = 0;
        m_fields->wasEnabled = false;
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        bool enabled = Mod::get()->getSettingValue<bool>("enabled");

        if (!enabled) {
            m_fields->elapsed = 0.f;
            m_fields->nextEvent = 0;
            m_fields->wasEnabled = false;
            return;
        }

        if (!m_fields->wasEnabled) {
            m_fields->elapsed = 0.f;
            m_fields->nextEvent = 0;
            m_fields->wasEnabled = true;
        }

        m_fields->elapsed += dt;

        while (m_fields->nextEvent < std::size(EVENTS) &&
               EVENTS[m_fields->nextEvent].time <= m_fields->elapsed) {
            auto const& ev = EVENTS[m_fields->nextEvent];

            if (m_player1)
                m_player1->pushButton(PlayerButton::Jump, ev.down);

            ++m_fields->nextEvent;
        }
    }
};
