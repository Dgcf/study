#include<iostream>
#include"intSLList.h"

IntSLList()::~IntSLList()       //析构函数为什么要这么写
{
    for(IntSLLNode *p;!isEmpty();)
    {
        p=head->next;          
        delete head;
        head=p;
    }
}

void IntSLList::addToHead(int el)
{
    head=new IntSLList(el,head);   
    if(tail==0)                     //必须要判断tail指针？
        tail=head;
}

void IntSLList::addToTail(int el)
{
    if(tail!=nullptr)
    {
        tail->next = new IntSLList(el); 
        tail=tail->next;   
    }
    else
        head=tail=new IntSLList(el);    
}

int IntSLList::deleteFromHead()
{
/*
    delete head;
    if(tail!=0)
    {
        head=head->next;
    }
    else
        head=tail;
*/
    int el=head->info;
    IntSLLNode *tmp=head;
    if(head==tail)
    {
        head=tail=nullptr;
    }
    else
        head=head->next;
    delete tmp;                       //对指针的操作,不能直接删除head吗？
    return el;
}

int IntSLList::deleteFromTail()
{
/*
    if(head==tail)
    {
        head=tail=nullptr;
    }
    else
    {
        IntSLLNode* tmp=--tail;           //链表不是按顺序存储的，所以不能使用与顺序访问相关的运算符
        tmp->next=nullptr;
    }
*/
    int el=tail->info;
    if(head==tail)
    {
        delete head;      
        head=tail=nullptr;
    }
    else
    {
        IntSLLNode* tmp;
        for(tmp=head;tmp->next != tail;tmp=tmp->next);
        delete tail;
        tail=tmp;
        tail->next=nullptr;
    }
    return el;
}

void IntSLList::deleteNode(int el)
{
    if(head!=0)
    {
        if(head==tail && el==head->info)     //只有一个节点
        {
            delete head;
            head=tail=nullptr;
        }
        else if(el==head->info)
        {
//            deleteFromHead();     
            IntSLLNode* tmp=head;
            head=head->next;
            delete tmp;
        }
        //再加一个判断是否是最后一个元素的语句？
        else        //需要在链表中查找是否有要删除的节点
        {
            /*
            IntSLLNode *pred， *tmp;
            for(pred=head,tmp=head->next; tmp->next!=tail; pred=pred->next,tmp=tmp->next)
            {
                if(el==tmp->info)
                {
                    pred->next=tmp->next;
                    delete tmp;
                }
            }
            */
            IntSLLNode *pred, *tmp;
            for(pred=head,tmp=head->next; tmp!=0 && !(tmp->info==el); pred=pred->next,tmp=tmp->next);    //该for循环止于 tmp->info==el;
            if(tmp!=0)
            {
                pred->next=tmp->next;
                if(tmp==tail)
                    tail=pred;
                delete tmp;
            }
        }
    }
}

bool IntSLList::isInList(int el) const
{
    IntSLLNode *tmp;
    /*
    for(tmp=head;tmp!=0; tmp=tmp->next)
    {
        if(el==tmp->info)
            return true;
        else
            return false;
    }
    */
    for(tmp=head; tmp!=0 && !(tmp->info==el); tmp=tmp->next);
    return tmp!=0;
}