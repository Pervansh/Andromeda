#pragma once

#include <MPU6050.h>
#include <BMP280_DEV.h>
#include <Device.h>
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

#include "config.h"

extern BMP280_DEV     bmp;
extern MPU6050        mpu;
extern TinyGPSPlus    gps;
extern SoftwareSerial gpsSerial;

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
