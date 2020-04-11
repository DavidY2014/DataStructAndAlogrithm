#include <stdio.h>
#include <unistd.h>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

/*
*单链表
*/
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x):val(x),next(NULL){}
};

/*
*复杂链表,带有随机指针
*/
struct RandomListNode{
    int label;
    RandomListNode* next;
    RandomListNode* random;
    RandomListNode(int x):label(x),next(NULL),random(NULL){}
};


/*
*链表逆序
*/
class Solution{
public:
    ListNode* reverseList(ListNode* head){
        ListNode* new_head = NULL;
        while(head){
            ListNode* backupNext=  head->next ;
            
            head->next = new_head;
            new_head = head;   

            head = backupNext;
        }
        return new_head;
        
        
    }


    ListNode* reverseBetween(ListNode* head,int m,int n){
        ListNode* new_head = NULL;
        while(head){
            
        }

    }

    /*
    链表相交
    */
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB){
        std::set<ListNode*> nodeSet;
        while(headA){
            nodeSet.insert(headA);
            headA = headA->next;
        }
        while(headB){
            if(nodeSet.find(headB)!=nodeSet.end()){
                return headB;
            }
            headB = headB->next;
        }
        return NULL;

    }

    /*
    *计算链表长度
    */
    int get_list_length(ListNode* head){
        int len = 0;
        while(head){
            len++;
            head = head->next;
        }
        return len;
    }

/*
*对齐长链表
*/
    ListNode* fowardLongList(int shortlength, int longlength ,ListNode* longHead){
        int delta = longlength-shortlength;
        while(longHead && delta){
            longHead = longHead->next;
            delta--;
        }
        return longHead;
    }
/*
*获取相交节点
*/
    ListNode* getIntersectionNode2(ListNode* headA, ListNode* headB){
        int Alength = get_list_length(headA);
        int Blength = get_list_length(headB);
        if(Alength>Blength){
            headA =  fowardLongList(Blength,Alength,headA);

        }else{
            headB =  fowardLongList(Alength,Blength,headB);
        }
        while(headA && headB){
            printf("headA元素:%d,headB元素:%d",headA->val,headB->val);
            if(headA->val == headB->val){
                return headA;
            }
            headA = headA->next;
            headB = headB->next;
        }
        return NULL;
    }

/*
*判断链表是否有环，并把开始节点返回
*/
    ListNode* detectCycle(ListNode* head){
        std::set<ListNode*> node_set;
        while(head){
            //如果没有一直找到最后一个节点，就代表是找到了
            if(node_set.find(head)!=node_set.end()){
                return head;
            }
            node_set.insert(head);
            head = head->next;
        }
        return NULL; 
    }

/*
快慢指针做法
leetcode 141
*/
    ListNode* detectCycle2(ListNode* head){
        ListNode* slowhead = head;
        ListNode* quickhead = head;
        ListNode* meet = NULL;
        while(quickhead){
            slowhead = slowhead->next;
            quickhead = quickhead->next;
            if(!quickhead){
                return NULL; //链尾
            }
            quickhead = quickhead->next;
            if(quickhead == slowhead){
                meet = quickhead;
                break;
            }         
        }
        if(meet == NULL){
            return NULL;
        }
        while(head && meet){
            if(head == meet){
                return head;
            }
            head = head->next;
            meet = meet->next;
        }
        return NULL;
    }
    /*
    *链表划分,思路，通过新建两个大小节点，这里面要区分一个节点和指针的关系，遍历的判断进行插入
    *leetcode 86
    */
    ListNode* partition(ListNode *head, int x)
    {
        ListNode lessnode(0); //新建两个节点
        ListNode morenode(0);
        ListNode* less_ptr = &lessnode;
        ListNode* more_ptr = &morenode;
        while (head)
        {
            if (head->val <= x)
            {
                less_ptr->next = head; 
                less_ptr=head;
            }
            else
            {
                more_ptr->next = head;
                more_ptr =head;
            }
            head = head->next;
        }
        //大小链表合并
        less_ptr->next = morenode.next;
        more_ptr->next = NULL;
        return lessnode.next;
    }

    /*
    *复杂链表的深度拷贝，难点是random指针的拷贝，可以通过map解决
    *leetcode 138
    **/
    RandomListNode *copyRandomList(RandomListNode *head)
    {
        RandomListNode newnode(0);
        RandomListNode *newhead = &newnode;
        std::map<RandomListNode *, int> node_map; //random
        std::vector<RandomListNode*> node_vector; //节点位置
        RandomListNode* ptr = head;
        int i=0;
        while(ptr)
        {
            node_vector.push_back(new RandomListNode(ptr->label));
            //创建random map
            node_map[ptr]=i;
            ptr=ptr->next;
            i++;
        }
        node_vector.push_back(0);//最后一个节点初始化为0节点
        ptr = head; //从头开始遍历
        i = 0;
        while(ptr)
        {
            node_vector[i]->next = node_vector[i+1];
            if(ptr->random)
            {
                int id = node_map[ptr->random];
                node_vector[i]->random = node_vector[id];
            }
            ptr = ptr->next;
            i++;
        }
        return node_vector[0];
    }

/*
* 两个排序链表合并
*leetcode 21
*/
    ListNode* mergerTwoList(ListNode* headA,ListNode* headB){
        ListNode new_node(0);//下一个节点才是
        ListNode* pre = &new_node;
        while(headA && headB){
            if(headA->val <= headB->val){
                pre->next = headA;
                headA = headA->next;
            }else
            {
                pre->next = headB;
                headB = headB->next;
            }
            pre = pre->next;
        }
        //headA 有剩余
        if(headA)
        {   
            pre->next = headA;
        }
        if(headB){
            pre->next =headB;
        }
        return new_node.next;
    }

/*
*k个排序链表合并,传入的是链表引用
方法1：就是两两合并，时间复杂度高
方法2：遍历所有节点扔到vector中排序，然后拼成一个大的，KN*logKN+KN
方法3：分制后相连，也就是两两合并
leetcode 23
*/
    bool cmp(ListNode* headA,ListNode* headB){
        return headA->val<headB->val;
    }

//方法2
    ListNode* mergeKLists(std::vector<ListNode*>& lists){
       std::vector<ListNode*> node_vec;
       for(int i=0;i<lists.size();i++){
            ListNode* head = lists[i];
            while(head){
                node_vec.push_back(head);
                head = head->next;
            }    
       } 
        if(node_vec.size() == 0){
            return NULL;
        }
        std::sort(node_vec.begin(),node_vec.end(),cmp);
        for(int i=1;i<node_vec.size();i++){
            node_vec[i-1]->next = node_vec[i];//把vector元素串联起来了
        }
        node_vec[node_vec.size()-1]->next = NULL;
        return node_vec[0];
    }
//方法3 分治法
    ListNode *mergeKLists2(std::vector<ListNode *> &lists)
    {
        if(lists.size() == 0){
            return NULL;
        }
        if(lists.size() == 1){
            return lists[0];
        }
        if(lists.size() == 2){
            //merge
            return mergerTwoList(lists[0],lists[1]);
        }
        int mid = (int)lists.size()/2;
        std::vector<ListNode*> sub1_lists;
        std::vector<ListNode*> sub2_lists;
        for(int i=0;i<mid;i++){
            sub1_lists.push_back(lists[i]);//多个链表的首地址
        }
        for(int i=mid;i<lists.size();i++){
            sub2_lists.push_back(lists[i]);
        }
        ListNode* l1 = mergeKLists2(sub1_lists);
        ListNode* l2 = mergeKLists2(sub2_lists);
        return mergerTwoList(l1,l2);
    }




};


int main(){

    // ListNode a(10);
    // ListNode b(20);
    // ListNode c(30);
    // ListNode d(40);
    // ListNode e(50);
    // a.next = &b;
    // b.next = &c;
    // c.next = &d;
    // d.next = &e;
    // e.next = NULL;
    // ListNode* head = &a;
    // printf("原来的链表\n");
    // while(head){
    //     printf("%d\n",head->val);
    //     head = head->next;
    // }

    // printf("逆序的链表\n");
    // Solution solu;
    // ListNode* new_head =  solu.reverseList(&a);
    // while(new_head){
    //     printf("%d\n",new_head->val);
    //     new_head = new_head->next;
    // }

//第二个列表
    ListNode a2(9);
    ListNode b2(18);
    ListNode c2(27);
    ListNode d2(37);
    ListNode e2(30);
    ListNode f2(42);
    ListNode g2(61);
    a2.next = &b2;
    b2.next = &c2;
    c2.next = &d2;
    d2.next = &e2;
    e2.next = &f2;
    f2.next = &g2;
    g2.next = NULL;
    printf("列表2的元素为\n");
    ListNode* head2 = &a2;
    while(head2){
        printf("%d\n",head2->val);
        head2 = head2->next;
    }
    printf("列表2的分段链表元素为\n");
    Solution solu;
    ListNode* newcombinehead  = solu.partition(head2,30);
    while(newcombinehead){
        printf("%d,",newcombinehead->val);
        newcombinehead = newcombinehead->next;
    }
    // ListNode* intersectNode =  solu.getIntersectionNode2(&a,&a2);
    // printf("相交的点为%d",intersectNode->val);

    return 0;
}


