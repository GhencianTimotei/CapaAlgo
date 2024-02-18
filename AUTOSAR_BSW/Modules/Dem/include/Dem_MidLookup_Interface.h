/* *********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  --------------------------------------------------------------------------------------------------------------------
 */
/*!
 *  \ingroup    Dem_DtrIF
 *  \defgroup   Dem_MidLookup Mid/TID Lookup
 *  \{
 *  \file       Dem_MidLookup_Interface.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Public interface of MidLookup subcomponent
 *********************************************************************************************************************/

/* *********************************************************************************************************************
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 **********************************************************************************************************************/

#if !defined (DEM_MIDLOOKUP_INTERFACE_H)
#define DEM_MIDLOOKUP_INTERFACE_H

/* *********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_MidLookup_Types.h"
#include "Dem_DtrData_Types.h"
/* ------------------------------------------------------------------------- */


/* *********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 **********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_MidLookup_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_MidLookup_Init
 *****************************************************************************/
/*!
 * \brief         Initializes MidLookup functionality.
 *
 * \details       This function controls initialization of the MidLookup
 *                subcomponent.
 *
 * \pre           May only be called during initialization.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_Init(
  void
  );

/* ****************************************************************************
 * Dem_MidLookup_PreInit
 *****************************************************************************/
/*!
 * \brief         Pre-initializes MidLookup.
 *
 * \details       This function performs basic initialization to allow later
 *                full initialization.
 *
 * \pre           May only be called during pre-initialization.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_PreInit(
  void
  );

/* ****************************************************************************
 * Dem_MidLookup_UpdateMidVisibility
 *****************************************************************************/
/*!
 * \brief         Requests the immediate update of the available OBD MIDs.
 *
 * \details       As the visibility status of Dtrs can change during runtime
 *                and therefore MIDs might also not be visible anymore
 *                the application can trigger the update of the available
 *                OBD MIDs.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_UpdateMidVisibility(
  void
  );

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_NotifyVisibilityChanged()
 *****************************************************************************/
/*!
 * \brief         Notification to report a change in visibility.
 *
 * \details       If the visibility is reported changed, the next request
 *                to read supported Mids will recalculate the supported Mids
 *                automatically. The process can be started immediate with
 *                \see Dem_MidLookup_UpdateMidVisibility.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_NotifyVisibilityChanged(
  void
  );
#endif

/* ****************************************************************************
 * Dem_MidLookup_IsSupportedMid
 *****************************************************************************/
/*!
 * \brief         Check if a Mid is a supported Mid.
 *
 * \details       Check if a Mid is a supported Mid, i.e. 0x00, 0x20, 0x40....
 *
 * \param[in]     Mid
 *                MonitorId to check
 *
 * \return        TRUE
 *                MonitorId is a supported Mid
 * \return        TRUE
 *                MonitorId is not supported Mid
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_IsSupportedMid(
  CONST(uint8, AUTOMATIC)  Mid
  );

/* ****************************************************************************
 * Dem_MidLookup_GetSupportedMidValue
 *****************************************************************************/
/*!
 * \brief         Get the SupportedMidMask of a Mid.
 *
 * \details       Get the SupportedMidMask of a Mid. This will recalculate the
 *                Mid Visibility if changes are pending.
 *
 * \param[in]     Mid
 *                Requested MonitorId. This will return the value of
 *                the supported Mid Mask corresponding to the passed MonitorId.
 *
 * \return        Supported Mid Mask
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MidLookup_GetSupportedMidValue(
  CONST(uint8, AUTOMATIC)  Mid
  );

/* ****************************************************************************
 * Dem_MidLookup_GetTidCountOfMid
 *****************************************************************************/
/*!
 * \brief         Get the number of available TIDs for a MID.
 *
 * \details       Get the number of available TIDs for a MID.
 *
 * \param[in]     Mid
 *                MonitorId
 * \param[out]    TidCount
 *                Number of available Tids for the requested Mid
 *
 * \return        E_OK
 *                DTR data was successfully copied
 * \return        E_NOT_OK
 *                DTR data was not copied
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_MidLookup_GetTidCountOfMid(
  CONST(uint8, AUTOMATIC)  Mid,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  TidCount
  );

/* ****************************************************************************
 * Dem_MidLookup_FindDtrId
 *****************************************************************************/
/*!
 * \brief         Get the DTR handle for a OBDMID / TID combination.
 *
 * \details       Returns the DTR handle for a OBDMID / TID combination.
 *
 * \param[in]     Mid
 *                Mid number
 * \param[in]     TidIndex
 *                Zero based index of the requested Tid
 * \param[out]    Tid
 *                Tid number of the selected Tid
 *
 * \return        The DTR handle requested. The handle is invalid if the Mid/Tid
 *                combination does not exist.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_MidLookup_FindDtrId(
  CONST(uint8, AUTOMATIC) Mid,
  CONST(uint8, AUTOMATIC) TidIndex,
  CONSTP2VAR(uint8, AUTOMATIC, AUTOMATIC)  Tid
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MIDLOOKUP_INTERFACE_H */

/*!
 * \}
 */
/* *********************************************************************************************************************
 *  END OF FILE: Dem_MidLookup_Declarations.h
 **********************************************************************************************************************/
