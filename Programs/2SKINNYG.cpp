/*
* -----------------------------------------------------------------
* COMPANY : Shandong University
* AUTHOR  : Yanhong Fan, Chaoran Wang, Lixuan Wu,    Meiqin Wang
* DOCUMENT: "A Fast Search Method for 3-Share Second-Order Masking Schemes for Lightweight S-Boxes"  
* -----------------------------------------------------------------
*
* Copyright c 2023, Yanhong Fan, Chaoran Wang,  Lixuan Wu,  Meiqin Wang
*
*
* All rights reserved.
* Please see LICENSE and README for license and further instructions.
*/
/*SKINNY G*/
/*
f0 = d&b^a^1
f1 = d&c^b^1
f2 = c^1
f3 = d^1

f0_0=d1&b1 ^1  || f1_0= d1&c1 ^1          || f2_0=c1^1  || f3_0=d1^1 
f0_1=d1&b2^a2  || f1_1= d1&c2^b2          || f2_1=0     || f3_1=0    
f0_2=d1&b3     || f1_2= d1&c3             || f2_2=0     || f3_2=0    
f0_3=d2&b1^a1  || f1_3= d2&c1^b1          || f2_3=0     || f3_3=0    
f0_4=d2&b2     || f1_4= d2&c2             || f2_4=c2    || f3_4=d2   
f0_5=d2&b3     || f1_5= d2&c3             || f2_5= 0    || f3_5= 0   
f0_6=d3&b1     || f1_6= d3&c1             || f2_6= 0    || f3_6= 0   
f0_7=d3&b2     || f1_7= d3&c2             || f2_7= 0    || f3_7= 0   
f0_8=d3&b3^a3  || f1_8= d3&c3^b3          || f2_8=c3    || f3_8=d3   


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
#define D3SameIntuple_b123a123      1 
#define D3SameIntuple_c123b123      2
#define NoNeedTable    0
// TableIndex
#define D3SameIntuple_b123a123_Index   3
#define D3SameIntuple_c123b123_Index   3 
#define  NoNeedTable_Index 0

//ExpressionType
#define  EType_dANDbXORa       1 //  this  suits for the case of b&c ^ c&d ^ d , b&c ^ c&d ^ c ^ d
#define  EType_dANDcXORb       2 
#define  EType_NoDeal            0 


#define  CaseNumSet               1000 // The Storable maximum solution  number of each coordinate is set to be 1000, according to the test, 20000 is enough large.
#define  Var4Share3Space         4096
char FileName[30]="Gen2orderExpression.txt";






char f0BaseExpression[9][30]=
{{"f0[0]=d1&b1 ^1      "},
 {"f0[1]=d1&b2^a2    "},
 {"f0[2]=d1&b3       "},	
 {"f0[3]=d2&b1^a1    "},	
 {"f0[4]=d2&b2       "},	
 {"f0[5]=d2&b3       "},
 {"f2[6]=d3&b1       "},	
 {"f0[7]=d3&b2       "},	
 {"f0[8]=d3&b3^a3    "}	
};

char f1BaseExpression[9][30]=
{{"f1[0]=d1&c1 ^1      "},
 {"f1[1]=d1&c2^b2      "},
 {"f1[2]=d1&c3         "},	
 {"f1[3]=d2&c1^b1      "},	
 {"f1[4]=d2&c2         "},	
 {"f1[5]=d2&c3         "},
 {"f1[6]=d3&c1         "},	
 {"f1[7]=d3&c2         "},	
 {"f1[8]=d3&c3^b3      "}	
};


char f2BaseExpression[9][30]=
{{"f2[0]=c1^1    "},
 {"f2[1]=0      "},
 {"f2[2]=0      "},	
 {"f2[3]=0      "},	
 {"f2[4]=c2     "},	
 {"f2[5]= 0     "},
 {"f2[6]= 0     "},	
 {"f2[7]= 0     "},	
 {"f2[8]=c3     "}	
};

char f3BaseExpression[9][30]=
{{"f3[0]=d1^1     "},
 {"f3[1]=0    "},
 {"f3[2]=0    "},	
 {"f3[3]=0    "},	
 {"f3[4]=d2       "},	
 {"f3[5]= 0   "},
 {"f3[6]= 0   "},	
 {"f3[7]= 0   "},	
 {"f3[8]=d3       "}	
};
 


char f0AddItems[9][3][10]={
{"","^a1","^b1"},
{"","^a2","^b2"},
{"","^a3","^b3"},
{"","^a1","^b1"},
{"","^a2","^b2"},
{"","^a3","^b3"},
{"","^a1","^b1"},
{"","^a2","^b2"},
{"","^a3","^b3"}
};	

char f1AddItems[9][3][10]={
{"","^b1","^c1"},
{"","^b2","^c2"},
{"","^b3","^c3"},
{"","^b1","^c1"},
{"","^b2","^c2"},
{"","^b3","^c3"},
{"","^b1","^c1"},
{"","^b2","^c2"},
{"","^b3","^c3"}
};	



unsigned char  CheckCorrect(unsigned char*     F3To1UnMaskValue[4][3])
{
	unsigned char  abcd,a1b1c1d1,a2b2c2d2,a3b3c3d3;
	unsigned short	Masked_InputIndex,TypeIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3;
	unsigned char a,b,c,d,f0,f1,f2,f3,f0m,f1m,f2m,f3m;
	
	
	Masked_InputIndex = 0;
	for (abcd=0;abcd<16;abcd++)
	{
            a=(abcd>>0)&0x1;
			b=(abcd>>1)&0x1;
	    	c=(abcd>>2)&0x1;
	    	d=(abcd>>3)&0x1;
		
		f0=d&b^a^1 ;
		f1=d&c^b^1 ;
		f2=c^1 ;
		f3=d^1 ;
		
				
			
		
	   for(a1b1c1d1=0;a1b1c1d1<16;a1b1c1d1++)
	    {
			a1=(a1b1c1d1>>0)&0x1;
			b1=(a1b1c1d1>>1)&0x1;
	    	c1=(a1b1c1d1>>2)&0x1;
	    	d1=(a1b1c1d1>>3)&0x1;
			
			
	    	for(a2b2c2d2=0;a2b2c2d2<16;a2b2c2d2++)
	    	{
	    		a3b3c3d3=abcd^a1b1c1d1^a2b2c2d2;
				
				a2=(a2b2c2d2>>0)&0x01;
				b2=(a2b2c2d2>>1)&0x01;
                c2=(a2b2c2d2>>2)&0x01;
				d2=(a2b2c2d2>>3)&0x01;
				
				a3=(a3b3c3d3>>0)&0x01;
				b3=(a3b3c3d3>>1)&0x01;
                c3=(a3b3c3d3>>2)&0x01;
				d3=(a3b3c3d3>>3)&0x01;
				
				f0m=F3To1UnMaskValue[0][0][Masked_InputIndex]^F3To1UnMaskValue[0][1][Masked_InputIndex]^F3To1UnMaskValue[0][2][Masked_InputIndex];
				
				f1m=F3To1UnMaskValue[1][0][Masked_InputIndex]^F3To1UnMaskValue[1][1][Masked_InputIndex]^F3To1UnMaskValue[1][2][Masked_InputIndex];
				
				f2m=F3To1UnMaskValue[2][0][Masked_InputIndex]^F3To1UnMaskValue[2][1][Masked_InputIndex]^F3To1UnMaskValue[2][2][Masked_InputIndex];
				
				f3m=F3To1UnMaskValue[3][0][Masked_InputIndex]^F3To1UnMaskValue[3][1][Masked_InputIndex]^F3To1UnMaskValue[3][2][Masked_InputIndex];
				
				
				if((f0!=f0m)|(f1!=f1m)|(f2!=f2m)|(f3!=f3m))
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


 
 /*TableType1
 
        type[0]    type[1]    type[2]    
comp_0     0         a1         b1          
comp_1     0         a2         b2          
comp_2     0         a3         b3          
-----------------------------------------
comp_3     0         a1         b1          
comp_4     0         a2         b2          
comp_5     0         a3         b3          
-----------------------------------------
comp_6     0         a1         b1          
comp_7     0         a2         b2          
comp_8     0         a3         b3          
-----------------------------------------



*/
void TransLinearItem_d3Sb123a123(unsigned char CoordIndex,   unsigned short  TransLinearItem[4][9][4],unsigned char*   XorValue[4][9][4]) 
 {
	 unsigned short	Masked_InputIndex,i;
	unsigned char  abcd,a1b1c1d1,a2b2c2d2,a3b3c3d3;
	
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,CompIndex;

	 // the linear items  in the all possible composed items in our bebuiled Table.	
		 
	  for(CompIndex=0;CompIndex<9;CompIndex++)
	   {
		   TransLinearItem[CoordIndex][CompIndex][0]=0; // type[0] for comp0----8
		   
		   if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
			  { 
			   TransLinearItem[CoordIndex][CompIndex][1]= 0x800 ;//a1   type[1]   for comp0  comp3   comp6
		       TransLinearItem[CoordIndex][CompIndex][2]= 0x100  ; //b1  type[2]   for comp0  comp3   comp6
			  } 
		  else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]= 0x400 ; //a2 type[1]   for comp1  comp4   comp7
		       TransLinearItem[CoordIndex][CompIndex][2]= 0x080    ; //b2    type[2]   for comp1  comp4   comp7
              } 
		  else 
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]= 0x200 ;// a3 type[1]   for comp2  comp5   comp8
		       TransLinearItem[CoordIndex][CompIndex][2]= 0x040;//b3    type[2]   for comp2  comp5   comp8
               } 
  
	   }
			
		
//the XOR values of  linear items  in the all possible composed items.		
	
    Masked_InputIndex=0;
	for (abcd=0;abcd<16;abcd++)
	{
	   for(a1b1c1d1=0;a1b1c1d1<16;a1b1c1d1++)
	    {
			a1=(a1b1c1d1>>0)&0x1;
			b1=(a1b1c1d1>>1)&0x1;
	    	c1=(a1b1c1d1>>2)&0x1;
	    	d1=(a1b1c1d1>>3)&0x1;
			
			
	    	for(a2b2c2d2=0;a2b2c2d2<16;a2b2c2d2++)
	    	{
	    		a3b3c3d3=abcd^a1b1c1d1^a2b2c2d2;
				
				a2=(a2b2c2d2>>0)&0x01;
				b2=(a2b2c2d2>>1)&0x01;
                c2=(a2b2c2d2>>2)&0x01;
				d2=(a2b2c2d2>>3)&0x01;
				
				a3=(a3b3c3d3>>0)&0x01;
				b3=(a3b3c3d3>>1)&0x01;
                c3=(a3b3c3d3>>2)&0x01;
				d3=(a3b3c3d3>>3)&0x01;
				
                for(CompIndex=0;CompIndex<9;CompIndex++)
	               {
	            	  XorValue[CoordIndex][CompIndex][0][Masked_InputIndex]=0; // type[0] for comp0----8
	            	   
	            	if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=a1  ; //a1  type[1]   for comp0  comp3   comp6
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]= b1  ; //b1  type[2]   for comp0  comp3   comp6
	            		  } 
	            	else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=a2    ; //a2 type[1]   for comp1  comp4   comp7
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=b2    ; //b2  type[2]   for comp1  comp4   comp7
	            	       } 
	            	else 
	            		   {
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=a3;//a3 type[1]   for comp2  comp5   comp8
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=b3;//b3  type[2]   for comp2  comp5   comp8
	            	       } 

	               }

				Masked_InputIndex++;
			}
		}
	}
 } 
 /*TableType2
 
        type[0]    type[1]    type[2]    
comp_0     0         b1         c1          
comp_1     0         b2         c2          
comp_2     0         b3         c3          
-----------------------------------------
comp_3     0         b1         c1          
comp_4     0         b2         c2          
comp_5     0         b3         c3          
-----------------------------------------
comp_6     0         b1         c1          
comp_7     0         b2         c2          
comp_8     0         b3         c3          
-----------------------------------------
*/
void TransLinearItem_d3Sc123b123(unsigned char CoordIndex,   unsigned short  TransLinearItem[4][9][4],unsigned char*   XorValue[4][9][4]) 
 {
	 unsigned short	Masked_InputIndex,i;
	unsigned char  abcd,a1b1c1d1,a2b2c2d2,a3b3c3d3;
	
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3,CompIndex;

	 // the linear items  in the all possible composed items in our bebuiled Table.	
		 
	  for(CompIndex=0;CompIndex<9;CompIndex++)
	   {
		   TransLinearItem[CoordIndex][CompIndex][0]=0; // type[0] for comp0----8
		   
		   if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x100  ; //b1   type[1]   for comp0  comp3   comp6
		       TransLinearItem[CoordIndex][CompIndex][2]= 0x020  ; //c1  type[2]   for comp0  comp3   comp6
			  } 
		  else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x080    ; //b2   type[1]   for comp1  comp4   comp7
		       TransLinearItem[CoordIndex][CompIndex][2]= 0x010  ; //c2   type[2]   for comp1  comp4   comp7
              } 
		  else 
			  { 
			  TransLinearItem[CoordIndex][CompIndex][1]=0x040;//b3   type[1]   for comp2  comp5   comp8
		       TransLinearItem[CoordIndex][CompIndex][2]= 0x008  ;//c3   type[2]   for comp2  comp5   comp8
               } 
  
	   }
			
		
//the XOR values of  linear items  in the all possible composed items.		
	
    Masked_InputIndex=0;
	for (abcd=0;abcd<16;abcd++)
	{
	   for(a1b1c1d1=0;a1b1c1d1<16;a1b1c1d1++)
	    {
			a1=(a1b1c1d1>>0)&0x1;
			b1=(a1b1c1d1>>1)&0x1;
	    	c1=(a1b1c1d1>>2)&0x1;
	    	d1=(a1b1c1d1>>3)&0x1;
			
			
	    	for(a2b2c2d2=0;a2b2c2d2<16;a2b2c2d2++)
	    	{
	    		a3b3c3d3=abcd^a1b1c1d1^a2b2c2d2;
				
				a2=(a2b2c2d2>>0)&0x01;
				b2=(a2b2c2d2>>1)&0x01;
                c2=(a2b2c2d2>>2)&0x01;
				d2=(a2b2c2d2>>3)&0x01;
				
				a3=(a3b3c3d3>>0)&0x01;
				b3=(a3b3c3d3>>1)&0x01;
                c3=(a3b3c3d3>>2)&0x01;
				d3=(a3b3c3d3>>3)&0x01;
				
                for(CompIndex=0;CompIndex<9;CompIndex++)
	               {
	            	  XorValue[CoordIndex][CompIndex][0][Masked_InputIndex]=0; // type[0] for comp0----8
	            	   
	            	if((CompIndex==0)||(CompIndex==3)||(CompIndex==6))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=b1  ; //b1  type[1]   for comp0  comp3   comp6
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]= c1  ; //c1  type[2]   for comp0  comp3   comp6
	            		  } 
	            	else if((CompIndex==1)||(CompIndex==4)||(CompIndex==7))
	            		  { 
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=b2    ; //b2 type[1]   for comp1  comp4   comp7
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=c2    ; //c2  type[2]   for comp1  comp4   comp7
	            	       } 
	            	else 
	            		   {
						   XorValue[CoordIndex][CompIndex][1][Masked_InputIndex]=b3;//b3 type[1]   for comp2  comp5   comp8
	            	       XorValue[CoordIndex][CompIndex][2][Masked_InputIndex]=c3;//c3  type[2]   for comp2  comp5   comp8
	            	       } 

	               }

				Masked_InputIndex++;
			}
		}
	}
 } 







void NotTrans(unsigned char CoordIndex,   unsigned short  TransLinearItem[4][9][4],unsigned char*   XorValue[4][9][4]) 
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

void MakeSearchDisUnifTable(unsigned short  InitLinearItem[4][9],unsigned short  TransLinearItem[4][9][4],unsigned char*   XorValue[4][9][4], unsigned char TableType[4]
)// InitLinearItem1[CompIndex]:CompIndex:0-8;  TransLinearItem[CompIndex][Type]:Type:0-7, XorValue[CompIndex][Type][Masked_InputIndex]: Masked_InputIndex:0-4095.
{

	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3;
	unsigned char   CoordIndex,CompIndex;
	unsigned short  InitLinearItem1[4][9];
	unsigned char   ShiftNum;
	unsigned short  TshareValue;
	
	unsigned char  f0[9], f1[9],f2[9],f3[9];
	
	
	
    for(CoordIndex=0;CoordIndex<4;CoordIndex++)
    {
		for(CompIndex=0;CompIndex<9;CompIndex++)
		{
			InitLinearItem[CoordIndex][CompIndex]=0;
		}
	}


	for(ShiftNum=0;ShiftNum<12;ShiftNum++)
	{
		TshareValue=1<<ShiftNum;
		a1=(TshareValue>>11)&1; a2=(TshareValue>>10)&1; a3=(TshareValue>>9)&1;
		b1=(TshareValue>>8)&1; b2=(TshareValue>>7)&1; b3=(TshareValue>>6)&1;
		c1=(TshareValue>>5)&1; c2=(TshareValue>>4)&1; c3=(TshareValue>>3)&1;
		d1=(TshareValue>>2)&1; d2=(TshareValue>>1)&1; d3=(TshareValue>>0)&1;
         
	// 3  need to  change  with different implementations.the linear items in the  9 initail components 		

		f0[0]=d1&b1    ;
	    f0[1]=d1&b2^a2   ;
	    f0[2]=d1&b3      ;
	    f0[3]=d2&b1^a1   ;
	    f0[4]=d2&b2      ;
	    f0[5]=d2&b3      ;
	    f0[6]=d3&b1      ;
	    f0[7]=d3&b2      ;
	    f0[8]=d3&b3^a3   ;

		f1[0]= d1&c1      ;
		f1[1]= d1&c2^b2     ;
		f1[2]= d1&c3        ;
		f1[3]= d2&c1^b1     ;
		f1[4]= d2&c2        ;
		f1[5]= d2&c3        ;
		f1[6]= d3&c1        ;
		f1[7]= d3&c2        ;
		f1[8]= d3&c3^b3     ;
		
	   
	    
		
		for(CompIndex=0;CompIndex<9;CompIndex++)
		{
		  if(f0[CompIndex])
			 InitLinearItem[0][CompIndex] |=TshareValue;
		  if(f1[CompIndex])
			 InitLinearItem[2][CompIndex] |=TshareValue;
		}

	}

   for( CoordIndex=0;CoordIndex<4;CoordIndex++)
		{
			
			if(TableType[CoordIndex]==D3SameIntuple_b123a123)	
			    TransLinearItem_d3Sb123a123(CoordIndex,   TransLinearItem, XorValue);
			if(TableType[CoordIndex]==D3SameIntuple_c123b123)
				TransLinearItem_d3Sc123b123(CoordIndex,   TransLinearItem, XorValue);
			
			else
				NotTrans(CoordIndex,   TransLinearItem, XorValue);
			
		}

}


/*TableType1
b&c ^ c&d ^ c ^ d,   b&c ^ c&d ^ d 
*/




void  InputTableIndexGen_NLdbLa(unsigned char  Type[4][9],  unsigned char CoordIndex, unsigned short  InitTranComLinearItem[4][9], unsigned char*   InputTableIndex[4][9],unsigned short  InitLinearItem[4][9],unsigned short  TransLinearItem[4][9][4])
{
	unsigned int  CompIndex, InputMask,OutShare,i;
	unsigned char  abcd,a1b1c1d1,a2b2c2d2,a3b3c3d3;
	unsigned short	Masked_InputIndex,TypeIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3;
	
	for(CompIndex=0;CompIndex<9;CompIndex++)	
	{
		InitTranComLinearItem[CoordIndex][CompIndex]=InitLinearItem[CoordIndex][CompIndex]^TransLinearItem[CoordIndex][CompIndex][Type[CoordIndex][CompIndex]];
	}

    Masked_InputIndex = 0;
	for (abcd=0;abcd<16;abcd++)
	{
	   for(a1b1c1d1=0;a1b1c1d1<16;a1b1c1d1++)
	    {
			a1=(a1b1c1d1>>0)&0x1;
			b1=(a1b1c1d1>>1)&0x1;
	    	c1=(a1b1c1d1>>2)&0x1;
	    	d1=(a1b1c1d1>>3)&0x1;
			
			
	    	for(a2b2c2d2=0;a2b2c2d2<16;a2b2c2d2++)
	    	{
	    		a3b3c3d3=abcd^a1b1c1d1^a2b2c2d2;
				
				a2=(a2b2c2d2>>0)&0x01;
				b2=(a2b2c2d2>>1)&0x01;
                c2=(a2b2c2d2>>2)&0x01;
				d2=(a2b2c2d2>>3)&0x01;
				
				a3=(a3b3c3d3>>0)&0x01;
				b3=(a3b3c3d3>>1)&0x01;
                c3=(a3b3c3d3>>2)&0x01;
				d3=(a3b3c3d3>>3)&0x01;
				//---component 0  



				//---component 0
                if ((InitTranComLinearItem[CoordIndex][0] &0xe00)==0x800)
				     InputTableIndex[CoordIndex][0][Masked_InputIndex]=(a1<<2)|(b1<<1)|(d1<<0);
				
				 else 
					 InputTableIndex[CoordIndex][0][Masked_InputIndex]=(b1<<1)|(d1<<0); 
					//printf("InputTableIndex[%d][0][%d]:%d \n",CoordIndex,Masked_InputIndex,InputTableIndex[CoordIndex][0][Masked_InputIndex]);
				//---component 1
				 if ((InitTranComLinearItem[CoordIndex][1] &0xe00)==0x400)
				     InputTableIndex[CoordIndex][1][Masked_InputIndex]=(a2<<2)|(b2<<1)|(d1<<0); 
				
                else
                    InputTableIndex[CoordIndex][1][Masked_InputIndex]=(b2<<1)|(d1<<0); 	
					//printf("InputTableIndex[%d][1][%d]:%d \n",CoordIndex,Masked_InputIndex,InputTableIndex[CoordIndex][0][Masked_InputIndex]);				
				//---component 2 
				if ((InitTranComLinearItem[CoordIndex][2] &0xe00)==0x200)
				     InputTableIndex[CoordIndex][2][Masked_InputIndex]=(a3<<2)|(b3<<1)|(d1<<0);  
				else
					 InputTableIndex[CoordIndex][2][Masked_InputIndex]=(b3<<1)|(d1<<0);  
				 
                //---component 3
				if ((InitTranComLinearItem[CoordIndex][3] &0xe00)==0x800)
				     InputTableIndex[CoordIndex][3][Masked_InputIndex]=(a1<<2)|(b1<<1)|(d2<<0);
				
				else
					InputTableIndex[CoordIndex][3][Masked_InputIndex]=(b1<<1)|(d2<<0); 
				 
				 //---component 4

				 if ((InitTranComLinearItem[CoordIndex][4] &0xe00)==0x400)
				     InputTableIndex[CoordIndex][4][Masked_InputIndex]=(a2<<2)|(b2<<1)|(d2<<0); 
				
				 else
					InputTableIndex[CoordIndex][4][Masked_InputIndex]=(b2<<1)|(d2<<0); 
				//---component 5
				if ((InitTranComLinearItem[CoordIndex][5] &0xe00)==0x200)
				     InputTableIndex[CoordIndex][5][Masked_InputIndex]=(a3<<2)|(b3<<1)|(d2<<0);
				else 
					InputTableIndex[CoordIndex][5][Masked_InputIndex]=(b3<<1)|(d2<<0);

                //---component 6
				if ((InitTranComLinearItem[CoordIndex][6] &0xe00)==0x800)
				     InputTableIndex[CoordIndex][6][Masked_InputIndex]=(a1<<2)|(b1<<1)|(d3<<0);
				
				else 
          			InputTableIndex[CoordIndex][6][Masked_InputIndex]=(b1<<1)|(d3<<0);		
				 //---component 7
				 if ((InitTranComLinearItem[CoordIndex][7] &0xe00)==0x400)
				     InputTableIndex[CoordIndex][7][Masked_InputIndex]=(a2<<2)|(b2<<1)|(d3<<0); 

				else 
          			InputTableIndex[CoordIndex][7][Masked_InputIndex]=(b2<<1)|(d3<<0);
                //---component 8
				 if ((InitTranComLinearItem[CoordIndex][8] &0xe00)==0x200)
				     InputTableIndex[CoordIndex][8][Masked_InputIndex]=(a3<<2)|(b3<<1)|(d3<<0);
				else 
          			InputTableIndex[CoordIndex][8][Masked_InputIndex]=(b3<<1)|(d3<<0);
          			
          			Masked_InputIndex++;

			}
		}
	}

}


void InputTableIndexGen_NLdcLb( unsigned char  Type[4][9], unsigned char CoordIndex, unsigned short  InitTranComLinearItem[4][9], unsigned char*   InputTableIndex[4][9],unsigned short  InitLinearItem[4][9],unsigned short  TransLinearItem[4][9][4])
{	
	unsigned int  CompIndex, InputMask,OutShare,i;
	unsigned char  abcd,a1b1c1d1,a2b2c2d2,a3b3c3d3;
	unsigned short	Masked_InputIndex,TypeIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3;
    
   

	for(CompIndex=0;CompIndex<9;CompIndex++)	
	{
		InitTranComLinearItem[CoordIndex][CompIndex]=InitLinearItem[CoordIndex][CompIndex]^TransLinearItem[CoordIndex][CompIndex][Type[CoordIndex][CompIndex]];
		
	}

    Masked_InputIndex = 0;
	for (abcd=0;abcd<16;abcd++)
	{
	   for(a1b1c1d1=0;a1b1c1d1<16;a1b1c1d1++)
	    {
			a1=(a1b1c1d1>>0)&0x1;
			b1=(a1b1c1d1>>1)&0x1;
	    	c1=(a1b1c1d1>>2)&0x1;
	    	d1=(a1b1c1d1>>3)&0x1;
			
			
	    	for(a2b2c2d2=0;a2b2c2d2<16;a2b2c2d2++)
	    	{
	    		a3b3c3d3=abcd^a1b1c1d1^a2b2c2d2;
				
				a2=(a2b2c2d2>>0)&0x01;
				b2=(a2b2c2d2>>1)&0x01;
                c2=(a2b2c2d2>>2)&0x01;
				d2=(a2b2c2d2>>3)&0x01;
				
				a3=(a3b3c3d3>>0)&0x01;
				b3=(a3b3c3d3>>1)&0x01;
                c3=(a3b3c3d3>>2)&0x01;
				d3=(a3b3c3d3>>3)&0x01;

				//---component 0
                if ((InitTranComLinearItem[CoordIndex][0] &0x1c0)==0x100)
				     InputTableIndex[CoordIndex][0][Masked_InputIndex]=(b1<<2)|(c1<<1)|(d1<<0);
				else if ((InitTranComLinearItem[CoordIndex][0] &0x1c0)==0x080)
				     InputTableIndex[CoordIndex][0][Masked_InputIndex]=(b2<<2)|(c1<<1)|(d1<<0); 
				else if ((InitTranComLinearItem[CoordIndex][0] &0x1c0)==0x040)
				     InputTableIndex[CoordIndex][0][Masked_InputIndex]=(b3<<2)|(c1<<1)|(d1<<0); 
				 else 
					 InputTableIndex[CoordIndex][0][Masked_InputIndex]=(c1<<1)|(d1<<0); 
					//printf("InputTableIndex[%d][0][%d]:%d \n",CoordIndex,Masked_InputIndex,InputTableIndex[CoordIndex][0][Masked_InputIndex]);
				//---component 1
				if ((InitTranComLinearItem[CoordIndex][1] &0x1c0)==0x100)
				     InputTableIndex[CoordIndex][1][Masked_InputIndex]=(b1<<2)|(c2<<1)|(d1<<0);
				else if ((InitTranComLinearItem[CoordIndex][1] &0x1c0)==0x080)
				     InputTableIndex[CoordIndex][1][Masked_InputIndex]=(b2<<2)|(c2<<1)|(d1<<0); 
				else if ((InitTranComLinearItem[CoordIndex][1] &0x1c0)==0x040)
				     InputTableIndex[CoordIndex][1][Masked_InputIndex]=(b3<<2)|(c2<<1)|(d1<<0); 
                else
                    InputTableIndex[CoordIndex][1][Masked_InputIndex]=(c2<<1)|(d1<<0); 	
					//printf("InputTableIndex[%d][1][%d]:%d \n",CoordIndex,Masked_InputIndex,InputTableIndex[CoordIndex][0][Masked_InputIndex]);				
				//---component 2 
				if ((InitTranComLinearItem[CoordIndex][2] &0x1c0)==0x100)
				     InputTableIndex[CoordIndex][2][Masked_InputIndex]=(b1<<2)|(c3<<1)|(d1<<0);
				else if ((InitTranComLinearItem[CoordIndex][2] &0x1c0)==0x080)
				     InputTableIndex[CoordIndex][2][Masked_InputIndex]=(b2<<2)|(c3<<1)|(d1<<0); 
				else if ((InitTranComLinearItem[CoordIndex][2] &0x1c0)==0x040)
				     InputTableIndex[CoordIndex][2][Masked_InputIndex]=(b3<<2)|(c3<<1)|(d1<<0);  
				else
					 InputTableIndex[CoordIndex][2][Masked_InputIndex]=(c3<<1)|(d1<<0);  
				 
                //---component 3
				if ((InitTranComLinearItem[CoordIndex][3] &0x1c0)==0x100)
				     InputTableIndex[CoordIndex][3][Masked_InputIndex]=(b1<<2)|(c1<<1)|(d2<<0);
				else if ((InitTranComLinearItem[CoordIndex][3] &0x1c0)==0x080)
				     InputTableIndex[CoordIndex][3][Masked_InputIndex]=(b2<<2)|(c1<<1)|(d2<<0); 
				else if ((InitTranComLinearItem[CoordIndex][3] &0x1c0)==0x040)
				     InputTableIndex[CoordIndex][3][Masked_InputIndex]=(b3<<2)|(c1<<1)|(d2<<0);  
				else
					InputTableIndex[CoordIndex][3][Masked_InputIndex]=(c1<<1)|(d2<<0); 
				 
				 //---component 4

				if ((InitTranComLinearItem[CoordIndex][4] &0x1c0)==0x100)
				     InputTableIndex[CoordIndex][4][Masked_InputIndex]=(b1<<2)|(c2<<1)|(d2<<0);
				else if ((InitTranComLinearItem[CoordIndex][4] &0x1c0)==0x080)
				     InputTableIndex[CoordIndex][4][Masked_InputIndex]=(b2<<2)|(c2<<1)|(d2<<0); 
				else if ((InitTranComLinearItem[CoordIndex][4] &0x1c0)==0x040)
				     InputTableIndex[CoordIndex][4][Masked_InputIndex]=(b3<<2)|(c2<<1)|(d2<<0);
				 else
					InputTableIndex[CoordIndex][4][Masked_InputIndex]=(c2<<1)|(d2<<0); 
				//---component 5
				if ((InitTranComLinearItem[CoordIndex][5] &0x1c0)==0x100)
				     InputTableIndex[CoordIndex][5][Masked_InputIndex]=(b1<<2)|(c3<<1)|(d2<<0);
				else if ((InitTranComLinearItem[CoordIndex][5] &0x1c0)==0x080)
				     InputTableIndex[CoordIndex][5][Masked_InputIndex]=(b2<<2)|(c3<<1)|(d2<<0); 
				else if ((InitTranComLinearItem[CoordIndex][5] &0x1c0)==0x040)
				     InputTableIndex[CoordIndex][5][Masked_InputIndex]=(b3<<2)|(c3<<1)|(d2<<0);
				else 
					InputTableIndex[CoordIndex][5][Masked_InputIndex]=(c3<<1)|(d2<<0);

                //---component 6
				if ((InitTranComLinearItem[CoordIndex][6] &0x1c0)==0x100)
				     InputTableIndex[CoordIndex][6][Masked_InputIndex]=(b1<<2)|(c1<<1)|(d3<<0);
				else if ((InitTranComLinearItem[CoordIndex][6] &0x1c0)==0x080)
				     InputTableIndex[CoordIndex][6][Masked_InputIndex]=(b2<<2)|(c1<<1)|(d3<<0); 
				else if ((InitTranComLinearItem[CoordIndex][6] &0x1c0)==0x040)
				     InputTableIndex[CoordIndex][6][Masked_InputIndex]=(b3<<2)|(c1<<1)|(d3<<0);
				else 
          			InputTableIndex[CoordIndex][6][Masked_InputIndex]=(c1<<1)|(d3<<0);		
				 //---component 7
				if ((InitTranComLinearItem[CoordIndex][7] &0x1c0)==0x100)
				     InputTableIndex[CoordIndex][7][Masked_InputIndex]=(b1<<2)|(c2<<1)|(d3<<0);
				else if ((InitTranComLinearItem[CoordIndex][7] &0x1c0)==0x080)
				     InputTableIndex[CoordIndex][7][Masked_InputIndex]=(b2<<2)|(c2<<1)|(d3<<0); 
				else if ((InitTranComLinearItem[CoordIndex][7] &0x1c0)==0x040)
				     InputTableIndex[CoordIndex][7][Masked_InputIndex]=(b3<<2)|(c2<<1)|(d3<<0);
				else 
          			InputTableIndex[CoordIndex][7][Masked_InputIndex]=(c2<<1)|(d3<<0);
                //---component 8
				if ((InitTranComLinearItem[CoordIndex][8] &0x1c0)==0x100)
				     InputTableIndex[CoordIndex][8][Masked_InputIndex]=(b1<<2)|(c3<<1)|(d3<<0);
				else if ((InitTranComLinearItem[CoordIndex][8] &0x1c0)==0x080)
				     InputTableIndex[CoordIndex][8][Masked_InputIndex]=(b2<<2)|(c3<<1)|(d3<<0); 
				else if ((InitTranComLinearItem[CoordIndex][8] &0x1c0)==0x040)
				     InputTableIndex[CoordIndex][8][Masked_InputIndex]=(b3<<2)|(c3<<1)|(d3<<0);
				else 
          			InputTableIndex[CoordIndex][8][Masked_InputIndex]=(c3<<1)|(d3<<0);
          			
          			Masked_InputIndex++;

			}
		}
	}

}




void MakeLargeTables( unsigned char  Type[4][9], unsigned char*     InputTableIndex[4][9], unsigned char*     F3FullMaskValue[4][3],unsigned char*     F3To1UnMaskValue[4][3],unsigned char*   XorValue[4][9][4],unsigned short  InitLinearItem[4][9],unsigned short  TransLinearItem[4][9][4],unsigned short  InitTranComLinearItem[4][9],unsigned char ExpressionType[4])
{
    unsigned int   CompIndex, InputMask,OutShare,i,j;
	unsigned char  abcd,a1b1c1d1,a2b2c2d2,a3b3c3d3;
	unsigned short	Masked_InputIndex,TypeIndex;
	unsigned char  a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3;
	unsigned char  f0_1,f0_2,f0_3,f0_4,f0_5,f0_6,f0_7,f0_8,f0_9;
	unsigned char  f1_1,f1_2,f1_3,f1_4,f1_5,f1_6,f1_7,f1_8,f1_9;
    unsigned char  f1_1c,f1_2c,f1_3c,f1_4c,f1_5c,f1_6c,f1_7c,f1_8c,f1_9c;
	
	unsigned char  f2_1,f2_2,f2_3,f2_4,f2_5,f2_6,f2_7,f2_8,f2_9;
		unsigned char  f2_1c,f2_2c,f2_3c,f2_4c,f2_5c,f2_6c,f2_7c,f2_8c,f2_9c;
	unsigned char  f3_1,f3_2,f3_3,f3_4,f3_5,f3_6,f3_7,f3_8,f3_9;
	
	unsigned char  CoordIndex;
	
	// need to  change change  the compIndex according to  the linear tranfer components 

	  
 for(CoordIndex=0;CoordIndex<4;CoordIndex++)
	 {
		 if(ExpressionType[CoordIndex]==EType_dANDbXORa )
		     InputTableIndexGen_NLdbLa(Type,CoordIndex,InitTranComLinearItem, InputTableIndex,InitLinearItem,TransLinearItem);
		 else if(ExpressionType[CoordIndex]==EType_dANDcXORb )
		     InputTableIndexGen_NLdcLb(Type,CoordIndex,InitTranComLinearItem, InputTableIndex,InitLinearItem,TransLinearItem);
	 }

	Masked_InputIndex = 0;
	for (abcd=0;abcd<16;abcd++)
	{
	   for(a1b1c1d1=0;a1b1c1d1<16;a1b1c1d1++)
	    {
			a1=(a1b1c1d1>>0)&0x1;
			b1=(a1b1c1d1>>1)&0x1;
	    	c1=(a1b1c1d1>>2)&0x1;
	    	d1=(a1b1c1d1>>3)&0x1;
			
			
	    	for(a2b2c2d2=0;a2b2c2d2<16;a2b2c2d2++)
	    	{
	    		a3b3c3d3=abcd^a1b1c1d1^a2b2c2d2;
				
				a2=(a2b2c2d2>>0)&0x01;
				b2=(a2b2c2d2>>1)&0x01;
                c2=(a2b2c2d2>>2)&0x01;
				d2=(a2b2c2d2>>3)&0x01;
				
				a3=(a3b3c3d3>>0)&0x01;
				b3=(a3b3c3d3>>1)&0x01;
                c3=(a3b3c3d3>>2)&0x01;
				d3=(a3b3c3d3>>3)&0x01;
				
				
				
				CoordIndex=2;
				InputTableIndex[CoordIndex][0][Masked_InputIndex]=(c1<<1);
				InputTableIndex[CoordIndex][1][Masked_InputIndex]=0;
				InputTableIndex[CoordIndex][2][Masked_InputIndex]=0;
				InputTableIndex[CoordIndex][3][Masked_InputIndex]=0;
				InputTableIndex[CoordIndex][4][Masked_InputIndex]=(c2<<1);
				InputTableIndex[CoordIndex][5][Masked_InputIndex]=0;
				InputTableIndex[CoordIndex][6][Masked_InputIndex]=0;
				InputTableIndex[CoordIndex][7][Masked_InputIndex]=0;
				InputTableIndex[CoordIndex][8][Masked_InputIndex]=(c3<<1);				
				
				CoordIndex=3;
				InputTableIndex[CoordIndex][0][Masked_InputIndex]=(d1<<1);
				InputTableIndex[CoordIndex][1][Masked_InputIndex]=0;
				InputTableIndex[CoordIndex][2][Masked_InputIndex]=0;
				InputTableIndex[CoordIndex][3][Masked_InputIndex]=0;
				InputTableIndex[CoordIndex][4][Masked_InputIndex]=(d2<<1);
				InputTableIndex[CoordIndex][5][Masked_InputIndex]=0;
				InputTableIndex[CoordIndex][6][Masked_InputIndex]=0;
				InputTableIndex[CoordIndex][7][Masked_InputIndex]=0;
				InputTableIndex[CoordIndex][8][Masked_InputIndex]=(d3<<1);	
				
				

				/* 2 need to  change the   after fi_j =   the expressions */
			    // coordinate_0 initial expression+ possible linear item in the search process
				f0_1=d1&b1 ^1    ^ XorValue[0][0][Type[0][0]][Masked_InputIndex];
				f0_2=d1&b2^a2    ^ XorValue[0][1][Type[0][1]][Masked_InputIndex];
				f0_3=d1&b3       ^ XorValue[0][2][Type[0][2]][Masked_InputIndex];
				f0_4=d2&b1^a1^ XorValue[0][3][Type[0][3]][Masked_InputIndex];
				f0_5=d2&b2   ^ XorValue[0][4][Type[0][4]][Masked_InputIndex];
				f0_6=d2&b3   ^ XorValue[0][5][Type[0][5]][Masked_InputIndex];
				f0_7=d3&b1    ^ XorValue[0][6][Type[0][6]][Masked_InputIndex]   ;
                f0_8=d3&b2    ^ XorValue[0][7][Type[0][7]][Masked_InputIndex]   ;
                f0_9=d3&b3^a3 ^ XorValue[0][8][Type[0][8]][Masked_InputIndex]    ;				
				
				
				F3FullMaskValue[0][0][Masked_InputIndex]=(f0_3<<2)|(f0_2<<1)|(f0_1<<0);
				F3To1UnMaskValue[0][0][Masked_InputIndex]=f0_1^f0_2^f0_3;

				F3FullMaskValue[0][1][Masked_InputIndex]=(f0_6<<2)|(f0_5<<1)|(f0_4<<0);
				F3To1UnMaskValue[0][1][Masked_InputIndex]=f0_6^f0_5^f0_4;
 
				F3FullMaskValue[0][2][Masked_InputIndex]=(f0_9<<2)|(f0_8<<1)|(f0_7<<0);
				F3To1UnMaskValue[0][2][Masked_InputIndex]=f0_9^f0_8^f0_7;
				
				// coordinate_1


				f1_1=d1&c1 ^1     ^ XorValue[1][0][Type[1][0]][Masked_InputIndex]   ;
                f1_2=d1&c2^b2     ^ XorValue[1][1][Type[1][1]][Masked_InputIndex]   ;
                f1_3=d1&c3        ^ XorValue[1][2][Type[1][2]][Masked_InputIndex]   ;
				f1_4=d2&c1^b1    ^ XorValue[1][3][Type[1][3]][Masked_InputIndex]            ;
                f1_5=d2&c2       ^ XorValue[1][4][Type[1][4]][Masked_InputIndex]            ;
                f1_6=d2&c3       ^ XorValue[1][5][Type[1][5]][Masked_InputIndex]            ;
				f1_7=d3&c1        ^ XorValue[1][6][Type[1][6]][Masked_InputIndex]   ; 
                f1_8=d3&c2        ^ XorValue[1][7][Type[1][7]][Masked_InputIndex]   ; 
                f1_9=d3&c3^b3     ^ XorValue[1][8][Type[1][8]][Masked_InputIndex]    ;                 
	                
         
                
				F3FullMaskValue[1][0][Masked_InputIndex]=(f1_3<<2)|(f1_2<<1)|(f1_1<<0);
				F3To1UnMaskValue[1][0][Masked_InputIndex]=f1_1^f1_2^f1_3;

				F3FullMaskValue[1][1][Masked_InputIndex]=(f1_6<<2)|(f1_5<<1)|(f1_4<<0);
				F3To1UnMaskValue[1][1][Masked_InputIndex]=f1_6^f1_5^f1_4;

				F3FullMaskValue[1][2][Masked_InputIndex]=(f1_9<<2)|(f1_8<<1)|(f1_7<<0);
				F3To1UnMaskValue[1][2][Masked_InputIndex]=f1_9^f1_8^f1_7;


				// coordinate_2

				f2_1=c1^1 ;
                f2_2=0    ;
				f2_3=0    ;
				f2_4=0    ;
                f2_5=c2   ;
				f2_6= 0   ;
				f2_7= 0   ;
                f2_8= 0   ;
				f2_9=c3   ;
				
				
				F3FullMaskValue[2][0][Masked_InputIndex]=(f2_3<<2)|(f2_2<<1)|(f2_1<<0);
				F3To1UnMaskValue[2][0][Masked_InputIndex]=f2_1^f2_2^f2_3;

				 
				F3FullMaskValue[2][1][Masked_InputIndex]=(f2_6<<2)|(f2_5<<1)|(f2_4<<0);
				F3To1UnMaskValue[2][1][Masked_InputIndex]=f2_6^f2_5^f2_4;


				F3FullMaskValue[2][2][Masked_InputIndex]=(f2_9<<2)|(f2_8<<1)|(f2_7<<0);
				F3To1UnMaskValue[2][2][Masked_InputIndex]=f2_9^f2_8^f2_7;
				
				// coordinate_3

				f3_1=d1^1 ;
				f3_2=0    ;
				f3_3=0    ;
                f3_4=0    ;
                f3_5=d2   ;
                f3_6= 0   ;
                f3_7= 0   ;
                f3_8= 0   ;
                f3_9=d3   ; 	

				
				F3FullMaskValue[3][0][Masked_InputIndex]=(f3_3<<2)|(f3_2<<1)|(f3_1<<0);
				F3To1UnMaskValue[3][0][Masked_InputIndex]=f3_1^f3_2^f3_3;

				F3FullMaskValue[3][1][Masked_InputIndex]=(f3_6<<2)|(f3_5<<1)|(f3_4<<0);
				F3To1UnMaskValue[3][1][Masked_InputIndex]=f3_6^f3_5^f3_4;
				
				F3FullMaskValue[3][2][Masked_InputIndex]=(f3_9<<2)|(f3_8<<1)|(f3_7<<0);
				F3To1UnMaskValue[3][2][Masked_InputIndex]=f3_9^f3_8^f3_7;
				Masked_InputIndex++;
			}
		}
	}
}

unsigned char  CheckSingleCoordinateDistributions(unsigned char*     InputTableIndex[4][9], unsigned char*     F3FullMaskValue[4][3],unsigned char*     DisInCoorF3COm[4][3][9],unsigned char*     DisInCoorF3F3[4][3][3],  unsigned char CoordIndexNumber)
{
unsigned int  CoordIndex, CompIndex, InputMask,OutShare, OutShare1, OutShare2,i;
	
	unsigned short	Masked_InputIndex;
	
	unsigned short	OneFCcompose,OneFFcompose;

	unsigned char   DisOld[256];
	unsigned char res;
	
	memset(DisOld,0,256);

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
	{
		for(OutShare=0;OutShare<3;OutShare++)
			for(CompIndex=0;CompIndex<9;CompIndex++)
		   {
			 for(Masked_InputIndex=0;Masked_InputIndex<Var4Share3Space;Masked_InputIndex++)
	         {
				 OneFCcompose=(InputTableIndex[CoordIndex][CompIndex][Masked_InputIndex]<<3)|F3FullMaskValue[CoordIndex][OutShare][Masked_InputIndex]  ;
			     DisInCoorF3COm[CoordIndex][OutShare][CompIndex][OneFCcompose]++;

				 if ((Masked_InputIndex & 0xFF) == 0xFF) //every256
				         if(Masked_InputIndex==0xFF)
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
	
	memset(DisOld,0,256);
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
		   	 for(Masked_InputIndex=0;Masked_InputIndex<Var4Share3Space;Masked_InputIndex++)
	         {
			    OneFFcompose=(F3FullMaskValue[CoordIndex][OutShare1][Masked_InputIndex] <<3)|F3FullMaskValue[CoordIndex][OutShare2][Masked_InputIndex]  ;
			    DisInCoorF3F3[CoordIndex][OutShare1][OutShare2][OneFFcompose]++;
				 
				if ((Masked_InputIndex & 0xFF) == 0xFF) //every256
				         if(Masked_InputIndex==0xFF)
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

unsigned char  CheckTotalDistributions(unsigned char***  InputTableIndexComp[4], unsigned char***   F3FullMaskValueComp[4], unsigned short  CaseNumComp[4], unsigned char*     Dis2CoorF3COm[4][3][4][9],unsigned char*     Dis2CoorF3F3[4][3][4][3] )
{

	unsigned int  CoordIndex,  CoordIndex1,  CoordIndex2,CompIndex, InputMask,OutShare, OutShare1, OutShare2,i;
	
	unsigned short	Masked_InputIndex;
	
	unsigned short	OneFCcompose,OneFFcompose,TwoFFcompose,TwoFCcompose;

	unsigned char   DisOld[256];
	unsigned char res;

 	memset(DisOld,0,256);	
//------------------------ verify   the independent  idential  distribution between   fi_j  and  fi_j	 between two coordinates.	
	for (CoordIndex1 = 0; CoordIndex1 < 4; CoordIndex1++)
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for (CoordIndex2 = CoordIndex1+1; CoordIndex2 < 4; CoordIndex2++)
		       for(OutShare2=0;OutShare2<3;OutShare2++)
		        {
	              memset(Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2],0,64);
				}
	}
	
   for (CoordIndex1 = 0; CoordIndex1 < 4; CoordIndex1++)
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for (CoordIndex2 = CoordIndex1+1; CoordIndex2 < 4; CoordIndex2++)
		       for(OutShare2=0;OutShare2<3;OutShare2++)
		        {
                   	 for(Masked_InputIndex=0;Masked_InputIndex<Var4Share3Space;Masked_InputIndex++)
	                 {
							TwoFFcompose=(F3FullMaskValueComp[CoordIndex1][CaseNumComp[CoordIndex1]][OutShare1][Masked_InputIndex] <<3)|F3FullMaskValueComp[CoordIndex2][CaseNumComp[CoordIndex2]][OutShare2][Masked_InputIndex]  ;
							
							
							Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2][TwoFFcompose]++;
							
							if ((Masked_InputIndex & 0xFF) == 0xFF) //every256
									if(Masked_InputIndex==0xFF)
									{
										memcpy(DisOld, Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2], 64 * sizeof(unsigned char));
										memset(Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2],0,64);
									}
									
									else{
									
										res= memcmp(DisOld, Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2], 64 * sizeof(unsigned char));

										if (res )
										{ 
                                          if((CoordIndex1 == 0)&&(CoordIndex2 ==1))	
											  return 10;
										  else if(((CoordIndex1 == 0)&&(CoordIndex2 ==2))||((CoordIndex1 == 1)&&(CoordIndex2 ==2)))	
											  return 20;
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
   for (CoordIndex1 = 0; CoordIndex1 < 4; CoordIndex1++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
			for (CoordIndex2 = 0; CoordIndex2 < 4; CoordIndex2++)
			    for(CompIndex=0;CompIndex<9;CompIndex++)
		         {
	              memset(Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex],0,256);
				 }
	}
	
	
	for (CoordIndex1 = 0; CoordIndex1 < 4; CoordIndex1++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
			for (CoordIndex2 = 0; CoordIndex2 < 4; CoordIndex2++)
			    for(CompIndex=0;CompIndex<9;CompIndex++)
		         {
			       for(Masked_InputIndex=0;Masked_InputIndex<Var4Share3Space;Masked_InputIndex++)
	                 {
				       TwoFCcompose=(InputTableIndexComp[CoordIndex2][CaseNumComp[CoordIndex2]][CompIndex][Masked_InputIndex]<<3)|F3FullMaskValueComp[CoordIndex1][CaseNumComp[CoordIndex1]][OutShare][Masked_InputIndex];

			           Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex][TwoFCcompose]++;
			    
				       if ((Masked_InputIndex & 0xFF) == 0xFF) //every256
				         if(Masked_InputIndex==0xFF)
						 {
							 
							memcpy(DisOld, Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex], 256 * sizeof(unsigned char));
							
							 memset(Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex],0,256);
							
						 }
						 
						 else{
						 	
						 	res= memcmp(DisOld, Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex], 256 * sizeof(unsigned char));

						 	if (res )
						 	    {
							        if((CoordIndex1 == 0)&&(CoordIndex2 ==1))	
								  	   return 10;
								    else if(((CoordIndex1 == 0)&&(CoordIndex2 ==2))||((CoordIndex1 == 1)&&(CoordIndex2 ==2)))	
								  	   return 20;
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

unsigned char CheckSingleUniformity( unsigned char*   F3FullMaskValue[4][3],unsigned char*     F3To1UnMaskValue[4][3], unsigned short   UniformitySOSCounter[4][3][2], unsigned short     Uniformity3OSCounter[4][8],  unsigned char CoordIndexNumber)
{
	unsigned  char CoordIndex,CompIndex,OutShare;
	unsigned short  Masked_InputIndex,i;
	unsigned char  share3Value[4][Var4Share3Space];
    unsigned short   Share12Compose[Var4Share3Space];

//-----------------------verify  the uniformity of each outshare ----------------------------------------------------------------
        CoordIndex=CoordIndexNumber;
			for(OutShare=0;OutShare<3;OutShare++)
			  {
	             memset(UniformitySOSCounter[CoordIndex][OutShare],0,4);
			  }
	    CoordIndex=CoordIndexNumber;
			for(OutShare=0;OutShare<3;OutShare++)
			  {
			    memset(UniformitySOSCounter[CoordIndex][OutShare],0,4);
				for(Masked_InputIndex=0;Masked_InputIndex<Var4Share3Space;Masked_InputIndex++)
					{
					  UniformitySOSCounter[CoordIndex][OutShare][F3To1UnMaskValue[CoordIndex][OutShare][Masked_InputIndex]]++;
					  
					  if((Masked_InputIndex&0xff)==0xff)
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
			
                for(Masked_InputIndex=0;Masked_InputIndex<Var4Share3Space;Masked_InputIndex++)
					{  
				      share3Value[CoordIndex][Masked_InputIndex]= ((F3To1UnMaskValue[CoordIndex][2][Masked_InputIndex]&0x01)<<2) |((F3To1UnMaskValue[CoordIndex][1][Masked_InputIndex]&0x01)<<1)|(F3To1UnMaskValue[CoordIndex][0][Masked_InputIndex]&0x01); 
					  Uniformity3OSCounter[CoordIndex][share3Value[CoordIndex][Masked_InputIndex]]++;
					  if(Masked_InputIndex==4095)
						{
							for(i=0;i<8;i++)
							{
								if(Uniformity3OSCounter[CoordIndex][i]!=Var4Share3Space/8)
								   {
								   return 0;
						        	}
							}
						   memset(Uniformity3OSCounter[CoordIndex],0,16);
						}
					}
return 1;	
	
}



unsigned char CheckTotalUniformity(unsigned char***   F3FullMaskValueComp[4], unsigned short  CaseNumComp[4], unsigned char*    Uniformity12OSCounter)
{
    unsigned  char CoordIndex,OutShare;
	unsigned short  Masked_InputIndex,i;
    unsigned short   Share12Compose[Var4Share3Space];
    unsigned char  OutValue[4][3];
//-------------------------verify the uniformity  of total 12 shares------------------------------------------------------------ 	
    memset(Uniformity12OSCounter,0,Var4Share3Space);
	for(Masked_InputIndex=0;Masked_InputIndex<Var4Share3Space;Masked_InputIndex++)
	{
		for(CoordIndex=0;CoordIndex<4;CoordIndex++)
	       {
	       	for(OutShare=0;OutShare<3;OutShare++)
	           {
	       	    OutValue[CoordIndex][OutShare]=((F3FullMaskValueComp[CoordIndex][CaseNumComp[CoordIndex]][OutShare][Masked_InputIndex]>>2)&1)^((F3FullMaskValueComp[CoordIndex][CaseNumComp[CoordIndex]][OutShare][Masked_InputIndex]>>1)&1)^(F3FullMaskValueComp[CoordIndex][CaseNumComp[CoordIndex]][OutShare][Masked_InputIndex]&1);
	           }
	       }
		
		Share12Compose[Masked_InputIndex]= ((OutValue[3][2]&0x01)<<11)|((OutValue[3][1]&0x01)<<10)|((OutValue[3][0]&0x01)<<9)|((OutValue[2][2]&0x01)<<8)|((OutValue[2][1]&0x01)<<7)|((OutValue[2][0]&0x01)<<6)|((OutValue[1][2]&0x01)<<5)|((OutValue[1][1]&0x01)<<4)|((OutValue[1][0]&0x01)<<3)|((OutValue[0][2]&0x01)<<2)|((OutValue[0][1]&0x01)<<1)|((OutValue[0][0]&0x01)<<0);

		
	  
	  Uniformity12OSCounter[Share12Compose[Masked_InputIndex]]++;
	  if(Uniformity12OSCounter[Share12Compose[Masked_InputIndex]]>1)
		  return 0;	
	  
	}
	
	if(Masked_InputIndex==(Var4Share3Space-1))
	  {
		  for(i=0;i<Var4Share3Space;i++)
		  {
			 if(Uniformity12OSCounter[i]!=1) 
			 {	
              return 0;	
			 }
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
	unsigned char*     InputTableIndex[4][9] = {NULL};  //InputTableIndex[CoordinateIndex][ComponentIndex][InputMask]: coordinate:{0,1,2,3};  ComponentIndex:{0,1,...,8}, InputMask:{0,1,...,4095}
	unsigned char***  InputTableIndexComp[4]= {NULL};  //InputTableIndexComp[CoordinateIndex][CaseNum][ComponentIndex][InputMask]: CaseNum:is set to be 1000,														 
	unsigned char*     F3FullMaskValue[4][3]= {NULL}; //F3FullMaskValue[CoordinateIndex][OutShare][InputMask]: coordinate:{0,1,2,3};  OutShare:{0,1,2}, InputMask:{0,1,...,4095} ；OutShare=0: f3||f2||f1;OutShare=1: f6||f5||f4; OutShare=2: f9||f8||f7;
	unsigned char***   F3FullMaskValueComp[4]= {NULL}; //F3FullMaskValueComp[CoordinateIndex][CaseNum][OutShare][InputMask]:CaseNum:is set to be 1000,												
	unsigned char*     F3To1UnMaskValue[4][3]= {NULL}; // F3To1UnMaskValue[CoordinateIndex][OutShare][InputMask]: coordinate:{0,1,2,3};  OutShare:{0,1,2}, InputMask:{0,1,...,4095}; OutShare=0: f3^f2^f1;OutShare=1: f6^f5^f4; OutShare=2: f9^f8^f7;
		
    unsigned short      UniformitySOSCounter[4][3][2];//SOS:single output share.UniformitySOS[CoordinateIndex][OutShare][UmaskValue]:coordinate:{0,1,2,3};   OutShare:{0,1,2}, UmaskValue:{0,1};  UmaskValue-> F3To1UnMaskValue[CoordinateIndex][OutShare][InputMask]
	unsigned short     Uniformity3OSCounter[4][8];//3OS:3 output shares/coordinate.UniformitySOS[CoordinateIndex][MaskValue]:coordinate:{0,1,2,3};  MaskValue:{0,1,...,7}; MaskValue-> F3FullMaskValue[CoordinateIndex][OutShare][InputMask]
	
	unsigned char*    Uniformity12OSCounter;//12OS:12 output shares  in 4 coordinates.

	unsigned char*     DisInCoorF3COm[4][3][9]={NULL}; // In only one coordinate, F3COm: ((f3||f2||f1) or(f6||f5||f4) or(f9||f8||f7) ) composed with components   DisInCoorF3COm[CoordinateIndex][OutShare][ComponentIndex][ComposeValue],coordinate:{0,1,2,3};  OutShare:{0,1,2},ComponentIndex:{0,1,...,8}, ComposeValue= F3FullMaskValue[]||InputTableIndex[]; 
	unsigned char*     DisInCoorF3F3[4][3][3]={NULL}; // In only one coordinate, e.g., F3F3:f3||f2||f1||f6||f5||f4. DisInCoorF3F3[CoordinateIndex][OutShare][OutShare][ComposeValue],coordinate:{0,1,2,3};  OutShare:{0,1,2},OutShare:{0,1,2}, ComposeValue= F3FullMaskValue[]||F3FullMaskValue[]; 
	unsigned char*     Dis2CoorF3COm[4][3][4][9]={NULL};//between two coordinates ,  Dis2CoorF3COm[CoordinateIndex][OutShare][CoordinateIndex][ComponentIndex][ComposeValue], ComposeValue= F3FullMaskValue[]||InputTableIndex[];
	
	unsigned char*     Dis2CoorF3F3[4][3][4][3]={NULL};
	unsigned char*   XorValue[4][9][4];
	unsigned char  Type[4][9],Type3,Type4,Type5;
	unsigned short  InitLinearItem[4][9];
	unsigned short  TransLinearItem[4][9][4];
    unsigned short  CaseNum[4];// the searched cases with required uniformity and distribution for simple linear compositions
    unsigned char**   DisUnifTypeCand[4];// DisUnifTypeCand[CoordIndex][CaseNumber][ComponentNum]: the Type values of 9 components in the CoordIndex for the CaseNumber
	unsigned short  InitTranComLinearItem[4][9]; //InitTranComLinearItem[CoordIndex][ComponentNum];
	unsigned char res1,res2,res3,flag;
    unsigned int  CoordIndex,CoordIndex0,CoordIndex1, CoordIndex2,CoordIndex3,CompIndex,InputMask, OutShare,OutShare1,OutShare2,i,j,m,n,p,TypeIndex;
    unsigned char TableType[4],TableTypeIndex[4]; // TableType[CoordIndex] TableTypeIndex[CoordIndex]
     time_t              tt;
     unsigned char ExpressionType[4]; //ExpressionType[CoordIndex] 
	unsigned char  TypeRage[4][9][4];
    unsigned char  TypeRageNum[4][9];
    unsigned char  TypeN[4][9];
    unsigned  short  TcaseNum,CaseNumber;
	unsigned short  CaseNumComp[4];   
	 unsigned short Masked_InputIndex;
	FILE*				F;  
	
	 time(&tt);
     printf("start to alloc,  time :%s \n",ctime(&tt));
//----------------------Allocate space-------------------------------------------------------------------
    Uniformity12OSCounter= (unsigned char*)calloc(Var4Share3Space, sizeof(unsigned char));


	for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
		   for(CompIndex=0;CompIndex<9;CompIndex++)
		   {
			   DisInCoorF3COm[CoordIndex][OutShare][CompIndex]= (unsigned char*)calloc(256, sizeof(unsigned char)); //  take this  f3||f2||f1  ||a1||b1||c1||d1 as example total have 7 bits,so 256 space  is enough
		   }
	}
	
for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
	{
		DisUnifTypeCand[CoordIndex]=(unsigned char**)calloc(CaseNumSet, sizeof(unsigned char*)); //  now  we  set to be CaseNumSet which can be changed to be larger
		for(CaseNumber=0;CaseNumber<CaseNumSet;CaseNumber++)
		{
		    DisUnifTypeCand[CoordIndex][CaseNumber]=(unsigned char*)calloc(9, sizeof(unsigned char));
		}
		   
	}
	
	for (CoordIndex1 = 0; CoordIndex1 < 4; CoordIndex1++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
		   for (CoordIndex2 = 0; CoordIndex2 < 4; CoordIndex2++)
			  for(CompIndex=0;CompIndex<9;CompIndex++)
		      {
			   Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex]= (unsigned char*)calloc(256, sizeof(unsigned char)); //  take this  f3||f2||f1  ||a1||b1||c1||d1 as example total have 7 bits,so 256 space  is enough
		      }
	}
	
	for (CoordIndex1 = 0; CoordIndex1 < 4; CoordIndex1++)
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for (CoordIndex2 = 0; CoordIndex2 < 4; CoordIndex2++)
		       for(OutShare2=0;OutShare2<3;OutShare2++)
		        {
			     Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2]= (unsigned char*)calloc(64, sizeof(unsigned char)); //  take this  f3||f2||f1  ||f6^f5^f4 as example total have 6 bits,so 64 space  is enough

		        }
	}

	for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for(OutShare2=0;OutShare2<3;OutShare2++)
		   {
			   DisInCoorF3F3[CoordIndex][OutShare1][OutShare2]= (unsigned char*)calloc(64,sizeof(unsigned char)); //  take this  f3||f2||f1  ||f6^f5^f4 as example total have 6 bits,so 64 space  is enough
		   }
	}

      for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
	  {
		for(CompIndex=0;CompIndex<9;CompIndex++)
			for(TypeIndex=0;TypeIndex<4;TypeIndex++)
		      { XorValue[CoordIndex][CompIndex][TypeIndex] = (unsigned char*)calloc(Var4Share3Space, sizeof(unsigned char));   // allocate space and set to be zero
			}
	  }
	for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
	{
		for(CompIndex=0;CompIndex<9;CompIndex++)
		   { 
	         InputTableIndex[CoordIndex][CompIndex] = (unsigned char*)calloc(Var4Share3Space, sizeof(unsigned char));   // allocate space and set to be zero
			}
	  
   }

	for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
	{
		InputTableIndexComp[CoordIndex]=(unsigned char***)calloc(CaseNumSet, sizeof(unsigned char**));
		for(CaseNumber=0;CaseNumber<CaseNumSet;CaseNumber++)
		{
		    InputTableIndexComp[CoordIndex][CaseNumber]=(unsigned char**)calloc(9, sizeof(unsigned char*));
			for(CompIndex=0;CompIndex<9;CompIndex++)
				{
				InputTableIndexComp[CoordIndex][CaseNumber][CompIndex] = (unsigned char*)calloc(Var4Share3Space, sizeof(unsigned char)); 
				}
		}
		   
	}

	for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
		    {
			 F3FullMaskValue[CoordIndex][OutShare] = (unsigned char*)calloc(Var4Share3Space, sizeof(unsigned char));
		     F3To1UnMaskValue[CoordIndex][OutShare] = (unsigned char*)calloc(Var4Share3Space, sizeof(unsigned char));
			}
			 //printf("F3FullMaskValue");  
	}
	
	
	for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
	{
		F3FullMaskValueComp[CoordIndex]=(unsigned char***)calloc(CaseNumSet, sizeof(unsigned char**));
		for(CaseNumber=0;CaseNumber<CaseNumSet;CaseNumber++)
		{
		    F3FullMaskValueComp[CoordIndex][CaseNumber]=(unsigned char**)calloc(3, sizeof(unsigned char*));
			for(OutShare=0;OutShare<3;OutShare++)
				{
				F3FullMaskValueComp[CoordIndex][CaseNumber][OutShare] = (unsigned char*)calloc(Var4Share3Space, sizeof(unsigned char)); 
				}
		}
    }
    
 
 F = fopen(FileName, "wt");	   
    
 time(&tt);
 printf("start to transt,time :%s \n",ctime(&tt));		 
 fprintf(F,"start to transt,time :%s \n",ctime(&tt)); 
  

TableType[0]=D3SameIntuple_b123a123;
TableTypeIndex[0]= D3SameIntuple_b123a123_Index;
TableType[1]=D3SameIntuple_c123b123 ;
TableTypeIndex[1]=D3SameIntuple_c123b123_Index;

TableType[2]=NoNeedTable;
TableTypeIndex[2]=NoNeedTable_Index;
TableType[3]=NoNeedTable;
TableTypeIndex[3]=NoNeedTable_Index;


MakeSearchDisUnifTable(InitLinearItem,TransLinearItem,XorValue,TableType);
for(CoordIndex = 0; CoordIndex < 4; CoordIndex++)
   {
   	memset(Type[CoordIndex],0,9);
   	CaseNum[CoordIndex]=0;
   }


ExpressionType[0]= EType_dANDbXORa   ;
ExpressionType[1]= EType_dANDcXORb;
ExpressionType[2]= EType_NoDeal; 
ExpressionType[3]= EType_NoDeal;   
#if 1
for (CoordIndex =0; CoordIndex <4; CoordIndex++)
{   
  for(Type[CoordIndex][0]=0;Type[CoordIndex][0]<TableTypeIndex[CoordIndex]; Type[CoordIndex][0]++)
   	{    
       
	    for(Type[CoordIndex][1]=0;Type[CoordIndex][1]<TableTypeIndex[CoordIndex]; Type[CoordIndex][1]++)
	       {
			for(Type[CoordIndex][2]=0;Type[CoordIndex][2]<TableTypeIndex[CoordIndex]; Type[CoordIndex][2]++)
			   {
				for(Type[CoordIndex][3]=0;Type[CoordIndex][3]<TableTypeIndex[CoordIndex]; Type[CoordIndex][3]++)
				{
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
                                          
		                                    #if 1
										   for (CompIndex=0;CompIndex<9;CompIndex++)
                                                {
										            DisUnifTypeCand[CoordIndex][ CaseNum[CoordIndex]][CompIndex]=Type[CoordIndex][CompIndex];
                                                    for(Masked_InputIndex=0; Masked_InputIndex<Var4Share3Space;Masked_InputIndex++)
											        {
											        	InputTableIndexComp[CoordIndex][CaseNum[CoordIndex]][CompIndex][Masked_InputIndex]=InputTableIndex[CoordIndex][CompIndex][Masked_InputIndex];
											        }
										        }
										     for(OutShare=0;OutShare<3;OutShare++)
											    {
											        for(Masked_InputIndex=0; Masked_InputIndex<Var4Share3Space;Masked_InputIndex++)
											        {
											        	F3FullMaskValueComp[CoordIndex][CaseNum[CoordIndex]][OutShare][Masked_InputIndex]=F3FullMaskValue[CoordIndex][OutShare][Masked_InputIndex];
											        }
											    
										        }
										      #endif 
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
	}
	#if 1 
	if(TableType[CoordIndex]==NoNeedTable)
	{
		CaseNum[CoordIndex]=0;
		for(i=0;i<9;i++)
		{
		  Type[CoordIndex][i]=0;	
		}
	    MakeLargeTables(Type, InputTableIndex,F3FullMaskValue,F3To1UnMaskValue,XorValue,InitLinearItem,TransLinearItem,InitTranComLinearItem, ExpressionType);	
		for (CompIndex=0;CompIndex<9;CompIndex++)
           {
		       DisUnifTypeCand[CoordIndex][ CaseNum[CoordIndex]][CompIndex]=Type[CoordIndex][CompIndex];
               for(Masked_InputIndex=0; Masked_InputIndex<Var4Share3Space;Masked_InputIndex++)
		      {
		         InputTableIndexComp[CoordIndex][CaseNum[CoordIndex]][CompIndex][Masked_InputIndex]= InputTableIndex[CoordIndex][CompIndex][Masked_InputIndex];
		         
		      }
		   }
		for(OutShare=0;OutShare<3;OutShare++)
		  {
		      for(Masked_InputIndex=0; Masked_InputIndex<Var4Share3Space;Masked_InputIndex++)
		      {
		      	 F3FullMaskValueComp[CoordIndex][CaseNum[CoordIndex]][OutShare][Masked_InputIndex]=F3FullMaskValue[CoordIndex][OutShare][Masked_InputIndex];
		      }
		  
		   }
	     CaseNum[CoordIndex]=1;	
	}
  #endif
  memset(Type[CoordIndex],0,9);  // Type[CoordIndex]  must be cleared  , otherwise the correctness will be wrong.

}
#endif
TcaseNum=0; 

flag=0;


#if 1
    CoordIndex0=0;
    CoordIndex1=1;
    CoordIndex2=2;
	CoordIndex3=3;
    printf("CaseNum[%d]:%d;\n",CoordIndex0, CaseNum[CoordIndex0]);
	printf("CaseNum[%d]:%d;\n",CoordIndex1, CaseNum[CoordIndex1]);
    printf("CaseNum[%d]:%d;\n",CoordIndex2, CaseNum[CoordIndex2]);
    printf("CaseNum[%d]:%d;\n",CoordIndex3, CaseNum[CoordIndex3]);
	
 for(m=0;m<CaseNum[CoordIndex0];m++)
	{
		for (j=0;j<9;j++)
        {
		  Type[CoordIndex0][j]=DisUnifTypeCand[CoordIndex0][m][j];  
	    } 
		CaseNumComp[CoordIndex0]=m;
        for(n=0;n<CaseNum[CoordIndex1];n++)
	    {
		   for (j=0;j<9;j++)
           {
		     Type[CoordIndex1][j]=DisUnifTypeCand[CoordIndex1][n][j];  
	       } 
		   CaseNumComp[CoordIndex1]=n;
		  for(p=0;p<CaseNum[CoordIndex2];p++)
			{
				for (j=0;j<9;j++)
				{
				Type[CoordIndex2][j]=DisUnifTypeCand[CoordIndex2][p][j];  
				}   
				CaseNumComp[CoordIndex2]=p;			   
				for(int k=0;k<CaseNum[CoordIndex3];k++)
					{
						for (j=0;j<9;j++)
						{
						Type[CoordIndex3][j]=DisUnifTypeCand[CoordIndex3][k][j];  
						} 
						CaseNumComp[CoordIndex3]=k;
						res1=0;
						res2=0;
						res3=0;
						res1 = CheckTotalDistributions( InputTableIndexComp,F3FullMaskValueComp,CaseNumComp,Dis2CoorF3COm,Dis2CoorF3F3); 
						
						if (res1==10)  // end the loop of f2 and f3
						{
						  p=CaseNum[CoordIndex2];//	end the loop of f2
						  k=CaseNum[CoordIndex3];//	end the loop of f3
						}
						else if(res1==20) //end the loop of f3
						{
						  k=CaseNum[CoordIndex3];//	end the loop of f3	
						}
						else if(res1==1)
						{
							res2= CheckTotalUniformity(F3FullMaskValueComp,CaseNumComp,Uniformity12OSCounter);
							if(res2)
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
							fprintf(F, "%s %s ; \n",f0BaseExpression[i],  f0AddItems[i][Type[CoordIndex0][i]]);
						   }
						  fprintf(F, "========================================\n");

							 for (i=0;i<9;i++)
						   {
							fprintf(F, "%s  %s; \n",f1BaseExpression[i],  f1AddItems[i][Type[CoordIndex0][i]]);
						   }	
						  fprintf(F, "========================================\n");
						   for (i=0;i<9;i++)
						   {
							fprintf(F, "%s ; \n",f2BaseExpression[i]);
						   }	
						   fprintf(F, "========================================\n");	
						   for (i=0;i<9;i++)
						   {
							fprintf(F, "%s ; \n",f3BaseExpression[i]);
						   }
						    if(flag==0)
							{
							time(&tt);
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

#endif


printf("TcaseNum:%d \n",TcaseNum);
fclose(F);



time(&tt);
printf("This is the end,time :%s      ",ctime(&tt));	

 	for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
       	{
       		for(CompIndex=0;CompIndex<9;CompIndex++)
       		   { 		   
                   free(InputTableIndex[CoordIndex][CompIndex]);
       			}
       		   
         }
      		    
    for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
       	{	    
       	      
		          free(DisUnifTypeCand[CoordIndex]); 
       }       	
       	
       	for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
       	{
       		for(OutShare=0;OutShare<3;OutShare++)
       		    {
       			 free(F3FullMaskValue[CoordIndex][OutShare]); 
       		     free(F3To1UnMaskValue[CoordIndex][OutShare]); 
       
       			}
       	}
		   		
for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
	  {
	     for(CompIndex=0;CompIndex<9;CompIndex++)
			for(TypeIndex=0;TypeIndex<5;TypeIndex++)
		      {  
		         free(XorValue[CoordIndex][CompIndex][TypeIndex]);
			  }
			  
	  }	  
#if 1			  
for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
		   for(CompIndex=0;CompIndex<9;CompIndex++)
		   {
			   free(DisInCoorF3COm[CoordIndex][OutShare][CompIndex]);
		   }
	}
	

	
	for (CoordIndex1 = 0; CoordIndex1 < 4; CoordIndex1++)
	{
		for(OutShare=0;OutShare<3;OutShare++)
		   for (CoordIndex2 = 0; CoordIndex2 < 4; CoordIndex2++)
			  for(CompIndex=0;CompIndex<9;CompIndex++)
		      {
			   free(Dis2CoorF3COm[CoordIndex1][OutShare][CoordIndex2][CompIndex]);
			   
		      }
	}
	
	for (CoordIndex1 = 0; CoordIndex1 < 4; CoordIndex1++)
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for (CoordIndex2 = 0; CoordIndex2 < 4; CoordIndex2++)
		       for(OutShare2=0;OutShare2<3;OutShare2++)
		        {
			     free(Dis2CoorF3F3[CoordIndex1][OutShare1][CoordIndex2][OutShare2]) ;
			     
			     
		        }
	}

	for (CoordIndex = 0; CoordIndex < 4; CoordIndex++)
	{
		for(OutShare1=0;OutShare1<3;OutShare1++)
		   for(OutShare2=0;OutShare2<3;OutShare2++)
		   {
			   free(DisInCoorF3F3[CoordIndex][OutShare1][OutShare2]);
			   
			   
		   }
	}

#endif


	

	return 0;
}
