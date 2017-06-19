#include "system.h"

void TOP::initInstances()
{
    m_dut = new obipm_wrapper("obipm_wrapper");

    // Connect the design module
    m_dut->clk(clk);
    m_dut->rst(rst);
    // OBIPM-Buffer Interface -- MV
    m_dut->row_0_b(row_0_b);
    m_dut->data_b_in(data_b_in);   // used for read operartion
    m_dut->data_b_out(data_b_out);  // used for write opertaion
    m_dut->address_b(address_b);
    m_dut->w_enable_b(w_enable_b);
    m_dut->r_enable_b(r_enable_b);
    m_dut->generic_enable_b(generic_enable_b);
    // OBIPM-IP Interface
    m_dut->data_ip_in(data_ip_in);   //for write operation from IP
    m_dut->data_ip_out(data_ip_out);  // for read operation from IP
    m_dut->address_ip(address_ip);
    m_dut->w_enable_ip(w_enable_ip);
    m_dut->r_enable_ip(r_enable_ip);
    m_dut->generic_enable_ip(generic_enable_ip);
    m_dut->enable_ip(enable_ip);
    m_dut->ack_ip(ack_ip);
    m_dut->interrupt_ip(interrupt_ip);
    // OBIPM-CPU Interface
    m_dut->interrupt_cpu(interrupt_cpu);

    // Connect the testbench
    m_tb = new tb("tb");
    m_tb->clk(clk);
    m_tb->rst(rst);
    // OBIPM-Buffer Interface -- MV
    m_tb->row_0_b(row_0_b);
    m_tb->data_b_in(data_b_in);   // used for read operartion
    m_tb->data_b_out(data_b_out);  // used for write opertaion
    m_tb->address_b(address_b);
    m_tb->w_enable_b(w_enable_b);
    m_tb->r_enable_b(r_enable_b);
    m_tb->generic_enable_b(generic_enable_b);
    // OBIPM-IP Interface
    m_tb->data_ip_in(data_ip_in);   //for write operation from IP
    m_tb->data_ip_out(data_ip_out);  // for read operation from IP
    m_tb->address_ip(address_ip);
    m_tb->w_enable_ip(w_enable_ip);
    m_tb->r_enable_ip(r_enable_ip);
    m_tb->generic_enable_ip(generic_enable_ip);
    m_tb->enable_ip(enable_ip);
    m_tb->ack_ip(ack_ip);
    m_tb->interrupt_ip(interrupt_ip);
    // OBIPM-CPU Interface
    m_tb->interrupt_cpu(interrupt_cpu);

}

void TOP::deleteInstances()
{
    delete m_tb;
    delete m_dut;
}
