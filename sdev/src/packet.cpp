#include <util/util.h>
#include "include/main.h"
#include "include/static.h"
#include "include/shaiya/include/CCharacter.h"
using namespace shaiya;

namespace packet
{
    void hook_0x303(CCharacter* user)
    {
        if (!user->petType)
            user->pet = nullptr;

        if (!user->costumeType)
        {
            user->enableCostume = 0;
            user->costume.fill(-1);
        }

        if (!user->wingsType)
            user->wings = nullptr;
    }

    // Adds support for system message 509
    void hook_0x229(CCharacter* killer, uint killCount)
    {
        std::memcpy(g_var->msgTargetName.data(), killer->charName.data(), killer->charName.size());
        g_var->msgTargetName[killer->charName.size() - 1] = '\0';
        g_var->msgValue = killCount;
        Static::MsgTextOut(5, 509, 1);
    }
}

unsigned u0x59F8AF = 0x59F8AF;
void __declspec(naked) naked_0x59F896()
{
    __asm
    {
        // CPlayerData->charId
        mov edi,dword ptr ds:[0x90E2F4]
        // CCharacter->id
        cmp edi,[esi+0x34]
        jne wrong_appearance

        // sex, size, face, hair
        mov byte ptr ds:[0x914474],al
        mov byte ptr ds:[0x913472],cl
        mov byte ptr ds:[0x913471],dl
        mov byte ptr ds:[0x913470],bl

        wrong_appearance:
        mov ecx,esi
        jmp u0x59F8AF
    }
}

unsigned u0x5933FE = 0x5933FE;
void __declspec(naked) naked_0x5933F8()
{
    __asm
    {
        // original
        mov byte ptr[esi+0x1C9],al

        pushad

        push esi // user
        call packet::hook_0x303
        add esp,0x4

        popad

        jmp u0x5933FE
    }
}

unsigned u0x4EF315 = 0x4EF315;
void __declspec(naked) naked_0x4EF2F3()
{
    __asm
    {
        // original
        mov [eax+0x10],ebx

        pushad

        push ebx // killCount
        push edi // killer
        call packet::hook_0x229
        add esp,0x8

        popad

        jmp u0x4EF315
    }
}

unsigned u0x593D15 = 0x593D15;
unsigned u0x593D73 = 0x593D73;
void __declspec(naked) naked_0x593D0F()
{
    __asm
    {
        // original
        push 0x0 // arg #16
        cmp al,0xB
        jne _0x593D73

        push 0x0 // arg #15
        jmp u0x593D15

        _0x593D73:
        jmp u0x593D73
    }
}

void hook::packet()
{
    // disguise bug
    util::detour((void*)0x5933F8, naked_0x5933F8, 6);
    // appearance/sex change bug
    util::detour((void*)0x59F896, naked_0x59F896, 6);
    // revenge message 509
    util::detour((void*)0x4EF2F3, naked_0x4EF2F3, 5);
    // javelin attack bug (0x502 handler)
    util::detour((void*)0x593D0F, naked_0x593D0F, 6);

    // javelin attack bug

    // increase the stack offsets (see detour)
    util::write_memory((void*)0x593D46, 0x3C, 1);
    util::write_memory((void*)0x593D4D, 0x4C, 1);
    // remove argument #8
    util::write_memory((void*)0x593D4F, 0x90, 2);
}
