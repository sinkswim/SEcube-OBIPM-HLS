// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2016.4
// Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module obipm_support_logic (
        ack_ip,
        ack_ip_ap_vld,
        interrupt_ip,
        interrupt_cpu,
        interrupt_cpu_ap_vld,
        interrupt_internal,
        ack_internal,
        acked,
        acked_ap_vld,
        irq,
        irq_ap_vld
);

parameter    ap_const_lv5_0 = 5'b00000;

output  [4:0] ack_ip;
output   ack_ip_ap_vld;
input  [4:0] interrupt_ip;
output  [0:0] interrupt_cpu;
output   interrupt_cpu_ap_vld;
input  [0:0] interrupt_internal;
input  [4:0] ack_internal;
output  [0:0] acked;
output   acked_ap_vld;
output  [0:0] irq;
output   irq_ap_vld;

assign ack_ip_ap_vld = 1'b1;

assign acked_ap_vld = 1'b1;

assign interrupt_cpu_ap_vld = 1'b1;

assign irq_ap_vld = 1'b1;

assign ack_ip = ack_internal;

assign acked = ((ack_internal != ap_const_lv5_0) ? 1'b1 : 1'b0);

assign interrupt_cpu = interrupt_internal;

assign irq = ((interrupt_ip != ap_const_lv5_0) ? 1'b1 : 1'b0);

endmodule //obipm_support_logic