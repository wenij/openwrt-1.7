/***********************license start***************
 * Copyright (c) 2003-2010  Cavium Inc. (support@cavium.com). All rights
 * reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.

 *   * Neither the name of Cavium Inc. nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.

 * This Software, including technical data, may be subject to U.S. export  control
 * laws, including the U.S. Export Administration Act and its  associated
 * regulations, and may be subject to export or import  regulations in other
 * countries.

 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION OR
 * DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM
 * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,
 * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF
 * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK ARISING OUT OF USE OR
 * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 ***********************license end**************************************/

/**
 * @file
 * Definitions for enumerations used with Octeon CSRs.
 *
 * <hr>$Revision: 73842 $<hr>
 *
 */
#ifndef __CVMX_CSR_ENUMS_H__
#define __CVMX_CSR_ENUMS_H__

typedef enum {
	CVMX_IPD_OPC_MODE_STT = 0LL,	/* All blocks DRAM, not cached in L2 */
	CVMX_IPD_OPC_MODE_STF = 1LL,	/* All blocks into L2 */
	CVMX_IPD_OPC_MODE_STF1_STT = 2LL,	/* 1st block L2, rest DRAM */
	CVMX_IPD_OPC_MODE_STF2_STT = 3LL	/* 1st, 2nd blocks L2, rest DRAM */
} cvmx_ipd_mode_t;

/**
 * Enumeration representing the amount of packet processing
 * and validation performed by the input hardware.
 */
typedef enum {
	CVMX_PIP_PORT_CFG_MODE_NONE = 0ull,
					 /**< Packet input doesn't perform any
                                            processing of the input packet. */
	CVMX_PIP_PORT_CFG_MODE_SKIPL2 = 1ull,
					 /**< Full packet processing is performed
                                            with pointer starting at the L2
                                            (ethernet MAC) header. */
	CVMX_PIP_PORT_CFG_MODE_SKIPIP = 2ull
					 /**< Input packets are assumed to be IP.
                                            Results from non IP packets is
                                            undefined. Pointers reference the
                                            beginning of the IP header. */
} cvmx_pip_port_parse_mode_t;

/**
 * This enumeration controls how a QoS watcher matches a packet.
 *
 * @deprecated  This enumeration was used with cvmx_pip_config_watcher which has
 *              been deprecated.
 */
typedef enum {
	CVMX_PIP_QOS_WATCH_DISABLE = 0ull,
					 /**< QoS watcher is diabled */
	CVMX_PIP_QOS_WATCH_PROTNH = 1ull,/**< QoS watcher will match based on the IP protocol */
	CVMX_PIP_QOS_WATCH_TCP = 2ull,	 /**< QoS watcher will match TCP packets to a specific destination port */
	CVMX_PIP_QOS_WATCH_UDP = 3ull	 /**< QoS watcher will match UDP packets to a specific destination port */
} cvmx_pip_qos_watch_types;

/**
 * This enumeration is used in PIP tag config to control how
 * POW tags are generated by the hardware.
 */
typedef enum {
	CVMX_PIP_TAG_MODE_TUPLE = 0ull,	    /**< Always use tuple tag algorithm. This is the only mode supported on Pass 1 */
	CVMX_PIP_TAG_MODE_MASK = 1ull,	    /**< Always use mask tag algorithm */
	CVMX_PIP_TAG_MODE_IP_OR_MASK = 2ull,/**< If packet is IP, use tuple else use mask */
	CVMX_PIP_TAG_MODE_TUPLE_XOR_MASK = 3ull
					    /**< tuple XOR mask */
} cvmx_pip_tag_mode_t;

/**
 * Tag type definitions
 */
typedef enum {
	CVMX_POW_TAG_TYPE_ORDERED = 0L,	/**< Tag ordering is maintained */
	CVMX_POW_TAG_TYPE_ATOMIC = 1L,	/**< Tag ordering is maintained, and at most one PP has the tag */
	CVMX_POW_TAG_TYPE_NULL = 2L,	/**< The work queue entry from the order
                                            - NEVER tag switch from NULL to NULL */
	CVMX_POW_TAG_TYPE_NULL_NULL = 3L/**< A tag switch to NULL, and there is no space reserved in POW
                                            - NEVER tag switch to NULL_NULL
                                            - NEVER tag switch from NULL_NULL
                                            - NULL_NULL is entered at the beginning of time and on a deschedule.
                                            - NULL_NULL can be exited by a new work request. A NULL_SWITCH load can also switch the state to NULL */
} cvmx_pow_tag_type_t;

/**
 * LCR bits 0 and 1 control the number of bits per character. See the following table for encodings:
 *
 * - 00 = 5 bits (bits 0-4 sent)
 * - 01 = 6 bits (bits 0-5 sent)
 * - 10 = 7 bits (bits 0-6 sent)
 * - 11 = 8 bits (all bits sent)
 */
typedef enum {
	CVMX_UART_BITS5 = 0,
	CVMX_UART_BITS6 = 1,
	CVMX_UART_BITS7 = 2,
	CVMX_UART_BITS8 = 3
} cvmx_uart_bits_t;

/**
 * Interrupt   Priority   Interrupt         Interrupt                                       Interrupt
 * ID          Level      Type              Source                                          Reset By
 * ---------------------------------------------------------------------------------------------------------------------------------
 * 0001        -          None              None                                            -
 *
 * 0110        Highest    Receiver Line     Overrun, parity, or framing errors or break     Reading the Line Status Register
 *                        Status            interrupt
 *
 * 0100        Second     Received Data     Receiver data available (FIFOs disabled) or     Reading the Receiver Buffer Register
 *                        Available         RX FIFO trigger level reached (FIFOs            (FIFOs disabled) or the FIFO drops below
 *                                          enabled)                                        the trigger level (FIFOs enabled)
 *
 * 1100        Second     Character         No characters in or out of the RX FIFO          Reading the Receiver Buffer Register
 *                        Timeout           during the last 4 character times and there
 *                        Indication        is at least 1 character in it during this
 *                                          time
 *
 * 0010        Third      Transmitter       Transmitter Holding Register Empty              Reading the Interrupt Identity Register
 *                        Holding           (Programmable THRE Mode disabled) or TX         (if source of interrupt) or writing into
 *                        Register          FIFO at or below threshold (Programmable        THR (FIFOs or THRE Mode disabled) or TX
 *                        Empty             THRE Mode enabled)                              FIFO above threshold (FIFOs and THRE
 *                                                                                          Mode enabled)
 *
 * 0000        Fourth     Modem Status      Clear To Send (CTS) or Data Set Ready (DSR)     Reading the Modem Status Register
 *                        Changed           or Ring Indicator (RI) or Data Center
 *                                          Detect (DCD) changed
 *
 * 0111        Fifth      Busy Detect       Software has tried to write to the Line         Reading the UART Status Register
 *                        Indication        Control Register while the BUSY bit of the
 *                                          UART Status Register was set
 */
typedef enum {
	CVMX_UART_IID_NONE = 1,
	CVMX_UART_IID_RX_ERROR = 6,
	CVMX_UART_IID_RX_DATA = 4,
	CVMX_UART_IID_RX_TIMEOUT = 12,
	CVMX_UART_IID_TX_EMPTY = 2,
	CVMX_UART_IID_MODEM = 0,
	CVMX_UART_IID_BUSY = 7
} cvmx_uart_iid_t;

#endif /* __CVMX_CSR_ENUMS_H__ */
