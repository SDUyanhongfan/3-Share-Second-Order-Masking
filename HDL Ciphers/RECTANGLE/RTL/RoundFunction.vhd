--  
--  -----------------------------------------------------------------
--  COMPANY : Shandong University
--  AUTHOR  : Yanhong Fan, Chaoran Wang, Lixuan Wu, Meiqin Wang
--  DOCUMENT: "A Fast Search Method for 3-Share Second-Order Masking Schemes for Lightweight S-Boxes"  
--  -----------------------------------------------------------------
--  
--  Copyright c 2024, Yanhong Fan, Chaoran Wang, Lixuan Wu, Meiqin Wang
--  
--  
--  All rights reserved.
--  
--  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
--  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
--  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
--  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTERS BE LIABLE FOR ANY
--  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
--  INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
--  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND
--  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
--  INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE OF THIS
--  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--  
--  Please see LICENSE and README for license and further instructions.
-- 

-- IMPORTS
----------------------------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;


-- ENTITY
----------------------------------------------------------------------------------
ENTITY RoundFunction IS
   PORT ( CLK        : IN  STD_LOGIC;
   		 -- CONTROL PORTS --------------------------------
          RESET      : IN  STD_LOGIC;
   	    -- KEY PORT -------------------------------------
          ROUND_KEY  : IN  STD_LOGIC_VECTOR ((80 - 1) DOWNTO 0);
   	    -- DATA PORTS -----------------------------------
          ROUND_IN   : IN  STD_LOGIC_VECTOR ((64 - 1) DOWNTO 0);
			 SUB_IN		: OUT STD_LOGIC_VECTOR ((64 - 1) DOWNTO 0);
			 SUB_OUT		: IN  STD_LOGIC_VECTOR ((64 - 1) DOWNTO 0);
          ROUND_OUT  : OUT STD_LOGIC_VECTOR ((64 - 1) DOWNTO 0));
END RoundFunction;



-- ARCHITECTURE : ROUND
----------------------------------------------------------------------------------
ARCHITECTURE Round OF RoundFunction IS

	-- CONSTANTS ------------------------------------------------------------------
	CONSTANT N : INTEGER := 64;

	-- SIGNALS --------------------------------------------------------------------
	SIGNAL STATE, STATE_NEXT, SUBSTITUTE, ADDITION, PERMOUT	: STD_LOGIC_VECTOR((N - 1) DOWNTO 0);
    SIGNAL ROUND_INITIAL	: STD_LOGIC_VECTOR((N - 1) DOWNTO 0);
	SIGNAL Sbox_I0,	Sbox_I1, Sbox_I2, Sbox_I3, Sbox_I4, Sbox_I5, Sbox_I6,  Sbox_I7, Sbox_I8,	Sbox_I9, Sbox_I10, Sbox_I11, Sbox_I12, Sbox_I13, Sbox_I14,  Sbox_I15: STD_LOGIC_VECTOR(3 DOWNTO 0);
	SIGNAL Sbox_O0,	Sbox_O1, Sbox_O2, Sbox_O3, Sbox_O4, Sbox_O5, Sbox_O6,  Sbox_O7, Sbox_O8,	Sbox_O9, Sbox_O10, Sbox_O11, Sbox_O12, Sbox_O13, Sbox_O14,  Sbox_O15: STD_LOGIC_VECTOR(3 DOWNTO 0);
	SIGNAL Row_0,	Row_1, Row_2, Row_3: STD_LOGIC_VECTOR(15 DOWNTO 0);
	
	

BEGIN
    ROUND_INITIAL <= ROUND_IN XOR ROUND_KEY (63 DOWNTO 0 );
	-- REGISTER STAGE -------------------------------------------------------------
	RS : ENTITY work.ScanFF GENERIC MAP (SIZE => N) PORT MAP (CLK, RESET, STATE_NEXT,ROUND_INITIAL , STATE);

	-- SUBSTITUTION ---------------------------------------------------------------
	Sbox_I0 <= STATE(48) & STATE(32) &  STATE(16) &  STATE(0) ;
	Sbox_I1 <= STATE(49) & STATE(33) &  STATE(17) &  STATE(1) ;
	Sbox_I2 <= STATE(50) & STATE(34) &  STATE(18) &  STATE(2) ;
	Sbox_I3 <= STATE(51) & STATE(35) &  STATE(19) &  STATE(3) ;
	Sbox_I4 <= STATE(52) & STATE(36) &  STATE(20) &  STATE(4) ;
	Sbox_I5 <= STATE(53) & STATE(37) &  STATE(21) &  STATE(5) ;
	Sbox_I6 <= STATE(54) & STATE(38) &  STATE(22) &  STATE(6) ;
	Sbox_I7 <= STATE(55) & STATE(39) &  STATE(23) &  STATE(7) ;
	Sbox_I8 <= STATE(56) & STATE(40) &  STATE(24) &  STATE(8) ;
	Sbox_I9 <= STATE(57) & STATE(41) &  STATE(25) &  STATE(9) ;
	Sbox_I10<= STATE(58) & STATE(42) &  STATE(26) &  STATE(10) ;	
	Sbox_I11<= STATE(59) & STATE(43) &  STATE(27) &  STATE(11) ;
	Sbox_I12<= STATE(60) & STATE(44) &  STATE(28) &  STATE(12) ;
	Sbox_I13<= STATE(61) & STATE(45) &  STATE(29) &  STATE(13) ;
	Sbox_I14<= STATE(62) & STATE(46) &  STATE(30) &  STATE(14) ;
	Sbox_I15<= STATE(63) & STATE(47) &  STATE(31) &  STATE(15) ;		
	
	
	
	SUB_IN <= Sbox_I15 & Sbox_I14  & Sbox_I13  & Sbox_I12  & Sbox_I11  & Sbox_I10  & Sbox_I9  & Sbox_I8  & Sbox_I7  & Sbox_I6  & Sbox_I5  & Sbox_I4  & Sbox_I3  & Sbox_I2  & Sbox_I1  & Sbox_I0 ;
	
	Sbox_O0 <= SUB_OUT(  3  DOWNTO  0   )  ;
    Sbox_O1 <= SUB_OUT(  7  DOWNTO  4   )  ;
    Sbox_O2 <= SUB_OUT(  11 DOWNTO  8   )  ;
    Sbox_O3 <= SUB_OUT(  15 DOWNTO  12  )  ;
    Sbox_O4 <= SUB_OUT(  19 DOWNTO  16  )  ;
    Sbox_O5 <= SUB_OUT(  23 DOWNTO  20  )  ;
    Sbox_O6 <= SUB_OUT(  27 DOWNTO  24  )  ;
    Sbox_O7 <= SUB_OUT(  31 DOWNTO  28  )  ;
    Sbox_O8 <= SUB_OUT(  35 DOWNTO  32  )  ;
    Sbox_O9 <= SUB_OUT(  39 DOWNTO  36  )  ;
    Sbox_O10<= SUB_OUT(  43 DOWNTO  40  )  ;
    Sbox_O11<= SUB_OUT(  47 DOWNTO  44  )  ;
    Sbox_O12<= SUB_OUT(  51 DOWNTO  48  )  ;
    Sbox_O13<= SUB_OUT(  55 DOWNTO  52  )  ;
    Sbox_O14<= SUB_OUT(  59 DOWNTO  56  )  ;
    Sbox_O15<= SUB_OUT(  63 DOWNTO  60  )  ;
	
	Row_3 <=   Sbox_O15(3)& Sbox_O14(3) & Sbox_O13(3) & Sbox_O12(3) & Sbox_O11(3) & Sbox_O10(3) & Sbox_O9(3) & Sbox_O8(3) & Sbox_O7(3) & Sbox_O6(3) & Sbox_O5(3) & Sbox_O4(3) & Sbox_O3(3) & Sbox_O2(3) & Sbox_O1(3)& Sbox_O0(3);
    Row_2 <=   Sbox_O15(2)& Sbox_O14(2) & Sbox_O13(2) & Sbox_O12(2) & Sbox_O11(2) & Sbox_O10(2) & Sbox_O9(2) & Sbox_O8(2) & Sbox_O7(2) & Sbox_O6(2) & Sbox_O5(2) & Sbox_O4(2) & Sbox_O3(2) & Sbox_O2(2) & Sbox_O1(2)& Sbox_O0(2);
	Row_1 <=   Sbox_O15(1)& Sbox_O14(1) & Sbox_O13(1) & Sbox_O12(1) & Sbox_O11(1) & Sbox_O10(1) & Sbox_O9(1) & Sbox_O8(1) & Sbox_O7(1) & Sbox_O6(1) & Sbox_O5(1) & Sbox_O4(1) & Sbox_O3(1) & Sbox_O2(1) & Sbox_O1(1)& Sbox_O0(1);
	Row_0 <=   Sbox_O15(0)& Sbox_O14(0) & Sbox_O13(0) & Sbox_O12(0) & Sbox_O11(0) & Sbox_O10(0) & Sbox_O9(0) & Sbox_O8(0) & Sbox_O7(0) & Sbox_O6(0) & Sbox_O5(0) & Sbox_O4(0) & Sbox_O3(0) & Sbox_O2(0) & Sbox_O1(0)& Sbox_O0(0);
	
	SUBSTITUTE	<= Row_3 & Row_2 & Row_1 & Row_0;

   -- permutation -----------------------------------------------------------------
   
   
	PM : ENTITY work.pdata PORT MAP (SUBSTITUTE, PERMOUT);
	
	-- CONSTANT AND KEY ADDITION --------------------------------------------------
	KA : ENTITY work.AddKey PORT MAP ( ROUND_KEY, PERMOUT, STATE_NEXT);

	
	
	-- ROUND OUTPUT ---------------------------------------------------------------
	ROUND_OUT <= STATE;

END Round;
