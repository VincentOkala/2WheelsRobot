/*
 * Flash.c
 *
 *  Created on: Oct 11, 2019
 *      Author: 16138
 */

#ifndef USERCODE_FLASH_FLASH_C_
#define USERCODE_FLASH_FLASH_C_

#include "Flash.h"
#include "FlashBase.h"

#define FLASH_USER_START_ADDR       ADDR_FLASH_PAGE_32   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR         ADDR_FLASH_PAGE_36   /* End @ of user Flash area */
#define FLASH_PAGE_TO_BE_PROTECTED (OB_WRP_PAGES32TO35 | OB_WRP_PAGES48TO51)


#endif /* USERCODE_FLASH_FLASH_C_ */
