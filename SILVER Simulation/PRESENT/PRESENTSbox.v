/*
* -----------------------------------------------------------------
* COMPANY : Shandong University
* AUTHOR  : Yanhong Fan,Chaoran Wang, Lixuan Wu,      Meiqin Wang
* DOCUMENT: "A Fast Search Method for 3-Share Second-Order Masking Schemes for Lightweight S-Boxes"  
* -----------------------------------------------------------------
*
* Copyright c 2023, Yanhong Fan,Chaoran Wang, Lixuan Wu,  Meiqin Wang
*
* All rights reserved.
* Please see LICENSE and README for license and further instructions.
*/

module PRESENTSbox ( clk, in1, in2, in3, r, out1, out2, out3 );
  (* SILVER="[3:0]_0" *) input [3:0] in1;
  (* SILVER="[3:0]_1" *) input [3:0] in2;
  (* SILVER="[3:0]_2" *) input [3:0] in3;
  (* SILVER="refresh" *) input [7:0] r;
  (* SILVER="[3:0]_0" *) output [3:0] out1;
  (* SILVER="[3:0]_1" *) output [3:0] out2;
  (* SILVER="[3:0]_2" *) output [3:0] out3;
  (* SILVER="clock" *) input clk;
  wire   F_in2_3_, F_in3_3_, G_N3, G_N2, n81, n82, n83, n84, n85, n86, n87,
         n88, n89, n90, n91, n92, n93, n94, n95, n96, n97, n98, n99, n100,
         n101, n102, n103, n104, n105, n106, n107, n108, n109, n110, n111,
         n112, n113, n114, n115, n116, n117, n118, n119, n120, n121, n122,
         n123, n124, n125, n126, n127, n128, n129, n130, n131, n132, n133,
         n134, n135, n136, n137, n138, n139, n140, n141, n142, n143, n144,
         n145, n146, n147, n148, n149, n150, n151, n152, n153, n154, n155,
         n156;
  wire   [3:0] Rq1;
  wire   [3:0] q1;
  wire   [3:0] Rq2;
  wire   [3:0] q2;
  wire   [3:0] Rq3;
  wire   [3:0] q3;
  wire   [3:0] F_in1_reg;
  wire   [3:0] F_in2_reg;
  wire   [3:0] F_in3_reg;
  wire   [35:0] F_CF_Reg;
  wire   [35:0] F_CF_Out;
  wire   [26:0] G_CF_Reg;
  wire   [26:0] G_CF_Out;

  DFF_X1 F_in1_reg_reg_3_ ( .D(n82), .CK(clk), .Q(F_in1_reg[3]), .QN(n143) );
  DFF_X1 F_in1_reg_reg_2_ ( .D(in1[1]), .CK(clk), .Q(F_in1_reg[2]) );
  DFF_X1 F_in1_reg_reg_1_ ( .D(in1[3]), .CK(clk), .Q(F_in1_reg[1]), .QN(n149)
         );
  DFF_X1 F_in1_reg_reg_0_ ( .D(in1[0]), .CK(clk), .Q(F_in1_reg[0]) );
  DFF_X1 F_in2_reg_reg_3_ ( .D(F_in2_3_), .CK(clk), .Q(F_in2_reg[3]), .QN(n145) );
  DFF_X1 F_in2_reg_reg_2_ ( .D(in2[1]), .CK(clk), .Q(F_in2_reg[2]) );
  DFF_X1 F_in2_reg_reg_1_ ( .D(in2[3]), .CK(clk), .Q(F_in2_reg[1]), .QN(n152)
         );
  DFF_X1 F_in2_reg_reg_0_ ( .D(in2[0]), .CK(clk), .Q(F_in2_reg[0]) );
  DFF_X1 F_in3_reg_reg_3_ ( .D(F_in3_3_), .CK(clk), .Q(F_in3_reg[3]), .QN(n150) );
  DFF_X1 F_in3_reg_reg_2_ ( .D(in3[1]), .CK(clk), .Q(F_in3_reg[2]) );
  DFF_X1 F_in3_reg_reg_1_ ( .D(in3[3]), .CK(clk), .Q(F_in3_reg[1]), .QN(n156)
         );
  DFF_X1 F_in3_reg_reg_0_ ( .D(in3[0]), .CK(clk), .Q(F_in3_reg[0]) );
  DFF_X1 F_CF_Reg_reg_0_ ( .D(F_CF_Out[0]), .CK(clk), .Q(F_CF_Reg[0]) );
  DFF_X1 Rq1_reg_0_ ( .D(q1[0]), .CK(clk), .Q(Rq1[0]) );
  DFF_X1 F_CF_Reg_reg_4_ ( .D(F_CF_Out[4]), .CK(clk), .Q(F_CF_Reg[4]) );
  DFF_X1 Rq2_reg_0_ ( .D(q2[0]), .CK(clk), .Q(Rq2[0]) );
  DFF_X1 F_CF_Reg_reg_8_ ( .D(F_CF_Out[8]), .CK(clk), .Q(F_CF_Reg[8]) );
  DFF_X1 Rq3_reg_0_ ( .D(q3[0]), .CK(clk), .Q(Rq3[0]) );
  DFF_X1 F_CF_Reg_reg_9_ ( .D(F_CF_Out[9]), .CK(clk), .Q(F_CF_Reg[9]) );
  DFF_X1 F_CF_Reg_reg_10_ ( .D(F_CF_Out[10]), .CK(clk), .Q(F_CF_Reg[10]) );
  DFF_X1 F_CF_Reg_reg_11_ ( .D(F_CF_Out[11]), .CK(clk), .Q(F_CF_Reg[11]) );
  DFF_X1 Rq1_reg_1_ ( .D(q1[1]), .CK(clk), .Q(Rq1[1]) );
  DFF_X1 F_CF_Reg_reg_12_ ( .D(F_CF_Out[12]), .CK(clk), .Q(F_CF_Reg[12]) );
  DFF_X1 F_CF_Reg_reg_13_ ( .D(F_CF_Out[13]), .CK(clk), .Q(F_CF_Reg[13]) );
  DFF_X1 F_CF_Reg_reg_14_ ( .D(F_CF_Out[14]), .CK(clk), .Q(F_CF_Reg[14]) );
  DFF_X1 Rq2_reg_1_ ( .D(q2[1]), .CK(clk), .Q(Rq2[1]), .QN(n151) );
  DFF_X1 F_CF_Reg_reg_15_ ( .D(F_CF_Out[15]), .CK(clk), .Q(F_CF_Reg[15]) );
  DFF_X1 F_CF_Reg_reg_16_ ( .D(F_CF_Out[16]), .CK(clk), .Q(F_CF_Reg[16]) );
  DFF_X1 F_CF_Reg_reg_17_ ( .D(F_CF_Out[17]), .CK(clk), .Q(F_CF_Reg[17]) );
  DFF_X1 Rq3_reg_1_ ( .D(q3[1]), .CK(clk), .Q(Rq3[1]), .QN(n144) );
  DFF_X1 F_CF_Reg_reg_18_ ( .D(F_CF_Out[18]), .CK(clk), .Q(F_CF_Reg[18]) );
  DFF_X1 F_CF_Reg_reg_19_ ( .D(F_CF_Out[19]), .CK(clk), .Q(F_CF_Reg[19]) );
  DFF_X1 Rq1_reg_2_ ( .D(q1[2]), .CK(clk), .Q(Rq1[2]), .QN(n147) );
  DFF_X1 F_CF_Reg_reg_21_ ( .D(F_CF_Out[21]), .CK(clk), .Q(F_CF_Reg[21]) );
  DFF_X1 Rq2_reg_2_ ( .D(q2[2]), .CK(clk), .Q(Rq2[2]), .QN(n146) );
  DFF_X1 F_CF_Reg_reg_24_ ( .D(F_CF_Out[24]), .CK(clk), .Q(F_CF_Reg[24]) );
  DFF_X1 F_CF_Reg_reg_25_ ( .D(F_CF_Out[25]), .CK(clk), .Q(F_CF_Reg[25]) );
  DFF_X1 F_CF_Reg_reg_26_ ( .D(F_CF_Out[26]), .CK(clk), .Q(F_CF_Reg[26]) );
  DFF_X1 Rq3_reg_2_ ( .D(q3[2]), .CK(clk), .Q(Rq3[2]), .QN(n153) );
  DFF_X1 F_CF_Reg_reg_27_ ( .D(F_CF_Out[27]), .CK(clk), .Q(F_CF_Reg[27]) );
  DFF_X1 F_CF_Reg_reg_28_ ( .D(F_CF_Out[28]), .CK(clk), .Q(F_CF_Reg[28]) );
  DFF_X1 F_CF_Reg_reg_29_ ( .D(F_CF_Out[29]), .CK(clk), .Q(F_CF_Reg[29]) );
  DFF_X1 Rq1_reg_3_ ( .D(q1[3]), .CK(clk), .Q(Rq1[3]), .QN(n148) );
  DFF_X1 F_CF_Reg_reg_30_ ( .D(F_CF_Out[30]), .CK(clk), .Q(F_CF_Reg[30]) );
  DFF_X1 F_CF_Reg_reg_31_ ( .D(F_CF_Out[31]), .CK(clk), .Q(F_CF_Reg[31]) );
  DFF_X1 F_CF_Reg_reg_32_ ( .D(F_CF_Out[32]), .CK(clk), .Q(F_CF_Reg[32]) );
  DFF_X1 Rq2_reg_3_ ( .D(q2[3]), .CK(clk), .Q(Rq2[3]), .QN(n155) );
  DFF_X1 F_CF_Reg_reg_33_ ( .D(F_CF_Out[33]), .CK(clk), .Q(F_CF_Reg[33]) );
  DFF_X1 F_CF_Reg_reg_34_ ( .D(F_CF_Out[34]), .CK(clk), .Q(F_CF_Reg[34]) );
  DFF_X1 F_CF_Reg_reg_35_ ( .D(F_CF_Out[35]), .CK(clk), .Q(F_CF_Reg[35]) );
  DFF_X1 Rq3_reg_3_ ( .D(q3[3]), .CK(clk), .Q(Rq3[3]), .QN(n154) );
  DFF_X1 G_out1_reg_0_ ( .D(n81), .CK(clk), .Q(out1[0]) );
  DFF_X1 G_CF_Reg_reg_0_ ( .D(G_CF_Out[0]), .CK(clk), .Q(G_CF_Reg[0]) );
  DFF_X1 G_CF_Reg_reg_2_ ( .D(G_CF_Out[2]), .CK(clk), .Q(G_CF_Reg[2]) );
  DFF_X1 G_CF_Reg_reg_5_ ( .D(G_CF_Out[5]), .CK(clk), .Q(G_CF_Reg[5]) );
  DFF_X1 G_CF_Reg_reg_6_ ( .D(G_CF_Out[6]), .CK(clk), .Q(G_CF_Reg[6]) );
  DFF_X1 G_CF_Reg_reg_9_ ( .D(G_CF_Out[9]), .CK(clk), .Q(G_CF_Reg[9]) );
  DFF_X1 G_CF_Reg_reg_10_ ( .D(G_CF_Out[10]), .CK(clk), .Q(G_CF_Reg[10]) );
  DFF_X1 G_CF_Reg_reg_11_ ( .D(G_CF_Out[11]), .CK(clk), .Q(G_CF_Reg[11]) );
  DFF_X1 G_CF_Reg_reg_12_ ( .D(G_CF_Out[12]), .CK(clk), .Q(G_CF_Reg[12]) );
  DFF_X1 G_CF_Reg_reg_13_ ( .D(G_CF_Out[13]), .CK(clk), .Q(G_CF_Reg[13]) );
  DFF_X1 G_CF_Reg_reg_14_ ( .D(G_CF_Out[14]), .CK(clk), .Q(G_CF_Reg[14]) );
  DFF_X1 G_CF_Reg_reg_15_ ( .D(G_CF_Out[15]), .CK(clk), .Q(G_CF_Reg[15]) );
  DFF_X1 G_CF_Reg_reg_16_ ( .D(G_CF_Out[16]), .CK(clk), .Q(G_CF_Reg[16]) );
  DFF_X1 G_CF_Reg_reg_17_ ( .D(G_CF_Out[17]), .CK(clk), .Q(G_CF_Reg[17]) );
  DFF_X1 G_CF_Reg_reg_18_ ( .D(G_CF_Out[18]), .CK(clk), .Q(G_CF_Reg[18]) );
  DFF_X1 G_CF_Reg_reg_19_ ( .D(G_CF_Out[19]), .CK(clk), .Q(G_CF_Reg[19]) );
  DFF_X1 G_CF_Reg_reg_20_ ( .D(G_CF_Out[20]), .CK(clk), .Q(G_CF_Reg[20]) );
  DFF_X1 G_CF_Reg_reg_21_ ( .D(G_CF_Out[21]), .CK(clk), .Q(G_CF_Reg[21]) );
  DFF_X1 G_CF_Reg_reg_22_ ( .D(G_CF_Out[22]), .CK(clk), .Q(G_CF_Reg[22]) );
  DFF_X1 G_CF_Reg_reg_23_ ( .D(G_CF_Out[23]), .CK(clk), .Q(G_CF_Reg[23]) );
  DFF_X1 G_CF_Reg_reg_24_ ( .D(G_CF_Out[24]), .CK(clk), .Q(G_CF_Reg[24]) );
  DFF_X1 G_CF_Reg_reg_25_ ( .D(G_CF_Out[25]), .CK(clk), .Q(G_CF_Reg[25]) );
  DFF_X1 G_CF_Reg_reg_26_ ( .D(G_CF_Out[26]), .CK(clk), .Q(G_CF_Reg[26]) );
  DFF_X1 G_out3_reg_0_ ( .D(G_N3), .CK(clk), .Q(out3[0]) );
  DFF_X1 G_out2_reg_0_ ( .D(G_N2), .CK(clk), .Q(out2[0]) );
  NAND2_X1 U159 ( .A1(F_in3_reg[3]), .A2(F_in2_reg[1]), .ZN(n114) );
  INV_X1 U160 ( .A(n114), .ZN(F_CF_Out[16]) );
  NAND2_X1 U161 ( .A1(F_in3_reg[1]), .A2(F_in2_reg[3]), .ZN(n122) );
  INV_X1 U162 ( .A(n122), .ZN(F_CF_Out[14]) );
  NAND2_X1 U163 ( .A1(Rq1[2]), .A2(Rq1[3]), .ZN(n83) );
  XNOR2_X1 U164 ( .A(Rq1[1]), .B(n83), .ZN(G_CF_Out[0]) );
  INV_X1 U165 ( .A(G_CF_Out[0]), .ZN(G_CF_Out[18]) );
  NAND2_X1 U166 ( .A1(F_in2_reg[1]), .A2(n143), .ZN(n117) );
  XNOR2_X1 U167 ( .A(F_in2_reg[2]), .B(n117), .ZN(F_CF_Out[10]) );
  NAND2_X1 U168 ( .A1(F_in1_reg[3]), .A2(F_in2_reg[2]), .ZN(n116) );
  AND2_X1 U169 ( .A1(F_CF_Out[10]), .A2(n116), .ZN(F_CF_Out[19]) );
  XOR2_X1 U170 ( .A(in3[2]), .B(in3[1]), .Z(F_in3_3_) );
  XOR2_X1 U171 ( .A(in2[2]), .B(in2[1]), .Z(F_in2_3_) );
  XOR2_X1 U172 ( .A(r[3]), .B(r[2]), .Z(n85) );
  XNOR2_X1 U173 ( .A(F_CF_Reg[34]), .B(F_CF_Reg[35]), .ZN(n84) );
  XNOR2_X1 U174 ( .A(n85), .B(n84), .ZN(n86) );
  XOR2_X1 U175 ( .A(F_CF_Reg[33]), .B(n86), .Z(q3[3]) );
  XNOR2_X1 U176 ( .A(r[3]), .B(F_CF_Reg[30]), .ZN(n87) );
  XOR2_X1 U177 ( .A(F_CF_Reg[32]), .B(F_CF_Reg[31]), .Z(n93) );
  XNOR2_X1 U178 ( .A(n87), .B(n93), .ZN(q2[3]) );
  XOR2_X1 U179 ( .A(F_CF_Reg[28]), .B(F_CF_Reg[27]), .Z(n89) );
  XNOR2_X1 U180 ( .A(r[2]), .B(F_CF_Reg[29]), .ZN(n88) );
  XNOR2_X1 U181 ( .A(n89), .B(n88), .ZN(q1[3]) );
  XOR2_X1 U182 ( .A(r[1]), .B(r[0]), .Z(n91) );
  XNOR2_X1 U183 ( .A(F_CF_Reg[25]), .B(F_CF_Reg[26]), .ZN(n90) );
  XNOR2_X1 U184 ( .A(n91), .B(n90), .ZN(n92) );
  XOR2_X1 U185 ( .A(F_CF_Reg[24]), .B(n92), .Z(q3[2]) );
  XNOR2_X1 U186 ( .A(r[1]), .B(n93), .ZN(n94) );
  XNOR2_X1 U187 ( .A(n94), .B(F_CF_Reg[21]), .ZN(q2[2]) );
  XOR2_X1 U188 ( .A(F_CF_Reg[19]), .B(F_CF_Reg[18]), .Z(n96) );
  XNOR2_X1 U189 ( .A(r[0]), .B(F_CF_Reg[29]), .ZN(n95) );
  XNOR2_X1 U190 ( .A(n96), .B(n95), .ZN(q1[2]) );
  XOR2_X1 U191 ( .A(F_CF_Reg[17]), .B(r[7]), .Z(n98) );
  XOR2_X1 U192 ( .A(F_CF_Reg[15]), .B(F_CF_Reg[16]), .Z(n101) );
  XNOR2_X1 U193 ( .A(n101), .B(r[6]), .ZN(n97) );
  XNOR2_X1 U194 ( .A(n98), .B(n97), .ZN(q3[1]) );
  XOR2_X1 U195 ( .A(F_CF_Reg[14]), .B(F_CF_Reg[12]), .Z(n104) );
  XNOR2_X1 U196 ( .A(r[7]), .B(n104), .ZN(n99) );
  XNOR2_X1 U197 ( .A(n99), .B(F_CF_Reg[13]), .ZN(q2[1]) );
  XNOR2_X1 U198 ( .A(r[6]), .B(F_CF_Reg[9]), .ZN(n100) );
  XOR2_X1 U199 ( .A(F_CF_Reg[11]), .B(F_CF_Reg[10]), .Z(n106) );
  XNOR2_X1 U200 ( .A(n100), .B(n106), .ZN(q1[1]) );
  XOR2_X1 U201 ( .A(F_CF_Reg[8]), .B(r[5]), .Z(n103) );
  XNOR2_X1 U202 ( .A(n101), .B(r[4]), .ZN(n102) );
  XNOR2_X1 U203 ( .A(n103), .B(n102), .ZN(q3[0]) );
  XNOR2_X1 U204 ( .A(r[5]), .B(n104), .ZN(n105) );
  XNOR2_X1 U205 ( .A(n105), .B(F_CF_Reg[4]), .ZN(q2[0]) );
  XNOR2_X1 U206 ( .A(r[4]), .B(n106), .ZN(n107) );
  XNOR2_X1 U207 ( .A(n107), .B(F_CF_Reg[0]), .ZN(q1[0]) );
  XOR2_X1 U208 ( .A(Rq3[0]), .B(Rq3[3]), .Z(G_N3) );
  XOR2_X1 U209 ( .A(Rq2[0]), .B(Rq2[3]), .Z(G_N2) );
  NAND2_X1 U210 ( .A1(n143), .A2(n149), .ZN(F_CF_Out[0]) );
  NAND2_X1 U211 ( .A1(n152), .A2(n145), .ZN(F_CF_Out[4]) );
  NOR2_X1 U212 ( .A1(F_in3_reg[1]), .A2(n150), .ZN(n108) );
  XOR2_X1 U213 ( .A(F_in3_reg[2]), .B(n108), .Z(F_CF_Out[8]) );
  NOR2_X1 U214 ( .A1(F_in1_reg[3]), .A2(n149), .ZN(F_CF_Out[9]) );
  NOR2_X1 U215 ( .A1(n143), .A2(n156), .ZN(F_CF_Out[11]) );
  NAND2_X1 U216 ( .A1(F_in2_reg[3]), .A2(F_in1_reg[1]), .ZN(n109) );
  XNOR2_X1 U217 ( .A(n109), .B(F_in1_reg[2]), .ZN(F_CF_Out[12]) );
  NOR2_X1 U218 ( .A1(F_in2_reg[3]), .A2(n152), .ZN(F_CF_Out[13]) );
  NOR2_X1 U219 ( .A1(F_in3_reg[3]), .A2(n149), .ZN(F_CF_Out[15]) );
  NAND2_X1 U220 ( .A1(F_in3_reg[1]), .A2(F_in3_reg[3]), .ZN(n110) );
  XNOR2_X1 U221 ( .A(n110), .B(F_in3_reg[2]), .ZN(F_CF_Out[17]) );
  NAND2_X1 U222 ( .A1(F_in1_reg[3]), .A2(F_in1_reg[1]), .ZN(n112) );
  NAND2_X1 U223 ( .A1(F_in1_reg[2]), .A2(n143), .ZN(n111) );
  NAND2_X1 U224 ( .A1(n112), .A2(n111), .ZN(F_CF_Out[18]) );
  XOR2_X1 U225 ( .A(n149), .B(F_in1_reg[2]), .Z(n124) );
  NOR2_X1 U226 ( .A1(F_in2_reg[3]), .A2(n124), .ZN(F_CF_Out[21]) );
  NAND2_X1 U227 ( .A1(F_in2_reg[2]), .A2(n150), .ZN(n113) );
  NAND2_X1 U228 ( .A1(n114), .A2(n113), .ZN(F_CF_Out[25]) );
  OR2_X1 U229 ( .A1(n143), .A2(n124), .ZN(n115) );
  XNOR2_X1 U230 ( .A(F_in1_reg[0]), .B(n115), .ZN(F_CF_Out[27]) );
  NAND2_X1 U231 ( .A1(n117), .A2(n116), .ZN(n118) );
  XOR2_X1 U232 ( .A(F_in2_reg[0]), .B(n118), .Z(F_CF_Out[28]) );
  XOR2_X1 U233 ( .A(n156), .B(F_in3_reg[2]), .Z(n142) );
  NOR2_X1 U234 ( .A1(n143), .A2(n142), .ZN(F_CF_Out[29]) );
  NAND2_X1 U235 ( .A1(F_in1_reg[1]), .A2(n145), .ZN(n120) );
  NAND2_X1 U236 ( .A1(F_in1_reg[2]), .A2(F_in2_reg[3]), .ZN(n119) );
  NAND2_X1 U237 ( .A1(n120), .A2(n119), .ZN(n121) );
  XOR2_X1 U238 ( .A(F_in1_reg[0]), .B(n121), .Z(F_CF_Out[30]) );
  XOR2_X1 U239 ( .A(F_in2_reg[2]), .B(n152), .Z(n125) );
  NOR2_X1 U240 ( .A1(n145), .A2(n125), .ZN(F_CF_Out[31]) );
  NAND2_X1 U241 ( .A1(F_in3_reg[2]), .A2(n145), .ZN(n123) );
  NAND2_X1 U242 ( .A1(n123), .A2(n122), .ZN(F_CF_Out[32]) );
  NOR2_X1 U243 ( .A1(n124), .A2(n150), .ZN(F_CF_Out[24]) );
  XOR2_X1 U244 ( .A(F_in1_reg[0]), .B(F_CF_Out[24]), .Z(F_CF_Out[33]) );
  NOR2_X1 U245 ( .A1(n150), .A2(n125), .ZN(F_CF_Out[34]) );
  NOR2_X1 U246 ( .A1(n148), .A2(n153), .ZN(G_CF_Out[2]) );
  NAND2_X1 U247 ( .A1(Rq2[3]), .A2(Rq3[2]), .ZN(n126) );
  XOR2_X1 U248 ( .A(n126), .B(n144), .Z(G_CF_Out[5]) );
  NOR2_X1 U249 ( .A1(n154), .A2(n147), .ZN(G_CF_Out[6]) );
  NAND2_X1 U250 ( .A1(Rq1[1]), .A2(Rq1[3]), .ZN(n127) );
  XNOR2_X1 U251 ( .A(n127), .B(Rq1[0]), .ZN(G_CF_Out[9]) );
  NAND2_X1 U252 ( .A1(Rq2[1]), .A2(Rq1[3]), .ZN(n128) );
  XOR2_X1 U253 ( .A(n128), .B(n146), .Z(G_CF_Out[10]) );
  NOR2_X1 U254 ( .A1(Rq1[3]), .A2(n144), .ZN(G_CF_Out[11]) );
  NAND2_X1 U255 ( .A1(Rq2[3]), .A2(Rq1[1]), .ZN(n129) );
  XOR2_X1 U256 ( .A(n129), .B(n147), .Z(G_CF_Out[12]) );
  NOR2_X1 U257 ( .A1(Rq2[3]), .A2(n151), .ZN(n130) );
  XOR2_X1 U258 ( .A(Rq2[0]), .B(n130), .Z(G_CF_Out[13]) );
  NOR2_X1 U259 ( .A1(n144), .A2(n155), .ZN(G_CF_Out[14]) );
  AND2_X1 U260 ( .A1(Rq3[3]), .A2(Rq1[1]), .ZN(G_CF_Out[15]) );
  NOR2_X1 U261 ( .A1(Rq3[3]), .A2(n151), .ZN(G_CF_Out[16]) );
  XNOR2_X1 U262 ( .A(n153), .B(Rq3[0]), .ZN(n132) );
  NAND2_X1 U263 ( .A1(Rq3[1]), .A2(n154), .ZN(n131) );
  XNOR2_X1 U264 ( .A(n132), .B(n131), .ZN(G_CF_Out[17]) );
  NOR2_X1 U265 ( .A1(Rq1[3]), .A2(n146), .ZN(G_CF_Out[19]) );
  NOR2_X1 U266 ( .A1(Rq3[2]), .A2(n148), .ZN(G_CF_Out[20]) );
  NOR2_X1 U267 ( .A1(Rq2[3]), .A2(n147), .ZN(G_CF_Out[21]) );
  NOR2_X1 U268 ( .A1(n146), .A2(n155), .ZN(G_CF_Out[22]) );
  NOR2_X1 U269 ( .A1(Rq3[2]), .A2(n155), .ZN(n133) );
  XNOR2_X1 U270 ( .A(n144), .B(n133), .ZN(G_CF_Out[23]) );
  NOR2_X1 U271 ( .A1(Rq1[2]), .A2(n154), .ZN(G_CF_Out[24]) );
  NAND2_X1 U272 ( .A1(Rq3[3]), .A2(Rq2[2]), .ZN(n134) );
  XOR2_X1 U273 ( .A(n134), .B(n151), .Z(G_CF_Out[25]) );
  NOR2_X1 U274 ( .A1(Rq3[3]), .A2(n153), .ZN(G_CF_Out[26]) );
  XNOR2_X1 U275 ( .A(G_CF_Reg[25]), .B(G_CF_Reg[26]), .ZN(n139) );
  XNOR2_X1 U276 ( .A(G_CF_Reg[24]), .B(n139), .ZN(out3[3]) );
  XNOR2_X1 U277 ( .A(G_CF_Reg[22]), .B(G_CF_Reg[21]), .ZN(n140) );
  XNOR2_X1 U278 ( .A(G_CF_Reg[23]), .B(n140), .ZN(out2[3]) );
  XNOR2_X1 U279 ( .A(G_CF_Reg[19]), .B(G_CF_Reg[20]), .ZN(n135) );
  XNOR2_X1 U280 ( .A(n135), .B(G_CF_Reg[18]), .ZN(out1[3]) );
  XNOR2_X1 U281 ( .A(G_CF_Reg[17]), .B(G_CF_Reg[16]), .ZN(n136) );
  XNOR2_X1 U282 ( .A(n136), .B(G_CF_Reg[15]), .ZN(out3[2]) );
  XNOR2_X1 U283 ( .A(G_CF_Reg[14]), .B(G_CF_Reg[13]), .ZN(n137) );
  XNOR2_X1 U284 ( .A(n137), .B(G_CF_Reg[12]), .ZN(out2[2]) );
  XNOR2_X1 U285 ( .A(G_CF_Reg[11]), .B(G_CF_Reg[10]), .ZN(n138) );
  XNOR2_X1 U286 ( .A(n138), .B(G_CF_Reg[9]), .ZN(out1[2]) );
  XNOR2_X1 U287 ( .A(G_CF_Reg[6]), .B(n139), .ZN(out3[1]) );
  XNOR2_X1 U288 ( .A(G_CF_Reg[5]), .B(n140), .ZN(out2[1]) );
  XNOR2_X1 U289 ( .A(G_CF_Reg[19]), .B(G_CF_Reg[0]), .ZN(n141) );
  XNOR2_X1 U290 ( .A(n141), .B(G_CF_Reg[2]), .ZN(out1[1]) );
  NOR2_X1 U291 ( .A1(F_in3_reg[3]), .A2(n142), .ZN(F_CF_Out[26]) );
  XOR2_X1 U292 ( .A(F_in3_reg[0]), .B(F_CF_Out[26]), .Z(F_CF_Out[35]) );
  XNOR2_X1 U293 ( .A(in1[2]), .B(in1[1]), .ZN(n82) );
  XOR2_X1 U294 ( .A(n148), .B(Rq1[0]), .Z(n81) );
endmodule

