#define SET_BIT(var, bitNo)  (var | (1<<bitNo))
#define CLR_BIT(var, bitNo)  (var & (255 ^ (1<<bitNo)))
#define TOGGLE_BIT(var, bitNo)  (var ^ (1<<bitNo))