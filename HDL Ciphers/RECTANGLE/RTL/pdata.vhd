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


-- This is the P-layer of GIFT
-- i   :  63 62  ...51.. 1   0
-- p(i):  15 62  ...63.. 17  0

LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

USE ieee.numeric_std.all;

entity pdata is
port(
	dataIn	: in std_logic_vector(63 downto 0);
	dataOut:	out std_logic_vector(63 downto 0)
	);
	
end entity pdata;

architecture dfl of pdata is

begin

dataOut <= dataIn(50 downto 48 )&  dataIn(63 downto 51 )& dataIn(35 downto 32 ) &  dataIn(47 downto 36 )& dataIn(30 downto 16 )& dataIn(31) & dataIn(15 downto 0 ); 

end architecture dfl;
