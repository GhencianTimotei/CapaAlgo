/**
*   @file    Reg_eSys_Cse.h
*
*   @version 1.0.1
*   @brief   AUTOSAR Crypto - Cryptographic Services Engine (CSE) Registers
*   @details Contains information about the CSE's registers
*
*   @addtogroup  CRYPTO
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : ARM
*   Peripheral           : Crypto
*   Dependencies         : none
*
*   Autosar Version      : 4.3.1
*   Autosar Revision     : ASR_REL_4_3_REV_0001
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : S32K14x_MCAL_1_0_1_RTM_P1_HF3_ASR_REL_4_3_REV_0001_20210324
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2019 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/


#ifndef REG_ESYS_CSE_H
#define REG_ESYS_CSE_H

#ifdef __cplusplus
extern "C" {
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Reg_eSys.h"
/**
* @file           Reg_eSys_Cse.h    
*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief  Parameters that shall be published within the driver header file and also in the 
* module's description file
*/
#define REG_ESYS_CSE_VENDOR_ID                      43
#define REG_ESYS_CSE_AR_RELEASE_MAJOR_VERSION       4
#define REG_ESYS_CSE_AR_RELEASE_MINOR_VERSION       3
#define REG_ESYS_CSE_AR_RELEASE_REVISION_VERSION    1
#define REG_ESYS_CSE_SW_MAJOR_VERSION               1
#define REG_ESYS_CSE_SW_MINOR_VERSION               0
#define REG_ESYS_CSE_SW_PATCH_VERSION               1

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Reg_eSys header file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((REG_ESYS_CSE_AR_RELEASE_MAJOR_VERSION != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
         (REG_ESYS_CSE_AR_RELEASE_MINOR_VERSION != REG_ESYS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Reg_eSys_Cse.h and Reg_eSys.h are different"
    #endif
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/**
* @brief Platform Flash Register List
*/
#define CRYPTO_FSTAT_ADDR32                           ((uint32)(FTFE_BASEADDR + (uint32)0x00UL))  /**< @brief Flash Status Register (CRYPTO_CSE_FSTAT) */
#define CRYPTO_FCNFG_ADDR32                           ((uint32)(FTFE_BASEADDR + (uint32)0x01UL))  /**< @brief Flash Configuration Register (CRYPTO_CSE_FCNFG) */
#define CRYPTO_FCSESTAT_ADDR32                        ((uint32)(FTFE_BASEADDR + (uint32)0x2CUL))  /**< @brief Flash CSE Status Register (CRYPTO_CSE_FCSESTAT) */
#define CRYPTO_PRAM_HDR_ADDR32                        (PRAM_BASEADDR + (uint32)0x00UL)            /**< @brief PRAM page 0 header slot */
#define CRYPTO_PRAM_ERR_ADDR32                        (PRAM_BASEADDR + (uint32)0x06UL)            /**< @brief PRAM page 0 error slot */
#define CRYPTO_PRAM_PAGE1_ADDR32                      (PRAM_BASEADDR + (uint32)0x10UL)            /**< @brief PRAM page 1 */
#define CRYPTO_PRAM_PAGE2_ADDR32                      (PRAM_BASEADDR + (uint32)0x20UL)            /**< @brief PRAM page 2 */
#define CRYPTO_PRAM_PAGE3_ADDR32                      (PRAM_BASEADDR + (uint32)0x30UL)            /**< @brief PRAM page 3 */
#define CRYPTO_PRAM_PAGE4_ADDR32                      (PRAM_BASEADDR + (uint32)0x40UL)            /**< @brief PRAM page 4 */
#define CRYPTO_PRAM_PAGE5_ADDR32                      (PRAM_BASEADDR + (uint32)0x50UL)            /**< @brief PRAM page 5 */
#define CRYPTO_PRAM_PAGE7_ADDR32                      (PRAM_BASEADDR + (uint32)0x70UL)            /**< @brief PRAM page 7 */
#define CRYPTO_PRAM_PAGE0_LENGTH_SLOT_ADDR16          (PRAM_BASEADDR + (uint32)0x0CUL)            /**< @brief PRAM page 0 length slot */
#define CRYPTO_PRAM_PAGE0_MAC_LENGTH_SLOT_ADDR16      (PRAM_BASEADDR + (uint32)0x0AUL)            /**< @brief PRAM page 0 MAC length slot */
#define CRYPTO_PRAM_PAGE1_MAC_STATUS_ADDR16           (CRYPTO_PRAM_PAGE1_ADDR32 + (uint32)0x06UL)   /**< @brief Verify MAC command */
#define CRYPTO_PRAM_PAGE2_STATUS_REG_ADDR8            (CRYPTO_PRAM_PAGE2_ADDR32 + (uint32)0x0CUL)   /**< @brief Used for Get_ID command */
#define CRYPTO_PRAM_PAGE1_BOOT_METHOD_ADDR8           (CRYPTO_PRAM_PAGE1_ADDR32 + (uint32)0x08UL)   /**< @brief Used for Boot_define command */
#define CRYPTO_PRAM_PAGE1_BOOT_SIZE_ADDR32            (CRYPTO_PRAM_PAGE1_ADDR32 + (uint32)0x0CUL)   /**< @brief Used for Boot_define command */ 
#define CRYPTO_FCCOB3_ADDR32                          ((uint32)(FTFE_BASEADDR + (uint32)0x04UL))  /**< @brief Flash Common Command Object Registers(FTFE_FCCOB3) */
#define CRYPTO_FCCOB2_ADDR32                          ((uint32)(FTFE_BASEADDR + (uint32)0x05UL))  /**< @brief Flash Common Command Object Registers(FTFE_FCCOB2) */
#define CRYPTO_FCCOB1_ADDR32                          ((uint32)(FTFE_BASEADDR + (uint32)0x06UL))  /**< @brief Flash Common Command Object Registers(FTFE_FCCOB1) */
#define CRYPTO_FCCOB0_ADDR32                          ((uint32)(FTFE_BASEADDR + (uint32)0x07UL))  /**< @brief Flash Common Command Object Registers(FTFE_FCCOB0) */
#define CRYPTO_FCCOB5_ADDR32                          ((uint32)(FTFE_BASEADDR + (uint32)0x0AUL))  /**< @brief Flash Common Command Object Registers(FTFE_FCCOB5) */
#define CRYPTO_FCCOB4_ADDR32                          ((uint32)(FTFE_BASEADDR + (uint32)0x0BUL))  /**< @brief Flash Common Command Object Registers(FTFE_FCCOB4) */

#define CRYPTO_PRAM_HDR_KEYID_U8               ((uint32)0x00UL)
#define CRYPTO_PRAM_HDR_SEQ_U8                 ((uint32)0x08UL)
#define CRYPTO_PRAM_HDR_FORMAT_U8              ((uint32)0x10UL)
#define CRYPTO_PRAM_HDR_CMD_U8                 ((uint32)0x18UL)         

#define CRYPTO_PRAM_HDR_KEYID_ADDR32           (CRYPTO_PRAM_HDR_ADDR32 + (uint32)0x00UL)
#define CRYPTO_PRAM_HDR_SEQ_ADDR32             (CRYPTO_PRAM_HDR_ADDR32 + (uint32)0x01UL)
#define CRYPTO_PRAM_HDR_FORMAT_ADDR32          (CRYPTO_PRAM_HDR_ADDR32 + (uint32)0x02UL)
#define CRYPTO_PRAM_HDR_CMD_ADDR32             (CRYPTO_PRAM_HDR_ADDR32 + (uint32)0x03UL)   
             
/**
 * @brief Flash CSE Status Register (CRYPTO_CSE_FCSESTAT)
 */
#define CRYPTO_FCSESTAT_BSY_U8                (0x01U) /**< @brief Busy Flag */

/**
 * @brief Flash Configuration Register (CRYPTO_CSE_FCNFG)
 */
#define CRYPTO_FCNFG_RAMRDY_U8          (0x02U) /**< @brief RAM Ready */
#define CRYPTO_FCNFG_EEERDY_U8          (0x01U) /**< @brief EEE Ready */
#define CRYPTO_FCNFG_ENABLE_CCIE_U8     (0X80U) /**< @brief Enable a interrupt when a command completed */
#define CRYPTO_FCNFG_DISABLE_CCIE_U8    (0x00U) /**< @brief Enable a interrupt when a command completed */
/**
 * @brief Flash Status Register (FTFE_FSTAT) flags
 */
#define CRYPTO_FSTAT_CCIF_U8         (0x80U) /**< @brief Command Complete Interrupt Flag */
#define CRYPTO_FSTAT_ENABLE_CCIE_U8  (0X80U) /**< @brief Enable a interrupt when a command completed */
#define CRYPTO_FSTAT_DISABLE_CCIE_U8 (0x00U) /**< @brief Disable a interrupt when a command completed */
#define CRYPTO_FSTAT_RDCOLERR_U8     (0x40U) /**< @brief FTFE Read Collision Error Flag */
#define CRYPTO_FSTAT_ACCERR_U8       (0x20U) /**< @brief Flash Access Error Flag */
#define CRYPTO_FSTAT_FPVIOL_U8       (0x10U) /**< @brief Flash Protection Violation Flag */
#define CRYPTO_FSTAT_MGSTAT0_U8      (0x01U) /**< @brief Memory Controller Command Completion Status Flag */

/**
 * @brief FSTAT masks for W1C operations 
 */       
#define CRYPTO_FSTAT_RDCOLERR_W1C    (CRYPTO_FSTAT_RDCOLERR_U8)
#define CRYPTO_FSTAT_ACCERR_W1C      (CRYPTO_FSTAT_ACCERR_U8)      
#define CRYPTO_FSTAT_FPVIOL_W1C      (CRYPTO_FSTAT_FPVIOL_U8)    

/**
 * @brief Used to wait for FCSESTAT_BUSY flag to turn into 0 after a command is launched 
 */
#define CRYPTO_COMMAND_IN_PROGRESS_U8         ((uint8)1U)
#define CRYPTO_NO_COMMAND_IN_PROGRESS_U8      ((uint8)0U)

/**
 * @brief Used to wait for FSTAT CCIF flag to verify no other command is in progress 
 */
#define CRYPTO_CCIF_NO_COMMAND_IN_PROGRESS_U8      ((uint8)0x80U)

#define CRYPTO_EEERDY_CONFIGURED          ((uint8)0x01UL)
#define CRYPTO_RAMRDY_NOT_CONFIGURED      ((uint8)0x00UL)

/**
 * @brief FCCOB commands IDs
 */
#define CRYPTO_CMD_PROGRAM_PARTITION             (0x80U)


/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif  /* REG_ESYS_CSE_H */

/** @} */
