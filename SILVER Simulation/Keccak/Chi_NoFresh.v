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


module Chi_NoFresh ( clk, in1, in2, in3, out1, out2, out3 );
  (* SILVER="[4:0]_0" *) input [4:0] in1;
  (* SILVER="[4:0]_1" *) input [4:0] in2;
  (* SILVER="[4:0]_2" *) input [4:0] in3;
//  (* SILVER="refresh" *) input [7:0] r;
  (* SILVER="[4:0]_0" *) output [4:0] out1;
  (* SILVER="[4:0]_1" *) output [4:0] out2;
  (* SILVER="[4:0]_2" *) output [4:0] out3;
  (* SILVER="clock" *) input clk;
  wire   Inst_0__CF_Inst_n1, Inst_2__CF_Inst_n1, Inst_3__CF_Inst_n2,
         Inst_3__CF_Inst_n1, Inst_5__CF_Inst_n1, Inst_6__CF_Inst_n1,
         Inst_7__CF_Inst_n2, Inst_7__CF_Inst_n1, Inst_10__CF_Inst_n2,
         Inst_10__CF_Inst_n1, Inst_11__CF_Inst_n1, Inst_12__CF_Inst_n1,
         Inst_14__CF_Inst_n2, Inst_14__CF_Inst_n1, Inst_15__CF_Inst_n1,
         Inst_17__CF_Inst_n1, Inst_19__CF_Inst_n1, Inst_20__CF_Inst_n1,
         Inst_21__CF_Inst_n2, Inst_21__CF_Inst_n1, Inst_22__CF_Inst_n1,
         Inst_25__CF_Inst_n2, Inst_25__CF_Inst_n1, Inst_26__CF_Inst_n1,
         Inst_27__CF_Inst_n1, Inst_29__CF_Inst_n1, Inst_30__CF_Inst_n2,
         Inst_30__CF_Inst_n1, Inst_32__CF_Inst_n1, Inst_33__CF_Inst_n1,
         Inst_34__CF_Inst_n2, Inst_34__CF_Inst_n1, Inst_36__CF_Inst_n1,
         Inst_38__CF_Inst_n1, Inst_39__CF_Inst_n2, Inst_39__CF_Inst_n1,
         Inst_41__CF_Inst_n1, Inst_42__CF_Inst_n1, Inst_43__CF_Inst_n2,
         Inst_43__CF_Inst_n1, InstXOR_0__Compression1_n1,
         InstXOR_0__Compression2_n1, InstXOR_0__Compression3_n1,
         InstXOR_1__Compression1_n1, InstXOR_1__Compression2_n1,
         InstXOR_1__Compression3_n1, InstXOR_2__Compression1_n1,
         InstXOR_2__Compression2_n1, InstXOR_2__Compression3_n1,
         InstXOR_3__Compression1_n1, InstXOR_3__Compression2_n1,
         InstXOR_3__Compression3_n1, InstXOR_4__Compression1_n1,
         InstXOR_4__Compression2_n1, InstXOR_4__Compression3_n1;
  wire   [44:0] CF_Out;
  wire   [44:0] CF_Reg;

  DFF_X1 CF_Reg_reg_44_ ( .D(CF_Out[44]), .CK(clk), .Q(CF_Reg[44]) );
  DFF_X1 CF_Reg_reg_43_ ( .D(CF_Out[43]), .CK(clk), .Q(CF_Reg[43]) );
  DFF_X1 CF_Reg_reg_42_ ( .D(CF_Out[42]), .CK(clk), .Q(CF_Reg[42]) );
  DFF_X1 CF_Reg_reg_41_ ( .D(CF_Out[41]), .CK(clk), .Q(CF_Reg[41]) );
  DFF_X1 CF_Reg_reg_40_ ( .D(CF_Out[40]), .CK(clk), .Q(CF_Reg[40]) );
  DFF_X1 CF_Reg_reg_39_ ( .D(CF_Out[39]), .CK(clk), .Q(CF_Reg[39]) );
  DFF_X1 CF_Reg_reg_38_ ( .D(CF_Out[38]), .CK(clk), .Q(CF_Reg[38]) );
  DFF_X1 CF_Reg_reg_37_ ( .D(CF_Out[37]), .CK(clk), .Q(CF_Reg[37]) );
  DFF_X1 CF_Reg_reg_36_ ( .D(CF_Out[36]), .CK(clk), .Q(CF_Reg[36]) );
  DFF_X1 CF_Reg_reg_35_ ( .D(CF_Out[35]), .CK(clk), .Q(CF_Reg[35]) );
  DFF_X1 CF_Reg_reg_34_ ( .D(CF_Out[34]), .CK(clk), .Q(CF_Reg[34]) );
  DFF_X1 CF_Reg_reg_33_ ( .D(CF_Out[33]), .CK(clk), .Q(CF_Reg[33]) );
  DFF_X1 CF_Reg_reg_32_ ( .D(CF_Out[32]), .CK(clk), .Q(CF_Reg[32]) );
  DFF_X1 CF_Reg_reg_31_ ( .D(CF_Out[31]), .CK(clk), .Q(CF_Reg[31]) );
  DFF_X1 CF_Reg_reg_30_ ( .D(CF_Out[30]), .CK(clk), .Q(CF_Reg[30]) );
  DFF_X1 CF_Reg_reg_29_ ( .D(CF_Out[29]), .CK(clk), .Q(CF_Reg[29]) );
  DFF_X1 CF_Reg_reg_28_ ( .D(CF_Out[28]), .CK(clk), .Q(CF_Reg[28]) );
  DFF_X1 CF_Reg_reg_27_ ( .D(CF_Out[27]), .CK(clk), .Q(CF_Reg[27]) );
  DFF_X1 CF_Reg_reg_26_ ( .D(CF_Out[26]), .CK(clk), .Q(CF_Reg[26]) );
  DFF_X1 CF_Reg_reg_25_ ( .D(CF_Out[25]), .CK(clk), .Q(CF_Reg[25]) );
  DFF_X1 CF_Reg_reg_24_ ( .D(CF_Out[24]), .CK(clk), .Q(CF_Reg[24]) );
  DFF_X1 CF_Reg_reg_23_ ( .D(CF_Out[23]), .CK(clk), .Q(CF_Reg[23]) );
  DFF_X1 CF_Reg_reg_22_ ( .D(CF_Out[22]), .CK(clk), .Q(CF_Reg[22]) );
  DFF_X1 CF_Reg_reg_21_ ( .D(CF_Out[21]), .CK(clk), .Q(CF_Reg[21]) );
  DFF_X1 CF_Reg_reg_20_ ( .D(CF_Out[20]), .CK(clk), .Q(CF_Reg[20]) );
  DFF_X1 CF_Reg_reg_19_ ( .D(CF_Out[19]), .CK(clk), .Q(CF_Reg[19]) );
  DFF_X1 CF_Reg_reg_18_ ( .D(CF_Out[18]), .CK(clk), .Q(CF_Reg[18]) );
  DFF_X1 CF_Reg_reg_17_ ( .D(CF_Out[17]), .CK(clk), .Q(CF_Reg[17]) );
  DFF_X1 CF_Reg_reg_16_ ( .D(CF_Out[16]), .CK(clk), .Q(CF_Reg[16]) );
  DFF_X1 CF_Reg_reg_15_ ( .D(CF_Out[15]), .CK(clk), .Q(CF_Reg[15]) );
  DFF_X1 CF_Reg_reg_14_ ( .D(CF_Out[14]), .CK(clk), .Q(CF_Reg[14]) );
  DFF_X1 CF_Reg_reg_13_ ( .D(CF_Out[13]), .CK(clk), .Q(CF_Reg[13]) );
  DFF_X1 CF_Reg_reg_12_ ( .D(CF_Out[12]), .CK(clk), .Q(CF_Reg[12]) );
  DFF_X1 CF_Reg_reg_11_ ( .D(CF_Out[11]), .CK(clk), .Q(CF_Reg[11]) );
  DFF_X1 CF_Reg_reg_10_ ( .D(CF_Out[10]), .CK(clk), .Q(CF_Reg[10]) );
  DFF_X1 CF_Reg_reg_9_ ( .D(CF_Out[9]), .CK(clk), .Q(CF_Reg[9]) );
  DFF_X1 CF_Reg_reg_8_ ( .D(CF_Out[8]), .CK(clk), .Q(CF_Reg[8]) );
  DFF_X1 CF_Reg_reg_7_ ( .D(CF_Out[7]), .CK(clk), .Q(CF_Reg[7]) );
  DFF_X1 CF_Reg_reg_6_ ( .D(CF_Out[6]), .CK(clk), .Q(CF_Reg[6]) );
  DFF_X1 CF_Reg_reg_5_ ( .D(CF_Out[5]), .CK(clk), .Q(CF_Reg[5]) );
  DFF_X1 CF_Reg_reg_4_ ( .D(CF_Out[4]), .CK(clk), .Q(CF_Reg[4]) );
  DFF_X1 CF_Reg_reg_3_ ( .D(CF_Out[3]), .CK(clk), .Q(CF_Reg[3]) );
  DFF_X1 CF_Reg_reg_2_ ( .D(CF_Out[2]), .CK(clk), .Q(CF_Reg[2]) );
  DFF_X1 CF_Reg_reg_1_ ( .D(CF_Out[1]), .CK(clk), .Q(CF_Reg[1]) );
  DFF_X1 CF_Reg_reg_0_ ( .D(CF_Out[0]), .CK(clk), .Q(CF_Reg[0]) );
  NOR2_X1 Inst_0__CF_Inst_U2 ( .A1(in1[0]), .A2(Inst_0__CF_Inst_n1), .ZN(
        CF_Out[0]) );
  INV_X1 Inst_0__CF_Inst_U1 ( .A(in1[1]), .ZN(Inst_0__CF_Inst_n1) );
  AND2_X1 Inst_1__CF_Inst_U1 ( .A1(in1[0]), .A2(in2[1]), .ZN(CF_Out[1]) );
  XNOR2_X1 Inst_2__CF_Inst_U2 ( .A(Inst_2__CF_Inst_n1), .B(in3[4]), .ZN(
        CF_Out[2]) );
  NAND2_X1 Inst_2__CF_Inst_U1 ( .A1(in1[0]), .A2(in3[1]), .ZN(
        Inst_2__CF_Inst_n1) );
  XNOR2_X1 Inst_3__CF_Inst_U3 ( .A(in1[4]), .B(Inst_3__CF_Inst_n2), .ZN(
        CF_Out[3]) );
  NAND2_X1 Inst_3__CF_Inst_U2 ( .A1(in1[1]), .A2(Inst_3__CF_Inst_n1), .ZN(
        Inst_3__CF_Inst_n2) );
  INV_X1 Inst_3__CF_Inst_U1 ( .A(in2[0]), .ZN(Inst_3__CF_Inst_n1) );
  AND2_X1 Inst_4__CF_Inst_U1 ( .A1(in2[0]), .A2(in2[1]), .ZN(CF_Out[4]) );
  NOR2_X1 Inst_5__CF_Inst_U2 ( .A1(in2[0]), .A2(Inst_5__CF_Inst_n1), .ZN(
        CF_Out[5]) );
  INV_X1 Inst_5__CF_Inst_U1 ( .A(in3[1]), .ZN(Inst_5__CF_Inst_n1) );
  NOR2_X1 Inst_6__CF_Inst_U2 ( .A1(in3[0]), .A2(Inst_6__CF_Inst_n1), .ZN(
        CF_Out[6]) );
  INV_X1 Inst_6__CF_Inst_U1 ( .A(in1[1]), .ZN(Inst_6__CF_Inst_n1) );
  XNOR2_X1 Inst_7__CF_Inst_U3 ( .A(in2[4]), .B(Inst_7__CF_Inst_n2), .ZN(
        CF_Out[7]) );
  NAND2_X1 Inst_7__CF_Inst_U2 ( .A1(in2[1]), .A2(Inst_7__CF_Inst_n1), .ZN(
        Inst_7__CF_Inst_n2) );
  INV_X1 Inst_7__CF_Inst_U1 ( .A(in3[0]), .ZN(Inst_7__CF_Inst_n1) );
  AND2_X1 Inst_8__CF_Inst_U1 ( .A1(in3[0]), .A2(in3[1]), .ZN(CF_Out[8]) );
  AND2_X1 Inst_9__CF_Inst_U1 ( .A1(in1[4]), .A2(in1[0]), .ZN(CF_Out[9]) );
  XNOR2_X1 Inst_10__CF_Inst_U3 ( .A(in2[3]), .B(Inst_10__CF_Inst_n2), .ZN(
        CF_Out[10]) );
  NAND2_X1 Inst_10__CF_Inst_U2 ( .A1(in2[0]), .A2(Inst_10__CF_Inst_n1), .ZN(
        Inst_10__CF_Inst_n2) );
  INV_X1 Inst_10__CF_Inst_U1 ( .A(in1[4]), .ZN(Inst_10__CF_Inst_n1) );
  NOR2_X1 Inst_11__CF_Inst_U2 ( .A1(in1[4]), .A2(Inst_11__CF_Inst_n1), .ZN(
        CF_Out[11]) );
  INV_X1 Inst_11__CF_Inst_U1 ( .A(in3[0]), .ZN(Inst_11__CF_Inst_n1) );
  NOR2_X1 Inst_12__CF_Inst_U2 ( .A1(in2[4]), .A2(Inst_12__CF_Inst_n1), .ZN(
        CF_Out[12]) );
  INV_X1 Inst_12__CF_Inst_U1 ( .A(in1[0]), .ZN(Inst_12__CF_Inst_n1) );
  AND2_X1 Inst_13__CF_Inst_U1 ( .A1(in2[4]), .A2(in2[0]), .ZN(CF_Out[13]) );
  XNOR2_X1 Inst_14__CF_Inst_U3 ( .A(in3[3]), .B(Inst_14__CF_Inst_n2), .ZN(
        CF_Out[14]) );
  NAND2_X1 Inst_14__CF_Inst_U2 ( .A1(in3[0]), .A2(Inst_14__CF_Inst_n1), .ZN(
        Inst_14__CF_Inst_n2) );
  INV_X1 Inst_14__CF_Inst_U1 ( .A(in2[4]), .ZN(Inst_14__CF_Inst_n1) );
  XNOR2_X1 Inst_15__CF_Inst_U2 ( .A(Inst_15__CF_Inst_n1), .B(in1[3]), .ZN(
        CF_Out[15]) );
  NAND2_X1 Inst_15__CF_Inst_U1 ( .A1(in3[4]), .A2(in1[0]), .ZN(
        Inst_15__CF_Inst_n1) );
  AND2_X1 Inst_16__CF_Inst_U1 ( .A1(in3[4]), .A2(in2[0]), .ZN(CF_Out[16]) );
  NOR2_X1 Inst_17__CF_Inst_U2 ( .A1(in3[4]), .A2(Inst_17__CF_Inst_n1), .ZN(
        CF_Out[17]) );
  INV_X1 Inst_17__CF_Inst_U1 ( .A(in3[0]), .ZN(Inst_17__CF_Inst_n1) );
  AND2_X1 Inst_18__CF_Inst_U1 ( .A1(in1[3]), .A2(in1[4]), .ZN(CF_Out[18]) );
  NOR2_X1 Inst_19__CF_Inst_U2 ( .A1(in1[3]), .A2(Inst_19__CF_Inst_n1), .ZN(
        CF_Out[19]) );
  INV_X1 Inst_19__CF_Inst_U1 ( .A(in2[4]), .ZN(Inst_19__CF_Inst_n1) );
  XNOR2_X1 Inst_20__CF_Inst_U2 ( .A(Inst_20__CF_Inst_n1), .B(in3[2]), .ZN(
        CF_Out[20]) );
  NAND2_X1 Inst_20__CF_Inst_U1 ( .A1(in1[3]), .A2(in3[4]), .ZN(
        Inst_20__CF_Inst_n1) );
  XNOR2_X1 Inst_21__CF_Inst_U3 ( .A(in1[2]), .B(Inst_21__CF_Inst_n2), .ZN(
        CF_Out[21]) );
  NAND2_X1 Inst_21__CF_Inst_U2 ( .A1(in1[4]), .A2(Inst_21__CF_Inst_n1), .ZN(
        Inst_21__CF_Inst_n2) );
  INV_X1 Inst_21__CF_Inst_U1 ( .A(in2[3]), .ZN(Inst_21__CF_Inst_n1) );
  NOR2_X1 Inst_22__CF_Inst_U2 ( .A1(in2[3]), .A2(Inst_22__CF_Inst_n1), .ZN(
        CF_Out[22]) );
  INV_X1 Inst_22__CF_Inst_U1 ( .A(in2[4]), .ZN(Inst_22__CF_Inst_n1) );
  AND2_X1 Inst_23__CF_Inst_U1 ( .A1(in2[3]), .A2(in3[4]), .ZN(CF_Out[23]) );
  AND2_X1 Inst_24__CF_Inst_U1 ( .A1(in3[3]), .A2(in1[4]), .ZN(CF_Out[24]) );
  XNOR2_X1 Inst_25__CF_Inst_U3 ( .A(in2[2]), .B(Inst_25__CF_Inst_n2), .ZN(
        CF_Out[25]) );
  NAND2_X1 Inst_25__CF_Inst_U2 ( .A1(in2[4]), .A2(Inst_25__CF_Inst_n1), .ZN(
        Inst_25__CF_Inst_n2) );
  INV_X1 Inst_25__CF_Inst_U1 ( .A(in3[3]), .ZN(Inst_25__CF_Inst_n1) );
  NOR2_X1 Inst_26__CF_Inst_U2 ( .A1(in3[3]), .A2(Inst_26__CF_Inst_n1), .ZN(
        CF_Out[26]) );
  INV_X1 Inst_26__CF_Inst_U1 ( .A(in3[4]), .ZN(Inst_26__CF_Inst_n1) );
  NOR2_X1 Inst_27__CF_Inst_U2 ( .A1(in1[2]), .A2(Inst_27__CF_Inst_n1), .ZN(
        CF_Out[27]) );
  INV_X1 Inst_27__CF_Inst_U1 ( .A(in1[3]), .ZN(Inst_27__CF_Inst_n1) );
  AND2_X1 Inst_28__CF_Inst_U1 ( .A1(in1[2]), .A2(in2[3]), .ZN(CF_Out[28]) );
  XNOR2_X1 Inst_29__CF_Inst_U2 ( .A(Inst_29__CF_Inst_n1), .B(in3[1]), .ZN(
        CF_Out[29]) );
  NAND2_X1 Inst_29__CF_Inst_U1 ( .A1(in1[2]), .A2(in3[3]), .ZN(
        Inst_29__CF_Inst_n1) );
  XNOR2_X1 Inst_30__CF_Inst_U3 ( .A(in1[1]), .B(Inst_30__CF_Inst_n2), .ZN(
        CF_Out[30]) );
  NAND2_X1 Inst_30__CF_Inst_U2 ( .A1(in1[3]), .A2(Inst_30__CF_Inst_n1), .ZN(
        Inst_30__CF_Inst_n2) );
  INV_X1 Inst_30__CF_Inst_U1 ( .A(in2[2]), .ZN(Inst_30__CF_Inst_n1) );
  AND2_X1 Inst_31__CF_Inst_U1 ( .A1(in2[2]), .A2(in2[3]), .ZN(CF_Out[31]) );
  NOR2_X1 Inst_32__CF_Inst_U2 ( .A1(in2[2]), .A2(Inst_32__CF_Inst_n1), .ZN(
        CF_Out[32]) );
  INV_X1 Inst_32__CF_Inst_U1 ( .A(in3[3]), .ZN(Inst_32__CF_Inst_n1) );
  NOR2_X1 Inst_33__CF_Inst_U2 ( .A1(in3[2]), .A2(Inst_33__CF_Inst_n1), .ZN(
        CF_Out[33]) );
  INV_X1 Inst_33__CF_Inst_U1 ( .A(in1[3]), .ZN(Inst_33__CF_Inst_n1) );
  XNOR2_X1 Inst_34__CF_Inst_U3 ( .A(in2[1]), .B(Inst_34__CF_Inst_n2), .ZN(
        CF_Out[34]) );
  NAND2_X1 Inst_34__CF_Inst_U2 ( .A1(in2[3]), .A2(Inst_34__CF_Inst_n1), .ZN(
        Inst_34__CF_Inst_n2) );
  INV_X1 Inst_34__CF_Inst_U1 ( .A(in3[2]), .ZN(Inst_34__CF_Inst_n1) );
  AND2_X1 Inst_35__CF_Inst_U1 ( .A1(in3[2]), .A2(in3[3]), .ZN(CF_Out[35]) );
  NOR2_X1 Inst_36__CF_Inst_U2 ( .A1(in1[1]), .A2(Inst_36__CF_Inst_n1), .ZN(
        CF_Out[36]) );
  INV_X1 Inst_36__CF_Inst_U1 ( .A(in1[2]), .ZN(Inst_36__CF_Inst_n1) );
  AND2_X1 Inst_37__CF_Inst_U1 ( .A1(in1[1]), .A2(in2[2]), .ZN(CF_Out[37]) );
  XNOR2_X1 Inst_38__CF_Inst_U2 ( .A(Inst_38__CF_Inst_n1), .B(in3[0]), .ZN(
        CF_Out[38]) );
  NAND2_X1 Inst_38__CF_Inst_U1 ( .A1(in1[1]), .A2(in3[2]), .ZN(
        Inst_38__CF_Inst_n1) );
  XNOR2_X1 Inst_39__CF_Inst_U3 ( .A(in1[0]), .B(Inst_39__CF_Inst_n2), .ZN(
        CF_Out[39]) );
  NAND2_X1 Inst_39__CF_Inst_U2 ( .A1(in1[2]), .A2(Inst_39__CF_Inst_n1), .ZN(
        Inst_39__CF_Inst_n2) );
  INV_X1 Inst_39__CF_Inst_U1 ( .A(in2[1]), .ZN(Inst_39__CF_Inst_n1) );
  AND2_X1 Inst_40__CF_Inst_U1 ( .A1(in2[1]), .A2(in2[2]), .ZN(CF_Out[40]) );
  NOR2_X1 Inst_41__CF_Inst_U2 ( .A1(in2[1]), .A2(Inst_41__CF_Inst_n1), .ZN(
        CF_Out[41]) );
  INV_X1 Inst_41__CF_Inst_U1 ( .A(in3[2]), .ZN(Inst_41__CF_Inst_n1) );
  NOR2_X1 Inst_42__CF_Inst_U2 ( .A1(in3[1]), .A2(Inst_42__CF_Inst_n1), .ZN(
        CF_Out[42]) );
  INV_X1 Inst_42__CF_Inst_U1 ( .A(in1[2]), .ZN(Inst_42__CF_Inst_n1) );
  XNOR2_X1 Inst_43__CF_Inst_U3 ( .A(in2[0]), .B(Inst_43__CF_Inst_n2), .ZN(
        CF_Out[43]) );
  NAND2_X1 Inst_43__CF_Inst_U2 ( .A1(in2[2]), .A2(Inst_43__CF_Inst_n1), .ZN(
        Inst_43__CF_Inst_n2) );
  INV_X1 Inst_43__CF_Inst_U1 ( .A(in3[1]), .ZN(Inst_43__CF_Inst_n1) );
  AND2_X1 Inst_44__CF_Inst_U1 ( .A1(in3[1]), .A2(in3[2]), .ZN(CF_Out[44]) );
  XNOR2_X1 InstXOR_0__Compression1_U2 ( .A(InstXOR_0__Compression1_n1), .B(
        CF_Reg[1]), .ZN(out1[4]) );
  XNOR2_X1 InstXOR_0__Compression1_U1 ( .A(CF_Reg[0]), .B(CF_Reg[2]), .ZN(
        InstXOR_0__Compression1_n1) );
  XNOR2_X1 InstXOR_0__Compression2_U2 ( .A(InstXOR_0__Compression2_n1), .B(
        CF_Reg[4]), .ZN(out2[4]) );
  XNOR2_X1 InstXOR_0__Compression2_U1 ( .A(CF_Reg[3]), .B(CF_Reg[5]), .ZN(
        InstXOR_0__Compression2_n1) );
  XNOR2_X1 InstXOR_0__Compression3_U2 ( .A(InstXOR_0__Compression3_n1), .B(
        CF_Reg[7]), .ZN(out3[4]) );
  XNOR2_X1 InstXOR_0__Compression3_U1 ( .A(CF_Reg[6]), .B(CF_Reg[8]), .ZN(
        InstXOR_0__Compression3_n1) );
  XNOR2_X1 InstXOR_1__Compression1_U2 ( .A(InstXOR_1__Compression1_n1), .B(
        CF_Reg[10]), .ZN(out1[3]) );
  XNOR2_X1 InstXOR_1__Compression1_U1 ( .A(CF_Reg[9]), .B(CF_Reg[11]), .ZN(
        InstXOR_1__Compression1_n1) );
  XNOR2_X1 InstXOR_1__Compression2_U2 ( .A(InstXOR_1__Compression2_n1), .B(
        CF_Reg[13]), .ZN(out2[3]) );
  XNOR2_X1 InstXOR_1__Compression2_U1 ( .A(CF_Reg[12]), .B(CF_Reg[14]), .ZN(
        InstXOR_1__Compression2_n1) );
  XNOR2_X1 InstXOR_1__Compression3_U2 ( .A(InstXOR_1__Compression3_n1), .B(
        CF_Reg[16]), .ZN(out3[3]) );
  XNOR2_X1 InstXOR_1__Compression3_U1 ( .A(CF_Reg[15]), .B(CF_Reg[17]), .ZN(
        InstXOR_1__Compression3_n1) );
  XNOR2_X1 InstXOR_2__Compression1_U2 ( .A(InstXOR_2__Compression1_n1), .B(
        CF_Reg[19]), .ZN(out1[2]) );
  XNOR2_X1 InstXOR_2__Compression1_U1 ( .A(CF_Reg[18]), .B(CF_Reg[20]), .ZN(
        InstXOR_2__Compression1_n1) );
  XNOR2_X1 InstXOR_2__Compression2_U2 ( .A(InstXOR_2__Compression2_n1), .B(
        CF_Reg[22]), .ZN(out2[2]) );
  XNOR2_X1 InstXOR_2__Compression2_U1 ( .A(CF_Reg[21]), .B(CF_Reg[23]), .ZN(
        InstXOR_2__Compression2_n1) );
  XNOR2_X1 InstXOR_2__Compression3_U2 ( .A(InstXOR_2__Compression3_n1), .B(
        CF_Reg[25]), .ZN(out3[2]) );
  XNOR2_X1 InstXOR_2__Compression3_U1 ( .A(CF_Reg[24]), .B(CF_Reg[26]), .ZN(
        InstXOR_2__Compression3_n1) );
  XNOR2_X1 InstXOR_3__Compression1_U2 ( .A(InstXOR_3__Compression1_n1), .B(
        CF_Reg[28]), .ZN(out1[1]) );
  XNOR2_X1 InstXOR_3__Compression1_U1 ( .A(CF_Reg[27]), .B(CF_Reg[29]), .ZN(
        InstXOR_3__Compression1_n1) );
  XNOR2_X1 InstXOR_3__Compression2_U2 ( .A(InstXOR_3__Compression2_n1), .B(
        CF_Reg[31]), .ZN(out2[1]) );
  XNOR2_X1 InstXOR_3__Compression2_U1 ( .A(CF_Reg[30]), .B(CF_Reg[32]), .ZN(
        InstXOR_3__Compression2_n1) );
  XNOR2_X1 InstXOR_3__Compression3_U2 ( .A(InstXOR_3__Compression3_n1), .B(
        CF_Reg[34]), .ZN(out3[1]) );
  XNOR2_X1 InstXOR_3__Compression3_U1 ( .A(CF_Reg[33]), .B(CF_Reg[35]), .ZN(
        InstXOR_3__Compression3_n1) );
  XNOR2_X1 InstXOR_4__Compression1_U2 ( .A(InstXOR_4__Compression1_n1), .B(
        CF_Reg[37]), .ZN(out1[0]) );
  XNOR2_X1 InstXOR_4__Compression1_U1 ( .A(CF_Reg[36]), .B(CF_Reg[38]), .ZN(
        InstXOR_4__Compression1_n1) );
  XNOR2_X1 InstXOR_4__Compression2_U2 ( .A(InstXOR_4__Compression2_n1), .B(
        CF_Reg[40]), .ZN(out2[0]) );
  XNOR2_X1 InstXOR_4__Compression2_U1 ( .A(CF_Reg[39]), .B(CF_Reg[41]), .ZN(
        InstXOR_4__Compression2_n1) );
  XNOR2_X1 InstXOR_4__Compression3_U2 ( .A(InstXOR_4__Compression3_n1), .B(
        CF_Reg[43]), .ZN(out3[0]) );
  XNOR2_X1 InstXOR_4__Compression3_U1 ( .A(CF_Reg[42]), .B(CF_Reg[44]), .ZN(
        InstXOR_4__Compression3_n1) );
endmodule

