#include "node.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/************************************************************************
 * 函数名：Node_t *Node_Init();
 * 
 * 功能：双向循环链表的初始化
 * 
 * 参数：无
 * 
 * 返回值：
 *     成功：链表的首地址
 *     失败：NULL
 * 
 * 其他说明：无
 * **********************************************************************/
Node_t *Node_Init()
{
    /**********************************
     * 1.申请一个节点承担头节点
     * 2.头节点特征
     *   data = NULL
     *   next = 自己首地址
     *   prev = 自己首地址
     * 3.将头结点首地址返回
     * **********************************/
    //1.申请一个节点承担头节点
    Node_t *node = (Node_t *)malloc(sizeof(Node_t));
    CheckValue(node, ==, NULL, "申请头节点空间失败", NULL);
    //2.头节点特征
    node->data = NULL;
    node->prev = node;
    node->next = node;

    //3.将头结点首地址返回
    return node;
}
/************************************************************************
 * 函数名：int Node_PushFron(Node_t **head,void *value,int value_size);
 * 
 * 功能：双向循环链表的头部插入
 * 
 * 参数：
 *      Node_t **head：链表的首地址
 *      void *value：要插入的数据首地址
 *      int value_size：要插入的数据大小
 * 
 * 返回值：
 *     成功：0
 *     失败：非0
 * 
 * 其他说明：无
 * **********************************************************************/
int Node_PushFron(Node_t **head, void *value, int value_size)
{
    /************************************************
     * 1.检查参数有效性
     * 2.申请一个新的节点
     * 3.申请该新节点的数据域
     * 4.将插入数据拷贝进入新节点的数据域中
     * 5.更改指向
     *  5.1 找到第一个元素节点
     *  5.2 更改指向
     * 6.返回操作正确
     * ***********************************************/

    //1.检查参数有效性
    CheckValue(*head, ==, NULL, "链表无效", -1);
    CheckValue(value, ==, NULL, "数据无效", -2);
    CheckValue(value_size, <=, 0, "数据大小无效", -3);

    //2.申请一个新的节点
    Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
    CheckValue(new_node, ==, NULL, "申请头节点空间失败", -5);

    //3.申请该新节点的数据域
    new_node->data = malloc(value_size);
    if (new_node->data == NULL) //判断有效性
    {
        free(new_node);
        return -4;
    }

    //4.将插入数据拷贝进入新节点的数据域中
    memcpy(new_node->data, value, value_size);

    //5.1 找到第一个元素节点 和 上一个节点
    Node_t *next_node = (*head)->next;
    Node_t *prev_node = (*head);
    //5.2 更改指向
    prev_node->next = new_node;
    next_node->prev = new_node;

    new_node->prev = prev_node;
    new_node->next = next_node;

    return 0;
}

/************************************************************************
 * 函数名：int Node_Insert(Node_t *node,void *value,int value_size);
 * 
 * 功能：双向循环链表的指定位置插入
 * 
 * 参数：
 *      Node_t *node：链表的节点
 *      void *value：要插入的数据首地址
 *      int value_size：要插入的数据大小
 * 
 * 返回值：
 *     成功：0
 *     失败：非0
 * 
 * 其他说明：无
 * **********************************************************************/
int Node_Insert(Node_t *node, void *value, int value_size)
{
    /************************************************
     * 1.检查参数有效性
     * 2.申请一个新的节点
     * 3.申请该新节点的数据域
     * 4.将插入数据拷贝进入新节点的数据域中
     * 5.更改指向
     *  5.1 找到第一个元素节点
     *  5.2 更改指向
     * 6.返回操作正确
     * ***********************************************/

    //1.检查参数有效性
    CheckValue(node, ==, NULL, "节点无效", -1);
    CheckValue(value, ==, NULL, "数据无效", -2);
    CheckValue(value_size, <=, 0, "数据大小无效", -3);

    //2.申请一个新的节点
    Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
    CheckValue(new_node, ==, NULL, "申请头节点空间失败", -5);

    //3.申请该新节点的数据域
    new_node->data = malloc(value_size);
    if (new_node->data == NULL) //判断有效性
    {
        free(new_node);
        return -4;
    }

    //4.将插入数据拷贝进入新节点的数据域中
    memcpy(new_node->data, value, value_size);

    //5.1 找到当前节点 和 下一个节点
    Node_t *next_node = node->next;
    Node_t *prev_node = node;
    //5.2 更改指向
    prev_node->next = new_node;
    next_node->prev = new_node;

    new_node->prev = prev_node;
    new_node->next = next_node;

    return 0;
}

/************************************************************************
 * 函数名：int Node_PushBack(Node_t **head,void *value,int value_size);
 * 
 * 功能：双向循环链表的尾部插入
 * 
 * 参数：
 *      Node_t **head：链表的首地址
 *      void *value：要插入的数据首地址
 *      int value_size：要插入的数据大小
 * 
 * 返回值：
 *     成功：0
 *     失败：非0
 * 
 * 其他说明：无
 * **********************************************************************/
int Node_PushBack(Node_t **head, void *value, int value_size)
{
    /************************************************
     * 1.检查参数有效性
     * 2.申请一个新的节点
     * 3.申请该新节点的数据域
     * 4.将插入数据拷贝进入新节点的数据域中
     * 5.更改指向
     *  5.1 找到尾部节点
     *  5.2 更改指向
     * 6.返回操作正确
     * ***********************************************/

    //1.检查参数有效性
    CheckValue(*head, ==, NULL, "链表无效", -1);
    CheckValue(value, ==, NULL, "数据无效", -2);
    CheckValue(value_size, <=, 0, "数据大小无效", -3);

    //2.申请一个新的节点
    Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
    CheckValue(new_node, ==, NULL, "申请头节点空间失败", -5);

    //3.申请该新节点的数据域
    new_node->data = malloc(value_size);
    if (new_node->data == NULL) //判断有效性
    {
        free(new_node);
        return -4;
    }

    //4.将插入数据拷贝进入新节点的数据域中
    memcpy(new_node->data, value, value_size);

    //5.1 找到尾部节点
    Node_t *end_node = (*head)->prev;

    //5.2 更改指向
    end_node->next = new_node;

    new_node->next = *head;
    new_node->prev = end_node;

    (*head)->prev = new_node;

    //6.返回操作正确
    return 0;
}

/************************************************************************
 * 函数名：void Node_for_each(Node_t *head,void (*Print_func)(void *));
 * 
 * 功能：双向循环链表的遍历显示
 * 
 * 参数：
 *      Node_t *head：链表的首地址
 *      void (*Print_func)(void *)：显示函数的首地址(回调函数/函数指针)
 * 
 * 返回值：无
 * 其他说明：无
 * **********************************************************************/
void Node_for_each(Node_t *head, void (*Print_func)(void *))
{
    /**************************************
     * 1.检查参数有效性
     * 2.遍历调用回调函数
     *    2.1 遍历链表
     *    2.2 调用回调函数
     * *********************************/
    //1.检查参数有效性
    CheckValue(head, ==, NULL, "链表无效", );
    CheckValue(head->next, ==, head, "链表没有元素", );
    CheckValue(Print_func, ==, NULL, "回调函数无效", );

    //2.1 遍历链表
    Node_t *node = head->next;
    while (node != head)
    {
        //2.2 调用回调函数
        Print_func(node->data);
        //2.3 往后遍历
        node = node->next;
    }
}

/************************************************************************
 * 函数名：void Node_free(Node_t **head);
 * 
 * 功能：双向循环链表的销毁
 * 
 * 参数：
 *      Node_t **head：链表的首地址
 * 返回值：
 * 其他说明：无
 * **********************************************************************/
void Node_free(Node_t **head)
{
    /******************************
     * 1.判断参数有效性
     * 2.存储要删除节点的下一节点
     * 3.释放要删除的节点
     *    3.1 释放数据域
     *    3.2 释放节点域
     * 4.将遍历指针往后移动
     * 5.删除头节点的节点空间
     * 6.将链表销毁特点是该表直接指向NULL
     * ******************************/
    CheckValue(*head, ==, NULL, "链表无效", );

    Node_t *temp_node = (*head)->next; //第一个有效元素
    Node_t *next_save = NULL;          //要删除节点的下一节点首地址
    while (temp_node != *head)
    {
        //2.先存储要要删除节点的下一节点首地址
        next_save = temp_node->next;
        //3.1 释放数据域
        free(temp_node->data);
        //3.2 释放节点域
        free(temp_node);
        //4.将遍历指针往后移动
        temp_node = next_save;
    }

    //5.删除头节点的节点空间
    free(*head);

    //6.将链表销毁特点是该表直接指向NULL
    *head = NULL;
}

/************************************************************************
 * 函数名：Node_t *Node_find(Node_t *head,void *data,int (*cmp_func)(void *,void *));
 * 
 * 功能：双向循环链表的查找
 * 
 * 参数：
 *      Node_t *head：链表的首地址
 *      void *data:用户要查找的数据
 * 
 * 
 *      int (*cmp_func)(void *data1,void *data2))：比较函数(回调函数/函数指针)
 *          回调函数说明：
 *              功能：显示
 *              参数：
 *                  void *data1：链表中的节点数据
 *                  void *data2：用户自己传入的数据
 *              返回值：
 *                  匹配：0
 *                  不匹配：非0
 * 返回值：
 *      成功：查找到的节点首地址
 *      失败：NULL
 * 其他说明：无
 * **********************************************************************/
Node_t *Node_find(Node_t *head, void *data, int (*cmp_func)(void *, void *))
{
    /******************************
     * 1.判断参数有效性
     * 2.遍历比较数据
     * **************************/
    CheckValue(head, ==, NULL, "传入的地址为NULL,无效", NULL);
    CheckValue(head->next, ==, head, "链表内没有元素", NULL);

    /********2.遍历比较数据************/
    Node_t *node = head->next; //第一个元素节点地址
    while (node != head && node->data != NULL)
    {
        if (cmp_func(node->data, data) == 0) //找到了
        {
            return node; //把找到的该节点地址返回
        }

        node = node->next; //往后遍历
    }

    return NULL; //遍历完了都没有找到
}

/************************************************************************
 * 函数名：int Node_PopBack(Node_t **head);
 * 
 * 功能：双向循环链表的尾部删除
 * 
 * 参数：
 *      Node_t **head：链表的首地址
 * 返回值：
 * 其他说明：无
 * **********************************************************************/
int Node_PopBack(Node_t **head)
{
    /******************************
     * 1.判断参数有效性
     * 2.找到要删除的节点
     * 3.找到要删除的节点的上一节点
     * 4.找到要删除的节点的下一节点
     * 5.释放该节点
     *  5.1 释放数据域空间
     *  5.2 释放节点空间
     * 6.更改指向
     * **************************/
    //1.判断参数有效性
    CheckValue(*head, ==, NULL, "传入的地址为NULL,无效", -1);
    CheckValue((*head)->next, ==, (*head), "链表内没有元素", -2);

    //2.找到要删除的节点
    Node_t *delete_node = (*head)->prev;

    //3.找到要删除的节点的上一节点
    Node_t *delete_node_prev = delete_node->prev;

    //4.找到要删除的节点的下一节点
    Node_t *delete_node_next = delete_node->next;

    //5.1 释放数据域空间
    free(delete_node->data);
    //5.2 释放节点空间
    free(delete_node);

    //6.更改指向
    delete_node_prev->next = delete_node_next;
    delete_node_next->prev = delete_node_prev;

    return 0;
}

/************************************************************************
 * 函数名：int Node_PopFron(Node_t **head);
 * 
 * 功能：双向循环链表的头部删除
 * 
 * 参数：
 *      Node_t **head：链表的首地址
 * 返回值：
 * 其他说明：无
 * **********************************************************************/
int Node_PopFron(Node_t **head)
{
    /******************************
     * 1.判断参数有效性
     * 2.找到要删除的节点
     * 3.找到要删除的节点的上一节点
     * 4.找到要删除的节点的下一节点
     * 5.释放该节点
     *  5.1 释放数据域空间
     *  5.2 释放节点空间
     * 6.更改指向
     * **************************/
    //1.判断参数有效性
    CheckValue(*head, ==, NULL, "传入的地址为NULL,无效", -1);
    CheckValue((*head)->next, ==, (*head), "链表内没有元素", -2);

    //2.找到要删除的节点
    Node_t *delete_node = (*head)->next;

    //3.找到要删除的节点的上一节点
    Node_t *delete_node_prev = delete_node->prev;

    //4.找到要删除的节点的下一节点
    Node_t *delete_node_next = delete_node->next;

    //5.1 释放数据域空间
    free(delete_node->data);
    //5.2 释放节点空间
    free(delete_node);

    //6.更改指向
    delete_node_prev->next = delete_node_next;
    delete_node_next->prev = delete_node_prev;

    return 0;
}

/************************************************************************
 * 函数名：int Node_Erase(Node_t *node);
 * 
 * 功能：双向循环链表的指定节点删除
 * 
 * 参数：
 *      Node_t *node：要删除的节点
 * 返回值：
 * 其他说明：无
 * **********************************************************************/
int Node_Erase(Node_t *node)
{
    /******************************
     * 1.判断参数有效性
     * 2.找到要删除的节点
     * 3.找到要删除的节点的上一节点
     * 4.找到要删除的节点的下一节点
     * 5.释放该节点
     *  5.1 释放数据域空间
     *  5.2 释放节点空间
     * 6.更改指向
     * **************************/
    //1.判断参数有效性
    CheckValue(node, ==, NULL, "传入的地址为NULL,无效", -1);

    //2.找到要删除的节点
    Node_t *delete_node = node;

    //3.找到要删除的节点的上一节点
    Node_t *delete_node_prev = delete_node->prev;

    //4.找到要删除的节点的下一节点
    Node_t *delete_node_next = delete_node->next;

    //5.1 释放数据域空间
    free(delete_node->data);
    //5.2 释放节点空间
    free(delete_node);

    //6.更改指向
    delete_node_prev->next = delete_node_next;
    delete_node_next->prev = delete_node_prev;

    return 0;
}

/************************************************************************
 * 函数名：void Node_Update(Node_t *node,void *data,void (*updata_func)(void *,void *));
 * 
 * 功能：双向循环链表的指定的修改
 * 
 * 参数：
 *      Node_t *node：要修改数据的节点
 *      void *data：传入修改后的节点数据
 *      void (*updata_func)(void *data1,void *data2)：修改回调函数
 *          函数名:void 函数名(void *data1,void *data2)
 *          功能：修改链表的数据
 *          参数：
 *              data1：链表的数据
 *              data2：用户的数据
 *          返回值：无
 * 返回值：
 * 其他说明：无
 * **********************************************************************/
void Node_Update(Node_t *node, void *data, void (*updata_func)(void *, void *))
{
    /******************************
     * 1.判断参数有效性
     * 2.调用用户传入的修改函数
     * *****************************/
    CheckValue(node, ==, NULL, "节点无效", );
    CheckValue(data, ==, NULL, "数据无效", );

    updata_func(node->data, data);
}

/**************************************************************************
 * 函数名：void Node_sort(Node_t *head,int (*cmp_func)(void *data1,void *data2));
 * 功能：排序
 * 参数：
 *      Node_t *head：链表的首地址
 *      int (*cmp_func)(void *data1,void *data2)：比较回调函数
 *          功能：比较链表相邻节点的数据
 *          参数：
 *              void *data1：当前节点的数据
 *              void *data2：当前节点的下一节点数据
 *          返回值：
 *              成立：> 0
 *              不成立：<= 0
 * 返回值：无
 * 其他说明：
 * ************************************************************************/
void Node_sort(Node_t *head, int (*cmp_func)(void *data1, void *data2))
{
    /***************************************
     * 1.参数检查
     * 2.特征
     * *************************************/
    CheckValue(head, ==, NULL, "链表无效", );
    CheckValue(head->next, ==, head, "没有元素，没必要排序", );
    CheckValue(cmp_func, ==, NULL, "比较回调函数无效", );

    void *temp_data = NULL;
    Node_t *num = head->next;

    int flag = 0;   //效率1
    Node_t *end_node = head->prev;   //效率2：临时尾部 
    while (num != head->prev)
    {
        flag = 0;
        for (Node_t *i = head->next; i < end_node; i = i->next)
        {
            if (cmp_func(i->data, i->next->data) > 0)
            {
                flag = 1;

                temp_data = i->data;
                i->data = i->next->data;
                i->next->data = temp_data;
            }
        }
        end_node = end_node->prev;  //临时末尾往前移动一个节点

        if(flag == 0)
        {
            return ;    //表示已经排好了
        }

        num = num->next;        
    }
}



/**************************************************************************
 * 函数名：void Node_sort_insert(Node_t *head, int (*cmp_func)(void *data1, void *data2))
 * 功能：排序
 * 参数：
 *      Node_t *head：链表的首地址
 *      int (*cmp_func)(void *data1,void *data2)：比较回调函数
 *          功能：比较链表相邻节点的数据
 *          参数：
 *              void *data1：当前节点的数据
 *              void *data2：当前节点的下一节点数据
 *          返回值：
 *              成立：> 0
 *              不成立：<= 0
 * 返回值：无
 * 其他说明：
 * ************************************************************************/
void Node_sort_insert(Node_t *head, int (*cmp_func)(void *data1, void *data2))
{
    /***************************************
     * 1.参数检查
     * 2.特征
     * *************************************/
    CheckValue(head, ==, NULL, "链表无效", );
    CheckValue(head->next, ==, head, "没有元素，没必要排序", );
    CheckValue(cmp_func, ==, NULL, "比较回调函数无效", );

    //1.临时头部    用于遍历
    Node_t *temp_head = head->next; //第一个元素
    Node_t *Index = NULL;

    void *data = NULL;
    while(temp_head != head->prev)
    {
        Index = temp_head;
        for(Node_t *i = temp_head->next; i != head; i = i->next)
        {
            if(cmp_func(Index->data,i->data) > 0)
            {   //记录当前的下标位置
                Index = i;
            }
        }

        if( Index != temp_head)
        {
            data = Index->data;
            Index->data = temp_head->data;
            temp_head->data = data;
        }

        /******* 遍历比较一次后temp_head往后移动 ******/
        temp_head = temp_head->next;
    }
}
