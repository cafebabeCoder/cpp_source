#include <iostream>
#include <cstdio>
using namespace std;
// https://www.bilibili.com/video/BV1s5411J78m?p=10
// 指针是一个变量， 用于存储另一个变量的地址
void method1(){
	// 指针基础
	// int 4字节， 分配一个地址
	int a ;  // 可以把a赋值，下面代码就显示对应值，而不是垃圾值
	int* p;
	p=&a;
	// 7ffdd7b244cc is 0,实际上是a对应地址存的内容,未初始化，为垃圾值
	cout<<"Address of "<<p<<" is "<<*p<<endl;  
	//ffdd7b244d0 is  4197120 垃圾值; 指针会直接加对应类型的size，跳到下一个位置，比如int* 就会+4
	// 指针++主要用于数组
	cout<<"Address of "<<p+1<< " is " << *(p+1)<<endl;    
	cout<<"size of int : "<<sizeof(int)<<endl;  // int的大小： 4字节
	*p = 5; // a = 5, 会改变a存的值

	char c = 'A';
	char* p0;
	p0 = &c;
	cout<<"size of char : "<<sizeof(char)<<endl;  // 1
	cout<<"Address of "<<p0<< " is " << *p0<<endl;     
	cout<<"Address of "<<p0+1<< " is " << *(p0+1)<<endl;      //没有打印出来， Address of  is 

}

// 指针类型: 指针是强类型，因为不仅需要指明地址，还需要告诉编译器，这个值占多少个字节。
// 	  比如int4字节，最左边一位是符号;char占1字节。
// 空指针 void pointer
// 指针运算
void method2(){
	int a = 1025;
	int* p;
	p = &a;
	cout<<"Address = "<<p<<", value = "<<*p<<endl; // Address = 0x7ffe0e080d74, value = 1025
	double* d = (double*) p;
	cout<<"Address = "<<d<<", value = "<<*(d)<<endl; //Address = 0x7ffe0e080d74, value = 1.78799e-307
	char* p0 = (char*)p; //  需要强制类型转换
	cout<<"Address = "<<p0<<", value = "<<*(p0)<<endl; // Address = , value = ;转失败了

	void *p1;
	p1 = p;
	//编译 error: ‘void*’ is not a pointer-to-object type
	// cout<<"Address = "<<p1<<", value = "<<*(p1)<<endl;  
	cout<<"Address of next = "<<p1+1<<endl; //可以运算
}

//指针的指针
void method2_2(){
	int x= 5;
	int* p = &x;
	*p = 6; // x=6
	int** q = &p;
	int*** r = &q;
	printf("%d\n%d\n%d\n%d\n%d\n", *p, *q, **q, **r, ***r);
	***r =10;
	printf("x=%d\n", x);
}

// 传引用； 
// 应用程序的空间分为4块： headp, stack(function), static/global(全局变量), Code
// 方法1： 参数用  (int* p)； 调用用： increment(&a)
// 方法2： 参数用  (int& p); 调用用： increment(a)
void increment(int* p){
	*p += 1;
}
void method3(){
	int a;
	a = 10;
	increment(&a);
	cout<<a<<endl;
}

// 指针和数组
// 数组分配了连续空间，所以直接用指针运算就行
// A 是base address； &A[i]与A+i的地址一样（因为是指针）
void method4(){
	int A[] = {1,2,3,4,5};
	int i;
	
	cout<<"Address: "<< &A[0]<<" "<<A<<endl;
	for (int i = 0; i<5; i++){
		cout<<"Address: "<< &A[i]<<" "<<A+i<<endl;
		cout<<"Value: "<<A[i]<<" "<<*(A+i)<<endl;
	}
}

// 数组作为函数参数
// 当函数执行时，会建立一个stack， 对于数组来说，不会复制所有数组的值，而是用一个指针指向调用者的空间。
// 所以传入的数组参数实际只是一个指针而不是value
int SumOfElement(int A[]){  // 改写法等于 int SumOfElement(int* A)
	cout<<"size of A: "<< sizeof(A)<<"; size of A[0]: "<<sizeof(A[0])<<endl;
	int sum = 0;
	// 此时的A是指针，可以加加减减，但是main里面的A不是指针，不能加加减减
	// A = 0x7ffdd649b894; A++ = 0x7ffdd649b890
	cout<<"A = "<<A<<"; A++ = "<<A++<<endl;
	for(int i = 0; i<sizeof(A)/sizeof(A[0]); i++){
		sum += A[i];
	}
	return sum;
}
int SumOfElement(int A[], int size){  //遍历时，需要传入size ，此时就是正确的
	cout<<"size of A: "<< size<<"; size of A[0]: "<<sizeof(A[0])<<endl;
	int sum = 0;
	for(int i = 0; i<size; i++){
		sum += A[i];
	}
	return sum;
}
void method5(){
	int A[]={1,2,3,4,5};
	cout<<"size of A: "<< sizeof(A)<<"; size of A[0]: "<<sizeof(A[0])<<endl;
	cout<<"-----"<<endl;
	int sizes = sizeof(A)/sizeof(A[0]);
	// error: lvalue required as increment operand
	// cout<<"A"<<A++<<endl;
	cout<<"sum="<<SumOfElement(A)<<endl;  // sum=5
	cout<<"sum="<<SumOfElement(A, sizes)<<endl;  // sum=15
}

// 字符数组和指针
#include<cstring>
void print(const char* s){
	for(int i=0; i<10; i++){
		if((*s)!='\0'){
			printf("%c:", *s);
			s++;
		}
	}
}
void method6(){
	char C[4];
	C[0] ='J';
	C[1] = 'O';
	// C[2] = '\0';
	printf("%s\n", C); //按道理最后一个应该存 '\0'，否则会一直打印到 '\0'，但是gnu测出来打印"JO"
	int lens = strlen(C);
	printf("len = %d\n", lens);  // 长度是字符串的长度，而不是分配的长度

	char S[10] = "JOHN"; // 另一种初始化方式,也可以写成 char c[] = "JOHN"
	printf("len = %zu\n", strlen(S));  // 长度是字符串的长度，而不是分配的长度

	// 数组和指针是不同的类型，但是可以用相似的使用方式
	// 数组当做参数时，传的是引用
	// right! 和下面的对比， 当S时字符串时。 不能++，--。 但是是指针的时候，可以
	print(S);
	// error! 和上面比， 不能当做指针使用
	// for(int i=0; i<10; i++){
	// 	if((*S)!='\0'){
	// 		printf("%s", *S);
	// 		S++;
	// 	}
	// }
	cout<<"-----"<<endl;

	char c1[6]="hello";
	char* c2;
	c2 = c1; // c1=c2就是错的
	cout<<"c2 = "<<c2<<"; c2++ = "<<c2++; //c2 = ello; c2++ = hello
	// c1++是错的 
	// c2[i] is *(c2+i)
	cout<<c1[0]<<c2[0]<<endl;

	char t[20] = "hello";  //  分配在栈， 值放在给array分配的空间里
	char *t0 = "HELLO"; // 分配在代码块， 常量 不能修改
	printf("print const:\n");
	print(t0);

}

// 指针和多维数组
// int B[2][3]

//模拟的地址:   |400|404|408|412|416|410|
//value:      | 2 | 3 | 6 | 4 | 5 | 8 |
//            |----B[0]---|----B[1]---|
// 此时的 B[0]或者B[1]是 1-D arrays of 3 integers 
// 写成： int (*p)[3] = B
// 而不是: int (*p) = B
// B = &B[0]= 400
// *B = B[0] = &B[0][0] = 400
// B+1 = B[1] = 412
// *(B+1) = B[1]=&B[1][0] = 412
// *(B+1)+2 = B[1]+2 = &B[1][2] = 420
// *(*B+1) = *(B[0][1]) = B[0][1] = 3
// B[i][j] = *(B[i]+j) = *(*(B+i)+j) . B[i]=int* , *(B+i)= int*

// 同理扩展到三维数组
// c[i][j][k] = *(c[i][j]+k) = *(*(c[i]+j)+k) = *(*(*(c+i)+j)+k)

// 指针作为函数返回
int* add(int* a, int* b){
	int c = (*a) + (*b);
	return &c;
}
int* add_r(int* a, int* b){
	int* c = (int*) malloc(sizeof(int));
	*c = (*a) + (*b);
	return c;
}
void helloword(){
	cout<<"hello"<<endl;
}
int* method7_2(){
	int a = 5;
	int b = 3;
	int* ptr = add(&a, &b);
	helloword();
	cout<<"sum="<<*ptr<<endl;  //0，随着函数栈退出，原来引用的地址被释放了
}
int* method7(){
	int a = 5;
	int b = 3;
	int* ptr = add_r(&a, &b);
	helloword();
	cout<<"sum="<<*ptr<<endl;  //8， 分配在堆去，即使函数栈退出也不影响
}


//函数指针
// 可以指向function
int adds(int a, int b){
	return a+b;
}
int method9(){
	int c;
	int (*p)(int, int); //参数要对应
	p = &adds; // 指向 adds
	c = (*p)(2, 3);  //5
	cout<<c<<endl;
	// 注意这里的 &add， 把 &去掉也一样， 只用函数名也成立
	p = adds; // 指向 adds
	c = p(2, 3);  //5
	cout<<c<<endl;

}
//注意函数指针的写法
// int* func(int, int) -> 声明了一个返回指针的函数
// int (*func)(int, int) -> 声明了一个指针函数

// callback
int compare(int a, int b){
	if (a>b) return -1;
	else return 1;
}
void bubbleSort(int* A, int n, int (*compare)(int, int)){
	int i,j, tmp;
	for (i=0; i<n;i++){
		for (j=0; j<n-1; j++){
			if(compare(A[j], A[j+1]) > 0){
				tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
			}
		}
	}
}
int method10(){
	int i, A[] = {3,2,1,5,6,4};
	bubbleSort(A, 6, compare);
	for(int i = 0; i<6;i++){
		cout<<i<<' ';
	}
}



int main(){
	method10();
	return 0 ;
}