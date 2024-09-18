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

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity counter is
	generic(NBITS: integer);
	port(
		clk	: in std_logic;
		nReset	: in std_logic;
		en    : in std_logic;
		q	: out std_logic_vector(NBITS - 1 downto 0)
		);

end entity counter;

architecture dfl of counter  is

	signal count_reg : unsigned(NBITS - 1 downto 0);
begin

process(clk, nReset, en)
begin
	if(clk'event and clk = '1') then
	   if (nReset = '0') then
		   count_reg <= (others => '0'); 
	   elsif(en = '1') then
			count_reg <= count_reg + 1;
		end if;
	end if;
end process;

q <= std_logic_vector(count_reg);

end architecture dfl;
