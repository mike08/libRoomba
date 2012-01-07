#pragma once

#include <windows.h>

#include "common.h"

#include "op_code.h"

#include "Transport.h"

#include "Thread.h"
#include <RoombaException.h>

#include <map>

namespace net {
	namespace ysuga {
		namespace roomba {

			/**
			 * @brief Roomba Control Library main class.
			 * @see http://www.irobot.lv/uploaded_files/File/iRobot_Roomba_500_Open_Interface_Spec.pdf
			 */
			class Roomba : public Thread
			{
			private:


			public:

				/**
				 * @brief Roomba's Modes.
				 * 
				 * Mainly Roomba has three modes, PASSIVE, SAFE, and FULL.
				 * The other modes invode some specific behavior like spot-cleaning.
				 * During those specific behaviors, Roomba is in PASSIVE modes.
	
				enum Mode {
					PASSIVE = 100,
					SAFE,
					FULL,
					SLEEP,
					SPOT_CLEAN,
					NORMAL_CLEAN,
					MAX_TIME_CLEAN,
					DOCK,
					POWER_DOWN,
				};
				 */

			private:
				Mode m_CurrentMode;

			private:
				Transport *m_pTransport;

			public:

				/**
				 * @brief Constructor
				 *
				 * @param portName Port Name that Roomba is connected (e.g., "\\\\.\\COM4", "/dev/ttyUSB0")
				 * @param baudrate Baud Rate. Default 115200.
				 */
				LIBROOMBA_API Roomba(const char *portName, const int baudrate = 115200);

				/**
				 * @brief Destructor
				 */
				LIBROOMBA_API virtual ~Roomba(void);


			public:
				/** 
				 * @brief Set Roomba's mode 
				 *
				 * Roomba's Mode definitions are as follows: <br />
				 *  -- MODE_SAFE   Safe mode. (Precondition must be FULL)
				 *  -- MODE_FULL   Full control mode. No safety features. 
				 *  -- POWER  Power Down Roomba (In this mode, Roomba is in PASSIVE mode.)
				 *  -- SPOT_CLEAN  Start Spot cleaning (In this mode, Roomba is in PASSIVE mode.)
				 *  -- NORMAL_CLEAN  Start normal cleaning (In this mode, Roomba is in PASSIVE mode.)
				 *  -- MAX_TIME_CLEAN  Start cleaning in maximum time (In this mode, Roomba is in PASSIVE mode.)
				 *  -- DOCK Start seeking dock station (In this mode, Roomba is in PASSIVE mode.)
				 *
				 * @param mode Mode Definition
				 */
				LIBROOMBA_API void setMode(Mode mode);

				/** 
				 * @brief Get Roomba's mode 
				 *
				 * Roomba's Mode definitions are as follows: <br />
				 *  -- MODE_SAFE   Safe mode. (Precondition must be FULL)
				 *  -- MODE_FULL   Full control mode. No safety features. 
				 *  -- POWER  Power Down Roomba (In this mode, Roomba is in PASSIVE mode.)
				 *  -- SPOT_CLEAN  Start Spot cleaning (In this mode, Roomba is in PASSIVE mode.)
				 *  -- NORMAL_CLEAN  Start normal cleaning (In this mode, Roomba is in PASSIVE mode.)
				 *  -- MAX_TIME_CLEAN  Start cleaning in maximum time (In this mode, Roomba is in PASSIVE mode.)
				 *  -- DOCK Start seeking dock station (In this mode, Roomba is in PASSIVE mode.)
				 *
				 * @return Mode Definition
				 */
				LIBROOMBA_API Mode getMode() const {
					return m_CurrentMode;
				}
			public:


				/**
				 * @brief Drive Roomba with Translation Velocity and Turn Radius.
				 *
				 * @param translation Translation Velcoity (-500 – 500 mm/s)  
				 * @param turnRadius Radius (-2000 – 2000 mm) (negative => CCW)
				 * @throw PreconditionNotMetError
				 */
				LIBROOMBA_API void drive(unsigned short translation, unsigned short turnRadius);


				/**
				 * @brief Drive Each Wheel Directly
				 *
				 * @param rightWheel Translation Velocity (-500 - 500 mm/s)
				 * @param leftWheel  Translation Velocity (-500 - 500 mm/s)
				 * @throw PreconditionNotMetError
				 */
				LIBROOMBA_API void driveDirect(unsigned short rightWheel, unsigned short leftWheel);

				/**
				 * @brief Drive Each Wheel with PWM
				 *
				 * @param rightWheel Translation Velocity (-255 - +255)
				 * @param leftWheel  Translation Velocity (-255 - +255)
				 * @throw PreconditionNotMetError
				 */
				LIBROOMBA_API void drivePWM(unsigned short rightWheel, unsigned short leftWheel);

				
				/**
				 * @brief Drive Motors of Brush, SideBrush, and Vacuum.
				 *
				 * @param mainBrush  This parameter can be CW, CCW, or OFF.
				 * @param sideBrush  This parameter can be CW, CCW, or OFF,
				 * @param vacuum     This parameter can be ON or OFF.
				 * @throw PreconditionNotMetError
				 */
				LIBROOMBA_API void driveMotors(Motors mainBrush, Motors sideBrush, Motors vacuum);


				/**
				 * @brief Set LEDs on Roomba
				 *
				 * This function changes LEDs lighting states.
				 * The first argument must be the OR of following values:
				 *  LED_CHECK_ROBOT, LED_DOCK, LED_SPORT, LED_DEBRIS.
				 * The second argument indicates the intensity (0 - 255)
				 * The third argument indicates the color of CLEAN/POWER button 
				 * which places on the center of the top panel of the robot.
				 * 0 and 255 corresponds to green and red respectively. The other
				 * values mean intermediate colors.
				 *
				 * @param leds flags that indicates leds. (0-255)
				 * @param intensity intensity of the leds. (0-255)
				 * @param color color of the CLEAN/POWER button (0-green, 255-red).
				 */
				LIBROOMBA_API void setLED(unsigned char leds, unsigned char intensity, unsigned char color = 127);


			private:
				int m_isStreamMode;

				std::map<SensorID, unsigned short> m_SensorDataMap;

			public:
				/**
				 * @brief Start Sensor Data Stream Receiving.
				 *
				 * This function starts sensor stream from Roomba. The sensor data will be received
				 * in every 15 ms.
				 *
				 * @param requestingSensors array that includes sensorIds
				 * @param numSensors The numbers of sensors which are listed in the previous argument.
				 */
				void startSensorStream(unsigned char* requestingSensors, int numSensors);

				/**
				 * @brief Resume Sensor Data Stream
				 */
				LIBROOMBA_API void resumeSensorStream();

				/**
				 * @brief Suspend Sensor Data Stream
				 */
				LIBROOMBA_API void suspendSensorStream();

				void Run();

				/**
				 * @brief
				 *
				 */
				LIBROOMBA_API void runAsync();

			private:
				void RequestSensor(unsigned char sensorId, short *value) const ;
				void RequestSensor(unsigned char sensorId, unsigned short *value) const;
				void RequestSensor(unsigned char sensorId, char *value) const;
				void RequestSensor(unsigned char sensorId, unsigned char *value) const;

			public:

				/**
				 * @brief Is Right Wheel Dropped ?
				 *
				 * @return true if dropped. false if not dropped.
				 */
				LIBROOMBA_API int isRightWheelDropped() const;

				/**
				 * @brief Is Left Wheel Dropped ?
				 *
				 * @return true if dropped. false if not dropped.
				 */
				LIBROOMBA_API int isLeftWheelDropped() const;

				/**
				 * @brief Is Right Bump ?
				 *
				 * @return true if bumped. false if not bumped.
				 */
				LIBROOMBA_API int isRightBump() const;

				/**
				 * @brief Is Left Bump ?
				 *
				 * @return true if bumped. false if not bumped.
				 */
				LIBROOMBA_API int isLeftBump() const;

				/**
				 * @brief Is Left Cliff ?
				 *
				 * @return true if cliff. false if not cliff.
				 */
				LIBROOMBA_API int isCliffLeft() const;

				/**
				 * @brief Is Front Left Cliff ?
				 *
				 * @return true if cliff. false if not cliff.
				 */
				LIBROOMBA_API int isCliffFrontLeft() const;

				/**
				 * @brief Is Front Right Cliff ?
				 *
				 * @return true if cliff. false if not cliff.
				 */
				LIBROOMBA_API int isCliffFrontRight() const;

				/**
				 * @brief Is Right Cliff ?
				 *
				 * @return true if cliff. false if not cliff.
				 */
				LIBROOMBA_API int isCliffRight() const;

				/**
				 * @brief Is Virtual Wall deteceted?
				 *
				 * @return true if virtual wall detected.
				 */
				LIBROOMBA_API int isVirtualWall() const;

				/** 
				 * @brief Wheel OverCurrent?
				 *
				 * Return value can be or-combination of following values:
				 *  RightWheel, LeftWheel, MainBrush, SideBrush
				 *
				 * @return MotorFlag data. 
				 */
				LIBROOMBA_API MotorFlag isWheelOvercurrents() const;

				/**
				 * @brief Is Right Wheel Over Current?
				 *
				 * @return true if overcurrent
				 */
				LIBROOMBA_API int isRightWheelOvercurrent() const;

				/**
				 * @brief Is Left Wheel Over Current?
				 *
				 * @return true if overcurrent
				 */
				LIBROOMBA_API int isLeftWheelOvercurrent() const;

				/**
				 * @brief Is Main Brush Over Current?
				 *
				 * @return true if overcurrent
				 */
				LIBROOMBA_API int isMainBrushOvercurrent() const;

				/**
				 * @brief Is Side Brush Over Current?
				 *
				 * @return true if overcurrent
				 */
				LIBROOMBA_API int isSideBrushOvercurrent() const;

				/**
				 * @brief Detect Dirt
				 *
				 * @return 0-255
				 */
				LIBROOMBA_API int dirtDetect() const;

				/**
				 * @brief Get 8-bit IR character received by Roomba's omnidirectional IR receiver.
				 *
				 * @return received character. value 0 indicates no character received.
				 * 
				 */
				LIBROOMBA_API unsigned char getInfraredCharacterOmni() const;

				/**
				 * @brief Get 8-bit IR character received by Roomba's right IR receiver.
				 *
				 * @return received character. value 0 indicates no character received.
				 * 
				 */
				LIBROOMBA_API unsigned char getInfraredCharacterRight() const;

				/**
				 * @brief Get 8-bit IR character received by Roomba's left IR receiver.
				 *
				 * @return received character. value 0 indicates no character received.
				 * 
				 */
				LIBROOMBA_API unsigned char getInfraredCharacterLeft() const;


				/**
				 * @brief Get Button State
				 * 
				 * The return value is combination of following value.
				 *  CLOCK, SCHEDULE, DAY, HOUR, MINUTE, DOCK, SPOT, CLEAN
				 *
				 * @return Button Flag.
				 */
				LIBROOMBA_API ButtonFlag getButtons() const;

				/**
				 * @brief Get Traveled Distance since this function previously called.
				 *
				 * @return distance in millimeters
				 */
				LIBROOMBA_API int getDistance() const;

				/**
				 * @brief Get Traveled Angle since this function previously called.
				 *
				 * @return angle in degrees
				 */
				LIBROOMBA_API int getAngle() const;

				/**
				 * @brief Get Charging State
				 *
				 * Return value can be..
				 *  NotChargning, ReconditioningCharging, FullCharging, TrickleCharging, Waiting, ChargingFaultCondition
				 *
				 * @return ChargingState
				 */
				LIBROOMBA_API ChargingState getChargingState() const;

				/**
				 * @brief Get Voltage of Battery
				 *
				 * @return voltage in milli volt
				 */
				LIBROOMBA_API int getVoltage() const;

				/**
				 * @brief Get Current
				 *
				 * @return current in milli amps (mA)
				 */
				LIBROOMBA_API int getCurrent() const;

				/** 
				 * @brief Get Temperature of Roomba
				 *
				 * @return temperature (cercius)
				 */
				LIBROOMBA_API int getTemperature() const;




				//LIBROOMBA_API int GetBatteryChargeCurrent() const;

				//LIBROOMBA_API int GetBatteryCapacity() const;

				//LIBROOMBA_API int GetWallSignal() const;

				//LIBROOMBA_API int GetCliffLeftSignal() const;
				//LIBROOMBA_API int GetCliffFrontLeftSignal() const;
				//LIBROOMBA_API int GetCliffFrontRightSignal() const;
				//LIBROOMBA_API int GetCliffRightSignal() const;

				//LIBROOMBA_API int GetAvailableChargingSources() const;

				/**
				 * @brief Get OI mode directly from Roomba
				 * 
				 * Return value can be one of the following values:
				 *  MODE_PASSIVE, MODE_SAFE, MODE_FULL, and MODE_OFF
				 *
				 * @return OI mode
				 */
				LIBROOMBA_API Mode getOIMode() const;

				/**
				 * @brief Get Requested Translational Velocity
				 *
				 * @return requested translational velocity (mm/s)
				 */
				LIBROOMBA_API int getRequestedVelocity() const;

				/**
				 * @brief Get Requested Translational Radius
				 *
				 * @return requested translational radius (mm)
				 */
				LIBROOMBA_API int getRequestedRadius() const;


				/**
				 * @brief Get Right Wheel's Encoder Count
				 *
				 * @return Encoder Count (0-65535)
				 */
				LIBROOMBA_API unsigned short getRightEncoderCounts() const;

				/**
				 * @brief Get Left Wheel's Encoder Count
				 *
				 * @return Encoder Count (0-65535)
				 */
				LIBROOMBA_API unsigned short getLeftEncoderCounts() const;
			};

		}
	}
}


