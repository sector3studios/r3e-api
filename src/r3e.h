#pragma once

#include <stdint.h>

typedef int32_t r3e_int32;
typedef float r3e_float32;
typedef double r3e_float64;

#define R3E_SHARED_MEMORY_NAME "$Race$"

typedef enum
{
    R3E_TREAD_LOC_LEFT = 0,
    R3E_TREAD_LOC_CENTER,
    R3E_TREAD_LOC_RIGHT,
    R3E_TREAD_LOC_SIZE
} r3e_treadlocation;

typedef enum
{
    R3E_TIRE_LOC_FL = 0,
    R3E_TIRE_LOC_FR,
    R3E_TIRE_LOC_RL,
    R3E_TIRE_LOC_RR,
    R3E_TIRE_LOC_SIZE
} r3e_tirelocation;

typedef enum
{
    R3E_ORI_PITCH = 0,
    R3E_ORI_YAW,
    R3E_ORI_ROLL,
    R3E_ORI_SIZE
} r3e_orientation;

typedef enum
{
    R3E_VEC3_X = 0,
    R3E_VEC3_Y,
    R3E_VEC3_Z,
    R3E_VEC3_SIZE
} r3e_vec3;

// High precision data for player's vehicle only
typedef struct
{
    // Virtual physics time
    // Unit: Ticks (1 tick = 1/400th of a second)
    r3e_int32 gameSimulationTicks;

    // Virtual physics time
    // Unit: Seconds
    r3e_float64 gameSimulationTime;

    // Car world-space position
    r3e_float64 position[R3E_VEC3_SIZE];

    // Car world-space velocity
    // Unit: Meter per second (m/s)
    r3e_float64 velocity[R3E_VEC3_SIZE];

    // Car world-space acceleration
    // Unit: Meter per second squared (m/s^2)
    r3e_float64 acceleration[R3E_VEC3_SIZE];

    // Car local-space acceleration
    // Unit: Meter per second squared (m/s^2)
    r3e_float64 localAcceleration[R3E_VEC3_SIZE];

    // Car body orientation
    // Unit: Euler angles
    r3e_float64 orientation[R3E_VEC3_SIZE];

    // Car body rotation
    r3e_float64 rotation[R3E_VEC3_SIZE];

    // Car body angular acceleration (torque divided by inertia)
    r3e_float64 angularAcceleration[R3E_VEC3_SIZE];

    // Acceleration of driver's body in local coordinates
    r3e_float64 driverBodyAcceleration[R3E_VEC3_SIZE];
} r3e_playerdata;

typedef struct
{
    // Deprecated
    r3e_float32 userInput[6];

    // Engine speed
    // Unit: Radians per second (rad/s)
    r3e_float32 engineRps;

    // Maximum engine speed
    // Unit: Radians per second (rad/s)
    r3e_float32 maxEngineRps;

    // Unit: Kilopascals (KPa)
    r3e_float32 fuelPressure;

    // Current amount of fuel in the tank(s)
    // Unit: Liters (l)
    r3e_float32 fuelLeft;

    // Maximum capacity of fuel tank(s)
    // Unit: Liters (l)
    r3e_float32 fuelCapacity;

    // Unit: Kelvin (K)
    r3e_float32 engineWaterTemp;

    // Unit: Kelvin (K)
    r3e_float32 engineOilTemp;

    // Unit: Kilopascals (KPa)
    r3e_float32 engineOilPressure;

    // Unit: Meter per second (m/s)
    r3e_float32 carSpeed;

    // Total number of laps in the race, or -1 if player is not in race mode (practice, test mode, etc.)
    r3e_int32 numberOfLaps;

    // How many laps the player has completed. If this value is 6, the player is on his 7th lap. -1 = n/a
    r3e_int32 completedLaps;

    // Unit: Seconds (-1.0 = none)
    r3e_float32 lapTimeBest;

    // Unit: Seconds (-1.0 = none)
    r3e_float32 lapTimePrevious;

    // Unit: Seconds (-1.0 = none)
    r3e_float32 lapTimeCurrent;

    // Current position (1 = first place)
    r3e_int32 position;

    // Number of cars (including the player) in the race
    r3e_int32 numCars;

    // -2 = no data
    // -1 = reverse,
    //  0 = neutral
    //  1 = first gear
    // (... up to 7th)
    r3e_int32 gear;

    // Temperature of three points across the tread of each tire
    // Unit: Kelvin (K)
    r3e_float32 tireTemp[R3E_TIRE_LOC_SIZE][R3E_TREAD_LOC_SIZE];

    // Number of penalties pending for the player
    r3e_int32 numPenalties;

    // Physical location of car's center of gravity in world space (X, Y, Z) (Y = up)
    r3e_float32 carCgLoc[R3E_VEC3_SIZE];

    // Pitch, yaw, roll
    // Unit: Radians (rad)
    r3e_float32 carOrientation[R3E_ORI_SIZE];

    // Acceleration in three axes (X, Y, Z) of car body in local-space.
    // From car center, +X=left, +Y=up, +Z=back.
    // Unit: Meter per second squared (m/s^2)
    r3e_float32 localAcceleration[R3E_VEC3_SIZE];

    // -1 = no data for DRS
    //  0 = not available
    //  1 = available
    r3e_int32 drsAvailable;

    // -1 = no data for DRS
    //  0 = not engaged
    //  1 = engaged
    r3e_int32 drsEngaged;

    // High precision data for player's vehicle only
    r3e_playerdata player;
} r3e_shared;