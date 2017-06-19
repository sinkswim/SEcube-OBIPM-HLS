#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <systemc.h>
#include <esc.h>
#include <stratus_hls.h>            // Cadence Stratus definitions.
#include "tb.h"
#include "obipm_wrap.h"
#include "defines.h"

SC_MODULE(TOP)
{
    public:

    // clock and reset signals
    sc_clock            clk;
    sc_signal < bool >  rst;

    // communication signals (dut<->tb)
    // OBIPM-Buffer Interface -- MV
    sc_signal< sc_bv<16> >    row_0_b;
    sc_signal< sc_bv<16> >    data_b_in;   // used for read operartion
    sc_signal< sc_bv<16> >   data_b_out;  // used for write opertaion
    sc_signal< sc_bv<6> >    address_b;
    sc_signal< sc_bv<1> >    w_enable_b;
    sc_signal< sc_bv<1> >    r_enable_b;
    sc_signal< sc_bv<1> >    generic_enable_b;
    // OBIPM-IP Interface
    //sc_inout< sc_bv<NUM_IP*16> > data_ip; -- old version
    sc_signal< sc_bv<NUM_IP*16> >   data_ip_in;   //for write operation from IP
    sc_signal< sc_bv<NUM_IP*16> >  data_ip_out;  // for read operation from IP
    sc_signal< sc_bv<NUM_IP*6> >    address_ip;
    sc_signal< sc_bv<NUM_IP> >      w_enable_ip;
    sc_signal< sc_bv<NUM_IP> >      r_enable_ip;
    sc_signal< sc_bv<NUM_IP> >      generic_enable_ip;
    sc_signal< sc_bv<NUM_IP> >     enable_ip;
    sc_signal< sc_bv<NUM_IP> >     ack_ip;
    sc_signal< sc_bv<NUM_IP> >      interrupt_ip;
    // OBIPM-CPU Interface
    sc_signal< sc_bv<1> > interrupt_cpu;

    // The testbench and DUT modules.
    obipm_wrapper *m_dut;
    tb   *m_tb;

    void initInstances();
    void deleteInstances();

    SC_CTOR(TOP): clk("clk", CLOCK_PERIOD, SC_NS, 0.5, 0, SC_NS, true),
        rst("rst")
    {
        initInstances();
    }

    ~TOP()
    {
        deleteInstances();
    }
};

#endif // SYSTEM_H_INCLUDED
