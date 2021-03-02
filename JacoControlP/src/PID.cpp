/*
 * PID.cpp
 *
 *  Created on: 25.07.2016
 *      Author: yitao
 */
#include "PID.h"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
//Constructor without IntegralLimit
PID::PID(std::vector<double> pGain, std::vector<double> iGain, std::vector<double> dSetValueGain, std::vector<double> dCurrentValueGain, double sampleFrequency){
	mProportionalGain = pGain;
	mIntegralGain = iGain;
	mDerivativeSetValueGain = dSetValueGain;
	mDerivativeCurrentValueGain = dCurrentValueGain;
	mSampleFrequency = sampleFrequency;
	mEndpoint = false;

	for (unsigned int i = 0; i < pGain.size(); i++){
		mIntegralSum.push_back(0);
		mIntegralLimit.push_back(0);
		mPreviousCurrentValue.push_back(0);
		mPreviousSetValue.push_back(0);
		merror.push_back(0);
	}
}

//Constructor with IntegralLimit
PID::PID(std::vector<double> pGain, std::vector<double> iGain, std::vector<double> dSetValueGain, std::vector<double> dCurrentValueGain, double sampleFrequency, std::vector<bool> integralLimit, std::vector<double> integralUpperLimit, std::vector<double> integralLowerLimit){
	mProportionalGain = pGain;
	mIntegralGain = iGain;
	mDerivativeSetValueGain = dSetValueGain;
	mDerivativeCurrentValueGain = dCurrentValueGain;
	mSampleFrequency = sampleFrequency;
	mEndpoint = false;

	mIntegralLimit = integralLimit;
	mIntegralUpperLimit = integralUpperLimit;
	mIntegralLowerLimit = integralLowerLimit;

	for (unsigned int i = 0; i < pGain.size(); i++){
		mIntegralSum.push_back(0);
		mPreviousCurrentValue.push_back(0);
		mPreviousSetValue.push_back(0);
	}
}
PID::~PID(void){

}

// PID control algorithm
std::vector<double> PID::calculate(std::vector<double> setValue,std::vector<double> currentValue){
	std::vector<double> u (mProportionalGain.size());

	for (unsigned int i = 0; i < mProportionalGain.size(); i++){
		// Complete the controller here:
	}
	mPreviousCurrentValue = currentValue;
	mPreviousSetValue = setValue;

	return u;
}

// set previous values for derivatives
void PID::setPreviousCurrentValue(std::vector<double> previousCurrentValue){
	mPreviousCurrentValue = previousCurrentValue;
}

void PID::setPreviousSetValue(std::vector<double> previousSetValue){
	mPreviousSetValue = previousSetValue;
}

std::vector<double> PID::getError(){
	return merror;
}



