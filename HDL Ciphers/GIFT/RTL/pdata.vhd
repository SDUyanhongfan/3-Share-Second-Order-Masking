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

dataOut <=dataIn(51)&dataIn(62)&dataIn(57)&dataIn(52)&dataIn(35)&dataIn(46)&dataIn(41)&dataIn(36)&dataIn(19)&dataIn(30)&dataIn(25)&dataIn(20)&dataIn(3)&dataIn(14)&dataIn(9)&dataIn(4) &dataIn(55)&dataIn(50)&dataIn(61)&dataIn(56)&dataIn(39)&dataIn(34)&dataIn(45)&dataIn(40) &dataIn(23)&dataIn(18)&dataIn(29)&dataIn(24)&dataIn(7)&dataIn(2)&dataIn(13)&dataIn(8)&dataIn(59)&dataIn(54)&dataIn(49)&dataIn(60)&dataIn(43)&dataIn(38)&dataIn(33)&dataIn(44)&dataIn(27)&dataIn(22)&dataIn(17)&dataIn(28)&dataIn(11)&dataIn(6)&dataIn(1)&dataIn(12)&dataIn(63)&dataIn(58)&dataIn(53)&dataIn(48)&dataIn(47)&dataIn(42)&dataIn(37)&dataIn(32)&dataIn(31)&dataIn(26)&dataIn(21)&dataIn(16)&dataIn(15)&dataIn(10)&dataIn(5)&dataIn(0); 

end architecture dfl;
