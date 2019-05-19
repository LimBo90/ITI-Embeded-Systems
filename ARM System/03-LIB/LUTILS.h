#ifndef LUTILS_H_
#define LUTILS_H_

#define LUTILS_SET_BIT(REG, BIT)  (REG |= (1<<BIT))
#define LUTILS_CLR_BIT(REG, BIT)  (REG &= ~(1<<BIT))
#define LUTILS_TOGGLE_BIT(REG, BIT)  (REG ^= (1<<BIT))
#define LUTILS_GET_BIT(REG, BIT)  ((REG >> BIT) &1)

#endif