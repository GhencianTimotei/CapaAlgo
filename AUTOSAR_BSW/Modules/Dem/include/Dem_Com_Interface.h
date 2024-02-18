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
/*! \ingroup    Dem_Shared
 *  \defgroup   Dem_Communication Communication
 *  \{
 *  \file       Dem_Com_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of communication subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_COM_INTERFACE_H)
#define DEM_COM_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Com_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Communication_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Com_SyncCompareAndSwap
 *****************************************************************************/
/*!
 * \brief         Perform atomic compare and swap.
 *
 * \details       Atomically:
 *                 - tests if the Address pointed to contains the passed old value
 *                 - if so, the function exchanges the old value with the new value.
 *
 * \param[in]     AddressPtr
 *                Pointer to the memory location to compare and swap
 * \param[in]     OldValue
 *                Expected value at the memory location
 * \param[in]     NewValue
 *                New value to write to the memory location
 *
 * \return        TRUE
 *                The value was written successfully
 * \return        FALSE
 *                The value could not be written due to modification
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Com_SyncCompareAndSwap(
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) AddressPtr,
  CONST(Dem_Com_ProcessorWordType, AUTOMATIC) OldValue,
  CONST(Dem_Com_ProcessorWordType, AUTOMATIC) NewValue
  );

/* ****************************************************************************
 * Dem_Com_TestBitInBitfield
 *****************************************************************************/
/*!
 * \brief         Read the current state of a bit in a bitfield.
 *
 * \details       Read the current state of a bit in a bitfield.
 *
 * \param[in]     BitfieldPtr
 *                Pointer to the bitfield
 * \param[in]     BitfieldSize
 *                Size of the bitfield array (number of words)
 * \param[in]     BitPosition
 *                Position of the bit
 *
 * \return        State of the bit
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Com_TestBitInBitfield(
  volatile CONSTP2CONST(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  );

/* ****************************************************************************
 * Dem_Com_SyncSetBitInBitfield
 *****************************************************************************/
/*!
 * \brief         Perform atomic update of a bit in a bitfield.
 *
 * \details       Atomically sets a bit in a bitfield.
 *
 * \param[in]     BitfieldPtr
 *                Pointer to the bitfield
 * \param[in]     BitfieldSize
 *                Size of the bitfield array (number of words)
 * \param[in]     BitPosition
 *                Position of the bit
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Com_SyncSetBitInBitfield(
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  );

/* ****************************************************************************
 * Dem_Com_SyncResetBitInBitfield
 *****************************************************************************/
/*!
 * \brief         Perform atomic update of a bit in a bitfield.
 *
 * \details       Atomically resets a bit in a bitfield.
 *
 * \param[in]     BitfieldPtr
 *                Pointer to the bitfield
 * \param[in]     BitfieldSize
 *                Size of the bitfield array (number of words)
 * \param[in]     BitPosition
 *                Position of the bit
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Com_SyncResetBitInBitfield(
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  );

/* ****************************************************************************
 * Dem_Com_SetBitInBitfield
 *****************************************************************************/
/*!
 * \brief         Perform update of a bit in a bitfield.
 *
 * \details       Sets a bit in a bitfield.
 *
 * \param[in]     BitfieldPtr
 *                Pointer to the bitfield
 * \param[in]     BitfieldSize
 *                Size of the bitfield array (number of words)
 * \param[in]     BitPosition
 *                Position of the bit
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Com_SetBitInBitfield(
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  );

/* ****************************************************************************
 * Dem_Com_ResetBitInBitfield
 *****************************************************************************/
/*!
 * \brief         Perform update of a bit in a bitfield.
 *
 * \details       Resets a bit in a bitfield.
 *
 * \param[in]     BitfieldPtr
 *                Pointer to the bitfield
 * \param[in]     BitfieldSize
 *                Size of the bitfield array (number of words)
 * \param[in]     BitPosition
 *                Position of the bit
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Com_ResetBitInBitfield(
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_COM_INTERFACE_H */
/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Com_Interface.h
 *********************************************************************************************************************/
