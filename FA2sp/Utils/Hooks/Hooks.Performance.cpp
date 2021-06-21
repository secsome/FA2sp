#include <Helpers/Macro.h>

#include "../../Logger.h"

struct ShapeHeaderStruct
{
    __int16 Type;
    __int16 Width;
    __int16 Height;
    __int16 FrameCount;
};

struct RGB
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

struct ShapeFrameHeader
{
    __int16 X;
    __int16 Y;
    __int16 Width;
    __int16 Height;
    __int16 Flags;
    RGB RadarColor;
    char padding[5];
    int DataOffset;
};

struct ShapeFileStruct
{
    ShapeHeaderStruct Header;
    ShapeFrameHeader* FrameHeaders;
};

//DEFINE_HOOK(525A60, sub_525A60_Debug, 7)
//{
//    GET_STACK(DWORD, dwCallerAddress, 0x0);
//    GET_STACK(int, nFrame, 0x4);
//    GET_STACK(ShapeFrameHeader*, pFrameHeader, 0x8);
//    Logger::Debug("Caller = %p, nFrame = %d\n", dwCallerAddress, nFrame);
//    Logger::Debug("pFrameHeader Info : \n");
//    Logger::Debug("X = %d, Y = %d, Width = %d, Height = %d, Flags = %d, [R G B] = [%d %d %d], offset = %d\n",
//        pFrameHeader->X, pFrameHeader->Y, pFrameHeader->Width, pFrameHeader->Height, pFrameHeader->Flags,
//        pFrameHeader->RadarColor.R, pFrameHeader->RadarColor.G, pFrameHeader->RadarColor.B, pFrameHeader->DataOffset);
//    return 0;
//}

//DEFINE_HOOK(480966, sub_480963_Debugger, 9)
//{
//    Logger::Debug("%c\n", R->BL());
//    return 0;
//}

//DEFINE_HOOK(525A9A, sub_525A60_Optimize, 8)
//{
//    /*GET_STACK(int, nFrame, STACK_OFFS(0x24, -0x4));
//    GET_STACK(ShapeFrameHeader*, pFrameHeader, STACK_OFFS(0x24, -0x8));
//    
//    Logger::Debug("nFrame = %d, pFrame [W,H] = [%d,%d]\n", nFrame, pFrameHeader->Width, pFrameHeader->Height);
//
//
//    return 0;*/
//    //__asm
//    //{
//    //    lea     eax, [eax + eax * 2]
//    //    push    edi
//    //    lea     edi, pFrameHeader
//    //    lea     esi, [ecx + eax * 8 + 8]
//    //    mov     ecx, 6
//    //    mov     eax, 1 // return true
//    //    rep movsd
//    //    pop     edi
//    //}
//    //return 0x525AC0;
//}