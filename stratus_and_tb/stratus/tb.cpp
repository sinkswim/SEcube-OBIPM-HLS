#include "tb.h"
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
// RESETTER- BEGIN
/////////////////////////////////////////////////////////////////////////
// resetter: in charge of simply sending the reset signal at start
//of simulation.
void tb::resetter()
{
    // Reset
    rst = 0;    // Assert the reset signal.
    wait(2);
    rst = 1;
    wait();
}
/////////////////////////////////////////////////////////////////////////
// RESETTER - END
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
// READ TEST TB - BEGIN
/////////////////////////////////////////////////////////////////////////
#ifdef READ_TEST
// The following is the TB for testing a read operation, i.e. the IP1
// reads data from the buffer. IP1 is not active during this test

/////////////////////////////////////////////////////////////////////////
// BUFFER - BEGIN
/////////////////////////////////////////////////////////////////////////
// buffer (regfile)
void tb::buffer()
{
    // reset phase, this block executed at time 0 when all process are
    // executed.
    regfile[0] = CW_READ_TEST;  // Place here the CW for READ_TEST
    // assuming a read_operation from the buffer
    // some data  must be placed here
    for(int i=1; i < 64; i++)
        regfile[i] = (sc_bv<16> )i;

    row_0_b.write(regfile[0]);  // write row_zero's content to the output signal row_0_b

    wait();

    while(1) {

      if(generic_enable_b.read() == "1"){
          if(w_enable_b.read() == "1") {
              std::cout << "BUFFER: Address write: " << address_b.read()
                        << " Data write: "    << data_b_out.read()
                        << '\n';
              regfile[sc_uint<16>(address_b.read())] = data_b_out.read();
          } else if(r_enable_b.read() == "1") {   // read operation
              std::cout << "BUFFER: Address read: " << address_b.read()
                        << " Data read: "      << regfile[sc_uint<16>(address_b.read())]
                        << '\n';
              data_b_in.write(regfile[sc_uint<16>(address_b.read())]);
          } else {
              //invalid transaction, output at 0
              std::cout << "Buffer: Invalid transaction." << '\n';
              data_b_in.write((sc_bv<16>)0);
          }
      }
      row_0_b.write(regfile[0]);  //write out whatever is written (if overwritten, else outputs same the same value as above)
      wait();   //wait for any event from the manager
    }
  }

/////////////////////////////////////////////////////////////////////////
// BUFFER - END
/////////////////////////////////////////////////////////////////////////
#endif // READ_TEST
/////////////////////////////////////////////////////////////////////////
// READ TEST TB - END
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#ifdef WRITE_TEST
/////////////////////////////////////////////////////////////////////////
// WRITE TEST TB - BEGIN
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// BUFFER - BEGIN
/////////////////////////////////////////////////////////////////////////
// buffer (regfile)
void tb::buffer()
{
    // reset phase, this block executed at time 0 when all process are
    // executed.
    regfile[0] = CW_WRITE_TEST;  // Place here the CW for READ_TEST
    // assuming a read_operation from the buffer
    // some data  must be placed here
    for(int i=1; i < 64; i++)
        regfile[i] = (sc_bv<16> )0;

    row_0_b.write(regfile[0]);  //write the content to the output
    wait();

    while(1) {

      if(generic_enable_b.read() == "1"){
          if(w_enable_b.read() == "1") {
              std::cout << "BUFFER: Address write: " << address_b.read()
                        << " Data write: "    << data_b_out.read()
                        << '\n';
              regfile[sc_uint<16>(address_b.read())] = data_b_out.read();
          } else if(r_enable_b.read() == "1") {   // read operation
              std::cout << "BUFFER: Address read: " << address_b.read()
                        << " Data read: "      << regfile[sc_uint<16>(address_b.read())]
                        << '\n';
              data_b_in.write(regfile[sc_uint<16>(address_b.read())]);
          } else {
              //invalid transaction, output at 0
              data_b_in.write((sc_bv<16>)0);
          }
      }
      row_0_b.write(regfile[0]);  //write out whatever is written
      wait();   //wait for any event from the manager
    }
  }

/////////////////////////////////////////////////////////////////////////
// BUFFER - END
/////////////////////////////////////////////////////////////////////////
#endif // WRITE_TEST
/////////////////////////////////////////////////////////////////////////
// WRITE TEST TB - END
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#ifdef INTERRUPT_TEST
/////////////////////////////////////////////////////////////////////////
// INTERRUPT TEST TB - BEGIN
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// BUFFER - BEGIN
/////////////////////////////////////////////////////////////////////////
// buffer (regfile)
void tb::buffer()
{
    // reset phase, this block executed at time 0 when all process are
    // executed.
    regfile[0] = CW_INTERRUPT_TEST_BEGIN;  // Place here the CW for READ_TEST
    // assuming a read_operation from the buffer
    // some data  must be placed here
    for(int i=1; i < 64; i++)
        regfile[i] = (sc_bv<16> )0;



    row_0_b.write(regfile[0]);  //write the content to the output

    // wait for 15 clock cycles before closing the transaction
    // CLK_PERIOD is a define
    std::cout << "@ " << sc_time_stamp() << " BUFFER: keeping the transaction open to interrupt requests.\n";
    wait(CLK_PERIOD*15, SC_NS);
    std::cout << "@ " << sc_time_stamp() << " BUFFER: sending interrupt test end CW.\n";
    regfile[0] = CW_INTERRUPT_TEST_END;
    row_0_b.write(regfile[0]);
    
    while(1) {

      if(generic_enable_b.read() == "1"){
          if(w_enable_b.read() == "1") {
              std::cout << "BUFFER: Address write: " << address_b.read()
                        << " Data write: "    << data_b_out.read()
                        << '\n';
              regfile[sc_uint<16>(address_b.read())] = data_b_out.read();
          } else if(r_enable_b.read() == "1") {   // read operation
              std::cout << "BUFFER: Address read: " << address_b.read()
                        << " Data read: "      << regfile[sc_uint<16>(address_b.read())]
                        << '\n';
              data_b_in.write(regfile[sc_uint<16>(address_b.read())]);
          } else {
              //invalid transaction, output at 0
              data_b_in.write((sc_bv<16>)0);
          }
      }
      row_0_b.write(regfile[0]);  //write out whatever is written
      wait();   //wait for any event from the manager
    }
  }

/////////////////////////////////////////////////////////////////////////
// BUFFER - END
/////////////////////////////////////////////////////////////////////////
#endif  // INTERRUPT TEST
/////////////////////////////////////////////////////////////////////////
// INTERRUPT TEST TB - END
/////////////////////////////////////////////////////////////////////////
