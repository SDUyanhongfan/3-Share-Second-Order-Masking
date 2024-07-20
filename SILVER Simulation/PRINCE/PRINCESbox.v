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


module PRINCESbox ( clk, in1, in2, in3, r, out1, out2, out3 );
  (* SILVER="[3:0]_0" *) input [3:0] in1;
  (* SILVER="[3:0]_1" *) input [3:0] in2;
  (* SILVER="[3:0]_2" *) input [3:0] in3;
  (* SILVER="refresh" *) input [15:0] r;
  (* SILVER="[3:0]_0" *) output [3:0] out1;
  (* SILVER="[3:0]_1" *) output [3:0] out2;
  (* SILVER="[3:0]_2" *) output [3:0] out3;
  (* SILVER="clock" *) input clk;
  wire   F_in1_3_, F_in2_3_, F_in3_3_, F_N5, F_N4, F_N3, F_N2, F_N1, F_N0,
         G_N5, G_N4, G_N3, G_N2, G_N1, G_N0, n113, n114, n115, n116, n117,
         n118, n119, n120, n121, n122, n123, n124, n125, n126, n127, n128,
         n129, n130, n131, n132, n133, n134, n135, n136, n137, n138, n139,
         n140, n141, n142, n143, n144, n145, n146, n147, n148, n149, n150,
         n151, n152, n153, n154, n155, n156, n157, n158, n159, n160, n161,
         n162, n163, n164, n165, n166, n167, n168, n169, n170, n171, n172,
         n173, n174, n175, n176, n177, n178, n179, n180, n181, n182, n183,
         n184, n185, n186, n187, n188, n189, n190, n191, n192, n193, n194,
         n195, n196, n197, n198, n199, n200, n201, n202, n203, n204, n205,
         n206, n207, n208, n209, n210, n211, n212, n213, n214, n215, n216,
         n217, n218, n219, n220, n221, n222, n223;
  wire   [3:0] Rq1;
  wire   [3:0] q1;
  wire   [3:0] Rq2;
  wire   [3:0] q2;
  wire   [3:0] Rq3;
  wire   [3:0] q3;
  wire   [3:0] F_in1_reg;
  wire   [3:0] F_in2_reg;
  wire   [3:0] F_in3_reg;
  wire   [3:0] G_out1_reg;
  wire   [3:0] G_out1;
  wire   [3:0] G_out2_reg;
  wire   [3:0] G_out2;
  wire   [3:0] G_out3_reg;
  wire   [3:0] G_out3;
  wire   [3:0] H_out1;
  wire   [3:0] H_out2;
  wire   [3:0] H_out3;
  wire   [17:0] F_CF_Reg;
  wire   [17:0] F_CF_Out;
  wire   [17:0] G_CF_Reg;
  wire   [17:0] G_CF_Out;
  wire   [26:0] H_CF_Reg;
  wire   [26:0] H_CF_Out;

  DFF_X1 F_in1_reg_reg_3_ ( .D(F_in1_3_), .CK(clk), .Q(F_in1_reg[3]), .QN(n208) );
  DFF_X1 F_in1_reg_reg_2_ ( .D(in1[2]), .CK(clk), .Q(F_in1_reg[2]), .QN(n216)
         );
  DFF_X1 F_in1_reg_reg_1_ ( .D(in1[0]), .CK(clk), .Q(F_in1_reg[1]), .QN(n219)
         );
  DFF_X1 F_in1_reg_reg_0_ ( .D(in1[1]), .CK(clk), .Q(F_in1_reg[0]) );
  DFF_X1 F_in2_reg_reg_3_ ( .D(F_in2_3_), .CK(clk), .Q(F_in2_reg[3]), .QN(n207) );
  DFF_X1 F_in2_reg_reg_2_ ( .D(in2[2]), .CK(clk), .Q(F_in2_reg[2]), .QN(n217)
         );
  DFF_X1 F_in2_reg_reg_1_ ( .D(in2[0]), .CK(clk), .Q(F_in2_reg[1]), .QN(n221)
         );
  DFF_X1 F_in2_reg_reg_0_ ( .D(in2[1]), .CK(clk), .Q(F_in2_reg[0]) );
  DFF_X1 F_in3_reg_reg_3_ ( .D(F_in3_3_), .CK(clk), .Q(F_in3_reg[3]), .QN(n209) );
  DFF_X1 F_in3_reg_reg_2_ ( .D(in3[2]), .CK(clk), .Q(F_in3_reg[2]), .QN(n220)
         );
  DFF_X1 F_in3_reg_reg_1_ ( .D(in3[0]), .CK(clk), .Q(F_in3_reg[1]), .QN(n218)
         );
  DFF_X1 F_in3_reg_reg_0_ ( .D(in3[1]), .CK(clk), .Q(F_in3_reg[0]) );
  DFF_X1 F_CF_Reg_reg_0_ ( .D(F_CF_Out[0]), .CK(clk), .Q(F_CF_Reg[0]) );
  DFF_X1 F_CF_Reg_reg_1_ ( .D(F_CF_Out[1]), .CK(clk), .Q(F_CF_Reg[1]) );
  DFF_X1 F_CF_Reg_reg_2_ ( .D(F_CF_Out[2]), .CK(clk), .Q(F_CF_Reg[2]) );
  DFF_X1 Rq1_reg_2_ ( .D(q1[2]), .CK(clk), .Q(Rq1[2]), .QN(n204) );
  DFF_X1 F_CF_Reg_reg_3_ ( .D(F_CF_Out[3]), .CK(clk), .Q(F_CF_Reg[3]) );
  DFF_X1 F_CF_Reg_reg_4_ ( .D(F_CF_Out[4]), .CK(clk), .Q(F_CF_Reg[4]) );
  DFF_X1 F_CF_Reg_reg_5_ ( .D(F_CF_Out[5]), .CK(clk), .Q(F_CF_Reg[5]) );
  DFF_X1 Rq2_reg_2_ ( .D(q2[2]), .CK(clk), .Q(Rq2[2]), .QN(n211) );
  DFF_X1 F_CF_Reg_reg_6_ ( .D(F_CF_Out[6]), .CK(clk), .Q(F_CF_Reg[6]) );
  DFF_X1 F_CF_Reg_reg_7_ ( .D(F_CF_Out[7]), .CK(clk), .Q(F_CF_Reg[7]) );
  DFF_X1 F_CF_Reg_reg_8_ ( .D(F_CF_Out[8]), .CK(clk), .Q(F_CF_Reg[8]) );
  DFF_X1 Rq3_reg_2_ ( .D(q3[2]), .CK(clk), .Q(Rq3[2]), .QN(n215) );
  DFF_X1 F_CF_Reg_reg_9_ ( .D(F_CF_Out[9]), .CK(clk), .Q(F_CF_Reg[9]) );
  DFF_X1 F_CF_Reg_reg_10_ ( .D(F_CF_Out[10]), .CK(clk), .Q(F_CF_Reg[10]) );
  DFF_X1 F_CF_Reg_reg_11_ ( .D(F_CF_Out[11]), .CK(clk), .Q(F_CF_Reg[11]) );
  DFF_X1 Rq1_reg_3_ ( .D(q1[3]), .CK(clk), .Q(Rq1[3]), .QN(n206) );
  DFF_X1 F_CF_Reg_reg_12_ ( .D(F_CF_Out[12]), .CK(clk), .Q(F_CF_Reg[12]) );
  DFF_X1 F_CF_Reg_reg_13_ ( .D(F_CF_Out[13]), .CK(clk), .Q(F_CF_Reg[13]) );
  DFF_X1 F_CF_Reg_reg_14_ ( .D(F_CF_Out[14]), .CK(clk), .Q(F_CF_Reg[14]) );
  DFF_X1 Rq2_reg_3_ ( .D(q2[3]), .CK(clk), .Q(Rq2[3]), .QN(n212) );
  DFF_X1 F_CF_Reg_reg_15_ ( .D(F_CF_Out[15]), .CK(clk), .Q(F_CF_Reg[15]) );
  DFF_X1 F_CF_Reg_reg_16_ ( .D(F_CF_Out[16]), .CK(clk), .Q(F_CF_Reg[16]) );
  DFF_X1 F_CF_Reg_reg_17_ ( .D(F_CF_Out[17]), .CK(clk), .Q(F_CF_Reg[17]) );
  DFF_X1 Rq3_reg_3_ ( .D(q3[3]), .CK(clk), .Q(Rq3[3]), .QN(n213) );
  DFF_X1 F_out2_reg_0_ ( .D(F_N4), .CK(clk), .Q(q2[0]) );
  DFF_X1 Rq2_reg_0_ ( .D(q2[0]), .CK(clk), .Q(Rq2[0]) );
  DFF_X1 F_out2_reg_1_ ( .D(F_N1), .CK(clk), .Q(q2[1]) );
  DFF_X1 Rq2_reg_1_ ( .D(q2[1]), .CK(clk), .Q(Rq2[1]) );
  DFF_X1 F_out3_reg_0_ ( .D(F_N5), .CK(clk), .Q(q3[0]) );
  DFF_X1 Rq3_reg_0_ ( .D(q3[0]), .CK(clk), .Q(Rq3[0]) );
  DFF_X1 F_out3_reg_1_ ( .D(F_N2), .CK(clk), .Q(q3[1]) );
  DFF_X1 Rq3_reg_1_ ( .D(q3[1]), .CK(clk), .Q(Rq3[1]) );
  DFF_X1 F_out1_reg_0_ ( .D(F_N3), .CK(clk), .Q(q1[0]) );
  DFF_X1 Rq1_reg_0_ ( .D(q1[0]), .CK(clk), .Q(Rq1[0]) );
  DFF_X1 F_out1_reg_1_ ( .D(F_N0), .CK(clk), .Q(q1[1]) );
  DFF_X1 Rq1_reg_1_ ( .D(q1[1]), .CK(clk), .Q(Rq1[1]) );
  DFF_X1 G_out2_reg_0_ ( .D(G_N1), .CK(clk), .Q(G_out2[0]) );
  DFF_X1 G_out2_reg_reg_0_ ( .D(G_out2[0]), .CK(clk), .Q(G_out2_reg[0]) );
  DFF_X1 G_out2_reg_1_ ( .D(G_N4), .CK(clk), .Q(G_out2[1]) );
  DFF_X1 G_out2_reg_reg_1_ ( .D(G_out2[1]), .CK(clk), .Q(G_out2_reg[1]), .QN(
        n222) );
  DFF_X1 G_out3_reg_0_ ( .D(G_N2), .CK(clk), .Q(G_out3[0]) );
  DFF_X1 G_out3_reg_reg_0_ ( .D(G_out3[0]), .CK(clk), .Q(G_out3_reg[0]) );
  DFF_X1 G_out3_reg_1_ ( .D(G_N5), .CK(clk), .Q(G_out3[1]) );
  DFF_X1 G_out3_reg_reg_1_ ( .D(G_out3[1]), .CK(clk), .Q(G_out3_reg[1]) );
  DFF_X1 G_out1_reg_0_ ( .D(G_N0), .CK(clk), .Q(G_out1[0]) );
  DFF_X1 G_out1_reg_reg_0_ ( .D(G_out1[0]), .CK(clk), .Q(G_out1_reg[0]) );
  DFF_X1 G_out1_reg_1_ ( .D(G_N3), .CK(clk), .Q(G_out1[1]) );
  DFF_X1 G_out1_reg_reg_1_ ( .D(G_out1[1]), .CK(clk), .Q(G_out1_reg[1]), .QN(
        n202) );
  DFF_X1 G_CF_Reg_reg_0_ ( .D(G_CF_Out[0]), .CK(clk), .Q(G_CF_Reg[0]) );
  DFF_X1 G_CF_Reg_reg_1_ ( .D(G_CF_Out[1]), .CK(clk), .Q(G_CF_Reg[1]) );
  DFF_X1 G_CF_Reg_reg_2_ ( .D(G_CF_Out[2]), .CK(clk), .Q(G_CF_Reg[2]) );
  DFF_X1 G_out1_reg_reg_2_ ( .D(G_out1[2]), .CK(clk), .Q(G_out1_reg[2]), .QN(
        n205) );
  DFF_X1 G_CF_Reg_reg_3_ ( .D(G_CF_Out[3]), .CK(clk), .Q(G_CF_Reg[3]) );
  DFF_X1 G_CF_Reg_reg_4_ ( .D(G_CF_Out[4]), .CK(clk), .Q(G_CF_Reg[4]) );
  DFF_X1 G_CF_Reg_reg_5_ ( .D(G_CF_Out[5]), .CK(clk), .Q(G_CF_Reg[5]) );
  DFF_X1 G_out2_reg_reg_2_ ( .D(G_out2[2]), .CK(clk), .Q(G_out2_reg[2]) );
  DFF_X1 G_CF_Reg_reg_6_ ( .D(G_CF_Out[6]), .CK(clk), .Q(G_CF_Reg[6]) );
  DFF_X1 G_CF_Reg_reg_7_ ( .D(G_CF_Out[7]), .CK(clk), .Q(G_CF_Reg[7]) );
  DFF_X1 G_CF_Reg_reg_8_ ( .D(G_CF_Out[8]), .CK(clk), .Q(G_CF_Reg[8]) );
  DFF_X1 G_out3_reg_reg_2_ ( .D(G_out3[2]), .CK(clk), .Q(G_out3_reg[2]), .QN(
        n203) );
  DFF_X1 G_CF_Reg_reg_9_ ( .D(G_CF_Out[9]), .CK(clk), .Q(G_CF_Reg[9]) );
  DFF_X1 G_CF_Reg_reg_10_ ( .D(G_CF_Out[10]), .CK(clk), .Q(G_CF_Reg[10]) );
  DFF_X1 G_CF_Reg_reg_11_ ( .D(G_CF_Out[11]), .CK(clk), .Q(G_CF_Reg[11]) );
  DFF_X1 G_out1_reg_reg_3_ ( .D(G_out1[3]), .CK(clk), .Q(G_out1_reg[3]), .QN(
        n223) );
  DFF_X1 G_CF_Reg_reg_12_ ( .D(G_CF_Out[12]), .CK(clk), .Q(G_CF_Reg[12]) );
  DFF_X1 G_CF_Reg_reg_13_ ( .D(G_CF_Out[13]), .CK(clk), .Q(G_CF_Reg[13]) );
  DFF_X1 G_CF_Reg_reg_14_ ( .D(G_CF_Out[14]), .CK(clk), .Q(G_CF_Reg[14]) );
  DFF_X1 G_out2_reg_reg_3_ ( .D(G_out2[3]), .CK(clk), .Q(G_out2_reg[3]), .QN(
        n210) );
  DFF_X1 G_CF_Reg_reg_15_ ( .D(G_CF_Out[15]), .CK(clk), .Q(G_CF_Reg[15]) );
  DFF_X1 G_CF_Reg_reg_16_ ( .D(G_CF_Out[16]), .CK(clk), .Q(G_CF_Reg[16]) );
  DFF_X1 G_CF_Reg_reg_17_ ( .D(G_CF_Out[17]), .CK(clk), .Q(G_CF_Reg[17]) );
  DFF_X1 G_out3_reg_reg_3_ ( .D(G_out3[3]), .CK(clk), .Q(G_out3_reg[3]), .QN(
        n214) );
  DFF_X1 H_out3_reg_3_ ( .D(G_out3_reg[2]), .CK(clk), .Q(H_out3[3]) );
  DFF_X1 out3_reg_3_ ( .D(H_out3[3]), .CK(clk), .Q(out3[3]) );
  DFF_X1 H_out2_reg_3_ ( .D(G_out2_reg[2]), .CK(clk), .Q(H_out2[3]) );
  DFF_X1 out2_reg_3_ ( .D(H_out2[3]), .CK(clk), .Q(out2[3]) );
  DFF_X1 H_out1_reg_3_ ( .D(G_out1_reg[2]), .CK(clk), .Q(H_out1[3]) );
  DFF_X1 out1_reg_3_ ( .D(H_out1[3]), .CK(clk), .Q(out1[3]) );
  DFF_X1 H_CF_Reg_reg_0_ ( .D(H_CF_Out[0]), .CK(clk), .Q(H_CF_Reg[0]) );
  DFF_X1 H_CF_Reg_reg_1_ ( .D(H_CF_Out[1]), .CK(clk), .Q(H_CF_Reg[1]) );
  DFF_X1 H_CF_Reg_reg_2_ ( .D(H_CF_Out[2]), .CK(clk), .Q(H_CF_Reg[2]) );
  DFF_X1 out1_reg_0_ ( .D(H_out1[0]), .CK(clk), .Q(out1[0]) );
  DFF_X1 H_CF_Reg_reg_3_ ( .D(H_CF_Out[3]), .CK(clk), .Q(H_CF_Reg[3]) );
  DFF_X1 H_CF_Reg_reg_4_ ( .D(H_CF_Out[4]), .CK(clk), .Q(H_CF_Reg[4]) );
  DFF_X1 H_CF_Reg_reg_5_ ( .D(H_CF_Out[5]), .CK(clk), .Q(H_CF_Reg[5]) );
  DFF_X1 out2_reg_0_ ( .D(H_out2[0]), .CK(clk), .Q(out2[0]) );
  DFF_X1 H_CF_Reg_reg_6_ ( .D(H_CF_Out[6]), .CK(clk), .Q(H_CF_Reg[6]) );
  DFF_X1 H_CF_Reg_reg_7_ ( .D(H_CF_Out[7]), .CK(clk), .Q(H_CF_Reg[7]) );
  DFF_X1 H_CF_Reg_reg_8_ ( .D(H_CF_Out[8]), .CK(clk), .Q(H_CF_Reg[8]) );
  DFF_X1 out3_reg_0_ ( .D(H_out3[0]), .CK(clk), .Q(out3[0]) );
  DFF_X1 H_CF_Reg_reg_9_ ( .D(H_CF_Out[9]), .CK(clk), .Q(H_CF_Reg[9]) );
  DFF_X1 H_CF_Reg_reg_10_ ( .D(H_CF_Out[10]), .CK(clk), .Q(H_CF_Reg[10]) );
  DFF_X1 H_CF_Reg_reg_11_ ( .D(H_CF_Out[11]), .CK(clk), .Q(H_CF_Reg[11]) );
  DFF_X1 out1_reg_1_ ( .D(H_out1[1]), .CK(clk), .Q(out1[1]) );
  DFF_X1 H_CF_Reg_reg_12_ ( .D(H_CF_Out[12]), .CK(clk), .Q(H_CF_Reg[12]) );
  DFF_X1 H_CF_Reg_reg_13_ ( .D(H_CF_Out[13]), .CK(clk), .Q(H_CF_Reg[13]) );
  DFF_X1 H_CF_Reg_reg_14_ ( .D(H_CF_Out[14]), .CK(clk), .Q(H_CF_Reg[14]) );
  DFF_X1 out2_reg_1_ ( .D(H_out2[1]), .CK(clk), .Q(out2[1]) );
  DFF_X1 H_CF_Reg_reg_15_ ( .D(H_CF_Out[15]), .CK(clk), .Q(H_CF_Reg[15]) );
  DFF_X1 H_CF_Reg_reg_16_ ( .D(H_CF_Out[16]), .CK(clk), .Q(H_CF_Reg[16]) );
  DFF_X1 H_CF_Reg_reg_17_ ( .D(H_CF_Out[17]), .CK(clk), .Q(H_CF_Reg[17]) );
  DFF_X1 out3_reg_1_ ( .D(H_out3[1]), .CK(clk), .Q(out3[1]) );
  DFF_X1 H_CF_Reg_reg_18_ ( .D(H_CF_Out[18]), .CK(clk), .Q(H_CF_Reg[18]) );
  DFF_X1 H_CF_Reg_reg_19_ ( .D(H_CF_Out[19]), .CK(clk), .Q(H_CF_Reg[19]) );
  DFF_X1 H_CF_Reg_reg_20_ ( .D(H_CF_Out[20]), .CK(clk), .Q(H_CF_Reg[20]) );
  DFF_X1 out1_reg_2_ ( .D(H_out1[2]), .CK(clk), .Q(out1[2]) );
  DFF_X1 H_CF_Reg_reg_21_ ( .D(H_CF_Out[21]), .CK(clk), .Q(H_CF_Reg[21]) );
  DFF_X1 H_CF_Reg_reg_22_ ( .D(H_CF_Out[22]), .CK(clk), .Q(H_CF_Reg[22]) );
  DFF_X1 H_CF_Reg_reg_23_ ( .D(H_CF_Out[23]), .CK(clk), .Q(H_CF_Reg[23]) );
  DFF_X1 out2_reg_2_ ( .D(H_out2[2]), .CK(clk), .Q(out2[2]) );
  DFF_X1 H_CF_Reg_reg_24_ ( .D(H_CF_Out[24]), .CK(clk), .Q(H_CF_Reg[24]) );
  DFF_X1 H_CF_Reg_reg_25_ ( .D(H_CF_Out[25]), .CK(clk), .Q(H_CF_Reg[25]) );
  DFF_X1 H_CF_Reg_reg_26_ ( .D(H_CF_Out[26]), .CK(clk), .Q(H_CF_Reg[26]) );
  DFF_X1 out3_reg_2_ ( .D(H_out3[2]), .CK(clk), .Q(out3[2]) );
  NAND2_X1 U214 ( .A1(n212), .A2(Rq3[2]), .ZN(n162) );
  INV_X1 U215 ( .A(n162), .ZN(G_CF_Out[5]) );
  NAND2_X1 U216 ( .A1(G_out2_reg[1]), .A2(G_out1_reg[3]), .ZN(n170) );
  INV_X1 U217 ( .A(n170), .ZN(n184) );
  NAND2_X1 U218 ( .A1(G_out2_reg[2]), .A2(n184), .ZN(n172) );
  NAND2_X1 U219 ( .A1(G_out2_reg[2]), .A2(G_out1_reg[3]), .ZN(n113) );
  NAND2_X1 U220 ( .A1(n222), .A2(n113), .ZN(n169) );
  AND2_X1 U221 ( .A1(n172), .A2(n169), .ZN(H_CF_Out[19]) );
  XOR2_X1 U222 ( .A(in3[3]), .B(in3[0]), .Z(F_in3_3_) );
  XOR2_X1 U223 ( .A(in2[3]), .B(in2[0]), .Z(F_in2_3_) );
  XNOR2_X1 U224 ( .A(in1[3]), .B(in1[0]), .ZN(F_in1_3_) );
  XOR2_X1 U225 ( .A(r[3]), .B(r[2]), .Z(n115) );
  XNOR2_X1 U226 ( .A(F_CF_Reg[16]), .B(F_CF_Reg[17]), .ZN(n114) );
  XNOR2_X1 U227 ( .A(n115), .B(n114), .ZN(n116) );
  XOR2_X1 U228 ( .A(F_CF_Reg[15]), .B(n116), .Z(q3[3]) );
  XOR2_X1 U229 ( .A(F_CF_Reg[13]), .B(F_CF_Reg[12]), .Z(n118) );
  XNOR2_X1 U230 ( .A(r[3]), .B(F_CF_Reg[14]), .ZN(n117) );
  XNOR2_X1 U231 ( .A(n118), .B(n117), .ZN(q2[3]) );
  XOR2_X1 U232 ( .A(F_CF_Reg[10]), .B(F_CF_Reg[9]), .Z(n120) );
  XNOR2_X1 U233 ( .A(r[2]), .B(F_CF_Reg[11]), .ZN(n119) );
  XNOR2_X1 U234 ( .A(n120), .B(n119), .ZN(q1[3]) );
  XOR2_X1 U235 ( .A(r[1]), .B(r[0]), .Z(n122) );
  XNOR2_X1 U236 ( .A(F_CF_Reg[7]), .B(F_CF_Reg[8]), .ZN(n121) );
  XNOR2_X1 U237 ( .A(n122), .B(n121), .ZN(n123) );
  XOR2_X1 U238 ( .A(F_CF_Reg[6]), .B(n123), .Z(q3[2]) );
  XOR2_X1 U239 ( .A(F_CF_Reg[4]), .B(F_CF_Reg[3]), .Z(n125) );
  XNOR2_X1 U240 ( .A(r[1]), .B(F_CF_Reg[5]), .ZN(n124) );
  XNOR2_X1 U241 ( .A(n125), .B(n124), .ZN(q2[2]) );
  XOR2_X1 U242 ( .A(F_CF_Reg[1]), .B(F_CF_Reg[0]), .Z(n127) );
  XNOR2_X1 U243 ( .A(r[0]), .B(F_CF_Reg[2]), .ZN(n126) );
  XNOR2_X1 U244 ( .A(n127), .B(n126), .ZN(q1[2]) );
  XOR2_X1 U245 ( .A(n209), .B(r[4]), .Z(n128) );
  XNOR2_X1 U246 ( .A(n128), .B(r[5]), .ZN(F_N5) );
  XOR2_X1 U247 ( .A(r[5]), .B(F_in2_reg[3]), .Z(F_N4) );
  XNOR2_X1 U248 ( .A(r[4]), .B(n208), .ZN(F_N3) );
  XOR2_X1 U249 ( .A(n220), .B(r[6]), .Z(n129) );
  XNOR2_X1 U250 ( .A(n129), .B(r[7]), .ZN(F_N2) );
  XNOR2_X1 U251 ( .A(r[7]), .B(n217), .ZN(F_N1) );
  XNOR2_X1 U252 ( .A(r[6]), .B(n216), .ZN(F_N0) );
  XOR2_X1 U253 ( .A(r[11]), .B(r[10]), .Z(n131) );
  XNOR2_X1 U254 ( .A(G_CF_Reg[16]), .B(G_CF_Reg[17]), .ZN(n130) );
  XNOR2_X1 U255 ( .A(n131), .B(n130), .ZN(n132) );
  XOR2_X1 U256 ( .A(G_CF_Reg[15]), .B(n132), .Z(G_out3[3]) );
  XOR2_X1 U257 ( .A(G_CF_Reg[13]), .B(G_CF_Reg[12]), .Z(n134) );
  XNOR2_X1 U258 ( .A(r[11]), .B(G_CF_Reg[14]), .ZN(n133) );
  XNOR2_X1 U259 ( .A(n134), .B(n133), .ZN(G_out2[3]) );
  XOR2_X1 U260 ( .A(G_CF_Reg[10]), .B(G_CF_Reg[9]), .Z(n136) );
  XNOR2_X1 U261 ( .A(r[10]), .B(G_CF_Reg[11]), .ZN(n135) );
  XNOR2_X1 U262 ( .A(n136), .B(n135), .ZN(G_out1[3]) );
  XOR2_X1 U263 ( .A(r[9]), .B(r[8]), .Z(n138) );
  XNOR2_X1 U264 ( .A(G_CF_Reg[7]), .B(G_CF_Reg[8]), .ZN(n137) );
  XNOR2_X1 U265 ( .A(n138), .B(n137), .ZN(n139) );
  XOR2_X1 U266 ( .A(G_CF_Reg[6]), .B(n139), .Z(G_out3[2]) );
  XOR2_X1 U267 ( .A(G_CF_Reg[4]), .B(G_CF_Reg[3]), .Z(n141) );
  XNOR2_X1 U268 ( .A(r[9]), .B(G_CF_Reg[5]), .ZN(n140) );
  XNOR2_X1 U269 ( .A(n141), .B(n140), .ZN(G_out2[2]) );
  XOR2_X1 U270 ( .A(G_CF_Reg[1]), .B(G_CF_Reg[0]), .Z(n143) );
  XNOR2_X1 U271 ( .A(r[8]), .B(G_CF_Reg[2]), .ZN(n142) );
  XNOR2_X1 U272 ( .A(n143), .B(n142), .ZN(G_out1[2]) );
  XOR2_X1 U273 ( .A(r[14]), .B(r[15]), .Z(n145) );
  XOR2_X1 U274 ( .A(n213), .B(Rq3[2]), .Z(n144) );
  XNOR2_X1 U275 ( .A(n145), .B(n144), .ZN(G_N5) );
  XOR2_X1 U276 ( .A(n211), .B(r[15]), .Z(n146) );
  XOR2_X1 U277 ( .A(n146), .B(n212), .Z(G_N4) );
  XOR2_X1 U278 ( .A(n206), .B(r[14]), .Z(n147) );
  XOR2_X1 U279 ( .A(n147), .B(n204), .Z(G_N3) );
  XOR2_X1 U280 ( .A(n215), .B(r[12]), .Z(n148) );
  XNOR2_X1 U281 ( .A(n148), .B(r[13]), .ZN(G_N2) );
  XNOR2_X1 U282 ( .A(n211), .B(r[13]), .ZN(G_N1) );
  XOR2_X1 U283 ( .A(r[12]), .B(Rq1[2]), .Z(G_N0) );
  NAND2_X1 U284 ( .A1(F_in1_reg[2]), .A2(F_in1_reg[3]), .ZN(n149) );
  XNOR2_X1 U285 ( .A(n219), .B(n149), .ZN(F_CF_Out[0]) );
  NOR2_X1 U286 ( .A1(n208), .A2(n217), .ZN(F_CF_Out[1]) );
  NOR2_X1 U287 ( .A1(F_in1_reg[3]), .A2(n220), .ZN(F_CF_Out[2]) );
  NOR2_X1 U288 ( .A1(n216), .A2(n207), .ZN(F_CF_Out[3]) );
  NAND2_X1 U289 ( .A1(F_in2_reg[2]), .A2(n207), .ZN(n150) );
  XOR2_X1 U290 ( .A(n221), .B(n150), .Z(F_CF_Out[4]) );
  NOR2_X1 U291 ( .A1(F_in2_reg[3]), .A2(n220), .ZN(F_CF_Out[5]) );
  NOR2_X1 U292 ( .A1(n209), .A2(n216), .ZN(F_CF_Out[6]) );
  NOR2_X1 U293 ( .A1(F_in3_reg[3]), .A2(n217), .ZN(F_CF_Out[7]) );
  NAND2_X1 U294 ( .A1(F_in3_reg[2]), .A2(F_in3_reg[3]), .ZN(n151) );
  XOR2_X1 U295 ( .A(n151), .B(n218), .Z(F_CF_Out[8]) );
  NAND2_X1 U296 ( .A1(F_in1_reg[3]), .A2(F_in1_reg[1]), .ZN(n152) );
  XOR2_X1 U297 ( .A(F_in1_reg[0]), .B(n152), .Z(F_CF_Out[9]) );
  NOR2_X1 U298 ( .A1(n208), .A2(n221), .ZN(F_CF_Out[10]) );
  NOR2_X1 U299 ( .A1(F_in1_reg[3]), .A2(n218), .ZN(F_CF_Out[11]) );
  NOR2_X1 U300 ( .A1(n219), .A2(n207), .ZN(F_CF_Out[12]) );
  NAND2_X1 U301 ( .A1(n207), .A2(F_in2_reg[1]), .ZN(n153) );
  XNOR2_X1 U302 ( .A(n153), .B(F_in2_reg[0]), .ZN(F_CF_Out[13]) );
  NOR2_X1 U303 ( .A1(F_in2_reg[3]), .A2(n218), .ZN(F_CF_Out[14]) );
  NOR2_X1 U304 ( .A1(n209), .A2(n219), .ZN(F_CF_Out[15]) );
  NOR2_X1 U305 ( .A1(F_in3_reg[3]), .A2(n221), .ZN(F_CF_Out[16]) );
  NAND2_X1 U306 ( .A1(F_in3_reg[1]), .A2(F_in3_reg[3]), .ZN(n154) );
  XNOR2_X1 U307 ( .A(n154), .B(F_in3_reg[0]), .ZN(F_CF_Out[17]) );
  NAND2_X1 U308 ( .A1(Rq1[3]), .A2(Rq1[2]), .ZN(n156) );
  XNOR2_X1 U309 ( .A(n156), .B(Rq1[1]), .ZN(G_CF_Out[0]) );
  NOR2_X1 U310 ( .A1(Rq1[3]), .A2(n211), .ZN(G_CF_Out[1]) );
  NOR2_X1 U311 ( .A1(n215), .A2(n206), .ZN(G_CF_Out[2]) );
  NAND2_X1 U312 ( .A1(Rq2[2]), .A2(Rq2[3]), .ZN(n159) );
  XNOR2_X1 U313 ( .A(Rq2[1]), .B(n159), .ZN(G_CF_Out[4]) );
  NOR2_X1 U314 ( .A1(Rq3[3]), .A2(n211), .ZN(G_CF_Out[7]) );
  NAND2_X1 U315 ( .A1(Rq1[1]), .A2(n206), .ZN(n155) );
  NAND2_X1 U316 ( .A1(n156), .A2(n155), .ZN(n157) );
  XOR2_X1 U317 ( .A(Rq1[0]), .B(n157), .Z(G_CF_Out[9]) );
  XNOR2_X1 U318 ( .A(n211), .B(Rq2[1]), .ZN(n165) );
  NAND2_X1 U319 ( .A1(Rq1[3]), .A2(n165), .ZN(n158) );
  XNOR2_X1 U320 ( .A(n158), .B(Rq2[0]), .ZN(G_CF_Out[10]) );
  XOR2_X1 U321 ( .A(n215), .B(Rq3[1]), .Z(n200) );
  NOR2_X1 U322 ( .A1(n200), .A2(n206), .ZN(G_CF_Out[11]) );
  XOR2_X1 U323 ( .A(Rq1[1]), .B(n204), .Z(n164) );
  NOR2_X1 U324 ( .A1(n164), .A2(n212), .ZN(G_CF_Out[12]) );
  NOR2_X1 U325 ( .A1(n212), .A2(n204), .ZN(G_CF_Out[3]) );
  NAND2_X1 U326 ( .A1(Rq2[1]), .A2(n212), .ZN(n160) );
  NAND2_X1 U327 ( .A1(n160), .A2(n159), .ZN(n161) );
  XOR2_X1 U328 ( .A(Rq2[0]), .B(n161), .Z(G_CF_Out[13]) );
  NAND2_X1 U329 ( .A1(Rq3[1]), .A2(Rq2[3]), .ZN(n163) );
  NAND2_X1 U330 ( .A1(n163), .A2(n162), .ZN(G_CF_Out[14]) );
  NOR2_X1 U331 ( .A1(n164), .A2(n213), .ZN(G_CF_Out[15]) );
  NOR2_X1 U332 ( .A1(n213), .A2(n204), .ZN(G_CF_Out[6]) );
  NAND2_X1 U333 ( .A1(n165), .A2(Rq3[3]), .ZN(n166) );
  XNOR2_X1 U334 ( .A(n166), .B(Rq2[0]), .ZN(G_CF_Out[16]) );
  NAND2_X1 U335 ( .A1(G_out1_reg[3]), .A2(G_out1_reg[2]), .ZN(n168) );
  NAND2_X1 U336 ( .A1(G_out1_reg[3]), .A2(G_out1_reg[1]), .ZN(n167) );
  XNOR2_X1 U337 ( .A(n167), .B(G_out1_reg[0]), .ZN(n183) );
  XNOR2_X1 U338 ( .A(n168), .B(n183), .ZN(H_CF_Out[0]) );
  NAND2_X1 U339 ( .A1(n170), .A2(n169), .ZN(n171) );
  NAND2_X1 U340 ( .A1(n172), .A2(n171), .ZN(H_CF_Out[1]) );
  XOR2_X1 U341 ( .A(n203), .B(G_out3_reg[1]), .Z(n176) );
  NOR2_X1 U342 ( .A1(n176), .A2(n223), .ZN(H_CF_Out[2]) );
  NAND2_X1 U343 ( .A1(G_out1_reg[1]), .A2(n210), .ZN(n173) );
  NAND2_X1 U344 ( .A1(G_out2_reg[3]), .A2(G_out1_reg[2]), .ZN(n188) );
  NAND2_X1 U345 ( .A1(n173), .A2(n188), .ZN(n174) );
  XOR2_X1 U346 ( .A(G_out1_reg[0]), .B(n174), .Z(H_CF_Out[3]) );
  XOR2_X1 U347 ( .A(n222), .B(G_out2_reg[2]), .Z(n179) );
  NOR2_X1 U348 ( .A1(n179), .A2(n210), .ZN(n175) );
  XOR2_X1 U349 ( .A(G_out2_reg[0]), .B(n175), .Z(H_CF_Out[4]) );
  NOR2_X1 U350 ( .A1(n176), .A2(n210), .ZN(H_CF_Out[5]) );
  XOR2_X1 U351 ( .A(n205), .B(n202), .Z(n177) );
  NAND2_X1 U352 ( .A1(n177), .A2(G_out3_reg[3]), .ZN(n178) );
  XNOR2_X1 U353 ( .A(G_out1_reg[0]), .B(n178), .ZN(H_CF_Out[6]) );
  NOR2_X1 U354 ( .A1(n179), .A2(n214), .ZN(H_CF_Out[7]) );
  NAND2_X1 U355 ( .A1(G_out3_reg[3]), .A2(G_out3_reg[2]), .ZN(n181) );
  NAND2_X1 U356 ( .A1(G_out3_reg[1]), .A2(n214), .ZN(n180) );
  NAND2_X1 U357 ( .A1(n181), .A2(n180), .ZN(n182) );
  XOR2_X1 U358 ( .A(G_out3_reg[0]), .B(n182), .Z(H_CF_Out[8]) );
  XOR2_X1 U359 ( .A(n205), .B(n183), .Z(H_CF_Out[9]) );
  XOR2_X1 U360 ( .A(G_out2_reg[2]), .B(n184), .Z(H_CF_Out[10]) );
  AND2_X1 U361 ( .A1(G_out1_reg[3]), .A2(G_out3_reg[1]), .ZN(H_CF_Out[11]) );
  NOR2_X1 U362 ( .A1(n210), .A2(n202), .ZN(H_CF_Out[12]) );
  NAND2_X1 U363 ( .A1(n210), .A2(G_out2_reg[1]), .ZN(n185) );
  XNOR2_X1 U364 ( .A(n185), .B(G_out2_reg[0]), .ZN(H_CF_Out[13]) );
  NAND2_X1 U365 ( .A1(G_out2_reg[3]), .A2(G_out3_reg[1]), .ZN(n186) );
  XOR2_X1 U366 ( .A(n186), .B(n203), .Z(H_CF_Out[14]) );
  NOR2_X1 U367 ( .A1(n214), .A2(n202), .ZN(H_CF_Out[15]) );
  NOR2_X1 U368 ( .A1(G_out3_reg[3]), .A2(n222), .ZN(H_CF_Out[16]) );
  NAND2_X1 U369 ( .A1(G_out3_reg[1]), .A2(G_out3_reg[3]), .ZN(n187) );
  XNOR2_X1 U370 ( .A(n187), .B(G_out3_reg[0]), .ZN(H_CF_Out[17]) );
  NAND2_X1 U371 ( .A1(n205), .A2(n223), .ZN(H_CF_Out[18]) );
  NOR2_X1 U372 ( .A1(n223), .A2(n203), .ZN(H_CF_Out[20]) );
  XOR2_X1 U373 ( .A(n202), .B(n188), .Z(H_CF_Out[21]) );
  NOR2_X1 U374 ( .A1(G_out2_reg[2]), .A2(n210), .ZN(H_CF_Out[22]) );
  NOR2_X1 U375 ( .A1(G_out2_reg[3]), .A2(n203), .ZN(H_CF_Out[23]) );
  NOR2_X1 U376 ( .A1(G_out3_reg[3]), .A2(n205), .ZN(H_CF_Out[24]) );
  AND2_X1 U377 ( .A1(G_out2_reg[2]), .A2(G_out3_reg[3]), .ZN(H_CF_Out[25]) );
  NAND2_X1 U378 ( .A1(n203), .A2(n214), .ZN(n189) );
  XOR2_X1 U379 ( .A(n189), .B(G_out3_reg[1]), .Z(H_CF_Out[26]) );
  XNOR2_X1 U380 ( .A(H_CF_Reg[26]), .B(H_CF_Reg[25]), .ZN(n190) );
  XNOR2_X1 U381 ( .A(n190), .B(H_CF_Reg[24]), .ZN(H_out3[2]) );
  XNOR2_X1 U382 ( .A(H_CF_Reg[23]), .B(H_CF_Reg[22]), .ZN(n191) );
  XNOR2_X1 U383 ( .A(n191), .B(H_CF_Reg[21]), .ZN(H_out2[2]) );
  XNOR2_X1 U384 ( .A(H_CF_Reg[20]), .B(H_CF_Reg[19]), .ZN(n192) );
  XNOR2_X1 U385 ( .A(n192), .B(H_CF_Reg[18]), .ZN(H_out1[2]) );
  XNOR2_X1 U386 ( .A(H_CF_Reg[17]), .B(H_CF_Reg[16]), .ZN(n193) );
  XNOR2_X1 U387 ( .A(n193), .B(H_CF_Reg[15]), .ZN(H_out3[1]) );
  XNOR2_X1 U388 ( .A(H_CF_Reg[14]), .B(H_CF_Reg[13]), .ZN(n194) );
  XNOR2_X1 U389 ( .A(n194), .B(H_CF_Reg[12]), .ZN(H_out2[1]) );
  XNOR2_X1 U390 ( .A(H_CF_Reg[11]), .B(H_CF_Reg[10]), .ZN(n195) );
  XNOR2_X1 U391 ( .A(n195), .B(H_CF_Reg[9]), .ZN(H_out1[1]) );
  XNOR2_X1 U392 ( .A(H_CF_Reg[8]), .B(H_CF_Reg[7]), .ZN(n196) );
  XNOR2_X1 U393 ( .A(n196), .B(H_CF_Reg[6]), .ZN(H_out3[0]) );
  XNOR2_X1 U394 ( .A(H_CF_Reg[5]), .B(H_CF_Reg[4]), .ZN(n197) );
  XNOR2_X1 U395 ( .A(n197), .B(H_CF_Reg[3]), .ZN(H_out2[0]) );
  XNOR2_X1 U396 ( .A(H_CF_Reg[2]), .B(H_CF_Reg[1]), .ZN(n198) );
  XNOR2_X1 U397 ( .A(n198), .B(H_CF_Reg[0]), .ZN(H_out1[0]) );
  NAND2_X1 U398 ( .A1(Rq3[2]), .A2(n213), .ZN(n199) );
  XNOR2_X1 U399 ( .A(Rq3[1]), .B(n199), .ZN(G_CF_Out[8]) );
  NOR2_X1 U400 ( .A1(n200), .A2(Rq3[3]), .ZN(n201) );
  XOR2_X1 U401 ( .A(Rq3[0]), .B(n201), .Z(G_CF_Out[17]) );
endmodule

