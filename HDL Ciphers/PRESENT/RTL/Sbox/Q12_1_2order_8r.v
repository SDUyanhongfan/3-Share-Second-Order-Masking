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
* Please see LICENSE and README for license and further instructions.*/

module Q12_1_2order_8r(
	 input clk,
	 input [3:0] in1,
    input [3:0] in2,
    input [3:0] in3,
    input [7:0] r,
    output reg [3:0] out1,
    output reg [3:0] out2,
    output reg [3:0] out3
    );


	wire [3:0] q1;
   wire [3:0] q2;
   wire [3:0] q3;
	
	wire [35:0] CF_Out;
	reg [35:0] CF_Reg;
	
	reg [3:1] a;
	reg [3:1] b;
	reg [3:1] c;
	reg [3:1] d;

	
	always @(*) begin
		d = {in3[3],in2[3],in1[3]};
		c = {in3[2],in2[2],in1[2]};
		b = {in3[1],in2[1],in1[1]};
		a = {in3[0],in2[0],in1[0]};
	end

	genvar i;
   generate
		//NonLinear Layer
     
         NF_CF_1  CF_Inst (
				.a(a), 
				.b(b), 
				.c(c), 
				.d(d), 
				.q(CF_Out)
			);
     
		
	 //Compression

      assign q1[0]= CF_Reg[0]  ^ CF_Reg[1]   ^ CF_Reg[2] ;
      assign q1[1]= CF_Reg[9]  ^ CF_Reg[10]  ^ CF_Reg[11] ;
      assign q1[2]= CF_Reg[18] ^ CF_Reg[19]  ^ CF_Reg[20] ;
      assign q1[3]= CF_Reg[27] ^ CF_Reg[28]  ^ CF_Reg[29] ;	  

      assign q2[0]= CF_Reg[3]  ^ CF_Reg[4]   ^ CF_Reg[5] ;
      assign q2[1]= CF_Reg[12] ^ CF_Reg[13]  ^ CF_Reg[14] ;
      assign q2[2]= CF_Reg[21] ^ CF_Reg[22]  ^ CF_Reg[23] ;
	  assign q2[3]= CF_Reg[30] ^ CF_Reg[31]  ^ CF_Reg[32] ;	 

      assign q3[0]= CF_Reg[6]  ^ CF_Reg[7]   ^ CF_Reg[8] ;
      assign q3[1]= CF_Reg[15]  ^ CF_Reg[16]  ^ CF_Reg[17] ;
      assign q3[2]= CF_Reg[24] ^ CF_Reg[25]  ^ CF_Reg[26] ;
	  assign q3[3]= CF_Reg[33] ^ CF_Reg[34]  ^ CF_Reg[35] ;	 	  
	  
	  
	  
   endgenerate
	
	always @(posedge clk) begin
		//register between component functions and compression layer
		CF_Reg <= CF_Out;

	end
	
	always @(*) begin
	
		out1[0] = q1[0] ^ r[4];
		out2[0] = q2[0] ^ r[5];
		out3[0] = q3[0] ^ r[4] ^ r[5];
		
		out1[1] = q1[1] ^ r[6];
		out2[1] = q2[1] ^ r[7];
		out3[1] = q3[1] ^ r[6] ^ r[7];
		
		out1[2] = q1[2] ^ r[0];
		out2[2] = q2[2] ^ r[1];
		out3[2] = q3[2] ^ r[1] ^ r[0];
		
		out1[3] = q1[3] ^ r[2];
		out2[3] = q2[3] ^ r[3];
		out3[3] = q3[3] ^ r[2] ^ r[3];
	end

endmodule
