#ifndef __OBIPM__H
#define __OBIPM__H

#include "defines.h"
#include <systemc.h>
#include "stratus_hls.h"

SC_MODULE(obipm)
{
    public:
    ///////////////////////////////////////////////////////////////////////////
    //  INPUT/OUTPUT PORTS
    ///////////////////////////////////////////////////////////////////////////
    // Declaration of clock and reset parameters
    sc_in_clk            clk;
    sc_in < bool >       rst;

    // OBIPM-Buffer Interface -- MV
    sc_in< sc_bv<16> >    row_0_b;
    sc_in< sc_bv<16> >    data_b_in;   // used for read operation
    sc_out< sc_bv<16> >   data_b_out;  // used for write operation
    sc_out< sc_bv<6> >    address_b;
    sc_out< sc_bv<1> >    w_enable_b;
    sc_out< sc_bv<1> >    r_enable_b;
    sc_out< sc_bv<1> >    generic_enable_b;

    // OBIPM-IP Interface
    //sc_inout< sc_bv<NUM_IP*16> > data_ip; -- old version
    sc_in< sc_bv<NUM_IP*16> >   data_ip_in;   //for write operation from IP
    sc_out< sc_bv<NUM_IP*16> >  data_ip_out;  // for read operation from IP
    sc_in< sc_bv<NUM_IP*6> >    address_ip;
    sc_in< sc_bv<NUM_IP> >      w_enable_ip;
    sc_in< sc_bv<NUM_IP> >      r_enable_ip;
    sc_in< sc_bv<NUM_IP> >      generic_enable_ip;
    sc_out< sc_bv<NUM_IP> >     enable_ip;
    sc_out< sc_bv<NUM_IP> >     ack_ip;
    sc_in< sc_bv<NUM_IP> >      interrupt_ip;

    // OBIPM-CPU Interface
    sc_out< sc_bv<1> > interrupt_cpu;

    ///////////////////////////////////////////////////////////////////////////
    // Internal signals
    ///////////////////////////////////////////////////////////////////////////
    sc_signal< sc_bv<1> >       transaction;
    sc_signal< sc_uint<LOG> >   index_ip;
    sc_signal< sc_bv<1> >       interrupt_internal;
    sc_signal < unsigned int >  index_interrupt;

    sc_signal< sc_bv<NUM_IP> >  ack_internal;
    sc_signal< sc_bv<1> >       acked;
    sc_signal< sc_bv<1> >       irq;

    ///////////////////////////////////////////////////////////////////////////
    // Constructor
    ///////////////////////////////////////////////////////////////////////////

    SC_CTOR(obipm):clk("clk"), rst("rst")
    {
        SC_METHOD(enabler);
        sensitive << row_0_b;

        SC_METHOD(packet_switcher);
        sensitive << data_ip_in << address_ip << w_enable_ip << r_enable_ip
                  << generic_enable_ip << transaction << index_ip
                  << interrupt_internal << index_interrupt
                  << data_b_in;

        SC_CTHREAD(interrupt_controller, clk.pos());
        reset_signal_is(rst, false);       // Posedge reset.

        SC_METHOD(support_logic);
        sensitive << ack_internal << interrupt_internal;

    }

    ///////////////////////////////////////////////////////////////////////////
    // METHODS AND THREADS
    ///////////////////////////////////////////////////////////////////////////

    void enabler();
    void packet_switcher();
    void interrupt_controller();
    void support_logic();

};

#endif
