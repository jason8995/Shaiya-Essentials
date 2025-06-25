#include "include/static.h"
using namespace shaiya;

void Static::DrawRect(D3DCOLOR argb, int x, int y, int w, int h)
{
    typedef void(__cdecl* LPFN)(D3DCOLOR, int, int, int, int);
    (*(LPFN)0x4B6180)(argb, x, y, w, h);
}

bool Static::PlayWav(const char* wavFileName, D3DVECTOR* origin, float volume, bool repeat)
{
    typedef bool(__thiscall* LPFN)(void*, const char*, D3DVECTOR*, float, bool);
    return (*(LPFN)0x56C650)((void*)0x22B4030, wavFileName, origin, volume, repeat);
}

void Static::MsgTextOut(int messageType, int messageNumber, int unknown)
{
    typedef void(__cdecl* LPFN)(int, int, int);
    (*(LPFN)0x423150)(messageType, messageNumber, unknown);
}

D3DXMATRIX* Static::D3DXMatrixMultiply(D3DXMATRIX* out, D3DXMATRIX* mat1, D3DXMATRIX* mat2)
{
    typedef D3DXMATRIX* (__stdcall* LPFN)(D3DMATRIX*, D3DMATRIX*, D3DMATRIX*);
    return (*(LPFN)0x6594D1)(out, mat1, mat2);
}

D3DXMATRIX* Static::D3DXMatrixRotationY(D3DXMATRIX* out, float angle)
{
    typedef D3DXMATRIX* (__stdcall* LPFN)(D3DMATRIX*, float);
    return (*(LPFN)0x659F8E)(out, angle);
}

D3DXMATRIX* Static::D3DXMatrixRotationZ(D3DXMATRIX* out, float angle)
{
    typedef D3DXMATRIX* (__stdcall* LPFN)(D3DMATRIX*, float);
    return (*(LPFN)0x65A031)(out, angle);
}

void* Static::malloc(size_t size)
{
    typedef void* (__cdecl* LPFN)(size_t);
    return (*(LPFN)0x6307F3)(size);
}
