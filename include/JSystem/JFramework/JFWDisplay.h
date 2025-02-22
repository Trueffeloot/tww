#ifndef JFWDISPLAY_H
#define JFWDISPLAY_H

#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JUtility/JUTDirectPrint.h"
#include "JSystem/JUtility/JUTFader.h"
#include "JSystem/JUtility/JUTXfb.h"
#include "dolphin/os/OSAlarm.h"
#include "dolphin/types.h"

typedef struct _GXColor GXColor;
typedef struct _GXRenderModeObj GXRenderModeObj;
class JKRHeap;

typedef void (*JFWDisplayUnkFunc)(void);

extern bool JFWAutoAbortGfx;

class JFWAlarm : public OSAlarm {
public:
    JFWAlarm() /* : mLink(this) */ {}
    ~JFWAlarm() {}
    void createAlarm() { OSCreateAlarm(this); }
    void cancelAlarm() { OSCancelAlarm(this); }
    //void removeLink() { sList.remove(&mLink); }
    //void appendLink() { sList.append(&mLink); }
    OSThread* getThread() const { return mThread; }
    void setThread(OSThread* thread) { mThread = thread; }

    static JSUList<JFWAlarm> sList;

public:
    /* 0x30 */ OSThread* mThread;
};

class JFWDisplay {
public:
    enum EDrawDone {
        /* 0x0 */ UNK_METHOD_0 = 0,
        /* 0x1 */ UNK_METHOD_1 = 1
    };

    /* 80272040 */ void ctor_subroutine(const _GXRenderModeObj*, bool enableAlpha);
    /* 802720F8 */ JFWDisplay(const _GXRenderModeObj*, JKRHeap*, JUTXfb::EXfbNumber, bool);
    /* 802721DC */ static JFWDisplay* createManager(JKRHeap*, JUTXfb::EXfbNumber, bool);
    /* 802722B8 */ void prepareCopyDisp();
    /* 802723AC */ void drawendXfb_single();
    /* 802723F4 */ void exchangeXfb_double();
    /* 802724FC */ void exchangeXfb_triple();
    /* 80272574 */ void copyXfb_triple();
    /* 802725F8 */ void preGX();
    /* 8027268C */ void endGX();
    /* 80272C60 */ void waitBlanking(int);
    /* 80272E10 */ void threadSleep(s64);
    /* 80272EB8 */ void clearEfb_init();
    /* 80272F9C */ void clearEfb(int param_0, int param_1, int param_2, int param_3, GXColor color);
    /* 80272F2C */ void clearEfb();
    /* 80272F58 */ void clearEfb(_GXColor color);
    /* 8027331C */ void calcCombinationRatio();

    /* 80272798 */ virtual void beginRender();
    /* 80272A04 */ virtual void endRender();
    /* 80272AB0 */ virtual void endFrame();
    /* 80272160 */ virtual ~JFWDisplay();

    static JFWDisplay* getManager() { return sManager; }

    int startFadeOut(int param_0) {
        if (mpFader != NULL) {
            return mpFader->startFadeOut(param_0);
        }
        return 1;
    }

    int startFadeIn(int param_0) {
        if (mpFader != NULL) {
            return mpFader->startFadeIn(param_0);
        }
        return 1;
    }

    void setTickRate(u32 rate) {
        mTickRate = rate;
        mFrameRate = 0;
    }

    void setDrawDoneMethod(EDrawDone drawDone) { mDrawDoneMethod = drawDone; }
    void setFader(JUTFader* fader) { mpFader = fader; }
    void setClearColor(JUtility::TColor color) { mClearColor = color; }

    static JFWDisplay* sManager;

private:
    /* 0x04 */ JUTFader* mpFader;
    /* 0x08 */ const _GXRenderModeObj* mpRenderMode;
    /* 0x0C */ JUtility::TColor mClearColor;
    /* 0x10 */ u32 mZClear;
    /* 0x14 */ JUTXfb* mXfbManager;
    /* 0x18 */ u16 mGamma;
    /* 0x1C */ EDrawDone  mDrawDoneMethod;
    /* 0x20 */ u16 mFrameRate;
    /* 0x24 */ u32 mTickRate;
    /* 0x28 */ bool mEnableAlpha;
    /* 0x2A */ u16 mClamp;
    /* 0x2C */ f32 mCombinationRatio;
    /* 0x30 */ u32 field_0x30;
    /* 0x34 */ u32 field_0x34;
    /* 0x38 */ u32 field_0x38;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ u8 field_0x3E;
};

inline void JUTChangeFrameBuffer(void* buffer, u16 height, u16 width) {
    JUTDirectPrint::getManager()->changeFrameBuffer(buffer, width, height);
}

static void JFWDrawDoneAlarm();
static void JFWGXDrawDoneAutoAbort();
static void JFWGXAbortAlarmHandler(OSAlarm* p_alarm, OSContext* p_ctx);
static void waitForTick(u32 p1, u16 p2);
static void diagnoseGpHang();

#endif /* JFWDISPLAY_H */
