/*
** ###################################################################
**     Processors:          MKL25Z128VFM4
**                          MKL25Z128VFT4
**                          MKL25Z128VLH4
**                          MKL25Z128VLK4
**
**     Compiler:            GNU C Compiler
**     Reference manual:    KL25P80M48SF0RM, Rev.3, Sep 2012
**     Version:             rev. 2.5, 2015-02-19
**     Build:               b150220
**
**     Abstract:
**         Linker file for the GNU C Compiler
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
** ###################################################################
*/

/* ���ý���� */
ENTRY(Reset_Handler)

/* ���öѺ�ջ�Ĵ�С */
HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x0000;
STACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x0400;

/* �����ڴ��и�������Ĵ�С */
MEMORY
{
  m_interrupts          (RX)  : ORIGIN = 0x00000000, LENGTH = 0x00000100
  m_flash_config        (RX)  : ORIGIN = 0x00000400, LENGTH = 0x00000010
  m_text                (RX)  : ORIGIN = 0x00000410, LENGTH = 0x0001FBF0
  m_data                (RW)  : ORIGIN = 0x1FFFF000, LENGTH = 0x00004000
}

/* �ζ��� */
SECTIONS
{
  /* �����������Ƚ����ڲ�flash */
  .interrupts :
  {
    __VECTOR_TABLE = .;
    . = ALIGN(4);
    KEEP(*(.isr_vector))     /* �������Ĵ��� */
    . = ALIGN(4);
  } > m_interrupts

  .flash_config :
  {
    . = ALIGN(4);
    KEEP(*(.FlashConfig))    /* flash�������� */
    . = ALIGN(4);
  } > m_flash_config

  /* ��д�ĳ������������д���ڲ�flash */
  .text :
  {
    . = ALIGN(4);
    *(.text)                 /* .text �� (code) */
    *(.text*)                /* .text* �� (code) */
    *(.rodata)               /* .rodata �� (constants, strings, etc.) */
    *(.rodata*)              /* .rodata* �� (constants, strings, etc.) */
    *(.glue_7)               /* glue arm to thumb code */
    *(.glue_7t)              /* glue thumb to arm code */
    *(.eh_frame)
    KEEP (*(.init))
    KEEP (*(.fini))
    . = ALIGN(4);
    
    /* Additional code content defined by components BEGIN */

    /* MQX Lite component BEGIN */
    * (KERNEL)/*����dispatch.S*/
    __VECTOR_TABLE_START = __VECTOR_TABLE;
    . = ALIGN(0x4);
    *(.rdata)
    . = ALIGN(0x4);
    *(.exception)
    . = ALIGN(0x4);
    __exception_table_start__ = .;
    /* EXCEPTION */
    __exception_table_end__ = .;
    __sinit__ = .;
    /* STATICINIT */
    /* MQX Lite component END */
    /* Additional code content defined by components END */
  } > m_text

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > m_text

  .ARM :
  {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } > m_text

 .ctors :
  {
    __CTOR_LIST__ = .;
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    __CTOR_END__ = .;
  } > m_text

  .dtors :
  {
    __DTOR_LIST__ = .;
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    __DTOR_END__ = .;
  } > m_text

  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } > m_text

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > m_text

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } > m_text

  __etext = .;    /* ��������������ȫ�ֱ�־ */
  __DATA_ROM = .; /* ��������ʱ���ݳ�ʼ���ı�־ */

  /* ��m_data��ʼ������MTB�ڴ� */
  .mtb : /* MTB��������ַ��Ӳ������� */
  {
    . = ALIGN(8);
    _mtb_start = .;
    KEEP(*(.mtb_buf)) /* ��Ҫ����MTB����Ӧ�ó������� */
    . = ALIGN(8);
    _mtb_end = .;
  } > m_data

  .data : AT(__DATA_ROM)
  {
    . = ALIGN(4);
    __DATA_RAM = .;
    __data_start__ = .;      /* ����data��ʼ����ȫ�ֱ�־ */
    *(.data)                 /* .data �� */
    *(.data*)                /* .data* �� */
    KEEP(*(.jcr*))
    . = ALIGN(4);
    __data_end__ = .;        /* ����data��������ȫ�ֱ�־ */
  } > m_data

  __DATA_END = __DATA_ROM + (__data_end__ - __data_start__);

  /* ����Ҫ��ʼ�������ݶ� */
  .bss :
  {
    /* �˴�������������������ʼ��.bss�� */
    . = ALIGN(4);
    __START_BSS = .;
    __bss_start__ = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
    __END_BSS = .;
  } > m_data

  .heap :
  {
    . = ALIGN(8);
    __end__ = .;
    PROVIDE(end = .);
    __HeapBase = .;
    . += HEAP_SIZE;
    __HeapLimit = .;
  } > m_data

  .stack :
  {
    . = ALIGN(8);
    . += STACK_SIZE;
  } > m_data

  /* �ڿ������ʼ��ջ */
  __StackTop   = ORIGIN(m_data) + LENGTH(m_data);
  __StackLimit = __StackTop - STACK_SIZE;
  PROVIDE(__stack = __StackTop);

  .ARM.attributes 0 : { *(.ARM.attributes) }

  ASSERT(__StackLimit >= __HeapLimit, "region m_data overflowed with stack and heap")
}
