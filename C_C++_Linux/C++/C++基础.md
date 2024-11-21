# static  关键字有什么作用？

- 修饰局部变量时，在静态存储区为其分配内存，只在函数首次调用的时候初始化一次，后续的函数调用不再进行初始化；该变量的生命周期和程序相同，但是作用域为局部作用域。
- 修饰全局变量时，在静态存储区为其分配内存，在声明该变量的整个文件中都是可见的，而文件外不可见。
- 修饰函数时，在声明该函数的整个文件中都是可见的，文件外不可见，从而避免了多人协作时的函数命名冲突。
- 修饰成员变量时，所有的对象只可以维持一份数据拷贝，可以实现不同对象之间的数据共享；不需要实例化对象就可以访问，一般在类外进行初始化，并且初始化时不加static。
- 修饰成员函数时，该函数不接受this指针，只能访问静态成员；不需要实例化对象即可访问。



# 什么是内存泄露？内存泄露有哪些情况？

内存泄露是程序运行过程中分配在堆区的内存，没有释放或无法释放从而造成该堆区的内存没法在次被利用，导致程序运行缓慢甚至造成的系统崩溃；

堆内存泄露

资源泄露：系统资源泄露（socket、文件描述符等）

内存泄露的场景:

- malloc和free、new/new [] 和delete/delete [ ]未成对出现;

- 未定义拷贝构造函数或未重载复制运算符，从而造成两次释放相同内存。
- 没有将基类的析构函数定义为虚函数。



# C++中抽象类和接口的区别？为什么有了抽象类还要有接口？

- C++中抽象类：

  至少具有一个纯虚方法，可以定义方法的实现，可以定义变量，通常使用class 关键字。

- C++中的接口（纯虚类）:

  类中所有的函数被声明为纯虚函数，类中无变量的声明，通常使用struct关键字

- 接口和抽象类都体现了多态，接口带来的最大好处是避免了多继承带来的复杂性和低效性，并且同时提供了多重继承的好处。

- 抽象类是对事物进行抽象，更多的是为了继承和扩展，从而实现代码的复用，子类和父类之间体现的是is-a的关系。

- 接口是一种行为约束，一种规则，实现一个接口要实现接口中所有的方法。

# C11 final关键字用法有哪些？



# 只能在堆区创建对象

```c++
#include<iostream>
using namespace std;
class test
{
private:
	~test(){ cout << "test destroy" << endl; }
public:
	void destroy()
	{
		delete this;
	}
};
int main()
{
	//test p;//编译器报错test::~test()不可访问
	test *p = new test;
	p->destroy();
}
```

# 只能在栈区创建对象

```c++
#include<iostream>
using namespace std;
class test
{
private:
	void* operator new(size_t t){}
	void operator delete(void* ptr){}
public:
	~test()
	{
		cout << "test destroy" << endl;
	}
};
int main()
{
    test a;
	//test *A = new test;
	//编译器报错函数test::operator new 不可访问
	test A;
}
```

# new的用法

函数new：

```cpp
#include<iostream>

using namespace std;

int main()
{
	const int n = 10;

	int* p = (int*)::operator new (n * sizeof(int));

	for (int i = 0; i < 10; i++)
	{
		p[i] = i * i;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << p[i] << endl;
	}
	::operator delete(p);
	return 0;
}


```

定位new

```cpp
#include<iostream>

using namespace std;

int main()
{
	int* pa = (int*)::operator new(sizeof(int));
	int* pb = (int*)::operator new[](sizeof(int) * 10);


	new(pa) int(20);
	new(pb) int[] {1, 2, 3, 3, 4, 5, 6, 7, 8, 9};//最新标准有效

	for (int i = 0; i < 10; i++)
	{
		cout << pb[i] << endl;
	}

	::delete pa;
	::delete[] pb;
	return 0;

}
```

# 有继承情况下的拷贝构造和赋值运算符的重载的调用规则

# 一个函数可以是内联函数与虚函数
