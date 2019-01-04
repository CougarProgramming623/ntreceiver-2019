#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "ntcore_cpp.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include <iostream>
#include <string>

using namespace std;

std::shared_ptr<nt::NetworkTable> start_networktables(void)
{
	auto inst = nt::NetworkTableInstance::GetDefault();
	inst.StartClient("roborio-623-frc.local");
	return inst.GetTable("beaglebone");
}

int
main(int argc, char **argv)
{
	std::shared_ptr<nt::NetworkTable> table = start_networktables();

	sleep(3);	
//	nt::NetworkTableEntry color = table.get()->GetEntry("color entry");
	
//	std::cout << "Hello world" << std::endl;
	
	std::string saved = "invalid";

	for (;;) {
		if(table.get()->GetBoolean("shutdown", false)) {
			system("sudo poweroff");
		} else {
				std::string currentColor = table.get()->GetString("color entry", "invalid color");

				if(saved.compare(currentColor) != 0) {
					std::cout << "COLOR CHANGE to " << currentColor << endl;//code to change color
					system("echo stop > /sys/class/remoteproc/remoteproc1/state");
					if(currentColor.compare("red") == 0) {
						system("echo red.out > /sys/class/remoteproc/remoteproc1/firmware");
					} else if(currentColor.compare("blue") == 0) {
						system("echo blue.out > /sys/class/remoteproc/remoteproc1/firmware");
					} else {
						system("echo green.out > /sys/class/remoteproc/remoteproc1/firmware");
					}

					system("echo start > /sys/class/remoteproc/remoteproc1/state");
					sleep(3);
				} else {
					sleep(3);
				}
				saved = currentColor;
		}
	}

	
}
