/****************************************************************************************************
* 第一种实现方式，通过static指针成员
* 注意点：构造要声明为private保证只通过接口Instance产生唯一对象
* 弊端：调用端有可能delete掉对象
****************************************************************************************************/
class Singletons1
{
public:
	static Singletons1* Instance()
	{
		if (!pInstance_)
		{
			pInstance_ = new Singletons1;
		}
		return pInstance_;
	}

    static void Wt(const string &s)
    {
        cout << ++count_ << endl;
        WriteFile t(s);
        t << "good afternoon";
    }

	~Singletons1()
	{
		delete pInstance_;
		pInstance_ = nullptr;
	}

private:
    Singletons1() {}
	Singletons1(const Singletons1&){}

private:
	static Singletons1* pInstance_;
    static int count_;
};

// .cpp中对pInstance_定义
Singletons1* Singletons1::pInstance_ = nullptr;


/****************************************************************************************************
* 第二种实现方式，通过static指针成员
* 弊端：动态初始化，如果面对不同的编译单元中的动态初始化对象，C++并未规定义期间的初始化顺序，就会出现以下问题：
*  somefile.cpp: #include "Singletons2" int global = Singletons2::Instance()->test();
*  如果Instance_在global之前没有初始化就有可能会返回一个未构造的对象
*  这意味着，无法保证任何外部对象使用的instance_是一个已被正确初始化的对象
****************************************************************************************************/
class Singletons2 
{
public:
    static Singletons2* Instance()
    {
        return &Instance_;
    }

    static int test()
    {
        return 134;
    }

private:
    Singletons2(const Singletons2&) {}
    Singletons2& operator=(const Singletons2&) {}

    static Singletons2 Instance_;
};

// .cpp中对Instance_定义
Singletons2* Singletons2::Instance_；	// 静态初始化：无构造可通过编译期常量来初始化


/**************************************************************************************************
* 第三种方式：使用一个局部的静态变量：存在 dead-reference问题
* 产生这个问题的场景：三个单例，其中一个log单例应当在第一次出错时记录，在最后析构退出
**************************************************************************************************/
class Singletons3
{
public:
    static Singletons3& Instance()
    {
        static Singletons3 obj;
        return obj;
    }

    void Func1()
    {
        cout << "Singletons3::Func1" << endl;
    }

private:
    Singletons3()
    {
        cout << "Singletons3" << endl;
    }
};


/***************************************************************************************************
* 第四种方式：解决dead reference问题
* 1.如果单例类已经析构掉了则抛出异常
* 但对于解决log问题仍不完美，只在出错时抛出异常并没有完全解决没有log对象
***************************************************************************************************/
class Singleton4
{
public:
    Singleton4& Instance()
    {
        if (!pInstance_)
        {
            if (destroyed_)
            {
                OnDeadReference();
            }
            else
            {
                Create();
            }
        }
        return *pInstance_;
    }

private:
    static void Create()
    {
        static Singelton4 theInstance;
        pInstance_ = &theInstance;
    }

    static void OnDeadReference()
    {
        throw std::runtime_error("Dead Reference Detected");
    }

    virtual ~Singleton4()
    {
        pInstance_ = 0;
        destroyed_ = true;
    }

private:
    static bool destroyed_;
    static Singleton4* pInstance_;
};

// .cpp中实现：
Singleton4* Singleton4::pInstance_ = nullptr;
bool Singleton4::destroyed_ = false;

/*************************************************************
* 第五种方式：
* 2.单例被析构后仍然可以使用
*   修改点：仅修改OnDeadReference()
* 缺点：破坏了Singleton5正常的生命周期，从而给使用者带来疑惑，如果你的Singletons5持有状态，那个状态会在"析构""创建"周期中丢失
*************************************************************/
class Singleton5
{
public:
    Singleton5& Instance()
    {
        if (!pInstance_)
        {
            if (destroyed_)
            {
                OnDeadReference();
            }
            else
            {
                Create();
            }
        }
        return *pInstance_;
    }

private:
    static void Create()
    {
        static Singelton5 theInstance;
        pInstance_ = &theInstance;
    }

    static void OnDeadReference()
    {
        Create();  // 为什么需要Create？
        new(pInstance_) Singleton5;        // placement new操作符
        atexit(KillPhoenixSingleton);
        destroyed_ = false;
    }

    void Singleton5::KillPhoenixSingleton()
    {
        pInstance_->~Singleton();
    }

    virtual ~Singleton5()
    {
        pInstance_ = 0;
        destroyed_ = true;
    }

private:
    static bool destroyed_;
    static Singleton5* pInstance_;
};


/*****************************************************************************
* 第六种方式：带寿命的Singleton
* 3.
*****************************************************************************/

/*****************************************************************************
* 第七种方式：双检测锁定
* 解决场景：每次进入Instance执行都会引发同步对象的加锁与解锁，这种操作是很昂贵的
* 使用"双检测锁定"确保多线程创建单例对象
*  警告：即使使用双检测锁定编译器的优化也有可能破坏这种情况，所以还是要了解编译器
*  这个并没有利用到static变量，是不是可以使用static变量做优化？
*****************************************************************************/
Singleton7& Singleton7::Instance()
{
    if(!pInstance_){
        lock_guard lock(lock_);
        if(!pInstance_){
            pInstance_ = new Singleton7;
        }
    }
}