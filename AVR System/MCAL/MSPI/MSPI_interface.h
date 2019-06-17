#ifndef MSPI_INTERFACE_H_
#define MSPI_INTERFACE_H_


#define MSPI_LSB_FIRST		0
#define MSPI_MSB_FIRST		1

#define MSPI_CLK_POLARITY_IDLE_LOW		0
#define MSPI_CLK_POLARITY_IDLE_HIGH 	    1

#define	MSPI_CLK_PHASE_SAMPLE_ON_LEADING		0
#define MSPI_CLK_PHASE_SAMPLE_ON_TRAILING		1

#define MSPI_DATA_ORDER_LSB_FIRST			0
#define MSPI_DATA_ORDER_MSB_FIRST           1

#define MSPI_DUMMY_DATA MSPI_CFG_DUMMY_DATA

void MSPI_voidMasterInit(void);

void MSPI_voidSlaveInit(void);

u8 MSPI_u8TransferData(u8 Data);



#endif /* MSPI_INTERFACE_H_ */
