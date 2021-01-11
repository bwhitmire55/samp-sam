# samp-sam

[![sampctl](https://img.shields.io/badge/sampctl-samp--sam-2f2f2f.svg?style=for-the-badge)](https://github.com/bwhitmire55/samp-sam)

<!--
Short description of your library, why it's useful, some examples, pictures or
videos. Link to your forum release thread too.

Remember: You can use "forumfmt" to convert this readme to forum BBCode!

What the sections below should be used for:

`## Installation`: Leave this section un-edited unless you have some specific
additional installation procedure.

`## Testing`: Whether your library is tested with a simple `main()` and `print`,
unit-tested, or demonstrated via prompting the player to connect, you should
include some basic information for users to try out your code in some way.

And finally, maintaining your version number`:

* Follow [Semantic Versioning](https://semver.org/)
* When you release a new version, update `VERSION` and `git tag` it
* Versioning is important for sampctl to use the version control features

Happy Pawning!
-->

Create Surface-To-Air Missile sites with configurable settings

## Installation

Simply install to your project:

```bash
sampctl package install bwhitmire55/samp-sam
```

Include in your code and begin using the library:

```pawn
#include <sam>
```

## Functions

```pawn
/*
PARAMS:
    Float: x, Float: y, Float: z,           - position (x, y, z)
    Float: rotX, Float: rotY, Float: rotZ,  - rotation
    bool: createLauncher = true,            - create the launcher object
    bool: createBase = true,                - create the base of launcher object
    Float: speed = SAM_DEFAULT_SPEED,       - speed the missile will travel
    Float: range = SAM_DEFAULT_RANGE,       - range to start firing at targets
    Float: drawdistance = 0.00              - draw distance of objects

RETURNS:
    1 on success, otherwise 0
*/
SAM_Create(Float: x, Float: y, Float: z, Float: rotX, Float: rotY, Float: rotZ, bool: createLauncher = true, bool: createBase = true, Float: speed = SAM_DEFAULT_SPEED, Float: range = SAM_DEFAULT_RANGE, Float: drawdistance = 0.00);
```

```pawn
/*
PARAMS:
    id      - The SAM id to destroy

RETURNS:
    1 on success, otherwise 0
*/
SAM_Destroy(id);
```

```pawn
/*
PARAMS:
    id              - The SAM id to set
    Float: speed    - The speed for missiles to fire at

RETURNS:
    1 on success, otherwise 0
*/
SAM_SetSpeed(id, Float: speed);
```

```pawn
/*
PARAMS:
    id  - The SAM id to get the speed of

RETURNS:
    Missile travel speed on success, otherwise 0.0
*/
Float: SAM_GetSpeed(id);
```

```pawn
/*
PARAMS:
    id              - The SAM id to set
    Float: range    - The range to begin firing at targets

RETURNS:
    1 on success, otherwise 0
*/
SAM_SetRange(id, Float: range);
```

```pawn
/*
PARAMS:
    id  - The SAM id to get the range of

RETURNS:
    The firing range on success, otherwise 0.0
*/
Float: SAM_GetRange(id);
```

## Callbacks

```pawn
/*
PARAMS:
    samid       - The SAM id that is firing
    vehicleid   - The target vehicle of the missile
*/
public SAM_OnMissileFired(samid, vehicleid);
```

```pawn
/*
PARAMS:
    samid       - The SAM id that hit their target
    vehicleid   - The target vehicle of the missile that was hit
*/
public SAM_OnTargetHit(samid, vehicleid);
```

## Macros

```pawn
// Maximum number of concurrent SAM sites
#if !defined SAM_MAX_SITES
    #define SAM_MAX_SITES           (10)
#endif
```

```pawn
// Default speed a fired missile will travel
#if !defined SAM_DEFAULT_SPEED
    #define SAM_DEFAULT_SPEED       (50.0)
#endif
```

```pawn
// Default range a missile will be fired from
#if !defined SAM_DEFAULT_RANGE 
    #define SAM_DEFAULT_RANGE       (300.0)
#endif
```

```pawn
// Default range the missile will explode in relation to the target's position
#if !defined SAM_DEFAULT_EXP_RADIUS
    #define SAM_DEFAULT_EXP_RADIUS  (20.0)
#endif
```

```pawn
// Timer frequency to update the missile's position
#if !defined SAM_UPDATE_FREQUENCY
    #define SAM_UPDATE_FREQUENCY    (200)
#endif
```

## Dependencies

Streamer Plugin (https://www.github.com/samp-incognito/samp-streamer-plugin)