//
// sam.inc
//

/**
    TO-DO:
        Restructure data elements to remove monolithic enum
        Add map icon displaying missile position
 */

#if defined SAM_INC 
    #endinput
#endif 
#define SAM_INC 

#include <streamer>

#if !defined SAM_MAX_SITES
    #define SAM_MAX_SITES           (10)
#endif

#if !defined SAM_DEFAULT_SPEED
    #define SAM_DEFAULT_SPEED       (50.0)
#endif

#if !defined SAM_DEFAULT_RANGE 
    #define SAM_DEFAULT_RANGE       (300.0)
#endif

#if !defined SAM_DEFAULT_EXP_RADIUS
    #define SAM_DEFAULT_EXP_RADIUS  (20.0)
#endif

#if !defined SAM_UPDATE_FREQUENCY
    #define SAM_UPDATE_FREQUENCY    (200)
#endif

#define SAM_INVALID                 (-1)
#define SAM_OBJECT_BASE             (3885)
#define SAM_OBJECT_LAUNCHER         (18848)
#define SAM_OBJECT_MISSILE          (354)
#define SAM_OBJECT_SMOKE            (18716)

enum eSAM_data {
    bool: eSAM_Created,

    Float: eSAM_X,
    Float: eSAM_Y,
    Float: eSAM_Z,
    Float: eSAM_Speed,
    Float: eSAM_Range,
    bool: eSAM_Waiting,
    eSAM_TargetID,

    eSAM_BaseObject,
    eSAM_LauncherObject,
    eSAM_MissileObject,
    eSAM_SmokeObject,
    STREAMER_TAG_AREA: eSAM_DynamicArea,
    eSAM_Timer
};

static gSAM_Data[SAM_MAX_SITES][eSAM_data];
//static gTimer;

stock SAM_Create(
    Float: x, Float: y, Float: z, 
    Float: rotX, Float: rotY, Float: rotZ,
    bool: createLauncher = true,
    bool: createBase = true,
    Float: speed = SAM_DEFAULT_SPEED,
    Float: range = SAM_DEFAULT_RANGE,
    Float: drawdistance = 0.00
) {
    new slot = GetEmptySlot();
    if(slot == SAM_INVALID)
        return SAM_INVALID;

    gSAM_Data[slot][eSAM_Created] = true;
    gSAM_Data[slot][eSAM_X] = x;
    gSAM_Data[slot][eSAM_Y] = y;
    gSAM_Data[slot][eSAM_Z] = z;
    gSAM_Data[slot][eSAM_Speed] = speed;
    gSAM_Data[slot][eSAM_Range] = range;
    gSAM_Data[slot][eSAM_Waiting] = false;
    gSAM_Data[slot][eSAM_TargetID] = INVALID_VEHICLE_ID;

    gSAM_Data[slot][eSAM_DynamicArea] = CreateDynamicSphere(x, y, z, range);

    if(createBase)
        gSAM_Data[slot][eSAM_BaseObject] = CreateDynamicObject(SAM_OBJECT_BASE, x, y, z, rotX, rotY, rotZ, .drawdistance = drawdistance);
    
    if(createLauncher)
        gSAM_Data[slot][eSAM_LauncherObject] = CreateDynamicObject(SAM_OBJECT_LAUNCHER, x, y, z, rotX, rotY, rotZ, .drawdistance = drawdistance);
    return 1;
}

stock SAM_Destroy(id) {
    if((0 < id < SAM_MAX_SITES) && gSAM_Data[id][eSAM_Created]) {
        gSAM_Data[id][eSAM_Created] = false;
        gSAM_Data[id][eSAM_X] = 0.0;
        gSAM_Data[id][eSAM_Y] = 0.0;
        gSAM_Data[id][eSAM_Z] = 0.0;
        gSAM_Data[id][eSAM_Speed] = SAM_DEFAULT_SPEED;
        gSAM_Data[id][eSAM_Range] = SAM_DEFAULT_RANGE;
        gSAM_Data[id][eSAM_Waiting] = false;
        gSAM_Data[id][eSAM_TargetID] = INVALID_VEHICLE_ID;

        DestroyDynamicArea(gSAM_Data[id][eSAM_DynamicArea]);

        if(gSAM_Data[id][eSAM_BaseObject] != 0) {
            DestroyDynamicObject(gSAM_Data[id][eSAM_BaseObject]);
            gSAM_Data[id][eSAM_BaseObject] = 0;
        }

        if(gSAM_Data[id][eSAM_LauncherObject] != 0) {
            DestroyDynamicObject(gSAM_Data[id][eSAM_LauncherObject]);
            gSAM_Data[id][eSAM_LauncherObject] = 0;
        }

        if(gSAM_Data[id][eSAM_MissileObject] != 0) {
            DestroyObject(gSAM_Data[id][eSAM_MissileObject]);
            gSAM_Data[id][eSAM_MissileObject] = 0;
        }

        if(gSAM_Data[id][eSAM_SmokeObject] != 0) {
            DestroyDynamicObject(gSAM_Data[id][eSAM_SmokeObject]);
            gSAM_Data[id][eSAM_SmokeObject] = 0;
        }

        if(gSAM_Data[id][eSAM_Timer]) {
            KillTimer(gSAM_Data[id][eSAM_Timer]);
            gSAM_Data[id][eSAM_Timer] = 0;
        }
        return 1;
    }
    return 0;
}

stock SAM_SetSpeed(id, Float: speed) {
    if((0 < id < SAM_MAX_SITES) && gSAM_Data[id][eSAM_Created]) {
        gSAM_Data[id][eSAM_Speed] = speed;
        return 1;
    }
    return 0;
}

stock Float: SAM_GetSpeed(id) {
    if((0 < id < SAM_MAX_SITES) && gSAM_Data[id][eSAM_Created]) {
        return gSAM_Data[id][eSAM_Speed];
    }
    return 0.0;
}

stock SAM_SetRange(id, Float: range) {
    if((0 < id < SAM_MAX_SITES) && gSAM_Data[id][eSAM_Created]) {
        gSAM_Data[id][eSAM_Range] = range;
        return 1;
    }
    return 0;
}

stock Float: SAM_GetRange(id) {
    if((0 < id < SAM_MAX_SITES) && gSAM_Data[id][eSAM_Created]) {
        return gSAM_Data[id][eSAM_Range];
    }
    return 0.0;
}

static GetEmptySlot() {
    for(new i = 0; i < SAM_MAX_SITES; i++) {
        if(!gSAM_Data[i][eSAM_Created]) {
            return i;
        }
    }
    return SAM_INVALID;
}

static GetSAMIndexFromAreaID(STREAMER_TAG_AREA: areaid) {
    for(new i = 0; i < SAM_MAX_SITES; i++) {
        if(gSAM_Data[i][eSAM_DynamicArea] == areaid) {
            return i;
        }
    }
    return SAM_INVALID;
}

static bool: IsPlayerInAirVehicle(playerid) {
    new model = GetVehicleModel(GetPlayerVehicleID(playerid));
    switch(model) {
        case 460, 476, 511, 512, 513, 519, 520, 553, 577, 592, 593:
            return true;
        case 417, 425, 447, 469, 487, 488, 497, 548, 563:
            return true;
    }
    return false;
}

public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA: areaid) {  

    new idx = GetSAMIndexFromAreaID(areaid);
    if(idx != SAM_INVALID) {
        if(!gSAM_Data[idx][eSAM_Waiting]) {
            new Float: x, Float: y, Float: z;
            GetPlayerPos(playerid, x, y, z);
            if(IsPlayerInAirVehicle(playerid) && z > gSAM_Data[idx][eSAM_Z]) {
                gSAM_Data[idx][eSAM_MissileObject] = CreateDynamicObject(
                    SAM_OBJECT_MISSILE, 
                    gSAM_Data[idx][eSAM_X], gSAM_Data[idx][eSAM_Y], gSAM_Data[idx][eSAM_Z] + 5.0,
                    0.0, 90.0, 0.0
                );
                gSAM_Data[idx][eSAM_SmokeObject] = CreateDynamicObject(
                    SAM_OBJECT_SMOKE,
                    gSAM_Data[idx][eSAM_X], gSAM_Data[idx][eSAM_Y], gSAM_Data[idx][eSAM_Z],
                    0.0, 0.0, 0.0
                );
                AttachDynamicObjectToObject(
                    gSAM_Data[idx][eSAM_SmokeObject],
                    gSAM_Data[idx][eSAM_MissileObject],
                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0
                );

                gSAM_Data[idx][eSAM_Waiting] = true;
                gSAM_Data[idx][eSAM_TargetID] = GetPlayerVehicleID(playerid);
                gSAM_Data[idx][eSAM_Timer] = SetTimerEx("UpdateSAM", SAM_UPDATE_FREQUENCY, true, "i", idx);
                CallLocalFunction("SAM_OnMissileFired", "ii", idx, gSAM_Data[idx][eSAM_TargetID]);
            }
        }
    }
    return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
#undef OnPlayerEnterDynamicArea
#else 
    #define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea sam_OnPlayerEnterDynamicArea
forward sam_OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA: areaid);

forward UpdateSAM(id);
public UpdateSAM(id) {
    new Float: x, Float: y, Float: z;
    new Float: ox, Float: oy, Float: oz;
    GetVehiclePos(gSAM_Data[id][eSAM_TargetID], x, y, z);
    GetDynamicObjectPos(gSAM_Data[id][eSAM_MissileObject], ox, oy, oz);

    if(GetVehicleDistanceFromPoint(gSAM_Data[id][eSAM_TargetID], ox, oy, oz) < SAM_DEFAULT_EXP_RADIUS) {
        CreateExplosion(x, y, z, 7, 10.0);
        DestroyDynamicObject(gSAM_Data[id][eSAM_MissileObject]);
        DestroyDynamicObject(gSAM_Data[id][eSAM_SmokeObject]);
        KillTimer(gSAM_Data[id][eSAM_Timer]);

        CallLocalFunction("SAM_OnTargetHit", "ii", id, gSAM_Data[id][eSAM_TargetID]);

        gSAM_Data[id][eSAM_MissileObject] = 0;
        gSAM_Data[id][eSAM_SmokeObject] = 0;
        gSAM_Data[id][eSAM_TargetID] = INVALID_VEHICLE_ID;
        gSAM_Data[id][eSAM_Waiting] = false;
        gSAM_Data[id][eSAM_Timer] = 0;
    } else {
        MoveDynamicObject(gSAM_Data[id][eSAM_MissileObject], x, y, z, gSAM_Data[id][eSAM_Speed], 0.0, 0.0, 0.0);
    }
    return 1;
}

// --
/*
#pragma tabsize 0

#if defined FILTERSCRIPT
    public OnFilterScriptInit() {
#else 
    public OnGameModeInit() {
#endif
        gTimer = SetTimer("UpdateSAMs", SAM_UPDATE_FREQUENCY, true);
#if defined FILTERSCRIPT 
        return CallLocalFunction("sam_OnFilterScriptInit", "", "");
    }

    #if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
    #else 
        #define _ALS_OnFilterScriptInit
    #endif
    #define OnFilterScriptInit sam_OnFilterScriptInit
    forward sam_OnFilterScriptInit();
#else 
        return CallLocalFunction("sam_OnGameModeInit", "", "");
    }

    #if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
    #else 
        #define _ALS_OnGameModeInit
    #endif
    #define OnGameModeInit sam_OnGameModeInit
    forward sam_OnGameModeInit();
#endif

// -- 

#if defined FILTERSCRIPT
    public OnFilterScriptExit() {
#else 
    public OnGameModeExit() {
#endif
        KillTimer(gTimer);
#if defined FILTERSCRIPT 
        return CallLocalFunction("sam_OnFilterScriptExit", "", "");
    }

    #if defined _ALS_OnFilterScriptExit
    #undef OnFilterScriptExit
    #else 
        #define _ALS_OnFilterScriptExit
    #endif
    #define OnFilterScriptExit sam_OnFilterScriptExit
    forward sam_OnFilterScriptExit();
#else 
        return CallLocalFunction("sam_OnGameModeExit", "", "");
    }

    #if defined _ALS_OnGameModeExit
    #undef OnGameModeExit
    #else 
        #define _ALS_OnGameModeExit
    #endif
    #define OnGameModeExit sam_OnGameModeExit
    forward sam_OnGameModeExit();
#endif

#pragma tabsize 8
*/
// -- 

forward SAM_OnMissileFired(samid, vehicleid);
forward SAM_OnTargetHit(samid, vehicleid);