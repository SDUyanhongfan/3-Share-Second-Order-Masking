-- 
-- -----------------------------------------------------------------
-- COMPANY : Shandong University
-- AUTHOR  : Yanhong Fan, Chaoran Wang, Lixuan Wu, Meiqin Wang
-- DOCUMENT: "A Fast Search Method for 3-Share Second-Order Masking Schemes for Lightweight S-Boxes"  
-- -----------------------------------------------------------------
-- 
-- Copyright c 2024, Yanhong Fan, Chaoran Wang, Lixuan Wu, Meiqin Wang
-- 
-- 
-- All rights reserved.
-- 
-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
-- ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
-- WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
-- DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTERS BE LIABLE FOR ANY
-- DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
-- INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
-- LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND
-- ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
-- INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE OF THIS
-- SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-- 
-- Please see LICENSE and README for license and further instructions.
-- 


-- IMPORTS
----------------------------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

-- ENTITY
----------------------------------------------------------------------------------
ENTITY AddKey IS
	PORT ( 
			 -- KEY PORT -------------------------------------
			 ROUND_KEY		: IN	STD_LOGIC_VECTOR((80 	- 1) DOWNTO 0);
			 -- DATA PORTS -----------------------------------
			 DATA_IN			: IN	STD_LOGIC_VECTOR((64 	- 1) DOWNTO 0);
			 DATA_OUT		: OUT STD_LOGIC_VECTOR((64	- 1) DOWNTO 0));
END AddKey;



-- ARCHITECTURE : MIXED
----------------------------------------------------------------------------------
ARCHITECTURE Parallel OF AddKey IS

	-- CONSTANTS ------------------------------------------------------------------
	CONSTANT N : INTEGER := 64;


	-- SIGNALS --------------------------------------------------------------------
	SIGNAL CONST_ADDITION	: STD_LOGIC_VECTOR((N - 1) DOWNTO 0);
	SIGNAL KEY_U,KEY_V	: STD_LOGIC_VECTOR((16 - 1) DOWNTO 0);

BEGIN
   
    DATA_OUT<=  DATA_IN XOR  ROUND_KEY (63 DOWNTO 0 ) ;
  
END Parallel;
