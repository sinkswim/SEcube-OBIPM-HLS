// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2016.4
// Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="obipm,hls_ip_2016_4,{HLS_INPUT_TYPE=sc,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xa7z030fbg484-1i,HLS_INPUT_CLOCK=10.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=6.995250,HLS_SYN_LAT=4,HLS_SYN_TPT=none,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=2,HLS_SYN_LUT=2031}" *)

module obipm (
        clk,
        rst,
        row_0_b,
        data_b_in,
        data_b_out,
        address_b,
        w_enable_b,
        r_enable_b,
        generic_enable_b,
        data_ip_in,
        data_ip_out,
        address_ip,
        w_enable_ip,
        r_enable_ip,
        generic_enable_ip,
        enable_ip,
        ack_ip,
        interrupt_ip,
        interrupt_cpu
);

parameter    ap_const_lv32_0 = 32'b00000000000000000000000000000000;
parameter    ap_const_lv32_1 = 32'b1;
parameter    ap_const_lv32_2 = 32'b10;
parameter    ap_const_lv32_4 = 32'b100;
parameter    ap_const_lv5_0 = 5'b00000;

input   clk;
input   rst;
input  [15:0] row_0_b;
input  [15:0] data_b_in;
output  [15:0] data_b_out;
output  [5:0] address_b;
output  [0:0] w_enable_b;
output  [0:0] r_enable_b;
output  [0:0] generic_enable_b;
input  [79:0] data_ip_in;
output  [79:0] data_ip_out;
input  [29:0] address_ip;
input  [4:0] w_enable_ip;
input  [4:0] r_enable_ip;
input  [4:0] generic_enable_ip;
output  [4:0] enable_ip;
output  [4:0] ack_ip;
input  [4:0] interrupt_ip;
output  [0:0] interrupt_cpu;

wire   [0:0] obipm_ssdm_thread_1_load_fu_408_p1;
wire   [4:0] ap_CS_fsm;
wire   [0:0] ap_CS_fsm_state1;
wire   [0:0] obipm_ssdm_thread_3_load_fu_416_p1;
wire   [0:0] ap_CS_fsm_state2;
wire   [4:0] StgValue_35_obipm_enabler_fu_180_enable_ip;
wire    StgValue_35_obipm_enabler_fu_180_enable_ip_ap_vld;
wire   [0:0] StgValue_35_obipm_enabler_fu_180_transaction_r;
wire    StgValue_35_obipm_enabler_fu_180_transaction_r_ap_vld;
wire   [2:0] StgValue_35_obipm_enabler_fu_180_index_ip;
wire    StgValue_35_obipm_enabler_fu_180_index_ip_ap_vld;
wire   [4:0] StgValue_35_obipm_enabler_fu_180_ack_internal;
wire    StgValue_35_obipm_enabler_fu_180_ack_internal_ap_vld;
wire   [15:0] StgValue_41_obipm_packet_switcher_fu_236_data_b_out;
wire    StgValue_41_obipm_packet_switcher_fu_236_data_b_out_ap_vld;
wire   [5:0] StgValue_41_obipm_packet_switcher_fu_236_address_b;
wire    StgValue_41_obipm_packet_switcher_fu_236_address_b_ap_vld;
wire   [0:0] StgValue_41_obipm_packet_switcher_fu_236_w_enable_b;
wire    StgValue_41_obipm_packet_switcher_fu_236_w_enable_b_ap_vld;
wire   [0:0] StgValue_41_obipm_packet_switcher_fu_236_r_enable_b;
wire    StgValue_41_obipm_packet_switcher_fu_236_r_enable_b_ap_vld;
wire   [0:0] StgValue_41_obipm_packet_switcher_fu_236_generic_enable_b;
wire    StgValue_41_obipm_packet_switcher_fu_236_generic_enable_b_ap_vld;
wire   [79:0] StgValue_41_obipm_packet_switcher_fu_236_data_ip_out;
wire    StgValue_41_obipm_packet_switcher_fu_236_data_ip_out_ap_vld;
wire   [4:0] StgValue_61_obipm_support_logic_fu_292_ack_ip;
wire    StgValue_61_obipm_support_logic_fu_292_ack_ip_ap_vld;
wire   [0:0] StgValue_61_obipm_support_logic_fu_292_interrupt_cpu;
wire    StgValue_61_obipm_support_logic_fu_292_interrupt_cpu_ap_vld;
wire   [0:0] StgValue_61_obipm_support_logic_fu_292_acked;
wire    StgValue_61_obipm_support_logic_fu_292_acked_ap_vld;
wire   [0:0] StgValue_61_obipm_support_logic_fu_292_irq;
wire    StgValue_61_obipm_support_logic_fu_292_irq_ap_vld;
wire   [0:0] obipm_ssdm_thread_load_fu_404_p1;
wire   [0:0] ap_CS_fsm_state3;
wire   [0:0] ap_CS_fsm_state5;

obipm_enabler StgValue_35_obipm_enabler_fu_180(
    .row_0_b(row_0_b),
    .enable_ip(StgValue_35_obipm_enabler_fu_180_enable_ip),
    .enable_ip_ap_vld(StgValue_35_obipm_enabler_fu_180_enable_ip_ap_vld),
    .transaction_r(StgValue_35_obipm_enabler_fu_180_transaction_r),
    .transaction_r_ap_vld(StgValue_35_obipm_enabler_fu_180_transaction_r_ap_vld),
    .index_ip(StgValue_35_obipm_enabler_fu_180_index_ip),
    .index_ip_ap_vld(StgValue_35_obipm_enabler_fu_180_index_ip_ap_vld),
    .ack_internal(StgValue_35_obipm_enabler_fu_180_ack_internal),
    .ack_internal_ap_vld(StgValue_35_obipm_enabler_fu_180_ack_internal_ap_vld)
);

obipm_packet_switcher StgValue_41_obipm_packet_switcher_fu_236(
    .data_b_in(data_b_in),
    .data_b_out(StgValue_41_obipm_packet_switcher_fu_236_data_b_out),
    .data_b_out_ap_vld(StgValue_41_obipm_packet_switcher_fu_236_data_b_out_ap_vld),
    .address_b(StgValue_41_obipm_packet_switcher_fu_236_address_b),
    .address_b_ap_vld(StgValue_41_obipm_packet_switcher_fu_236_address_b_ap_vld),
    .w_enable_b(StgValue_41_obipm_packet_switcher_fu_236_w_enable_b),
    .w_enable_b_ap_vld(StgValue_41_obipm_packet_switcher_fu_236_w_enable_b_ap_vld),
    .r_enable_b(StgValue_41_obipm_packet_switcher_fu_236_r_enable_b),
    .r_enable_b_ap_vld(StgValue_41_obipm_packet_switcher_fu_236_r_enable_b_ap_vld),
    .generic_enable_b(StgValue_41_obipm_packet_switcher_fu_236_generic_enable_b),
    .generic_enable_b_ap_vld(StgValue_41_obipm_packet_switcher_fu_236_generic_enable_b_ap_vld),
    .data_ip_in(data_ip_in),
    .data_ip_out(StgValue_41_obipm_packet_switcher_fu_236_data_ip_out),
    .data_ip_out_ap_vld(StgValue_41_obipm_packet_switcher_fu_236_data_ip_out_ap_vld),
    .address_ip(address_ip),
    .w_enable_ip(w_enable_ip),
    .r_enable_ip(r_enable_ip),
    .generic_enable_ip(generic_enable_ip),
    .transaction_r(StgValue_35_obipm_enabler_fu_180_transaction_r),
    .index_ip(StgValue_35_obipm_enabler_fu_180_index_ip),
    .interrupt_internal(1'b0),
    .index_interrupt(ap_const_lv32_0)
);

obipm_support_logic StgValue_61_obipm_support_logic_fu_292(
    .ack_ip(StgValue_61_obipm_support_logic_fu_292_ack_ip),
    .ack_ip_ap_vld(StgValue_61_obipm_support_logic_fu_292_ack_ip_ap_vld),
    .interrupt_ip(interrupt_ip),
    .interrupt_cpu(StgValue_61_obipm_support_logic_fu_292_interrupt_cpu),
    .interrupt_cpu_ap_vld(StgValue_61_obipm_support_logic_fu_292_interrupt_cpu_ap_vld),
    .interrupt_internal(1'b0),
    .ack_internal(StgValue_35_obipm_enabler_fu_180_ack_internal),
    .acked(StgValue_61_obipm_support_logic_fu_292_acked),
    .acked_ap_vld(StgValue_61_obipm_support_logic_fu_292_acked_ap_vld),
    .irq(StgValue_61_obipm_support_logic_fu_292_irq),
    .irq_ap_vld(StgValue_61_obipm_support_logic_fu_292_irq_ap_vld)
);

obipm_interrupt_controller grp_obipm_interrupt_controller_fu_348(
    .ap_clk(clk),
    .ap_rst(rst),
    .interrupt_ip(interrupt_ip),
    .transaction_r(StgValue_35_obipm_enabler_fu_180_transaction_r),
    .irq(StgValue_61_obipm_support_logic_fu_292_irq)
);

assign ack_ip = StgValue_61_obipm_support_logic_fu_292_ack_ip;

assign address_b = StgValue_41_obipm_packet_switcher_fu_236_address_b;

assign ap_CS_fsm = ap_const_lv5_0;

assign ap_CS_fsm_state1 = ap_CS_fsm[ap_const_lv32_0];

assign ap_CS_fsm_state2 = ap_CS_fsm[ap_const_lv32_1];

assign ap_CS_fsm_state3 = ap_CS_fsm[ap_const_lv32_2];

assign ap_CS_fsm_state5 = ap_CS_fsm[ap_const_lv32_4];

assign data_b_out = StgValue_41_obipm_packet_switcher_fu_236_data_b_out;

assign data_ip_out = StgValue_41_obipm_packet_switcher_fu_236_data_ip_out;

assign enable_ip = StgValue_35_obipm_enabler_fu_180_enable_ip;

assign generic_enable_b = StgValue_41_obipm_packet_switcher_fu_236_generic_enable_b;

assign interrupt_cpu = StgValue_61_obipm_support_logic_fu_292_interrupt_cpu;

assign obipm_ssdm_thread_1_load_fu_408_p1 = 1'b0;

assign obipm_ssdm_thread_3_load_fu_416_p1 = 1'b0;

assign obipm_ssdm_thread_load_fu_404_p1 = 1'b0;

assign r_enable_b = StgValue_41_obipm_packet_switcher_fu_236_r_enable_b;

assign w_enable_b = StgValue_41_obipm_packet_switcher_fu_236_w_enable_b;

endmodule //obipm
