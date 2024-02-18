/*
 * OC_Types.h
 *
 *  Created on: Apr 9, 2019
 *      Author: amot
 */

#ifndef OC_TYPES_H_
#define OC_TYPES_H_

/*! OC Modes */
typedef enum
{
    OC_MODE_UNDEFINED_E         = 0x00u,   /*!< Undefined OC-Mode */
    OC_MODE_BINARY_E            = 0x53u,   /*!< OC-Binary mode (used for customer specific binary-signals) */
    OC_MODE_FRAME_E             = 0x55u,   /*!< OC-Frame mode (used for customer specific frame-based signals) */
    OC_MODE_OFF_E               = 0xFEu,   /*!< OC-OFF (OC Output deactivated) */
} OC_MODE_EN_TYPE;

#endif /* OC_TYPES_H_ */
