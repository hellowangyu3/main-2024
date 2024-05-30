#ifndef __NODE_H__
#define __NODE_H__
/****** 定义节点结构体 *****/
struct Node
{
    void *data; //数据域
    struct Node *prev;  //前一节点首地址
    struct Node *next;  //后一节点首地址
};

/****** 给链表取个别名 ******/
typedef struct Node Node_t;

/****** 宏函数检测参数是否正确 *****/
#define CheckValue(Value1,Operator,Value2,Out,Return)  {\
    if((Value1) Operator (Value2))\
    {           \
        printf("file:%s,line:%d,func:%s,error:%s\n",__FILE__,__LINE__,__func__,Out);    \
        return Return;  \
    }\
}

/****** 函数的操作集合 ******/
//链表的:初始化，增，删，改，查，排序

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
Node_t *Node_Init();

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
int Node_PushBack(Node_t **head,void *value,int value_size);

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
int Node_PushFron(Node_t **head,void *value,int value_size);

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
int Node_Insert(Node_t *node,void *value,int value_size);


/************************************************************************
 * 函数名：void Node_for_each(Node_t *head,void (*Print_func)(void *));
 * 
 * 功能：双向循环链表的遍历显示
 * 
 * 参数：
 *      Node_t *head：链表的首地址
 *      void (*Print_func)(void *data)：显示函数的首地址(回调函数/函数指针)
 *          回调函数说明：
 *              功能：显示
 *              参数：
 *                  void *data：节点数据
 *              返回值：无
 * 返回值：无
 * 其他说明：无
 * **********************************************************************/
void Node_for_each(Node_t *head,void (*Print_func)(void *));

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
Node_t *Node_find(Node_t *head,void *data,int (*cmp_func)(void *,void *));

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
void Node_free(Node_t **head);


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
int Node_PopBack(Node_t **head);

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
int Node_PopFron(Node_t **head);

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
int Node_Erase(Node_t *node);


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
void Node_Update(Node_t *node,void *data,void (*updata_func)(void *,void *));

/**************************************************************************
 * 函数名：void Node_sort(Node_t *head,int (*cmp_func)(void *data1,void *data2));
 * 功能：冒泡排序
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
void Node_sort(Node_t *head, int (*cmp_func)(void *data1, void *data2));

/**************************************************************************
 * 函数名：void Node_sort_insert(Node_t *head, int (*cmp_func)(void *data1, void *data2))
 * 功能：插入排序
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
void Node_sort_insert(Node_t *head, int (*cmp_func)(void *data1, void *data2));
#endif
