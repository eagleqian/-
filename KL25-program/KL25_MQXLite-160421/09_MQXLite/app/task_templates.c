/*
 * tasks.c
 *
 *  Created on: Dec 13, 2012
 *      Author: SY
 */
#include "app_inc.h"
// Ϊ����������ע������ջ
const uint_8 * mqx_task_stack_pointers[] = 
{
    task_main_stack,
    NULL
};
// ����ģ���б�
const TASK_TEMPLATE_STRUCT MQX_template_list[] =
{
    // ������,  ������,   ����ջ��С,        ���ȼ�, ������,   ��������
    {TASK_MAIN, task_main, TASK_MAIN_STACK_SIZE,  9,   "main",MQX_AUTO_START_TASK},
    {TASK_A,    task_A,    TASK_A_STACK_SIZE,     10,  "task_A", 0},
    {TASK_B,    task_B,    TASK_B_STACK_SIZE,     10,  "task_B", 0},
    {TASK_C,    task_C,    TASK_C_STACK_SIZE,     10,  "task_C", 0},
    {TASK_D,    task_D,    TASK_D_STACK_SIZE,     8,   "task_D", 0},
    {0}
};
