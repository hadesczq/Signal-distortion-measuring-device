/*本文件为8×16点阵西文字库文件,字的纵向8点构成一字节,上方的点在字节的低位,字符点阵四角按左上角→右上角→左下角→右下角取字*/
/*如你想在以后继续用HZDotReader打开文件,追加汉字点阵数据,请不要修改或增删所有注释*/
#include "CPU.H"
#define  CHAR_NUM  96

unsigned char _CONST_ charIndex[96] = {
0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f };

unsigned char _CONST_ chardot_8x16[1536] = {
/*    CHAR_20 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*!   CHAR_21 */
0x00,0x00,0x38,0xFC,0xFC,0x38,0x00,0x00,0x00,0x00,0x00,0x0D,0x0D,0x00,0x00,0x00,

/*"   CHAR_22 */
0x00,0x0E,0x1E,0x00,0x00,0x1E,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*#   CHAR_23 */
0x20,0xF8,0xF8,0x20,0xF8,0xF8,0x20,0x00,0x02,0x0F,0x0F,0x02,0x0F,0x0F,0x02,0x00,

/*$   CHAR_24 */
0x38,0x7C,0x44,0x47,0x47,0xCC,0x98,0x00,0x03,0x06,0x04,0x1C,0x1C,0x07,0x03,0x00,

/*%   CHAR_25 */
0x30,0x30,0x00,0x80,0xC0,0x60,0x30,0x00,0x0C,0x06,0x03,0x01,0x00,0x0C,0x0C,0x00,

/*&   CHAR_26 */
0x80,0xD8,0x7C,0xE4,0xBC,0xD8,0x40,0x00,0x07,0x0F,0x08,0x08,0x07,0x0F,0x08,0x00,

/*'   CHAR_27 */
0x00,0x10,0x1E,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*(   CHAR_28 */
0x00,0x00,0xF0,0xF8,0x0C,0x04,0x00,0x00,0x00,0x00,0x03,0x07,0x0C,0x08,0x00,0x00,

/*)   CHAR_29 */
0x00,0x00,0x04,0x0C,0xF8,0xF0,0x00,0x00,0x00,0x00,0x08,0x0C,0x07,0x03,0x00,0x00,

/**   CHAR_2A */
0x80,0xA0,0xE0,0xC0,0xC0,0xE0,0xA0,0x80,0x00,0x02,0x03,0x01,0x01,0x03,0x02,0x00,

/*+   CHAR_2B */
0x00,0x80,0x80,0xE0,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,

/*,   CHAR_2C */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x1E,0x0E,0x00,0x00,0x00,

/*-   CHAR_2D */
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*.   CHAR_2E */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00,

/*/   CHAR_2F */
0x00,0x00,0x00,0x80,0xC0,0x60,0x30,0x00,0x0C,0x06,0x03,0x01,0x00,0x00,0x00,0x00,

/*0   CHAR_30 */
0xF8,0xFC,0x04,0xC4,0x24,0xFC,0xF8,0x00,0x07,0x0F,0x09,0x08,0x08,0x0F,0x07,0x00,

/*1   CHAR_31 */
0x00,0x10,0x18,0xFC,0xFC,0x00,0x00,0x00,0x00,0x08,0x08,0x0F,0x0F,0x08,0x08,0x00,

/*2   CHAR_32 */
0x08,0x0C,0x84,0xC4,0x64,0x3C,0x18,0x00,0x0E,0x0F,0x09,0x08,0x08,0x0C,0x0C,0x00,

/*3   CHAR_33 */
0x08,0x0C,0x44,0x44,0x44,0xFC,0xB8,0x00,0x04,0x0C,0x08,0x08,0x08,0x0F,0x07,0x00,

/*4   CHAR_34 */
0xC0,0xE0,0xB0,0x98,0xFC,0xFC,0x80,0x00,0x00,0x00,0x00,0x08,0x0F,0x0F,0x08,0x00,

/*5   CHAR_35 */
0x7C,0x7C,0x44,0x44,0xC4,0xC4,0x84,0x00,0x04,0x0C,0x08,0x08,0x08,0x0F,0x07,0x00,

/*6   CHAR_36 */
0xF0,0xF8,0x4C,0x44,0x44,0xC0,0x80,0x00,0x07,0x0F,0x08,0x08,0x08,0x0F,0x07,0x00,

/*7   CHAR_37 */
0x0C,0x0C,0x04,0x84,0xC4,0x7C,0x3C,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00,

/*8   CHAR_38 */
0xB8,0xFC,0x44,0x44,0x44,0xFC,0xB8,0x00,0x07,0x0F,0x08,0x08,0x08,0x0F,0x07,0x00,

/*9   CHAR_39 */
0x38,0x7C,0x44,0x44,0x44,0xFC,0xF8,0x00,0x00,0x08,0x08,0x08,0x0C,0x07,0x03,0x00,

/*:   CHAR_3A */
0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x00,0x00,

/*;   CHAR_3B */
0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x08,0x0E,0x06,0x00,0x00,0x00,

/*<   CHAR_3C */
0x00,0x80,0xC0,0x60,0x30,0x18,0x08,0x00,0x00,0x00,0x01,0x03,0x06,0x0C,0x08,0x00,

/*=   CHAR_3D */
0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,

/*>   CHAR_3E */
0x00,0x08,0x18,0x30,0x60,0xC0,0x80,0x00,0x00,0x08,0x0C,0x06,0x03,0x01,0x00,0x00,

/*?   CHAR_3F */
0x18,0x1C,0x04,0xC4,0xE4,0x3C,0x18,0x00,0x00,0x00,0x00,0x0D,0x0D,0x00,0x00,0x00,

/*@   CHAR_40 */
0xF0,0xF8,0x08,0xC8,0xC8,0xF8,0xF0,0x00,0x07,0x0F,0x08,0x0B,0x0B,0x0B,0x01,0x00,

/*A   CHAR_41 */
0xE0,0xF0,0x98,0x8C,0x98,0xF0,0xE0,0x00,0x0F,0x0F,0x00,0x00,0x00,0x0F,0x0F,0x00,

/*B   CHAR_42 */
0x04,0xFC,0xFC,0x44,0x44,0xFC,0xB8,0x00,0x08,0x0F,0x0F,0x08,0x08,0x0F,0x07,0x00,

/*C   CHAR_43 */
0xF0,0xF8,0x0C,0x04,0x04,0x0C,0x18,0x00,0x03,0x07,0x0C,0x08,0x08,0x0C,0x06,0x00,

/*D   CHAR_44 */
0x04,0xFC,0xFC,0x04,0x0C,0xF8,0xF0,0x00,0x08,0x0F,0x0F,0x08,0x0C,0x07,0x03,0x00,

/*E   CHAR_45 */
0x04,0xFC,0xFC,0x44,0xE4,0x0C,0x1C,0x00,0x08,0x0F,0x0F,0x08,0x08,0x0C,0x0E,0x00,

/*F   CHAR_46 */
0x04,0xFC,0xFC,0x44,0xE4,0x0C,0x1C,0x00,0x08,0x0F,0x0F,0x08,0x00,0x00,0x00,0x00,

/*G   CHAR_47 */
0xF0,0xF8,0x0C,0x84,0x84,0x8C,0x98,0x00,0x03,0x07,0x0C,0x08,0x08,0x07,0x0F,0x00,

/*H   CHAR_48 */
0xFC,0xFC,0x40,0x40,0x40,0xFC,0xFC,0x00,0x0F,0x0F,0x00,0x00,0x00,0x0F,0x0F,0x00,

/*I   CHAR_49 */
0x00,0x00,0x04,0xFC,0xFC,0x04,0x00,0x00,0x00,0x00,0x08,0x0F,0x0F,0x08,0x00,0x00,

/*J   CHAR_4A */
0x00,0x00,0x00,0x04,0xFC,0xFC,0x04,0x00,0x07,0x0F,0x08,0x08,0x0F,0x07,0x00,0x00,

/*K   CHAR_4B */
0x04,0xFC,0xFC,0xC0,0xF0,0x3C,0x0C,0x00,0x08,0x0F,0x0F,0x00,0x01,0x0F,0x0E,0x00,

/*L   CHAR_4C */
0x04,0xFC,0xFC,0x04,0x00,0x00,0x00,0x00,0x08,0x0F,0x0F,0x08,0x08,0x0C,0x0E,0x00,

/*M   CHAR_4D */
0xFC,0xFC,0x38,0x70,0x38,0xFC,0xFC,0x00,0x0F,0x0F,0x00,0x00,0x00,0x0F,0x0F,0x00,

/*N   CHAR_4E */
0xFC,0xFC,0x38,0x70,0xE0,0xFC,0xFC,0x00,0x0F,0x0F,0x00,0x00,0x00,0x0F,0x0F,0x00,

/*O   CHAR_4F */
0xF0,0xF8,0x0C,0x04,0x0C,0xF8,0xF0,0x00,0x03,0x07,0x0C,0x08,0x0C,0x07,0x03,0x00,

/*P   CHAR_50 */
0x04,0xFC,0xFC,0x44,0x44,0x7C,0x38,0x00,0x08,0x0F,0x0F,0x08,0x00,0x00,0x00,0x00,

/*Q   CHAR_51 */
0xF8,0xFC,0x04,0x04,0x04,0xFC,0xF8,0x00,0x07,0x0F,0x08,0x0E,0x3C,0x3F,0x27,0x00,

/*R   CHAR_52 */
0x04,0xFC,0xFC,0x44,0xC4,0xFC,0x38,0x00,0x08,0x0F,0x0F,0x00,0x00,0x0F,0x0F,0x00,

/*S   CHAR_53 */
0x18,0x3C,0x64,0x44,0xC4,0x9C,0x18,0x00,0x06,0x0E,0x08,0x08,0x08,0x0F,0x07,0x00,

/*T   CHAR_54 */
0x00,0x1C,0x0C,0xFC,0xFC,0x0C,0x1C,0x00,0x00,0x00,0x08,0x0F,0x0F,0x08,0x00,0x00,

/*U   CHAR_55 */
0xFC,0xFC,0x00,0x00,0x00,0xFC,0xFC,0x00,0x07,0x0F,0x08,0x08,0x08,0x0F,0x07,0x00,

/*V   CHAR_56 */
0xFC,0xFC,0x00,0x00,0x00,0xFC,0xFC,0x00,0x01,0x03,0x06,0x0C,0x06,0x03,0x01,0x00,

/*W   CHAR_57 */
0xFC,0xFC,0x00,0x80,0x00,0xFC,0xFC,0x00,0x03,0x0F,0x0E,0x03,0x0E,0x0F,0x03,0x00,

/*X   CHAR_58 */
0x0C,0x3C,0xF0,0xC0,0xF0,0x3C,0x0C,0x00,0x0C,0x0F,0x03,0x00,0x03,0x0F,0x0C,0x00,

/*Y   CHAR_59 */
0x00,0x3C,0x7C,0xC0,0xC0,0x7C,0x3C,0x00,0x00,0x00,0x08,0x0F,0x0F,0x08,0x00,0x00,

/*Z   CHAR_5A */
0x1C,0x0C,0x84,0xC4,0x64,0x3C,0x1C,0x00,0x0E,0x0F,0x09,0x08,0x08,0x0C,0x0E,0x00,

/*[   CHAR_5B */
0x00,0x00,0xFC,0xFC,0x04,0x04,0x00,0x00,0x00,0x00,0x0F,0x0F,0x08,0x08,0x00,0x00,

/*\   CHAR_5C */
0x38,0x70,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0E,0x00,

/*]   CHAR_5D */
0x00,0x00,0x04,0x04,0xFC,0xFC,0x00,0x00,0x00,0x00,0x08,0x08,0x0F,0x0F,0x00,0x00,

/*^   CHAR_5E */
0x08,0x0C,0x06,0x03,0x06,0x0C,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*_   CHAR_5F */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,

/*`   CHAR_60 */
0x00,0x00,0x03,0x07,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*a   CHAR_61 */
0x00,0xA0,0xA0,0xA0,0xE0,0xC0,0x00,0x00,0x07,0x0F,0x08,0x08,0x07,0x0F,0x08,0x00,

/*b   CHAR_62 */
0x04,0xFC,0xFC,0x20,0x60,0xC0,0x80,0x00,0x08,0x0F,0x07,0x08,0x08,0x0F,0x07,0x00,

/*c   CHAR_63 */
0xC0,0xE0,0x20,0x20,0x20,0x60,0x40,0x00,0x07,0x0F,0x08,0x08,0x08,0x0C,0x04,0x00,

/*d   CHAR_64 */
0x80,0xC0,0x60,0x24,0xFC,0xFC,0x00,0x00,0x07,0x0F,0x08,0x08,0x07,0x0F,0x08,0x00,

/*e   CHAR_65 */
0xC0,0xE0,0xA0,0xA0,0xA0,0xE0,0xC0,0x00,0x07,0x0F,0x08,0x08,0x08,0x0C,0x04,0x00,

/*f   CHAR_66 */
0x40,0xF8,0xFC,0x44,0x0C,0x18,0x00,0x00,0x08,0x0F,0x0F,0x08,0x00,0x00,0x00,0x00,

/*g   CHAR_67 */
0xC0,0xE0,0x20,0x20,0xC0,0xE0,0x20,0x00,0x27,0x6F,0x48,0x48,0x7F,0x3F,0x00,0x00,

/*h   CHAR_68 */
0x04,0xFC,0xFC,0x40,0x20,0xE0,0xC0,0x00,0x08,0x0F,0x0F,0x00,0x00,0x0F,0x0F,0x00,

/*i   CHAR_69 */
0x00,0x00,0x20,0xEC,0xEC,0x00,0x00,0x00,0x00,0x00,0x08,0x0F,0x0F,0x08,0x00,0x00,

/*j   CHAR_6A */
0x00,0x00,0x00,0x00,0x20,0xEC,0xEC,0x00,0x00,0x30,0x70,0x40,0x40,0x7F,0x3F,0x00,

/*k   CHAR_6B */
0x04,0xFC,0xFC,0x80,0xC0,0x60,0x20,0x00,0x08,0x0F,0x0F,0x01,0x03,0x0E,0x0C,0x00,

/*l   CHAR_6C */
0x00,0x00,0x04,0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0x08,0x0F,0x0F,0x08,0x00,0x00,

/*m   CHAR_6D */
0xE0,0xE0,0x60,0xC0,0x60,0xE0,0xC0,0x00,0x0F,0x0F,0x00,0x0F,0x00,0x0F,0x0F,0x00,

/*n   CHAR_6E */
0x20,0xE0,0xC0,0x20,0x20,0xE0,0xC0,0x00,0x00,0x0F,0x0F,0x00,0x00,0x0F,0x0F,0x00,

/*o   CHAR_6F */
0xC0,0xE0,0x20,0x20,0x20,0xE0,0xC0,0x00,0x07,0x0F,0x08,0x08,0x08,0x0F,0x07,0x00,

/*p   CHAR_70 */
0x20,0xE0,0xC0,0x20,0x20,0xE0,0xC0,0x00,0x40,0x7F,0x7F,0x48,0x08,0x0F,0x07,0x00,

/*q   CHAR_71 */
0xC0,0xE0,0x20,0x20,0xC0,0xE0,0x20,0x00,0x07,0x0F,0x08,0x48,0x7F,0x7F,0x40,0x00,

/*r   CHAR_72 */
0x20,0xE0,0xC0,0x60,0x20,0x60,0xC0,0x00,0x08,0x0F,0x0F,0x08,0x00,0x00,0x00,0x00,

/*s   CHAR_73 */
0x40,0xE0,0xA0,0x20,0x20,0x60,0x40,0x00,0x04,0x0C,0x09,0x09,0x0B,0x0E,0x04,0x00,

/*t   CHAR_74 */
0x20,0x20,0xF8,0xFC,0x20,0x20,0x00,0x00,0x00,0x00,0x07,0x0F,0x08,0x0C,0x04,0x00,

/*u   CHAR_75 */
0xE0,0xE0,0x00,0x00,0xE0,0xE0,0x00,0x00,0x07,0x0F,0x08,0x08,0x07,0x0F,0x08,0x00,

/*v   CHAR_76 */
0x00,0xE0,0xE0,0x00,0x00,0xE0,0xE0,0x00,0x00,0x03,0x07,0x0C,0x0C,0x07,0x03,0x00,

/*w   CHAR_77 */
0xE0,0xE0,0x00,0x00,0x00,0xE0,0xE0,0x00,0x07,0x0F,0x0C,0x07,0x0C,0x0F,0x07,0x00,

/*x   CHAR_78 */
0x20,0x60,0xC0,0x80,0xC0,0x60,0x20,0x00,0x08,0x0C,0x07,0x03,0x07,0x0C,0x08,0x00,

/*y   CHAR_79 */
0xE0,0xE0,0x00,0x00,0x00,0xE0,0xE0,0x00,0x47,0x4F,0x48,0x48,0x68,0x3F,0x1F,0x00,

/*z   CHAR_7A */
0x60,0x60,0x20,0xA0,0xE0,0x60,0x20,0x00,0x0C,0x0E,0x0B,0x09,0x08,0x0C,0x0C,0x00,

/*{   CHAR_7B */
0x00,0x40,0x40,0xF8,0xBC,0x04,0x04,0x00,0x00,0x00,0x00,0x07,0x0F,0x08,0x08,0x00,

/*|   CHAR_7C */
0x00,0x00,0x00,0xBC,0xBC,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,

/*}   CHAR_7D */
0x00,0x04,0x04,0xBC,0xF8,0x40,0x40,0x00,0x00,0x08,0x08,0x0F,0x07,0x00,0x00,0x00,

/*~   CHAR_7E */
0x08,0x0C,0x04,0x0C,0x08,0x0C,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*   CHAR_7F */
0x80,0xC0,0x60,0x30,0x60,0xC0,0x80,0x00,0x07,0x07,0x04,0x04,0x04,0x07,0x07,0x00

};
unsigned char _CONST_ chardot_5x8[480] = {
/*    CHAR_20 */
0x00,0x00,0x00,0x00,0x00,

/*!   CHAR_21 */
0x00,0x00,0x5F,0x00,0x00,

/*"   CHAR_22 */
0x00,0x07,0x00,0x07,0x00,

/*#   CHAR_23 */
0x14,0x7F,0x14,0x7F,0x14,

/*$   CHAR_24 */
0x24,0x2E,0x7B,0x2A,0x12,

/*%   CHAR_25 */
0x23,0x13,0x08,0x64,0x62,

/*&   CHAR_26 */
0x36,0x49,0x56,0x20,0x50,

/*'   CHAR_27 */
0x00,0x04,0x03,0x01,0x00,

/*(   CHAR_28 */
0x00,0x1C,0x22,0x41,0x00,

/*)   CHAR_29 */
0x00,0x41,0x22,0x1C,0x00,

/**   CHAR_2A */
0x22,0x14,0x7F,0x14,0x22,

/*+   CHAR_2B */
0x08,0x08,0x7F,0x08,0x08,

/*,   CHAR_2C */
0x40,0x30,0x10,0x00,0x00,

/*-   CHAR_2D */
0x08,0x08,0x08,0x08,0x08,

/*.   CHAR_2E */
0x00,0x60,0x60,0x00,0x00,

/*/   CHAR_2F */
0x20,0x10,0x08,0x04,0x02,

/*0   CHAR_30 */
0x3E,0x51,0x49,0x45,0x3E,

/*1   CHAR_31 */
0x00,0x42,0x7F,0x40,0x00,

/*2   CHAR_32 */
0x62,0x51,0x49,0x49,0x46,

/*3   CHAR_33 */
0x21,0x41,0x49,0x4D,0x33,

/*4   CHAR_34 */
0x18,0x14,0x12,0x7F,0x10,

/*5   CHAR_35 */
0x27,0x45,0x45,0x45,0x39,

/*6   CHAR_36 */
0x3C,0x4A,0x49,0x49,0x31,

/*7   CHAR_37 */
0x01,0x71,0x09,0x05,0x03,

/*8   CHAR_38 */
0x36,0x49,0x49,0x49,0x36,

/*9   CHAR_39 */
0x46,0x49,0x49,0x29,0x1E,

/*:   CHAR_3A */
0x00,0x36,0x36,0x00,0x00,

/*;   CHAR_3B */
0x40,0x36,0x36,0x00,0x00,

/*<   CHAR_3C */
0x08,0x14,0x22,0x41,0x00,

/*=   CHAR_3D */
0x14,0x14,0x14,0x14,0x14,

/*>   CHAR_3E */
0x00,0x41,0x22,0x14,0x08,

/*?   CHAR_3F */
0x02,0x01,0x59,0x05,0x02,

/*@   CHAR_40 */
0x3E,0x41,0x5D,0x55,0x5E,

/*A   CHAR_41 */
0x7C,0x12,0x11,0x12,0x7C,

/*B   CHAR_42 */
0x7F,0x49,0x49,0x49,0x36,

/*C   CHAR_43 */
0x3E,0x41,0x41,0x41,0x22,

/*D   CHAR_44 */
0x7F,0x41,0x41,0x41,0x3E,

/*E   CHAR_45 */
0x7F,0x49,0x49,0x49,0x41,

/*F   CHAR_46 */
0x7F,0x09,0x09,0x09,0x01,

/*G   CHAR_47 */
0x3E,0x41,0x51,0x51,0x72,

/*H   CHAR_48 */
0x7F,0x08,0x08,0x08,0x7F,

/*I   CHAR_49 */
0x00,0x41,0x7F,0x41,0x00,

/*J   CHAR_4A */
0x20,0x40,0x41,0x3F,0x01,

/*K   CHAR_4B */
0x7F,0x08,0x14,0x22,0x41,

/*L   CHAR_4C */
0x7F,0x40,0x40,0x40,0x40,

/*M   CHAR_4D */
0x7F,0x02,0x0C,0x02,0x7F,

/*N   CHAR_4E */
0x7F,0x04,0x08,0x10,0x7F,

/*O   CHAR_4F */
0x3E,0x41,0x41,0x41,0x3E,

/*P   CHAR_50 */
0x7F,0x09,0x09,0x09,0x06,

/*Q   CHAR_51 */
0x3E,0x41,0x51,0x21,0x5E,

/*R   CHAR_52 */
0x7F,0x09,0x19,0x29,0x46,

/*S   CHAR_53 */
0x26,0x49,0x49,0x49,0x32,

/*T   CHAR_54 */
0x01,0x01,0x7F,0x01,0x01,

/*U   CHAR_55 */
0x3F,0x40,0x40,0x40,0x3F,

/*V   CHAR_56 */
0x1F,0x20,0x40,0x20,0x1F,

/*W   CHAR_57 */
0x7F,0x20,0x18,0x20,0x7F,

/*X   CHAR_58 */
0x63,0x14,0x08,0x14,0x63,

/*Y   CHAR_59 */
0x03,0x04,0x78,0x04,0x03,

/*Z   CHAR_5A */
0x61,0x51,0x49,0x45,0x43,

/*[   CHAR_5B */
0x7F,0x7F,0x41,0x41,0x00,

/*\   CHAR_5C */
0x02,0x04,0x08,0x10,0x20,

/*]   CHAR_5D */
0x00,0x41,0x41,0x7F,0x7F,

/*^   CHAR_5E */
0x04,0x02,0x7F,0x02,0x04,

/*_   CHAR_5F */
0x08,0x1C,0x2A,0x08,0x08,

/*`   CHAR_60 */
0x00,0x00,0x01,0x02,0x04,

/*a   CHAR_61 */
0x24,0x54,0x54,0x38,0x40,

/*b   CHAR_62 */
0x7F,0x28,0x44,0x44,0x38,

/*c   CHAR_63 */
0x38,0x44,0x44,0x44,0x08,

/*d   CHAR_64 */
0x38,0x44,0x44,0x28,0x7F,

/*e   CHAR_65 */
0x38,0x54,0x54,0x54,0x08,

/*f   CHAR_66 */
0x08,0x7E,0x09,0x09,0x02,

/*g   CHAR_67 */
0x98,0xA4,0xA4,0xA4,0x78,

/*h   CHAR_68 */
0x7F,0x08,0x04,0x04,0x78,

/*i   CHAR_69 */
0x00,0x00,0x79,0x00,0x00,

/*j   CHAR_6A */
0x00,0x80,0x88,0x79,0x00,

/*k   CHAR_6B */
0x7F,0x10,0x28,0x44,0x40,

/*l   CHAR_6C */
0x00,0x41,0x7F,0x40,0x00,

/*m   CHAR_6D */
0x78,0x04,0x78,0x04,0x78,

/*n   CHAR_6E */
0x04,0x78,0x04,0x04,0x78,

/*o   CHAR_6F */
0x38,0x44,0x44,0x44,0x38,

/*p   CHAR_70 */
0xFC,0x24,0x24,0x24,0x18,

/*q   CHAR_71 */
0x18,0x24,0x24,0x24,0xFC,

/*r   CHAR_72 */
0x04,0x78,0x04,0x04,0x08,

/*s   CHAR_73 */
0x48,0x54,0x54,0x54,0x24,

/*t   CHAR_74 */
0x04,0x3F,0x44,0x44,0x24,

/*u   CHAR_75 */
0x3C,0x40,0x40,0x3C,0x40,

/*v   CHAR_76 */
0x1C,0x20,0x40,0x20,0x1C,

/*w   CHAR_77 */
0x3C,0x40,0x3C,0x40,0x3C,

/*x   CHAR_78 */
0x44,0x28,0x10,0x28,0x44,

/*y   CHAR_79 */
0x9C,0xA0,0xA0,0x90,0x7C,

/*z   CHAR_7A */
0x44,0x64,0x54,0x4C,0x44,

/*{   CHAR_7B */
0x08,0x36,0x41,0x00,0x00,

/*|   CHAR_7C */
0x00,0x00,0x77,0x00,0x00,

/*}   CHAR_7D */
0x00,0x00,0x41,0x36,0x08,

/*~   CHAR_7E */
0x08,0x04,0x08,0x10,0x08,

/*   CHAR_7F */
0x55,0x2A,0x55,0x2A,0x55

};

