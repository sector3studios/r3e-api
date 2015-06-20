using System;
using System.Runtime.InteropServices;

namespace R3E
{
	class Constant
	{
		public const string SharedMemoryName = "$Race$";
	}

	namespace Data
	{
		[StructLayout(LayoutKind.Sequential, Pack = 1)]
		internal struct Vector3<T>
		{
			public T X;
			public T Y;
			public T Z;
		}

		[StructLayout(LayoutKind.Sequential, Pack = 1)]
		internal struct Orientation<T>
		{
			public T Pitch;
			public T Yaw;
			public T Roll;
		}

		[StructLayout(LayoutKind.Sequential, Pack = 1)]
		internal struct UserInput
		{
			public Single _1, _2, _3, _4, _5, _6;
		}

		[StructLayout(LayoutKind.Sequential, Pack = 1)]
		internal struct TireTemperature
		{
			public Single FrontLeft_Left;
			public Single FrontLeft_Center;
			public Single FrontLeft_Right;

			public Single FrontRight_Left;
			public Single FrontRight_Center;
			public Single FrontRight_Right;

			public Single RearLeft_Left;
			public Single RearLeft_Center;
			public Single RearLeft_Right;

			public Single RearRight_Left;
			public Single RearRight_Center;
			public Single RearRight_Right;
		}

		[StructLayout(LayoutKind.Sequential, Pack = 1)]
		internal struct PlayerData
		{
			// Virtual physics time
			// Unit: Ticks (1 tick = 1/400th of a second)
			public Int32 GameSimulationTicks;

			// Padding to accomodate for legacy alignment
			[ObsoleteAttribute("Used for padding", true)]
			public Int32 Padding1;

			// Virtual physics time
			// Unit: Seconds
			public Double GameSimulationTime;

			// Car world-space position
			public Vector3<Double> Position;

			// Car world-space velocity
			// Unit: Meter per second (m/s)
			public Vector3<Double> Velocity;

			// Car world-space acceleration
			// Unit: Meter per second squared (m/s^2)
			public Vector3<Double> Acceleration;

			// Car local-space acceleration
			// Unit: Meter per second squared (m/s^2)
			public Vector3<Double> LocalAcceleration;

			// Car body orientation
			// Unit: Euler angles
			public Vector3<Double> Orientation;

			// Car body rotation
			public Vector3<Double> Rotation;

			// Car body angular acceleration (torque divided by inertia)
			public Vector3<Double> AngularAcceleration;

			// Acceleration of driver's body in local coordinates
			public Vector3<Double> DriverBodyAcceleration;
		}

		[StructLayout(LayoutKind.Sequential, Pack = 1)]
		internal struct Shared
		{
			[ObsoleteAttribute("Not set anymore", false)]
			public UserInput UserInput;

			// Engine speed
			// Unit: Radians per second (rad/s)
			public Single EngineRps;

			// Maximum engine speed
			// Unit: Radians per second (rad/s)
			public Single MaxEngineRps;

			// Unit: Kilopascals (KPa)
			public Single FuelPressure;

			// Current amount of fuel in the tank(s)
			// Unit: Liters (l)
			public Single FuelLeft;

			// Maximum capacity of fuel tank(s)
			// Unit: Liters (l)
			public Single FuelCapacity;

			// Unit: Kelvin (K)
			public Single EngineWaterTemp;

			// Unit: Kelvin (K)
			public Single EngineOilTemp;

			// Unit: Kilopascals (KPa)
			public Single EngineOilPressure;

			// Unit: Meter per second (m/s)
			public Single CarSpeed;

			// Total number of laps in the race, or -1 if player is not in race mode (practice, test mode, etc.)
			public Int32 NumberOfLaps;

			// How many laps the player has completed. If this value is 6, the player is on his 7th lap. -1 = n/a
			public Int32 CompletedLaps;

			// Unit: Seconds (-1.0 = none)
			public Single LapTimeBest;

			// Unit: Seconds (-1.0 = none)
			public Single LapTimePrevious;

			// Unit: Seconds (-1.0 = none)
			public Single LapTimeCurrent;

			// Current position (1 = first place)
			public Int32 Position;

			// Number of cars (including the player) in the race
			public Int32 NumCars;

			// -2 = no data
			// -1 = reverse,
			//  0 = neutral
			//  1 = first gear
			// (... up to 7th)
			public Int32 Gear;

			// Temperature of three points across the tread of each tire
			// Unit: Kelvin (K)
			public TireTemperature TireTemp;

			// Number of penalties pending for the player
			public Int32 NumPenalties;

			// Physical location of car's center of gravity in world space (X, Y, Z) (Y = up)
			public Vector3<Single> CarCgLoc;

			// Pitch, yaw, roll
			// Unit: Radians (rad)
			public Orientation<Single> CarOrientation;

			// Acceleration in three axes (X, Y, Z) of car body in local-space.
			// From car center, +X=left, +Y=up, +Z=back.
			// Unit: Meter per second squared (m/s^2)
			public Vector3<Single> LocalAcceleration;

			// -1 = no data for DRS
			//  0 = not available
			//  1 = available
			public Int32 DrsAvailable;

			// -1 = no data for DRS
			//  0 = not engaged
			//  1 = engaged
			public Int32 DrsEngaged;

			// Padding to accomodate for legacy alignment
			[ObsoleteAttribute("Used for padding", true)]
			public Int32 Padding1;

			// High precision data for player's vehicle only
			public PlayerData Player;
		}
	}
}