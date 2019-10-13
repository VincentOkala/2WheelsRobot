/*
 * Params.c
 *
 *  Created on: Oct 12, 2019
 *      Author: 16138
 */

#include "Params.h"
#include <stm32f1xx.h>

#define PARAMS_PAGE_ADDRESS 0x0800FC00
#define HAVE_SAVED_DATA		0x01

params_t params = {
		.pid_params = {
				.KP = 10,
				.KI = 0.1,
				.KD = 0,
				.preIPart = 0,
				.preError = 0,
				.minIpart = -500,
				.maxIPart = 500,
				.minDpart = -500,
				.maxDPart = 500,
				.minOut = -1000,
				.maxOut = 1000,
				.isFistCompute = true
		},
		.stand_point = 0,
		.believe_in_gyro = 0.90,

		.gx_offset = 1,
		.gy_offset = 2,
		.gz_offset = 3
};

void params_save(){
	HAL_FLASH_Unlock();

	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = PARAMS_PAGE_ADDRESS;
	EraseInitStruct.NbPages     = 1;

	uint32_t PageError = 0;
	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

	uint32_t address = PARAMS_PAGE_ADDRESS;
	uint32_t *ptr;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, HAVE_SAVED_DATA);
	address+=4;

	ptr = &params.pid_params.KP;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, *ptr);
	address+=4;

	ptr = &params.pid_params.KI;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, *ptr);
	address+=4;

	ptr = &params.pid_params.KD;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, *ptr);
	address+=4;

	ptr = &params.stand_point;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, *ptr);
	address+=4;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, params.gx_offset);
	address+=4;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, params.gy_offset);
	address+=4;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, params.gz_offset);
	address+=4;

	HAL_FLASH_Lock();
}

bool params_load(){
	uint32_t address = PARAMS_PAGE_ADDRESS;

	if((*(__IO uint32_t*) address) != HAVE_SAVED_DATA) return false;
	address+=4;

	float *ptr;
	ptr = (__IO uint32_t*) address;
	params.pid_params.KP = *ptr;
	address+=4;
	ptr = (__IO uint32_t*) address;
	params.pid_params.KI = *ptr;
	address+=4;
	ptr = (__IO uint32_t*) address;
	params.pid_params.KD = *ptr;
	address+=4;
	ptr = (__IO uint32_t*) address;
	params.stand_point = *ptr;
	address+=4;
	params.gx_offset = (*(__IO uint32_t*) address);
	address+=4;
	params.gy_offset = (*(__IO uint32_t*) address);
	address+=4;
	params.gz_offset = (*(__IO uint32_t*) address);
	address+=4;
	return true;
}
