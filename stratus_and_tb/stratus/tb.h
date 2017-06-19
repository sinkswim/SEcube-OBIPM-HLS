#ifndef __TB__H
#define __TB__H

#include <systemc.h>
#include "defines.h"
#include "wrapper.h"
#include "ip.h"
#include <iostream>

SC_MODULE(tb)
{
    public:
    // Declaration of clock and reset parameters
    sc_in_clk                   clk;
    sc_out < bool >             rst;
    sc_in < bool >              rst_in; // sampling version of "rst"

    // Communication with DUT
    // OBIPM-Buffer Interface -- MV
    sc_out< sc_bv<16> >     row_0_b;
    sc_out< sc_bv<16> >     data_b_in;   // used for read operartion
    sc_in< sc_bv<16> >      data_b_out;  // used for write opertaion
    sc_in< sc_bv<6> >       address_b;
    sc_in< sc_bv<1> >       w_enable_b;
    sc_in< sc_bv<1> >       r_enable_b;
    sc_in< sc_bv<1> >       generic_enable_b;
    // OBIPM-IP Interface
    //sc_inout< sc_bv<NUM_IP*16> > data_ip; -- old version
    sc_out< sc_bv<NUM_IP*16> >      data_ip_in;   //for write operation from IP
    sc_in< sc_bv<NUM_IP*16> >       data_ip_out;  // for read operation from IP
    sc_out< sc_bv<NUM_IP*6> >       address_ip;
    sc_out< sc_bv<NUM_IP> >         w_enable_ip;
    sc_out< sc_bv<NUM_IP> >         r_enable_ip;
    sc_out< sc_bv<NUM_IP> >         generic_enable_ip;
    sc_in< sc_bv<NUM_IP> >          enable_ip;
    sc_in< sc_bv<NUM_IP> >          ack_ip;
    sc_out< sc_bv<NUM_IP> >         interrupt_ip;
    // OBIPM-CPU Interface
    sc_in< sc_bv<1> >               interrupt_cpu;

    SC_CTOR(tb): wrap ("obipm_ip_bridge"), dummy_IP1 ("dummy1", false),
    dummy_IP2 ("dummy2", true)
    {
        rst_in(rst);    // auto-sample the reset signal inside the tb

        SC_CTHREAD(resetter, clk.pos());
        SC_THREAD(buffer);
        sensitive << data_b_out << address_b << w_enable_b << r_enable_b
                  << generic_enable_b;

        // --- Connect the wrapper to the tb interface and the IPs
        // INPUT PORTS
        // OBIPM -> WRAPPER
        // the following are output ports in OBIPM Interface
        wrap.data_ip_out_OBIPM(data_ip_out);
        wrap.enable_ip_OBIPM(enable_ip);
        wrap.ack_ip_OBIPM(ack_ip);
        // WRAPPER <- IPs
        wrap.data_ip_in_IP1(data_ip_in_IP1);
        wrap.data_ip_in_IP2(data_ip_in_IP2);
        wrap.address_ip_IP1(address_ip_IP1);
        wrap.address_ip_IP2(address_ip_IP2);
        wrap.w_enable_ip_IP1(w_enable_ip_IP1);
        wrap.w_enable_ip_IP2(w_enable_ip_IP2);
        wrap.r_enable_ip_IP1(r_enable_ip_IP1);
        wrap.r_enable_ip_IP2(r_enable_ip_IP2);
        wrap.generic_enable_ip_IP1(generic_enable_ip_IP1);
        wrap.generic_enable_ip_IP2(generic_enable_ip_IP2);
        wrap.interrupt_ip_IP1(interrupt_ip_IP1);
        wrap.interrupt_ip_IP2(interrupt_ip_IP2);
        // OUTPUT PORTS
        // WRAPPER -> OBIPM
        wrap.data_ip_in_OBIPM(data_ip_in);
        wrap.address_ip_OBIPM(address_ip);
        wrap.w_enable_ip_OBIPM(w_enable_ip);
        wrap.r_enable_ip_OBIPM(r_enable_ip);
        wrap.generic_enable_ip_OBIPM(generic_enable_ip);
        wrap.interrupt_ip_OBIPM(interrupt_ip);
        // WRAPPER -> IPs
        wrap.data_ip_out_IP1(data_ip_out_IP1);
        wrap.data_ip_out_IP2(data_ip_out_IP2);
        wrap.enable_ip_IP1(enable_ip_IP1);
        wrap.enable_ip_IP2(enable_ip_IP2);
        wrap.ack_ip_IP1(ack_ip_IP1);
        wrap.ack_ip_IP2(ack_ip_IP2);
        // --- ENDOF Connect the wrapper to the tb interface

        // --- Connect the IPs to the wrapper
        //clock and reset
        dummy_IP1.clk(clk);
        dummy_IP1.rst(rst_in);
        dummy_IP2.clk(clk);
        dummy_IP2.rst(rst_in);
        // wrapper->IP1
        dummy_IP1.data_ip_out(data_ip_out_IP1);
        dummy_IP1.enable_ip(enable_ip_IP1);
        dummy_IP1.ack_ip(ack_ip_IP1);
        // IP1->wrapper
        dummy_IP1.data_ip_in(data_ip_in_IP1);
        dummy_IP1.address_ip(address_ip_IP1);
        dummy_IP1.w_enable_ip(w_enable_ip_IP1);
        dummy_IP1.r_enable_ip(r_enable_ip_IP1);
        dummy_IP1.generic_enable_ip(generic_enable_ip_IP1);
        dummy_IP1.interrupt_ip(interrupt_ip_IP1);
        // wrapper->IP2
        dummy_IP2.data_ip_out(data_ip_out_IP2);
        dummy_IP2.enable_ip(enable_ip_IP2);
        dummy_IP2.ack_ip(ack_ip_IP2);
        // IP2->wrapper
        dummy_IP2.data_ip_in(data_ip_in_IP2);
        dummy_IP2.address_ip(address_ip_IP2);
        dummy_IP2.w_enable_ip(w_enable_ip_IP2);
        dummy_IP2.r_enable_ip(r_enable_ip_IP2);
        dummy_IP2.generic_enable_ip(generic_enable_ip_IP2);
        dummy_IP2.interrupt_ip(interrupt_ip_IP2);
        // --- ENDOFConnect the IPs to the wrapper
    }
    void resetter();
    void buffer();

    // Member variables
    sc_bv<16> regfile[64];

    // Wrapper module (OBIPM-IPs bridge)
    wrapper wrap;
    // dummy IPs
    ip dummy_IP1;   // Reader
    ip dummy_IP2;   // Writer

    // Signals for wrapper<->ips interconnection
    // WRAPPER <- IPs
    sc_signal<sc_bv<16> >     data_ip_in_IP1;
    sc_signal<sc_bv<16> >     data_ip_in_IP2;
    sc_signal<sc_bv<6> >      address_ip_IP1;
    sc_signal<sc_bv<6> >      address_ip_IP2;
    sc_signal<sc_bv<1> >      w_enable_ip_IP1;
    sc_signal<sc_bv<1> >      w_enable_ip_IP2;
    sc_signal<sc_bv<1> >      r_enable_ip_IP1;
    sc_signal<sc_bv<1> >      r_enable_ip_IP2;
    sc_signal<sc_bv<1> >      generic_enable_ip_IP1;
    sc_signal<sc_bv<1> >      generic_enable_ip_IP2;
    sc_signal<sc_bv<1> >      interrupt_ip_IP1;
    sc_signal<sc_bv<1> >      interrupt_ip_IP2;
    // WRAPPER -> IPs
    sc_signal<sc_bv<16> >        data_ip_out_IP1;
    sc_signal<sc_bv<16> >        data_ip_out_IP2;
    sc_signal<sc_bv<1> >         enable_ip_IP1;
    sc_signal<sc_bv<1> >         enable_ip_IP2;
    sc_signal<sc_bv<1> >         ack_ip_IP1;
    sc_signal<sc_bv<1> >         ack_ip_IP2;
};

#endif
