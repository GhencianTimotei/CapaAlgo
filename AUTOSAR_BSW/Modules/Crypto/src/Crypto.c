/**
*   @file    Crypto.c
*   @implements Crypto.c_Artifact
*   @version 1.0.1
*   @brief   AUTOSAR Crypto - Cryptographic Services Engine (CRYPTO) functions
*   @details Contains functions for accessing CRYPTO from the CRYPTO driver perspective
*
*   @addtogroup  Crypto
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

#ifdef __cplusplus
extern "C"{
#endif

/**
*  @page misra_violations MISRA-C:2004 violations
*
* @section Crypto_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
* @section Crypto_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
* of a header file being included more than once. This comes from the order of includes in the .c file
* and from include dependencies. As a safe approach, any file must include all its dependencies.
* Header files are already protected against double inclusions. The inclusion of Crypto_MemMap.h is as
* per AUTOSAR requirement [SWS_MemMap_00003].
*
* @section Crypto_c_REF_3
* Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer
* arithmetic but used due to the code complexity.
* they are referenced in only one translation unit.
* These functions represent the API of the driver. External linkage is needed to "export" the API.
*
* @section Crypto_c_REF_4
* Violates MISRA 2004 Required Rule 16.9, A function identifier shall only be used with either 
* preceding &, or with a parenthesised parameter list which may be empty.
*
* @section Crypto_c_REF_5
* Violates MISRA 2004 Required Rule 1.4, Identifier clash.
* This violation is due to the requirement that request to have a file version check.
*
* @section Crypto_c_REF_6
* Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
* The used compilers use more than 31 chars for identifiers.
*
* @section Crypto_c_REF_7
*          Violates MISRA 2004 Required Rule 8.10, could be made static The respective code could not be made 
*          static because of layers architecture design of the driver.
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/**
* @file           Crypto.c    
*/
#include "Crypto.h"
#include "Det.h"
#include "Crypto_Ipw.h"

/*==================================================================================================
*                                       SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @file           Crypto.c
*/
#define CRYPTO_VENDOR_ID_C                     43
/*
* @violates @ref Crypto_c_REF_5 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/*
* @violates @ref Crypto_c_REF_6 Violates MISRA 2012 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_AR_RELEASE_MAJOR_VERSION_C      4
/*
* @violates @ref Crypto_c_REF_5 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/*
* @violates @ref Crypto_c_REF_6 Violates MISRA 2012 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_AR_RELEASE_MINOR_VERSION_C      3
/*
* @violates @ref Crypto_c_REF_5 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/*
* @violates @ref Crypto_c_REF_6 Violates MISRA 2012 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_AR_RELEASE_REVISION_VERSION_C   1
#define CRYPTO_SW_MAJOR_VERSION_C              1
#define CRYPTO_SW_MINOR_VERSION_C              0
#define CRYPTO_SW_PATCH_VERSION_C              1
/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/* Check if Crypto source file and Crypto header file are of the same vendor */
#if (CRYPTO_VENDOR_ID_C != CRYPTO_VENDOR_ID)
#error "Crypto.c and Crypto.h have different vendor ids"
#endif

/* Check if Crypto source file and Crypto header file are of the same Autosar version */
#if ((CRYPTO_AR_RELEASE_MAJOR_VERSION_C != CRYPTO_AR_RELEASE_MAJOR_VERSION) || \
     (CRYPTO_AR_RELEASE_MINOR_VERSION_C != CRYPTO_AR_RELEASE_MINOR_VERSION) || \
     (CRYPTO_AR_RELEASE_REVISION_VERSION_C != CRYPTO_AR_RELEASE_REVISION_VERSION) \
    )
#error "AutoSar Version Numbers of Crypto.c and Crypto.h are different"
#endif

/* Check if Crypto source file and Crypto header file are of the same Software version */
#if ((CRYPTO_SW_MAJOR_VERSION_C != CRYPTO_SW_MAJOR_VERSION) || \
     (CRYPTO_SW_MINOR_VERSION_C != CRYPTO_SW_MINOR_VERSION) || \
     (CRYPTO_SW_PATCH_VERSION_C != CRYPTO_SW_PATCH_VERSION) \
    )
#error "Software Version Numbers of Crypto.c and Crypto.h are different"
#endif



/* Check if Crypto source file and Crypto types header file are of the same vendor */
#if (CRYPTO_VENDOR_ID_C != CRYPTO_VENDOR_ID_TYPES)
#error "Crypto.c and Crypto_Types.h have different vendor ids"
#endif

/* Check if Crypto source file and Crypto types header file are of the same Autosar version */
#if ((CRYPTO_AR_RELEASE_MAJOR_VERSION_C != CRYPTO_AR_RELEASE_MAJOR_VERSION_TYPES) || \
     (CRYPTO_AR_RELEASE_MINOR_VERSION_C != CRYPTO_AR_RELEASE_MINOR_VERSION_TYPES) || \
     (CRYPTO_AR_RELEASE_REVISION_VERSION_C != CRYPTO_AR_RELEASE_REVISION_VERSION_TYPES) \
    )
#error "AutoSar Version Numbers of Crypto.c and Crypto_Types.h are different"
#endif

/* Check if Crypto source file and Crypto types header file are of the same Software version */
#if ((CRYPTO_SW_MAJOR_VERSION_C != CRYPTO_SW_MAJOR_VERSION_TYPES) || \
     (CRYPTO_SW_MINOR_VERSION_C != CRYPTO_SW_MINOR_VERSION_TYPES) || \
     (CRYPTO_SW_PATCH_VERSION_C != CRYPTO_SW_PATCH_VERSION_TYPES) \
    )
#error "Software Version Numbers of Crypto.c and Crypto_Types.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
 #if (CRYPTO_DEV_ERROR_DETECT == STD_ON)
    #if ((CRYPTO_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (CRYPTO_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
        )
    #error "AutoSar Version Numbers of Crypto.c and Det.h are different"
    #endif
 #endif 
#endif

/* Check if Crypto source file and Crypto IPW header file are of the same vendor */
#if (CRYPTO_VENDOR_ID_C != CRYPTO_VENDOR_ID_IPW_H)
#error "Crypto.c and Crypto_Ipw.h have different vendor ids"
#endif

/* Check if Crypto source file and Crypto IPW header file are of the same Autosar version */
#if ((CRYPTO_AR_RELEASE_MAJOR_VERSION_C != CRYPTO_AR_RELEASE_MAJOR_VERSION_IPW_H) || \
     (CRYPTO_AR_RELEASE_MINOR_VERSION_C != CRYPTO_AR_RELEASE_MINOR_VERSION_IPW_H) || \
     (CRYPTO_AR_RELEASE_REVISION_VERSION_C != CRYPTO_AR_RELEASE_REVISION_VERSION_IPW_H) \
    )
#error "AutoSar Version Numbers of Crypto.c and Crypto_Ipw.h are different"
#endif

/* Check if Crypto source file and Crypto IPW header file are of the same Software version */
#if ((CRYPTO_SW_MAJOR_VERSION_C != CRYPTO_SW_MAJOR_VERSION_IPW_H) || \
     (CRYPTO_SW_MINOR_VERSION_C != CRYPTO_SW_MINOR_VERSION_IPW_H) || \
     (CRYPTO_SW_PATCH_VERSION_C != CRYPTO_SW_PATCH_VERSION_IPW_H) \
    )
#error "Software Version Numbers of Crypto.c and Crypto_Ipw.h are different"
#endif



/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/


#define CRYPTO_START_SEC_VAR_INIT_UNSPECIFIED
/**
* @violates @ref Crypto_c_REF_1 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
* @violates @ref Crypto_c_REF_2 , Repeated include file MemMap.h.
*/
#include "Crypto_MemMap.h"


/**
* @brief          This variable holds the state of the driver.
* @details        This variable holds the state of the driver. After reset is UNINIT. The output of Crypto_Init() function
*                 should set this variable into IDLE state.
*                  CRYPTO_UNINIT = The CRYPTO controller is not initialized. All registers belonging to the CRYPTO module are in reset state.
*
*/

VAR(Crypto_InitStateType, CRYPTO_VAR) Crypto_eDriverStatus = CRYPTO_UNINIT;

#define CRYPTO_STOP_SEC_VAR_INIT_UNSPECIFIED
/**
* @violates @ref Crypto_c_REF_1 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
* @violates @ref Crypto_c_REF_2 , Repeated include file MemMap.h
*/
#include "Crypto_MemMap.h"

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define CRYPTO_START_SEC_CODE
/**
* @violates @ref Crypto_c_REF_1 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
* @violates @ref Crypto_c_REF_2 , Repeated include file MemMap.h
*/
#include "Crypto_MemMap.h"

/**
* @brief           Verify if an object ID is valid
* @details         Verify if an object ID is valid (found inside the array of all crypto object IDs supported by the Crypto driver)
*
* @param[in]       u32objectId - obejctId to be verified
* @param[inout]    none
* @param[out]      u32Index - indicated the position in the array where the object ID was found
* @returns         E_OK: Request succesful, object ID found
*                  E_NOT_OK: Request failed, object ID not found
* @api
*
* @pre            
*                   
*/
LOCAL_INLINE FUNC(Crypto_VerifyObjectIdType, CRYPTO_CODE) Crypto_VerifyObjectId (VAR (uint32, AUTOMATIC) u32objectId);

#if (CRYPTO_KEYS_EXIST == 1U)
/**
* @brief           Verify if a key ID is valid 
* @details         Verify if a key ID is valid  (found inside the array of all key IDs supported by the Crypto driver)
*
* @param[in]       Job - structure containing the key ID
* @param[inout]    none
* @param[out]      none
* @returns         E_OK: Request succesful, key ID found
*                  E_NOT_OK: Request failed, key ID not found
* @api
*
* @pre            
*                   
*/
LOCAL_INLINE FUNC(Std_ReturnType, CRYPTO_CODE) Crypto_VerifyKeyValidity (P2CONST (Crypto_JobType, AUTOMATIC, CRYPTO_APPL_CONST) job );

#endif

#if( CRYPTO_DEV_ERROR_DETECT == STD_ON )
/**
* @brief           Verify if certain parameters of one job are incorrect (null ptr, invalid length)
* @details         Verify if certain parameters of one job are incorrect (null ptr, invalid length)
*
* @param[in]       job - Pointer to the configuration of the job. Contains structures with job and primitive relevant information but also pointer to result buffers.
* @param[inout]    none
* @param[out]      eOutFound
* @returns         CRYPTO_NOT_OK: Request failed, only singlecall mode supported
*                  CRYPTO_NULL_PTR: NULL PTR found
*                  CRYPTO_INVALID_LEN : Invalid length found
*                  CRYPTO_NO_ERROR : Request succesful
* @api
*
* @pre            
*                   
*/
LOCAL_INLINE FUNC(Crypto_ErrorType, CRYPTO_CODE) Crypto_VerifyServiceParameters (P2CONST ( Crypto_JobType, AUTOMATIC, CRYPTO_APPL_CONST) job );

/**
* @brief           Verify if a certain primitive is supported by a crypto driver object
* @details         Verify if a certain primitive is supported by a crypto driver object specified by u32ObjectIndex
*
* @param[in]       u32ObjectIndex - Holds the identifier of the Crypto Driver Object.
* @param[in]       job - Pointer to the configuration of the job. Contains structures with job and primitive relevant information but also pointer to result buffers.
* @param[inout]    none
* @param[out]      eOutFound
* @returns         E_OK: Request successful, primitive found
*                  E_NOT_OK: Request failed, primitive not found
* @api
*
* @pre            
*                   
*/
LOCAL_INLINE FUNC(Std_ReturnType, CRYPTO_CODE) Crypto_VerifyPrimitive (VAR (uint32, AUTOMATIC) u32ObjectIndex, P2CONST (Crypto_JobType, AUTOMATIC, CRYPTO_APPL_CONST) job );
#endif

/*==================================================================================================
*                                      LOCAL FUNCTIONS
==================================================================================================*/
/**
* @brief           Verify if an object ID is valid
* @details         Verify if an object ID is valid (found inside the array of all crypto object IDs supported by the Crypto driver)
*
* @param[in]       u32objectId - obejctId to be verified
* @param[inout]    none
* @param[out]      u32Index - indicated the position in the array where the object ID was found
* @returns         E_OK: Request succesful, object ID found
*                  E_NOT_OK: Request failed, object ID not found
* @api
*
* @pre            
*                   
*/
LOCAL_INLINE FUNC(Crypto_VerifyObjectIdType, CRYPTO_CODE) Crypto_VerifyObjectId (VAR (uint32, AUTOMATIC) u32objectId)
{
    VAR(Crypto_VerifyObjectIdType, AUTOMATIC) sVerifyId = {(Std_ReturnType)E_NOT_OK, 0U};
    VAR(uint32, AUTOMATIC) u32Counter = 0U;
    
    for ( u32Counter = 0U; ( ( u32Counter < CRYPTO_NUMBER_OF_DRIVER_OBJECTS ) &&  ( (Std_ReturnType)E_NOT_OK == sVerifyId.eFound ) ); u32Counter++ )
    {
        if ( u32objectId == Crypto_aObjectList[u32Counter]->u32CryptoDriverObjectId ) 
        {
            sVerifyId.eFound = (Std_ReturnType)E_OK;
            sVerifyId.u32ObjectIndex = u32Counter;
        }
    }
    
    return sVerifyId;
}


#if (CRYPTO_KEYS_EXIST == 1U)
/**
* @brief           Verify if a key ID is valid 
* @details         Verify if a key ID is valid  (found inside the array of all key IDs supported by the Crypto driver)
*
* @param[in]       Job - structure containing the key ID
* @param[inout]    none
* @returns         E_OK: Request succesful, key ID found
*                  E_NOT_OK: Request failed, key ID not found
* @api
*
* @pre            
*                   
*/
LOCAL_INLINE FUNC(Std_ReturnType, CRYPTO_CODE) Crypto_VerifyKeyValidity (P2CONST (Crypto_JobType, AUTOMATIC, CRYPTO_APPL_CONST) job)
{
    VAR(uint32, AUTOMATIC) u32KeyIndex;
    VAR(Std_ReturnType, AUTOMATIC) eOutResponse = (Std_ReturnType)E_OK;
    VAR (Crypto_VerifyKeyType, AUTOMATIC) sVerifyKey;
    
    /* All crypto services listed in Crypto_ServiceInfoType except of CRYPTO_HASH, CRYPTO_SECCOUNTERINCREMENT, CRYPTO_SECCOUNTERREAD and CRYPTO_RANDOMGENERATE require a key 
       represented as a key identifier. */
    if ( ( CRYPTO_RANDOMGENERATE != job->jobPrimitiveInfo->primitiveInfo->service ) &&  
         ( CRYPTO_HASH != job->jobPrimitiveInfo->primitiveInfo->service ) && ( CRYPTO_SECCOUNTERINCREMENT != job->jobPrimitiveInfo->primitiveInfo->service ) && 
         ( CRYPTO_SECCOUNTERREAD != job->jobPrimitiveInfo->primitiveInfo->service )
        )
    {
        sVerifyKey = Crypto_Ipw_VerifyKeyId ( job->cryptoKeyId );
        if ( (Std_ReturnType)E_OK == sVerifyKey.eFound )
        {
            /* Check if the key is valid */
            u32KeyIndex = sVerifyKey.u32Counter; 
            if ( 0U == Crypto_aKeyList[u32KeyIndex]->bCryptoKeyValid )
            {
                eOutResponse = (Std_ReturnType)CRYPTO_E_KEY_NOT_VALID;
            }
        }
        else
        {
            eOutResponse = (Std_ReturnType)E_NOT_OK;
        }
    }
    
    return eOutResponse;
}

#endif

#if( CRYPTO_DEV_ERROR_DETECT == STD_ON )
/**
* @brief           Verify if certain parameters of one job are incorrect (null ptr, invalid length)
* @details         Verify if certain parameters of one job are incorrect (null ptr, invalid length)
*
* @param[in]       job - Pointer to the configuration of the job. Contains structures with job and primitive relevant information but also pointer to result buffers.
* @param[inout]    none
* @param[out]      eOutFound
* @returns         CRYPTO_NOT_OK: Request failed, only singlecall mode supported
*                  CRYPTO_NULL_PTR: NULL PTR found
*                  CRYPTO_INVALID_LEN : Invalid length found
*                  CRYPTO_NO_ERROR : Request succesful
* @api
*
* @pre            
*                   
*/
LOCAL_INLINE FUNC(Crypto_ErrorType, CRYPTO_CODE) Crypto_VerifyServiceParameters (P2CONST (Crypto_JobType, AUTOMATIC, CRYPTO_APPL_CONST) job)
{
    VAR(Crypto_ErrorType, AUTOMATIC) eOutFound = CRYPTO_NO_ERROR;
    
        switch ( job->jobPrimitiveInfo->primitiveInfo->service )
        {
            case CRYPTO_HASH:
            case CRYPTO_MACGENERATE:
            case CRYPTO_SIGNATUREGENERATE:
            {
                if ( 
                     ( CRYPTO_OPERATIONMODE_UPDATE == job->jobPrimitiveInputOutput.mode ) || \
                     ( CRYPTO_OPERATIONMODE_STREAMSTART == job->jobPrimitiveInputOutput.mode )  || \
                     ( CRYPTO_OPERATIONMODE_SINGLECALL == job->jobPrimitiveInputOutput.mode )
                    )
                {
                    if ( NULL_PTR == job->jobPrimitiveInputOutput.inputPtr )
                    {
                        eOutFound = CRYPTO_NULL_PTR;
                    }
                    else if ( 0U == job->jobPrimitiveInputOutput.inputLength )
                    {
                        eOutFound = CRYPTO_INVALID_LEN;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                if ( 
                     ( ( CRYPTO_OPERATIONMODE_FINISH == job->jobPrimitiveInputOutput.mode ) || ( CRYPTO_OPERATIONMODE_STREAMSTART == job->jobPrimitiveInputOutput.mode ) || \
                     ( CRYPTO_OPERATIONMODE_SINGLECALL == job->jobPrimitiveInputOutput.mode ) ) && ( CRYPTO_NO_ERROR == eOutFound ) 
                    )
                {
                    if ( ( NULL_PTR == job->jobPrimitiveInputOutput.outputPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.outputLengthPtr ) )
                    {
                        eOutFound = CRYPTO_NULL_PTR;
                    }
                    else if ( 0U == *job->jobPrimitiveInputOutput.outputLengthPtr ) 
                    {
                        eOutFound = CRYPTO_INVALID_LEN;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
            } break;
            case CRYPTO_MACVERIFY:
            case CRYPTO_SIGNATUREVERIFY:
            {
                if ( 
                     ( CRYPTO_OPERATIONMODE_UPDATE == job->jobPrimitiveInputOutput.mode ) || \
                     ( CRYPTO_OPERATIONMODE_STREAMSTART == job->jobPrimitiveInputOutput.mode )  || \
                     ( CRYPTO_OPERATIONMODE_SINGLECALL == job->jobPrimitiveInputOutput.mode )
                    )
                {
                    if ( NULL_PTR == job->jobPrimitiveInputOutput.inputPtr ) 
                    {
                        eOutFound = CRYPTO_NULL_PTR;
                    }
                    else if ( 0U == job->jobPrimitiveInputOutput.inputLength )
                    {
                        eOutFound = CRYPTO_INVALID_LEN;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                if ( 
                     ( ( CRYPTO_OPERATIONMODE_FINISH == job->jobPrimitiveInputOutput.mode ) || ( CRYPTO_OPERATIONMODE_STREAMSTART == job->jobPrimitiveInputOutput.mode ) || \
                     ( CRYPTO_OPERATIONMODE_SINGLECALL == job->jobPrimitiveInputOutput.mode ) ) && ( CRYPTO_NO_ERROR == eOutFound ) 
                    )
                {
                    if ( ( NULL_PTR == job->jobPrimitiveInputOutput.secondaryInputPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.verifyPtr ) )
                    {
                        eOutFound = CRYPTO_NULL_PTR;
                    }
                    else if ( 0U == job->jobPrimitiveInputOutput.secondaryInputLength )
                    {
                        eOutFound = CRYPTO_INVALID_LEN;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
            } break;
            case CRYPTO_ENCRYPT:
            case CRYPTO_DECRYPT:
            {
                if ( 
                     ( CRYPTO_OPERATIONMODE_UPDATE == job->jobPrimitiveInputOutput.mode ) || \
                     ( CRYPTO_OPERATIONMODE_STREAMSTART == job->jobPrimitiveInputOutput.mode )  || \
                     ( CRYPTO_OPERATIONMODE_SINGLECALL == job->jobPrimitiveInputOutput.mode )
                    )
                {
                    if ( ( NULL_PTR == job->jobPrimitiveInputOutput.inputPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.outputPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.outputLengthPtr ) )
                    {
                        eOutFound = CRYPTO_NULL_PTR;
                    }
                    else if ( ( 0U == job->jobPrimitiveInputOutput.inputLength ) || ( 0U == *job->jobPrimitiveInputOutput.outputLengthPtr ) )
                    {
                        eOutFound = CRYPTO_INVALID_LEN;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                if ( 
                     ( ( CRYPTO_OPERATIONMODE_FINISH == job->jobPrimitiveInputOutput.mode ) || ( CRYPTO_OPERATIONMODE_STREAMSTART == job->jobPrimitiveInputOutput.mode ) || \
                     ( CRYPTO_OPERATIONMODE_SINGLECALL == job->jobPrimitiveInputOutput.mode ) ) && ( CRYPTO_NO_ERROR == eOutFound ) 
                    )
                {
                    if ( ( NULL_PTR == job->jobPrimitiveInputOutput.outputPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.outputLengthPtr ) )
                    {
                        eOutFound = CRYPTO_NULL_PTR;
                    }
                    else if ( 0U == *job->jobPrimitiveInputOutput.outputLengthPtr )
                    {
                        eOutFound = CRYPTO_INVALID_LEN;
                    }
                    else
                    {
                        /* do nothing */
                    }  
                }
            } break;
            case CRYPTO_AEADENCRYPT:
            {
                if ( 
                     ( CRYPTO_OPERATIONMODE_UPDATE == job->jobPrimitiveInputOutput.mode ) || \
                     ( CRYPTO_OPERATIONMODE_STREAMSTART == job->jobPrimitiveInputOutput.mode )  || \
                     ( CRYPTO_OPERATIONMODE_SINGLECALL == job->jobPrimitiveInputOutput.mode )
                    )
                {
                    if ( ( NULL_PTR == job->jobPrimitiveInputOutput.inputPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.outputPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.outputLengthPtr ) )
                    {
                        eOutFound = CRYPTO_NULL_PTR;
                    }
                    else if ( ( 0U == job->jobPrimitiveInputOutput.inputLength ) || ( 0U == *job->jobPrimitiveInputOutput.outputLengthPtr ) )
                    {
                        eOutFound = CRYPTO_INVALID_LEN;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                if ( 
                     ( ( CRYPTO_OPERATIONMODE_FINISH == job->jobPrimitiveInputOutput.mode ) || ( CRYPTO_OPERATIONMODE_STREAMSTART == job->jobPrimitiveInputOutput.mode ) || \
                     ( CRYPTO_OPERATIONMODE_SINGLECALL == job->jobPrimitiveInputOutput.mode ) ) && ( CRYPTO_NO_ERROR == eOutFound ) 
                    )
                {
                    if ( 
                         ( NULL_PTR == job->jobPrimitiveInputOutput.secondaryInputPtr )  || ( NULL_PTR == job->jobPrimitiveInputOutput.outputPtr ) || \
                         ( NULL_PTR == job->jobPrimitiveInputOutput.secondaryOutputPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.outputLengthPtr ) || \
                         ( NULL_PTR == job->jobPrimitiveInputOutput.secondaryOutputLengthPtr )
                        )
                    {
                        eOutFound = CRYPTO_NULL_PTR;
                    }
                    else if ( ( 0U == job->jobPrimitiveInputOutput.secondaryInputLength ) || ( 0U == *job->jobPrimitiveInputOutput.secondaryOutputLengthPtr ) || \
                              ( 0U == *job->jobPrimitiveInputOutput.secondaryOutputLengthPtr )
                             )
                    {
                        eOutFound = CRYPTO_INVALID_LEN;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
            } break;
            case CRYPTO_AEADDECRYPT:
            {
                if ( 
                     ( CRYPTO_OPERATIONMODE_UPDATE == job->jobPrimitiveInputOutput.mode ) || \
                     ( CRYPTO_OPERATIONMODE_STREAMSTART == job->jobPrimitiveInputOutput.mode )  || \
                     ( CRYPTO_OPERATIONMODE_SINGLECALL == job->jobPrimitiveInputOutput.mode )
                    )
                {
                    if ( ( NULL_PTR == job->jobPrimitiveInputOutput.inputPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.outputPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.outputLengthPtr ) )
                    {
                        eOutFound = CRYPTO_NULL_PTR;
                    }
                    else if ( ( 0U == job->jobPrimitiveInputOutput.inputLength ) || ( 0U == *job->jobPrimitiveInputOutput.outputLengthPtr ) )
                    {
                        eOutFound = CRYPTO_INVALID_LEN;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                if ( 
                    ( ( CRYPTO_OPERATIONMODE_FINISH == job->jobPrimitiveInputOutput.mode ) || ( CRYPTO_OPERATIONMODE_STREAMSTART == job->jobPrimitiveInputOutput.mode ) || \
                    ( CRYPTO_OPERATIONMODE_SINGLECALL == job->jobPrimitiveInputOutput.mode ) ) && ( CRYPTO_NO_ERROR == eOutFound ) 
                   )
                {
                    if ( 
                         ( NULL_PTR == job->jobPrimitiveInputOutput.secondaryInputPtr )  || ( NULL_PTR == job->jobPrimitiveInputOutput.tertiaryInputPtr ) || \
                         ( NULL_PTR == job->jobPrimitiveInputOutput.outputPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.verifyPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.outputLengthPtr )
                        )
                    {
                        eOutFound = CRYPTO_NULL_PTR;
                    }
                    else if ( ( 0U == job->jobPrimitiveInputOutput.secondaryInputLength ) || ( 0U == job->jobPrimitiveInputOutput.tertiaryInputLength ) || \
                            ( 0U == *job->jobPrimitiveInputOutput.outputLengthPtr )
                            )
                    {
                        eOutFound = CRYPTO_INVALID_LEN;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                
            } break;
            case CRYPTO_SECCOUNTERINCREMENT:
            {
                /* nothing to be verified; Only single call is available for seccounterincrement (start, update, finish not possible)*/ 
                if ( CRYPTO_OPERATIONMODE_SINGLECALL != job->jobPrimitiveInputOutput.mode ) 
                {
                    eOutFound = CRYPTO_NOT_OK;
                }
            } break;
            case CRYPTO_SECCOUNTERREAD:
            {
                if ( CRYPTO_OPERATIONMODE_SINGLECALL == job->jobPrimitiveInputOutput.mode ) 
                {
                    if ( NULL_PTR == job->jobPrimitiveInputOutput.output64Ptr )
                    {
                        eOutFound = CRYPTO_NULL_PTR;
                    }
                }
                else
                {
                    /* Only single call is available for seccounteread (start, update, finish not possible)*/
                    eOutFound = CRYPTO_NOT_OK;
                }
            } break;
            case CRYPTO_RANDOMGENERATE:
            {
                /* Only single call is available for random function (start, update, finish not possible)*/
                if ( CRYPTO_OPERATIONMODE_SINGLECALL == job->jobPrimitiveInputOutput.mode ) 
                {
                    if  ( ( NULL_PTR == job->jobPrimitiveInputOutput.outputPtr ) || ( NULL_PTR == job->jobPrimitiveInputOutput.outputLengthPtr ) )
                    {
                        eOutFound = CRYPTO_NULL_PTR;
                    }
                    else if ( 0U == *job->jobPrimitiveInputOutput.outputLengthPtr )
                    {
                        eOutFound = CRYPTO_INVALID_LEN;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                else
                {
                    /* Only single call is available for random function (start, update, finish not possible) - return an error in this case */
                    eOutFound = CRYPTO_NOT_OK;
                }
            } break;
            default:
            {
                /* should never get here */
                eOutFound = CRYPTO_NOT_OK;
            } break;
        }
        
    return eOutFound;
}

/**
* @brief           Verify if a certain primitive is supported by a crypto driver object
* @details         Verify if a certain primitive is supported by a crypto driver object specified by u32ObjectIndex
*
* @param[in]       u32ObjectIndex - Holds the identifier of the Crypto Driver Object.
* @param[in]       job - Pointer to the configuration of the job. Contains structures with job and primitive relevant information but also pointer to result buffers.
* @param[inout]    none
* @param[out]      eOutFound
* @returns         E_OK: Request successful, primitive found
*                  E_NOT_OK: Request failed, primitive not found
* @api
*
* @pre            
*                   
*/
LOCAL_INLINE FUNC(Std_ReturnType, CRYPTO_CODE) Crypto_VerifyPrimitive (VAR (uint32, AUTOMATIC) u32ObjectIndex, P2CONST (Crypto_JobType, AUTOMATIC, CRYPTO_APPL_CONST) job)
{
    VAR(Std_ReturnType, AUTOMATIC) eOutFound = (Std_ReturnType)E_NOT_OK;
    VAR(uint32, AUTOMATIC) u32Counter = 0U;
    
    for ( u32Counter = 0U; ( ( u32Counter < Crypto_aObjectList[u32ObjectIndex]->u32NoCryptoPrimitives ) && ( (Std_ReturnType)E_NOT_OK == eOutFound ) ); u32Counter++ )
    {
        /*@violates @ref Crypto_c_REF_3 Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer*/
        if ( ( job->jobPrimitiveInfo->primitiveInfo->service == Crypto_aObjectList[u32ObjectIndex]->pCryptoKeyPrimitives[u32Counter].eService ) &&
        /*@violates @ref Crypto_c_REF_3 Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer*/
             ( job->jobPrimitiveInfo->primitiveInfo->algorithm.family == Crypto_aObjectList[u32ObjectIndex]->pCryptoKeyPrimitives[u32Counter].eFamily ) &&
        /*@violates @ref Crypto_c_REF_3 Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer*/
              ( job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == Crypto_aObjectList[u32ObjectIndex]->pCryptoKeyPrimitives[u32Counter].eMode ) ) 
        {
            eOutFound = (Std_ReturnType)E_OK;
        }
    }
    
    return eOutFound;
}
#endif

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/**
* @brief           Initializes the Crypto Driver.
* @details         Initializes the Crypto Driver.
*
* @param[in]       None
* @param[inout]    None
* @param[out]      None
*
* @api
*
* @pre            
*
* @implements     Crypto_Init_Activity
*                   
*/
/**
* @violates @ref Crypto_c_REF_7 Violates MISRA 2004 Required Rule 8.10 could be made static
*/
FUNC(void, CRYPTO_CODE) Crypto_Init (void)
{
    VAR (Std_ReturnType, AUTOMATIC) eStatus = (Std_ReturnType)E_NOT_OK;

    /* Initialize the driver only if the driver was not already initialized */
    if ( CRYPTO_UNINIT == Crypto_eDriverStatus )
    {
        eStatus = Crypto_Ipw_Init();
        
        if((Std_ReturnType)E_OK == eStatus)
        {
            /* After initialization the crypto driver is in IDLE state */
            Crypto_eDriverStatus = CRYPTO_IDLE;
        }
#if( CRYPTO_DEV_ERROR_DETECT == STD_ON )
        else
        {
            (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_INIT_ID, (uint8)CRYPTO_E_INIT_FAILED );
        }
#endif /* CRYPTO_DEV_ERROR_DETECT == STD_ON */
    }
    else
    {
        /*Do nothing*/
    }
}


#if (CRYPTO_VERSION_INFO_API == STD_ON)
/**
* @brief           Returns the version information of this module.
* @details         Returns the version information of this module.
*
* @param[in]       versioninfo  - Pointer to where to store the version information of this module.
* @param[inout]    None
* @param[out]      None
*
* @api
*
* @pre            
*
* @implements     Crypto_GetVersionInfo_Activity
*                   
*/
/**
* @violates @ref Crypto_c_REF_7 Violates MISRA 2004 Required Rule 8.10 could be made static
*/
FUNC(void, CRYPTO_CODE) Crypto_GetVersionInfo (P2VAR(Std_VersionInfoType, AUTOMATIC, CRYPTO_APPL_DATA) versioninfo)
{
#if( CRYPTO_DEV_ERROR_DETECT == STD_ON )
    if ( NULL_PTR == versioninfo )
    {
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_GETVERSIONINFO_ID, (uint8)CRYPTO_E_PARAM_POINTER );
    }
    else
    {
#endif /* CRYPTO_DEV_ERROR_DETECT == STD_ON */
        versioninfo->moduleID           = (uint16)CRYPTO_MODULE_ID;
        versioninfo->vendorID           = (uint16)CRYPTO_VENDOR_ID;
        versioninfo->sw_major_version   = (uint8)CRYPTO_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version   = (uint8)CRYPTO_SW_MINOR_VERSION;
        versioninfo->sw_patch_version   = (uint8)CRYPTO_SW_PATCH_VERSION;
#if( CRYPTO_DEV_ERROR_DETECT == STD_ON )        
    }
#endif /* CRYPTO_DEV_ERROR_DETECT == STD_ON */
}
#endif /* (CRYPTO_VERSION_INFO_API == STD_ON) */

/**
* @brief           Performs the crypto primitive, that is configured in the job parameter.
* @details         Performs the crypto primitive, that is configured in the job parameter.
*
* @param[in]       objectId - Holds the identifier of the Crypto Driver Object.
* @param[inout]    pJob - Pointer to the configuration of the job. Contains structures with job and primitive relevant information but also pointer to result buffers.
* @param[out]      None
* @returns         E_OK: Request successful 
*                  E_NOT_OK: Request Failed 
*                  CRYPTO_E_BUSY: Request Failed, Crypro Driver Object is Busy 
*                  CRYPTO_E_KEY_NOT_VALID, Request failed, the key is not valid 
*                  CRYPTO_E_KEY_SIZE_MISMATCH, Request failed, a key element has the wrong size
*                  CRYPTO_E_QUEUE_FULL: Request failed, the queue is full 
*                  CRYPTO_E_ENTROPY_EXHAUSTION: Request failed, the entropy is exhausted
*                  CRYPTO_E_SMALL_BUFFER: The provided buffer is too small to store the result 
*                  CRYPTO_E_COUNTER_OVERFLOW: The counter is overflowed. 
*                  CRYPTO_E_JOB_CANCELED: The service request failed because the synchronous Job has been canceled.
* @api
*
* @pre            
*
* @implements     Crypto_ProcessJob_Activity
*                   
*/
/**
* @violates @ref Crypto_c_REF_7 Violates MISRA 2004 Required Rule 8.10 could be made static
*/
FUNC(Std_ReturnType, CRYPTO_CODE) Crypto_ProcessJob (VAR(uint32, AUTOMATIC) u32ObjectId, P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_APPL_DATA) pJob)
{
    VAR(Crypto_VerifyObjectIdType, AUTOMATIC) u32ObjectStaus;
    
    u32ObjectStaus = Crypto_VerifyObjectId ( u32ObjectId );
    
#if (CRYPTO_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the Crypto driver is in CRYPTO_UNINIT state */
    if ( CRYPTO_UNINIT == Crypto_eDriverStatus )
    {
        /* Crypto driver has been already initialized */
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_PROCESSJOB_ID, (uint8)CRYPTO_E_UNINIT );
        u32ObjectStaus.eFound = (Std_ReturnType)E_NOT_OK;
    }
    /* If the parameter pJob is a null pointer and if development error detection for the Crypto Driver is enabled, 
       the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_POINTER to the DET and return E_NOT_OK. */
    else if ( NULL_PTR == pJob )
    {
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_PROCESSJOB_ID, (uint8)CRYPTO_E_PARAM_POINTER );
        u32ObjectStaus.eFound = (Std_ReturnType)E_NOT_OK;
    }
    /* If the parameter u32ObjectId is out of range and if development error detection for the Crypto Driver is enabled, 
       the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. */
    else if ( (Std_ReturnType)E_NOT_OK == u32ObjectStaus.eFound )
    {
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_PROCESSJOB_ID, (uint8)CRYPTO_E_PARAM_HANDLE );
        u32ObjectStaus.eFound = (Std_ReturnType)E_NOT_OK;
    }
    /* If the parameter pJob->jobPrimitiveInfo->primitiveInfo->service is not supported by the Crypto Driver Object and
      if development error detection for the Crypto Driver is enabled, the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK */
    else if ( (Std_ReturnType)E_NOT_OK == Crypto_VerifyPrimitive ( u32ObjectStaus.u32ObjectIndex, pJob ) )
    {
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_PROCESSJOB_ID, (uint8)CRYPTO_E_PARAM_HANDLE );
        u32ObjectStaus.eFound = (Std_ReturnType)E_NOT_OK;
    }
    /* If a pointer is required as an argument, but it is a null pointer, the Crypto_ProcessJob() function shall report CRYPTO_E_PARAM_POINTER. */
    else if ( CRYPTO_NULL_PTR == Crypto_VerifyServiceParameters(pJob) )
    {
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_PROCESSJOB_ID, (uint8)CRYPTO_E_PARAM_POINTER );
        u32ObjectStaus.eFound = (Std_ReturnType)E_NOT_OK;
    }
    /* If the value, which is pointed by a length pointer, is zero, and if development error detection for the Crypto Driver is enabled, the Crypto_ProcessJob() function report CRYPTO_E_PARAM_VALUE to the DET and return E_NOT_OK.
       If a length pointer is required as an argument, but the value, which is pointed by the length pointer is zero, and if development error detection for the Crypto Driver is enabled, the Crypto_ProcessJob() function report CRYPTO_E_PARAM_VALUE to the DET and return E_NOT_OK.    */
    else if ( CRYPTO_INVALID_LEN == Crypto_VerifyServiceParameters(pJob) )
    {
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_PROCESSJOB_ID, (uint8)CRYPTO_E_PARAM_VALUE );
        u32ObjectStaus.eFound = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* (CRYPTO_DEV_ERROR_DETECT == STD_ON) */
    {
#if (CRYPTO_KEYS_EXIST == 1U)
        if ( (Std_ReturnType)E_OK == u32ObjectStaus.eFound )
        {
            /* All crypto services listed in Crypto_ServiceInfoType except of CRYPTO_HASH, CRYPTO_SECCOUNTERINCREMENT, CRYPTO_SECCOUNTERREAD and CRYPTO_RANDOMGENERATE require a key represented as a key identifier. */
            u32ObjectStaus.eFound = Crypto_VerifyKeyValidity(pJob);
#endif
            if ( (Std_ReturnType)E_OK == u32ObjectStaus.eFound )
            {
                u32ObjectStaus.eFound = Crypto_Ipw_ProcessJob (u32ObjectStaus.u32ObjectIndex, pJob);
            }
#if (CRYPTO_KEYS_EXIST == 1U)
        }
#endif
    }
    /* If the buffer pJob->jobPrimitiveInput.outputPtr or pJob->jobPrimitiveInput.secondaryOutputPtr is too small to store the result of the request, 
    CRYPTO_E_SMALL_BUFFER shall be returned and the function shall additionally report the runtime error CRYPTO_E_RE_SMALL_BUFFER */
    if ( (Std_ReturnType)CRYPTO_E_SMALL_BUFFER == u32ObjectStaus.eFound )
    {
        (void) Det_ReportRuntimeError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_PROCESSJOB_ID, (uint8)CRYPTO_E_RE_SMALL_BUFFER );
    }
    
    return u32ObjectStaus.eFound;
}


/**
* @brief           This interface removes the provided job from the queue and cancels the processing of the job if possible.
* @details         This interface removes the provided job from the queue and cancels the processing of the job if possible.
*
* @param[in]       objectId - Holds the identifier of the Crypto Driver Object.
* @param[inout]    pJob - Pointer to the configuration of the job. Contains structures with job and primitive relevant information.
* @param[out]      None
* @returns         E_OK: E_OK: Request successful, job has been removed
*                  E_NOT_OK: Request Failed, job couldn't be removed 
* @api
*
* @pre            
*
* @implements     Crypto_CancelJob_Activity
*                   
*/
/**
* @violates @ref Crypto_c_REF_7 Violates MISRA 2004 Required Rule 8.10 could be made static
*/
FUNC(Std_ReturnType, CRYPTO_CODE) Crypto_CancelJob (VAR(uint32, AUTOMATIC) u32ObjectId, P2VAR(Crypto_JobInfoType, AUTOMATIC, CRYPTO_APPL_DATA) pJob)
{
    VAR(Crypto_VerifyObjectIdType, AUTOMATIC) u32ObjectStaus;
    
    u32ObjectStaus = Crypto_VerifyObjectId ( u32ObjectId );
    
#if (CRYPTO_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the Crypto driver is in CRYPTO_UNINIT state */
    if ( CRYPTO_UNINIT == Crypto_eDriverStatus )
    {
        /* If development error detection for the Crypto Driver is enabled: The function Crypto_CancelJob shall raise the error CRYPTO_E_UNINIT and return E_NOT_OK if the module is not yet initialized. */
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_CANCELJOB_ID, (uint8)CRYPTO_E_UNINIT );
        u32ObjectStaus.eFound = (Std_ReturnType)E_NOT_OK;
    }
    /* If development error detection for the Crypto Driver is enabled: The function Crypto_CancelJob shall raise the error CRYPTO_E_PARAM_POINTER and return E_NOT_OK if the parameter pJob is a null pointer. */
    else if ( NULL_PTR == pJob )
    {
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_CANCELJOB_ID, (uint8)CRYPTO_E_PARAM_POINTER );
        u32ObjectStaus.eFound = (Std_ReturnType)E_NOT_OK;        
    }
    /* If development error detection for the Crypto Driver is enabled: The function Crypto_CancelJob shall raise the error CRYPTO_E_PARAM_HANDLE and return E_NOT_OK if the parameter ObjectId is out or range. */
    else if ( (Std_ReturnType)E_NOT_OK == u32ObjectStaus.eFound )
    {
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_CANCELJOB_ID, (uint8)CRYPTO_E_PARAM_HANDLE );
        u32ObjectStaus.eFound = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* (CRYPTO_DEV_ERROR_DETECT == STD_ON) */
    {
        u32ObjectStaus.eFound = Crypto_Ipw_CancelJob(u32ObjectStaus.u32ObjectIndex, pJob);
        (void)pJob;
    }

    return u32ObjectStaus.eFound;
}


/**
* @brief           Parses the certificate data stored in the key element CRYPTO_KE_CERT_DATA and fills the key elements CRYPTO_KE_CERT_SIGNEDDATA, CRYPTO_KE_CERT_PARSEDPUBLICKEY and CRYPTO_KE_CERT_SIGNATURE.
* @details         Parses the certificate data stored in the key element CRYPTO_KE_CERT_DATA and fills the key elements CRYPTO_KE_CERT_SIGNEDDATA, CRYPTO_KE_CERT_PARSEDPUBLICKEY and CRYPTO_KE_CERT_SIGNATURE.
*
* @param[in]       cryptoKeyId  -   Holds the identifier of the key which shall be parsed.
* @param[inout]    None
* @param[out]      None
* @returns         E_OK: E_OK: Request successful
*                  E_NOT_OK: Request Failed
*                  E_BUSY: Request Failed, Crypto Driver Object is Busy
*
* @api
*
* @pre            
*
* @implements  Crypto_CertificateParse_Activity   
*                   
*/
/**
* @violates @ref Crypto_c_REF_7 Violates MISRA 2004 Required Rule 8.10 could be made static
*/
FUNC(Std_ReturnType, CRYPTO_CODE) Crypto_CertificateParse (VAR(uint32, AUTOMATIC) cryptoKeyId)
{
    VAR(Std_ReturnType, AUTOMATIC) eOutResponse = (Std_ReturnType)E_NOT_OK;
    VAR(uint32, AUTOMATIC) u32KeyIndex = 0U;
    VAR (Crypto_VerifyKeyType, AUTOMATIC) sVerifyKey;
    
    sVerifyKey = Crypto_Ipw_VerifyKeyId ( cryptoKeyId );
    if ( (Std_ReturnType)E_OK == sVerifyKey.eFound )
    {
        u32KeyIndex = sVerifyKey.u32Counter;
    }
    
#if (CRYPTO_DEV_ERROR_DETECT == STD_ON)
    /* If the module is not yet initialized and if development error detection for the Crypto Driver is enabled, the function Crypto_CertificateParse shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. */
    if ( CRYPTO_UNINIT == Crypto_eDriverStatus )
    {
        /* Crypto driver has been already initialized */
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_CERTIFICATEPARSE_ID, (uint8)CRYPTO_E_UNINIT );
        eOutResponse = (Std_ReturnType)E_NOT_OK;
    }
    /* If the parameter cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, the function Crypto_CertificateParse shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. */
    else if ( (Std_ReturnType)E_NOT_OK == sVerifyKey.eFound )
    {
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_CERTIFICATEPARSE_ID, (uint8)CRYPTO_E_PARAM_HANDLE );
        eOutResponse = (Std_ReturnType)E_NOT_OK;
    }  
    else
#endif /* (CRYPTO_DEV_ERROR_DETECT == STD_ON) */
    {
        (void)cryptoKeyId;
        (void)u32KeyIndex;
    }

    return eOutResponse;
}


/**
* @brief           Verifies the certificate stored in the key referenced by cryptoValidateKeyId with the certificate stored in the key referenced by cryptoKeyId.
* @details         Verifies the certificate stored in the key referenced by cryptoValidateKeyId with the certificate stored in the key referenced by cryptoKeyId.
*
* @param[in]       cryptoKeyId            -   Holds the identifier of the key which shall be used to validate the certificate.
* @param[in]       verifyCryptoKeyId      -   Holds the identifier of the key contain.
* @param[inout]    None
* @param[out]      verifyPtr              -   Holds a pointer to the memory location which will contain the result of the certificate verification.
* @returns         E_OK: E_OK: Request successful
*                  E_NOT_OK: Request Failed
*                  E_BUSY: Request Failed, Crypto Driver Object is Busy
*
* @api
*
* @pre            
*
* @implements  Crypto_CertificateVerify_Activity   
*                   
*/
/**
* @violates @ref Crypto_c_REF_7 Violates MISRA 2004 Required Rule 8.10 could be made static
*/
FUNC(Std_ReturnType, CRYPTO_CODE) Crypto_CertificateVerify (VAR(uint32, AUTOMATIC) cryptoKeyId, VAR(uint32, AUTOMATIC) verifyCryptoKeyId, P2VAR(Crypto_VerifyResultType, AUTOMATIC, CRYPTO_APPL_DATA) verifyPtr)
{
    VAR(Std_ReturnType, AUTOMATIC) eOutResponse = (Std_ReturnType)E_NOT_OK;
    VAR (Crypto_VerifyKeyType, AUTOMATIC) sVerifyKey;
    VAR (Crypto_VerifyKeyType, AUTOMATIC) sVerifyTargetKey;
    
#if (CRYPTO_DEV_ERROR_DETECT == STD_ON)
    /* If the module is not yet initialized and if development error detection for the Crypto Driver is enabled, the function Crypto_CertificateVerify shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. */
    if ( CRYPTO_UNINIT == Crypto_eDriverStatus )
    {
        /* Crypto driver has been already initialized */
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_CERTIFICATEVERIFY_ID, (uint8)CRYPTO_E_UNINIT );
    }
    /* If the parameter verifyPtr is a null pointer and if development error detection for the Crypto Driver is enabled, the function Crypto_CertificateVerify shall report CRYPTO_E_PARAM_POINTER to the DET and return E_NOT_OK. */
    else if ( NULL_PTR == verifyPtr )
    {
        (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_CERTIFICATEVERIFY_ID, (uint8)CRYPTO_E_PARAM_POINTER );
    }
    else
#endif /* (CRYPTO_DEV_ERROR_DETECT == STD_ON) */
   { 
        /* If the parameter cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, the function Crypto_CertificateVerify shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. */
        /* If the parameter verifyCryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, the function Crypto_CertificateVerify shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK.*/
        sVerifyKey = Crypto_Ipw_VerifyKeyId ( cryptoKeyId );
        if ( (Std_ReturnType)E_OK == sVerifyKey.eFound )
        {
            /* Check if the key is valid */
            sVerifyTargetKey = Crypto_Ipw_VerifyKeyId ( verifyCryptoKeyId );
            if ( (Std_ReturnType)E_OK == sVerifyTargetKey.eFound )
            {
                eOutResponse = (Std_ReturnType)E_OK;
                /* This function is not supported for this release due to missing support inside HSM core */
            }
            else
            {
#if (CRYPTO_DEV_ERROR_DETECT == STD_ON)
                (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_CERTIFICATEVERIFY_ID, (uint8)CRYPTO_E_PARAM_HANDLE );
#endif /* (CRYPTO_DEV_ERROR_DETECT == STD_ON) */
            }
        }
        else
        {
#if (CRYPTO_DEV_ERROR_DETECT == STD_ON)
            (void) Det_ReportError( (uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)CRYPTO_CERTIFICATEVERIFY_ID, (uint8)CRYPTO_E_PARAM_HANDLE );
#endif /* (CRYPTO_DEV_ERROR_DETECT == STD_ON) */
            (void)cryptoKeyId;
            (void)verifyCryptoKeyId;
            (void)verifyPtr;
        }
    }

    return eOutResponse;
}

/**
* @brief           If asynchronous job processing is configured and there are job queues, the function is called cyclically to process queued jobs.
* @details         If asynchronous job processing is configured and there are job queues, the function is called cyclically to process queued jobs.
*
* @param[in]       None
* @param[inout]    None
* @param[out]      None
*
* @api
*
* @pre            
*
* @implements  Crypto_MainFunction_Activity
*                   
*/
/**
* @violates @ref Crypto_c_REF_7 Violates MISRA 2004 Required Rule 8.10 could be made static
*/
FUNC(void, CRYPTO_CODE) Crypto_MainFunction (void)
{
    Crypto_Ipw_MainFunction();
}


#define CRYPTO_STOP_SEC_CODE
/**
* @violates @ref Crypto_c_REF_1 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
* @violates @ref Crypto_c_REF_2 , Repeated include file MemMap.h
*/
#include "Crypto_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
