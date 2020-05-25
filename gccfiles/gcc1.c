int abc,def;
int ghi[10];
char jkl[]="fuck china";
int func(int a,int b) {
	int c = a + b;
	return c;
}
int main(){
	int a,b;
	char c[20]="hello world";
	switch(a){
		case 1:a++;break;
		case 2:a--;
		case 3:a+=5;
		case 4:a-=5; break;
		case 9:a=123;
		case 8:a++;b-=124;break;
		default:
			a+=999;
			c[5]="0";
			break;
	}
	abc=a+b;
	def=func(a,b);
	return (int)c[6];
}