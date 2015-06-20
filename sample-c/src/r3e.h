#pragma once

#include <stdint.h>

typedef int32_t r3e_int32;
typedef float r3e_float32;
typedef double r3e_float64;

#define R3E_SHARED_MEMORY_NAME "$Race$"

// Make sure everything is tightly packed, to prevent the compiler from adding any hidden padding
#pragma pack(push, 1)

typedef struct
{
    r3e_float32 x;
    r3e_float32 y;
    r3e_float32 z;
} r3e_vec3_f32;

typedef struct
{
    r3e_float64 x;
    r3e_float64 y;
    r3e_float64 z;
} r3e_vec3_f64;

typedef struct
{
    r3e_float32 pitch;
    r3e_float32 yaw;
    r3e_float32 roll;
} r3e_orientation_f32;

typedef struct
{
    r3e_float32 frontleft_left;
    r3e_float32 frontleft_center;
    r3e_float32 frontleft_right;

    r3e_float32 frontright_left;
    r3e_float32 frontright_center;
    r3e_float32 frontright_right;

    r3e_float32 rearleft_left;
    r3e_float32 rearleft_center;
    r3e_float32 rearleft_right;

    r3e_float32 rearright_left;
    r3e_float32 rearright_center;
    r3e_float32 rearright_right;
} r3e_tiretemps;

// High precision data for player's vehicle only
typedef struct
{
    // Virtual physics time
    // Unit: Ticks (1 tick = 1/400th of a second)
    r3e_int32 game_simulation_ticks;

    // Padding to accomodate for legacy alignment
    r3e_int32 _padding1;

    // Virtual physics time
    // Unit: Seconds
    r3e_float64 game_simulation_time;

    // Car world-space position
    r3e_vec3_f64 position;

    // Car world-space velocity
    // Unit: Meter per second (m/s)
    r3e_vec3_f64 velocity;

    // Car world-space acceleration
    // Unit: Meter per second squared (m/s^2)
    r3e_vec3_f64 acceleration;

    // Car local-space acceleration
    // Unit: Meter per second squared (m/s^2)
    r3e_vec3_f64 local_acceleration;

    // Car body orientation
    // Unit: Euler angles
    r3e_vec3_f64 orientation;

    // Car body rotation
    r3e_vec3_f64 rotation;

    // Car body angular acceleration (torque divided by inertia)
    r3e_vec3_f64 angular_acceleration;

    // Acceleration of driver's body in local coordinates
    r3e_vec3_f64 driver_body_acceleration;
} r3e_playerdata;

typedef struct
{
    // Deprecated
    r3e_float32 user_input[6];

    // Engine speed
    // Unit: Radians per second (rad/s)
    r3e_float32 engine_rps;

    // Maximum engine speed
    // Unit: Radians per second (rad/s)
    r3e_float32 max_engine_rps;

    // Unit: Kilopascals (KPa)
    r3e_float32 fuel_pressure;

    // Current amount of fuel in the tank(s)
    // Unit: Liters (l)
    r3e_float32 fuel_left;

    // Maximum capacity of fuel tank(s)
    // Unit: Liters (l)
    r3e_float32 fuel_capacity;

    // Unit: Kelvin (K)
    r3e_float32 engine_water_temp;

    // Unit: Kelvin (K)
    r3e_float32 engine_oil_temp;

    // Unit: Kilopascals (KPa)
    r3e_float32 engine_oil_pressure;

    // Unit: Meter per second (m/s)
    r3e_float32 car_speed;

    // Total number of laps in the race, or -1 if player is not in race mode (practice, test mode, etc.)
    r3e_int32 number_of_laps;

    // How many laps the player has completed. If this value is 6, the player is on his 7th lap. -1 = n/a
    r3e_int32 completed_laps;

    // Unit: Seconds (-1.0 = none)
    r3e_float32 lap_time_best;

    // Unit: Seconds (-1.0 = none)
    r3e_float32 lap_time_previous;

    // Unit: Seconds (-1.0 = none)
    r3e_float32 lap_time_current;

    // Current position (1 = first place)
    r3e_int32 position;

    // Number of cars (including the player) in the race
    r3e_int32 num_cars;

    // -2 = no data
    // -1 = reverse,
    //  0 = neutral
    //  1 = first gear
    // (... up to 7th)
    r3e_int32 gear;

    // Temperature of three points across the tread of each tire
    // Unit: Kelvin (K)
    r3e_tiretemps tire_temps;

    // Number of penalties pending for the player
    r3e_int32 num_penalties;

    // Physical location of car's center of gravity in world space (X, Y, Z) (Y = up)
    r3e_vec3_f32 car_cg_location;

    // Pitch, yaw, roll
    // Unit: Radians (rad)
    r3e_orientation_f32 car_orientation;

    // Acceleration in three axes (X, Y, Z) of car body in local-space.
    // From car center, +X=left, +Y=up, +Z=back.
    // Unit: Meter per second squared (m/s^2)
    r3e_vec3_f32 local_acceleration;

    // -1 = no data for DRS
    //  0 = not available
    //  1 = available
    r3e_int32 drs_available;

    // -1 = no data for DRS
    //  0 = not engaged
    //  1 = engaged
    r3e_int32 drs_engaged;

    // Padding to accomodate for legacy alignment
    r3e_int32 _padding1;

    // High precision data for player's vehicle only
    r3e_playerdata player;
} r3e_shared;

#pragma pack(pop)