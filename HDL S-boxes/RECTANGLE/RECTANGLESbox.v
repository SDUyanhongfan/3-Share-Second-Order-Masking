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
module RECTANGLESbox(
    input clk,
	 input [3:0] in1,
    input  [3:0] in2,
    input  [3:0] in3,
    input  [7:0] r,
    output  [3:0] out1,
    output  [3:0] out2,
    output  [3:0] out3
    );
	 
	 reg  [3:0] A_in1_reg,A_in2_reg,A_in3_reg;
	 wire [3:0] A_in1,A_in2,A_in3;
	 
	 reg  [3:0] A_out1_reg,A_out2_reg,A_out3_reg;
	 wire [3:0] A_out1,    A_out2,    A_out3;
	 
	
	 	 
	 
	 
	 always @(posedge clk) begin
		A_in1_reg	<= A_in1;
		A_in2_reg	<= A_in2;
		A_in3_reg	<= A_in3;
		
		A_out1_reg	<= A_out1;
		A_out2_reg	<= A_out2;
		A_out3_reg	<= A_out3;
		
	 end
	 
	 	 
	 RECTANGLEF_2order_8r F (
		 .clk(clk), 
		 .in1(in1), 
		 .in2(in2), 
		 .in3(in3), 
		 .r(r), 
		 .out1(A_in1), 
		 .out2(A_in2), 
		 .out3(A_in3)
    );

	 
	Affine #(.num(1)) InputAffine (
    .x1(A_in1_reg), 
    .x2(A_in2_reg), 
    .x3(A_in3_reg), 
    .y1(A_out1), 
    .y2(A_out2), 
    .y3(A_out3)
    );

	  RECTANGLEG_2order_NoFresh G (
		 .clk(clk), 
		 .in1(A_out1_reg), 
		 .in2(A_out2_reg), 
		 .in3(A_out3_reg), 
		 .out1(out1), 
		 .out2(out2), 
		 .out3(out3)
    );
	


endmodule
