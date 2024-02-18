#include "Platform_Types.h"
#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "LPSPI.h"


void LPSPI0_init_master(void)
{
    /*! LPSPI0 Initialization:
     * */
    LPSPI0->CR    = 0x00000000;         /* Disable module for configuration       */
    LPSPI0->IER   = 0x00000000;         /* Interrupts not used              */
    LPSPI0->DER   = 0x00000000;         /* DMA not used                 */
    LPSPI0->CFGR0 = 0x00000000;         /* Defaults:                  */
    /* RDM0=0: rec'd data to FIFO as normal     */
    /* CIRFIFO=0; Circular FIFO is disabled     */
    /* HRSEL, HRPOL, HREN=0: Host request disabled */

    LPSPI0->CFGR1 = LPSPI_CFGR1_MASTER_MASK;  /* Configurations: master mode                  */
    /* PCSCFG=0: PCS[3:2] are enabled                 */
    /* OUTCFG=0: Output data retains last value when CS negated */
    /* PINCFG=0: SIN is input, SOUT is output             */
    /* MATCFG=0: Match disabled                   */
    /* PCSPOL=0: PCS is active low                */
    /* NOSTALL=0: Stall if Tx FIFO empty or Rx FIFO full      */
    /* AUTOPCS=0: does not apply for master mode          */
    /* SAMPLE=0: input data sampled on SCK edge           */
    /* MASTER=1: Master mode                    */

    LPSPI0->TCR   = LPSPI_TCR_CPHA_MASK
            |LPSPI_TCR_PRESCALE(0)
            |LPSPI_TCR_PCS(0)
            |LPSPI_TCR_FRAMESZ(7);   /* Transmit cmd: PCS0, 16 bits, prescale func'l clk by 4, etc */
    /* CPOL=0: SCK inactive state is low              */
    /* CPHA=1: Change data on SCK lead'g, capture on trail'g edge */
    /* PRESCALE=2: Functional clock divided by 2**2 = 4       */
    /* PCS=0: Transfer using PCS0                   */
    /* LSBF=0: Data is transfered MSB first             */
    /* BYSW=0: Byte swap disabled                   */
    /* CONT, CONTC=0: Continuous transfer disabled        */
    /* RXMSK=0: Normal transfer: rx data stored in rx FIFO    */
    /* TXMSK=0: Normal transfer: data loaded from tx FIFO       */
    /* WIDTH=0: Single bit transfer                 */
    /* FRAMESZ=7: # bits in frame = 7+1=8            */

    LPSPI0->CCR   = LPSPI_CCR_SCKPCS(0)
                          |LPSPI_CCR_PCSSCK(0)
                          |LPSPI_CCR_DBT(0)
                          |LPSPI_CCR_SCKDIV(3);
    /* SCKPCS=8: SCK to PCS delay = 4+1 = 5 (500 nsec)      */
    /* PCSSCK=8: PCS to SCK delay = 9+1 = 10 (1 usec)         */
    /* DBT=16: Delay between Transfers = 8+2 = 10 (1 usec)       */
    /* SCKDIV=3: SCK divider */

    LPSPI0->FCR   = LPSPI_FCR_TXWATER(3);     /* RXWATER=0: Rx flags set when Rx FIFO >0  */
    /* TXWATER=3: Tx flags set when Tx FIFO <= 3  */
}


extern void LPSPI0_ChangePeripheralClockInput(TYPE_EN_LPSPI0_PERIPHERAL_INPUT_CLOCK InputClock_EN)
{
    switch(InputClock_EN)
    {
        case LPSPI0_CLOCK_4_MHZ_E:
            LPSPI0->CCR   = LPSPI_CCR_SCKPCS(0)
            |LPSPI_CCR_PCSSCK(0)
            |LPSPI_CCR_DBT(0)
            |LPSPI_CCR_SCKDIV(0);
            break;
        case LPSPI0_CLOCK_24_MHZ_E:
            LPSPI0->CCR   = LPSPI_CCR_SCKPCS(0)
            |LPSPI_CCR_PCSSCK(0)
            |LPSPI_CCR_DBT(0)
            |LPSPI_CCR_SCKDIV(3);
            break;
        default:
            break;
    }
}


void LPSPI0_enable (void)
{
    /* Enable module for operation      */
    LPSPI0->CR    = LPSPI_CR_MEN_MASK;
    /*            |LPSPI_CR_DBGEN_MASK */
    /* DBGEN=1: module enabled in debug mode  */
    /* DOZEN=0: module enabled in Doze mode   */
    /* RST=0: Master logic not reset      */
    /* MEN=1: Module is enabled         */
}

void LPSPI0_disable (void)
{
    LPSPI0->CR = 0;
}

status_t LPSPI0_MasterSyncTransmit(const uint8 * sendBuffer,  uint8 * receiveBuffer,  uint16 transferByteCount)
{
    uint16 i =0;
    status_t ret = STATUS_SUCCESS;
    uint32 timeOut = 48 * transferByteCount;

    LPSPI0->SR |= 0x00003F00UL;

    if (receiveBuffer == NULL)
    {
        LPSPI0->TCR |= LPSPI_TCR_RXMSK_MASK;
    }
    else
    {
        LPSPI0->TCR &= ~LPSPI_TCR_RXMSK_MASK;
    }

    for ( i=0 ;i<transferByteCount;i++)
    {
        while((LPSPI0->SR & LPSPI_SR_TDF_MASK) >>LPSPI_SR_TDF_SHIFT==0)
        {
            if (timeOut == 0)
            {
                return STATUS_TIMEOUT;
            }
            timeOut--;

        }/* Wait for Tx FIFO available  */

        LPSPI0->TDR = sendBuffer[i]; /* Transmit data         */

        if (receiveBuffer != NULL)
        {
            while((LPSPI0->SR & LPSPI_SR_RDF_MASK) >>LPSPI_SR_RDF_SHIFT==0)
            {
                if (timeOut == 0)
                {
                    return STATUS_TIMEOUT;
                }
                timeOut--;
            }/* Wait at least one RxFIFO entry  */

            receiveBuffer[i] = LPSPI0->RDR; /* Read received data        */
        }

        if (LPSPI0->SR & (LPSPI_SR_REF_MASK | LPSPI_SR_TEF_MASK ))
        {
            return STATUS_TIMEOUT;
        }
    }

    while((LPSPI0->SR & LPSPI_SR_TCF_MASK) >>LPSPI_SR_TCF_SHIFT==0)
    {
        if (timeOut == 0)
        {
            return STATUS_TIMEOUT;
        }
        timeOut--;
    }/* Wait transmission complete flag   */

    return ret;
}
