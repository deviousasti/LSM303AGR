/**
 ******************************************************************************
 * @file    LSM303AGR_ACC_Sensor.h
 * @author  AST
 * @version V1.0.0
 * @date    7 September 2017
 * @brief   Abstract Class of an LSM303AGR accelerometer sensor.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


/* Prevent recursive inclusion -----------------------------------------------*/

#ifndef __LSM303AGR_ACC_Sensor_H__
#define __LSM303AGR_ACC_Sensor_H__


/* Includes ------------------------------------------------------------------*/

#include "Wire.h"


/* Defines -------------------------------------------------------------------*/
#define LSM303AGR_ACC_SENSITIVITY_FOR_FS_2G_NORMAL_MODE               3.900f  /**< Sensitivity value for 2 g full scale and normal mode [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_FOR_FS_2G_HIGH_RESOLUTION_MODE      0.980f  /**< Sensitivity value for 2 g full scale and high resolution mode [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_FOR_FS_2G_LOW_POWER_MODE           15.630f  /**< Sensitivity value for 2 g full scale and low power mode [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_FOR_FS_4G_NORMAL_MODE               7.820f  /**< Sensitivity value for 4 g full scale and normal mode [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_FOR_FS_4G_HIGH_RESOLUTION_MODE      1.950f  /**< Sensitivity value for 4 g full scale and high resolution mode [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_FOR_FS_4G_LOW_POWER_MODE           31.260f  /**< Sensitivity value for 4 g full scale and low power mode [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_FOR_FS_8G_NORMAL_MODE              15.630f  /**< Sensitivity value for 8 g full scale and normal mode [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_FOR_FS_8G_HIGH_RESOLUTION_MODE      3.900f  /**< Sensitivity value for 8 g full scale and high resolution mode [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_FOR_FS_8G_LOW_POWER_MODE           62.520f  /**< Sensitivity value for 8 g full scale and low power mode [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_FOR_FS_16G_NORMAL_MODE             46.900f  /**< Sensitivity value for 16 g full scale and normal mode [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_FOR_FS_16G_HIGH_RESOLUTION_MODE    11.720f  /**< Sensitivity value for 16 g full scale and high resolution mode [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_FOR_FS_16G_LOW_POWER_MODE         187.580f  /**< Sensitivity value for 16 g full scale and low power mode [mg/LSB] */


/* Typedefs ------------------------------------------------------------------*/
typedef enum
{
  LSM303AGR_ACC_STATUS_OK = 0,
  LSM303AGR_ACC_STATUS_ERROR,
  LSM303AGR_ACC_STATUS_TIMEOUT,
  LSM303AGR_ACC_STATUS_NOT_IMPLEMENTED
} LSM303AGR_ACC_StatusTypeDef;

typedef enum 
{
    LSM303AGR_ACC_INT1_ALL              = 0xFF,
    LSM303AGR_ACC_INT1_CLICK            = 0x80,
    LSM303AGR_ACC_INT1_AOI1             = 0x40,
    LSM303AGR_ACC_INT1_AOI2             = 0x20,
    LSM303AGR_ACC_INT1_DRDY1            = 0x10,
    LSM303AGR_ACC_INT1_DRDY2            = 0x08,
    LSM303AGR_ACC_INT1_FIFO_WATERMARK   = 0x04,
    LSM303AGR_ACC_INT1_FIFO_OVERRUN     = 0x02,
    LSM303AGR_ACC_INT1_NONE             = 0x00,
} LSM303AGR_ACC_InterruptKind;


typedef enum
{
    LSM303AGR_ACC_INTERRUPT_ACTIVE = 0x40,
    LSM303AGR_ACC_HIGH_Z = 0x20,
    LSM303AGR_ACC_LOW_Z = 0x10,
    LSM303AGR_ACC_HIGH_Y = 0x08,
    LSM303AGR_ACC_LOW_Y = 0x04,
    LSM303AGR_ACC_HIGH_X = 0x02,
    LSM303AGR_ACC_LOW_X = 0x01,
    LSM303AGR_ACC_NO_INTERRUPT = 0x00,
} LSM303AGR_ACC_InterruptReason;

typedef enum
{
    LSM303AGR_ACC_MODE_LOW_POWER = 1,
    LSM303AGR_ACC_MODE_HIGH_RES  = 0,
} LSM303AGR_ACC_PowerMode;

typedef enum
{
    LSM303AGR_ACC_AXIS_X = 0x01,
    LSM303AGR_ACC_AXIS_Y = 0x02,
    LSM303AGR_ACC_AXIS_Z = 0x04,
    LSM303AGR_ACC_AXIS_ALL = LSM303AGR_ACC_AXIS_X | LSM303AGR_ACC_AXIS_Y | LSM303AGR_ACC_AXIS_Z,
    LSM303AGR_ACC_AXIS_NONE = 0
} LSM303AGR_ACC_Axes;

/* Class Declaration ---------------------------------------------------------*/

/**
 * Abstract class of an LSM303AGR Inertial Measurement Unit (IMU) 6 axes
 * sensor.
 */
class LSM303AGR_ACC_Sensor
{
  public:
    LSM303AGR_ACC_Sensor                        (TwoWire *i2c);
    LSM303AGR_ACC_Sensor                        (TwoWire *i2c, uint8_t address);
    LSM303AGR_ACC_StatusTypeDef Init            (void);
    LSM303AGR_ACC_StatusTypeDef Enable          (void);
    LSM303AGR_ACC_StatusTypeDef Disable         (void);
    LSM303AGR_ACC_StatusTypeDef ReadID          (uint8_t *p_id);
    
    LSM303AGR_ACC_StatusTypeDef GetAxes         (int32_t *pData);
    LSM303AGR_ACC_StatusTypeDef GetSensitivity  (float *pfData);
	LSM303AGR_ACC_StatusTypeDef GetAxesRaw      (int16_t *pData);
    LSM303AGR_ACC_StatusTypeDef IsDataAvailable (bool* available, LSM303AGR_ACC_Axes axes = LSM303AGR_ACC_AXIS_ALL);

    LSM303AGR_ACC_StatusTypeDef GetODR          (float *odr);
	LSM303AGR_ACC_StatusTypeDef SetODR          (float odr);

	LSM303AGR_ACC_StatusTypeDef GetFS           (float *fullScale);
	LSM303AGR_ACC_StatusTypeDef SetFS           (float fullScale);

	LSM303AGR_ACC_StatusTypeDef ReadReg         (uint8_t reg, uint8_t *data);
	LSM303AGR_ACC_StatusTypeDef WriteReg        (uint8_t reg, uint8_t data);

    LSM303AGR_ACC_StatusTypeDef Reboot          (void);
    LSM303AGR_ACC_StatusTypeDef EnableSelfTest  (uint8_t self_test = 0);
    LSM303AGR_ACC_StatusTypeDef DisableSelfTest (void);

    LSM303AGR_ACC_StatusTypeDef EnableTemperatureSensor     (void);
    LSM303AGR_ACC_StatusTypeDef DisableTemperatureSensor    (void);
    LSM303AGR_ACC_StatusTypeDef GetTemperature              (float* temperature);
    
    LSM303AGR_ACC_StatusTypeDef SetActivityThreshold        (float threshold, float fullScale = 0);
    LSM303AGR_ACC_StatusTypeDef SetActivityDuration         (int duration, float odr = 0);
    LSM303AGR_ACC_StatusTypeDef EnableActivityInterrupt     (void);
    LSM303AGR_ACC_StatusTypeDef DisableActivityInterrupt    (void);
    LSM303AGR_ACC_StatusTypeDef ReadInterrupt1             (LSM303AGR_ACC_InterruptReason* reason = nullptr);
    LSM303AGR_ACC_StatusTypeDef ReadInterrupt2             (LSM303AGR_ACC_InterruptReason* reason = nullptr);

    LSM303AGR_ACC_StatusTypeDef SetHighPassFilter       (int interrupt, bool enable, bool filterData);
    LSM303AGR_ACC_StatusTypeDef EnableInterrupt         (LSM303AGR_ACC_InterruptKind kind);
    LSM303AGR_ACC_StatusTypeDef DisableInterrupt        (LSM303AGR_ACC_InterruptKind kind);
    
    LSM303AGR_ACC_StatusTypeDef ReadReference           (void);
    LSM303AGR_ACC_StatusTypeDef SetInterruptThreshold   (int interrupt, float threshold, float fullScale = 0);
    LSM303AGR_ACC_StatusTypeDef SetInterruptDuration    (int interrupt, int duration, float odr = 0);
    LSM303AGR_ACC_StatusTypeDef EnableWakeUpDetection   (float threshold, float fullscale = 0, bool latch = false);

    LSM303AGR_ACC_StatusTypeDef SetPowerMode            (LSM303AGR_ACC_PowerMode mode);
    LSM303AGR_ACC_StatusTypeDef SetAxes                 (LSM303AGR_ACC_Axes axes);

	/**
     * @brief Utility function to read data.
     * @param  pBuffer: pointer to data to be read.
     * @param  RegisterAddr: specifies internal address register to be read.
     * @param  NumByteToRead: number of bytes to be read.
     * @retval 0 if ok, an error code otherwise.
     */
    uint8_t IO_Read(uint8_t* pBuffer, uint8_t RegisterAddr, uint16_t NumByteToRead)
    {
      dev_i2c->beginTransmission(((uint8_t)(((address) >> 1) & 0x7F)));
      dev_i2c->write(RegisterAddr);
      dev_i2c->endTransmission(false);

      dev_i2c->requestFrom(((uint8_t)(((address) >> 1) & 0x7F)), (byte) NumByteToRead);

      int i=0;
      while (dev_i2c->available())
      {
        pBuffer[i] = dev_i2c->read();
        i++;
      }

      return 0;
    }
    
    /**
     * @brief Utility function to write data.
     * @param  pBuffer: pointer to data to be written.
     * @param  RegisterAddr: specifies internal address register to be written.
     * @param  NumByteToWrite: number of bytes to write.
     * @retval 0 if ok, an error code otherwise.
     */
    uint8_t IO_Write(uint8_t* pBuffer, uint8_t RegisterAddr, uint16_t NumByteToWrite)
    {
      dev_i2c->beginTransmission(((uint8_t)(((address) >> 1) & 0x7F)));

      dev_i2c->write(RegisterAddr);
      for (int i = 0 ; i < NumByteToWrite ; i++)
        dev_i2c->write(pBuffer[i]);

      dev_i2c->endTransmission(true);

      return 0;
    }

  private:
    LSM303AGR_ACC_StatusTypeDef SetODR_When_Enabled(float odr);
    LSM303AGR_ACC_StatusTypeDef SetODR_When_Disabled(float odr);
    LSM303AGR_ACC_StatusTypeDef GetSensitivity_Normal_Mode( float *sensitivity );
    LSM303AGR_ACC_StatusTypeDef GetSensitivity_LP_Mode( float *sensitivity );
    LSM303AGR_ACC_StatusTypeDef GetSensitivity_HR_Mode( float *sensitivity );
    LSM303AGR_ACC_StatusTypeDef ReadInterruptSource(uint8_t reg, LSM303AGR_ACC_InterruptReason* reason);

    /* Helper classes. */
    TwoWire *dev_i2c;

    /* Configuration */
    uint8_t address;

    uint8_t isEnabled;
    float Last_ODR;
};

#ifdef __cplusplus
extern "C" {
#endif
uint8_t LSM303AGR_ACC_IO_Write( void *handle, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t nBytesToWrite );
uint8_t LSM303AGR_ACC_IO_Read( void *handle, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t nBytesToRead );
#ifdef __cplusplus
}
#endif

#endif