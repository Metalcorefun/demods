#pragma once

#ifndef COMEXECUTOR_H
#define COMEXECUTOR_H

using namespace std;

#import "Resources\\COM\\Pressure.exe"

#include "Hierarchy.h"

class DSHierarchy;

class COMExecutor
{
public:
	COMExecutor(DSHierarchy& hierarchy);
	~COMExecutor();
	void sendDataToPressure();
	bool learnPressure();
	bool ISReliable(DSClassifier classifier);
	float TCriterion(DSClassifier classifier);
	float TCriterionTable(DSClassifier classifier);
	void savePressureFOV(string filePath);
	void savePressureFSC(string filePath);

private:
	DSHierarchy* hierarchy_;
	Pressure::IALON_TeacherPtr teacher;
};

#endif
