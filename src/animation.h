#pragma once

#include "images.h"

// enumeration used to access individual animations
enum Animations
{
    ANIMATION_IDLE,
    ANIMATION_LPUNCH,
    ANIMATION_RPUNCH,

    // avoid a separate #define
    ANIMATION_COUNT
};

typedef struct
{
    u8 frame_count;

    // pointer to an array of dynamically allocated frame indices
    u8 *frames;
}
animation_t;

class Animation
{

public:

    Animation();
    ~Animation();

    // updates to next animation frame
    void update();

    // Gets the index of the current frame's sprite
    // \note usage: images.getSprite(animation.getAnimationIndex());
    u8 getAnimationIndex() const;

private:

    // \param `frames`: pointer to an array of allocated frames indices
    // \param `frame_count`: number of frames to allocate for
    // \returns allocated and initialized animation data to be stored in an
    // index of m_animations[]
    animation_t* create(const u8 *frames, u8 frame_count);

    // free's the data allocated in create()
    void release(animation_t *animation);

    // holds the animation data
    animation_t *m_animations[ANIMATION_COUNT];

    // enum'd name of current animation
    Animations m_current;
    // frame offset to current sprite within animation
    u8 m_offset;
};