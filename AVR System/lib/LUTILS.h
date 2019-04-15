#ifndef LUTILS_H_
#define LUTILS_H_

#define SET_BIT(REG, BIT)  (REG |= (1<<bitNo))
#define CLEAR_BIT(REG, BIT)  (REG &= ~(1<<bitNo))
#define TOGGLE_BIT(REG, BIT)  (REG ^= (1<<bitNo))
#define GET_BIT(REG, BIT)  ((REG >> BIT) &1)

#endif