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
			 ENABLE     : IN  STD_LOGIC;
		    -- KEY PORT -------------------------------------
			 KEY			: IN  STD_LOGIC_VECTOR ((128 - 1) DOWNTO 0);
			 ROUND_KEY	: OUT STD_LOGIC_VECTOR ((128 - 1) DOWNTO 0));
END KeyExpansion;



-- ARCHITECTURE : ROUND
----------------------------------------------------------------------------------
ARCHITECTURE Round OF KeyExpansion IS

	-- CONSTANTS ------------------------------------------------------------------
	CONSTANT T : INTEGER := 128;

	-- SIGNALS --------------------------------------------------------------------
	SIGNAL KEY_STATE, KEY_NEXT: STD_LOGIC_VECTOR((T - 1) DOWNTO 0);

BEGIN

	-- REGISTER STAGE -------------------------------------------------------------
	RS : ENTITY work.ScanFF_en GENERIC MAP (SIZE => T) PORT MAP (CLK, RESET, ENABLE, KEY_NEXT, KEY, KEY_STATE);

	
	 KEY_NEXT <= KEY_STATE(17 DOWNTO 16) & KEY_STATE(31 DOWNTO 18) & KEY_STATE(11 DOWNTO 0) & KEY_STATE(15 DOWNTO 12)& KEY_STATE(127 DOWNTO 32);

	-- KEY OUTPUT -----------------------------------------------------------------
	ROUND_KEY <= KEY_STATE;

END Round;
