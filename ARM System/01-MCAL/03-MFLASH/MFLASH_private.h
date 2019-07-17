#ifndef _MFLASH_PRIVATE_H
#define _MFLASH_PRIVATE_H

typedef struct
{
  u32 ACR;
  u32 KEYR;
  u32 OPTKEYR;
  u32 SR;
  u32 CR;
  u32 AR;
  u32 RESERVED;
  u32 OBR;
  u32 WRPR;
}FLASH_TYPE;

#define MFLASH ((volatile FLASH_TYPE *) (0x40022000))

/* Register PINS */
//FLASH_SR
#define BSY         0
#define PGERR       2
#define WRPRTERR    4
#define EOP         5
//FLASH_CR
#define PG      0
#define PER     1
#define MER     2
#define OPTPG   4
#define OPTER   5
#define STRT    6
#define LOCK    7
#define OPTWRE  9
#define ERRIE   10
#define EOPIE   12

/* FLASH Keys */
#define RDP_Key                  ((u16)0x00A5)
#define FLASH_KEY1               ((u32)0x45670123)
#define FLASH_KEY2               ((u32)0xCDEF89AB)

/* Delay definition */
#define ERASE_TIMEOUT          ((u32)0x000B0000)
#define PROGRAM_TIMEOUT        ((u32)0x00002000)

typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;


#endif
