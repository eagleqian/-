
#include "includes.h"

extern const MQXLITE_INITIALIZATION_STRUCT  MQX_init_struct;

int main(void)
{	
	// ��ʼ��mqx
	_mqxlite_init((MQXLITE_INITIALIZATION_STRUCT_PTR) &MQX_init_struct);
    // ����mqx
	_mqxlite();
	return 0;
}
