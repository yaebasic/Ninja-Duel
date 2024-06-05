#include "animation.h"

#define NELEMS(a) (sizeof(a) / sizeof(*a))

Animation::Animation()
{
    // initialize frame data with sprite indices

    const u8 idle_frames[]      = { SPRITE_IDLE_00, SPRITE_IDLE_01 };
    const u8 lpunch_frames[]    = { SPRITE_LPUNCH_00, SPRITE_LPUNCH_01 };
    const u8 rpunch_frames[]    = { SPRITE_RPUNCH_00, SPRITE_RPUNCH_01 };

    // build m_animations with frame data

    m_animations[ANIMATION_IDLE]
        = create(idle_frames, NELEMS(idle_frames));

    m_animations[ANIMATION_LPUNCH]
        = create(lpunch_frames, NELEMS(lpunch_frames));

    m_animations[ANIMATION_RPUNCH]
        = create(rpunch_frames, NELEMS(rpunch_frames));

    // set starting animation

    play(ANIMATION_IDLE, 5);
}

Animation::~Animation()
{
    release();  
}

void Animation::play(const Animations animation, const u8 frame_delay)
{
    m_animation = animation;
    m_frame_delay = frame_delay;

    m_offset = 0;
    m_frame_delay_counter = 0;
}

void Animation::update()
{
    m_frame_delay_counter++;

    if (m_frame_delay_counter == m_frame_delay)
    {
        m_frame_delay_counter = 0;

        // increments index offset and wraps to 0 if equal to frame_count
        m_offset = (m_offset + 1) % m_animations[m_animation].frame_count;
    }
}

u8 Animation::getAnimationIndex() const
{
    return m_animations[m_animation].frames[m_offset];
}

animation_t Animation::create(const u8 *frames, u8 frame_count)
{
    animation_t animation;

    animation.frames = (u8*)malloc(animation.frame_count * sizeof(u8));

    // initialize and copy frames

    animation.frame_count = frame_count;

    for (u8 i = 0; i < animation.frame_count; ++i)
    {
        animation.frames[i] = frames[i];
    }
    
    return animation;
}

void Animation::release()
{
    for (u8 i = 0; i < ANIMATION_COUNT; ++i)
    {
        free(m_animations[i].frames);
    }
}
