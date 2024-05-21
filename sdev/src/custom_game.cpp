#include <array>

#include <include/main.h>
#include <include/shaiya/static.h>
#include <include/shaiya/include/CNetwork.h>
#include <util/include/util.h>
using namespace shaiya;

const std::array<std::uint16_t, 21> weapon_step
{
    0, 7, 14, 21, 31, 41, 51, 64, 77, 90, 106, 122, 138, 157, 176, 195, 217, 239, 261, 286, 311
};

enum HelpMenuButtonIndex
{
    BasicPlay,
    PlayGuide,
    Interface,
    Blessing,
    BasicAction,
    PlayMode
};

void set_help_menu_npc(HelpMenuButtonIndex buttonIndex)
{
    // should not allow two windows at once
    if (g_static->global.windowType != WindowType::None)
    {
        Static::GetMsg(31, 806, 12);
        return;
    }

    switch (buttonIndex)
    {
    case BasicPlay:
    {
        g_static->global.npcType = NpcType::Blacksmith;
        g_static->global.npcTypeId = 40;
        // kill the icon and name for now (to-do?)
        g_static->global.npcIcon = -1;
        std::memset((char*)0x22AB7B8, 0, 128);
        g_static->global.windowType = WindowType::Blacksmith;
        break;
    }
    case PlayGuide:
    {
        g_static->global.npcType = NpcType::Merchant;
        g_static->global.npcTypeId = 248;
        g_static->global.npcIcon = -1;
        std::memset((char*)0x22AB7B8, 0, 128);
        g_static->global.windowType = WindowType::Recreation;
        break;
    }
    case Interface:
    {
        if (g_static->global.country == Country::Light)
        {
            std::uint16_t packet{ 0x218 };
            CNetwork::Send(&packet, 2);

            g_static->killLv = 0;
            g_static->deathLv = 0;

            g_static->global.npcType = NpcType::VetManager;
            g_static->global.npcTypeId = 1;
            g_static->global.npcIcon = -1;
            std::memset((char*)0x22AB7B8, 0, 128);
        }
        else
        {
            std::uint16_t packet{ 0x218 };
            CNetwork::Send(&packet, 2);

            g_static->killLv = 0;
            g_static->deathLv = 0;

            g_static->global.npcType = NpcType::VetManager;
            g_static->global.npcTypeId = 2;
            g_static->global.npcIcon = -1;
            std::memset((char*)0x22AB7B8, 0, 128);
        }

        break;
    }
    case Blessing:
    {
        if (g_static->global.country == Country::Light)
        {
            g_static->global.npcType = NpcType::Merchant;
            g_static->global.npcTypeId = 179;
            g_static->global.npcIcon = -1;
            std::memset((char*)0x22AB7B8, 0, 128);
            g_static->global.windowType = WindowType::BankTeller;
        }
        else
        {
            g_static->global.npcType = NpcType::Merchant;
            g_static->global.npcTypeId = 180;
            g_static->global.npcIcon = -1;
            std::memset((char*)0x22AB7B8, 0, 128);
            g_static->global.windowType = WindowType::BankTeller;
        }

        break;
    }
    case BasicAction:
    {
        if (g_static->global.country == Country::Light)
        {
            g_static->global.npcType = NpcType::GuildMaster;
            g_static->global.npcTypeId = 1;
            g_static->global.npcIcon = -1;
            std::memset((char*)0x22AB7B8, 0, 128);
            g_static->global.windowType = WindowType::GuildMaster;
        }
        else
        {
            g_static->global.npcType = NpcType::GuildMaster;
            g_static->global.npcTypeId = 2;
            g_static->global.npcIcon = -1;
            std::memset((char*)0x22AB7B8, 0, 128);
            g_static->global.windowType = WindowType::GuildMaster;
        }

        break;
    }
    case PlayMode:
    {
        g_static->global.npcType = NpcType::Merchant;
        g_static->global.npcTypeId = 437;
        g_static->global.npcIcon = -1;
        std::memset((char*)0x22AB7B8, 0, 128);
        g_static->global.windowType = WindowType::Merchant;
        break;
    }
    default:
        break;
    }
}

int get_weapon_step(std::uint8_t step)
{
    if (step >= weapon_step.size())
        return 0;

    return weapon_step[step];
}

unsigned u0x4B8766 = 0x4B8766;
void __declspec(naked) naked_0x4B8755()
{
    __asm
    {
        push eax // step
        call get_weapon_step
        add esp,0x4

        jmp u0x4B8766
    }
}

unsigned u0x522165 = 0x522165;
unsigned u0x51C070 = 0x51C070;
void __declspec(naked) naked_0x522160() 
{
    __asm 
    {
        cmp edi,0x5
        ja original

        pushad

        push edi
        call set_help_menu_npc
        add esp,0x4

        popad

        original:
        call u0x51C070
        jmp u0x522165
    }
}

void hook::custom_game()
{
    // weapon enchant bug
    util::detour((void*)0x4B8755, naked_0x4B8755, 5);
    // npc-to-go
    util::detour((void*)0x522160, naked_0x522160, 5);

    // npc-to-go bug workaround
    util::write_memory((void*)0x444129, 0xEB, 1);
    // speed recreation
    util::write_memory((void*)0x4C4D2F, 0x02, 1);
    // speed enhance
    util::write_memory((void*)0x501600, 0x02, 1);
    util::write_memory((void*)0x501602, 0x02, 1);
    util::write_memory((void*)0x501631, 0x02, 1);
    util::write_memory((void*)0x501633, 0x02, 1);
    util::write_memory((void*)0x501644, 0x03, 1);
    util::write_memory((void*)0x50164D, 0x03, 1);
    // show dungeon maps
    util::write_memory((void*)0x4D9497, 0x90, 2);
}