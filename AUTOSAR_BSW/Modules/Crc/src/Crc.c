/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  Crc.c
 *        \brief  Cyclic redundancy check header file
 *
 *      \details  Crc module is used to calculate cyclic codes, which encode messages by adding a fixed-length check
 *                value, for the purpose of error detection. Data blocks get a short CRC value attached, which is
 *                based on the remainder of a polynomial division of their contents. Upon retrieval of block data,
 *                the calculation is repeated and the calculated value is compared to the attached CRC value in order
 *                to ensure data integrity.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Crc.h"
#include "Crc_Tables.h"

/**********************************************************************************************************************
 *  VERSION CHECK  \trace SPEC-24723
 *********************************************************************************************************************/
#if(   (CRC_SW_MAJOR_VERSION != (6u) ) \
    || (CRC_SW_MINOR_VERSION != (0u) ))
# error "Version numbers of Crc.c and Crc.h are inconsistent!"
#endif

#if(   (CRC_CFG_MAJOR_VERSION != (3u) ) \
    || (CRC_CFG_MINOR_VERSION != (1u) ))
# error "Version numbers of Crc.c and Crc_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**** API Defines *****************************************************************************************************/

/* CRC8 polynomial */
#define CRC_INITIAL_VALUE8          (0xFFu)
#define CRC_POLYNOMIAL_8            (0x1Du)
#define CRC_FINAL_XOR_CRC8          (0xFFu)

/* CRC8 H2F polynomial */
#define CRC_INITIAL_VALUE8H2F       (0xFFu)
#define CRC_POLYNOMIAL_8H2F         (0x2Fu)
#define CRC_FINAL_XOR_CRC8H2F       (0xFFu)

/* CRC16 polynomial */
#define CRC_INITIAL_VALUE16         (0xFFFFu)
#define CRC_POLYNOMIAL_16           (0x1021u)

/* CRC32 polynomial */
#define CRC_INITIAL_VALUE32         (uint32)(0xFFFFFFFFuL)
#define CRC_POLYNOMIAL_32           (uint32)(0x04C11DB7uL)
#define CRC_POLYNOMIAL_32_REFLECT   (uint32)(0xEDB88320uL)
#define CRC_FINAL_XOR_CRC32         (uint32)(0xFFFFFFFFuL)

/* CRC32P4 polynomial */
#define CRC_INITIAL_VALUE32P4       (uint32)(0xFFFFFFFFuL)
#define CRC_POLYNOMIAL_32P4         (uint32)(0xF4ACFB13uL)
#define CRC_POLYNOMIAL_32P4_REFLECT (uint32)(0xC8DF352FuL)
#define CRC_FINAL_XOR_CRC32P4       (uint32)(0xFFFFFFFFuL)

/* CRC64 polynomial */
#define CRC_INITIAL_VALUE64         (0xFFFFFFFFFFFFFFFFuLL)
#define CRC_POLYNOMIAL_64           (0x42F0E1EBA9EA3693uLL)
#define CRC_POLYNOMIAL_64_REFLECT   (0xC96C5795D7870F42uLL)
#define CRC_FINAL_XOR_CRC64         (0xFFFFFFFFFFFFFFFFuLL)


#if ( (CRC_16_MODE    == CRC_16_TABLE_4) \
   || (CRC_32P4_MODE  == CRC_32P4_TABLE_4) \
   || (CRC_64_MODE    == CRC_64_TABLE_4) )
/* Chunk size when using slice-by-4 mechanism. 4 bytes will be processed at once. */
# define CRC_SB4_CHUNKSIZE 4u
#endif

#if ( (CRC_16_MODE    == CRC_16_TABLE_8) \
   || (CRC_32P4_MODE  == CRC_32P4_TABLE_8) \
   || (CRC_64_MODE    == CRC_64_TABLE_8))
/* Chunk size when using slice-by-8 mechanism. 8 bytes will be processed at once. */
# define CRC_SB8_CHUNKSIZE 8u
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (CRC_LOCAL) /* COV_CRC_COMPATIBILITY */
# define CRC_LOCAL static
#endif

#if !defined (CRC_LOCAL_INLINE) /* COV_CRC_COMPATIBILITY */
# define CRC_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CRC_START_SEC_CODE
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( (CRC_8_MODE == CRC_8_RUNTIME) || (CRC_8H2F_MODE == CRC_8H2F_RUNTIME) )
/**********************************************************************************************************************
 *  Crc_CalculateCRC8Runtime()
 *********************************************************************************************************************/
/*!
 * \brief       Performs runtime calculation of 8-bit CRC values
 * \details     This service is used by Crc_CalculateCRC8 and Crc_CalculateCRC8H2F routines.
 * \param[in]   Crc_Length      Length of data to be processed.
 * \param[in]   Crc_DataPtr     Data to be processed. 
 *                              Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value       Start value for processing.
 * \param[in]   Crc_Poly        Polynomial to use for CRC8 calculation.
 * \return      Calculated 8-bit CRC value
 * \pre         -
 * \config      CRC_8_RUNTIME or CRC_8H2F_RUNTIME
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
CRC_LOCAL FUNC(uint8, CRC_PRIVATE_CODE) Crc_CalculateCRC8Runtime(
  uint32 Crc_Length, 
  Crc_DataRefType Crc_DataPtr, 
  uint8 Crc_Value, 
  uint8 Crc_Poly);
#endif

#if (CRC_16_MODE == CRC_16_RUNTIME)
/**********************************************************************************************************************
 *  Crc_CalculateCRC16Runtime()
 *********************************************************************************************************************/
/*!
 * \brief       Performs runtime calculation of 16-bit CRC values.
 * \details     -
 * \param[in]   Crc_Length    Length of data to be processed.
 * \param[in]   Crc_DataPtr   Data to be processed. 
 *                            Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value     Start value for processing.
 * \return      Calculated 16-bit CRC value.
 * \pre         -
 * \config      CRC_16_RUNTIME
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
CRC_LOCAL FUNC(uint16, CRC_PRIVATE_CODE) Crc_CalculateCRC16Runtime(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint16 Crc_Value);
#endif

#if (CRC_16_MODE == CRC_16_TABLE)
/**********************************************************************************************************************
 *  Crc_CalculateCRC16Table()
 *********************************************************************************************************************/
/*!
 * \brief       Performs table based calculation of 16-bit CRC values.
 * \details     -
 * \param[in]   Crc_Length    Length of data to be processed.
 * \param[in]   Crc_DataPtr   Data to be processed. 
 *                            Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value     Start value for processing.
 * \return      Calculated 16-bit CRC value.
 * \pre         -
 * \config      CRC_16_TABLE
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
CRC_LOCAL FUNC(uint16, CRC_PRIVATE_CODE) Crc_CalculateCRC16Table(
  uint32 Crc_Length, 
  Crc_DataRefType Crc_DataPtr, 
  uint16 Crc_Value
);
#endif

#if (CRC_16_MODE == CRC_16_TABLE_4)
/**********************************************************************************************************************
 *  Crc_CalculateCRC16Table_SB4()
 *********************************************************************************************************************/
/*!
 * \brief       Performs table based calculation of 16-bit CRC values. 
 * \details     Uses 4 precalculated tables; requires more ROM.
 * \param[in]   Crc_Length    Length of data to be processed.
 * \param[in]   Crc_DataPtr   Data to be processed. 
 *                            Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value     Start value for processing.
 * \return      Calculated 16-bit CRC value.
 * \pre         -
 * \config      CRC_16_TABLE_4
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
CRC_LOCAL FUNC(uint16, CRC_PRIVATE_CODE) Crc_CalculateCRC16Table_SB4(
  uint32 Crc_Length, 
  Crc_DataRefType Crc_DataPtr, 
  uint16 Crc_Value
);
#endif

#if (CRC_16_MODE == CRC_16_TABLE_8)
/**********************************************************************************************************************
 *  Crc_CalculateCRC16Table_SB8()
 *********************************************************************************************************************/
/*!
 * \brief       Performs table based calculation of 16-bit CRC values. 
 * \details     Uses 8 precalculated tables; requires more ROM.
 * \param[in]   Crc_Length    Length of data to be processed.
 * \param[in]   Crc_DataPtr   Data to be processed. 
 *                            Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value     Start value for processing.
 * \return      Calculated 16-bit CRC value.
 * \pre         -
 * \config      CRC_16_TABLE_8
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
CRC_LOCAL FUNC(uint16, CRC_PRIVATE_CODE) Crc_CalculateCRC16Table_SB8(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint16 Crc_Value);
#endif

#if ( (CRC_32_MODE == CRC_32_RUNTIME) || (CRC_32P4_MODE == CRC_32P4_RUNTIME) )
/**********************************************************************************************************************
 *  Crc_CalculateCRC32Runtime()
 *********************************************************************************************************************/
/*!
 * \brief       Performs runtime calculation of 32-bit CRC values
 * \details     This service is used by Crc_CalculateCRC32 and Crc_CalculateCRC32P4 routines.
 * \param[in]   Crc_Length    Length of data to be processed.
 * \param[in]   Crc_DataPtr   Data to be processed. 
 *                            Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value     Start value for processing.
 * \param[in]   Crc_PolyReflected
 * \return      Calculated 32-bit CRC value
 * \pre         -
 * \config      CRC_32_RUNTIME or CRC_32P4_RUNTIME
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
CRC_LOCAL FUNC(uint32, CRC_PRIVATE_CODE) Crc_CalculateCRC32Runtime(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint32 Crc_Value,
  uint32 Crc_PolyReflected);
#endif

#if (CRC_32P4_MODE == CRC_32P4_TABLE)
/**********************************************************************************************************************
 *  Crc_CalculateCRC32P4Table()
 *********************************************************************************************************************/
/*!
 * \brief       Performs table based calculation of 32-bit CRC values.
 * \details     -
 * \param[in]   Crc_Length    Length of data to be processed.
 * \param[in]   Crc_DataPtr   Data to be processed. 
 *                            Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value     Start value for processing.
 * \return      Calculated 32-bit CRC value
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 * \config      CRC_32P4_TABLE
 * \pre         -
 */
CRC_LOCAL FUNC(uint32, CRC_PRIVATE_CODE) Crc_CalculateCRC32P4Table(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint32 Crc_Value);
#endif

#if (CRC_32P4_MODE == CRC_32P4_TABLE_4)
/**********************************************************************************************************************
 *  Crc_CalculateCRC32P4Table_SB4()
 *********************************************************************************************************************/
/*!
 * \brief       Performs table based calculation of 32-bit CRC values.
 * \details     -
 * \param[in]   Crc_Length    Length of data to be processed.
 * \param[in]   Crc_DataPtr   Data to be processed. 
 *                            Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value     Start value for processing.
 * \return      Calculated 32-bit CRC value.
 * \context     TASK 
 * \reentrant   TRUE 
 * \synchronous TRUE 
 * \config      CRC_32P4_TABLE_4
 * \pre         -
 */
CRC_LOCAL FUNC(uint32, CRC_PRIVATE_CODE) Crc_CalculateCRC32P4Table_SB4(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint32 Crc_Value);
#endif

#if (CRC_32P4_MODE == CRC_32P4_TABLE_8)
/**********************************************************************************************************************
 *  Crc_CalculateCRC32P4Table_SB8()
 *********************************************************************************************************************/
/*!
 * \brief       Performs table based calculation of 32-bit CRC values.
 * \details     -
 * \param[in]   Crc_Length    Length of data to be processed.
 * \param[in]   Crc_DataPtr   Data to be processed. 
 *                            Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value     Start value for processing.
 * \return      Calculated 32-bit CRC value.
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 * \config      CRC_32P4_TABLE_8
 * \pre         -
 */
CRC_LOCAL FUNC(uint32, CRC_PRIVATE_CODE) Crc_CalculateCRC32P4Table_SB8(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint32 Crc_Value);
#endif

#if (CRC_64_MODE == CRC_64_RUNTIME)
/**********************************************************************************************************************
 *  Crc_CalculateCRC64Runtime()
 *********************************************************************************************************************/
/*!
 * \brief       Performs runtime calculation of 64-bit CRC values
 * \details     Performs runtime calculation of 64-bit CRC values. This service is used by Crc_CalculateCRC64 routine.
 * \param[in]   Crc_Length          Length of data to be processed.
 * \param[in]   Crc_DataPtr         Data to be processed. 
 *                                  Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value           CRC start value for further processing.
 * \param[in]   Crc_PolyReflected   Reflected CRC64 polynomial to be used.
 * \return      Calculated 64-bit CRC value
 * \pre         -
 * \config      CRC_64_RUNTIME
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
CRC_LOCAL FUNC(uint64, CRC_PRIVATE_CODE) Crc_CalculateCRC64Runtime(
  uint32 Crc_Length, 
  Crc_DataRefType Crc_DataPtr, 
  uint64 Crc_Value, 
  uint64 Crc_PolyReflected);
#endif

#if (CRC_64_MODE == CRC_64_TABLE)
/**********************************************************************************************************************
 *  Crc_CalculateCRC64Table()
 *********************************************************************************************************************/
/*!
 * \brief       Performs table based calculation of 64-bit CRC values
 * \details     -
 * \param[in]   Crc_Length          Length of data to be processed.
 * \param[in]   Crc_DataPtr         Data to be processed. 
 *                                  Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value           CRC start value for further processing.
 * \return      Calculated 64-bit CRC value
 * \pre         -
 * \config      CRC_64_TABLE
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
CRC_LOCAL FUNC(uint64, CRC_PRIVATE_CODE) Crc_CalculateCRC64Table(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint64 Crc_Value);
#endif

#if (CRC_64_MODE == CRC_64_TABLE_4)
/**********************************************************************************************************************
 *  Crc_CalculateCRC64Table_SB4()
 *********************************************************************************************************************/
/*!
 * \brief       Performs table based calculation of 64-bit CRC values.
 * \details     Uses slice-by-4 concept for faster calculation.
 * \param[in]   Crc_Length          Length of data to be processed.
 * \param[in]   Crc_DataPtr         Data to be processed. 
 *                                  Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value           CRC start value for further processing.
 * \return      Calculated 64-bit CRC value
 * \pre         -
 * \config      CRC_64_TABLE_4
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
CRC_LOCAL FUNC(uint64, CRC_PRIVATE_CODE) Crc_CalculateCRC64Table_SB4(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint64 Crc_Value);
#endif

#if (CRC_64_MODE == CRC_64_TABLE_8)
/**********************************************************************************************************************
 *  Crc_CalculateCRC64Table_SB8()
 *********************************************************************************************************************/
/*!
 * \brief       Performs table based calculation of 64-bit CRC values.
 * \details     Uses slice-by-8 concept for faster calculation.
 * \param[in]   Crc_Length          Length of data to be processed.
 * \param[in]   Crc_DataPtr         Data to be processed. 
 *                                  Must not be NULL and must be valid for the duration of the CRC calculation.
 * \param[in]   Crc_Value           CRC start value for further processing.
 * \return      Calculated 64-bit CRC value
 * \pre         -
 * \config      CRC_64_TABLE_8
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
CRC_LOCAL FUNC(uint64, CRC_PRIVATE_CODE) Crc_CalculateCRC64Table_SB8(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint64 Crc_Value);
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

#if ( (CRC_8_MODE == CRC_8_RUNTIME) || (CRC_8H2F_MODE == CRC_8H2F_RUNTIME) )
/**********************************************************************************************************************
 *  Crc_CalculateCRC8Runtime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
CRC_LOCAL FUNC(uint8, CRC_PRIVATE_CODE) Crc_CalculateCRC8Runtime(
  uint32 Crc_Length, 
  Crc_DataRefType Crc_DataPtr, 
  uint8 Crc_Value, 
  uint8 Crc_Poly)
{
  uint32 Crc_DataPtrAddr;
  uint8 Crc_LoopCounter;
  uint8 Crc_CalcValue;

  Crc_CalcValue = Crc_Value;

  /* #10 Perform CRC calculation for each byte in Crc_DataPtr */
  for (Crc_DataPtrAddr = 0; Crc_DataPtrAddr < Crc_Length; Crc_DataPtrAddr++)
  {
    /* #20 XOR next byte of Crc_DataPtr with current CRC value. This is equivalent to calculating CRC value of 
     *     concatenated bytes */
    Crc_CalcValue ^= Crc_DataPtr[Crc_DataPtrAddr];

    /* #30 Perform modulo-2 division, a bit at a time */
    for (Crc_LoopCounter = 0u; Crc_LoopCounter < 8u; Crc_LoopCounter++)
    {
      /* #35 If MSB is 1, CRC value is XORed with polynomial */
      if ((Crc_CalcValue & (uint8) 0x80u) > 0u)
      {
        Crc_CalcValue = ( (uint8)(Crc_CalcValue << 1u) ) ^ Crc_Poly;
      }
      else
      {
        Crc_CalcValue = (uint8) (Crc_CalcValue << 1u);
      }
    }
  }

  return Crc_CalcValue;
}
#endif


#if (CRC_16_MODE == CRC_16_RUNTIME)
/**********************************************************************************************************************
 *  Crc_CalculateCRC16Runtime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
CRC_LOCAL FUNC(uint16, CRC_PRIVATE_CODE) Crc_CalculateCRC16Runtime(
    uint32 Crc_Length,
    Crc_DataRefType Crc_DataPtr,
    uint16 Crc_Value)
{
  uint32 Crc_DataPtrAddr;
  uint16 Crc_CalcValue;
  uint8 Crc_LoopCounter;

  Crc_CalcValue = Crc_Value;

  /* Perform CRC calculation for each byte in Crc_DataPtr */
  for (Crc_DataPtrAddr = 0; Crc_DataPtrAddr < Crc_Length; Crc_DataPtrAddr++)
  {
    /* XOR next byte of Crc_DataPtr with current CRC value. This is equivalent to calculating CRC value of 
       concatenated bytes */
    Crc_CalcValue ^= ((uint16)Crc_DataPtr[Crc_DataPtrAddr] << 8u);

    /* Perform modulo-2 division, a bit at a time */
    for (Crc_LoopCounter = 0u; Crc_LoopCounter < 8u; Crc_LoopCounter++)
    {
      /* If MSB is 1, CRC value is XORed with polynomial */
      if ((Crc_CalcValue & (uint16)0x8000u) > 0u)
      {
        Crc_CalcValue = ( (uint16)(Crc_CalcValue << 1u) ) ^ CRC_POLYNOMIAL_16;
      }
      else
      {
        Crc_CalcValue <<= 1u;
      }
    }
  }

  return Crc_CalcValue;
}
#endif

#if (CRC_16_MODE == CRC_16_TABLE)
/**********************************************************************************************************************
 *  Crc_CalculateCRC16Table()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
CRC_LOCAL FUNC(uint16, CRC_PRIVATE_CODE) Crc_CalculateCRC16Table(
  uint32 Crc_Length, 
  Crc_DataRefType Crc_DataPtr, 
  uint16 Crc_Value)
{
  uint32 Crc_DataPtrAddr;
  uint16 Crc_CalcValue = Crc_Value;
  uint8 TableIndex;

  for (Crc_DataPtrAddr = 0; Crc_DataPtrAddr < Crc_Length; Crc_DataPtrAddr++)
  {
    TableIndex = ((uint8)(Crc_CalcValue >> 8u)) ^ Crc_DataPtr[Crc_DataPtrAddr];
    Crc_CalcValue = (Crc_CalcValue << 8u) ^ Crc_Table16[TableIndex];
  }

  return Crc_CalcValue;
}
#endif

#if (CRC_16_MODE == CRC_16_TABLE_4)
/**********************************************************************************************************************
 *  Crc_CalculateCRC16Table_SB4()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
CRC_LOCAL FUNC(uint16, CRC_PRIVATE_CODE) Crc_CalculateCRC16Table_SB4(
  uint32 Crc_Length, 
  Crc_DataRefType Crc_DataPtr, 
  uint16 Crc_Value)
{
  uint32 Crc_DataPtrAddr = 0;
  uint16 Crc_CalcValue = Crc_Value;
  uint8 TableIndex;

  while(Crc_DataPtrAddr < Crc_Length)
  {
    /* Process 4 bytes as long as possible */
    if ((Crc_DataPtrAddr + CRC_SB4_CHUNKSIZE) <= Crc_Length)
    {
      /* Calculate chunks:
       * Note: 2-byte CRC start value is calculated within the first two table lookups */
      Crc_CalcValue = (
          (Crc_Table16_3[(Crc_DataPtr[Crc_DataPtrAddr     ]) ^ ((Crc_CalcValue >> 8)) ] ) ^
          (Crc_Table16_2[(Crc_DataPtr[Crc_DataPtrAddr + 1u]) ^ (Crc_CalcValue & 0xFFu)] ) ^
          (Crc_Table16_1[(Crc_DataPtr[Crc_DataPtrAddr + 2u])                          ] ) ^
          (Crc_Table16  [(Crc_DataPtr[Crc_DataPtrAddr + 3u])                          ] )
      );

      Crc_DataPtrAddr += CRC_SB4_CHUNKSIZE;
    }
    else /* Process the rest of data bytewise */
    {
      TableIndex = ((uint8) (Crc_CalcValue >> 8u)) ^ Crc_DataPtr[Crc_DataPtrAddr];
      Crc_CalcValue = (uint16)(Crc_CalcValue << 8u) ^ Crc_Table16[TableIndex];
      Crc_DataPtrAddr++;
    }
  }

  return Crc_CalcValue;
}
#endif

#if (CRC_16_MODE == CRC_16_TABLE_8)
/**********************************************************************************************************************
 *  Crc_CalculateCRC16Table_SB8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
CRC_LOCAL FUNC(uint16, CRC_PRIVATE_CODE) Crc_CalculateCRC16Table_SB8(
  uint32 Crc_Length, 
  Crc_DataRefType Crc_DataPtr, 
  uint16 Crc_Value)
{
  uint32 Crc_DataPtrAddr = 0;
  uint16 Crc_CalcValue = Crc_Value;
  uint8 TableIndex;

  while(Crc_DataPtrAddr < Crc_Length)
  {
    /* Process 8 bytes as long as possible */
    if ((Crc_DataPtrAddr + CRC_SB8_CHUNKSIZE) <= Crc_Length)
    {
      /* Calculate chunks:
       * Note: 2-byte CRC start value is calculated within the first two table lookups */
      Crc_CalcValue = (
          (Crc_Table16_7[(Crc_DataPtr[Crc_DataPtrAddr     ]) ^ ((Crc_CalcValue >> 8)) ] ) ^
          (Crc_Table16_6[(Crc_DataPtr[Crc_DataPtrAddr + 1u]) ^ (Crc_CalcValue & 0xFFu)] ) ^
          (Crc_Table16_5[(Crc_DataPtr[Crc_DataPtrAddr + 2u])                          ] ) ^
          (Crc_Table16_4[(Crc_DataPtr[Crc_DataPtrAddr + 3u])                          ] ) ^
          (Crc_Table16_3[(Crc_DataPtr[Crc_DataPtrAddr + 4u])                          ] ) ^
          (Crc_Table16_2[(Crc_DataPtr[Crc_DataPtrAddr + 5u])                          ] ) ^
          (Crc_Table16_1[(Crc_DataPtr[Crc_DataPtrAddr + 6u])                          ] ) ^
          (Crc_Table16  [(Crc_DataPtr[Crc_DataPtrAddr + 7u])                          ] )
          );

      Crc_DataPtrAddr += CRC_SB8_CHUNKSIZE;
    }
    else /* Process the rest of data bytewise */
    {
      TableIndex = ((uint8) (Crc_CalcValue >> 8u)) ^ Crc_DataPtr[Crc_DataPtrAddr];
      Crc_CalcValue = (uint16)(Crc_CalcValue << 8u) ^ Crc_Table16[TableIndex];
      Crc_DataPtrAddr++;
    }
  }

  return Crc_CalcValue;
}
#endif


#if ( (CRC_32_MODE == CRC_32_RUNTIME) || (CRC_32P4_MODE == CRC_32P4_RUNTIME) )
/**********************************************************************************************************************
 *  Crc_CalculateCRC32Runtime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CRC_LOCAL FUNC(uint32, CRC_PRIVATE_CODE) Crc_CalculateCRC32Runtime(
  uint32 Crc_Length, 
  Crc_DataRefType Crc_DataPtr, 
  uint32 Crc_Value, 
  uint32 Crc_PolyReflected)
{
  uint32 Crc_DataPtrAddr;
  uint8 Crc_LoopCounter;
  uint32 Crc_CalcValue;

  Crc_CalcValue = Crc_Value;

  /* #10 Perform CRC calculation for each byte in Crc_DataPtr */
  for (Crc_DataPtrAddr = 0; Crc_DataPtrAddr < Crc_Length; Crc_DataPtrAddr++)
  {
    /* #20 CRC32 routine considers reflection of input and output data. Instead of reflecting input and output data, a 
     *     reflected polynomial is used */
    /* #21 XOR next byte of Crc_DataPtr with current CRC value. This is equivalent to calculating CRC value of 
     *     concatenated bytes */
    Crc_CalcValue ^= (uint32) Crc_DataPtr[Crc_DataPtrAddr];

    /* #30 Perform modulo-2 division, a bit at a time */
    for (Crc_LoopCounter = 0u; Crc_LoopCounter < 8u; Crc_LoopCounter++)
    {
      /* #35 If LSB is 1, CRC value is XORed with polynomial */
      /* #36 Direction of modulo-2 division is reverse compared to Crc8 and Crc16, due to the reflection of the 
       *     polynomial */
      if ( (Crc_CalcValue & 1u) > 0u )
      {
        Crc_CalcValue = ( Crc_CalcValue >> 1u ) ^ Crc_PolyReflected;
      }
      else
      {
        Crc_CalcValue = Crc_CalcValue >> 1u;
      }
    }
  }

  return Crc_CalcValue;
}
#endif

#if (CRC_32P4_MODE == CRC_32P4_TABLE)
/**********************************************************************************************************************
 *  Crc_CalculateCRC32P4Table()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
CRC_LOCAL FUNC(uint32, CRC_PRIVATE_CODE) Crc_CalculateCRC32P4Table(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint32 Crc_Value)
{
  uint32 Crc_LoopCounter;
  uint32 Crc_CalcValue = Crc_Value;

  for ( Crc_LoopCounter = 0; Crc_LoopCounter < Crc_Length; Crc_LoopCounter++ )
  {
    Crc_CalcValue ^= (uint32)Crc_DataPtr[Crc_LoopCounter];
    Crc_CalcValue = (Crc_CalcValue >> 8u) ^ (Crc_Table32P4[(uint8)(Crc_CalcValue)]);
  }

  return Crc_CalcValue;
}
#endif

#if (CRC_32P4_MODE == CRC_32P4_TABLE_4)
/**********************************************************************************************************************
 *  Crc_CalculateCRC32P4Table_SB4()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
CRC_LOCAL FUNC(uint32, CRC_PRIVATE_CODE) Crc_CalculateCRC32P4Table_SB4(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint32 Crc_Value)
{
  uint32 Crc_DataPtrAddr = 0;
  uint32 Crc_CalcValue = Crc_Value;

  while (Crc_DataPtrAddr < Crc_Length)
  {
    /* Process 4 bytes as long as possible */
    if ((Crc_DataPtrAddr + CRC_SB4_CHUNKSIZE) <= Crc_Length)
    {
        /* Use each byte of the user buffer for lookups in different tables. */
        /* Use table entries as indices for table access. */
      Crc_CalcValue = (
          (Crc_Table32P4_3[(Crc_DataPtr[Crc_DataPtrAddr]) ^ ((uint8)(Crc_CalcValue & 0xFFu))]) ^
          (Crc_Table32P4_2[(Crc_DataPtr[Crc_DataPtrAddr + 1u]) ^ ((uint8)(Crc_CalcValue >> 8)) ]) ^
          (Crc_Table32P4_1[(Crc_DataPtr[Crc_DataPtrAddr + 2u]) ^ ((uint8)(Crc_CalcValue >> 16))]) ^
          (Crc_Table32P4  [(Crc_DataPtr[Crc_DataPtrAddr + 3u]) ^ ((uint8)(Crc_CalcValue >> 24))])
      );

      Crc_DataPtrAddr += CRC_SB4_CHUNKSIZE;
    }
    else /* Process the rest of data bytewise */
    {
      Crc_CalcValue ^= (uint32)Crc_DataPtr[Crc_DataPtrAddr];
      Crc_CalcValue = (Crc_CalcValue >> 8u) ^ (Crc_Table32P4[(uint8)(Crc_CalcValue )]);

      Crc_DataPtrAddr++;
    }
  }

  return Crc_CalcValue;
}
#endif

#if (CRC_32P4_MODE == CRC_32P4_TABLE_8)
/**********************************************************************************************************************
 *  Crc_CalculateCRC32P4Table_SB8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
CRC_LOCAL FUNC(uint32, CRC_PRIVATE_CODE) Crc_CalculateCRC32P4Table_SB8(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint32 Crc_Value)
{
  uint32 Crc_DataPtrAddr = 0;
  uint32 Crc_CalcValue = Crc_Value;

  while (Crc_DataPtrAddr < Crc_Length)
  {
    /* Process 8 bytes as long as possible */
    if ((Crc_DataPtrAddr + CRC_SB8_CHUNKSIZE) <= Crc_Length)
    {
        /* Use each byte of the user buffer for lookups in different tables. */
        /* Use table entries as indices for table access. */
      Crc_CalcValue = (
          (Crc_Table32P4_7[(Crc_DataPtr[Crc_DataPtrAddr]) ^ ((uint8)(Crc_CalcValue & 0xFFu))])^
          (Crc_Table32P4_6[(Crc_DataPtr[Crc_DataPtrAddr + 1u]) ^ ((uint8)(Crc_CalcValue >> 8)) ])^
          (Crc_Table32P4_5[(Crc_DataPtr[Crc_DataPtrAddr + 2u]) ^ ((uint8)(Crc_CalcValue >> 16))])^
          (Crc_Table32P4_4[(Crc_DataPtr[Crc_DataPtrAddr + 3u]) ^ ((uint8)(Crc_CalcValue >> 24))])^
          (Crc_Table32P4_3[(Crc_DataPtr[Crc_DataPtrAddr + 4u])]) ^
          (Crc_Table32P4_2[(Crc_DataPtr[Crc_DataPtrAddr + 5u])]) ^
          (Crc_Table32P4_1[(Crc_DataPtr[Crc_DataPtrAddr + 6u])]) ^
          (Crc_Table32P4  [(Crc_DataPtr[Crc_DataPtrAddr + 7u])])
          );

      Crc_DataPtrAddr += CRC_SB8_CHUNKSIZE;
    }
    else /* Process the rest of data bytewise */
    {
      Crc_CalcValue ^= (uint32)Crc_DataPtr[Crc_DataPtrAddr];
      Crc_CalcValue = (Crc_CalcValue >> 8u) ^ (Crc_Table32P4[(uint8)(Crc_CalcValue )]);

      Crc_DataPtrAddr++;
    }
  }

  return Crc_CalcValue;
}
#endif

#if (CRC_64_MODE == CRC_64_RUNTIME)
/**********************************************************************************************************************
 *  Crc_CalculateCRC64Runtime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CRC_LOCAL FUNC(uint64, CRC_PRIVATE_CODE) Crc_CalculateCRC64Runtime(
  uint32 Crc_Length, 
  Crc_DataRefType Crc_DataPtr, 
  uint64 Crc_Value, 
  uint64 Crc_PolyReflected)
{
  uint32 index;
  uint8 Crc_LoopCounter;
  uint64 Crc_CalcValue;

  Crc_CalcValue = Crc_Value;

  /* #10 Perform CRC calculation over Crc_Length in Crc_DataPtr */
  for (index = 0; index < Crc_Length; index++)
  {
    /* #20 CRC64 routine considers reflection of input and output data. Instead of reflecting input and output data, 
           a reflected polynomial is used */
    /* #21 XOR next byte of Crc_DataPtr with current CRC value. This is equivalent to calculating CRC value of 
           concatenated bytes */
    Crc_CalcValue ^= (uint64) Crc_DataPtr[index];

    /* #30 Perform modulo-2 division, a bit at a time */
    for (Crc_LoopCounter = 0u; Crc_LoopCounter < 8u; Crc_LoopCounter++)
    {
      /* #35 If LSB is 1, CRC value is XORed with polynomial */
      /* #36 Direction of modulo-2 division is reverse compared to Crc8 and Crc16, due to the reflection of the 
             polynomial */
      if ( (Crc_CalcValue & 1uL) > 0u )
      {
        Crc_CalcValue = ( Crc_CalcValue >> 1uL ) ^ Crc_PolyReflected;
      }
      else
      {
        Crc_CalcValue = Crc_CalcValue >> 1uL;
      }
    }
  }

  return Crc_CalcValue;
}
#endif

#if (CRC_64_MODE == CRC_64_TABLE)
/**********************************************************************************************************************
 *  Crc_CalculateCRC64Table()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
CRC_LOCAL FUNC(uint64, CRC_PRIVATE_CODE) Crc_CalculateCRC64Table(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint64 Crc_Value)
{
  uint64 Crc_CalcValue = Crc_Value;
  uint32 Crc_LoopCounter;

  for (Crc_LoopCounter = 0; Crc_LoopCounter < Crc_Length; Crc_LoopCounter++)
  {
    Crc_CalcValue ^= (uint64) Crc_DataPtr[Crc_LoopCounter];
    Crc_CalcValue = ( Crc_CalcValue >> 8uLL ) ^ ( Crc_Table64 [(uint8)(Crc_CalcValue)]);
  }

  return Crc_CalcValue;
}
#endif

#if (CRC_64_MODE == CRC_64_TABLE_4)
/**********************************************************************************************************************
 *  Crc_CalculateCRC64Table_SB4()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
CRC_LOCAL FUNC(uint64, CRC_PRIVATE_CODE) Crc_CalculateCRC64Table_SB4(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint64 Crc_Value)
{
  uint32 Crc_DataPtrAddr = 0;
  uint64 Crc_CalcValue = Crc_Value;

  while (Crc_DataPtrAddr < Crc_Length)
  {
    /* Process 4 bytes as long as possible */
    if ((Crc_DataPtrAddr + CRC_SB4_CHUNKSIZE) <= Crc_Length)
    {
        /* Use each byte of the user buffer for lookups in different tables. */
        /* Use table entries as indices for table access. */
      Crc_CalcValue = (
          (Crc_Table64_3[(Crc_DataPtr[Crc_DataPtrAddr]) ^ ((uint8)(Crc_CalcValue & 0xFFu))]) ^
          (Crc_Table64_2[(Crc_DataPtr[Crc_DataPtrAddr + 1u]) ^ ((uint8)(Crc_CalcValue >> 8)) ]) ^
          (Crc_Table64_1[(Crc_DataPtr[Crc_DataPtrAddr + 2u]) ^ ((uint8)(Crc_CalcValue >> 16))]) ^
          (Crc_Table64  [(Crc_DataPtr[Crc_DataPtrAddr + 3u]) ^ ((uint8)(Crc_CalcValue >> 24))]) ^
          /* The upper 4 bytes aren't used for table lookups */
          (Crc_CalcValue >> 32)
      );

      Crc_DataPtrAddr += CRC_SB4_CHUNKSIZE;
    }
    else /* Process the rest of data bytewise */
    {
      Crc_CalcValue ^= (uint64) Crc_DataPtr[Crc_DataPtrAddr];
      Crc_CalcValue = ( Crc_CalcValue >> 8uLL ) ^ ( Crc_Table64 [(uint8)(Crc_CalcValue)]);

      Crc_DataPtrAddr++;
    }
  }

  return Crc_CalcValue;
}
#endif

#if (CRC_64_MODE == CRC_64_TABLE_8)
/**********************************************************************************************************************
 *  Crc_CalculateCRC64Table_SB8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
CRC_LOCAL FUNC(uint64, CRC_PRIVATE_CODE) Crc_CalculateCRC64Table_SB8(
  uint32 Crc_Length,
  Crc_DataRefType Crc_DataPtr,
  uint64 Crc_Value)
{
  uint32 Crc_DataPtrAddr = 0;
  uint64 Crc_CalcValue = Crc_Value;

  while (Crc_DataPtrAddr < Crc_Length)
  {
    /* Process 8 bytes as long as possible */
    if ((Crc_DataPtrAddr + CRC_SB8_CHUNKSIZE) <= Crc_Length)
    {
      /* Calculate chunks:
       * Note: 2-byte CRC start value is calculated within the first two table lookups */
      Crc_CalcValue = (
          (Crc_Table64_7[(Crc_DataPtr[Crc_DataPtrAddr]) ^ ((uint8)(Crc_CalcValue & 0xFFu))]) ^
          (Crc_Table64_6[(Crc_DataPtr[Crc_DataPtrAddr + 1u]) ^ ((uint8)(Crc_CalcValue >> 8)) ]) ^
          (Crc_Table64_5[(Crc_DataPtr[Crc_DataPtrAddr + 2u]) ^ ((uint8)(Crc_CalcValue >> 16))]) ^
          (Crc_Table64_4[(Crc_DataPtr[Crc_DataPtrAddr + 3u]) ^ ((uint8)(Crc_CalcValue >> 24))]) ^
          (Crc_Table64_3[(Crc_DataPtr[Crc_DataPtrAddr + 4u]) ^ ((uint8)(Crc_CalcValue >> 32))]) ^
          (Crc_Table64_2[(Crc_DataPtr[Crc_DataPtrAddr + 5u]) ^ ((uint8)(Crc_CalcValue >> 40))]) ^
          (Crc_Table64_1[(Crc_DataPtr[Crc_DataPtrAddr + 6u]) ^ ((uint8)(Crc_CalcValue >> 48))]) ^
          (Crc_Table64  [(Crc_DataPtr[Crc_DataPtrAddr + 7u]) ^ ((uint8)(Crc_CalcValue >> 56))])
          );

      Crc_DataPtrAddr += CRC_SB8_CHUNKSIZE;
    }
    else /* Process the rest of data bytewise */
    {
      Crc_CalcValue ^= (uint64) Crc_DataPtr[Crc_DataPtrAddr];
      Crc_CalcValue = ( Crc_CalcValue >> 8uLL ) ^ ( Crc_Table64 [(uint8)(Crc_CalcValue)]);

      Crc_DataPtrAddr++;
    }
  }

  return Crc_CalcValue;
}
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Crc_CalculateCRC8
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(uint8, CRC_CODE) Crc_CalculateCRC8(
  Crc_DataRefType Crc_DataPtr, 
  uint32 Crc_Length, 
  uint8 Crc_StartValue8, 
  boolean Crc_IsFirstCall)
{
  uint8 Crc_Value;

#if (CRC_8_MODE == CRC_8_TABLE)
  uint32 Crc_LoopCounter;
#endif

  /* #10 Set initial value depending on whether it's the first call or a subsequent call */
  if( Crc_IsFirstCall == TRUE )
  {
      Crc_Value = CRC_INITIAL_VALUE8;
  }
  else
  {
      Crc_Value = (CRC_FINAL_XOR_CRC8 ^ Crc_StartValue8);
  }

#if (CRC_8_MODE == CRC_8_TABLE)
  /*********** TABLE CALCULATION *******************************************************************************/
  /* #20 Calculate CRC value by using a table */
  for (Crc_LoopCounter = 0; Crc_LoopCounter < Crc_Length; Crc_LoopCounter++)
  {
    Crc_Value = Crc_Table8[Crc_Value ^ Crc_DataPtr[Crc_LoopCounter]];
  }
#endif

#if (CRC_8_MODE == CRC_8_RUNTIME)
  /*********** RUNTIME CALCULATION *****************************************************************************/
  /* #30 Calculate CRC value via CRC8 routine */
  Crc_Value = Crc_CalculateCRC8Runtime(Crc_Length, Crc_DataPtr, Crc_Value, CRC_POLYNOMIAL_8);                           /* SBSW_CRC_02 */
#endif

  /* #40 Final CRC value is XORed */
  return Crc_Value ^ CRC_FINAL_XOR_CRC8;
}



/***********************************************************************************************************************
 *  Crc_CalculateCRC8H2F
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(uint8, CRC_CODE) Crc_CalculateCRC8H2F(
  Crc_DataRefType Crc_DataPtr, 
  uint32 Crc_Length, 
  uint8 Crc_StartValue8H2F, 
  boolean Crc_IsFirstCall)
{
  uint8 Crc_Value;

#if (CRC_8H2F_MODE == CRC_8H2F_TABLE)
  uint32 Crc_LoopCounter;
#endif

  /* #10 Set initial value depending on whether it's the first call or a subsequent call */
  if (Crc_IsFirstCall == TRUE)
  {
    Crc_Value = CRC_INITIAL_VALUE8H2F;
  }
  else
  {
    Crc_Value = (CRC_FINAL_XOR_CRC8H2F ^ Crc_StartValue8H2F);
  }

#if (CRC_8H2F_MODE == CRC_8H2F_TABLE)
  /*********** TABLE CALCULATION *******************************************************************************/
  /* #20 Calculate CRC value by using a table */
  for (Crc_LoopCounter = 0; Crc_LoopCounter < Crc_Length; Crc_LoopCounter++)
  {
    Crc_Value = Crc_Table8H2F[Crc_Value ^ Crc_DataPtr[Crc_LoopCounter]];
  }
#endif

#if (CRC_8H2F_MODE == CRC_8H2F_RUNTIME)
  /*********** RUNTIME CALCULATION *****************************************************************************/
  /* #30 Calculate CRC value via CRC8 routine */
  Crc_Value = Crc_CalculateCRC8Runtime(Crc_Length, Crc_DataPtr, Crc_Value, CRC_POLYNOMIAL_8H2F);                        /* SBSW_CRC_02 */
#endif

  /* #40 Final CRC value is XORed */
  return Crc_Value ^ CRC_FINAL_XOR_CRC8H2F;
}


/***********************************************************************************************************************
 *  Crc_CalculateCRC16
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(uint16, CRC_CODE) Crc_CalculateCRC16(
    Crc_DataRefType Crc_DataPtr,
    uint32 Crc_Length,
    uint16 Crc_StartValue16,
    boolean Crc_IsFirstCall)
{
  uint16 Crc_Value;

  /* Set initial value depending on whether it's the first call or a subsequent call */
  if (Crc_IsFirstCall == TRUE)
  {
    Crc_Value = CRC_INITIAL_VALUE16;
  }
  else
  {
    Crc_Value = Crc_StartValue16;
  }

  /* Calculate CRC value (depending on configured mode): */
#if (CRC_16_MODE == CRC_16_TABLE)
  Crc_Value = Crc_CalculateCRC16Table(Crc_Length, Crc_DataPtr, Crc_Value);                                              /* SBSW_CRC_02 */
#elif (CRC_16_MODE == CRC_16_TABLE_4)
  Crc_Value = Crc_CalculateCRC16Table_SB4(Crc_Length, Crc_DataPtr, Crc_Value);                                          /* SBSW_CRC_02 */
#elif (CRC_16_MODE == CRC_16_TABLE_8)
  Crc_Value = Crc_CalculateCRC16Table_SB8(Crc_Length, Crc_DataPtr, Crc_Value);                                          /* SBSW_CRC_02 */
#else
  Crc_Value = Crc_CalculateCRC16Runtime(Crc_Length, Crc_DataPtr, Crc_Value);                                            /* SBSW_CRC_02 */
#endif

  return Crc_Value;
}

/***********************************************************************************************************************
 *  Crc_CalculateCRC32
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(uint32, CRC_CODE) Crc_CalculateCRC32(
  Crc_DataRefType Crc_DataPtr, 
  uint32 Crc_Length, 
  uint32 Crc_StartValue32, 
  boolean Crc_IsFirstCall)
{
  uint32 Crc_Value;

#if (CRC_32_MODE == CRC_32_TABLE)
  uint32 Crc_LoopCounter;
#endif

  /* #10 Set initial value depending on whether it's the first call or a subsequent call */
  if( Crc_IsFirstCall == TRUE )
  {
    Crc_Value = CRC_INITIAL_VALUE32;
  }
  else
  {
    Crc_Value = (CRC_FINAL_XOR_CRC32 ^ Crc_StartValue32);
  }

#if (CRC_32_MODE == CRC_32_TABLE)
  /*********** TABLE CALCULATION *******************************************************************************/
  /* #20 Calculate CRC value by using a table */
  for (Crc_LoopCounter = 0; Crc_LoopCounter < Crc_Length; Crc_LoopCounter++)
  {
    Crc_Value ^= (uint32) Crc_DataPtr[Crc_LoopCounter];
    Crc_Value = ( Crc_Value >> 8u ) ^ ( Crc_Table32 [(uint8)(Crc_Value )]);
  }
#else
  /*********** RUNTIME CALCULATION *****************************************************************************/
  /* #30 Calculate CRC value via CRC32 routine */
  Crc_Value = Crc_CalculateCRC32Runtime(Crc_Length, Crc_DataPtr, Crc_Value, CRC_POLYNOMIAL_32_REFLECT);                 /* SBSW_CRC_02 */
#endif

  /* #40 Final CRC value is XORed */
  return Crc_Value ^ CRC_FINAL_XOR_CRC32;
}

/***********************************************************************************************************************
 *  Crc_CalculateCRC32P4
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(uint32, CRC_CODE) Crc_CalculateCRC32P4(
    Crc_DataRefType Crc_DataPtr,
    uint32 Crc_Length,
    uint32 Crc_StartValue32,
    boolean Crc_IsFirstCall)
{
  uint32 Crc_Value;

  /* Set initial value depending on whether it's the first call or a subsequent call */
  if( Crc_IsFirstCall == TRUE )
  {
    Crc_Value = CRC_INITIAL_VALUE32P4;
  }
  else
  {
    Crc_Value = (CRC_FINAL_XOR_CRC32P4 ^ Crc_StartValue32);
  }

 /* Calculate CRC value (depending on configured mode): */
#if (CRC_32P4_MODE == CRC_32P4_TABLE)
  Crc_Value = Crc_CalculateCRC32P4Table(Crc_Length, Crc_DataPtr, Crc_Value);                                            /* SBSW_CRC_02 */
#elif (CRC_32P4_MODE == CRC_32P4_TABLE_4)
  Crc_Value = Crc_CalculateCRC32P4Table_SB4(Crc_Length, Crc_DataPtr, Crc_Value);                                        /* SBSW_CRC_02 */
#elif (CRC_32P4_MODE == CRC_32P4_TABLE_8)
  Crc_Value = Crc_CalculateCRC32P4Table_SB8(Crc_Length, Crc_DataPtr, Crc_Value);                                        /* SBSW_CRC_02 */
#else
  /*********** RUNTIME CALCULATION *****************************************************************************/
  Crc_Value = Crc_CalculateCRC32Runtime(Crc_Length, Crc_DataPtr, Crc_Value, CRC_POLYNOMIAL_32P4_REFLECT);               /* SBSW_CRC_02 */
#endif

  /* Final CRC value is XORed */
  return Crc_Value ^ CRC_FINAL_XOR_CRC32P4;
}


/***********************************************************************************************************************
 *  Crc_CalculateCRC64
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(uint64, CRC_CODE) Crc_CalculateCRC64(
    Crc_DataRefType Crc_DataPtr,
    uint32 Crc_Length,
    uint64 Crc_StartValue64,
    boolean Crc_IsFirstCall)
{
  uint64 Crc_Value;

  if( Crc_IsFirstCall == TRUE )
  {
    Crc_Value = CRC_INITIAL_VALUE64;
  }
  else
  {
    Crc_Value = (CRC_FINAL_XOR_CRC64 ^ Crc_StartValue64);
  }

#if (CRC_64_MODE == CRC_64_TABLE)
  Crc_Value = Crc_CalculateCRC64Table(Crc_Length, Crc_DataPtr, Crc_Value);                                              /* SBSW_CRC_02 */
#elif (CRC_64_MODE == CRC_64_TABLE_4)
  Crc_Value = Crc_CalculateCRC64Table_SB4(Crc_Length, Crc_DataPtr, Crc_Value);                                          /* SBSW_CRC_02 */
#elif (CRC_64_MODE == CRC_64_TABLE_8)
  Crc_Value = Crc_CalculateCRC64Table_SB8(Crc_Length, Crc_DataPtr, Crc_Value);                                          /* SBSW_CRC_02 */
#else
  /*********** RUNTIME CALCULATION *****************************************************************************/
  Crc_Value = Crc_CalculateCRC64Runtime(Crc_Length, Crc_DataPtr, Crc_Value, CRC_POLYNOMIAL_64_REFLECT);                 /* SBSW_CRC_02 */
#endif

  return Crc_Value ^ CRC_FINAL_XOR_CRC64;
}



#if (CRC_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 *  Crc_GetVersionInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, CRC_CODE) Crc_GetVersionInfo (P2VAR(Std_VersionInfoType, AUTOMATIC, CRC_APPL_DATA) Versioninfo)
{
  if (Versioninfo != NULL_PTR)
  {
    Versioninfo->vendorID = CRC_VENDOR_ID;                                                                              /* SBSW_CRC_01 */
    Versioninfo->moduleID = CRC_MODULE_ID;                                                                              /* SBSW_CRC_01 */
    Versioninfo->sw_major_version = CRC_SW_MAJOR_VERSION;                                                               /* SBSW_CRC_01 */
    Versioninfo->sw_minor_version = CRC_SW_MINOR_VERSION;                                                               /* SBSW_CRC_01 */
    Versioninfo->sw_patch_version = CRC_SW_PATCH_VERSION;                                                               /* SBSW_CRC_01 */
  }
}
#endif



#define CRC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Module specific MISRA deviations:

MD_CRC_8.7_FileScopeStatic:
    Reason: CRC Calculation tables are defined outside of functions, in which they are used.
    This is done for reason of structural clarity.
    Risk: No risk.
    Prevention: Tables could be defined within calculation routines.

MD_CRC_10.3_Portability:
    Reason: Linux requires different type definitions. For the configurations that are used for big endian testing
            uint32 is defined as "unsigned int". Assigning values with the "uL" suffix causes this warning.
            This has nothing to do with the code itself.
    Risk: Integer values are cut off.
    Prevention: Cut-off integer values would result in wrong CRC values which would lead to failing tests.

*/

/* START_COVERAGE_JUSTIFICATION
    \ID COV_CRC_COMPATIBILITY
      \ACCEPT XF
      \ACCEPT TX
      \REASON [COV_MSR_COMPATIBILITY]
END_COVERAGE_JUSTIFICATION */

/* SBSW_JUSTIFICATION_BEGIN
   \ID SBSW_CRC_01
    \DESCRIPTION The function Crc_GetVersionInfo writes to the object referenced by parameter VersionInfoPtr
    \COUNTERMEASURE \N The caller ensures that the pointer passed to the parameter VersionInfoPtr is valid.

   \ID SBSW_CRC_02
    \DESCRIPTION Local function is called with pointer parameter Crc_DataPtr which was passed from caller of CRC 
                 library.
    \COUNTERMEASURE \N The caller ensures that the pointer passed to the parameter Crc_DataPtr is valid.
SBSW_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: Crc.c
 *********************************************************************************************************************/

