#include "global.h"
#include "script_pokemon_util.h"
#include "overworld.h"
#include "constants/maps.h"
#include "event_data.h"
#include "field_fadetransition.h"
#include "quest_log.h"
#include "script.h"
#include "safari_zone.h"
#include "sound.h"

/**
 * static bool32 IsPlayerDefeated(u32 battleOutcome)
 * Si devuelve TRUE:
 *      derrota normal.
 * Si devuelve FALSE:
 *      Ganó/Huyó/teleport/capturó
*/



//static overworld.c
extern void CB2_Overworld(void);
extern void SetFieldVBlankCallback(void);
extern void do_load_map_stuff_loop(u8 *state);
extern void SetInitialPlayerAvatarStateWithDirection(u8 dirn);
extern void DoWhiteOut(void);
extern void FieldClearVBlankHBlankCallbacks(void);
extern void Overworld_ResetStateAfterWhitingOut(void);


static void New_Warp(s8 mapGroup, s8 mapNum, s8 x, s8 y);
static bool8 New_Respawn(void);


/**
 * Lo mejor sería cambiar esta función.
 * 080566a4 g 00000078 CB2_WhiteOut
*/
void CB2_WhiteOut_new(void)
{
    u8 val;
    bool8 isDefault;

    if (++gMain.state >= 120)
    {
        FieldClearVBlankHBlankCallbacks();
        StopMapMusic();
        ResetSafariZoneFlag();
        isDefault = New_Respawn();
        SetInitialPlayerAvatarStateWithDirection(DIR_NORTH);
        ScriptContext1_Init();
        ScriptContext2_Disable();
        if (isDefault)
            gFieldCallback = FieldCB_RushInjuredPokemonToCenter;
        val = 0;
        do_load_map_stuff_loop(&val);
        QuestLog_CutRecording();
        SetFieldVBlankCallback();
        SetMainCallback1(CB1_Overworld);
        SetMainCallback2(CB2_Overworld);
    }
}


#define MAPA(banco,mapa) (mapa | (banco << 8))

static bool8 New_Respawn(void)
{
    s8 banco = gSaveBlock1Ptr->location.mapGroup;
    s8 mapa  = gSaveBlock1Ptr->location.mapNum;

/*
    if (FlagGet(0x200))//si 0x200 es  verdadero
    {
        New_Warp(4,2,4,6);
        return FALSE;
    }

    if (VarGet(0x4000) == 1)
    {
        New_Warp(4,2,4,6);
        return FALSE;
    }
*/

    switch ( MAPA(banco,mapa) )
    {
    case MAP_ROUTE1:
        New_Warp(3,3,0x18,0xC);//ciudad celestes
        return FALSE;
        break;
    case MAPA(3,22):
        New_Warp(MAP_GROUP(PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(PALLET_TOWN_PLAYERS_HOUSE_2F), 6, 6);
        return FALSE;
        break;

    case MAPA(3,20)://MAP_ROUTE2
        //New_Warp(MAP_GROUP(PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(PALLET_TOWN_PLAYERS_HOUSE_2F), 6, 6);
        New_Warp(4,2,4,6);
        return FALSE;
        break;
    case MAPA(3,41)://MAP_ROUTE22
        //warp to VIRIDIAN CITY
        //banco=3   mapa=1   x=8  y=18
        New_Warp(3, 1, 8, 18);
        return FALSE;
        break;
    default:
        DoWhiteOut();
        return TRUE;
        break;
    }
}

static void New_Warp(s8 mapGroup, s8 mapNum, s8 x, s8 y)
{
    HealPlayerParty();
    Overworld_ResetStateAfterWhitingOut();
    SetWarpDestination(mapGroup, mapNum, -1, x, y);
    WarpIntoMap();
    gSpecialVar_0x8000 = 1;
}


