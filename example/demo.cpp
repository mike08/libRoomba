#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "YConsole.h"
#include "Roomba.h"

using namespace net::ysuga;
using namespace net::ysuga::roomba;

void usage() {
  std::cout << "USAGE: demo /dev/ttyUSB0" << std::endl;
}


int main(const int argc, const char* argv[]) {
  int baudrate = 115200;
  if(argc == 1) {
    usage();
	std::cout << "Press enter key to exit" << std::endl;
	getchar();
    return 0;
  } else if (argc == 3) {
    baudrate = atoi(argv[2]);
  }
	try {
		bool endflag = false;

		Roomba roomba(Roomba::MODEL_500SERIES, argv[1], baudrate);
		//Roomba roomba(Roomba::MODEL_CREATE, argv[1], baudrate);
		init_scr();
		roomba.safeControl();
		roomba.runAsync();
		short color = 0;
		short intensity = 0;
		
		while(!endflag) {
			clear_scr();
			std::cout << "---------------------------------------------------------------\n";
			std::cout << "1: clean    2: spot_clean   3: max_clean  a: stop    z: dock\n";
			std::cout << "---------------------------------------------------------------\n";
			std::cout << "CleanLED                    RobotLED      DebrisLED  DockLED  SpotLED \n";
			std::cout << "5: Brighter 6: REDer        8: ON         9: ON      0: ON    -: ON   \n";
			std::cout << "t: Darker   y: GREENer      i: OFF        o: OFF     p: OFF   @: OFF  \n";
			std::cout << "---------------------------------------------------------------\n";
			std::cout << "mainBrush   sideBrush     vacuum               manuvour\n";
			std::cout << "w: cw       e: cw         r: on                u: forward\n";
			std::cout << "s: off      d: off        f: off       h: left j: stop    k: right\n";
			std::cout << "x: ccw      c: ccw        v: on                m: backward\n";
			std::cout << "---------------------------------------------------------------\n";
			//std::cout << "Right Encoder:" << std::right << roomba.getRightEncoderCounts() << "\n";
			//std::cout << "Left Encoder :" << std::right << roomba.getLeftEncoderCounts() << "\n";
			std::cout << "X            :" << std::right << roomba.getX() << "\n";
			std::cout << "Y            :" << std::right << roomba.getY() << "\n";
			std::cout << "Th           :" << std::right << roomba.getTh() << "\n";
			std::cout << "---------------------------------------------------------------\n";
			//std::cout << "Left  Bump:" << std::right << roomba.isLeftBump() << "\n";
			//std::cout << "Right Bump:" << std::right << roomba.isRightBump() << "\n";
			std::cout << "q: quit" << std::endl;

			short r_vel = 0;
			short l_vel = 0;

			if(myKbhit()) {
				int c = myGetch();
				c = tolower(c);
				switch(c) {
				case '0':
					roomba.setDockLED(1);
					break;
				case 'p':
					roomba.setDockLED(0);
					break;
				case ';':
					roomba.setSpotLED(1);
					break;
				case '/':
					roomba.setSpotLED(0);
					break;
				case '9':
					roomba.setDebrisLED(1);
					break;
				case 'o':
					roomba.setDebrisLED(0);
					break;
				case '8':
					roomba.setRobotLED(1);
					break;
				case 'i':
					roomba.setRobotLED(0);
					break;

				case '5':
					intensity += 20;
					if(intensity > 255) intensity = 255;
					roomba.setCleanLEDIntensity((unsigned char)intensity);
					break;
				case 't':
					intensity -= 20;
					if(intensity < 0) intensity = 0;
					roomba.setCleanLEDIntensity((unsigned char)intensity);
					break;

				case '6':
					color += 20;
					if(color > 255) color = 255;
					roomba.setCleanLEDColor((unsigned char)color);
					break;
				case 'y':
					color -= 20;
					if(color < 0) color = 0;
					roomba.setCleanLEDColor((unsigned char)color);
					break;


				case 'u':
					roomba.move(0.1, 0);
					r_vel = 100;
					l_vel = 100;
					break;
				case 'm':
					r_vel = -100;
					l_vel = -100;
					roomba.move(-0.1, 0);
					break;
				case 'h':
					r_vel = 100;
					l_vel = -100;
					roomba.move(0, 0.1);
					break;
				case 'k':
					r_vel = -100;
					l_vel = 100;
					roomba.move(0, -0.1);
					break;
				case 'j':
					r_vel = l_vel = 0;
					roomba.move(0, 0);
					break;

				case 'w':
					roomba.driveMainBrush(roomba.MOTOR_CW);
					break;
				case 's':
					roomba.driveMainBrush(roomba.MOTOR_OFF);
					break;
				case 'x':
					roomba.driveMainBrush(roomba.MOTOR_CCW);
					break;

				case 'e':
					roomba.driveSideBrush(roomba.MOTOR_CW);
					break;
				case 'd':
					roomba.driveSideBrush(roomba.MOTOR_OFF);
					break;
				case 'c':
					roomba.driveSideBrush(roomba.MOTOR_CCW);
					break;

				case 'r':
					roomba.driveVacuum(roomba.MOTOR_ON);
					break;				
				case 'f':
					roomba.driveVacuum(roomba.MOTOR_OFF);
					break;
				case 'v':
					roomba.driveVacuum(roomba.MOTOR_ON);
					break;

				case 'q':
					r_vel = l_vel = 0;
					roomba.driveMotors(roomba.MOTOR_OFF, roomba.MOTOR_OFF, roomba.MOTOR_OFF);
					endflag = true;
					break;

				case '1':
					roomba.clean();
					break;
				case '2':
					roomba.spotClean();
					break;
				case '3':
					roomba.maxClean();
					break;
				case 'z':
					roomba.dock();
					break;
				case 'a':
					roomba.safeControl();
					break;
				case '4':
					roomba.fullControl();
					break;


				default:
					r_vel = l_vel = 0;
					break;
				}
				try {
					if(roomba.getMode() == roomba.MODE_SAFE || roomba.getMode() == roomba.MODE_SAFE) {
						//roomba.driveDirect(r_vel, l_vel);
					}
				} catch (net::ysuga::roomba::PreconditionNotMetError &e) {
					std::cout << "Precondition Not Met" << std::endl;
				}

			} else {
				r_vel = l_vel = 0;
			}

		}

		exit_scr();

	} catch (net::ysuga::ComOpenException &e) {
		std::cerr << "Exception Occured:" << e.what()  << std::endl;
	}
	std::cout << "Hit Enter Key to Exit." << std::endl;
	getchar();
	return 0;
}
