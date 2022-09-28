#pragma once

#include <MPU6050.h>
#include <DFRobot_BMP280.h>
#include <Device.h>
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

#include "config.h"

void setupOrientationDetermination();

float getBmpAltitude();
float getBmpPressure();

float getMpuAccelerationX();
float getMpuAccelerationY();
float getMpuAccelerationZ();
float getMpuRotationX();
float getMpuRotationY();
float getMpuRotationZ();

void updateGpsData();

float getGpsLatitude();
float getGpsLongitude();
