/* ********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 */
/*! \ingroup    Dem_MemoryEntry
 *  \defgroup   Dem_ExtendedEntry ExtendedEntry
 *  \{
 *  \file       Dem_ExtendedEntry_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Encapsulates the list of extended data record buffers stored in the memory entry
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EXTENDEDENTRY_INTERFACE_H)
#define DEM_EXTENDEDENTRY_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_ExtendedEntry_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_ExtendedEntry_Public Public Methods
 * \{
 */

# if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_ExtendedEntry_ERecIsSupportedByAvailableCombinedEvent
 *****************************************************************************/
/*!
 * \brief         Tests if an available SubEvent has the ERec configured.
 *
 * \details       Tests if an available SubEvent has the ERec configured.
 *
 * \param[in]     CombinedDTCGroup
 *                Combined DTC group identifier
 * \param[in]     ERecId
 *                Identifier of the extended data record
 * \return        TRUE
 *                At least one SubEvent that has the ERec configured is available
 * \return        FALSE
 *                No SubEvent that has the ERec configured is available
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_ERECS == STD_ON) 
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_ExtendedEntry_ERecIsSupportedByAvailableCombinedEvent(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  CombinedDTCGroup,
  CONST(uint8, AUTOMATIC)  ERecId
  );
#endif

# if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_ExtendedEntry_TestDTCHasERecConfigured
 *****************************************************************************/
/*!
 * \brief         Tests whether the DTC has the requested ERec configured.
 *
 * \details       Tests whether the DTC has the requested ERec configured.
 *
 * \param[in]     ERecId
 *                Identifier of the extended data record
 * \param[in]     CombinedDTCGroup
 *                Combined DTC group identifier
 * \param[out]    ERecEntryIndex
 *                If the function returns TRUE, the parameters contains
 *                index of the extended data record in the Dem_Cfg_DataCollectionTable
 * \return        TRUE
 *                Requested ERec is configured for DTC
 * \return        FALSE
 *                Requested ERec is not configured for DTC
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_ERECS == STD_ON) 
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_ExtendedEntry_TestDTCHasERecConfigured(
  CONST(uint8, AUTOMATIC)  ERecId,
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  CombinedDTCGroup,
  CONSTP2VAR(Dem_Cfg_ERecIndexType, AUTOMATIC, AUTOMATIC)  ERecEntryIndex
  );
#endif

/* ****************************************************************************
 * Dem_ExtendedEntry_IterInit
 *****************************************************************************/
/*!
 * \brief         Initializes the extended entry iterator
 *
 * \details       Initializes the iterator to enumerate extended entries in 
 *                an memory entry
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    IterPtr
 *                Pointer to the extended entry iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtendedEntry_IterInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_ExtendedEntry_IterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );

/* ****************************************************************************
 * Dem_ExtendedEntry_IterNext
 *****************************************************************************/
/*!
 * \brief         Move the extended entry iterator to the next element
 *
 * \details       Move the extended entry iterator to the next element
 *
 * \param[in,out] IterPtr
 *                Pointer to the extended entry iterator
 *
 * \pre           IterPtr has been initialized with Dem_ExtendedEntry_IterInit
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtendedEntry_IterNext(
  CONSTP2VAR(Dem_ExtendedEntry_IterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );

/* ****************************************************************************
 * Dem_ExtendedEntry_IterExists
 *****************************************************************************/
/*!
 * \brief         Test if the extended entry iterator points to a valid element
 *
 * \details       Test if the extended entry iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the extended entry iterator
 *
 * \return        TRUE
 *                IterPtr points to a valid element
 * \return        FALSE
 *                IterPtr doesn't point to a valid element
 *
 * \pre           IterPtr has been initialized with Dem_ExtendedEntry_IterInit
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ExtendedEntry_IterExists(
  CONSTP2CONST(Dem_ExtendedEntry_IterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );

/* ****************************************************************************
 * Dem_ExtendedEntry_IterGet
 *****************************************************************************/
/*!
 * \brief         Returns handle to the extended record descriptor table
 *
 * \details       Returns handle to the extended record descriptor table
 *
 * \param[in]     IterPtr
 *                Pointer to the extended entry iterator
 *
 * \return        Handle to the extended record descriptor table
 *
 * \pre           IterPtr is verified with Dem_ExtendedEntry_IterExists
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ERecIndexType, DEM_CODE)
Dem_ExtendedEntry_IterGet(
  CONSTP2CONST(Dem_ExtendedEntry_IterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_ExtendedEntry_IteratorGetExtendedRecordDataConstPtr
 *****************************************************************************/
/*!
 * \brief         Returns the extended data buffer
 *
 * \details       Returns a const pointer to the extended data buffer at the 
 *                given index
 *
 * \param[in]     MemoryEntryId
 *                Handle for memory entry
 * \param[in]     ExtendedEntryIndex
 *                Index of the extended data record
 *
 * \return        Pointer to the unmodifiable (const) extended data buffer
 *
 * \pre           ExtendedEntryIter has been initialized
 * \config        DEM_CFG_SUPPORT_USER_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_ExtendedEntry_IteratorGetExtendedRecordDataConstPtr(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  );
#endif

/* ****************************************************************************
 * Dem_ExtendedEntry_IteratorIsExtendedRecordStored
 *****************************************************************************/
/*!
 * \brief         Tests whether an extended record is currently stored
 *
 * \details       Tests whether an extended record at the given index is
 *                currently stored
 *
 * \param[in]     MemoryEntryId
 *                Handle for memory entry
 * \param[in]     ExtendedEntryIndex
 *                Index of the extended data record
 *
 * \return        TRUE
 *                The extended record is stored
 * \return        FALSE
 *                The extended record is not stored
 *
 * \pre           ExtendedEntryIter->MemoryEntryId must be inside valid range
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ExtendedEntry_IteratorIsExtendedRecordStored(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  );

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_ExtendedEntry_IteratorUpdateExtendedEntry
 *****************************************************************************/
/*!
 * \brief         Set the 'stored' flag for an extended entry
 *
 * \details       Set the corresponding bit in the extended header of the
 *                memory entry
 *
 * \param[in]     MemoryEntryId
 *                Handle for memory entry
 * \param[in]     ExtendedEntryIndex
 *                Index of the extended data record
 *
 * \pre           ExtendedEntryIter->MemoryEntryId must be inside valid range
 * \config        DEM_CFG_SUPPORT_USER_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtendedEntry_IteratorUpdateExtendedEntry(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  );
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_ExtendedEntry_CalculateUserERecStorageIndex
 *****************************************************************************/
/*!
 * \brief         Get index corresponding to the provided user extended data 
 *                record inside the combined DTC extended record status.
 *
 * \details       Get index corresponding to the provided user extended data 
 *                record inside the combined DTC extended record status.
 *
 * \param[in]     ERecId
 *                Identifier of the extended data record
 * \param[in]     CombinedGroupId
 *                Group ID representing the combined DTC
 *
 * \return        Index corresponding to the provided user extended data 
 *                record inside the combined DTC extended record status
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) 
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_ExtendedEntry_CalculateUserERecStorageIndex(
  CONST(uint8, AUTOMATIC)  ERecId,
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) CombinedGroupId
  );
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_ExtendedEntry_GetUserERecStorageStatus
 *****************************************************************************/
/*!
 * \brief         Calculate the storage status of a user extended data record                
 *
 * \details       Calculate the storage status of a user extended data record
 *                by comparing the bit status of the DTC specific storage 
 *                mask inside event memory entry
 *
 * \param[in]     UserERecStorageIndex
 *                Index pointing to position of extended data record inside the 
 *                DTC specific storage mask
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        TRUE
 *                User extended data record at requested index is stored
 * \return        FALSE
 *                User extended data record at requested index is not stored
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) 
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_ExtendedEntry_GetUserERecStorageStatus(
  CONST(uint8, AUTOMATIC)  UserERecStorageIndex,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_ExtendedEntry_SetUserERecStorageStatus
 *****************************************************************************/
/*!
 * \brief         Set the storage status of a user extended data record                
 *
 * \details       Set the storage status of a user extended data record
 *                by setting the bit status of the DTC specific storage 
 *                mask inside event memory entry
 *
 * \param[in]     UserERecStorageIndex
 *                Index pointing to position of extended data record inside the 
 *                DTC specific storage mask
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) 
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtendedEntry_SetUserERecStorageStatus(
  CONST(uint8, AUTOMATIC)  UserERecStorageIndex,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_EXTENDEDENTRY_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ExtendedEntry_Interface.h
 *********************************************************************************************************************/
