#include "a4of/panel_latch.h"
#include <string.h>
void a4of_74hc373_init(a4of_74hc373_t*l){if(!l)return;memset(l,0,sizeof(*l));l->output_enable_n=true;l->q_valid=false;}
void a4of_74hc373_set_data(a4of_74hc373_t*l,uint8_t d){if(!l)return;l->data=d;if(l->latch_enable){l->q=d;l->q_valid=true;}}
void a4of_74hc373_set_le(a4of_74hc373_t*l,bool h){if(!l)return;l->latch_enable=h;if(h){l->q=l->data;l->q_valid=true;}}
void a4of_74hc373_set_oe_n(a4of_74hc373_t*l,bool h){if(l)l->output_enable_n=h;}
bool a4of_74hc373_output(const a4of_74hc373_t*l,uint8_t*v){if(!l||!v||l->output_enable_n||!l->q_valid)return false;*v=l->q;return true;}
