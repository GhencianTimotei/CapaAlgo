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
/*! \ingroup    Dem_Master
 *  \defgroup   Dem_Mem Memory Manager
 *  \{
 *  \file       Dem_Mem_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEM_INTERFACE_H)
#define DEM_MEM_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Mem_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Mem_PublicProperties Public Properties
 * \{
 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Mem_Private Private Methods
 * \{
 */
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Mem_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Mem_FreezeFrameObdIIGetDataPtr
 *****************************************************************************/
/*!
 * \brief         Get the data pointer for OBD FreezeFrame data of an OBD
 *                freezeframe entry
 *
 * \details       Get the data pointer for OBD FreezeFrame data of an OBD
 *                freezeframe entry
 *
 * \param[in]     Index
 *                Index of the freeze frame data
 *
 * \return        Pointer to OBD FreezeFrame data
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_Mem_FreezeFrameObdIIGetDataPtr(
  CONST(uint8, AUTOMATIC) Index
  );
#endif

/* ****************************************************************************
 * Dem_Mem_DebounceGetStoredValue
 *****************************************************************************/
/*!
 * \brief         Get the stored debounce value at position 'index'
 *
 * \details       Get the stored debounce value at position 'index'.
 *
 * \param[in]     Index
 *                Index of the debounce value
 *
 * \return        The stored debounce value
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_Mem_DebounceGetStoredValue(
  CONST(uint16, AUTOMATIC) Index
  );

/* ****************************************************************************
 * Dem_Mem_DebounceSetStoredValue
 *****************************************************************************/
/*!
 * \brief         Set the stored debounce value at position 'index'
 *
 * \details       Set the stored debounce value at position 'index'.
 *
 * \param[in]     Index
 *                Index of the debounce value
 * \param[in]     DebounceValue
 *                New stored debounce value at position 'index'
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Mem_DebounceSetStoredValue(
  CONST(uint16, AUTOMATIC) Index,
  CONST(sint16, AUTOMATIC) DebounceValue
  );


#if (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
/* ****************************************************************************
 * Dem_Mem_EventGetAvailableMask
 *****************************************************************************/
/*!
 * \brief         Get the event available mask at position 'index'
 *
 * \details       Get the event available mask at position 'index'.
 *
 * \param[in]     Index
 *                Index of the available mask
 *
 * \return        The event available mask at position 'index'
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Mem_EventGetAvailableMask(
  CONST(uint16, AUTOMATIC) Index
  );
#endif

#if (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
/* ****************************************************************************
 * Dem_Mem_EventSetAvailableMask
 *****************************************************************************/
/*!
 * \brief         Set the event available mask at position 'index'.
 *
 * \details       Set the event available mask at position 'index'.
 *
 * \param[in]     Index
 *                Index of the event available mask
 * \param[in]     Mask
 *                New event available mask at position 'index'
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Mem_EventSetAvailableMask(
  CONST(uint16, AUTOMATIC) Index,
  CONST(uint8, AUTOMATIC) Mask
  );
#endif

/* ****************************************************************************
 * Dem_Mem_FreezeFrameGetEvent
 *****************************************************************************/
/*!
 * \brief         Get the stored EventId of the freeze frame at position
 *                'Index'.
 *
 * \details       Get the stored EventId of the freeze frame at position
 *                'Index'.
 *
 * \param[in]     Index
 *                Index of the freeze frame
 *
 * \return        If OBDII is globally enabled: The stored EventId of the 
 *                freeze frame
 *                Else: the invalid EventId
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Mem_FreezeFrameGetEvent(
  CONST(uint8, AUTOMATIC)  Index
  );

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Mem_FreezeFrameSetEvent
 *****************************************************************************/
/*!
 * \brief         Set the EventId of the freeze frame at position 'Index'.
 *
 * \details       Set the EventId of the freeze frame at position 'Index'.
 *
 * \param[in]     Index
 *                Index of the freeze frame
 * \param[in]     EventId
 *                New EventId of freeze frame at position 'index'
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Mem_FreezeFrameSetEvent(
  CONST(uint8, AUTOMATIC)  Index,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Mem_FreezeFrameGetTimestamp
 *****************************************************************************/
/*!
 * \brief         Get the stored timestamp of the freeze frame at position
 *                'Index'.
 *
 * \details       Get the stored timestamp of the freeze frame at position
 *                'Index'.
 *
 * \param[in]     Index
 *                Index of the freeze frame
 *
 * \return        The stored timestamp of the freeze frame
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Mem_FreezeFrameGetTimestamp(
  CONST(uint8, AUTOMATIC)  Index
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Mem_FreezeFrameSetTimestamp
 *****************************************************************************/
/*!
 * \brief         Set the timestamp of the freeze frame at position 'Index'.
 *
 * \details       Set the timestamp of the freeze frame at position 'Index'.
 *
 * \param[in]     Index
 *                Index of the freeze frame
 * \param[in]     Timestamp
 *                New timestamp of freeze frame at position 'index'
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Mem_FreezeFrameSetTimestamp(
  CONST(uint8, AUTOMATIC)  Index,
  CONST(uint32, AUTOMATIC)  Timestamp
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_Mem_PermanentGetEvent
 *****************************************************************************/
/*!
 * \brief         Get the stored EventId of the permanent entry at position
 *                'Index'.
 *
 * \details       Get the stored EventId of the permanent entry at position
 *                'Index'.
 *
 * \param[in]     Index
 *                Index of the permanent entry
 *
 * \return        The stored EventId of the permanent entry
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Mem_PermanentGetEvent(
  CONST(uint8, AUTOMATIC)  Index
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_Mem_PermanentSetEvent
 *****************************************************************************/
/*!
 * \brief         Set the EventId of the permanent entry at position 'Index'.
 *
 * \details       Set the EventId of the permanent entry at position 'Index'.
 *
 * \param[in]     Index
 *                Index of the permanent entry
 * \param[in]     EventId
 *                New EventId of permanent entry at position 'index'
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Mem_PermanentSetEvent(
  CONST(uint8, AUTOMATIC)  Index,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_Mem_PermanentGetStatus
 *****************************************************************************/
/*!
 * \brief         Get the stored status of the permanent entry at position
 *                'Index'.
 *
 * \details       Get the stored status of the permanent entry at position
 *                'Index'.
 *
 * \param[in]     Index
 *                Index of the permanent entry
 *
 * \return        The stored status of the permanent entry
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Mem_PermanentGetStatus(
  CONST(uint8, AUTOMATIC)  Index
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_Mem_PermanentSetStatus
 *****************************************************************************/
/*!
 * \brief         Set the status of the permanent entry at position 'Index'.
 *
 * \details       Set the status of the permanent entry at position 'Index'.
 *
 * \param[in]     Index
 *                Index of the permanent entry
 * \param[in]     Status
 *                New status of permanent entry at position 'index'
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Mem_PermanentSetStatus(
  CONST(uint8, AUTOMATIC)  Index,
  CONST(uint8, AUTOMATIC)  Status
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_Mem_PermanentGetInitPattern
 *****************************************************************************/
/*!
 * \brief         Get the init pattern of the permanent memory.
 *
 * \details       Get the init pattern of the permanent memory.
 *
 * \return        The init pattern of the permanent memory
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Mem_PermanentGetInitPattern(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_Mem_PermanentSetInitPattern
 *****************************************************************************/
/*!
 * \brief         Set the init pattern of the permanent memory.
 *
 * \details       Set the init pattern of the permanent memory.
 *
 * \param[in]     InitPattern
 *                New init pattern to be set
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Mem_PermanentSetInitPattern(
  CONST(uint16, AUTOMATIC)  InitPattern
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Mem_StoreWwhObdFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Stores a WWHOBD Freeze Frame.
 *
 * \details       Stores a WWHOBD freeze frame.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           The event must be a WWHOBD relevant event.
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \return        DEM_DATA_USERDATA_CHANGED
 *                User provided data was updated.
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Mem_StoreWwhObdFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Mem_UpdateOBDIIFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Stores or updates an OBDII Freeze Frame.
 *
 * \details       Stores or updates the OBDII freeze frame data, visibility and
 *                time stamp depending on RequiredUpdates.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     FreezeFrameSlot
 *                FreezeFrame slot corresponding to the event.
 * \param[in]     RequiredUpdates
 *                Required freeze frame updates.
 *
 * \return        EventId of the event whose freeze frame was updated
 *
 * \pre           The event must be an OBD relevant event
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Mem_UpdateOBDIIFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC) FreezeFrameSlot,
  CONST(uint8, AUTOMATIC) RequiredUpdates
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Mem_FindOBDIIFreezeFrameSlot
 *****************************************************************************/
/*!
 * \brief         Finds an OBDII Freeze Frame storage slot.
 *                Determines, if freeze frame visbility must be updated.
 *
 * \details       This function tries to find an OBDII freeze frame storage slot
 *                for the given event. It also determines, if an invisible
 *                freeze frame related to a misfire or fuel system event must
 *                be made visible immediately.
 *
 * \param[in,out] DTCContext
 *                DTC processing context. This function updates the QualifyDTC
 *                member.
 *                TRUE: invisible freeze frame related to a misfire or fuel
 *                system event must be set visible before DCY qualification
 *                FALSE: no visibility change required
 * \param[in]     DisplacePendingFreezeFrame
 *                True if freeze frame displacement is enabled
 *                and the corresponding event is confirmed.
 *
 * \return        Freeze frame storage slot for the given event.
 *
 * \pre           The event must be an OBD relevant event.
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Mem_FindOBDIIFreezeFrameSlot(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
  CONST(boolean, AUTOMATIC) DisplacePendingFreezeFrame
  );
#endif

/* ****************************************************************************
 * Dem_Mem_Init_RestoreMemoryObd
 *****************************************************************************/
/*!
 * \brief         Initializes OBD Freeze Frame and Permanent memory
 *
 * \details       This function verifies the integrity of memory entries and
 *                links them up into the runtime control structures.
 *
 * \pre           NvM must have restored NV mirrors
 * \config        Feature OBD II or WWH-OBD is enabled
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Mem_Init_RestoreMemoryObd(
  void
  );

/* ****************************************************************************
 * Dem_Mem_IsDebounceNvEnabled
 *****************************************************************************/
/*!
 * \brief         Returns true if Debounce Counter storage in Nv is enabled
 * \details       -
 *
 * \return        TRUE
 *                Support for Debounce Counter storage in Nv
 * \return        FALSE
 *                Support for Debounce Counter storage in Nv
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Mem_IsDebounceNvEnabled(
  void
  );

/* ****************************************************************************
 * Dem_Mem_CopyDataDebounceNv
 *****************************************************************************/
/*!
 * \brief         Copies debounce values from debounce array to NVRAM mirror
 *
 * \details       This function copies all debounce counters and timer values
 *                that need to be stored in NV memory into the NV data buffer.
 *
 * \param[in]     NvBlockStatus
 *                Requested NvBlock status after copying
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Mem_CopyDataDebounceNv(
  CONST(uint8, AUTOMATIC)  NvBlockStatus
  );

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON)
/* ****************************************************************************
* Dem_Mem_FindDisplaceablePendingFreezeFrame
*****************************************************************************/
/*!
* \brief         Selects a displaceable Obd Freeze Frame entry
*
* \details       This function checks for pending freeze frames which can be
*                displaced by a confirmed freeze frame
*
* \param[in]     ReplaceMisfireOrFuelSys
*                TRUE: Replace freeze frames of misfire or fuel system events
*                FALSE: Do not replace freeze frames of misfire or fuel system
*                        events
*
* \return        Index of the displaceable entry. If displacing of pending
*                freeze frames is disabled, the number of configured
*                freeze frames will be returned.
*
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON && DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON
*
* \context       TASK/ISR2
* \synchronous   TRUE
* \reentrant     FALSE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Mem_FindDisplaceablePendingFreezeFrame(
CONST(boolean, AUTOMATIC)  ReplaceMisfireOrFuelSys
);
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
* Dem_Mem_IsFreezeFrameVisibleInMode02
*****************************************************************************/
/*!
* \brief         Tests if a freeze frame is visible in mode 02.
*
* \details       Tests if a freeze frame is visible in mode 02
*
* \return        TRUE:  Freeze frame visible in mode 02
*                FALSE: No freeze frame visible in mode 02
*
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON
*
* \context       TASK/ISR2
* \synchronous   TRUE
* \reentrant     FALSE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Mem_IsFreezeFrameVisibleInMode02(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
* Dem_Mem_GetFreezeFrameIndexMode02
*****************************************************************************/
/*!
* \brief         Returns the index of OBD Freeze Frame index visible in mode 02.
*
* \details       Returns the index of OBD Freeze Frame index visible in mode 02.
*
* \return        Index
*
* \pre           -
* \config        DEM_CFG_SUPPORT_DCM == STD_ON
*
* \context       TASK/ISR2
* \synchronous   TRUE
* \reentrant     FALSE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Mem_GetFreezeFrameIndexMode02(
  void
  );
#endif

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Mem_MemoryIndexofIumpr
 *****************************************************************************/
/*!
 * \brief         Get the NV Block handle of the IUMPR data block
 *
 * \details       Get the NV Block handle of the IUMPR data block
 *
 * \return        NV Block handle of the IUMPR data block
 *
 * \pre           -
 * \config        DEM_CFG_USE_NVM == STD_ON &&
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Mem_MemoryIndexofIumpr(
void
);
#endif

/* ****************************************************************************
 * Dem_Mem_FreezeFrameFindIndex
 *****************************************************************************/
/*!
 * \brief         Find the freeze frame index for the given event
 *
 * \details       This function scans the available freeze frame slots looking
 *                for the given event. If the event does not have a stored
 *                freeze frame, the maximum size for the freeze frame memory is
 *                returned.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Freeze Frame Index of the event if stored, otherwise
 *                Dem_Cfg_GlobalObdIIFFCount()
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Mem_FreezeFrameFindIndex(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if ( (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON) || (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON) )
/* ****************************************************************************
 * Dem_Mem_FreezeFrameDisplaced
 *****************************************************************************/
/*!
 * \brief         Remove a freeze frame due to event displacement
 *
 * \details       This function clears a freeze frame stored for the passed
 *                Event if OBDII is enabled
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON ||
 *                DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Mem_FreezeFrameDisplaced(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEM_INTERFACE_H */


/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Mem_Interface.h
 *********************************************************************************************************************/
