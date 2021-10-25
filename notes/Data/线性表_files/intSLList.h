#ifdef INT_LINKED_LIST
#DEFINE INT_LINKED_LIST

//节点定义
class IntSLLNode
{
public:
    IntSLLNode()
    {
        next=0;
    }
    IntSLLNode(int el, IntSLLNode* ptr=nullptr):info(el), next(nullptr)   //C++11中为指针赋空；列表初始化
    {       
    }
//private:                      //因为在具体实现中需要对象直接访问这两个成员，所以不能指定为私有成员
    int info;
    IntSLLNode* next;
}

//int单向链表
class IntSLList
{
public:
    IntSLList()
    {
        head=nullptr;
        tail=nullptr;
    }
    //定义析构函数：
    ~IntSLList();
    bool isEmpty()   //这个类型使用bool不是更好吗
    {
        return head==0;
    }
    void addToHead(int );
    void addToTail(int );
    int deleteFromHead();
    int deleteFromTail();
    void deleteNode(int );              //删除元素和删除节点有什么区别吗
    bool isInList(int ) const;
private:
    IntSLLNode *head,*tail;
}