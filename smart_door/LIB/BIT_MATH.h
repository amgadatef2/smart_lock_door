/*
 * BIT_MATH.h
 *
 * Created: 9/15/2023 10:06:57 AM
 *  Author: amgad
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/****************** BIT MATH ********************/
#define SET_BIT(REG , BIT)  (REG |= (1<<BIT))
#define CLR_BIT(REG , BIT)  (REG &=~ (1<<BIT))
#define TGL_BIT(REG , BIT)  (REG ^= (1<<BIT))
#define GET_BIT(REG , BIT)  ((REG >>BIT) & 0X01)
/***********************************************/

#endif /* BIT_MATH_H_ */