void main(){
	for (int i=0;i<13;i++){
		printf("case ",i,": ");
		switch (i) {
			case 1:
				printf("2\n");
				break;
			case 2:
				printf("3\n");
				break;
			case 3:
				printf("hello ");
			case 4:
				printf("world\n");
				break;
			case 10:
				printf("NO. 10\n");
				break;
			default:
				printf("default\n");
				break;
		}
	}
}