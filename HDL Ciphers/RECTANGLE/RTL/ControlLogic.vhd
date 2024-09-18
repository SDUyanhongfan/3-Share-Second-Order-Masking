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
--  Please see LICENSE and README for license and further instructions.*/
----------------------------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

-- ENTITY
----------------------------------------------------------------------------------
ENTITY ControlLogic IS
	PORT ( CLK			: IN	STD_LOGIC;
			 -- CONTROL PORTS --------------------------------
		  	 RESET		: IN  STD_LOGIC;
			 KEY_EN		: OUT STD_LOGIC;
		    DONE			: OUT STD_LOGIC;
			 -- CONST PORT -----------------------------------
          ROUND_CST	: OUT STD_LOGIC_VECTOR (4 DOWNTO 0));
END ControlLogic;



-- ARCHITECTURE : ROUND
----------------------------------------------------------------------------------
ARCHITECTURE Round OF ControlLogic IS

	-- SIGNALS --------------------------------------------------------------------
	SIGNAL STATE, UPDATE : STD_LOGIC_VECTOR(4 DOWNTO 0);
	SIGNAL SHIFT         : STD_LOGIC_VECTOR(4 DOWNTO 0);
	
BEGIN

	-- STATE ----------------------------------------------------------------------
	REG : PROCESS(CLK) BEGIN
		IF RISING_EDGE(CLK) THEN
			IF (RESET = '1') THEN
				STATE <= "00001";
				SHIFT <= "01000";
			ELSE
				IF (SHIFT(4) = '1') THEN
					STATE <= UPDATE;

				END IF;
				
				SHIFT <= SHIFT(3 DOWNTO 0) & SHIFT(4);
			END IF;
		END IF;
	END PROCESS;
	-------------------------------------------------------------------------------

	-- UPDATE FUNCTION ------------------------------------------------------------
	UPDATE <= STATE(3 DOWNTO 0) & (STATE(4) XOR STATE(2));

	-- CONSTANT -------------------------------------------------------------------
	ROUND_CST <= STATE;
	
	KEY_EN	<= SHIFT(4) OR RESET;

	-- DONE SIGNAL ----------------------------------------------------------------
	
	DONE <= '1' WHEN (STATE = "11010") ELSE '0';

END Round;
