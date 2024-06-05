#pragma once

#include "images.h"

enum Animations
{
    ANIMATION_IDLE,
    ANIMATION_LPUNCH,
    ANIMATION_RPUNCH,

    ANIMATION_COUNT
};

typedef struct
{
    u8 frame_count;
    u8 *frames; // pointer to an array of dynamically allocated frame indices
}
animation_t;

class Animation
{

public:

    Animation();
    ~Animation();

    void play(const Animations animation, const u8 frame_delay);
    void update();

    u8 getAnimationIndex() const;

private:

    // @returns allocated and initialized animation data to be stored in an
    // index of m_animations[]
    animation_t create(const u8 *frames, u8 frame_count);

    void release();

    animation_t m_animations[ANIMATION_COUNT];
    Animations m_animation;

    // frame offset to current sprite within animation
    u8 m_offset;

    u8 m_frame_delay;
    u8 m_frame_delay_counter;
};
