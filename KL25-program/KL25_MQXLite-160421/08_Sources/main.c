
#include "includes.h"

extern const MQXLITE_INITIALIZATION_STRUCT  MQX_init_struct;

int main(void)
{	
	// ≥ı ºªØmqx
	_mqxlite_init((MQXLITE_INITIALIZATION_STRUCT_PTR) &MQX_init_struct);
    // ∆Ù∂Ømqx
	_mqxlite();
	return 0;
}
