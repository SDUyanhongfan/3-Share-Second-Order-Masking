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
module NF_CF_1(
    input [3:1] a,
    input [3:1] b,
    input [3:1] c,
    input [3:1] d,
    output q 
	 );
	 
	parameter num = 1;
	 
	generate

		if(num==0) begin
			assign q = a[1]^(c[1]&b[1])^(c[1]&a[1]);
		end
		if(num==1) begin
			assign q =c[1]^(c[1]&b[2])^(c[1]&a[2]);
		end
		if(num==2) begin
			assign q = (c[1]&b[3])^(c[1]&a[3]);
		end
		if(num==3) begin
			assign q = (c[2]&b[1])^(c[2]&a[1]);
		end
		if(num==4) begin
			assign q =a[2]^(c[2]&b[2])^(c[2]&a[2]);
		end
		if(num==5) begin
			assign q = c[2]^(c[2]&b[3])^(c[2]&a[3]);
		end
		if(num==6) begin
			assign q = (c[3]&b[1])^(c[3]&a[1]);
		end
		if(num==7) begin
			assign q = c[3]^(c[3]&b[2])^(c[3]&a[2]);
		end
		if(num==8) begin
			assign q = a[3]^(c[3]&b[3])^(c[3]&a[3]);
		end
		if(num==9) begin
			assign q = a[1] ^ 1^(c[1]&b[1]);
		end
		if(num==10) begin
			assign q = c[1] ^ (c[1]&b[2]);
		end
		if(num==11) begin
			assign q =  b[3]^ (c[1]&b[3]);
		end
		if(num==12) begin
			assign q =  b[1] ^ (c[2]&b[1]);
		end
		if(num==13) begin
			assign q = a[2] ^ (c[2]&b[2]);
		end
		if(num==14) begin
			assign q = c[2]^(c[2]&b[3]);
		end
		if(num==15) begin
			assign q = c[3] ^ (c[3]&b[1]);
		end
		if(num==16) begin
			assign q = b[2] ^ (c[3]&b[2]);
		end
		if(num==17) begin
			assign q = a[3] ^ (c[3]&b[3]);
		end
		


	endgenerate


endmodule
