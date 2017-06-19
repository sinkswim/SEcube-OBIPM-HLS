#ifndef IP_H
#define IP_H

#include "systemc.h"
#include "defines.h"
#include <iostream>

SC_MODULE(ip){
    sc_in_clk                  clk;
    sc_in < bool >             rst;

    // OBIPM->IP
    sc_in<sc_bv<16> >        data_ip_out; // output for thte OBIPM
    sc_in<sc_bv<1> >         enable_ip;
    sc_in<sc_bv<1> >         ack_ip;

    // IP->OBIPM
    sc_out<sc_bv<16> >     data_ip_in;    //input for the OBIPM
    sc_out<sc_bv<6> >      address_ip;
    sc_out<sc_bv<1> >      w_enable_ip;
    sc_out<sc_bv<1> >      r_enable_ip;
    sc_out<sc_bv<1> >      generic_enable_ip;
    sc_out<sc_bv<1> >      interrupt_ip;

    // threads
    void IP_thread();

    SC_HAS_PROCESS(ip);

    // false means that the IP is not active.
    // true means that the IP is active
    // In case of interrupt test, true/false assume
    // a different meaning (se ip.cpp's interrupt section)
    ip(sc_module_name name_, bool type = false){
        mytype = type;
        SC_CTHREAD(IP_thread, clk.pos());
        reset_signal_is(rst, false);
    }

    // member variables
    bool mytype;
};

#endif // IP_H
