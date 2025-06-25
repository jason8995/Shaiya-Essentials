#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CTexture
    {
        // D3DRTYPE_TEXTURE
        LPDIRECT3DTEXTURE9 texture;
        PAD(4);
        D2D_SIZE_F size;
        // 0x10

        static int CreateFromFile(CTexture* texture, const char* path, const char* fileName/*.tga*/, int w, int h);
    };
    #pragma pack(pop)

    static_assert(sizeof(CTexture) == 0x10);
}
