#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int *hex_bin(int []);
int *binary4(int );
void round_keys(int []);
void des(int []);
int *sbox(int []);

int PC1[8][7]={ 57,49,41,33,25,17,9,
 		1,58,50,42,34,26,18,
 		10,2,59,51,43,35,27,
 		19,11,3,60,52,44,36,
 		63,55,47,39,31,23,15,
 		7,62,54,46,38,30,22,
 		14,6,61,53,45,37,29,
 		21,13,5,28,20,12,4
	      };
int PC2[8][6]={ 14,17,11,24,1,5,
 		3,28,15,6,21,10,
 		23,19,12,4,26,8,
 		16,7,27,20,13,2,
 		41,52,31,37,47,55,
 		30,40,51,45,33,48,
 		44,49,39,56,34,53,
 		46,42,50,36,29,32
	      };
int IP[8][8]={
		58,50,42,34,26,18,10,2,
 		60,52,44,36,28,20,12,4,
 		62,54,46,38,30,22,14,6,
 		64,56,48,40,32,24,16,8,
 		57,49,41,33,25,17,9,1,
 		59,51,43,35,27,19,11,3,
 		61,53,45,37,29,21,13,5,
 		63,55,47,39,31,23,15,7
	      };
int EP_bit[8][6]={
 		32,1,2,3,4,5,
 		4,5,6,7,8,9,
 		8,9,10,11,12,13,
 		12,13,14,15,16,17,
 		16,17,18,19,20,21,
 		20,21,22,23,24,25,
 		24,25,26,27,28,29,
 		28,29,30,31,32,1
	      };
int sb_permutation[8][4]={
 		16,7,20,21,
 		29,12,28,17,
 		1,15,23,26,
 		5,18,31,10,
 		2,8,24,14,
 		32,27,3,9,
 		19,13,30,6,
 		22,11,4,25
	      };
int ip_inverse[8][8]={
 		40,8,48,16,56,24,64,32,
 		39,7,47,15,55,23,63,31,
 		38,6,46,14,54,22,62,30,
 		37,5,45,13,53,21,61,29,
 		36,4,44,12,52,20,60,28,
 		35,3,43,11,51,19,59,27,
 		34,2,42,10,50,18,58,26,
 		33,1,41,9,49,17,57,25
	      };
int s1[4][16]={
 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13};

int s2[4][16]={
 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9};

int s3[4][16]={
 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12};

int s4[4][16]={
 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14};

int s5[4][16]={
 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3};

int s6[4][16]={
 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
 10,15,4,2,7,12,9,5,6,1,12,14,0,11,3,8,
 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13};

int s7[4][16]={
 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12};

int s8[4][16]={
 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};
int roundkey[17][49];
void main()
{
    //int key_hex[16]={1,3,3,4,5,7,7,9,9,11,11,12,13,15,15,1};
    //int key_hex[16]={5,11,5,10,5,7,6,7,6,10,5,6,6,7,6,14};
    int key_hex[16]={1,3,3,4,5,7,7,9,9,11,11,12,13,15,15,1};// input key
    int input_hex[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};// Plain Text
    //int input_hex[16]={6,7,5,10,6,9,6,7,5,14,5,10,6,11,5,10};
    int i,j,d=1,key_PC1[57],*key,key_dash[65],*plain_text,text[65],text_IP[65];	
   
    key=hex_bin(key_hex);//converting key into binary
    printf("64-bit key is: ");
    //indexing from 1 to 64
    for(i=0;i<64;i++){
	key_dash[d++]=key[i];
    }
    
    for(i=1;i<=64;i++){
	printf("%d ",key_dash[i]);
    } 
    printf("\n");
    d=1;
    //Applying PC1
    for(i=0;i<8;i++){
	for(j=0;j<7;j++){
	   key_PC1[d++]=key_dash[PC1[i][j]];
	}
    }
    printf("\nkey after Permuted Choice 1: ");
    for(i=1;i<d;i++){
	printf("%d ",key_PC1[i]);
    } 
    printf("\n\n");
    free(key);
    round_keys(key_PC1);// for generating 16 keys
   
 
    for(i=1;i<=16;i++){
	printf("Key for Round %d: ",i);
	for(j=1;j<=48;j++){
	    printf("%d ",roundkey[i][j]);
	}
	printf("\n");
    }
    printf("\n64-bit plain text is: ");
    plain_text=hex_bin(input_hex);//converting plain text into binary
    d=1;
    for(i=0;i<64;i++){
	text[d++]=plain_text[i];
    }
    for(i=1;i<=64;i++){
	printf("%d ",text[i]);
    }
    //Applying IP
    d=1;
    for(i=0;i<8;i++){
	for(j=0;j<8;j++){
	   text_IP[d++]=text[IP[i][j]];
	}
    }
    printf("\nafter IP: "); 
    for(i=1;i<=64;i++)
	printf("%d ",text_IP[i]);
    des(text_IP);

}

void des(int text_IP[65])
{
    int i,swap[65],j,k,d,textnew[65],temp[49],EP[49],xor[49],*sout,ciphertext[65];
    for(i=1;i<=16;i++){
        d=1;
	for(j=1;j<=48;j++){
	    temp[j]=roundkey[i][j];
	}
	for(j=33;j<=64;j++){
	    textnew[j-32]=text_IP[j];
	}
        for(k=0;k<8;k++){
	    for(j=0;j<6;j++){
	        EP[d++]=textnew[EP_bit[k][j]];
	    }
	}
	for(k=1;k<=48;k++){
	    xor[k]=EP[k]^temp[k];
	}
	sout=sbox(xor);
	d=1;
	for(k=0;k<8;k++){
	    for(j=0;j<4;j++){
	        EP[d++]=sout[sb_permutation[k][j]];
   	    }
	}

	for(k=1;k<=32;k++){
	    textnew[k+32]=text_IP[k]^EP[k];
	}
	//preparing input for next round
	
        printf("\nAfter round %d: ",i);
	for(k=1;k<=64;k++){
	    text_IP[k]=textnew[k];
	    printf("%d ",text_IP[k]);
	}
    }
    for(k=1;k<=32;k++){
	swap[32+k]=text_IP[k];
    }
    for(k=33;k<=64;k++){
	swap[k-32]=text_IP[k];
    }
   /* printf("\n Swap: ");
     for(k=1;k<65;k++){
	printf("%d ",swap[k]);
    }*/
    d=1;
    for(k=0;k<8;k++){
	    for(j=0;j<8;j++){
	        ciphertext[d++]=swap[ip_inverse[k][j]];
   	    }
    }
     printf("\n\nCipher text is: ");
    for(k=1;k<65;k++){
	printf("%d ",ciphertext[k]);
    }
    printf("\n");
}

int *sbox(int xor[49])
{
    int *bin,parts[8][6],i,j,d=1,row,col,*sout,temp;
    sout=(int *)malloc(sizeof(int)*33);
    for(i=0;i<8;i++){
	for(j=0;j<6;j++){
	    parts[i][j]=xor[d++];
	}
    }
    d=1;
    row=2*parts[0][0]+1*parts[0][5];
    col=8*parts[0][1]+4*parts[0][2]+2*parts[0][3]+1*parts[0][4];
    temp=s1[row][col];
    bin=binary4(temp);
    for(i=0;i<4;i++)
	sout[d++]=bin[i];
    row=2*parts[1][0]+1*parts[1][5];
    col=8*parts[1][1]+4*parts[1][2]+2*parts[1][3]+1*parts[1][4];
    temp=s2[row][col];
    bin=binary4(temp);
    for(i=0;i<4;i++)
	sout[d++]=bin[i];
    row=2*parts[2][0]+1*parts[2][5];
    col=8*parts[2][1]+4*parts[2][2]+2*parts[2][3]+1*parts[2][4];
    temp=s3[row][col];
    bin=binary4(temp);
    for(i=0;i<4;i++)
	sout[d++]=bin[i];
    row=2*parts[3][0]+1*parts[3][5];
    col=8*parts[3][1]+4*parts[3][2]+2*parts[3][3]+1*parts[3][4];
    temp=s4[row][col];
    bin=binary4(temp);
    for(i=0;i<4;i++)
	sout[d++]=bin[i];
    row=2*parts[4][0]+1*parts[4][5];
    col=8*parts[4][1]+4*parts[4][2]+2*parts[4][3]+1*parts[4][4];
    temp=s5[row][col];
    bin=binary4(temp);
    for(i=0;i<4;i++)
	sout[d++]=bin[i];
    row=2*parts[5][0]+1*parts[5][5];
    col=8*parts[5][1]+4*parts[5][2]+2*parts[5][3]+1*parts[5][4];
    temp=s6[row][col];
    bin=binary4(temp);
    for(i=0;i<4;i++)
	sout[d++]=bin[i];
    row=2*parts[6][0]+1*parts[6][5];
    col=8*parts[6][1]+4*parts[6][2]+2*parts[6][3]+1*parts[6][4];
    temp=s7[row][col];
    bin=binary4(temp);
    for(i=0;i<4;i++)
	sout[d++]=bin[i];
    row=2*parts[7][0]+1*parts[7][5];
    col=8*parts[7][1]+4*parts[7][2]+2*parts[7][3]+1*parts[7][4];
    temp=s8[row][col];
    bin=binary4(temp);
    for(i=0;i<4;i++)
	sout[d++]=bin[i];
	    
    return sout;
}

void round_keys(int key_PC1[57])
{
    int i,j,key[57],keynew[49],d,row;
    for(row=1;row<=16;row++){
	d=1;
	
	if(row==1 || row==2 || row==9 || row==16) {
    	    for(i=1;i<=27;i++)
	        key[i]=key_PC1[i+1];
    	    key[28]=key_PC1[1];
    	    for(i=29;i<=55;i++)
	        key[i]=key_PC1[i+1];
    	    key[56]=key_PC1[29];
    
       	    for(i=0;i<8;i++){
	        for(j=0;j<6;j++){
	   	    keynew[d++]=key[PC2[i][j]];
	        }
    	    }
    	    for(i=1;i<d;i++)
	        roundkey[row][i]=keynew[i];
	}
        else {
	    for(i=1;i<=26;i++)
	        key[i]=key_PC1[i+2];
	    key[27]=key_PC1[1];
    	    key[28]=key_PC1[2];
    	    for(i=29;i<=54;i++)
	        key[i]=key_PC1[i+2];
    	    key[55]=key_PC1[29];
    	    key[56]=key_PC1[30];
    
       	    for(i=0;i<8;i++){
	        for(j=0;j<6;j++){
	   	    keynew[d++]=key[PC2[i][j]];
	        }
    	    }
    	    for(i=1;i<d;i++)
	        roundkey[row][i]=keynew[i];
	    
	}
	for(i=1;i<=56;i++)
	    key_PC1[i]=key[i];
    }
   
}

int *hex_bin(int key_hex[16])
{
    int *key,k=0,i,j,temp,*temp_key;
    key=(int *)malloc(sizeof(int)*65);
    for(i=0;i<16;i++){
	temp=key_hex[i];
	temp_key=binary4(temp);
	for(j=0;j<4;j++)
	    key[k++]=temp_key[j];
	free(temp_key);
    }
    return key;
    
}

int *binary4(int temp)
{
    int mask=8;
    int *a,i=0; //mask = [1000 0000 0000 0000]
	//printf("Binary Equivalent of Plaintext : ");
    a=(int *)malloc(sizeof(int)*5);
    while(mask > 0) {
	if((temp & mask) == 0 ){
	    a[i++]=0;
	}
	else{
	    a[i++]=1;
	}
	mask = mask >> 1 ; // Right Shift
    }
	/*printf("\n");
	for(j=0;j<i;j++)
	    printf("%d",a[j]);
	printf("\n");
*/
    return a;
}

