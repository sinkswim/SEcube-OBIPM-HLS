// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2016.4
// Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#ifndef _obipm_support_logic_HH_
#define _obipm_support_logic_HH_

#include "systemc.h"
#include "AESL_pkg.h"


namespace ap_rtl {

struct obipm_support_logic : public sc_module {
    // Port declarations 11
    sc_out< sc_lv<5> > ack_ip;
    sc_out< sc_logic > ack_ip_ap_vld;
    sc_in< sc_lv<5> > interrupt_ip;
    sc_out< sc_lv<1> > interrupt_cpu;
    sc_out< sc_logic > interrupt_cpu_ap_vld;
    sc_in< sc_lv<1> > interrupt_internal;
    sc_in< sc_lv<5> > ack_internal;
    sc_out< sc_lv<1> > acked;
    sc_out< sc_logic > acked_ap_vld;
    sc_out< sc_lv<1> > irq;
    sc_out< sc_logic > irq_ap_vld;


    // Module declarations
    obipm_support_logic(sc_module_name name);
    SC_HAS_PROCESS(obipm_support_logic);

    ~obipm_support_logic();

    sc_trace_file* mVcdFile;

    static const bool ap_const_boolean_1;
    static const sc_logic ap_const_logic_0;
    static const sc_logic ap_const_logic_1;
    static const sc_lv<5> ap_const_lv5_0;
    // Thread declarations
    void thread_ack_ip();
    void thread_ack_ip_ap_vld();
    void thread_acked();
    void thread_acked_ap_vld();
    void thread_interrupt_cpu();
    void thread_interrupt_cpu_ap_vld();
    void thread_irq();
    void thread_irq_ap_vld();
};

}

using namespace ap_rtl;

#endif
