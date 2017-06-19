#include "ip.h"


#ifdef READ_TEST
////////////////////////////////////////////////////////////////////////////////
// READ test - BEGIN
////////////////////////////////////////////////////////////////////////////////
void ip::IP_thread(){
    // Local variables
    sc_bv<16> data_internal;    // holds data just read

    //reset
    data_ip_in.write((sc_bv<16>) 0);
    address_ip.write((sc_bv<6>) 0);
    w_enable_ip.write("0");
    r_enable_ip.write("0");
    generic_enable_ip.write("0");
    interrupt_ip.write("0");
    wait();   // wait for next clock edge to be activated
    // NOTE that the wait is necessary for allowing the reset
    // to work properly!

    //body
    if(!mytype){
        // Not active
        data_ip_in.write((sc_bv<16>) 0);
        address_ip.write((sc_bv<6>) 0);
        w_enable_ip.write("0");
        r_enable_ip.write("0");
        generic_enable_ip.write("0");
        interrupt_ip.write("0");

        // all outputs at 0


        while (1) {

          if (enable_ip.read() == "1") {
            // do nothing, not active
            // this situation should never happen
            std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << '\n';
            std::cout << "Error this IP shoudl not be enabled!!!" << '\n';
            std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << '\n';
            sc_stop();
          } else {
            // all outputs at 0
            data_ip_in.write((sc_bv<16>) 0);
            address_ip.write((sc_bv<6>) 0);
            w_enable_ip.write("0");
            r_enable_ip.write("0");
            generic_enable_ip.write("0");
            interrupt_ip.write("0");

          }
          wait(); //wait rising edge of clock
        }

    }
    //////////////////////////////////////////////////////////////////
    else {
        // Active
        data_ip_in.write((sc_bv<16>) 0);
        address_ip.write((sc_bv<6>) 0);
        w_enable_ip.write("0");
        r_enable_ip.write("0");
        generic_enable_ip.write("0");
        interrupt_ip.write("0");

        while (1) {

          if (enable_ip.read() == "1") {
            //set signals for a read
            w_enable_ip.write("0");
            r_enable_ip.write("1");
            generic_enable_ip.write("1");
            for (unsigned int i = 1; i < 4; i++) {
              //set address to be read
              address_ip.write( (sc_bv<6>) i);
              wait(); //suspend current process, signal get updated here
              // when the process resumes, data should from the buffer has arrived, read it
              data_internal = data_ip_out.read();
              std::cout << "IP: Data received: " << data_internal
                        << '\n';
            }
            // stop the simulation
            // TODO: NOTE by doing so we don't test the disable feature..
            sc_stop();
          } else {
            // all outputs at 0
              data_ip_in.write((sc_bv<16>) 0);
              address_ip.write((sc_bv<6>) 0);
              w_enable_ip.write("0");
              r_enable_ip.write("0");
              generic_enable_ip.write("0");
              interrupt_ip.write("0");
          }
          wait();
        }
    }

}

////////////////////////////////////////////////////////////////////////////////
// READ test - END
////////////////////////////////////////////////////////////////////////////////

#endif //READ_TEST

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


#ifdef WRITE_TEST
/////////////////////////////////////////////////////////////////////////
// WRITE TEST TB - BEGIN
/////////////////////////////////////////////////////////////////////////
void ip::IP_thread(){
    // Local variables
    sc_bv<16> data_internal;    // holds data just read

    //reset
    data_ip_in.write((sc_bv<16>) 0);
    address_ip.write((sc_bv<6>) 0);
    w_enable_ip.write("0");
    r_enable_ip.write("0");
    generic_enable_ip.write("0");
    interrupt_ip.write("0");
    wait();   // wait for next clock edge to be activated
    // NOTE that the wait is necessary for allowing the reset
    // to work properly!

    //body
    if(!mytype){
        // Not active
        data_ip_in.write((sc_bv<16>) 0);
        address_ip.write((sc_bv<6>) 0);
        w_enable_ip.write("0");
        r_enable_ip.write("0");
        generic_enable_ip.write("0");
        interrupt_ip.write("0");

        // all outputs at 0


        while (1) {

          if (enable_ip.read() == "1") {
            // do nothing, not active
            // this situazione should never happen
            std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << '\n';
            std::cout << "Error this IP shoudl not be enabled!!!" << '\n';
            std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << '\n';
            sc_stop();
          } else {
            // all outputs at 0
            data_ip_in.write((sc_bv<16>) 0);
            address_ip.write((sc_bv<6>) 0);
            w_enable_ip.write("0");
            r_enable_ip.write("0");
            generic_enable_ip.write("0");
            interrupt_ip.write("0");

          }
          wait(); //wait rising edge of clock
        }

    }
    //////////////////////////////////////////////////////////////////
    else {
        // Active
        data_ip_in.write((sc_bv<16>) 0);
        address_ip.write((sc_bv<6>) 0);
        w_enable_ip.write("0");
        r_enable_ip.write("0");
        generic_enable_ip.write("0");
        interrupt_ip.write("0");

        while (1) {

          if (enable_ip.read() == "1") {
            //set signals for a write
            w_enable_ip.write("1");
            r_enable_ip.write("0");
            generic_enable_ip.write("1");
            for (unsigned int i = 1; i < 4; i++) {
              //set address to be read
              address_ip.write( (sc_bv<6>) i);
              // set data to be written
              data_ip_in.write((sc_bv<16>) i);
              std::cout << "IP: writing value: "<< (sc_bv<16>)i << " @ address: " << (sc_bv<6>)i << "\n";
              wait(); //suspend current process, signals updated
            }
            // stop the simulation
            // TODO: NOTE by doing so we don't test the disable feature..
            sc_stop();
          } else {
            // all outputs at 0
              data_ip_in.write((sc_bv<16>) 0);
              address_ip.write((sc_bv<6>) 0);
              w_enable_ip.write("0");
              r_enable_ip.write("0");
              generic_enable_ip.write("0");
              interrupt_ip.write("0");
          }
          wait();
        }
    }

}
/////////////////////////////////////////////////////////////////////////
// WRITE TEST TB - END
/////////////////////////////////////////////////////////////////////////
#endif //WRITE_TEST



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#ifdef INTERRUPT_TEST
/////////////////////////////////////////////////////////////////////////
// INTERRUPT TEST TB - BEGIN
/////////////////////////////////////////////////////////////////////////
// IMPORTANT NOTE: here true/false parameters given to the constructors
// assumes a different meanign. True is the IP requesting an interrupt
// while the other (false) does a fake transaction (without exchange
// of data).

void ip::IP_thread(){
    // Local variables
    sc_bv<16> data_internal;    // holds data just read

    //reset
    data_ip_in.write((sc_bv<16>) 0);
    address_ip.write((sc_bv<6>) 0);
    w_enable_ip.write("0");
    r_enable_ip.write("0");
    generic_enable_ip.write("0");
    interrupt_ip.write("0");
    wait();   // wait for next clock edge to be activated
    // NOTE that the wait is necessary for allowing the reset
    // to work properly!

    //body
    if(!mytype){
        // Not active
        data_ip_in.write((sc_bv<16>) 0);
        address_ip.write((sc_bv<6>) 0);
        w_enable_ip.write("0");
        r_enable_ip.write("0");
        generic_enable_ip.write("0");
        interrupt_ip.write("0");

        // all outputs at 0


        while (1) {
          // do nothing, fake transaction
          wait(); //wait rising edge of clock
        }

    }
    //////////////////////////////////////////////////////////////////
    else {
        // Active
        data_ip_in.write((sc_bv<16>) 0);
        address_ip.write((sc_bv<6>) 0);
        w_enable_ip.write("0");
        r_enable_ip.write("0");
        generic_enable_ip.write("0");
        interrupt_ip.write("0");

        std::cout << "@ " << sc_time_stamp() << " IP: waiting 6 cycles before raising the interrupt request.\n";
        wait(6);    // wait 6 clock cycles to raise interrupt
        std::cout << "@ " << sc_time_stamp() << " IP: done waiting the 6 cycles.\n";

        while (1) {
          interrupt_ip.write("1");
          std::cout << "@ " << sc_time_stamp() << " IP: raising the irq.\n";
          wait();
        }
    }

}


/////////////////////////////////////////////////////////////////////////
// INTERRUPT TEST TB - BEGIN
/////////////////////////////////////////////////////////////////////////
#endif

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
