#pragma once

#include <stdint.h>

typedef int32_t r3e_int32;
typedef float r3e_float32;
typedef double r3e_float64;

#define R3E_SHARED_MEMORY_NAME "$Race$"

typedef enum
{
    R3E_SESSION_UNAVAILABLE = -1,
    R3E_SESSION_PRACTICE = 0,
    R3E_SESSION_QUALIFY = 1,
    R3E_SESSION_RACE = 2,
} r3e_session;

typedef enum
{
    R3E_SESSION_PHASE_UNAVAILABLE = -1,

    // Currently in garage
    R3E_SESSION_PHASE_GARAGE = 1,

    // Gridwalk or track walkthrough
    R3E_SESSION_PHASE_GRIDWALK = 2,

    // Formation lap, rolling start etc.
    R3E_SESSION_PHASE_FORMATION = 3,

    // Countdown to race is ongoing
    R3E_SESSION_PHASE_COUNTDOWN = 4,

    // Race is ongoing
    R3E_SESSION_PHASE_GREEN = 5,

    // End of session
    R3E_SESSION_PHASE_CHECKERED = 6,
} r3e_session_phase;

typedef enum
{
    R3E_CONTROL_UNAVAILABLE = -1,

    // Controlled by the actual player
    R3E_CONTROL_PLAYER = 0,

    // Controlled by AI
    R3E_CONTROL_AI = 1,

    // Controlled by a network entity of some sort
    R3E_CONTROL_REMOTE = 2,

    // Controlled by a replay or ghost
    R3E_CONTROL_REPLAY = 3,
} r3e_control;

typedef enum
{
    R3E_PIT_WINDOW_UNAVAILABLE = -1,

    // Pit stops are not enabled for this session
    R3E_PIT_WINDOW_DISABLED = 0,

    // Pit stops are enabled, but you're not allowed to perform one right now
    R3E_PIT_WINDOW_CLOSED = 1,

    // Allowed to perform a pit stop now
    R3E_PIT_WINDOW_OPEN = 2,

    // Currently performing the pit stop changes (changing driver, etc.)
    R3E_PIT_WINDOW_STOPPED = 3,

    // After the current mandatory pitstop have been completed
    R3E_PIT_WINDOW_COMPLETED = 4,
} r3e_pit_window;

typedef enum
{
    R3E_TIRE_TYPE_UNAVAILABLE = -1,
    R3E_TIRE_TYPE_OPTION = 0,
    R3E_TIRE_TYPE_PRIME = 1,
} r3e_tire_type;

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
} r3e_ori_f32;

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
} r3e_tire_temps;

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

    // Reserved for future implementation of driver_body_acceleration
    r3e_vec3_f64 reserved1;
} r3e_playerdata;

typedef struct
{
    // Whether yellow flag is currently active
    // -1 = no data
    //  0 = not active
    //  1 = active
    // Note: Uses legacy code and isn't really supported at the moment. Use at your own risk.
    r3e_int32 yellow;

    // Whether blue flag is currently active
    // -1 = no data
    //  0 = not active
    //  1 = active
    // Note: Uses legacy code and isn't really supported at the moment. Use at your own risk.
    r3e_int32 blue;

    // Whether black flag is currently active
    // -1 = no data
    //  0 = not active
    //  1 = active
    r3e_int32 black;
} r3e_flags;

typedef struct
{
    // Range: 0.0 - 1.0
    // Note: -1.0 = N/A
    r3e_float32 engine;

    // Range: 0.0 - 1.0
    // Note: -1.0 = N/A
    r3e_float32 transmission;

    // Range: 0.0 - 1.0
    // Note: A bit arbitrary at the moment. 0.0 doesn't necessarily mean completely destroyed.
    // Note: -1.0 = N/A
    r3e_float32 aerodynamics;

    // Tire wear
    // Range: 0.0 - 1.0
    // Note: -1.0 = N/A
    r3e_float32 tire_front_left;
    r3e_float32 tire_front_right;
    r3e_float32 tire_rear_left;
    r3e_float32 tire_rear_right;
} r3e_car_damage;

typedef struct
{
    r3e_float32 front_left;
    r3e_float32 front_right;
    r3e_float32 rear_left;
    r3e_float32 rear_right;
} r3e_tire_pressure;

typedef struct
{
    r3e_float32 front_left;
    r3e_float32 front_right;
    r3e_float32 rear_left;
    r3e_float32 rear_right;
} r3e_brake_temps;

typedef struct
{
    r3e_int32 drive_through;
    r3e_int32 stop_and_go;
    r3e_int32 pit_stop;
    r3e_int32 time_deduction;
    r3e_int32 slow_down;
} r3e_cut_track_penalties;

typedef struct
{
    // Note: Deprecated, doesn't get set
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

    // Unit: Celsius (C)
    r3e_float32 engine_water_temp;

    // Unit: Celsius (C)
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
    r3e_float32 lap_time_best_self;

    // Unit: Seconds (-1.0 = none)
    r3e_float32 lap_time_previous_self;

    // Unit: Seconds (-1.0 = none)
    r3e_float32 lap_time_current_self;

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
    // Unit: Celsius (C)
    r3e_tire_temps tire_temps;

    // Number of penalties pending for the player
    // Note: See the 'penalties' field
    r3e_int32 num_penalties;

    // Physical location of car's center of gravity in world space (X, Y, Z) (Y = up)
    r3e_vec3_f32 car_cg_location;

    // Pitch, yaw, roll
    // Unit: Radians (rad)
    r3e_ori_f32 car_orientation;

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

    // The current race event index, for championships with multiple events
    // Note: 0-indexed, -1 = N/A
    r3e_int32 event_index;

    // Which session the player is in (practice, qualifying, race, etc.)
    // Note: See the r3e_session enum
    r3e_int32 session_type;

    // Which phase the current session is in (gridwalk, countdown, green flag, etc.)
    // Note: See the r3e_session_phase enum
    r3e_int32 session_phase;

    // The current iteration of the current type of session (second qualifying session, etc.)
    // Note: 0-indexed, -1 = N/A
    r3e_int32 session_iteration;

    // Which controller is currently controlling the player's car (AI, player, remote, etc.)
    // Note: See the r3e_control enum
    r3e_int32 control_type;

    // How pressed the throttle pedal is
    // Range: 0.0 - 1.0
    r3e_float32 throttle_pedal;

    // How pressed the brake pedal is (-1.0 = N/A)
    // Range: 0.0 - 1.0
    r3e_float32 brake_pedal;

    // How pressed the clutch pedal is (-1.0 = N/A)
    // Range: 0.0 - 1.0
    r3e_float32 clutch_pedal;

    // How much the player's brakes are biased towards the back wheels (0.3 = 30%, etc.)
    // Note: -1.0 = N/A
    r3e_float32 brake_bias;

    // Unit: Kilopascals (KPa)
    r3e_tire_pressure tire_pressure;

    // -1 = no data available
    //  0 = not active
    //  1 = active
    r3e_int32 tire_wear_active;

    // Which type of tires the player's car has (option, prime, etc.)
    // Note: See the r3e_tire_type enum
    r3e_int32 tire_type;

    // Brake temperatures for all four wheels
    // Unit: Celsius (C)
    r3e_brake_temps brake_temps;

    // -1 = no data
    //  0 = not active
    //  1 = active
    r3e_int32 fuel_use_active;

    // Amount of time remaining for the current session
    // Note: Only available in time-based sessions, -1.0 = N/A
    // Units: Seconds
    r3e_float32 session_time_remaining;

    // The current best lap time for the leader of the session (-1.0 = N/A)
    r3e_float32 lap_time_best_leader;

    // The current best lap time for the leader of the player's class in the current session (-1.0 = N/A)
    r3e_float32 lap_time_best_leader_class;

    // Reserved for future (proper) implementation of lap_time_delta_self
    r3e_float32 reserved1;

    // The time delta between the player's time and the leader of the current session (-1.0 = N/A)
    r3e_float32 lap_time_delta_leader;

    // The time delta between the player's time and the leader of the player's class in the current session (-1.0 = N/A)
    r3e_float32 lap_time_delta_leader_class;

    // Reserved for future (proper) implementation of sector_time_delta_self
    r3e_float32 reserved2[3];

    // Reserved for future (proper) implementation of sector_time_delta_leader
    r3e_float32 reserved3[3];

    // Reserved for future (proper) implementation of sector_time_delta_leader_class
    r3e_float32 reserved4[3];

    // Time delta between the player and the car placed in front (-1.0 = N/A)
    // Units: Seconds
    r3e_float32 time_delta_front;

    // Time delta between the player and the car placed behind (-1.0 = N/A)
    // Units: Seconds
    r3e_float32 time_delta_behind;

    // Current status of the pit stop
    // Note: See the r3e_pit_window enum
    r3e_int32 pit_window_status;

    // The minute/lap from which you're obligated to pit (-1 = N/A)
    // Unit: Minutes in time-based sessions, otherwise lap
    r3e_int32 pit_window_start;

    // The minute/lap into which you need to have pitted (-1 = N/A)
    // Unit: Minutes in time-based sessions, otherwise lap
    r3e_int32 pit_window_end;

    // Total number of cut track warnings (-1 = N/A)
    r3e_int32 cut_track_warnings;

    // The number of penalties the player currently has pending of each type (-1 = N/A)
    r3e_cut_track_penalties penalties;

    // The current state of each type of flag
    r3e_flags flags;

    // The current state of various parts of the player's car
    r3e_car_damage car_damage;
} r3e_shared;

#pragma pack(pop)