#ifndef JPAPARTICLE_H
#define JPAPARTICLE_H

#include "JSystem/JSupport/JSUList.h"
#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/gx/GXStruct.h"

class JKRHeap;
class JPABaseEmitter;
class JPABaseParticle;
class JPAEmitterCallBack;
class JPAEmitterManager;
class JPAParticleCallBack;
class JPAResourceManager;
struct JPAEmitterWorkData;
struct JPACallBackBase2;

class JPABaseParticle {
public:
    void initParticle();
    void initChild(JPABaseParticle*);
    void incFrame();
    void calcVelocity();
    void calcPosition();
    void checkCreateChild();

    ~JPABaseParticle();
    JPABaseParticle();

public:
    /* 0x00 */ JSUPtrLink mLink;
    /* 0x10 */ cXyz mGlobalPosition;
    /* 0x1C */ cXyz mLocalPosition;
    /* 0x28 */ cXyz mPosition;
    /* 0x34 */ cXyz mVelocity;
    /* 0x40 */ cXyz mBaseVel;
    /* 0x4C */ cXyz mAccel;
    /* 0x58 */ cXyz mFieldVel;
    /* 0x64 */ cXyz mFieldAccel;
    /* 0x70 */ f32 mAirResist;
    /* 0x74 */ f32 mMoment;
    /* 0x78 */ f32 mCurFrame;
    /* 0x7C */ f32 mLifeTime;
    /* 0x80 */ f32 mCurNormTime;
    /* 0x84 */ f32 mFieldDrag;
    /* 0x88 */ f32 mDrag;
    /* 0x8C */ cXyz mAxis;
    /* 0x98 */ f32 mScaleOut;
    /* 0x9C */ f32 mScaleX;
    /* 0xA0 */ f32 mScaleY;
    /* 0xA4 */ u8 field_0xA4[0xAC - 0xA4];
    /* 0xAC */ f32 mAlphaOut;
    /* 0xB0 */ f32 mAlphaWaveRandom;
    /* 0xB4 */ int mLoopOffset;
    /* 0xB8 */ GXColor mPrmColor;
    /* 0xBC */ GXColor mEnvColor;
    /* 0xC0 */ s16 mRotateAngle;
    /* 0xC2 */ s16 mRotateSpeed;
    /* 0xC4 */ u8 field_0xC4[0xC6 - 0xC4];
    /* 0xC6 */ u16 mTexIdx;
    /* 0xC8 */ JPACallBackBase2* mpCallBack2;
    /* 0xCC */ u32 mFlags;
};

class JPAParticleCallBack {
public:
    JPAParticleCallBack() {}
    virtual ~JPAParticleCallBack();
    virtual void execute(JPABaseEmitter*, JPABaseParticle*);
    virtual void draw(JPABaseEmitter*, JPABaseParticle*);
};

// not sure where this belongs
static inline u32 COLOR_MULTI(u32 a, u32 b) {
    return ((a * (b + 1)) * 0x10000) >> 24;
}

#endif /* JPAPARTICLE_H */