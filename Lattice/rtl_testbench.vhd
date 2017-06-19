--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   22:48:57 06/06/2017
-- Design Name:   
-- Module Name:   D:/obipm/obpm_tb.vhd
-- Project Name:  obipm
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: obipm
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY obpm_tb IS
END obpm_tb;
 
ARCHITECTURE behavior OF obpm_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT obipm
    PORT(
         clk : IN  std_logic;
         rst : IN  std_logic;
         row_0_b : IN  std_logic_vector(15 downto 0);
         data_b_in : IN  std_logic_vector(15 downto 0);
         data_ip_in : IN  std_logic_vector(79 downto 0);
         address_ip : IN  std_logic_vector(29 downto 0);
         w_enable_ip : IN  std_logic_vector(4 downto 0);
         r_enable_ip : IN  std_logic_vector(4 downto 0);
         generic_enable_ip : IN  std_logic_vector(4 downto 0);
         interrupt_ip : IN  std_logic_vector(4 downto 0);
			
			data_ip_out : OUT  std_logic_vector(79 downto 0);
			enable_ip : OUT  std_logic_vector(4 downto 0);
         ack_ip : OUT  std_logic_vector(4 downto 0);
		   generic_enable_b : OUT  std_logic_vector(0 downto 0);
			data_b_out : OUT  std_logic_vector(15 downto 0);
         address_b : OUT  std_logic_vector(5 downto 0);
         w_enable_b : OUT  std_logic_vector(0 downto 0);
         r_enable_b : OUT  std_logic_vector(0 downto 0);
			
         interrupt_cpu : OUT  std_logic_vector(0 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal rst : std_logic := '0';
   signal row_0_b : std_logic_vector(15 downto 0) := (others => '0');
   signal data_b_in : std_logic_vector(15 downto 0) := (others => '0');
   signal data_ip_in : std_logic_vector(79 downto 0) := (others => '0');
   signal address_ip : std_logic_vector(29 downto 0) := (others => '0');
   signal w_enable_ip : std_logic_vector(4 downto 0) := (others => '0');
   signal r_enable_ip : std_logic_vector(4 downto 0) := (others => '0');
   signal generic_enable_ip : std_logic_vector(4 downto 0) := (others => '0');
   signal interrupt_ip : std_logic_vector(4 downto 0) := (others => '0');

 	--Outputs
   signal data_b_out : std_logic_vector(15 downto 0);
   signal address_b : std_logic_vector(5 downto 0);
   signal w_enable_b : std_logic_vector(0 downto 0);
   signal r_enable_b : std_logic_vector(0 downto 0);
   signal generic_enable_b : std_logic_vector(0 downto 0);
   signal data_ip_out : std_logic_vector(79 downto 0);
   signal enable_ip : std_logic_vector(4 downto 0);
   signal ack_ip : std_logic_vector(4 downto 0);
   signal interrupt_cpu : std_logic_vector(0 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: obipm PORT MAP (
          clk => clk,
          rst => rst,
          row_0_b => row_0_b,
          data_b_in => data_b_in,
          data_b_out => data_b_out,
          address_b => address_b,
          w_enable_b => w_enable_b,
          r_enable_b => r_enable_b,
          generic_enable_b => generic_enable_b,
          data_ip_in => data_ip_in,
          data_ip_out => data_ip_out,
          address_ip => address_ip,
          w_enable_ip => w_enable_ip,
          r_enable_ip => r_enable_ip,
          generic_enable_ip => generic_enable_ip,
          enable_ip => enable_ip,
          ack_ip => ack_ip,
          interrupt_ip => interrupt_ip,
          interrupt_cpu => interrupt_cpu
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
		rst<='1';
      wait for 20 ns;	
		generic_enable_ip<="00001";
		w_enable_ip<="00001"; -- IP1
		row_0_b<=x"1001";
		data_ip_in<=(0 =>'1',others=>'0'); --Data ='1' IP1
      wait for clk_period*2;
		
	   row_0_b<=x"0001";
		wait for clk_period*2;
		
		w_enable_ip<="00010";
		row_0_b<=x"1002";
		data_ip_in<=(17 =>'1',others=>'0');
		wait for clk_period*2;
		
		row_0_b<=x"0002";
		wait for clk_period*2;
		
		w_enable_ip<="00100";
		row_0_b<=x"1003";
		data_ip_in<=(33 downto 32 =>'1',others=>'0');
		wait for clk_period*2;
		
		row_0_b<=x"0003";
		wait for clk_period*2;
		
		w_enable_ip<="01000";
		row_0_b<=x"1004";
		data_ip_in<=(50 =>'1',others=>'0');
		
		wait for clk_period*2;
		row_0_b<=x"0004";
		
		wait for clk_period*2;
		
		w_enable_ip<="10000";
		row_0_b<=x"1005";
		data_ip_in<=(67 =>'1',others=>'0');
		
		wait for clk_period*2;
		row_0_b<=x"0005";
		
      wait;
   end process;

END;
