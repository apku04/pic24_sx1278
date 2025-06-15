#ifndef MACLAYER_DEFS_H
#define MACLAYER_DEFS_H

typedef enum {
    WAIT_DIFS = 0,
    PERFORM_BACKOFF = 1,
    SEND_RTS = 2,
    WAIT_FOR_CTS = 3,
    SEND_PAY = 4,
    WAIT_FOR_ACK = 5
} CSMA_CMD;

typedef struct {
    PacketBuffer *pktRxBuf;
    PacketBuffer *pktTxBuf;
    char headerSize;
    char mBcast;
    char mAddr;
    char macFrameSize;
    char mSlotTime;
    char mSIFSTime;
    char mDIFSTtime;
    char mCWmin;
    char mCWmax;
    char mCurrentCW;
    char mMACdrop;
    char mPAYTimeOut;
    unsigned int mACKTimeOut;
    int mBackoffTimer;
    char mGotACK;
    char mGotPAY;
    char mExpectPAY;
    char mExpectACK;
    char mUseCSMA;
} mlme;

#endif // MACLAYER_DEFS_H
