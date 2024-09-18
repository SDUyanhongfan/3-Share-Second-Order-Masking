/*
* -----------------------------------------------------------------
* COMPANY : Shandong University
* AUTHOR  : Yanhong Fan, Chaoran Wang, Lixuan Wu, Meiqin Wang
* DOCUMENT: "A Fast Search Method for 3-Share Second-Order Masking Schemes for Lightweight S-Boxes"  
* -----------------------------------------------------------------
*
* Copyright c 2024, Yanhong Fan, Chaoran Wang, Lixuan Wu, Meiqin Wang

*
* All rights reserved.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTERS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Please see LICENSE and README for license and further instructions.
*/
module NF_CF_2(
    input [3:1] a,
    input [3:1] b,
    input [3:1] c,
    input [3:1] d,
    output [26:0] q 
	 );
	 
	
			assign q[0] = 1 ^ b[1]  ^     (d[1]&b[1])  ^ (d[1]&c[1])   ;
			assign q[1] =  b[2] ^ c[2] ^  (d[1]&b[2])  ^ (d[1]&c[2])  ;
			assign q[2] =                 (d[1]&b[3])  ^ (d[1]&c[3])  ;
			assign q[3] =  b[1] ^  c[1]^  (d[2]&b[1])  ^ (d[2]&c[1])   ;
			assign q[4] =                 (d[2]&b[2])  ^ (d[2]&c[2])   ;
			assign q[5] =       b[3] ^    (d[2]&b[3])  ^ (d[2]&c[3])   ;
			assign q[6] =                 (d[3]&b[1])  ^ (d[3]&c[1])   ;
			assign q[7] =     b[2]^        (d[3]&b[2])  ^ (d[3]&c[2])   ;
			assign q[8] =  b[3]^  c[3]^   (d[3]&b[3])  ^ (d[3]&c[3])   ;
			assign q[9] =    a[1]^1^ (d[1]&b[1])  ^ (d[1]&c[1]) ^ (d[1]&a[1])   ; 
			assign q[10] =     b[2]^  (d[1]&b[2])  ^ (d[1]&c[2]) ^ (d[1]&a[2])  ; 
			assign q[11] =           (d[1]&b[3])  ^ (d[1]&c[3]) ^ (d[1]&a[3])  ;  
			assign q[12] =     b[1]^  (d[2]&b[1])  ^ (d[2]&c[1]) ^ (d[2]&a[1])   ; 
			assign q[13] =           (d[2]&b[2])  ^ (d[2]&c[2]) ^ (d[2]&a[2])   ;  
			assign q[14] =     a[3]^   (d[2]&b[3])  ^ (d[2]&c[3]) ^ (d[2]&a[3])   ; 
			assign q[15] =     a[1]^      (d[3]&b[1])  ^ (d[3]&c[1]) ^ (d[3]&a[1])   ;  
			assign q[16] =            (d[3]&b[2])  ^ (d[3]&c[2]) ^ (d[3]&a[2])   ; 
			assign q[17] =     b[3]^ a[3]^(d[3]&b[3])  ^ (d[3]&c[3]) ^ (d[3]&a[3])   ;  
			assign q[18] =     1   ^ (d[1]&c[1]) ^ (d[1]&a[1])   ;  
			assign q[19] =     a[2]   ^ (d[1]&c[2]) ^ (d[1]&a[2])  ; 
			assign q[20] =        (d[1]&c[3]) ^ (d[1]&a[3])  ;   
			assign q[21] =      a[1]  ^ (d[2]&c[1]) ^ (d[2]&a[1])   ; 
			assign q[22] =      (d[2]&c[2]) ^ (d[2]&a[2])   ;   
			assign q[23] =       (d[2]&c[3]) ^ (d[2]&a[3])   ; 
			assign q[24] =       (d[3]&c[1]) ^ (d[3]&a[1])   ;  
			assign q[25] =       (d[3]&c[2]) ^ (d[3]&a[2])   ;  
			assign q[26] =      a[3] ^ (d[3]&c[3]) ^ (d[3]&a[3])   ; 


endmodule
