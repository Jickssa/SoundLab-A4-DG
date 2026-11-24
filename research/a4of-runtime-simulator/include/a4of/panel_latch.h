#ifndef A4OF_PANEL_LATCH_H
#define A4OF_PANEL_LATCH_H
#include <stdbool.h>
#include <stdint.h>
typedef struct { uint8_t data,q; bool latch_enable,output_enable_n,q_valid; } a4of_74hc373_t;
void a4of_74hc373_init(a4of_74hc373_t*);
void a4of_74hc373_set_data(a4of_74hc373_t*,uint8_t);
void a4of_74hc373_set_le(a4of_74hc373_t*,bool);
void a4of_74hc373_set_oe_n(a4of_74hc373_t*,bool);
bool a4of_74hc373_output(const a4of_74hc373_t*,uint8_t*);
#endif
