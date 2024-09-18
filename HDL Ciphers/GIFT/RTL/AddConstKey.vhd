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
ENTITY AddConstKey IS
	PORT ( -- CONST PORT -----------------------------------
			 CONST			: IN	STD_LOGIC_VECTOR(5 DOWNTO 0);
			 -- KEY PORT -------------------------------------
			 ROUND_KEY		: IN	STD_LOGIC_VECTOR((128 	- 1) DOWNTO 0);
			 -- DATA PORTS -----------------------------------
			 DATA_IN			: IN	STD_LOGIC_VECTOR((64 	- 1) DOWNTO 0);
			 DATA_OUT		: OUT STD_LOGIC_VECTOR((64	- 1) DOWNTO 0));
END AddConstKey;



-- ARCHITECTURE : MIXED
----------------------------------------------------------------------------------
ARCHITECTURE Parallel OF AddConstKey IS

	-- CONSTANTS ------------------------------------------------------------------
	CONSTANT N : INTEGER := 64;


	-- SIGNALS --------------------------------------------------------------------
	SIGNAL CONST_ADDITION	: STD_LOGIC_VECTOR((N - 1) DOWNTO 0);
	SIGNAL KEY_U,KEY_V	: STD_LOGIC_VECTOR((16 - 1) DOWNTO 0);

BEGIN
    KEY_U <= ROUND_KEY(31 DOWNTO 16) ;
	KEY_V <= ROUND_KEY(15 DOWNTO 0) ;
	DATA_OUT(0)<=DATA_IN(0) XOR KEY_V(0);
	DATA_OUT(1)<=DATA_IN(1) XOR KEY_U(0);
    DATA_OUT(2)<=DATA_IN(2);
	DATA_OUT(3)<=DATA_IN(3) XOR CONST(0);
	
    DATA_OUT(4)<=DATA_IN(4) XOR KEY_V(1);
	DATA_OUT(5)<=DATA_IN(5) XOR KEY_U(1);
    DATA_OUT(6)<=DATA_IN(6);
	DATA_OUT(7)<=DATA_IN(7) XOR CONST(1);
	
    DATA_OUT(8 )<=DATA_IN(8 ) XOR KEY_V(2);
	DATA_OUT(9 )<=DATA_IN(9 ) XOR KEY_U(2);
    DATA_OUT(10)<=DATA_IN(10);
	DATA_OUT(11)<=DATA_IN(11) XOR CONST(2);	
	
    DATA_OUT(12)<=DATA_IN(12) XOR KEY_V(3);
	DATA_OUT(13)<=DATA_IN(13) XOR KEY_U(3);
    DATA_OUT(14)<=DATA_IN(14);
	DATA_OUT(15)<=DATA_IN(15) XOR CONST(3);	
	
    DATA_OUT(16)<=DATA_IN(16) XOR KEY_V(4);
	DATA_OUT(17)<=DATA_IN(17) XOR KEY_U(4);
    DATA_OUT(18)<=DATA_IN(18);
	DATA_OUT(19)<=DATA_IN(19) XOR CONST(4);		
	
    DATA_OUT(20)<=DATA_IN(20) XOR KEY_V(5);
	DATA_OUT(21)<=DATA_IN(21) XOR KEY_U(5);
    DATA_OUT(22)<=DATA_IN(22);
	DATA_OUT(23)<=DATA_IN(23) XOR CONST(5);		
	
    DATA_OUT(24)<=DATA_IN(24) XOR KEY_V(6);
	DATA_OUT(25)<=DATA_IN(25) XOR KEY_U(6);
    DATA_OUT(27 DOWNTO 26)<=DATA_IN(27 DOWNTO 26);

    DATA_OUT(28)<=DATA_IN(28) XOR KEY_V(7);
	DATA_OUT(29)<=DATA_IN(29) XOR KEY_U(7);
    DATA_OUT(31 DOWNTO 30)<=DATA_IN(31 DOWNTO 30);

    DATA_OUT(32)<=DATA_IN(32) XOR KEY_V(8);
	DATA_OUT(33)<=DATA_IN(33) XOR KEY_U(8);
    DATA_OUT(35 DOWNTO 34)<=DATA_IN(35 DOWNTO 34);

    DATA_OUT(36)<=DATA_IN(36) XOR KEY_V(9);
	DATA_OUT(37)<=DATA_IN(37) XOR KEY_U(9);
    DATA_OUT(39 DOWNTO 38)<=DATA_IN(39 DOWNTO 38);			

    DATA_OUT(40)<=DATA_IN(40) XOR KEY_V(10);
	DATA_OUT(41)<=DATA_IN(41) XOR KEY_U(10);
    DATA_OUT(43 DOWNTO 42)<=DATA_IN(43 DOWNTO 42);	

    DATA_OUT(44)<=DATA_IN(44) XOR KEY_V(11);
	DATA_OUT(45)<=DATA_IN(45) XOR KEY_U(11);
    DATA_OUT(47 DOWNTO 46)<=DATA_IN(47 DOWNTO 46);	

    DATA_OUT(48)<=DATA_IN(48) XOR KEY_V(12);
	DATA_OUT(49)<=DATA_IN(49) XOR KEY_U(12);
    DATA_OUT(51 DOWNTO 50)<=DATA_IN(51 DOWNTO 50);	

    DATA_OUT(52)<=DATA_IN(52) XOR KEY_V(13);
	DATA_OUT(53)<=DATA_IN(53) XOR KEY_U(13);
    DATA_OUT(55 DOWNTO 54)<=DATA_IN(55 DOWNTO 54);
	
    DATA_OUT(56)<=DATA_IN(56) XOR KEY_V(14);
	DATA_OUT(57)<=DATA_IN(57) XOR KEY_U(14);
    DATA_OUT(59 DOWNTO 58)<=DATA_IN(59 DOWNTO 58);
	
	DATA_OUT(60)<=DATA_IN(60) XOR KEY_V(15);
	DATA_OUT(61)<=DATA_IN(61) XOR KEY_U(15);
    DATA_OUT(62)<=DATA_IN(62);
    DATA_OUT(63)<= NOT DATA_IN(63)  ;
  
END Parallel;
