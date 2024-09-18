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
ENTITY KeyExpansion IS
	PORT ( CLK			: IN  STD_LOGIC;
			 -- CONTROL PORTS --------------------------------
                   RESET		: IN  STD_LOGIC;
		    ROUND_CST	: IN STD_LOGIC_VECTOR (4 DOWNTO 0);
			 ENABLE     : IN  STD_LOGIC;
		    -- KEY PORT -------------------------------------
			 KEY			: IN  STD_LOGIC_VECTOR ((80 - 1) DOWNTO 0);
			 KEY_SI		: OUT STD_LOGIC_VECTOR ((16 - 1) DOWNTO 0);
			 KEY_SO		: IN  STD_LOGIC_VECTOR ((16 - 1) DOWNTO 0);
			 
			 ROUND_KEY	: OUT STD_LOGIC_VECTOR ((80 - 1) DOWNTO 0));
END KeyExpansion;



-- ARCHITECTURE : ROUND
----------------------------------------------------------------------------------
ARCHITECTURE Round OF KeyExpansion IS

	-- CONSTANTS ------------------------------------------------------------------
	CONSTANT T : INTEGER := 80;

	-- SIGNALS --------------------------------------------------------------------
	SIGNAL KEY_STATE, KEY_NEXT: STD_LOGIC_VECTOR((T - 1) DOWNTO 0);
    SIGNAL Sbox_KI0,	Sbox_KI1, Sbox_KI2, Sbox_KI3: STD_LOGIC_VECTOR(3 DOWNTO 0);
	SIGNAL Sbox_KO0,	Sbox_KO1, Sbox_KO2, Sbox_KO3: STD_LOGIC_VECTOR(3 DOWNTO 0);
	SIGNAL ROW_K0,	ROW_K1, ROW_K2, ROW_K3,ROW_K4: STD_LOGIC_VECTOR(15 DOWNTO 0);
	SIGNAL ROWP_K0,	ROWP_K1, ROWP_K2, ROWP_K3,ROWP_K4: STD_LOGIC_VECTOR(15 DOWNTO 0);
	SIGNAL ROWS_K0,	ROWS_K3: STD_LOGIC_VECTOR(15 DOWNTO 0);
	SIGNAL Const_K0: STD_LOGIC_VECTOR(4 DOWNTO 0);
	
	
BEGIN

	-- REGISTER STAGE -------------------------------------------------------------
	RS : ENTITY work.ScanFF_en GENERIC MAP (SIZE => T) PORT MAP (CLK, RESET, ENABLE, KEY_NEXT, KEY, KEY_STATE);
 --   RS : ENTITY work.ScanFF GENERIC MAP (SIZE => T) PORT MAP (CLK, RESET, KEY_NEXT,KEY, KEY_STATE);


        Sbox_KI0 <= KEY_STATE(48) & KEY_STATE(32) &  KEY_STATE(16) &  KEY_STATE(0) ;
	Sbox_KI1 <= KEY_STATE(49) & KEY_STATE(33) &  KEY_STATE(17) &  KEY_STATE(1) ;
	Sbox_KI2 <= KEY_STATE(50) & KEY_STATE(34) &  KEY_STATE(18) &  KEY_STATE(2) ;
	Sbox_KI3 <= KEY_STATE(51) & KEY_STATE(35) &  KEY_STATE(19) &  KEY_STATE(3) ;
	
	KEY_SI	 <= Sbox_KI3& Sbox_KI2 & Sbox_KI1 & Sbox_KI0;
	Sbox_KO0 <= KEY_SO(3  DOWNTO 0);
	Sbox_KO1 <= KEY_SO(7  DOWNTO 4);
	Sbox_KO2 <= KEY_SO(11 DOWNTO 8);
	Sbox_KO3 <= KEY_SO(15 DOWNTO 12);
	
	ROW_K0  <= KEY_STATE(15 DOWNTO 4) & Sbox_KO3(0) & Sbox_KO2(0)  & Sbox_KO1(0)  & Sbox_KO0(0);
	ROW_K1  <= KEY_STATE(31 DOWNTO 20)& Sbox_KO3(1) & Sbox_KO2(1)  & Sbox_KO1(1)  & Sbox_KO0(1);	
	ROW_K2  <= KEY_STATE(47 DOWNTO 36) & Sbox_KO3(2) & Sbox_KO2(2)  & Sbox_KO1(2)  & Sbox_KO0(2);		
	ROW_K3  <= KEY_STATE(63 DOWNTO 52) & Sbox_KO3(3) & Sbox_KO2(3)  & Sbox_KO1(3)  & Sbox_KO0(3);	
	ROW_K4  <= KEY_STATE(79 DOWNTO 64);
	
	ROWS_K0  <= ROW_K0 (7 DOWNTO 0 ) &  ROW_K0 (15 DOWNTO 8 ); 
	ROWS_K3  <= ROW_K3 (3 DOWNTO 0 ) &  ROW_K3 (15 DOWNTO 4 ); 	
	
	ROWP_K0 <= ROWS_K0 XOR ROW_K1;
	ROWP_K1 <= ROW_K2;
	ROWP_K2 <= ROW_K3;	
	ROWP_K3 <= ROWS_K3 XOR ROW_K4;		
	ROWP_K4 <= ROW_K0;
	Const_K0 <= ROWP_K0 (4 DOWNTO 0) XOR ROUND_CST;
	
	KEY_NEXT <= ROWP_K4 &  ROWP_K3 & ROWP_K2 & ROWP_K1 & ROWP_K0(15 DOWNTO 5) & Const_K0;

	-- KEY OUTPUT -----------------------------------------------------------------
	ROUND_KEY <= KEY_STATE;

END Round;
