#include "OrientationDetermination.h"

#include <Wire.h>
#include "config.h"

extern DFRobot_BMP280_IIC bmp = DFRobot_BMP280_IIC(&Wire, DFRobot_BMP280_IIC::eSdoLow);
extern MPU6050            mpu = MPU6050();
extern TinyGPSPlus        gps = TinyGPSPlus();
extern SoftwareSerial     gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

void setupOrientationDetermination() {
  Wire.begin();

  bmp.reset();
  if (bmp.begin() != DFRobot_BMP280_IIC::eStatusOK) {
    Serial.println("bmp begin faild");
  }

  if (!USE_MPU6050_DEFAULT_I2C_ADDRESS) {
    mpu = MPU6050(MPU6050_INSTEAD_OF_DEFAULT_I2C_ADDRESS);
  }
  
  mpu.initialize();
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  gpsSerial.begin(GPS_SERIAL_BAUD);
  // Проверки GPS нет!!!
}

float getBmpAltitude() {
  return bmp.calAltitude(SEA_LEVEL_PRESSURE, bmp.getPressure());
}

float getBmpPressure() {
  return bmp.getPressure();
}

float getMpuAccelerationX() {
  return mpu.getAccelerationX();
}

float getMpuAccelerationY() {
  return mpu.getAccelerationY();
}

float getMpuAccelerationZ() {
  return mpu.getAccelerationZ();
}

float getMpuRotationX() {
  return mpu.getRotationX();
}

float getMpuRotationY() {
  return mpu.getRotationY();
}

float getMpuRotationZ() {
  return mpu.getRotationZ();
}

void updateGpsData() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }
}

float getGpsLatitude() {
  gps.location.lat();
}

float getGpsLongitude() {
  gps.location.lng();
}
