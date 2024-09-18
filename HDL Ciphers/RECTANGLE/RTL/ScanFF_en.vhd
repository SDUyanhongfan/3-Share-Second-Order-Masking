--
-- -----------------------------------------------------------------
-- COMPANY : Shandong University
-- AUTHOR  : Yanhong Fan, Chaoran Wang, Lixuan Wu, Meiqin Wang
-- DOCUMENT: "A Fast Search Method for 3-Share Second-Order Masking Sc
-- -----------------------------------------------------------------
--
-- Copyright c 2024, Yanhong Fan, Chaoran Wang, Lixuan Wu, Meiqin Wang
--
-- 
--All rights reserved.
-- 
-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
-- ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, T
-- WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
-- DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTERS 
-- DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
-- INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR S
-- LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAU
-- ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
-- INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
--SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-- 
--Please see LICENSE and README for license and further instructions.

-- IMPORTS
----------------------------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;



-- ENTITY
----------------------------------------------------------------------------------
ENTITY ScanFF_en IS
	GENERIC (SIZE : INTEGER);
	PORT ( CLK	: IN 	STD_LOGIC;
          SE 	: IN 	STD_LOGIC;
			 EN   : IN  STD_LOGIC;
          D  	: IN 	STD_LOGIC_VECTOR((SIZE - 1) DOWNTO 0);
          DS	: IN 	STD_LOGIC_VECTOR((SIZE - 1) DOWNTO 0);
          Q 	: OUT STD_LOGIC_VECTOR((SIZE - 1) DOWNTO 0));
END ScanFF_en;



-- ARCHITECTURE : STRUCTURAL
----------------------------------------------------------------------------------
ARCHITECTURE Structural OF ScanFF_en IS

	-- COMPONENTS -----------------------------------------------------------------
	COMPONENT dflipfloplw_en IS
	PORT ( CLK  : IN  STD_LOGIC;
			 SEL	: IN  STD_LOGIC;
			 EN	: IN  STD_LOGIC;
			 D0   : IN  STD_LOGIC;
			 D1   : IN  STD_LOGIC;
			 Q    : OUT STD_LOGIC);
	END COMPONENT;
	-------------------------------------------------------------------------------

BEGIN

	GEN : FOR I IN 0 TO (SIZE - 1) GENERATE
		SFF : dflipfloplw_en PORT MAP (CLK, SE, EN, D(I), DS(I), Q(I));
	END GENERATE;

END Structural;
