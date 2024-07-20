/*
* -----------------------------------------------------------------
* COMPANY : Shandong University
* AUTHOR  : Yanhong Fan,  Chaoran Wang, Lixuan Wu,   Meiqin Wang
* DOCUMENT: "A Fast Search Method for 3-Share Second-Order Masking Schemes for Lightweight S-Boxes"  
* -----------------------------------------------------------------
*
* Copyright c 2023, Yanhong Fan, Chaoran Wang, Lixuan Wu,    Meiqin Wang
*
*
* All rights reserved.
* Please see LICENSE and README for license and further instructions.
*/
/*keccack*/
/*
f0 = d&e ^ a ^ d  ;
f1 = a&e ^ b ^ e  ;
f2 = a&b ^ a ^ c  ;
f3 = b&c ^ b ^ d  ;
f4=  c&d ^ c ^ e  ;


f0_0=e1&d1^d1   ;   || f1_0=a1&e1^b1   ;   || f2_0= b1&a1^c1   ; || f3_0= c1&b1^b1   ; ||f4_0= d1&c1^c1   ;
f0_1=e1&d2^a2   ;   || f1_1=a1&e2^e2   ;   || f2_1= b1&a2^a2   ; || f3_1= c1&b2^d2   ; ||f4_1= d1&c2^e2   ;
f0_2=e1&d3      ;   || f1_2=a1&e3      ;   || f2_2= b1&a3      ; || f3_2= c1&b3      ; ||f4_2= d1&c3      ;
f0_3=e2&d1^a1   ;   || f1_3=a2&e1^e1   ;   || f2_3= b2&a1^a1   ; || f3_3= c2&b1^d1   ; ||f4_3= d2&c1^e1   ;
f0_4=e2&d2      ;   || f1_4=a2&e2      ;   || f2_4= b2&a2      ; || f3_4= c2&b2      ; ||f4_4= d2&c2      ; 
f0_5=e2&d3^d3   ;   || f1_5=a2&e3^b3   ;   || f2_5= b2&a3^c3   ; || f3_5= c2&b3^b3   ; ||f4_5= d2&c3^c3   ;
f0_6=e3&d1      ;   || f1_6=a3&e1      ;   || f2_6= b3&a1      ; || f3_6= c3&b1      ; ||f4_6= d3&c1      ;
f0_7=e3&d2^d2   ;   || f1_7=a3&e2^b2   ;   || f2_7= b3&a2^c2   ; || f3_7= c3&b2^b2   ; ||f4_7= d3&c2^c2   ;
f0_8=e3&d3^a3   ;   || f1_8=a3&e3^e3   ;   || f2_8= b3&a3^a3   ; || f3_8= c3&b3^d3   ; ||f4_8= d3&c3^e3   ;

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include <omp.h>
#include <time.h>


//TableType
#define E3SameIntuple_d123a123     1  // this suits for  the case of de + a + d
#define A3SameIntuple_e123b123     2  // this suits for the case of  ae + b + e
#define B3SameIntuple_c123a123     3  // this suits for the case of  ab + a + c
#define C3SameIntuple_d123b123     4  // this suits for the case of  bc + b + d
#define D3SameIntuple_c123e123     5  // this suits for the case of  cd + c + e

#define NoNeedTable    0
// TableIndex
#define E3SameIntuple_d123a123_Index   3
#define A3SameIntuple_e123b123_Index   3
#define B3SameIntuple_c123a123_Index   3
#define C3SameIntuple_d123b123_Index   3
#define D3SameIntuple_c123e123_Index   3
#define  NoNeedTable_Index 0


//ExpressionType
#define  EType_eANDdXORa          1  //  this suits for  the case of de + a + d
#define  EType_aANDeXORb          2  //  this suits for the case of  ae + b + e
#define  EType_bANDaXORc          3  //  this suits for the case of  ab + a + c
#define  EType_bANDcXORd          4  //  this suits for the case of  bc + b + d
#define  EType_dANDcXORe          5  //  this suits for the case of  cd + c + e
#define  EType_NoDeal              0 
time_t              tt;
#define  CaseNumSet               1000 // The Storable maximum solution  number of each coordinate is set to be 1000, according to the test, 1000 is enough large.
#define  Var5Share3Space         32768
char FileName[30]="Gen2orderExpression.txt";
char f0BaseExpression[9][30]=
{{"f0[0]=e1&d1^d1    "},
 {"f0[1]=e1&d2^a2  "},
 {"f0[2]=e1&d3     "},	
 {"f0[3]=e2&d1^a1  "},	
 {"f0[4]=e2&d2     "},	
 {"f0[5]=e2&d3^d3  "},
 {"f2[6]=e3&d1     "},	
 {"f0[7]=e3&d2^d2  "},	
 {"f0[8]=e3&d3^a3  "}	
};



char f1BaseExpression[9][30]=
{{"f1[0]=a1&e1^b1  "},
 {"f1[1]=a1&e2^e2  "},
 {"f1[2]=a1&e3     "},	
 {"f1[3]=a2&e1^e1  "},	
 {"f1[4]=a2&e2     "},	
 {"f1[5]=a2&e3^b3  "},
 {"f1[6]=a3&e1     "},	
 {"f1[7]=a3&e2^b2  "},	
 {"f1[8]=a3&e3^e3  "}	
};


char f2BaseExpression[9][30]=
{{"f2[0]=b1&a1^c1   "},
 {"f2[1]=b1&a2^a2  "},
 {"f2[2]=b1&a3     "},	
 {"f2[3]=b2&a1^a1  "},	
 {"f2[4]=b2&a2     "},	
 {"f2[5]=b2&a3^c3  "},
 {"f2[6]=b3&a1     "},	
 {"f2[7]=b3&a2^c2  "},	
 {"f2[8]=b3&a3^a3  "}	
};

char f3BaseExpression[9][30]=
{{"f3[0]=c1&b1^b1  "},
 {"f3[1]=c1&b2^d2  "},
 {"f3[2]=c1&b3     "},	
 {"f3[3]=c2&b1^d1  "},	
 {"f3[4]=c2&b2     "},	
 {"f3[5]=c2&b3^b3  "},
 {"f3[6]=c3&b1     "},	
 {"f3[7]=c3&b2^b2  "},	
 {"f3[8]=c3&b3^d3  "}	
};

char f4BaseExpression[9][30]=
{{"f4[0]=d1&c1^c1   "},
 {"f4[1]=d1&c2^e2   "},
 {"f4[2]=d1&c3      "},	
 {"f4[3]=d2&c1^e1   "},	
 {"f4[4]=d2&c2      "},	
 {"f4[5]=d2&c3^c3   "},
 {"f4[6]=d3&c1      "},	
 {"f4[7]=d3&c2^c2   "},	
 {"f4[8]=d3&c3^e3   "}	
};




char f0AddItems[9][3][10]={
{"","^a1","^d1"},
{"","^a2","^d2"},
{"","^a3","^d3"},
{"","^a1","^d1"},
{"","^a2","^d2"},
{"","^a3","^d3"},
{"","^a1","^d1"},
{"","^a2","^d2"},
{"","^a3","^d3"}
};	


char f1AddItems[9][3][10]={
{"","^b1","^e1"},
{"","^b2","^e2"},
{"","^b3","^e3"},
{"","^b1","^e1"},
{"","^b2","^e2"},
{"","^b3","^e3"},
{"","^b1","^e1"},
{"","^b2","^e2"},
{"","^b3","^e3"}
};	


char f2AddItems[9][3][10]={
{"","^a1","^c1"},
{"","^a2","^c2"},
{"","^a3","^c3"},
{"","^a1","^c1"},
{"","^a2","^c2"},
{"","^a3","^c3"},
{"","^a1","^c1"},
{"","^a2","^c2"},
{"","^a3","^c3"}
};	


char f3AddItems[9][3][10]={
{"","^b1","^d1"},
{"","^b2","^d2"},
{"","^b3","^d3"},
{"","^b1","^d1"},
{"","^b2","^d2"},
{"","^b3","^d3"},
{"","^b1","^d1"},
{"","^b2","^d2"},
{"","^b3","^d3"}
};

char f4AddItems[9][3][10]={
{"","^c1","^e1"},
{"","^c2","^e2"},
{"","^c3","^e3"},
{"","^c1","^e1"},
{"","^c2","^e2"},
{"","^c3","^e3"},
{"","^c1","^e1"},
{"","^c2","^e2"},
{"","^c3","^e3"}
};



unsigned char  CheckCorrect(unsigned char*     F3To1UnMaskValue[5][3])
{
	unsigned char  abcde,a1b1c1d1e1,a2b2c2d2e2,a3b3c3d3e3;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;
	unsigned short	Masked_InputIndex,TypeIndex;
	
	unsigned char a,b,c,d,e,f0,f1,f2,f3,f4,f0m,f1m,f2m,f3m,f4m;
	
	
	Masked_InputIndex = 0;
	for (abcde=0;abcde<32;abcde++)
	{
        a=(abcde>>0)&0x1;
		b=(abcde>>1)&0x1;
	    c=(abcde>>2)&0x1;
	    d=(abcde>>3)&0x1;
		e=(abcde>>4)&0x1;
		
		f0=d&e ^ a ^ d  ;
		f1=a&e ^ b ^ e  ;
		f2=a&b ^ a ^ c  ;
		f3=b&c ^ b ^ d  ;
		f4=c&d ^ c ^ e  ;
				
			
		
	   for(a1b1c1d1e1=0;a1b1c1d1e1<32;a1b1c1d1e1++)
	    {
			a1=(a1b1c1d1e1>>0)&0x1;
			b1=(a1b1c1d1e1>>1)&0x1;
	    	c1=(a1b1c1d1e1>>2)&0x1;
	    	d1=(a1b1c1d1e1>>3)&0x1;
			e1=(a1b1c1d1e1>>4)&0x1;
			
	    	for(a2b2c2d2e2=0;a2b2c2d2e2<32;a2b2c2d2e2++)
	    	{
	    		a3b3c3d3e3=abcde^a1b1c1d1e1^a2b2c2d2e2;
				
				a2=(a2b2c2d2e2>>0)&0x01;
				b2=(a2b2c2d2e2>>1)&0x01;
                c2=(a2b2c2d2e2>>2)&0x01;
				d2=(a2b2c2d2e2>>3)&0x01; 
				e2=(a2b2c2d2e2>>4)&0x01;
				
				a3=(a3b3c3d3e3>>0)&0x01;
				b3=(a3b3c3d3e3>>1)&0x01;
                c3=(a3b3c3d3e3>>2)&0x01;
				d3=(a3b3c3d3e3>>3)&0x01;
				e3=(a3b3c3d3e3>>4)&0x01;
				
				
				f0m=F3To1UnMaskValue[0][0][Masked_InputIndex]^F3To1UnMaskValue[0][1][Masked_InputIndex]^F3To1UnMaskValue[0][2][Masked_InputIndex];
				
				f1m=F3To1UnMaskValue[1][0][Masked_InputIndex]^F3To1UnMaskValue[1][1][Masked_InputIndex]^F3To1UnMaskValue[1][2][Masked_InputIndex];
				
				f2m=F3To1UnMaskValue[2][0][Masked_InputIndex]^F3To1UnMaskValue[2][1][Masked_InputIndex]^F3To1UnMaskValue[2][2][Masked_InputIndex];
				
				f3m=F3To1UnMaskValue[3][0][Masked_InputIndex]^F3To1UnMaskValue[3][1][Masked_InputIndex]^F3To1UnMaskValue[3][2][Masked_InputIndex];
				f4m=F3To1UnMaskValue[4][0][Masked_InputIndex]^F3To1UnMaskValue[4][1][Masked_InputIndex]^F3To1UnMaskValue[4][2][Masked_InputIndex];
				
				if((f0!=f0m)|(f1!=f1m)|(f2!=f2m)|(f3!=f3m)|(f4!=f4m))
				{
					return 0;
					printf("correctness is not pass");	
				}
				
				
				
				Masked_InputIndex++;
		    }
	    }
    }
return 1;	
}

/* type1
TransLinearItem_e3Sd123a123:   this   table  siuts  for  de + a + d 
        type[0]    type[1]     type[2]  
comp_0     0         a1           d1    
comp_1     0         a2           d2    
comp_2     0         a3           d3    
----------------------------------------
comp_3     0         a1           d1    
comp_4     0         a2           d2    
comp_5     0         a3           d3    
----------------------------------------
comp_6     0         a1           d1    
comp_7     0         a2           d2    
comp_8     0         a3           d3    
----------------------------------------

TransLinearItem[][][]=(a1<<14)| (a2<<13)|(a3<<12)|(d1<<5)|(d2<<4)|(d3<<3)|(e1<<2)|(e2<<1)|(e3<<0); e.g. if a1=1：TransLinearItem[][][]=0x4000, then this means that  the  item of "a1"  will used in the transformation  
*/

void TransLinearItem_e3Sd123a123(unsigned char CoordIndex,   unsigned short  TransLinearItem[5][9][3],unsigned char*   XorValue[5][9][3]) 
 {
	unsigned short	Masked_InputIndex,i;
	unsigned char  abcde,a1b1c1d1e1,a2b2c2d2e2,a3b3c3d3e3,CompIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;

	 // the linear items  in the all possible composed items in our bebuiled Table.	
	 
	     for(CompIndex=0;CompIndex<9;CompIndex++)
	   {
		   TransLinearItem[CoordIndex][CompIndex][0]=0; // type[0] for comp0----8
		   
		   if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
			  { 
			   TransLinearItem[CoordIndex][CompIndex][1]=0x4000  ; //a1   type[1]   for comp0  comp3   comp6
		       TransLinearItem[CoordIndex][CompIndex][2]= 0x0020  ; //d1  type[2]   for comp0  comp3   comp6
			  } 
		  else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x2000   ; // a2  type[1]   for comp1  comp4   comp7
		       TransLinearItem[CoordIndex][CompIndex][2]=0x0010   ; //d2  type[2]   for comp1  comp4   comp7
              } 
		  else 
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x1000;//a3  type[1]   for comp2  comp5   comp8
		       TransLinearItem[CoordIndex][CompIndex][2]=0x0008;//d3  type[2]   for comp2  comp5   comp8
               } 
        
	   }
		
//the XOR values of  linear items  in the all possible composed items.		

	   Masked_InputIndex=0;
	for (abcde=0;abcde<32;abcde++)
	{
	   for(a1b1c1d1e1=0;a1b1c1d1e1<32;a1b1c1d1e1++)
	    {
			a1=(a1b1c1d1e1>>0)&0x1;
			b1=(a1b1c1d1e1>>1)&0x1;
	    	c1=(a1b1c1d1e1>>2)&0x1;
	    	d1=(a1b1c1d1e1>>3)&0x1;
			e1=(a1b1c1d1e1>>4)&0x1;
			
			
	    	for(a2b2c2d2e2=0;a2b2c2d2e2<32;a2b2c2d2e2++)
	    	{
	    		a3b3c3d3e3=abcde^a1b1c1d1e1^a2b2c2d2e2;
				
				a2=(a2b2c2d2e2>>0)&0x01;
				b2=(a2b2c2d2e2>>1)&0x01;
                c2=(a2b2c2d2e2>>2)&0x01;
				d2=(a2b2c2d2e2>>3)&0x01; 
				e2=(a2b2c2d2e2>>4)&0x01;
				
				a3=(a3b3c3d3e3>>0)&0x01;
				b3=(a3b3c3d3e3>>1)&0x01;
                c3=(a3b3c3d3e3>>2)&0x01;
				d3=(a3b3c3d3e3>>3)&0x01;
				e3=(a3b3c3d3e3>>4)&0x01;
				
                for(CompIndex=0;CompIndex<9;CompIndex++)
	               {
	            	  XorValue[CoordIndex][CompIndex][0][Masked_InputIndex]=0; // type[0] for comp0----8
	            	   
	            	if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=a1  ; //a1   type[1]   for comp0  comp3   comp6
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]= d1  ; //d1  type[2]   for comp0  comp3   comp6
	            		  } 
	            	else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=a2  ; // a2  type[1]   for comp1  comp4   comp7
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=d2    ; //d2  type[2]   for comp1  comp4   comp7
	            	       } 
	            	else 
	            		   {
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=a3;//a3  type[1]   for comp2  comp5   comp8
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=d3;//d3  type[2]   for comp2  comp5   comp8
	            	       } 
 
	               }
				Masked_InputIndex++;
			}
		}
	}

 }


 /*type2
TransLinearItem_a3Se123b123:   this   table  siuts  for  ae + b + e

        type[0]    type[1]     type[2]  
comp_0     0         b1           e1    
comp_1     0         b2           e2    
comp_2     0         b3           e3    
----------------------------------------
comp_3     0         b1           e1    
comp_4     0         b2           e2    
comp_5     0         b3           e3    
----------------------------------------
comp_6     0         b1           e1    
comp_7     0         b2           e2    
comp_8     0         b3           e3    
----------------------------------------

TransLinearItem[][][]=(a1<<14)| (a2<<13)|(a3<<12)|(b1<<11)|(b2<<10)|(b3<<9)|(e1<<2)|(e2<<1)|(e3<<0); e.g. if b1=1：TransLinearItem[][][]=0x0800, then this means that  the  item of "b1"  will used in the transformation  
*/

void TransLinearItem_a3Se123b123(unsigned char CoordIndex,   unsigned short  TransLinearItem[5][9][3],unsigned char*   XorValue[5][9][3]) 
 {
	unsigned short	Masked_InputIndex,i;
	unsigned char  abcde,a1b1c1d1e1,a2b2c2d2e2,a3b3c3d3e3,CompIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;

	 // the linear items  in the all possible composed items in our bebuiled Table.	
	 
	     for(CompIndex=0;CompIndex<9;CompIndex++)
	   {
		   TransLinearItem[CoordIndex][CompIndex][0]=0; // type[0] for comp0----8
		   
		   if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x0800  ; //b1   type[1]   for comp0  comp3   comp6
		       TransLinearItem[CoordIndex][CompIndex][2]= 0x0004  ; //e1  type[2]   for comp0  comp3   comp6
			  } 
		  else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x0400   ; // b2  type[1]   for comp1  comp4   comp7
		       TransLinearItem[CoordIndex][CompIndex][2]=0x0002   ; //e2  type[2]   for comp1  comp4   comp7
              } 
		  else 
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x0200;//b3  type[1]   for comp2  comp5   comp8
		       TransLinearItem[CoordIndex][CompIndex][2]=0x0001;//e3  type[2]   for comp2  comp5   comp8
               } 

	   }
		
//the XOR values of  linear items  in the all possible composed items.		

	   Masked_InputIndex=0;
	for (abcde=0;abcde<32;abcde++)
	{
	   for(a1b1c1d1e1=0;a1b1c1d1e1<32;a1b1c1d1e1++)
	    {
			a1=(a1b1c1d1e1>>0)&0x1;
			b1=(a1b1c1d1e1>>1)&0x1;
	    	c1=(a1b1c1d1e1>>2)&0x1;
	    	d1=(a1b1c1d1e1>>3)&0x1;
			e1=(a1b1c1d1e1>>4)&0x1;
			
			
	    	for(a2b2c2d2e2=0;a2b2c2d2e2<32;a2b2c2d2e2++)
	    	{
	    		a3b3c3d3e3=abcde^a1b1c1d1e1^a2b2c2d2e2;
				
				a2=(a2b2c2d2e2>>0)&0x01;
				b2=(a2b2c2d2e2>>1)&0x01;
                c2=(a2b2c2d2e2>>2)&0x01;
				d2=(a2b2c2d2e2>>3)&0x01; 
				e2=(a2b2c2d2e2>>4)&0x01;
				
				a3=(a3b3c3d3e3>>0)&0x01;
				b3=(a3b3c3d3e3>>1)&0x01;
                c3=(a3b3c3d3e3>>2)&0x01;
				d3=(a3b3c3d3e3>>3)&0x01;
				e3=(a3b3c3d3e3>>4)&0x01;
				
                for(CompIndex=0;CompIndex<9;CompIndex++)
	               {
	            	  XorValue[CoordIndex][CompIndex][0][Masked_InputIndex]=0; // type[0] for comp0----8
	            	   
	            	if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=b1  ; //b1   type[1]   for comp0  comp3   comp6
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]= e1  ; //e1  type[2]   for comp0  comp3   comp6
	            		  } 
	            	else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=b2  ; // b2  type[1]   for comp1  comp4   comp7
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=e2    ; //e2  type[2]   for comp1  comp4   comp7
	            	       } 
	            	else 
	            		   {
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=b3;//b3  type[1]   for comp2  comp5   comp8
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=e3;//e3  type[2]   for comp2  comp5   comp8
	            	       } 

	               }
				Masked_InputIndex++;
			}
		}
	}

 }

 /*type3
 TransLinearItem_b3Sc123a123:   this   table  siuts  for  ab + a + c

        type[0]    type[1]     type[2]  
comp_0     0         a1           c1    
comp_1     0         a2           c2    
comp_2     0         a3           c3    
----------------------------------------
comp_3     0         a1           c1    
comp_4     0         a2           c2    
comp_5     0         a3           c3    
----------------------------------------
comp_6     0         a1           c1    
comp_7     0         a2           c2    
comp_8     0         a3           c3    
----------------------------------------

TransLinearItem[][][]=(a1<<14)| (a2<<13)|(a3<<12)|(b1<<11)|(b2<<10)|(b3<<9)|(c1<<8)|(c2<<7)|(c3<<6); e.g. if b1=1,TransLinearItem[][][]=0x0800, then this means that  the  item of "b1"  will used in the transformation  
*/

void TransLinearItem_b3Sc123a123(unsigned char CoordIndex,   unsigned short  TransLinearItem[5][9][3],unsigned char*   XorValue[5][9][3]) 
 {
	unsigned short	Masked_InputIndex,i;
	unsigned char  abcde,a1b1c1d1e1,a2b2c2d2e2,a3b3c3d3e3,CompIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;

	 // the linear items  in the all possible composed items in our bebuiled Table.	
	 
	     for(CompIndex=0;CompIndex<9;CompIndex++)
	   {
		   TransLinearItem[CoordIndex][CompIndex][0]=0; // type[0] for comp0----8
		   
		   if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x4000  ; //a1 type[1]   for comp0  comp3   comp6
		       TransLinearItem[CoordIndex][CompIndex][2]= 0x0100  ; //c1  type[2]   for comp0  comp3   comp6
			  } 
		  else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x2000  ; //a2 type[1]   for comp1  comp4   comp7
		       TransLinearItem[CoordIndex][CompIndex][2]=0x0080   ; //c2  type[2]   for comp1  comp4   comp7
              } 
		  else 
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]= 0x1000  ;//a3 type[1]for comp2  comp5   comp8
		       TransLinearItem[CoordIndex][CompIndex][2]=0x0040;//c3  type[2]   for comp2  comp5   comp8
               } 

	   }
		
//the XOR values of  linear items  in the all possible composed items.		

	   Masked_InputIndex=0;
	for (abcde=0;abcde<32;abcde++)
	{
	   for(a1b1c1d1e1=0;a1b1c1d1e1<32;a1b1c1d1e1++)
	    {
			a1=(a1b1c1d1e1>>0)&0x1;
			b1=(a1b1c1d1e1>>1)&0x1;
	    	c1=(a1b1c1d1e1>>2)&0x1;
	    	d1=(a1b1c1d1e1>>3)&0x1;
			e1=(a1b1c1d1e1>>4)&0x1;
			
			
	    	for(a2b2c2d2e2=0;a2b2c2d2e2<32;a2b2c2d2e2++)
	    	{
	    		a3b3c3d3e3=abcde^a1b1c1d1e1^a2b2c2d2e2;
				
				a2=(a2b2c2d2e2>>0)&0x01;
				b2=(a2b2c2d2e2>>1)&0x01;
                c2=(a2b2c2d2e2>>2)&0x01;
				d2=(a2b2c2d2e2>>3)&0x01; 
				e2=(a2b2c2d2e2>>4)&0x01;
				
				a3=(a3b3c3d3e3>>0)&0x01;
				b3=(a3b3c3d3e3>>1)&0x01;
                c3=(a3b3c3d3e3>>2)&0x01;
				d3=(a3b3c3d3e3>>3)&0x01;
				e3=(a3b3c3d3e3>>4)&0x01;
				
                for(CompIndex=0;CompIndex<9;CompIndex++)
	               {
	            	  XorValue[CoordIndex][CompIndex][0][Masked_InputIndex]=0; // type[0] for comp0----8
	            	   
	            	if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=a1  ; //a1   type[1]   for comp0  comp3   comp6
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]= c1  ; //c1  type[2]   for comp0  comp3   comp6
	            		  } 
	            	else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=a2  ; // a2  type[1]   for comp1  comp4   comp7
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=c2    ; //c2  type[2]   for comp1  comp4   comp7
	            	       } 
	            	else 
	            		   {
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=a3;//a3  type[1]   for comp2  comp5   comp8
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=c3;//c3  type[2]   for comp2  comp5   comp8
	            	       } 
 
	               }
				Masked_InputIndex++;
			}
		}
	}

 } 
 

 

 
 
 /* type4
TransLinearItem_c3Sd123b123:   this   table  siuts  for  bc + b + d


        type[0]    type[1]     type[2]  
comp_0     0         b1           d1    
comp_1     0         b2           d2    
comp_2     0         b3           d3    
----------------------------------------
comp_3     0         b1           d1    
comp_4     0         b2           d2    
comp_5     0         b3           d3    
----------------------------------------
comp_6     0         b1           d1    
comp_7     0         b2           d2    
comp_8     0         b3           d3    
----------------------------------------

TransLinearItem[][][]=(b1<<11)|(b2<<10)|(b3<<9)|(c1<<8)|(c2<<7)|(c3<<6)|(d1<<5)|(d2<<4)|(d3<<3); e.g. if b1=1,TransLinearItem[][][]=0x0800, then this means that  the  item of "b1"  will used in the transformation  
*/

void TransLinearItem_c3Sd123b123(unsigned char CoordIndex,   unsigned short  TransLinearItem[5][9][3],unsigned char*   XorValue[5][9][3]) 
 {
	unsigned short	Masked_InputIndex,i;
	unsigned char  abcde,a1b1c1d1e1,a2b2c2d2e2,a3b3c3d3e3,CompIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;

	 // the linear items  in the all possible composed items in our bebuiled Table.	
	 
	     for(CompIndex=0;CompIndex<9;CompIndex++)
	   {
		   TransLinearItem[CoordIndex][CompIndex][0]=0; // type[0] for comp0----8
		   
		   if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x0800  ; //b1   type[1]   for comp0  comp3   comp6
		       TransLinearItem[CoordIndex][CompIndex][2]= 0x0020  ; //d1  type[2]   for comp0  comp3   comp6
			  } 
		  else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x0400   ; // b2  type[1]   for comp1  comp4   comp7
		       TransLinearItem[CoordIndex][CompIndex][2]=0x0010   ; //d2  type[2]   for comp1  comp4   comp7
              } 
		  else 
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x0200;//b3  type[1]   for comp2  comp5   comp8
		       TransLinearItem[CoordIndex][CompIndex][2]=0x0008;//d3  type[2]   for comp2  comp5   comp8
               } 

	   }
		
//the XOR values of  linear items  in the all possible composed items.		

	   Masked_InputIndex=0;
	for (abcde=0;abcde<32;abcde++)
	{
	   for(a1b1c1d1e1=0;a1b1c1d1e1<32;a1b1c1d1e1++)
	    {
			a1=(a1b1c1d1e1>>0)&0x1;
			b1=(a1b1c1d1e1>>1)&0x1;
	    	c1=(a1b1c1d1e1>>2)&0x1;
	    	d1=(a1b1c1d1e1>>3)&0x1;
			e1=(a1b1c1d1e1>>4)&0x1;
			
			
	    	for(a2b2c2d2e2=0;a2b2c2d2e2<32;a2b2c2d2e2++)
	    	{
	    		a3b3c3d3e3=abcde^a1b1c1d1e1^a2b2c2d2e2;
				
				a2=(a2b2c2d2e2>>0)&0x01;
				b2=(a2b2c2d2e2>>1)&0x01;
                c2=(a2b2c2d2e2>>2)&0x01;
				d2=(a2b2c2d2e2>>3)&0x01; 
				e2=(a2b2c2d2e2>>4)&0x01;
				
				a3=(a3b3c3d3e3>>0)&0x01;
				b3=(a3b3c3d3e3>>1)&0x01;
                c3=(a3b3c3d3e3>>2)&0x01;
				d3=(a3b3c3d3e3>>3)&0x01;
				e3=(a3b3c3d3e3>>4)&0x01;
				
                for(CompIndex=0;CompIndex<9;CompIndex++)
	               {
	            	  XorValue[CoordIndex][CompIndex][0][Masked_InputIndex]=0; // type[0] for comp0----8
	            	   
	            	if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=b1  ; //b1   type[1]   for comp0  comp3   comp6
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]= d1  ; //d1  type[2]   for comp0  comp3   comp6
	            		  } 
	            	else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=b2  ; // b2  type[1]   for comp1  comp4   comp7
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=d2    ; //d2  type[2]   for comp1  comp4   comp7
	            	       } 
	            	else 
	            		   {
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=b3;//b3  type[1]   for comp2  comp5   comp8
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=d3;//d3  type[2]   for comp2  comp5   comp8
	            	       } 
 
	               }
				Masked_InputIndex++;
			}
		}
	}

 }  
 
 /*type5
TransLinearItem_d3Sc123e123:   this   table  siuts  for cd + c + e
        type[0]    type[1]     type[2] 
comp_0     0         c1           e1   
comp_1     0         c2           e2   
comp_2     0         c3           e3   
--------------------------------------
comp_3     0         c1           e1   
comp_4     0         c2           e2   
comp_5     0         c3           e3   
--------------------------------------
comp_6     0         c1           e1   
comp_7     0         c2           e2   
comp_8     0         c3           e3   
---------------------------------------

TransLinearItem[][][]=(c1<<8)|(c2<<7)|(c3<<6)|(d1<<5)|(d2<<4)|(d3<<3)|(e1<<2)|(e2<<1)|(e3<<0); e.g. if c1=1：TransLinearItem[][][]=0x0100, then this means that  the  item of "c1"  will used in the transformation  
*/

void TransLinearItem_d3Sc123e123(unsigned char CoordIndex,   unsigned short  TransLinearItem[5][9][3],unsigned char*   XorValue[5][9][3]) 
 {
	unsigned short	Masked_InputIndex,i;
	unsigned char  abcde,a1b1c1d1e1,a2b2c2d2e2,a3b3c3d3e3,CompIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;

	 // the linear items  in the all possible composed items in our bebuiled Table.	
	 
	     for(CompIndex=0;CompIndex<9;CompIndex++)
	   {
		   TransLinearItem[CoordIndex][CompIndex][0]=0; // type[0] for comp0----8
		   
		   if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
			  { 
			   TransLinearItem[CoordIndex][CompIndex][1]=0x0100  ;   //c1   type[1]   for comp0  comp3   comp6
		       TransLinearItem[CoordIndex][CompIndex][2]=0x0004   ; //e1  type[2]   for comp0  comp3   comp6
			  } 
		  else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
			  { 
			   TransLinearItem[CoordIndex][CompIndex][1]= 0x0080; // c2  type[1]   for comp1  comp4   comp7
		       TransLinearItem[CoordIndex][CompIndex][2]=0x0002; //e2  type[2]   for comp1  comp4   comp7
              } 
		  else 
			  { 
			   TransLinearItem[CoordIndex][CompIndex][1]=0x0040; //c3  type[1]   for comp2  comp5   comp8
		       TransLinearItem[CoordIndex][CompIndex][2]=0x0001;//e3  type[2]   for comp2  comp5   comp8
               } 

	   }
		
//the XOR values of  linear items  in the all possible composed items.		

	   Masked_InputIndex=0;
	for (abcde=0;abcde<32;abcde++)
	{
	   for(a1b1c1d1e1=0;a1b1c1d1e1<32;a1b1c1d1e1++)
	    {
			a1=(a1b1c1d1e1>>0)&0x1;
			b1=(a1b1c1d1e1>>1)&0x1;
	    	c1=(a1b1c1d1e1>>2)&0x1;
	    	d1=(a1b1c1d1e1>>3)&0x1;
			e1=(a1b1c1d1e1>>4)&0x1;
			
			
	    	for(a2b2c2d2e2=0;a2b2c2d2e2<32;a2b2c2d2e2++)
	    	{
	    		a3b3c3d3e3=abcde^a1b1c1d1e1^a2b2c2d2e2;
				
				a2=(a2b2c2d2e2>>0)&0x01;
				b2=(a2b2c2d2e2>>1)&0x01;
                c2=(a2b2c2d2e2>>2)&0x01;
				d2=(a2b2c2d2e2>>3)&0x01; 
				e2=(a2b2c2d2e2>>4)&0x01;
				
				a3=(a3b3c3d3e3>>0)&0x01;
				b3=(a3b3c3d3e3>>1)&0x01;
                c3=(a3b3c3d3e3>>2)&0x01;
				d3=(a3b3c3d3e3>>3)&0x01;
				e3=(a3b3c3d3e3>>4)&0x01;
				
                for(CompIndex=0;CompIndex<9;CompIndex++)
	               {
	            	  XorValue[CoordIndex][CompIndex][0][Masked_InputIndex]=0; // type[0] for comp0----8
	            	   
	            	if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=c1  ; //c1   type[1]   for comp0  comp3   comp6
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=e1  ; //e1  type[2]   for comp0  comp3   comp6
	            		  } 
	            	else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=c2  ;  //c2  type[1]   for comp1  comp4   comp7
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=e2  ;  //e2  type[2]   for comp1  comp4   comp7
	            	       } 
	            	else 
	            		   {
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=c3;//c3  type[1]   for comp2  comp5   comp8
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=e3;//e3  type[2]   for comp2  comp5   comp8
	            	       } 
 
	               }
				Masked_InputIndex++;
			}
		}
	}

 } 
 
void NotTrans(unsigned char CoordIndex,   unsigned short  TransLinearItem[5][9][3],unsigned char*   XorValue[5][9][3]) 
 {
	 unsigned short	Masked_InputIndex,i;
	 // the linear items  in the all possible composed items in our bebuiled Table.	
	         
		//component 0-8  Type 0
		for(i=0;i<9;i++)
		{
		TransLinearItem[CoordIndex][i][0]=0;	
		}

 }


//InitLinearItem[CoordIndex][]=(a1<<11)| (a2<<10)|(a3<<9)|(b1<<8)| (b2<<7)|(b3<<6)|(c1<<5)|(c2<<4)|(c3<<3)|(d1<<2)|(d2<<1)|(d3<<0)

void MakeSearchDisUnifTable(unsigned short  InitLinearItem[5][9],unsigned short  TransLinearItem[5][9][3],unsigned char*   XorValue[5][9][3], unsigned char TableType[5]
)// InitLinearItem1[CompIndex]:CompIndex:0-8;  TransLinearItem[CompIndex][Type]:Type:0-7, XorValue[CompIndex][Type][Masked_InputIndex]: Masked_InputIndex:0-(Var5Share3Space-1).
{

	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;
	unsigned char   CoordIndex,CompIndex;
	unsigned short  InitLinearItem1[5][9];
	unsigned char   ShiftNum;
	unsigned short  TshareValue;
	
	unsigned char  f0[9], f1[9],f2[9],f3[9],f4[9];
	
	
	
    for(CoordIndex=0;CoordIndex<5;CoordIndex++)
    {
		for(CompIndex=0;CompIndex<9;CompIndex++)
		{
			InitLinearItem[CoordIndex][CompIndex]=0;
		}
	}


	for(ShiftNum=0;ShiftNum<15;ShiftNum++)
	{
		TshareValue=1<<ShiftNum;
		a1=(TshareValue>>14)&1; a2=(TshareValue>>13)&1; a3=(TshareValue>>12)&1;
		b1=(TshareValue>>11)&1; b2=(TshareValue>>10)&1; b3=(TshareValue>>9)&1;
		c1=(TshareValue>>8)&1; c2=(TshareValue>>7)&1; c3=(TshareValue>>6)&1;
		d1=(TshareValue>>5)&1; d2=(TshareValue>>4)&1; d3=(TshareValue>>3)&1;
		e1=(TshareValue>>2)&1; e2=(TshareValue>>1)&1; e3=(TshareValue>>0)&1;
         
	// 3  need to  change  with different implementations.the linear items in the  9 initail components 		

		f0[0]=e1&d1^d1   ;
		f0[1]=e1&d2^a2   ;
		f0[2]=e1&d3      ;
		f0[3]=e2&d1^a1   ;
		f0[4]=e2&d2      ;  //#case2
		f0[5]=e2&d3^d3   ;
		f0[6]=e3&d1      ;
		f0[7]=e3&d2^d2   ;
		f0[8]=e3&d3^a3   ;
       
        f1[0]=a1&e1^b1    ;
        f1[1]=a1&e2^e2    ;
        f1[2]=a1&e3       ;
        f1[3]=a2&e1^e1    ;
        f1[4]=a2&e2       ;
        f1[5]=a2&e3^b3    ;
        f1[6]=a3&e1       ;
        f1[7]=a3&e2^b2    ;
        f1[8]=a3&e3^e3    ;

		f2[0]= b1&a1^c1   ;
		f2[1]= b1&a2^a2   ;
		f2[2]= b1&a3      ;
		f2[3]= b2&a1^a1   ;
		f2[4]= b2&a2      ;
		f2[5]= b2&a3^c3   ;
		f2[6]= b3&a1      ;
		f2[7]= b3&a2^c2   ;
		f2[8]= b3&a3^a3   ;

		
		f3[0]= c1&b1^b1  ;
		f3[1]= c1&b2^d2;
		f3[2]= c1&b3   ;
		f3[3]= c2&b1^d1;
		f3[4]= c2&b2     ;
		f3[5]= c2&b3^b3;
		f3[6]= c3&b1   ;
		f3[7]= c3&b2^b2;
		f3[8]= c3&b3^d3  ;
		
		f4[0]= d1&c1^c1   ;  
		f4[1]= d1&c2^e2   ;  
		f4[2]= d1&c3      ;  
		f4[3]= d2&c1^e1   ;  
		f4[4]= d2&c2      ;  
		f4[5]= d2&c3^c3   ;  
		f4[6]= d3&c1      ;  
		f4[7]= d3&c2^c2   ;  
		f4[8]= d3&c3^e3   ;  	
		
		for(CompIndex=0;CompIndex<9;CompIndex++)
		{
		  if(f0[CompIndex])
			 InitLinearItem[0][CompIndex] |=TshareValue;
		 if(f1[CompIndex])
			 InitLinearItem[1][CompIndex] |=TshareValue;
		  if(f2[CompIndex])
			 InitLinearItem[2][CompIndex] |=TshareValue;
		 if(f3[CompIndex])
			 InitLinearItem[3][CompIndex] |=TshareValue;
		 if(f4[CompIndex])
			 InitLinearItem[4][CompIndex] |=TshareValue;
		}
	}

   for( CoordIndex=0;CoordIndex<5;CoordIndex++)
		{
			if(TableType[CoordIndex]==E3SameIntuple_d123a123)
			   TransLinearItem_e3Sd123a123(CoordIndex,   TransLinearItem, XorValue);
			else if(TableType[CoordIndex]==A3SameIntuple_e123b123)
			    TransLinearItem_a3Se123b123(CoordIndex,   TransLinearItem, XorValue);
			else if(TableType[CoordIndex]==B3SameIntuple_c123a123)
			    TransLinearItem_b3Sc123a123(CoordIndex,   TransLinearItem, XorValue);
			else if(TableType[CoordIndex]==C3SameIntuple_d123b123)
				TransLinearItem_c3Sd123b123(CoordIndex,   TransLinearItem, XorValue);
			else if(TableType[CoordIndex]==D3SameIntuple_c123e123)	
			    TransLinearItem_d3Sc123e123(CoordIndex,   TransLinearItem, XorValue);
			else
				NotTrans(CoordIndex,   TransLinearItem, XorValue);
			
		}

}

/*
Type1
d&e ^ a ^ d
*/
void InputTableIndexGen_NLedLa( unsigned char  Type[5][9], unsigned char CoordIndex, unsigned short  InitTranComLinearItem[5][9], unsigned char*   InputTableIndex[5][9],unsigned short  InitLinearItem[5][9],unsigned short  TransLinearItem[5][9][3])
{	
	unsigned int  CompIndex, InputMask,OutShare,i;
	unsigned char  abcde,a1b1c1d1e1,a2b2c2d2e2,a3b3c3d3e3;
	unsigned short	Masked_InputIndex,TypeIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;
    
   

	for(CompIndex=0;CompIndex<9;CompIndex++)	
	{
		InitTranComLinearItem[CoordIndex][CompIndex]=InitLinearItem[CoordIndex][CompIndex]^TransLinearItem[CoordIndex][CompIndex][Type[CoordIndex][CompIndex]];
		
	}

    Masked_InputIndex = 0;
	for (abcde=0;abcde<32;abcde++)
	{
	   for(a1b1c1d1e1=0;a1b1c1d1e1<32;a1b1c1d1e1++)
	    {
			a1=(a1b1c1d1e1>>0)&0x1;
			b1=(a1b1c1d1e1>>1)&0x1;
	    	c1=(a1b1c1d1e1>>2)&0x1;
	    	d1=(a1b1c1d1e1>>3)&0x1;
			e1=(a1b1c1d1e1>>4)&0x1;
			
			
	    	for(a2b2c2d2e2=0;a2b2c2d2e2<32;a2b2c2d2e2++)
	    	{
	    		a3b3c3d3e3=abcde^a1b1c1d1e1^a2b2c2d2e2;
				
				a2=(a2b2c2d2e2>>0)&0x01;
				b2=(a2b2c2d2e2>>1)&0x01;
                c2=(a2b2c2d2e2>>2)&0x01;
				d2=(a2b2c2d2e2>>3)&0x01; 
				e2=(a2b2c2d2e2>>4)&0x01;
				
				a3=(a3b3c3d3e3>>0)&0x01;
				b3=(a3b3c3d3e3>>1)&0x01;
                c3=(a3b3c3d3e3>>2)&0x01;
				d3=(a3b3c3d3e3>>3)&0x01;
				e3=(a3b3c3d3e3>>4)&0x01;
				//---component 0
                if ((InitTranComLinearItem[CoordIndex][0] &0x7000)==0x3ff0)
				     InputTableIndex[CoordIndex][0][Masked_InputIndex]=(a1<<2)|(d1<<1)|(e1<<0);
				 else 
					 InputTableIndex[CoordIndex][0][Masked_InputIndex]=(d1<<1)|(e1<<0); 
					
				//---component 1
				 if ((InitTranComLinearItem[CoordIndex][1] &0x7000)==0x2000)
				     InputTableIndex[CoordIndex][1][Masked_InputIndex]=(a2<<2)|(d2<<1)|(e1<<0); 
				 
                else
                    InputTableIndex[CoordIndex][1][Masked_InputIndex]=(d2<<1)|(e1<<0); 	
				//---component 2 
				 if ((InitTranComLinearItem[CoordIndex][2] &0x7000)==0x1000)
				     InputTableIndex[CoordIndex][2][Masked_InputIndex]=(a3<<2)|(d3<<1)|(e1<<0);  
				else
					 InputTableIndex[CoordIndex][2][Masked_InputIndex]=(d3<<1)|(e1<<0);  
				 
                //---component 3
				if ((InitTranComLinearItem[CoordIndex][3] &0x7000)==0x3ff0)
				     InputTableIndex[CoordIndex][3][Masked_InputIndex]=(a1<<2)|(d1<<1)|(e2<<0);

				else
					InputTableIndex[CoordIndex][3][Masked_InputIndex]=(d1<<1)|(e2<<0); 
				 
				 //---component 4

                if ((InitTranComLinearItem[CoordIndex][4] &0x7000)==0x2000)
				     InputTableIndex[CoordIndex][4][Masked_InputIndex]=(a2<<2)|(d2<<1)|(e2<<0); 
		
				 else
					InputTableIndex[CoordIndex][4][Masked_InputIndex]=(d2<<1)|(e2<<0); 
				//---component 5
			     if ((InitTranComLinearItem[CoordIndex][5] &0x7000)==0x1000)
				     InputTableIndex[CoordIndex][5][Masked_InputIndex]=(a3<<2)|(d3<<1)|(e2<<0);
				else 
					InputTableIndex[CoordIndex][5][Masked_InputIndex]=(d3<<1)|(e2<<0);

                //---component 6
				if ((InitTranComLinearItem[CoordIndex][6] &0x7000)==0x3ff0)
				     InputTableIndex[CoordIndex][6][Masked_InputIndex]=(a1<<2)|(d1<<1)|(e3<<0);

				else 
          			InputTableIndex[CoordIndex][6][Masked_InputIndex]=(d1<<1)|(e3<<0);		
				 //---component 7
                if ((InitTranComLinearItem[CoordIndex][7] &0x7000)==0x2000)
				     InputTableIndex[CoordIndex][7][Masked_InputIndex]=(a2<<2)|(d2<<1)|(e3<<0); 

				else 
          			InputTableIndex[CoordIndex][7][Masked_InputIndex]=(d2<<1)|(e3<<0);
                //---component 8
			    if ((InitTranComLinearItem[CoordIndex][8] &0x7000)==0x1000)
				     InputTableIndex[CoordIndex][8][Masked_InputIndex]=(a3<<2)|(d3<<1)|(e3<<0);
				else 
          			InputTableIndex[CoordIndex][8][Masked_InputIndex]=(d3<<1)|(e3<<0);
          			
          			Masked_InputIndex++;

			}
		}
	}

}



/*type2
a&e ^ b ^ e
*/
void InputTableIndexGen_NLaeLb( unsigned char  Type[5][9], unsigned char CoordIndex, unsigned short  InitTranComLinearItem[5][9], unsigned char*   InputTableIndex[5][9],unsigned short  InitLinearItem[5][9],unsigned short  TransLinearItem[5][9][3])
{	
	unsigned int  CompIndex, InputMask,OutShare,i;
	unsigned char  abcde,a1b1c1d1e1,a2b2c2d2e2,a3b3c3d3e3;
	unsigned short	Masked_InputIndex,TypeIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;
    
   

	for(CompIndex=0;CompIndex<9;CompIndex++)	
	{
		InitTranComLinearItem[CoordIndex][CompIndex]=InitLinearItem[CoordIndex][CompIndex]^TransLinearItem[CoordIndex][CompIndex][Type[CoordIndex][CompIndex]];
		
	}

    Masked_InputIndex = 0;
	for (abcde=0;abcde<32;abcde++)
	{
	   for(a1b1c1d1e1=0;a1b1c1d1e1<32;a1b1c1d1e1++)
	    {
			a1=(a1b1c1d1e1>>0)&0x1;
			b1=(a1b1c1d1e1>>1)&0x1;
	    	c1=(a1b1c1d1e1>>2)&0x1;
	    	d1=(a1b1c1d1e1>>3)&0x1;
			e1=(a1b1c1d1e1>>4)&0x1;
			
			
	    	for(a2b2c2d2e2=0;a2b2c2d2e2<32;a2b2c2d2e2++)
	    	{
	    		a3b3c3d3e3=abcde^a1b1c1d1e1^a2b2c2d2e2;
				
				a2=(a2b2c2d2e2>>0)&0x01;
				b2=(a2b2c2d2e2>>1)&0x01;
                c2=(a2b2c2d2e2>>2)&0x01;
				d2=(a2b2c2d2e2>>3)&0x01; 
				e2=(a2b2c2d2e2>>4)&0x01;
				
				a3=(a3b3c3d3e3>>0)&0x01;
				b3=(a3b3c3d3e3>>1)&0x01;
                c3=(a3b3c3d3e3>>2)&0x01;
				d3=(a3b3c3d3e3>>3)&0x01;
				e3=(a3b3c3d3e3>>4)&0x01;
				//---component 0
                if ((InitTranComLinearItem[CoordIndex][0] &0x0e00)==0x0800)
				     InputTableIndex[CoordIndex][0][Masked_InputIndex]=(b1<<2)|(e1<<1)|(a1<<0);
				 else 
					 InputTableIndex[CoordIndex][0][Masked_InputIndex]=(e1<<1)|(a1<<0); 
					
				//---component 1
				 if ((InitTranComLinearItem[CoordIndex][1] &0x0e00)==0x0400)
				     InputTableIndex[CoordIndex][1][Masked_InputIndex]=(b2<<2)|(e2<<1)|(a1<<0); 
				 
                else
                    InputTableIndex[CoordIndex][1][Masked_InputIndex]=(e2<<1)|(a1<<0); 	
								
				//---component 2 
				 if ((InitTranComLinearItem[CoordIndex][2] &0x0e00)==0x0200)
				     InputTableIndex[CoordIndex][2][Masked_InputIndex]=(b3<<2)|(e3<<1)|(a1<<0);  
				else
					 InputTableIndex[CoordIndex][2][Masked_InputIndex]=(e3<<1)|(a1<<0);  
				 
                //---component 3
				if ((InitTranComLinearItem[CoordIndex][3] &0x0e00)==0x0800)
				     InputTableIndex[CoordIndex][3][Masked_InputIndex]=(b1<<2)|(e1<<1)|(a2<<0);

				else
					InputTableIndex[CoordIndex][3][Masked_InputIndex]=(e1<<1)|(a2<<0); 
				 
				 //---component 4

                if ((InitTranComLinearItem[CoordIndex][4] &0x0e00)==0x0400)
				     InputTableIndex[CoordIndex][4][Masked_InputIndex]=(b2<<2)|(e2<<1)|(a2<<0); 
		
				 else
					InputTableIndex[CoordIndex][4][Masked_InputIndex]=(e2<<1)|(a2<<0); 
				//---component 5
			     if ((InitTranComLinearItem[CoordIndex][5] &0x0e00)==0x0200)
				     InputTableIndex[CoordIndex][5][Masked_InputIndex]=(b3<<2)|(e3<<1)|(a2<<0);
				else 
					InputTableIndex[CoordIndex][5][Masked_InputIndex]=(e3<<1)|(a2<<0);

                //---component 6
				if ((InitTranComLinearItem[CoordIndex][6] &0x0e00)==0x0800)
				     InputTableIndex[CoordIndex][6][Masked_InputIndex]=(b1<<2)|(e1<<1)|(a3<<0);

				else 
          			InputTableIndex[CoordIndex][6][Masked_InputIndex]=(e1<<1)|(a3<<0);		
				 //---component 7
                if ((InitTranComLinearItem[CoordIndex][7] &0x0e00)==0x0400)
				     InputTableIndex[CoordIndex][7][Masked_InputIndex]=(b2<<2)|(e2<<1)|(a3<<0); 

				else 
          			InputTableIndex[CoordIndex][7][Masked_InputIndex]=(e2<<1)|(a3<<0);
                //---component 8
			    if ((InitTranComLinearItem[CoordIndex][8] &0x0e00)==0x0200)
				     InputTableIndex[CoordIndex][8][Masked_InputIndex]=(b3<<2)|(e3<<1)|(a3<<0);
				else 
          			InputTableIndex[CoordIndex][8][Masked_InputIndex]=(e3<<1)|(a3<<0);
          			
          			Masked_InputIndex++;

			}
		}
	}

}



/* Type3
a&b ^ a ^ c  ;
*/
void InputTableIndexGen_NLbaLc( unsigned char  Type[5][9], unsigned char CoordIndex, unsigned short  InitTranComLinearItem[5][9], unsigned char*   InputTableIndex[5][9],unsigned short  InitLinearItem[5][9],unsigned short  TransLinearItem[5][9][3])
{	
	unsigned int  CompIndex, InputMask,OutShare,i;
	unsigned char  abcde,a1b1c1d1e1,a2b2c2d2e2,a3b3c3d3e3;
	unsigned short	Masked_InputIndex,TypeIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;
    
   

	for(CompIndex=0;CompIndex<9;CompIndex++)	
	{
		InitTranComLinearItem[CoordIndex][CompIndex]=InitLinearItem[CoordIndex][CompIndex]^TransLinearItem[CoordIndex][CompIndex][Type[CoordIndex][CompIndex]];
		
	}

    Masked_InputIndex = 0;
	for (abcde=0;abcde<32;abcde++)
	{
	   for(a1b1c1d1e1=0;a1b1c1d1e1<32;a1b1c1d1e1++)
	    {
			a1=(a1b1c1d1e1>>0)&0x1;
			b1=(a1b1c1d1e1>>1)&0x1;
	    	c1=(a1b1c1d1e1>>2)&0x1;
	    	d1=(a1b1c1d1e1>>3)&0x1;
			e1=(a1b1c1d1e1>>4)&0x1;
			
			
	    	for(a2b2c2d2e2=0;a2b2c2d2e2<32;a2b2c2d2e2++)
	    	{
	    		a3b3c3d3e3=abcde^a1b1c1d1e1^a2b2c2d2e2;
				
				a2=(a2b2c2d2e2>>0)&0x01;
				b2=(a2b2c2d2e2>>1)&0x01;
                c2=(a2b2c2d2e2>>2)&0x01;
				d2=(a2b2c2d2e2>>3)&0x01; 
				e2=(a2b2c2d2e2>>4)&0x01;
				
				a3=(a3b3c3d3e3>>0)&0x01;
				b3=(a3b3c3d3e3>>1)&0x01;
                c3=(a3b3c3d3e3>>2)&0x01;
				d3=(a3b3c3d3e3>>3)&0x01;
				e3=(a3b3c3d3e3>>4)&0x01;
				//---component 0
                if ((InitTranComLinearItem[CoordIndex][0] &0x01c0)==0x0100)
				     InputTableIndex[CoordIndex][0][Masked_InputIndex]=(c1<<2)|(b1<<1)|(a1<<0);
				 else 
					 InputTableIndex[CoordIndex][0][Masked_InputIndex]=(b1<<1)|(a1<<0); 
					
				//---component 1
				 if ((InitTranComLinearItem[CoordIndex][1] &0x01c0)==0x0080)
				     InputTableIndex[CoordIndex][1][Masked_InputIndex]=(c2<<2)|(b1<<1)|(a2<<0); 
				 
                else
                    InputTableIndex[CoordIndex][1][Masked_InputIndex]=(b1<<1)|(a2<<0); 	
								
				//---component 2 
				 if ((InitTranComLinearItem[CoordIndex][2] &0x01c0)==0x0040)
				     InputTableIndex[CoordIndex][2][Masked_InputIndex]=(c3<<2)|(b1<<1)|(a3<<0);  
				else
					 InputTableIndex[CoordIndex][2][Masked_InputIndex]=(b1<<1)|(a3<<0);  
				 
                //---component 3
				if ((InitTranComLinearItem[CoordIndex][3] &0x01c0)==0x0100)
				     InputTableIndex[CoordIndex][3][Masked_InputIndex]=(c1<<2)|(b2<<1)|(a1<<0);

				else
					InputTableIndex[CoordIndex][3][Masked_InputIndex]=(b2<<1)|(a1<<0); 
				 
				 //---component 4

                if ((InitTranComLinearItem[CoordIndex][4] &0x01c0)==0x0080)
				     InputTableIndex[CoordIndex][4][Masked_InputIndex]=(c2<<2)|(b2<<1)|(a2<<0); 
		
				 else
					InputTableIndex[CoordIndex][4][Masked_InputIndex]=(b2<<1)|(a2<<0); 
				//---component 5
			     if ((InitTranComLinearItem[CoordIndex][5] &0x01c0)==0x0040)
				     InputTableIndex[CoordIndex][5][Masked_InputIndex]=(c3<<2)|(b2<<1)|(a3<<0);
				else 
					InputTableIndex[CoordIndex][5][Masked_InputIndex]=(b2<<1)|(a3<<0);

                //---component 6
				if ((InitTranComLinearItem[CoordIndex][6] &0x01c0)==0x0100)
				     InputTableIndex[CoordIndex][6][Masked_InputIndex]=(c1<<2)|(b3<<1)|(a1<<0);

				else 
          			InputTableIndex[CoordIndex][6][Masked_InputIndex]=(b3<<1)|(a1<<0);		
				 //---component 7
                if ((InitTranComLinearItem[CoordIndex][7] &0x01c0)==0x0080)
				     InputTableIndex[CoordIndex][7][Masked_InputIndex]=(c2<<2)|(b3<<1)|(a2<<0); 

				else 
          			InputTableIndex[CoordIndex][7][Masked_InputIndex]=(b3<<1)|(a2<<0);
                //---component 8
			    if ((InitTranComLinearItem[CoordIndex][8] &0x01c0)==0x0040)
				     InputTableIndex[CoordIndex][8][Masked_InputIndex]=(c3<<2)|(b3<<1)|(a3<<0);
				else 
          			InputTableIndex[CoordIndex][8][Masked_InputIndex]=(b3<<1)|(a3<<0);
          			
          			Masked_InputIndex++;

			}
		}
	}

}



/*Expression Type4
b&c ^ b ^ d  ;
*/
void InputTableIndexGen_NLbcLd( unsigned char  Type[5][9], unsigned char CoordIndex, unsigned short  InitTranComLinearItem[5][9], unsigned char*   InputTableIndex[5][9],unsigned short  InitLinearItem[5][9],unsigned short  TransLinearItem[5][9][3])
{	
	unsigned int  CompIndex, InputMask,OutShare,i;
	unsigned char  abcde,a1b1c1d1e1,a2b2c2d2e2,a3b3c3d3e3;
	unsigned short	Masked_InputIndex,TypeIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;
    
   

	for(CompIndex=0;CompIndex<9;CompIndex++)	
	{
		InitTranComLinearItem[CoordIndex][CompIndex]=InitLinearItem[CoordIndex][CompIndex]^TransLinearItem[CoordIndex][CompIndex][Type[CoordIndex][CompIndex]];
		
	}

    Masked_InputIndex = 0;
	for (abcde=0;abcde<32;abcde++)
	{
	   for(a1b1c1d1e1=0;a1b1c1d1e1<32;a1b1c1d1e1++)
	    {
			a1=(a1b1c1d1e1>>0)&0x1;
			b1=(a1b1c1d1e1>>1)&0x1;
	    	c1=(a1b1c1d1e1>>2)&0x1;
	    	d1=(a1b1c1d1e1>>3)&0x1;
			e1=(a1b1c1d1e1>>4)&0x1;
			
			
	    	for(a2b2c2d2e2=0;a2b2c2d2e2<32;a2b2c2d2e2++)
	    	{
	    		a3b3c3d3e3=abcde^a1b1c1d1e1^a2b2c2d2e2;
				
				a2=(a2b2c2d2e2>>0)&0x01;
				b2=(a2b2c2d2e2>>1)&0x01;
                c2=(a2b2c2d2e2>>2)&0x01;
				d2=(a2b2c2d2e2>>3)&0x01; 
				e2=(a2b2c2d2e2>>4)&0x01;
				
				a3=(a3b3c3d3e3>>0)&0x01;
				b3=(a3b3c3d3e3>>1)&0x01;
                c3=(a3b3c3d3e3>>2)&0x01;
				d3=(a3b3c3d3e3>>3)&0x01;
				e3=(a3b3c3d3e3>>4)&0x01;
				//---component 0
                if ((InitTranComLinearItem[CoordIndex][0] &0x0038)==0x0020)
				     InputTableIndex[CoordIndex][0][Masked_InputIndex]=(d1<<2)|(b1<<1)|(c1<<0);
				 else 
					 InputTableIndex[CoordIndex][0][Masked_InputIndex]=(b1<<1)|(c1<<0); 
					
				//---component 1
				 if ((InitTranComLinearItem[CoordIndex][1] &0x0038)==0x0010)
				     InputTableIndex[CoordIndex][1][Masked_InputIndex]=(d2<<2)|(b2<<1)|(c1<<0); 
				 
                else
                    InputTableIndex[CoordIndex][1][Masked_InputIndex]=(b2<<1)|(c1<<0); 	
								
				//---component 2 
				 if ((InitTranComLinearItem[CoordIndex][2] &0x0038)==0x0008)
				     InputTableIndex[CoordIndex][2][Masked_InputIndex]=(d3<<2)|(b3<<1)|(c1<<0);  
				else
					 InputTableIndex[CoordIndex][2][Masked_InputIndex]=(b3<<1)|(c1<<0);  
				 
                //---component 3
				if ((InitTranComLinearItem[CoordIndex][3] &0x0038)==0x0020)
				     InputTableIndex[CoordIndex][3][Masked_InputIndex]=(d1<<2)|(b1<<1)|(c2<<0);

				else
					InputTableIndex[CoordIndex][3][Masked_InputIndex]=(b1<<1)|(c2<<0); 
				 
				 //---component 4

                if ((InitTranComLinearItem[CoordIndex][4] &0x0038)==0x0010)
				     InputTableIndex[CoordIndex][4][Masked_InputIndex]=(d2<<2)|(b2<<1)|(c2<<0); 
		
				 else
					InputTableIndex[CoordIndex][4][Masked_InputIndex]=(b2<<1)|(c2<<0); 
				//---component 5
			     if ((InitTranComLinearItem[CoordIndex][5] &0x0038)==0x0008)
				     InputTableIndex[CoordIndex][5][Masked_InputIndex]=(d3<<2)|(b3<<1)|(c2<<0);
				else 
					InputTableIndex[CoordIndex][5][Masked_InputIndex]=(b3<<1)|(c2<<0);

                //---component 6
				if ((InitTranComLinearItem[CoordIndex][6] &0x0038)==0x0020)
				     InputTableIndex[CoordIndex][6][Masked_InputIndex]=(d1<<2)|(b1<<1)|(c3<<0);

				else 
          			InputTableIndex[CoordIndex][6][Masked_InputIndex]=(b1<<1)|(c3<<0);		
				 //---component 7
                if ((InitTranComLinearItem[CoordIndex][7] &0x0038)==0x0010)
				     InputTableIndex[CoordIndex][7][Masked_InputIndex]=(d2<<2)|(b2<<1)|(c3<<0); 

				else 
          			InputTableIndex[CoordIndex][7][Masked_InputIndex]=(b2<<1)|(c3<<0);
                //---component 8
			    if ((InitTranComLinearItem[CoordIndex][8] &0x0038)==0x0008)
				     InputTableIndex[CoordIndex][8][Masked_InputIndex]=(d3<<2)|(b3<<1)|(c3<<0);
				else 
          			InputTableIndex[CoordIndex][8][Masked_InputIndex]=(b3<<1)|(c3<<0);
          			
          			Masked_InputIndex++;

			}
		}
	}

}

/* Expression Type5
c&d ^ c ^ e
*/
void InputTableIndexGen_NLdcLe( unsigned char  Type[5][9], unsigned char CoordIndex, unsigned short  InitTranComLinearItem[5][9], unsigned char*   InputTableIndex[5][9],unsigned short  InitLinearItem[5][9],unsigned short  TransLinearItem[5][9][3])
{	
	unsigned int  CompIndex, InputMask,OutShare,i;
	unsigned char  abcde,a1b1c1d1e1,a2b2c2d2e2,a3b3c3d3e3;
	unsigned short	Masked_InputIndex,TypeIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;


	for(CompIndex=0;CompIndex<9;CompIndex++)	
	{
		InitTranComLinearItem[CoordIndex][CompIndex]=InitLinearItem[CoordIndex][CompIndex]^TransLinearItem[CoordIndex][CompIndex][Type[CoordIndex][CompIndex]];
	}

    Masked_InputIndex = 0;
	for (abcde=0;abcde<32;abcde++)
	{
	   for(a1b1c1d1e1=0;a1b1c1d1e1<32;a1b1c1d1e1++)
	    {
			a1=(a1b1c1d1e1>>0)&0x1;
			b1=(a1b1c1d1e1>>1)&0x1;
	    	c1=(a1b1c1d1e1>>2)&0x1;
	    	d1=(a1b1c1d1e1>>3)&0x1;
			e1=(a1b1c1d1e1>>4)&0x1;

	    	for(a2b2c2d2e2=0;a2b2c2d2e2<32;a2b2c2d2e2++)
	    	{
	    		a3b3c3d3e3=abcde^a1b1c1d1e1^a2b2c2d2e2;
				
				a2=(a2b2c2d2e2>>0)&0x01;
				b2=(a2b2c2d2e2>>1)&0x01;
                c2=(a2b2c2d2e2>>2)&0x01;
				d2=(a2b2c2d2e2>>3)&0x01; 
				e2=(a2b2c2d2e2>>4)&0x01;
				
				a3=(a3b3c3d3e3>>0)&0x01;
				b3=(a3b3c3d3e3>>1)&0x01;
                c3=(a3b3c3d3e3>>2)&0x01;
				d3=(a3b3c3d3e3>>3)&0x01;
				e3=(a3b3c3d3e3>>4)&0x01;
				//---component 0
                if ((InitTranComLinearItem[CoordIndex][0] &0x0007)==0x0004)
				     InputTableIndex[CoordIndex][0][Masked_InputIndex]=(e1<<2)|(c1<<1)|(d1<<0);
				 else 
					 InputTableIndex[CoordIndex][0][Masked_InputIndex]=(c1<<1)|(d1<<0); 
					
				//---component 1
				 if ((InitTranComLinearItem[CoordIndex][1] &0x0007)==0x0002)
				     InputTableIndex[CoordIndex][1][Masked_InputIndex]=(e2<<2)|(c2<<1)|(d1<<0); 
				 
                else
                    InputTableIndex[CoordIndex][1][Masked_InputIndex]=(c2<<1)|(d1<<0); 	
								
				//---component 2 
				 if ((InitTranComLinearItem[CoordIndex][2] &0x0007)==0x0001)
				     InputTableIndex[CoordIndex][2][Masked_InputIndex]=(e3<<2)|(c3<<1)|(d1<<0);  
				else
					 InputTableIndex[CoordIndex][2][Masked_InputIndex]=(c3<<1)|(d1<<0);  
				 
                //---component 3
				if ((InitTranComLinearItem[CoordIndex][3] &0x0007)==0x0004)
				     InputTableIndex[CoordIndex][3][Masked_InputIndex]=(e1<<2)|(c1<<1)|(d2<<0);

				else
					InputTableIndex[CoordIndex][3][Masked_InputIndex]=(c1<<1)|(d2<<0); 
				 
				 //---component 4

                if ((InitTranComLinearItem[CoordIndex][4] &0x0007)==0x0002)
				     InputTableIndex[CoordIndex][4][Masked_InputIndex]=(e2<<2)|(c2<<1)|(d2<<0); 
		
				 else
					InputTableIndex[CoordIndex][4][Masked_InputIndex]=(c2<<1)|(d2<<0); 
				//---component 5
			     if ((InitTranComLinearItem[CoordIndex][5] &0x0007)==0x0001)
				     InputTableIndex[CoordIndex][5][Masked_InputIndex]=(e3<<2)|(c3<<1)|(d2<<0);
				else 
					InputTableIndex[CoordIndex][5][Masked_InputIndex]=(c3<<1)|(d2<<0);

                //---component 6
				if ((InitTranComLinearItem[CoordIndex][6] &0x0007)==0x0004)
				     InputTableIndex[CoordIndex][6][Masked_InputIndex]=(e1<<2)|(c1<<1)|(d3<<0);

				else 
          			InputTableIndex[CoordIndex][6][Masked_InputIndex]=(c1<<1)|(d3<<0);		
				 //---component 7
                if ((InitTranComLinearItem[CoordIndex][7] &0x0007)==0x0002)
				     InputTableIndex[CoordIndex][7][Masked_InputIndex]=(e2<<2)|(c2<<1)|(d3<<0); 

				else 
          			InputTableIndex[CoordIndex][7][Masked_InputIndex]=(c2<<1)|(d3<<0);
                //---component 8
			    if ((InitTranComLinearItem[CoordIndex][8] &0x0007)==0x0001)
				     InputTableIndex[CoordIndex][8][Masked_InputIndex]=(e3<<2)|(c3<<1)|(d3<<0);
				else 
          			InputTableIndex[CoordIndex][8][Masked_InputIndex]=(c3<<1)|(d3<<0);
          			
          			Masked_InputIndex++;
			}
		}
	}
}

void MakeLargeTables( unsigned char  Type[5][9], unsigned char*     InputTableIndex[5][9], unsigned char*     F3FullMaskValue[5][3],unsigned char*     F3To1UnMaskValue[5][3],unsigned char*   XorValue[5][9][3],unsigned short  InitLinearItem[5][9],unsigned short  TransLinearItem[5][9][3],unsigned short  InitTranComLinearItem[5][9],unsigned char ExpressionType[5])
{
    unsigned int   CompIndex, InputMask,OutShare,i,j;
	unsigned char  abcde,a1b1c1d1e1,a2b2c2d2e2,a3b3c3d3e3;
	unsigned short	Masked_InputIndex,TypeIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,e1,e2,e3;
	unsigned char  f0_1,f0_2,f0_3,f0_4,f0_5,f0_6,f0_7,f0_8,f0_9;
	unsigned char  f1_1,f1_2,f1_3,f1_4,f1_5,f1_6,f1_7,f1_8,f1_9;
    unsigned char  f1_1c,f1_2c,f1_3c,f1_4c,f1_5c,f1_6c,f1_7c,f1_8c,f1_9c;
	
	unsigned char  f2_1,f2_2,f2_3,f2_4,f2_5,f2_6,f2_7,f2_8,f2_9;
		unsigned char  f2_1c,f2_2c,f2_3c,f2_4c,f2_5c,f2_6c,f2_7c,f2_8c,f2_9c;
	unsigned char  f3_1,f3_2,f3_3,f3_4,f3_5,f3_6,f3_7,f3_8,f3_9;
	unsigned char  f4_1,f4_2,f4_3,f4_4,f4_5,f4_6,f4_7,f4_8,f4_9;
	unsigned char  CoordIndex;

	// need to  change change  the compIndex according to  the linear tranfer components 

 for(CoordIndex=0;CoordIndex<5;CoordIndex++)
	 {
		if(ExpressionType[CoordIndex]==EType_eANDdXORa)
			InputTableIndexGen_NLedLa(Type,CoordIndex,InitTranComLinearItem, InputTableIndex,InitLinearItem,TransLinearItem);
		else if(ExpressionType[CoordIndex]==EType_aANDeXORb )
			InputTableIndexGen_NLaeLb(Type,CoordIndex,InitTranComLinearItem, InputTableIndex,InitLinearItem,TransLinearItem);
		else if(ExpressionType[CoordIndex]==EType_bANDaXORc)
			InputTableIndexGen_NLbaLc(Type,CoordIndex,InitTranComLinearItem, InputTableIndex,InitLinearItem,TransLinearItem);
		else if(ExpressionType[CoordIndex]==EType_bANDcXORd )
			InputTableIndexGen_NLbcLd(Type,CoordIndex,InitTranComLinearItem, InputTableIndex,InitLinearItem,TransLinearItem);
		else if(ExpressionType[CoordIndex]==EType_dANDcXORe)
			InputTableIndexGen_NLdcLe(Type,CoordIndex,InitTranComLinearItem, InputTableIndex,InitLinearItem,TransLinearItem);
		
	 }

	Masked_InputIndex = 0;

	//#pragma omp parallel for num_threads(4)
	for (abcde=0;abcde<32;abcde++)
	{
	   for(a1b1c1d1e1=0;a1b1c1d1e1<32;a1b1c1d1e1++)
	    {
			a1=(a1b1c1d1e1>>0)&0x1;
			b1=(a1b1c1d1e1>>1)&0x1;
	    	c1=(a1b1c1d1e1>>2)&0x1;
	    	d1=(a1b1c1d1e1>>3)&0x1;
            e1=(a1b1c1d1e1>>4)&0x1;
			
			
	    	for(a2b2c2d2e2=0;a2b2c2d2e2<32;a2b2c2d2e2++)
	    	{
	    		a3b3c3d3e3=abcde^a1b1c1d1e1^a2b2c2d2e2;
				
				a2=(a2b2c2d2e2>>0)&0x01;
				b2=(a2b2c2d2e2>>1)&0x01;
                c2=(a2b2c2d2e2>>2)&0x01;
				d2=(a2b2c2d2e2>>3)&0x01; 
                e2=(a2b2c2d2e2>>4)&0x01;
				
				a3=(a3b3c3d3e3>>0)&0x01;
				b3=(a3b3c3d3e3>>1)&0x01;
                c3=(a3b3c3d3e3>>2)&0x01;
				d3=(a3b3c3d3e3>>3)&0x01;
                e3=(a3b3c3d3e3>>4)&0x01;
				
				

				
				/* 2 need to  change the   after fi_j =   the expressions */
			    // coordinate_0 initial expression+ possible linear item in the search process
				
				f0_1=e1&d1^d1    ^ XorValue[0][0][Type[0][0]][Masked_InputIndex];
				f0_2=e1&d2^a2    ^ XorValue[0][1][Type[0][1]][Masked_InputIndex];                //case 2
				f0_3=e1&d3       ^ XorValue[0][2][Type[0][2]][Masked_InputIndex];            
				
				F3FullMaskValue[0][0][Masked_InputIndex]=(f0_3<<2)|(f0_2<<1)|(f0_1<<0);
				F3To1UnMaskValue[0][0][Masked_InputIndex]=f0_1^f0_2^f0_3;
				
                f0_4=e2&d1^a1   ^ XorValue[0][3][Type[0][3]][Masked_InputIndex]   ;
                f0_5=e2&d2      ^ XorValue[0][4][Type[0][4]][Masked_InputIndex]   ;    				
                f0_6=e2&d3^d3   ^ XorValue[0][5][Type[0][5]][Masked_InputIndex]    ;
				
				F3FullMaskValue[0][1][Masked_InputIndex]=(f0_6<<2)|(f0_5<<1)|(f0_4<<0);
				F3To1UnMaskValue[0][1][Masked_InputIndex]=f0_6^f0_5^f0_4;

				 f0_7=e3&d1     ^ XorValue[0][6][Type[0][6]][Masked_InputIndex]   ;
                 f0_8=e3&d2^d2  ^ XorValue[0][7][Type[0][7]][Masked_InputIndex]   ;    
                 f0_9=e3&d3^a3  ^ XorValue[0][8][Type[0][8]][Masked_InputIndex]    ;

				 
				F3FullMaskValue[0][2][Masked_InputIndex]=(f0_9<<2)|(f0_8<<1)|(f0_7<<0);
				F3To1UnMaskValue[0][2][Masked_InputIndex]=f0_9^f0_8^f0_7;
				
				// coordinate_1

				f1_1=a1&e1^b1  ^ XorValue[1][0][Type[1][0]][Masked_InputIndex];    
                f1_2=a1&e2^e2    ^ XorValue[1][1][Type[1][1]][Masked_InputIndex] ;   
                f1_3=a1&e3       ^ XorValue[1][2][Type[1][2]][Masked_InputIndex] ;   

                
				F3FullMaskValue[1][0][Masked_InputIndex]=(f1_3<<2)|(f1_2<<1)|(f1_1<<0);
				F3To1UnMaskValue[1][0][Masked_InputIndex]=f1_1^f1_2^f1_3;

				
				f1_4=a2&e1^e1 ^ XorValue[1][3][Type[1][3]][Masked_InputIndex];;
                f1_5=a2&e2    ^ XorValue[1][4][Type[1][4]][Masked_InputIndex];;
                f1_6=a2&e3^b3 ^ XorValue[1][5][Type[1][5]][Masked_InputIndex];;
                

				
				
				F3FullMaskValue[1][1][Masked_InputIndex]=(f1_6<<2)|(f1_5<<1)|(f1_4<<0);
				F3To1UnMaskValue[1][1][Masked_InputIndex]=f1_6^f1_5^f1_4;
				
				f1_7=a3&e1    ^ XorValue[1][6][Type[1][6]][Masked_InputIndex] ;
                f1_8=a3&e2^b2 ^ XorValue[1][7][Type[1][7]][Masked_InputIndex] ;
                f1_9=a3&e3^e3 ^ XorValue[1][8][Type[1][8]][Masked_InputIndex] ;  

				F3FullMaskValue[1][2][Masked_InputIndex]=(f1_9<<2)|(f1_8<<1)|(f1_7<<0);
				F3To1UnMaskValue[1][2][Masked_InputIndex]=f1_9^f1_8^f1_7;
				

				// coordinate_2

				
				f2_1=b1&a1^c1       ^ XorValue[2][0][Type[2][0]][Masked_InputIndex];  
				f2_2=b1&a2^a2         ^ XorValue[2][1][Type[2][1]][Masked_InputIndex] ;  //case2
                f2_3=b1&a3            ^ XorValue[2][2][Type[2][2]][Masked_InputIndex] ;
				
				
				
				F3FullMaskValue[2][0][Masked_InputIndex]=(f2_3<<2)|(f2_2<<1)|(f2_1<<0);
				F3To1UnMaskValue[2][0][Masked_InputIndex]=f2_1^f2_2^f2_3;

				
				f2_4=b2&a1^a1  ^ XorValue[2][3][Type[2][3]][Masked_InputIndex];
				f2_5=b2&a2     ^ XorValue[2][4][Type[2][4]][Masked_InputIndex]; //case2
				f2_6=b2&a3^c3  ^ XorValue[2][5][Type[2][5]][Masked_InputIndex];
				
				
				 
				F3FullMaskValue[2][1][Masked_InputIndex]=(f2_6<<2)|(f2_5<<1)|(f2_4<<0);
				F3To1UnMaskValue[2][1][Masked_InputIndex]=f2_6^f2_5^f2_4;

				
			    f2_7=b3&a1   ^ XorValue[2][6][Type[2][6]][Masked_InputIndex] ;
			    f2_8=b3&a2^c2^ XorValue[2][7][Type[2][7]][Masked_InputIndex] ; 	//case2
                f2_9=b3&a3^a3^ XorValue[2][8][Type[2][8]][Masked_InputIndex]  ;
			
			
			
			
				F3FullMaskValue[2][2][Masked_InputIndex]=(f2_9<<2)|(f2_8<<1)|(f2_7<<0);
				F3To1UnMaskValue[2][2][Masked_InputIndex]=f2_9^f2_8^f2_7;
				
				// coordinate_3

				f3_1=c1&b1^b1   ^ XorValue[3][0][Type[3][0]][Masked_InputIndex]   ;
				f3_2=c1&b2^d2   ^ XorValue[3][1][Type[3][1]][Masked_InputIndex]   ;
				f3_3=c1&b3      ^ XorValue[3][2][Type[3][2]][Masked_InputIndex]   ;
				
				F3FullMaskValue[3][0][Masked_InputIndex]=(f3_3<<2)|(f3_2<<1)|(f3_1<<0);
				F3To1UnMaskValue[3][0][Masked_InputIndex]=f3_1^f3_2^f3_3;

                f3_4= c2&b1^d1  ^ XorValue[3][3][Type[3][3]][Masked_InputIndex] ;
                f3_5= c2&b2      ^ XorValue[3][4][Type[3][4]][Masked_InputIndex] ;
                f3_6= c2&b3^b3   ^ XorValue[3][5][Type[3][5]][Masked_InputIndex] ;

				F3FullMaskValue[3][1][Masked_InputIndex]=(f3_6<<2)|(f3_5<<1)|(f3_4<<0);
				F3To1UnMaskValue[3][1][Masked_InputIndex]=f3_6^f3_5^f3_4;

                f3_7=c3&b1     ^ XorValue[3][6][Type[3][6]][Masked_InputIndex]  ;
                f3_8=c3&b2^b2  ^ XorValue[3][7][Type[3][7]][Masked_InputIndex]  ;
                f3_9=c3&b3^d3  ^ XorValue[3][8][Type[3][8]][Masked_InputIndex]  ;		
				
				F3FullMaskValue[3][2][Masked_InputIndex]=(f3_9<<2)|(f3_8<<1)|(f3_7<<0);
				F3To1UnMaskValue[3][2][Masked_InputIndex]=f3_9^f3_8^f3_7;

				// coordinate_4

				f4_1=d1&c1^c1   ^ XorValue[4][0][Type[4][0]][Masked_InputIndex]   ;
				f4_2=d1&c2^e2   ^ XorValue[4][1][Type[4][1]][Masked_InputIndex]   ;
				f4_3=d1&c3      ^ XorValue[4][2][Type[4][2]][Masked_InputIndex]   ;
				
				F3FullMaskValue[4][0][Masked_InputIndex]=(f4_3<<2)|(f4_2<<1)|(f4_1<<0);
				F3To1UnMaskValue[4][0][Masked_InputIndex]=f4_1^f4_2^f4_3;

                f4_4= d2&c1^e1 ^ XorValue[4][3][Type[4][3]][Masked_InputIndex] ;
                f4_5= d2&c2     ^ XorValue[4][4][Type[4][4]][Masked_InputIndex] ;
                f4_6= d2&c3^c3  ^ XorValue[4][5][Type[4][5]][Masked_InputIndex] ;

				F3FullMaskValue[4][1][Masked_InputIndex]=(f4_6<<2)|(f4_5<<1)|(f4_4<<0);
				F3To1UnMaskValue[4][1][Masked_InputIndex]=f4_6^f4_5^f4_4;

                f4_7=d3&c1     ^ XorValue[4][6][Type[4][6]][Masked_InputIndex]  ;
                f4_8=d3&c2^c2  ^ XorValue[4][7][Type[4][7]][Masked_InputIndex]  ;
                f4_9=d3&c3^e3  ^ XorValue[4][8][Type[4][8]][Masked_InputIndex]  ;		
				
				F3FullMaskValue[4][2][Masked_InputIndex]=(f4_9<<2)|(f4_8<<1)|(f4_7<<0);
				F3To1UnMaskValue[4][2][Masked_InputIndex]=f4_9^f4_8^f4_7;


				Masked_InputIndex++;
			}
		}
	}



}




//=================================
unsigned char  CheckSingleCoordinateDistributions(unsigned char*     InputTableIndex[5][9], unsigned char*     F3FullMaskValue[5][3],unsigned char*     DisInCoorF3COm[5][3][9],unsigned char*     DisInCoorF3F3[5][3][3],  unsigned char CoordIndexNumber)
{
unsigned int  CoordIndex, CompIndex, InputMask,OutShare, OutShare1, OutShare2,i;
	
	unsigned short	Masked_InputIndex;
	
	unsigned short	OneFCcompose,OneFFcompose;
	unsigned char   DisOld[256]; 
	unsigned char res;
	
	memset(DisOld,0,256);  // InputTableIndex(3-5 bits)||F3FullMaskValue(3bits) :6-8bit-->2^8=256
	
	CoordIndex = CoordIndexNumber; 
	{
		for(OutShare=0;OutShare<3;OutShare++)
			for(CompIndex=0;CompIndex<9;CompIndex++)
		   {
	         memset(DisInCoorF3COm[CoordIndex][OutShare][CompIndex],0,256);
		   }
	}
//------------------------ verify   the independent  idential  distribution between   fi_j  and  component function	 in only one coordinate
	
	CoordIndex = CoordIndexNumber; 
	{ for(OutShare=0;OutShare<3;OutShare++)
	  for(CompIndex=0;CompIndex<9;CompIndex++)
	  {
	     for(Masked_InputIndex=0;Masked_InputIndex<Var5Share3Space;Masked_InputIndex++)   //32*1024=Var5Share3Space
	         {        
				 OneFCcompose=(InputTableIndex[CoordIndex][CompIndex][Masked_InputIndex]<<3)|F3FullMaskValue[CoordIndex][OutShare][Masked_InputIndex]  ;
				 
			     DisInCoorF3COm[CoordIndex][OutShare][CompIndex][OneFCcompose]++;
				 
				 if ((Masked_InputIndex &0x3ff) ==0x3ff) //every1024
				        if(Masked_InputIndex==0x3ff)
						{
							memcpy(DisOld, DisInCoorF3COm[CoordIndex][OutShare][CompIndex], 256 * sizeof(unsigned char));
		
							 memset(DisInCoorF3COm[CoordIndex][OutShare][CompIndex],0,256);
							
						 }
						 
						 else{
						 
						 	res= memcmp(DisOld, DisInCoorF3COm[CoordIndex][OutShare][CompIndex], 256 * sizeof(unsigned char));
	
						 	if (res )
							   {
								
							    return 0;		  
									  
				                }
						 	memset(DisInCoorF3COm[CoordIndex][OutShare][CompIndex],0,256);
						 	 
						 }
			      }
	  }

	}

	
//------------------------ verify   the independent  idential  distribution between   fi_j  and  fi_j	 in only one coordinate.
	
	memset(DisOld,0,64); //     F3FullMaskValue(3bits)||F3FullMaskValue(3bits) :6 bits-->2^6=64
	
	CoordIndex = CoordIndexNumber; 
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for(OutShare2=OutShare1+1;OutShare2<3;OutShare2++)
		   {
		   	 
	            memset(DisInCoorF3F3[CoordIndex][OutShare1][OutShare2],0,64);
			
		   }
	}
	
	CoordIndex = CoordIndexNumber; 
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for(OutShare2=OutShare1+1;OutShare2<3;OutShare2++)
		   {
		   	 for(Masked_InputIndex=0;Masked_InputIndex<Var5Share3Space;Masked_InputIndex++)
	         {

			    OneFFcompose=(F3FullMaskValue[CoordIndex][OutShare1][Masked_InputIndex] <<3)|F3FullMaskValue[CoordIndex][OutShare2][Masked_InputIndex]  ;
			    DisInCoorF3F3[CoordIndex][OutShare1][OutShare2][OneFFcompose]++;
				 
				if ((Masked_InputIndex &0x3ff) ==0x3ff) //every  1024 5bit input variables  3shares/variable  4*4*4*4*4=1024 cases for abcde =0 ...31.
				         if(Masked_InputIndex==0x3ff)
						 {
							 
							memcpy(DisOld, DisInCoorF3F3[CoordIndex][OutShare1][OutShare2], 64 * sizeof(unsigned char));
							 memset(DisInCoorF3F3[CoordIndex][OutShare1][OutShare2],0,64);	
						 }
						 
						 else{						 
						 	res= memcmp(DisOld, DisInCoorF3F3[CoordIndex][OutShare1][OutShare2], 64 * sizeof(unsigned char));
						 	if (res )
							    return 0;
						 	memset(DisInCoorF3F3[CoordIndex][OutShare1][OutShare2],0,64);
						 }
		     }
		   }
	}	

return 1;
}





unsigned char  CheckDistributionsComp(unsigned char***  InputTableIndexComp[5], unsigned char***   F3FullMaskValueComp[5], unsigned short  CaseNumComp[5], unsigned char*     DisInCoorF3COm[5][3][9],unsigned char*     DisInCoorF3F3[5][3][3],unsigned char*     Dis2CoorF3COm[5][3][5][9],unsigned char*     Dis2CoorF3F3[5][3][5][3] )
{

	unsigned int  CoordIndex,  CoordIndex1,  CoordIndex2,CompIndex, InputMask,OutShare, OutShare1, OutShare2,i;
	
	unsigned short	Masked_InputIndex;
	
	unsigned short	OneFCcompose,OneFFcompose,TwoFFcompose,TwoFCcompose;

	unsigned char   DisOld[256];
	unsigned char res;
	
	memset(DisOld,0,256);
//------------------------ verify   the independent  idential  distribution between   fi_j  and  fi_j	 between two coordinates.	
	for (CoordIndex1 = 0; CoordIndex1 < 5; CoordIndex1++)
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for (CoordIndex2 = CoordIndex1+1; CoordIndex2 < 5; CoordIndex2++)
		       for(OutShare2=0;OutShare2<3;OutShare2++)
		        {
	              memset(Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2],0,64);
				}
	}
	
    for (CoordIndex1 = 0; CoordIndex1 < 5; CoordIndex1++)
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for (CoordIndex2 = CoordIndex1+1; CoordIndex2 < 5; CoordIndex2++)
		       for(OutShare2=0;OutShare2<3;OutShare2++)
		        {
                   	 for(Masked_InputIndex=0;Masked_InputIndex<Var5Share3Space;Masked_InputIndex++)
	                 {
							TwoFFcompose=(F3FullMaskValueComp[CoordIndex1][CaseNumComp[CoordIndex1]][OutShare1][Masked_InputIndex] <<3)|F3FullMaskValueComp[CoordIndex2][CaseNumComp[CoordIndex2]][OutShare2][Masked_InputIndex]  ;
							
							Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2][TwoFFcompose]++;
							
							if ((Masked_InputIndex &0x3ff) ==0x3ff) //every 1024
									if(Masked_InputIndex==0x3ff)
									{
										memcpy(DisOld, Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2], 64 * sizeof(unsigned char));
										memset(Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2],0,64);
									}
									else
									{
										res= memcmp(DisOld, Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2], 64 * sizeof(unsigned char));
										if (res )
										{ 
									      if((CoordIndex1==0)&&(CoordIndex2==1))
											  return 10;
										  else if(((CoordIndex1==0)&&(CoordIndex2==2))||((CoordIndex1==1)&&(CoordIndex2==2)))
											  return 20;
										  else if(((CoordIndex1==0)&&(CoordIndex2==3))||((CoordIndex1==1)&&(CoordIndex2==3)))
											  return 30;
										  else 
										     return 0;
										}
										memset(Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2],0,64);
									}
		            }
                }
	}
	
//------------------------ verify   the independent  idential  distribution between   fi_j  and  components	 between two coordinates.	
	
    memset(DisOld,0,256);
	
   for (CoordIndex1 = 0; CoordIndex1 < 5; CoordIndex1++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
			for (CoordIndex2 = 0; CoordIndex2 < 5; CoordIndex2++)
			    for(CompIndex=0;CompIndex<9;CompIndex++)
		         {
	              memset(Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex],0,256);
				 }
	}
	
	
	for (CoordIndex1 = 0; CoordIndex1 < 5; CoordIndex1++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
			for (CoordIndex2 = 0; CoordIndex2 < 5; CoordIndex2++)
			    for(CompIndex=0;CompIndex<9;CompIndex++)
		         {
			 
			       for(Masked_InputIndex=0;Masked_InputIndex<Var5Share3Space;Masked_InputIndex++)
	                 {
				       TwoFCcompose=(InputTableIndexComp[CoordIndex2][CaseNumComp[CoordIndex2]][CompIndex][Masked_InputIndex]<<3)|F3FullMaskValueComp[CoordIndex1][CaseNumComp[CoordIndex1]][OutShare][Masked_InputIndex];

			           Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex][TwoFCcompose]++;
			    
				       if ((Masked_InputIndex &0x3ff) ==0x3ff) //every 1024
				         if(Masked_InputIndex==0x3ff)
						 {
							 
							memcpy(DisOld, Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex], 256 * sizeof(unsigned char));
							
							memset(Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex],0,256);
							
						 }
						 
						 else{
						 	res= memcmp(DisOld, Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex], 256 * sizeof(unsigned char));
						 	if (res )
						 	{
							if((CoordIndex1==0)&&(CoordIndex2==1))
								  return 10;
							else if(((CoordIndex1==0)&&(CoordIndex2==2))||((CoordIndex1==1)&&(CoordIndex2==2)))
								  return 20;
							else if(((CoordIndex1==0)&&(CoordIndex2==3))||((CoordIndex1==1)&&(CoordIndex2==3)))
								  return 30;
							else 
							     return 0;
							}    
						 	memset(Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex],0,256);
						 }

					 }

				 }
	}
return 1;

}


unsigned char CheckSingleUniformity( unsigned char*   F3FullMaskValue[5][3],unsigned char*     F3To1UnMaskValue[5][3], unsigned short   UniformitySOSCounter[5][3][2], unsigned short     Uniformity3OSCounter[5][8],  unsigned char CoordIndexNumber)
{
	unsigned  char  CoordIndex,CompIndex,OutShare;
	unsigned short  Masked_InputIndex,i;
	unsigned char   share3Value[5][Var5Share3Space];

//-----------------------verify  the uniformity of each outshare ----------------------------------------------------------------
        CoordIndex=CoordIndexNumber;
		for(OutShare=0;OutShare<3;OutShare++)
			{
	         memset(UniformitySOSCounter[CoordIndex][OutShare],0,4);//SOS: Single Output Share
			}
	    CoordIndex=CoordIndexNumber;
		for(OutShare=0;OutShare<3;OutShare++)
			{
				memset(UniformitySOSCounter[CoordIndex][OutShare],0,4);
				for(Masked_InputIndex=0;Masked_InputIndex<Var5Share3Space;Masked_InputIndex++)
					{
					  UniformitySOSCounter[CoordIndex][OutShare][F3To1UnMaskValue[CoordIndex][OutShare][Masked_InputIndex]]++;
					  
					  if((Masked_InputIndex&0x400)==0x3ff)
						{
						   if(UniformitySOSCounter[CoordIndex][OutShare][0]!=UniformitySOSCounter[CoordIndex][OutShare][1])
					 	   {
								return 0;	
						   }
						memset(UniformitySOSCounter[CoordIndex][OutShare],0,4);// because   UniformitySOSCounter is short type ,  the clear number  is 4.
						 
						}
					
		        	}
					
					}

//-----------------------verify the uniformity of three outshares in one coordinate---------------------------------------------
            CoordIndex=CoordIndexNumber;
			memset(Uniformity3OSCounter[CoordIndex],0,16);
                for(Masked_InputIndex=0;Masked_InputIndex<Var5Share3Space;Masked_InputIndex++)
					{  
				      share3Value[CoordIndex][Masked_InputIndex]= ((F3To1UnMaskValue[CoordIndex][2][Masked_InputIndex]&0x01)<<2) |((F3To1UnMaskValue[CoordIndex][1][Masked_InputIndex]&0x01)<<1)|(F3To1UnMaskValue[CoordIndex][0][Masked_InputIndex]&0x01); 
					  
					  Uniformity3OSCounter[CoordIndex][share3Value[CoordIndex][Masked_InputIndex]]++;
					  
					  if(Masked_InputIndex==(Var5Share3Space-1))
						{
							for(i=0;i<8;i++)
							{
								if(Uniformity3OSCounter[CoordIndex][i]!=Var5Share3Space/8)
								{
								   return 0;
						        }
							}
						   memset(Uniformity3OSCounter[CoordIndex],0,16);
						}
					}
return 1;
}




unsigned char CheckUniformityComp(unsigned char***   F3FullMaskValueComp[5], unsigned short  CaseNumComp[5], unsigned short   UniformitySOSCounter[5][3][2], unsigned short     Uniformity3OSCounter[5][8],  unsigned char*    Uniformity15OSCounter)
{

	unsigned  char CoordIndex,CompIndex,OutShare;
	unsigned short  Masked_InputIndex,i;
    unsigned short   Share15Compose[Var5Share3Space];
	unsigned char  OutValue[5][3];

//-------------------------verify the uniformity  of total 15 shares------------------------------------------------------------ 	
    memset(Uniformity15OSCounter,0,Var5Share3Space);

	for(Masked_InputIndex=0;Masked_InputIndex<Var5Share3Space;Masked_InputIndex++)
	{
		for(CoordIndex=0;CoordIndex<5;CoordIndex++)
	       {
	       	for(OutShare=0;OutShare<3;OutShare++)
	           {
	       	    OutValue[CoordIndex][OutShare]=((F3FullMaskValueComp[CoordIndex][CaseNumComp[CoordIndex]][OutShare][Masked_InputIndex]>>2)&1)^((F3FullMaskValueComp[CoordIndex][CaseNumComp[CoordIndex]][OutShare][Masked_InputIndex]>>1)&1)^(F3FullMaskValueComp[CoordIndex][CaseNumComp[CoordIndex]][OutShare][Masked_InputIndex]&1);
	           }
	       }

	    Share15Compose[Masked_InputIndex]= (OutValue[4][2]<<14)|(OutValue[4][1]<<13)|(OutValue[4][0]<<12)|(OutValue[3][2]<<11)|(OutValue[3][1]<<10)|(OutValue[3][0]<<9)|((OutValue[2][2]<<8)|(OutValue[2][1]<<7)|(OutValue[2][0]<<6)|(OutValue[1][2]<<5)|(OutValue[1][1]<<4)|(OutValue[1][0])<<3)|(OutValue[0][2]<<2)|(OutValue[0][1]<<1)|(OutValue[0][0]<<0);
		
		
	    Uniformity15OSCounter[Share15Compose[Masked_InputIndex]]++;
	    if(Uniformity15OSCounter[Share15Compose[Masked_InputIndex]]>1)
			return 0;
	    
	}
	
	 for(i=0;i<Var5Share3Space;i++)
	 {
		 if(Uniformity15OSCounter[i]!=1) 
		 {	
         return 0;
		 }
	 }

    return 1;	
}



void	 Type0To2GenerateTypeNumber( unsigned char Coordinate ,  unsigned char CompIndex,      unsigned char  Type[4][9] ,unsigned char  TypeRage[4][9][4],  unsigned char  TypeN[4][9],unsigned char  TypeRageNum[4][9])
{
    
	unsigned char RelateCompIndex1,RelateCompIndex2;
	if(CompIndex==6)
	{
	  RelateCompIndex1=0;
	  RelateCompIndex2=3;
	}
	else if(CompIndex==7)
	{
	  RelateCompIndex1=1;
	  RelateCompIndex2=4;
	}
	
	else if(CompIndex==8)
	{
	  RelateCompIndex1=2;
	  RelateCompIndex2=5;
	}

    if((Type[Coordinate][ RelateCompIndex1 ]==1)&&(Type[Coordinate][ RelateCompIndex2 ]==1))
		{
			TypeRage[Coordinate][CompIndex][0]=0;      
			TypeRageNum[Coordinate][CompIndex]=1;
		}
		else if(((Type[Coordinate][ RelateCompIndex1 ]==1)&&(Type[Coordinate][ RelateCompIndex2 ]!=1)) ||((Type[Coordinate][ RelateCompIndex1 ]!=1)&&(Type[Coordinate][ RelateCompIndex2 ]==1)))
		{
			TypeRage[Coordinate][CompIndex][0]=1;  
			TypeRageNum[Coordinate][CompIndex]=1;
		}
		else if ((Type[Coordinate][ RelateCompIndex1 ]!=1)&&(Type[Coordinate][ RelateCompIndex2 ]!=1))
		{
		
		 if((Type[Coordinate][ RelateCompIndex1 ]==2)&&(Type[Coordinate][ RelateCompIndex2 ]==2))
		{
			TypeRage[Coordinate][CompIndex][0]=0; 
			TypeRageNum[Coordinate][CompIndex]=1;
		}
		else if(((Type[Coordinate][ RelateCompIndex1 ]==2)&&(Type[Coordinate][ RelateCompIndex2 ]!=2)) ||((Type[Coordinate][ RelateCompIndex1 ]!=2)&&(Type[Coordinate][ RelateCompIndex2 ]==2)))
		{
			TypeRage[Coordinate][CompIndex][0]=2;  
			TypeRageNum[Coordinate][CompIndex]=1;
		}
		else if ((Type[Coordinate][ RelateCompIndex1 ]!=2)&&(Type[Coordinate][ RelateCompIndex2 ]!=2))
		{
			TypeRage[Coordinate][CompIndex][0]=0;      
			TypeRageNum[Coordinate][CompIndex]=1;
		}	
		else
         {
			TypeRage[Coordinate][CompIndex][0]=0; 
			TypeRageNum[Coordinate][CompIndex]=2; 
		 }									 
		}
		else 
		{
			TypeRage[Coordinate][CompIndex][0]=0;     
			TypeRage[Coordinate][CompIndex][1]=1; 
			TypeRage[Coordinate][CompIndex][2]=2;  
			TypeRageNum[Coordinate][CompIndex]=3;
        }
}



int main()
{
	unsigned char*     InputTableIndex[5][9] = {NULL};  //InputTableIndex[CoordinateIndex][ComponentIndex][InputMask]: coordinate:{0,1,2,3,4};  ComponentIndex:{0,1,...,8}, InputMask:{0,1,...,(Var5Share3Space-1)}

    unsigned char***  InputTableIndexComp[5]= {NULL};  //InputTableIndexComp[CoordinateIndex][CaseNum][ComponentIndex][InputMask]: CaseNum:is set to be 1000,
	unsigned char*     F3FullMaskValue[5][3]= {NULL}; //F3FullMaskValue[CoordinateIndex][OutShare][InputMask]: coordinate:{0,1,2,3,4};  OutShare:{0,1,2}, InputMask:{0,1,...,(Var5Share3Space-1)} ；OutShare=0: f3||f2||f1;OutShare=1: f6||f5||f4; OutShare=2: f9||f8||f7;
	
	unsigned char***   F3FullMaskValueComp[5]= {NULL}; //F3FullMaskValueComp[CoordinateIndex][CaseNum][OutShare][InputMask]:CaseNum:is set to be 1000,
	
	unsigned char*     F3To1UnMaskValue[5][3]= {NULL}; // F3To1UnMaskValue[CoordinateIndex][OutShare][InputMask]: coordinate:{0,1,2,3,4};  OutShare:{0,1,2}, InputMask:{0,1,...,(Var5Share3Space-1)}; OutShare=0: f3^f2^f1;OutShare=1: f6^f5^f4; OutShare=2: f9^f8^f7;
		
    unsigned short      UniformitySOSCounter[5][3][2];//SOS:single output share.UniformitySOS[CoordinateIndex][OutShare][UmaskValue]:coordinate:{0,1,2,3,4};   OutShare:{0,1,2}, UmaskValue:{0,1};  UmaskValue-> F3To1UnMaskValue[CoordinateIndex][OutShare][InputMask]
	unsigned short     Uniformity3OSCounter[5][8];//3OS:3 output shares/coordinate.UniformitySOS[CoordinateIndex][MaskValue]:coordinate:{0,1,2,3,4};  MaskValue:{0,1,...,7}; MaskValue-> F3FullMaskValue[CoordinateIndex][OutShare][InputMask]
	
	unsigned char*    Uniformity15OSCounter;//15OS:15 output shares  in 5 coordinates.

	unsigned char*     DisInCoorF3COm[5][3][9]={NULL}; // In only one coordinate, F3COm: ((f3||f2||f1) or(f6||f5||f4) or(f9||f8||f7) ) composed with components   DisInCoorF3COm[CoordinateIndex][OutShare][ComponentIndex][ComposeValue],coordinate:{0,1,2,3,4};  OutShare:{0,1,2},ComponentIndex:{0,1,...,8}, ComposeValue= F3FullMaskValue[]||InputTableIndex[]; 
	unsigned char*     DisInCoorF3F3[5][3][3]={NULL}; // In only one coordinate, e.g., F3F3:f3||f2||f1||f6||f5||f4. DisInCoorF3F3[CoordinateIndex][OutShare][OutShare][ComposeValue],coordinate:{0,1,2,3,4};  OutShare:{0,1,2},OutShare:{0,1,2}, ComposeValue= F3FullMaskValue[]||F3FullMaskValue[]; 
	unsigned char*     Dis2CoorF3COm[5][3][5][9]={NULL};//between two coordinates ,  Dis2CoorF3COm[CoordinateIndex][OutShare][CoordinateIndex][ComponentIndex][ComposeValue], ComposeValue= F3FullMaskValue[]||InputTableIndex[];
	
	unsigned char*     Dis2CoorF3F3[5][3][5][3]={NULL};
	unsigned char*   XorValue[5][9][3];
	unsigned char  Type[5][9],Type3,Type4,Type5;
	unsigned short  InitLinearItem[5][9];
	unsigned short  TransLinearItem[5][9][3];
    unsigned short  CaseNum[5];// the searched cases with required uniformity and distribution for simple linear compositions
	unsigned short  CaseNumComp[5];
	unsigned char**   DisUnifTypeCand[5];// DisUnifTypeCand[CoordIndex][CaseNumber][ComponentNum]: the Type values of 9 components in the CoordIndex for the CaseNumber
	unsigned short  InitTranComLinearItem[5][9]; //InitTranComLinearItem[CoordIndex][ComponentNum];
	unsigned char res1,res2,res3,flag;
    unsigned int  CoordIndex,CoordIndexa[5],CoordIndex1,CoordIndex2,CompIndex,InputMask, OutShare,OutShare1,OutShare2,i,j,m,n,k,p,q,TypeIndex;
    unsigned char TableType[5],TableTypeIndex[5]; // TableType[CoordIndex] TableTypeIndex[CoordIndex]
    
     unsigned char ExpressionType[5]; //ExpressionType[CoordIndex] 
	unsigned char  TypeRage[5][9][4];
    unsigned char  TypeRageNum[5][9];
    unsigned char  TypeN[5][9];
    unsigned short  CaseNumber;							   
	unsigned short Masked_InputIndex;
	unsigned short TcaseNum;
    FILE*				F;  
	 time(&tt);
     printf("start to alloc,  time :%s \n",ctime(&tt));
//----------------------Allocate space-------------------------------------------------------------------
    Uniformity15OSCounter= (unsigned char*)calloc(Var5Share3Space, sizeof(unsigned char));


	for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
		   for(CompIndex=0;CompIndex<9;CompIndex++)
		   {
			   DisInCoorF3COm[CoordIndex][OutShare][CompIndex]= (unsigned char*)calloc(256, sizeof(unsigned char)); //  take this  f3||f2||f1  ||a1||b1||c1||d1||e1 as example total have 8 bits,so 256 space  is enough
		   }
	}
	
   for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
	{
		DisUnifTypeCand[CoordIndex]=(unsigned char**)calloc(CaseNumSet, sizeof(unsigned char*)); //  now  we  set CaseNumSet to be 1000 which can be changed to be larger
		for(CaseNumber=0;CaseNumber<CaseNumSet;CaseNumber++)// Now  the max  test casenumber is lower than 500.
		{
		    DisUnifTypeCand[CoordIndex][CaseNumber]=(unsigned char*)calloc(9, sizeof(unsigned char));
		}
		   
	}
	
	for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
	{
		InputTableIndexComp[CoordIndex]=(unsigned char***)calloc(CaseNumSet, sizeof(unsigned char**));
		for(CaseNumber=0;CaseNumber<CaseNumSet;CaseNumber++)
		{
		    InputTableIndexComp[CoordIndex][CaseNumber]=(unsigned char**)calloc(9, sizeof(unsigned char*));
			for(CompIndex=0;CompIndex<9;CompIndex++)
				{
				InputTableIndexComp[CoordIndex][CaseNumber][CompIndex] = (unsigned char*)calloc(Var5Share3Space, sizeof(unsigned char)); 
				}
		}
		   
	}
	
	for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
	{
		F3FullMaskValueComp[CoordIndex]=(unsigned char***)calloc(CaseNumSet, sizeof(unsigned char**));
		for(CaseNumber=0;CaseNumber<CaseNumSet;CaseNumber++)
		{
		    F3FullMaskValueComp[CoordIndex][CaseNumber]=(unsigned char**)calloc(3, sizeof(unsigned char*));
			for(OutShare=0;OutShare<3;OutShare++)
				{
				F3FullMaskValueComp[CoordIndex][CaseNumber][OutShare] = (unsigned char*)calloc(Var5Share3Space, sizeof(unsigned char)); 
				}
		}
		   
	}
	
	for (CoordIndex1 = 0; CoordIndex1 < 5; CoordIndex1++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
		   for (CoordIndex2 = 0; CoordIndex2 < 5; CoordIndex2++)
			  for(CompIndex=0;CompIndex<9;CompIndex++)
		      {
			   Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex]= (unsigned char*)calloc(256, sizeof(unsigned char)); //  take this  f3||f2||f1  ||a1||b1||c1||d1||e1 as example total have 8 bits,so 256 space  is enough
		      }
	}
	
	for (CoordIndex1 = 0; CoordIndex1 < 5; CoordIndex1++)
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for (CoordIndex2 = 0; CoordIndex2 < 5; CoordIndex2++)
		       for(OutShare2=0;OutShare2<3;OutShare2++)
		        {
			     Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2]= (unsigned char*)calloc(64, sizeof(unsigned char)); //  take this  f3||f2||f1  ||f6^f5^f4 as example total have 6 bits,so 64 space  is enough
		        }
	}

	for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for(OutShare2=0;OutShare2<3;OutShare2++)
		   {
			   DisInCoorF3F3[CoordIndex][OutShare1][OutShare2]= (unsigned char*)calloc(64,sizeof(unsigned char)); //  take this  f3||f2||f1  ||f6^f5^f4 as example total have 6 bits,so 64 space  is enough
		   }
	}

    for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
	  {
		for(CompIndex=0;CompIndex<9;CompIndex++)
			for(TypeIndex=0;TypeIndex<3;TypeIndex++)
		      { XorValue[CoordIndex][CompIndex][TypeIndex] = (unsigned char*)calloc(Var5Share3Space, sizeof(unsigned char));   //total value space is Var5Share3Space; allocate space and set to be zero
			}
	  }
	for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
	{
		for(CompIndex=0;CompIndex<9;CompIndex++)
		   { 
	         InputTableIndex[CoordIndex][CompIndex] = (unsigned char*)calloc(Var5Share3Space, sizeof(unsigned char));   // allocate space and set to be zero
			} 
   }
   
	
	
	for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
		    {
			 F3FullMaskValue[CoordIndex][OutShare] = (unsigned char*)calloc(Var5Share3Space, sizeof(unsigned char));
		     F3To1UnMaskValue[CoordIndex][OutShare] = (unsigned char*)calloc(Var5Share3Space, sizeof(unsigned char));
			}
	}
	
  F = fopen(FileName, "wt");	   
    
 time(&tt);
 printf("start to transt,time :%s \n",ctime(&tt));		 
 fprintf(F,"start to transt,time :%s \n",ctime(&tt)); 


TableType[0]=E3SameIntuple_d123a123 ;
TableTypeIndex[0]=E3SameIntuple_d123a123_Index;//case 2
TableType[1]=A3SameIntuple_e123b123;
TableTypeIndex[1]=A3SameIntuple_e123b123_Index;


TableType[2]=B3SameIntuple_c123a123;        //CASE 2
TableTypeIndex[2] = B3SameIntuple_c123a123_Index;

TableType[3] = C3SameIntuple_d123b123;
TableTypeIndex[3] = C3SameIntuple_d123b123_Index;
TableType[4] = D3SameIntuple_c123e123;
TableTypeIndex[4] = D3SameIntuple_c123e123_Index;


MakeSearchDisUnifTable(InitLinearItem,TransLinearItem,XorValue,TableType);
for(CoordIndex = 0; CoordIndex < 5; CoordIndex++)
   {
   	memset(Type[CoordIndex],0,9);
   	CaseNum[CoordIndex]=0;
   }

ExpressionType[0]= EType_eANDdXORa; 
ExpressionType[1]= EType_aANDeXORb;
ExpressionType[2]= EType_bANDaXORc; 
ExpressionType[3]= EType_bANDcXORd;   
ExpressionType[4]= EType_dANDcXORe;   

#if 1

for (CoordIndex =0; CoordIndex <5; CoordIndex++)
{  

  for(Type[CoordIndex][0]=0;Type[CoordIndex][0]<TableTypeIndex[CoordIndex]; Type[CoordIndex][0]++)
   	{    
       
	    for(Type[CoordIndex][1]=0;Type[CoordIndex][1]<TableTypeIndex[CoordIndex]; Type[CoordIndex][1]++)
	       {  

			for(Type[CoordIndex][2]=0;Type[CoordIndex][2]<TableTypeIndex[CoordIndex]; Type[CoordIndex][2]++)
			   {
				    for(Type[CoordIndex][3]=0;Type[CoordIndex][3]<TableTypeIndex[CoordIndex]; Type[CoordIndex][3]++)
				  	    for(Type[CoordIndex][4]=0;Type[CoordIndex][4]<TableTypeIndex[CoordIndex]; Type[CoordIndex][4]++)
						{
							for(Type[CoordIndex][5]=0;Type[CoordIndex][5]<TableTypeIndex[CoordIndex]; Type[CoordIndex][5]++)
			                  {
			                    
						 	   Type0To2GenerateTypeNumber(CoordIndex,6, Type ,TypeRage,   TypeN,TypeRageNum);

						 	    for(TypeN[CoordIndex][6]=0;TypeN[CoordIndex][6]<TypeRageNum[CoordIndex][6]; TypeN[CoordIndex][6]++)
			                    {
			                        Type[CoordIndex][6]=TypeRage[CoordIndex][6][TypeN[CoordIndex][6]];
									Type0To2GenerateTypeNumber(CoordIndex, 7,Type ,TypeRage,   TypeN,TypeRageNum) ; 

									for(TypeN[CoordIndex][7]=0;TypeN[CoordIndex][7]<TypeRageNum[CoordIndex][7]; TypeN[CoordIndex][7]++)
									{
										Type[CoordIndex][7]=TypeRage[CoordIndex][7][TypeN[CoordIndex][7]];

										Type0To2GenerateTypeNumber(CoordIndex, 8,Type ,TypeRage,   TypeN,TypeRageNum); 

										for(TypeN[CoordIndex][8]=0;TypeN[CoordIndex][8]<TypeRageNum[CoordIndex][8]; TypeN[CoordIndex][8]++)
									    { 
										  Type[CoordIndex][8]=TypeRage[CoordIndex][8][TypeN[CoordIndex][8]];
									    {
										
										res1=0;
										res2=0;
										res3=0;
                                        	
										MakeLargeTables(Type, InputTableIndex,F3FullMaskValue,F3To1UnMaskValue,XorValue,InitLinearItem,TransLinearItem,InitTranComLinearItem, ExpressionType);

									    //check one coordinate fulfill the idential independent distribution and uniformity
                                       res1 =CheckSingleCoordinateDistributions(InputTableIndex,F3FullMaskValue,DisInCoorF3COm,DisInCoorF3F3,CoordIndex);
										if(res1)
	                                     {
	                                     	res2=CheckSingleUniformity(F3FullMaskValue,F3To1UnMaskValue,UniformitySOSCounter,    Uniformity3OSCounter, CoordIndex);
                                            if(res2)
											    {
												  res3= CheckCorrect(F3To1UnMaskValue); 
												}
										 }
										 if ((res1&res2& res3)==1)
                                        {
										   for (CompIndex=0;CompIndex<9;CompIndex++)
                                           {
										       DisUnifTypeCand[CoordIndex][ CaseNum[CoordIndex]][CompIndex]=Type[CoordIndex][CompIndex];
                                               for(Masked_InputIndex=0; Masked_InputIndex<Var5Share3Space;Masked_InputIndex++)
											   {
											   	InputTableIndexComp[CoordIndex][CaseNum[CoordIndex]][CompIndex][Masked_InputIndex]=InputTableIndex[CoordIndex][CompIndex][Masked_InputIndex];
											   }
										   }
										   for(OutShare=0;OutShare<3;OutShare++)
											{
											    for(Masked_InputIndex=0; Masked_InputIndex<Var5Share3Space;Masked_InputIndex++)
											    {
											    	F3FullMaskValueComp[CoordIndex][CaseNum[CoordIndex]][OutShare][Masked_InputIndex]=F3FullMaskValue[CoordIndex][OutShare][Masked_InputIndex];
											    }
											
										    }
										   CaseNum[CoordIndex]++;
                                          
                                        } 
									  }
									}
								  }
								}
							}
						}
			   }
		   }
	}
  memset(Type[CoordIndex],0,9);  // Type[CoordIndex]  must be cleared  , otherwise the correctness will be wrong.
}
#endif
time(&tt);
printf("single time :%s      ",ctime(&tt));	


TcaseNum=0; 
flag=0;
 

#if 1
   for(i=0;i<5;i++)
   {
	   CoordIndexa[i]=i;
	   printf("CaseNum[%d]:%d;\n",CoordIndexa[i], CaseNum[CoordIndexa[i]]);
   }
   

for(m=0;m<CaseNum[CoordIndexa[0]];m++)
{
	for (j=0;j<9;j++)
    {
	  Type[CoordIndexa[0]][j]=DisUnifTypeCand[CoordIndexa[0]][m][j];  
	} 
	CaseNumComp[CoordIndexa[0]]=m;
	for(k=0;k<CaseNum[CoordIndexa[1]];k++)
	    {
		   for (j=0;j<9;j++)
           {
		     Type[CoordIndexa[1]][j]=DisUnifTypeCand[CoordIndexa[1]][k][j];  
	       } 
		   CaseNumComp[CoordIndexa[1]]=k;
           for(n=0;n<CaseNum[CoordIndexa[2]];n++)
	       {
		       for (j=0;j<9;j++)
               {
		         Type[CoordIndexa[2]][j]=DisUnifTypeCand[CoordIndexa[2]][n][j];  
	           } 
		       CaseNumComp[CoordIndexa[2]]=n;
		       for(q=0;q<CaseNum[CoordIndexa[3]];q++)
		       {
		       	   for (j=0;j<9;j++)
		       	   {
		       	       Type[CoordIndexa[3]][j]=DisUnifTypeCand[CoordIndexa[3]][q][j];  
		       	   }   
				   CaseNumComp[CoordIndexa[3]]=q;
                   for(p=0;p<CaseNum[CoordIndexa[4]];p++)
		           {
		       	     for (j=0;j<9;j++)
		       	     {
		       	         Type[CoordIndexa[4]][j]=DisUnifTypeCand[CoordIndexa[4]][p][j];  
		       	     } 
					 CaseNumComp[CoordIndexa[4]]=p;
					 
						res1=0;
						res2=0;
						res3=0;
						
					    res1= CheckUniformityComp(F3FullMaskValueComp,CaseNumComp,UniformitySOSCounter,Uniformity3OSCounter,Uniformity15OSCounter);
						if(res1)
						{
							res2 = CheckDistributionsComp( InputTableIndexComp,F3FullMaskValueComp,CaseNumComp,DisInCoorF3COm,DisInCoorF3F3,Dis2CoorF3COm,Dis2CoorF3F3); 
							
							if(res2==10)
							{
						     p=CaseNum[CoordIndexa[4]];
						     i=CaseNum[CoordIndexa[3]];
						     n=CaseNum[CoordIndexa[2]];
							}
							else if(res2==20)
							{
							p=CaseNum[CoordIndexa[4]];
						    i=CaseNum[CoordIndexa[3]];	
							}
							else if(res2==30)
							{
							p=CaseNum[CoordIndexa[4]];
							}
							
							else if(res2==1)
							{
								res3= CheckCorrect(F3To1UnMaskValue); 
							}
						}

						if ((res1&res2& res3)==1)
						{
						  //if(flag==0)
						   {
                           fprintf(F, "========================================\n"); 
						   for (i=0;i<9;i++)
						   {
							fprintf(F, "%s %s ; \n",f0BaseExpression[i],  f0AddItems[i][Type[CoordIndexa[0]][i]]);
						   }
						   fprintf(F, "========================================\n");
						   
						   for (i=0;i<9;i++)
						   {
							fprintf(F, "%s %s ; \n",f1BaseExpression[i],  f1AddItems[i][Type[CoordIndexa[1]][i]]);
						   }
						  fprintf(F, "========================================\n");
						   for (i=0;i<9;i++)
						   {
							fprintf(F, "%s %s ; \n",f2BaseExpression[i],  f2AddItems[i][Type[CoordIndexa[2]][i]]);
						   }
						  fprintf(F, "========================================\n");							

						   for (i=0;i<9;i++)
						   {
							fprintf(F, "%s %s ; \n",f3BaseExpression[i],  f3AddItems[i][Type[CoordIndexa[3]][i]]);
						   }
						  fprintf(F, "========================================\n");

						   for (i=0;i<9;i++)
						   {
							fprintf(F, "%s %s ; \n",f4BaseExpression[i],  f4AddItems[i][Type[CoordIndexa[4]][i]]);
						   }
						  fprintf(F, "========================================\n");
                            if(flag==0)
							{time(&tt);
							fprintf(F,"Get the first case,time :%s      ",ctime(&tt));  
							}
							flag=1;
							
						    }
						    TcaseNum++;
						}
				   }
			   }
		   }			
		}
 }
fclose(F);

#endif
printf("TcaseNum:%d \n",TcaseNum);


time(&tt);
printf("This is the end,time :%s      ",ctime(&tt));	


// ===========free memory
    free(Uniformity15OSCounter);
 	for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
       	{
       		for(CompIndex=0;CompIndex<9;CompIndex++)
       		   { 		   
                   free(InputTableIndex[CoordIndex][CompIndex]);
       			}
       		   
         }
      		    
    for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
       	{	    
       	      
		          free(DisUnifTypeCand[CoordIndex]); 
       }    





       for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
       	{
       	   free(InputTableIndexComp[CoordIndex]);  
       	}
       	
		for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
       	{
       	   free(F3FullMaskValueComp[CoordIndex]);  
       	}
     
	   
       	
       	for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
       	{
       		for(OutShare=0;OutShare<3;OutShare++)
       		    {
       			 free(F3FullMaskValue[CoordIndex][OutShare]); 
       		     free(F3To1UnMaskValue[CoordIndex][OutShare]); 
       
       			}
       	}
		   		
for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
	  {
	     for(CompIndex=0;CompIndex<9;CompIndex++)
			for(TypeIndex=0;TypeIndex<3;TypeIndex++)
		      {  
		         free(XorValue[CoordIndex][CompIndex][TypeIndex]);
			  }
			  
	  }	  
			  
for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
		   for(CompIndex=0;CompIndex<9;CompIndex++)
		   {
			   free(DisInCoorF3COm[CoordIndex][OutShare][CompIndex]);
		   }
	}

	for (CoordIndex1 = 0; CoordIndex1 < 5; CoordIndex1++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
		   for (CoordIndex2 = 0; CoordIndex2 < 5; CoordIndex2++)
			  for(CompIndex=0;CompIndex<9;CompIndex++)
		      {
			   free(Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex]);
		      }
	}
	
	for (CoordIndex1 = 0; CoordIndex1 < 5; CoordIndex1++)
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for (CoordIndex2 = 0; CoordIndex2 < 5; CoordIndex2++)
		       for(OutShare2=0;OutShare2<3;OutShare2++)
		        {
			     free(Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2]) ;
		        }
	}

	for (CoordIndex = 0; CoordIndex < 5; CoordIndex++)
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for(OutShare2=0;OutShare2<3;OutShare2++)
		   {
			   free(DisInCoorF3F3[CoordIndex][OutShare1][OutShare2]);
		   }
	}


	return 0;
}
