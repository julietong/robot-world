/*
 * RobotThread.cpp
 *
 *  Created on: 11.07.2016
 *      Author: yitao
 */

#include "RobotThread.h"
#include "PID.h"
#include <iostream>
#include "RobotIO.h"
#include "Store.h"


RobotThread::RobotThread():TheThread(){
	Status = 0;
	Activate = 0;
	FSample = 100;
}

RobotThread::~RobotThread(){
	RobotThread::stopThread();
}

void RobotThread::startThread(){
	if (Status == 0){
		std::cout << "Starting robot thread" << std::endl;
		Activate = 1;
		TheThread = std::thread(&RobotThread::ControlThread,this);
	}
	else{
		std::cout << "Thread already running" << std::endl;
	}
}

void RobotThread::stopThread(){

	if(TheThread.joinable()){
		std::cout << "Stopping Thread ..." << std::endl;
		Activate = 0;
		TheThread.join();
		std::cout << "Thread stopped" << std::endl;
	}

}

void RobotThread::ControlThread(){
	std::cout << "Control-thread started" << std::endl;
	Status = 1; // Set Thread to Active

	RobotIO Robot;
	Robot.Init();
	Robot.Home();
	Robot.Update();

	//Set Setpoint
	std::vector<double> setPoint = Robot.getPosition();
	setPoint[0] += 100;
	//Set P-gain
	std::vector<double> pg {5,0,0,0,0,0};

	std::vector<double> ig {0,0,0,0,0,0};
	std::vector<double> dg1 = ig;
	std::vector<double> dg2 = ig;

	//Init control value
	std::vector<double> u  {0,0,0,0,0,0};


	// Go to PID.h and PID.cpp and program the controller
	PID PositionController(pg,ig,dg1,dg2,FSample);

	PositionController.setPreviousCurrentValue(Robot.getPosition());
	PositionController.setPreviousSetValue(setPoint);


	LoopTime LT(FSample);

	// Main loop starting here
	while(Activate){

		u = PositionController.calculate(setPoint,Robot.getPosition());

		Robot.setVelocity(u);
		Robot.Update();

		// Delays the loop so that Fsample is fulfilled
		LT.Delay();
	}

	Status = 0;
	std::cout << "End of thread reached: " << std::endl;
}


LoopTime::LoopTime(unsigned int fs){
	FSample = fs;
	LoopTime::MeasureTime();
}

void LoopTime::MeasureTime(){
	time = std::chrono::steady_clock::now();
}

void LoopTime::Delay(){
	time_span = (std::chrono::steady_clock::now() - time);
	if ((std::chrono::microseconds(1000000/FSample) - time_span)>= std::chrono::microseconds(0)){
		std::this_thread::sleep_for(std::chrono::microseconds(1000000/FSample) - time_span);
		time = std::chrono::steady_clock::now();
	}
	else{
		//std::cout << "System Load too high!" << std::endl;
		time = std::chrono::steady_clock::now();
	}
}
