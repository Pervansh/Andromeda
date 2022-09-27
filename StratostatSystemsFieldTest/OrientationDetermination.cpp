#include "OrientationDetermination.h"

#include "config.h"

extern BMP280_DEV     bmp = BMP280_DEV();
extern MPU6050        mpu = MPU6050();
extern TinyGPSPlus    gps = TinyGPSPlus();
extern SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

void setupOrientationDetermination() {
  Wire.begin();
  gpsSerial.begin(GPS_SERIAL_BAUD);

  // Проверки GPS нет!!!

  bmp.begin();                                    // Default initialisation, place the BMP280 into SLEEP_MODE 
  bmp.setTimeStandby(TIME_STANDBY_2000MS);       // Set the standby time to 2 seconds
  bmp.startNormalConversion();                  // Start BMP280 continuous conversion in NORMAL_MODE

  if (!USE_MPU6050_DEFAULT_I2C_ADDRESS) {
    mpu = MPU6050(MPU6050_INSTEAD_OF_DEFAULT_I2C_ADDRESS);
  }
  
  mpu.initialize();
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

float getBmpAltitude() {
  float data;
  bmp.getAltitude(data);
  return data;
}

float getBmpPressure() {
  float data;
  bmp.getPressure(data);
  return data;
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
