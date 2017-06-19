#ifndef TB_IC_H
#define TB_IC_H 0

#include "ic.h"
#include <systemc.h>
#include <iostream>



SC_MODULE(tb) {
  // Inputs
  sc_in<bool> clk;

  // DUT
  ic  my_ic;    // interrupt controller

  // Internal signals
  sc_signal < bool >          tb_rst;
  sc_signal<sc_bv<1> >        tb_transaction;
  sc_signal<sc_bv<NUM_IP> >   tb_interrupt_ip;
  sc_signal<sc_bv<1> >        tb_irq;
  sc_signal<sc_bv<1> >        tb_acked;
  sc_signal<sc_bv<1> >        tb_interrupt_internal;
  sc_signal<unsigned int>     tb_index_interrupt;

  //Constructor
  SC_CTOR(tb): my_ic("dut0") {
    // module connections
    my_ic.clk(clk);
    my_ic.rst(tb_rst);
    my_ic.transaction(tb_transaction);
    my_ic.interrupt_ip(tb_interrupt_ip);
    my_ic.irq(tb_irq);
    my_ic.acked(tb_acked);
    my_ic.interrupt_internal(tb_interrupt_internal);
    my_ic.index_interrupt(tb_index_interrupt);

    //Main controller
    SC_CTHREAD(mc, clk.pos());
    reset_signal_is(tb_rst,false);

    //Signal Trace
    SC_METHOD(trace);
    sensitive << tb_interrupt_internal << tb_index_interrupt
              << clk << tb_transaction << tb_interrupt_ip
              << tb_acked << tb_rst << tb_irq;

    //Resetter
    SC_CTHREAD(resetter, clk.pos());
  }

  //Methods and Threads
  void resetter();
  void mc();
  void trace();

};



#endif
