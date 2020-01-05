#ifndef DISPLAYHELPER_H
#define DISPLAYHELPER_H
#include "LedControl.h"

const uint64_t DIGITS[] = {
  0x7e1818181c181800,
  0x7e060c3060663c00,
  0x3c66603860663c00,
  0x30307e3234383000,
  0x3c6660603e067e00,
  0x3c66663e06663c00,
  0x1818183030667e00,
  0x3c66663c66663c00,
  0x3c66607c66663c00,
  0x3c66666e76663c00
};
const uint64_t SHAPES[] = {
  0x0010107c10100000,
  0x0000003c00000000,
  0x006c38fe386c0000,
  0x00060c1830600000,
  0x60660c1830660600,
  0x00003c003c000000,
  0x000000365c000000,
  0x0000008244281000,
  0x6030180c18306000,
  0x060c1830180c0600,
  0x6030181818306000,
  0x060c1818180c0600,
  0x7818181818187800,
  0x1e18181818181e00,
  0x7018180c18187000,
  0x0e18183018180e00,
  0x0606000000000000,
  0x0018180018180000,
  0x0c18180018180000,
  0x060c0c0c00000000,
  0x180018183c3c1800,
  0x1800183860663c00,
  0x003c421a3a221c00,
  0xfc66a6143c663c00,
  0x103c403804781000,
  0x6c6cfe6cfe6c6c00,
  0x383838fe7c381000,
  0x10387cfe38383800,
  0x10307efe7e301000,
  0x1018fcfefc181000,
  0xfefe7c7c38381000,
  0x1038387c7cfefe00,
  0x061e7efe7e1e0600,
  0xc0f0fcfefcf0c000,
  0x7c92aa82aa827c00,
  0x7ceed6fed6fe7c00,
  0x10387cfefeee4400,
  0x10387cfe7c381000,
  0x381054fe54381000,
  0x38107cfe7c381000,
  0x00387c7c7c380000,
  0xffc7838383c7ffff,
  0x0038444444380000,
  0xffc7bbbbbbc7ffff,
  0x0c12129ca0c0f000,
  0x38444438107c1000,
  0x060e0c0808281800,
  0x066eecc88898f000,
  0x105438ee38541000,
  0x1038541054381000,
  0x6666006666666600,
  0x002844fe44280000,
  0x00000000286c6c00,
  0x006030180c060000,
  0x0000000060303000,
  0x0000000c18181800,
  0xfe8282c66c381000
};
const uint64_t LETTERS[] = {
  0x6666667e66663c00,
  0x3e66663e66663e00,
  0x3c66060606663c00,
  0x3e66666666663e00,
  0x7e06063e06067e00,
  0x0606063e06067e00,
  0x3c66760606663c00,
  0x6666667e66666600,
  0x3c18181818183c00,
  0x1c36363030307800,
  0x66361e0e1e366600,
  0x7e06060606060600,
  0xc6c6c6d6feeec600,
  0xc6c6e6f6decec600,
  0x3c66666666663c00,
  0x06063e6666663e00,
  0x603c766666663c00,
  0x66361e3e66663e00,
  0x3c66603c06663c00,
  0x18181818185a7e00,
  0x7c66666666666600,
  0x183c666666666600,
  0xc6eefed6c6c6c600,
  0xc6c66c386cc6c600,
  0x1818183c66666600,
  0x7e060c1830607e00,
  0x0000000000000000,
  0x7c667c603c000000,
  0x3e66663e06060600,
  0x3c6606663c000000,
  0x7c66667c60606000,
  0x3c067e663c000000,
  0x0c0c3e0c0c6c3800,
  0x3c607c66667c0000,
  0x6666663e06060600,
  0x3c18181800180000,
  0x1c36363030003000,
  0x66361e3666060600,
  0x1818181818181800,
  0xd6d6feeec6000000,
  0x6666667e3e000000,
  0x3c6666663c000000,
  0x06063e66663e0000,
  0xf0b03c36363c0000,
  0x060666663e000000,
  0x3e403c027c000000,
  0x1818187e18180000,
  0x7c66666666000000,
  0x183c666600000000,
  0x7cd6d6d6c6000000,
  0x663c183c66000000,
  0x3c607c6666000000,
  0x3c0c18303c000000
};          

// set the LedControl object pointer
void setLC(LedControl& high, LedControl& low);
// get correct control obj according to dev number, <8 lchigh, else lclow
LedControl *getLC (int dev);
// get correct control obj according to dev number, <8 lchigh, else lclow
LedControl* getLC(int dev);
// scroll a row by offset in bits
// direction: 0-left to right 1-right to left
void scrollRow(int row, int direction, int offset);
// put an image on the full canvas
// image has width and height, position (x,y), both in bit
void setImage(byte* image, int width=32, int height=32, int x=0, int y=0);
// display a 8x8 image at one device, image is 8 byte array
void setImage(int dev, byte *image);
// display a 8x8 image at one device, image is a uint64_t;
void setImage(int dev, uint64_t image);
// get a row of a deive, returns a byte;
byte getRowData(int dev, int row);
// get a collumn of a device, returns a byte;
byte getColData(int dev, int col);
// set a device one row
void setRowData(int dev, int row, byte val);
// get device data, returns a byte array
byte* getDeviceData(int dev);
// convert uint64_t to byte array
void uint64tobyte(uint64_t in, byte *out);
// tile 8x8 image at given scale, scale can be 1, 2, 4, by default is 1
void tile(byte *in, int scale=1);
//compress
void compress(byte *in);
// mirror 8x8 image
void mirror(byte *in, byte *out);
// flip 8x8 image bottom up
void flip(byte *in, byte *out);
// scroll a device content to a direction
// direction: 0: left, 1: right, 2: up, 4:down
// the shiftvalue will be 
void shift(int device, int direction, byte& shiftout, byte shiftin=0);
// display image on devices
void display(int delaytime=0);
#endif
