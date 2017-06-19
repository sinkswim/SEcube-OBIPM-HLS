#include "obipm.h"

///////////////////////////////////////////////////////////////////////////////
// --- Enabler.
///////////////////////////////////////////////////////////////////////////////
void obipm::enabler(){
    // Commodity variables
    sc_uint<16> addr_v   = sc_uint<16>(row_0_b.read());
    sc_uint<LOG> target_ip = addr_v.range(11, 0) - 1;
    sc_bv<NUM_IP> enab_v  = (sc_bv<NUM_IP>)0;
    sc_bv<NUM_IP> acks_v  = (sc_bv<NUM_IP>)0;
    //Operations
    transaction.write(sc_bv<1>(int(addr_v.range(12, 12))));
    index_ip.write(target_ip);
    if(addr_v.range(12, 12) == 1){
        enab_v.range(target_ip, target_ip) = "1";     //  enable[row_0(11:0) - 1] = 1;
        enable_ip.write(enab_v);
        if(addr_v.range(13, 13) == 1){
            acks_v.range(target_ip, target_ip) = "1";            // ack(row_0(11:0) - 1) = 1;
            ack_internal.write(acks_v);
        }
        else{
            ack_internal.write(acks_v);     // Writes all zeroes to ack_internal.
        }
    }
    else{       // Writes all zeroes to enable_ip and ack_internal.
        enable_ip.write(enab_v);
        ack_internal.write(acks_v);
    }
}

/*
////////////////////////////////////////////////////////////////////////////////
NOTE: THIS IS JUST PSEUDO CODE, NOT COMPATIBLE WITH SYSTEMC
Module: Enabler

// Sensitive to ROW_0, Pure Comb Logic Block
transaction = row_0(12);
index = row_0(11:0) - 1;  // -1 since the addr 0 is dedicated to the IP manager

if (row_0(12) == 1) { // begin at 1

  enable(row_0(11:0) - 1) = 1;
  if(row_0(13) == 1) {
    ack(row_0(11:0) - 1) = 1;
  } else {
    ack = 0; // multi bit signal
  }


} else {  // begin at 0, end of a transaction

  enable = 0;   // multi bit signal
  ack = 0;  // multi bit signal

}
 */
///////////////////////////////////////////////////////////////////////////////
// --- END of enabler.
///////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// --- Packet Switcher.
///////////////////////////////////////////////////////////////////////////////
void obipm::packet_switcher(){
    // Variables
    sc_bv<NUM_IP*6>     address_ip_i;
    sc_bv<NUM_IP>       w_enable_ip_i;
    sc_bv<NUM_IP>       r_enable_ip_i;
    sc_bv<NUM_IP>       generic_enable_ip_i;
    sc_bv<16>           data_b_in_i, data_b_out_i;
    sc_bv<NUM_IP*16>    data_ip_in_i, data_ip_out_i;
    sc_uint<LOG>       index_ip_i;
    sc_uint<LOG>       index_interrupt_i;


    // METHOD BODY

    // Read input ports
    address_ip_i        = address_ip.read();
    w_enable_ip_i       = w_enable_ip.read();
    r_enable_ip_i       = r_enable_ip.read();
    generic_enable_ip_i = generic_enable_ip.read();
    data_b_in_i         = data_b_in.read();
    data_ip_in_i        = data_ip_in.read();
    index_ip_i          = index_ip.read();
    index_interrupt_i   = index_interrupt.read();

    // Output ports to default value
    data_ip_out.write((sc_bv<NUM_IP*16>)0);
    data_b_out.write((sc_bv<16>)0);
    address_b.write((sc_bv<6>)0);
    w_enable_b.write((sc_bv<1>)0);
    r_enable_b.write((sc_bv<1>)0);
    generic_enable_b.write((sc_bv<1>)0);

    //Variable init
    data_ip_out_i       = (sc_bv<NUM_IP*16>)0;
    data_b_out_i        = (sc_bv<16>)0;

    //Comb. Beh.
    if(transaction.read() == "1") {
      // create a path from port(index) to data port
      // generic alg. is: index*DATA_WIDTH, index*DATA_WIDTH + (DATA_WIDTH-1)
      // data ports
      data_b_out.write(data_ip_in_i.range((index_ip_i)*16+15, (index_ip_i)*16));
      data_ip_out_i.range(index_ip_i*16+15, index_ip_i*16) = data_b_in_i;
      data_ip_out.write(data_ip_out_i);

      //control ports and address port
      address_b.write(address_ip_i.range(index_ip_i*6+5, index_ip_i*6));
      w_enable_b.write(w_enable_ip_i.range(index_ip_i, index_ip_i));
      r_enable_b.write(r_enable_ip_i.range(index_ip_i, index_ip_i));
      generic_enable_b.write(generic_enable_ip_i.range(index_ip_i, index_ip_i));


    } else {

      if(interrupt_internal.read() == "1") {
        // write at address 0 the content of index_interrupt_i
        // note that transaction bit must be 0, otherwise it will trigger
        // the enabler(it will active only if the tranaction bit is set!)
        // data_b_out_i is alreay all 0, set at the beginnign (Variable init)
        data_b_out_i.range(LOG-1, 0) = sc_bv<LOG>(index_interrupt_i);
        address_b.write((sc_bv<6>)0);
        // setup control signals for a write operation
        w_enable_b.write((sc_bv<1>)1);
        r_enable_b.write((sc_bv<1>)0);
        generic_enable_b.write((sc_bv<1>)1);
      } else {
        // ALL 0s
        data_ip_out.write((sc_bv<NUM_IP*16>)0);
        data_b_out.write((sc_bv<16>)0);
        address_b.write((sc_bv<6>)0);
        w_enable_b.write((sc_bv<1>)0);
        r_enable_b.write((sc_bv<1>)0);
        generic_enable_b.write((sc_bv<1>)0);
      }

    }
    return;
}

/*
////////////////////////////////////////////////////////////////////////////////
NOTE: THIS IS JUST PSEUDO CODE, NOT COMPATIBLE WITH SYSTEMC

Module: Packet switch

// Pure Comb module

if (transaction == 1) {     // get information from enabler
    // create a path from port(index) to data port
} else {  // transaction at 0, can get data from interrupt controller

  if(interrupt == 1) {    //probably not needed
    data = index_interrupt;
    address = 0;
  } else {
    .....
  }

}

////////////////////////////////////////////////////////////////////////////////
 */

///////////////////////////////////////////////////////////////////////////////
// --- END of packet Switcher.
///////////////////////////////////////////////////////////////////////////////


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// --- Interrupt controller.
///////////////////////////////////////////////////////////////////////////////
void obipm::interrupt_controller(){
    sc_bv<NUM_IP> intr_ip_v = (sc_bv<NUM_IP>)0;
    {
        HLS_DEFINE_PROTOCOL("Int_ctrl_reset");
        intr_ip_v = (sc_bv<NUM_IP>)0;
        // outpus signals should be set to 0
        index_interrupt.write(0);
        interrupt_internal.write("0");
        // MV end
        wait();
    }
    while(true){
        HLS_DEFINE_PROTOCOL("Int_ctrl_body");
        //wait();
        while(transaction.read() == '1'){
#ifdef DEBUG
            std::cout << "@ " << sc_time_stamp() << " OBIPM: filtering interrupts \n";
#endif
            wait();
        }
        intr_ip_v = interrupt_ip.read();
#ifdef DEBUG
        std::cout << "@ " << sc_time_stamp() << " OBIPM: accepting interrupts \n";
#endif
        if(irq.read() == '1'){
            for(int i = 0; i < NUM_IP; i++){
                if(intr_ip_v.range(i,i) == "1"){
                    index_interrupt.write(i+1);
                    while(transaction.read() == "1")    // Re-check if the CPU has required a transaction. Remember: CPU is the master.
                        wait();
                    interrupt_internal.write("1");
                    wait();
                    while(acked.read() == '0')
                        wait();
                    interrupt_internal.write('0');
                    break;
                }
            }
        }
        wait();
    }
}
///////////////////////////////////////////////////////////////////////////////
// --- END of interrupt controller.
///////////////////////////////////////////////////////////////////////////////

/*
////////////////////////////////////////////////////////////////////////////////
NOTE: THIS IS JUST PSEUDO CODE, NOT COMPATIBLE WITH SYSTEMC

Module: Interrupt controller



while(true) {

  while(transaction == 1) wait(); //if transaction used as reset signal(Reset = transaction OR global_reset) not need?
  if (int_req == 1) {
    for(i = 0; i < N_Port; i++) {
      if (interrupt_ip[i] == 1) {
        index_interrupt = i + 1;  //i + 1 due to IP Manager at addr 0
        int = 1;
        while(acked == 0) wait();
        int = 0;
        break;  // serve the current interrupt and scan it again from the first one, since new interrupt can arise in the meanwhile.
      }
    }
  }

}
 */

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// --- Support logic.
///////////////////////////////////////////////////////////////////////////////
// Manages internal combinational logic and wires.
void obipm::support_logic(){
    sc_bv<NUM_IP>  ack_internal_v;  // use these two variables to exploit the or_reduce() methods below.
    sc_bv<NUM_IP>  interrupt_ip_v;

    // Read values
    ack_internal_v = ack_internal.read();
    interrupt_ip_v = interrupt_ip.read();

    // Routing and oring of ack signals.
    ack_ip.write(ack_internal); // route to the external world
    acked.write(ack_internal_v.or_reduce());   // or reduce for the interrupt controller

    // Route interrupt signal to the external world
    interrupt_cpu.write(interrupt_internal);

    // Or reduce the interrupt signals from the IPs
    irq.write(interrupt_ip_v.or_reduce());
}
///////////////////////////////////////////////////////////////////////////////
// --- END of support logic.
///////////////////////////////////////////////////////////////////////////////
