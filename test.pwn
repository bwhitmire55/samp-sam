#include <a_samp>

//#define FILTERSCRIPT
#include "sam.inc"

public OnGameModeInit() {

    new sam = SAM_Create(
        0.00, 0.00, 0.00,       // position (x, y, z)
        0.00, 0.00, 0.00,       // rotation
        true,                   // create the launcher object
        true,                   // create the base of launcher object
        SAM_DEFAULT_SPEED,      // speed the missile will travel
        SAM_DEFAULT_RANGE,      // range to start firing at targets
        0.0                     // draw distance of object
    );

    SAM_SetSpeed(sam, 5.0);
    SAM_SetRange(sam, 10.0);

    printf("Speed: %0.2f", SAM_GetSpeed(sam));
    printf("Range: %0.2f", SAM_GetRange(sam));

    SAM_Destroy(sam);
    return 1;
}

public OnGameModeExit() {
    // test als
    return 1;
}

public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA: areaid) {
    // test als
    return 1;
}