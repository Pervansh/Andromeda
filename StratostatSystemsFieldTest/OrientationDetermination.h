#pragma once

#include <MPU6050.h>
#include <DFRobot_BMP280.h>
#include <Device.h>
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

#include "config.h"

extern DFRobot_BMP280_IIC bmp;
extern MPU6050            mpu;
extern TinyGPSPlus        gps;
extern SoftwareSerial     gpsSerial;

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
