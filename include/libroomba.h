

#ifndef LIB_ROOMBA_HEADER_INCLUDED
#define LIB_ROOMBA_HEADER_INCLUDED

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_ROOMBA 16



	/**
	 * @brief Constructor
	 *
	 * @param portName Port Name that Roomba is connected (e.g., "\\\\.\\COM4", "/dev/ttyUSB0")
	 * @param baudrate Baud Rate. Default 115200.
	 * @return Handle Value of Roomba
	 */
	LIBROOMBA_API int Roomba_create(const char* portname, const int baudrate);

	/**
	 * @brief Destructor
	 *
	 * @param hRoomba Handle Value of Roomba
	 */
	LIBROOMBA_API int Roomba_destroy(const int hRoomba);

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
	 * @param hRoomba Handle Value of Roomba
	 * @param mode Mode Definition
	 */
	LIBROOMBA_API int Roomba_setMode(const int hRoomba, const int mode);

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
	 * @param hRoomba Handle Value of Roomba
	 * @param mode Mode Definition
	 */
	LIBROOMBA_API int Roomba_getMode(const int hRoomba, int *mode);

	/**
	 * @brief Drive Roomba with Translation Velocity and Turn Radius.
	 *
	 * @param hRoomba Handle Value of Roomba
	 * @param translation Translation Velcoity (-500 – 500 mm/s)  
	 * @param turnRadius Radius (-2000 – 2000 mm) (negative => CCW)
	 * @throw PreconditionNotMetError
	 */
	LIBROOMBA_API int Roomba_drive(const int hRoomba, const short translationVelocity, const short turnRadius);

	/**
	 * @brief Drive Each Wheel Directly
	 *
	 * @param hRoomba Handle Value of Roomba
	 * @param rightWheel Translation Velocity (-500 - 500 mm/s)
	 * @param leftWheel  Translation Velocity (-500 - 500 mm/s)
	 * @throw PreconditionNotMetError
	 */
	LIBROOMBA_API int Roomba_driveDirect(const int hRoomba, const short rightWheelVelocity, const short leftWheelVelocity);

	/**
	 * @brief Drive Each Wheel with PWM
	 *
	 * @param hRoomba Handle Value of Roomba
	 * @param rightWheel Translation Velocity (-255 - +255)
	 * @param leftWheel  Translation Velocity (-255 - +255)
	 * @throw PreconditionNotMetError
	 */
	LIBROOMBA_API int Roomba_drivePWM(const int hRoomba, unsigned short rightWheel, unsigned short leftWheel);


	/**
	 * @brief Drive Motors of Brush, SideBrush, and Vacuum.
	 *
	 * @param hRoomba Handle Value of Roomba
	 * @param mainBrush  This parameter can be CW, CCW, or OFF.
	 * @param sideBrush  This parameter can be CW, CCW, or OFF,
	 * @param vacuum     This parameter can be ON or OFF.
	 * @throw PreconditionNotMetError
	 */
	LIBROOMBA_API int Roomba_driveMotors(const int hRoomba, const int mainBrush, const int sideBrush, const int vacuum);

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
	 * @param hRoomba Handle Value of Roomba
	 * @param leds flags that indicates leds. (0-255)
	 * @param intensity intensity of the leds. (0-255)
	 * @param color color of the CLEAN/POWER button (0-green, 255-red).
	 */
	LIBROOMBA_API int Roomba_setLED(const int hRoomba, unsigned char leds, unsigned char intensity, unsigned char color = 127);




#ifdef __cplusplus
}
#endif



#endif // #ifndef LIB_ROOMBA_HEADER_INCLUDED