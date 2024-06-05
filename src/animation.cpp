#include "animation.h"

// number of elements in an array
#define NELEMS(a) (sizeof(a) / sizeof(*a))

Animation::Animation()
{
    // initialize frame data with sprite indices

    const u8 idle_frames[] = { SPRITE_IDLE_00, SPRITE_IDLE_01 };
    const u8 lpunch_frames[] = { SPRITE_LPUNCH_00, SPRITE_LPUNCH_01 };
    const u8 rpunch_frames[] = { SPRITE_RPUNCH_00, SPRITE_RPUNCH_01 };

    // build m_animations with frame data

    m_animations[ANIMATION_IDLE]
        = create(idle_frames, NELEMS(idle_frames));

    m_animations[ANIMATION_LPUNCH]
        = create(lpunch_frames, NELEMS(lpunch_frames));

    m_animations[ANIMATION_RPUNCH]
        = create(rpunch_frames, NELEMS(rpunch_frames));

    // set default animation

    m_current = ANIMATION_IDLE;
    m_offset = 0;
}

Animation::~Animation()
{
    for (u8 i = 0; i < ANIMATION_COUNT; ++i)
    {
        release(m_animations[i]);
    }
}

void Animation::update()
{
    // increments m_offset and wraps to 0 if m_offset == frame_count
    m_offset = (m_offset + 1) % m_animations[m_current]->frame_count;
}

u8 Animation::getAnimationIndex() const
{
    return m_animations[m_current]->frames[m_offset];
}

animation_t* Animation::create(const u8 *frames, u8 frame_count)
{
    // allocate space for data

    animation_t *animation  = (animation_t*)malloc(sizeof(animation_t));

    animation->frames       = (u8*)malloc(animation->frame_count * sizeof(u8));

    // initialize and copy frames

    animation->frame_count  = frame_count;

    for (u8 i = 0; i < animation->frame_count; ++i)
    {
        animation->frames[i] = frames[i];
    }
    
    return animation;
}

void Animation::release(animation_t *animation)
{
    if (animation)
    {
        if (animation->frames) free(animation->frames);

        free(animation);
    }
}
