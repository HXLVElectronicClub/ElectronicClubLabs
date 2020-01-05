#include "displayHelper.h"
#define TOTALDEVICENUM 16
#define CANVAS_WIDTH 32
#define CANVAS_HEIGHT 32

// double buffer for fast action
byte displayBuffer1[TOTALDEVICENUM*8];
byte displayBuffer2[TOTALDEVICENUM*8];
byte * displayBuffer = displayBuffer1;
byte * flipbuffer = displayBuffer2;

int deviceOrder[TOTALDEVICENUM] = {0,1,2,3,
                                  7,6,5,4,
                                  8,9,10,11,
                                  15,14,13,12};
//orientation, 1 up-side-down, 2, left-right
int deviceOrien[TOTALDEVICENUM] = {1,1,1,1,
                                  2,2,2,2,
                                  1,1,1,1,
                                  2,2,2,2};
LedControl *lchigh, *lclow;

void setLC(LedControl& high, LedControl& low) {
    lchigh = &high;
    lclow = & low;
}

LedControl* getLC(int dev) {
    if (dev > 8) return lchigh;
    else return lclow;
}

void setImage(int dev, byte *image) {
    for (int row=0;row<8;row++) {
        displayBuffer[dev*8+row] = image[row];
    }
}

// width, height, x, y is in bit
void setImage(byte* image, int width, int height,int x, int y) {
    byte xre = x%8;
    byte mask = (1 << xre)-1;
    for (int row=y;row<y+height && y<CANVAS_HEIGHT; row++) {
        int dev = (row/8)*4 + x/8;
        byte dataleft = getRowData(dev,row%8) & mask;
        for(int i= x; i < (x + width) && i<CANVAS_WIDTH;i+=8) {
            dev = (row/8)*4 + i/8;
            setRowData(dev, row%8, dataleft + image[(row-y)*width/8 + i/8] << xre);
            dataleft = image[row*width/8 + i/8] >> (8-xre);
        }
        if (x%8>0 && (x+width) < CANVAS_WIDTH) {
            setRowData(dev, row%8, dataleft + getRowData(dev,row%8) & ~mask );
        }
    }
}

// display a image which represented by a 64bit uint on a device
void setImage(int dev, uint64_t image) {
    byte imageb[64];
    uint64tobyte(image, imageb);
    setImage(dev,imageb);
}

void uint64tobyte(uint64_t in, byte *out) {
    for (int row=0; row<8; row++) {
        byte data=(in >> (row*8)) & 0xFF;
        out[row] = data;
    }
}

// scale = 1, 2, 4
void tile(byte *in, int scale) {
    for (int tileh=0; tileh<4/scale; tileh++) {
        for (int tilev=0; tilev<4/scale; tilev++) {
            for (int row=0; row<8;row++) {
                for (int col=0; col<8;col++) {
                    int dev = tileh*4*scale + tilev*scale + (row*scale/8)*4 + (col*scale/8);
                    int newrow = (row*scale)%8;
                    int newcol = (col*scale)%8;
                    for(int i=0;i<scale;i++) {
                        for (int j=0; j<scale;j++) {
                                bitWrite(displayBuffer[dev*8+newrow+i], newcol+j, bitRead(in[row],col));
                        }
                    }
                }
            }
        }
    }
}

void mirror(byte *in, byte *out) {
    for (int row=0; row<8; row++) {
        for (int col=0; col<8; col++) {
            bitWrite(out[row],7-col,bitRead(in[row],col));
        }
    }
}

void flip(byte *in, byte *out) {
    for (int row=0; row<8; row++) {
        out[row] = in[7-row];
    }
}

void setRowData(int dev, int row, byte val) {
    displayBuffer[dev*8+row] = val;    
}

void setColData(int dev, int col, byte val) {
    for(int row=0;row<8;row++) {
        bitWrite(displayBuffer[dev*8+row], 7-col, bitRead(val,row));
    }
}

byte getRowData(int dev, int row) {
    return displayBuffer[dev*8 + row];
}

byte getColData(int dev, int col) {
    byte data = 0;
    for(int row=0;row<8; row++) {
        bitWrite(data, row, bitRead(displayBuffer[dev*8+row],7-col));
    }
    return data;
}

// scroll a device content to a direction
// direction: 0: left, 1: right, 2: up, 4:down
// the shiftvalue will be 
void shift(int dev, int direction, byte& shiftout, byte shiftin) {
    if (direction == 1) {
        shiftout = getColData(dev, 0);
        for(int i=1; i<7;i++) {
            setColData(dev,i, getColData(dev,i+1));
        }
        setColData(dev,7,shiftin);
    } else if (direction == 0) {
        shiftout = getColData(dev, 7);
        for(int i=6; i>0;i--) {
            setColData(dev,i, getColData(dev,i-1));
        }
        setColData(dev,0,shiftin);
    } else if (direction == 2) {
        shiftout = getRowData(dev, 0);
        for(int i=1;i<7;i++) {
            setRowData(dev,i, getRowData(dev,i+1));
        }
        setRowData(dev,7,shiftin);
    } else if (direction == 4) {
        shiftout = getRowData(dev, 7);
        for(int i=6; i>0;i--) {
            setRowData(dev,i, getRowData(dev,i-1));
        }
        setRowData(dev,0,shiftin);
    }
}

// only display the difference by row
void display(int delaytime) {
#ifdef ARDUINO_AVR_UNO
  byte tmp[8],realimage[8],flippedreal[8];
    LedControl* lc;
    for(int dev=0;dev<16;dev++) {
      if (dev<4) {
        flip(&displayBuffer[dev*8],realimage);
        flip(&flipbuffer[dev*8],flippedreal);
        lc = lchigh;
      } else if (dev<8) {
        mirror(&displayBuffer[dev*8],realimage);
        mirror(&flipbuffer[dev*8],flippedreal);
        lc = lchigh;
      } else if (dev<12) {
        flip(&displayBuffer[dev*8],realimage);
        flip(&flipbuffer[dev*8],flippedreal);
        lc = lclow;
      } else {
        mirror(&displayBuffer[dev*8],realimage);
        mirror(&flipbuffer[dev*8],flippedreal);
        lc = lclow;
      }
      int realdev = deviceOrder[dev];
      if (realdev>7) realdev-=8;
        for(int row=0;row<8;row++) {
          if (realimage[row] != flippedreal[row]) {
            lc->setRow(realdev, row, realimage[row]);
          }
        }
    }

    if (delaytime>0) {
      delay(delaytime);
    }
#else
    for(int dev=0;dev<8;dev++) {
        for(int row=0;row<8;row++) {
            if (displayBuffer[dev*8+row] != flipbuffer[dev*8+row])
                lchigh->setRow(dev, row, displayBuffer[dev*8+row]);
            if (displayBuffer[dev*8+row+8*8] != flipbuffer[dev*8+row+8*8])
                lclow ->setRow(dev, row, displayBuffer[dev*8+row+8*8]);
        }
    }

    lchigh->print();
    lclow->print();
#endif

    // flip buffer
    byte * temp;
    temp = flipbuffer;
    flipbuffer = displayBuffer;
    displayBuffer = temp;
}
