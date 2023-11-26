#include <stdio.h>
#include <string.h>
int s,n,idx = 0;
unsigned char bytes[2000000];
unsigned char buffer[2*1024*1024];
unsigned char* in_ptr = bytes, *end_ptr, *out_ptr = buffer;
inline char getByte(){
	char tem, byte = 0, flag = 0;
	while(1){
		tem = getchar();
		if(flag==1) byte <<= 4;
		if('0'<=tem&&tem<='9'){ 
			byte += tem - '0';
			flag++;
		}else if('a'<=tem&&tem<='f') {
			byte += tem - 'a' + 10;
			flag++;
		}
		if(flag==2) break;
	}
	return byte;
}
void getLength(){
	int base = 1;
	while(1){
		n += base * ((*in_ptr)&0x7f);
		if(*(in_ptr++)<128) break;
		base *= 128;
	}
}
inline void copy(int offset,int len){
	if(offset==-1){
		memcpy(out_ptr,in_ptr,len);
		in_ptr += len;
		out_ptr += len;
	}else{
		unsigned char* ptr = out_ptr;
		while(len>0){
			int size = offset<len? offset: len;
			memcpy(out_ptr,ptr-offset,size);
			len -= size;
			out_ptr += size;
		}
	}
}
void decompress(){
	getLength();
	while(in_ptr<end_ptr){
		switch((*in_ptr)&0x3){
			case 0:{
				int tmp = (*(in_ptr++)) >> 2,len = 1;
				if(tmp<60){
					len = tmp + 1;
				}else{
					tmp -= 59;
					for(int base=1;tmp>0;tmp--,in_ptr++){
						len += (*in_ptr) * base;
						base *= 256;
					}
				}
				copy(-1,len);
				break;
			}
			case 1:{
				int len = (((*in_ptr) >> 2)&0x7) + 4;
				int offset = int((*in_ptr) >>5) * 256 + in_ptr[1];
				copy(offset,len);
				in_ptr += 2;
				break;
			}
			case 2:{
				int len = ((*in_ptr)>>2) + 1, offset = (in_ptr[1] + in_ptr[2]*256);
				copy(offset,len);
				in_ptr += 3;
				break;
			}
		}
	}
}
inline char int2HexChar(int val){
	return (val<10)? '0' + val: 'a' + val - 10;
}
void output(){
	char low_ch, high_ch;
	for(int i=0;i<n;i++){
		low_ch = int2HexChar((buffer[i]&0xf0) >> 4);
		high_ch = int2HexChar(buffer[i]&0x0f);
		printf("%c%c",low_ch,high_ch);
		if((i&0x7)==7) printf("\n");
	}
}
int main(){
	scanf("%d",&s);
	for(int i=0;i<s;i++)
		bytes[i] = getByte();
	end_ptr = bytes + s;
	decompress();
	output();
	return 0;
}