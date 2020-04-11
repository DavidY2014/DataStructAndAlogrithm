#include <stdio.h>
#include <stack>
#include <queue>
#include <string>
/*
*利用queue实现一个stack
leetcode 225
*/

class MyStack {
private:
    std::queue<int> _data;
public:
    /** Initialize your data structure here. */
    MyStack() {
    }
    /** Push element x onto stack. */
    void push(int x) {
        std::queue<int> temp_queue;
        temp_queue.push(x);
        //通过tempqueue调换
        while(_data.empty()){
            temp_queue.push(_data.front());
            _data.pop();
        }
        while(temp_queue.empty()){
            _data.push(temp_queue.front());
            temp_queue.pop();
        }
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int x =_data.front();
         _data.pop();
        return x;
    }
    
    /** Get the top element. */
    int top() {
        return _data.front();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
       return  _data.empty();
    }
};

/*
*利用栈实现一个队列
*/
class MyQueue {
private:
    std::stack<int> _data;
public:
    /** Initialize your data structure here. */
    MyQueue() {
    }
    /** Push element x onto stack. */
    void push(int x) {
        std::stack<int> temp_stack;//新建一个临时stack
        //通过tempqueue调换
        while(!_data.empty()){//把旧栈数据插入新栈
            temp_stack.push(_data.top());
            _data.pop();
        }
        temp_stack.push(x);
        while(!temp_stack.empty()){
            _data.push(temp_stack.top());
            temp_stack.pop();
        }
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int x =_data.top();
         _data.pop();
        return x;
    }
    
    /** Get the top element. */
    int peek() {
        return _data.top();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
       return  _data.empty();
    }
};

/*
*栈的最小变量值，如果用一个变量来存储最小值的话是不满足要求的，所以用另一个栈来存储
*每个栈状态的最小值
*leetcode 155
**/
class MinStack {
private:
    std::stack<int> _data;//数据栈
    std::stack<int> _min;//最小值栈，两者要保持一致，不然不好跟踪
public:
    /** Initialize your data structure here. */
    MinStack() {
    }
    /** Push element x onto stack. */
    void push(int x) {
        _data.push(x);
        if(_min.empty()){
            _min.push(x);//如果min为空就不判断
        }else{
            if(x>_min.top()){
                x = _min.top();
            }
            _min.push(x);
        }
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        _data.pop();
        _min.pop();
    }
    
    /** Get the top element. */
    int top() {
        return _data.top();
    }
    
    /** Returns whether the stack is empty. */
    int getMin() {
        return _min.top();
    }
};


/*
*合法的出栈序列,利用栈和队列模拟入栈和出栈来判断,此处的序列为1到n
*POJ 1363 Rails
*/
bool check_is_valid_order(std::queue<int>& order){
    std::stack<int> S;//模拟入栈
    int n = order.size();
    for(int i=1;i<=n;i++){
        S.push(i);//不相等就一直入栈，相等了就出栈，判断是否为空
        if(!order.empty() && order.front() == S.top()){
            S.pop();
            order.pop();
        }
    }
    if(!S.empty()){
        return false;
    }
    return true;
}

/*
*简单计算器,加减直接算，遇到括号就不算，建立两个栈，一个是数字，一个是运算符栈
*leetcode 224
*/
int calculate(std::string s){
    



}

int StringConvertNumber(std::string s){
    int number = 0;
    for(int i=0;i<s.length();i++){
        number  = number*10+s[i]-'0';
    }
    return number;
}

void compute(std::stack<int> &number_stack, std::stack<char> &operation_stack)
{
    if (number_stack.size() < 2)
    {
        return;
    }
    //把数字弹出来
    int num2 = number_stack.top();
    number_stack.pop();
    int num1 = number_stack.top();
    number_stack.pop();
    if(operation_stack.top() == '+'){
        number_stack.push(num2+num1);
    }
    if(operation_stack.top() == '-'){
        number_stack.push(num1-num2);
    }
    operation_stack.pop();
}

/*
*数组中第K大的数,最大堆
*leetcode 215
**/

int findKthLargest(std::vector<int>& nums,int k){
    std::priority_queue<int,std::vector<int>,std::greater<int>> Q;//最小堆,堆中维护的都是最大的数字
    for(int i=0;i<nums.size();i++){
        if(Q.size()<k){
            Q.push(nums[i]);
        }else if(nums[i]> Q.top()){
            Q.pop();
            Q.push(nums[i]);
        }
    }
    return Q.top();
}

/*
*寻找中位数,按照一般做法，数组排序后算，效率不高，可以维护两个最大最小堆来综合计算
*leetcode 295
*/
class MedianFinder {
private:
    std::priority_queue<int,std::vector<int>,std::greater<int>> small_heap;
    std::priority_queue<int> big_heap; //最大堆
public:
    /** initialize your data structure here. */
    MedianFinder() {

    }
    
    void addNum(int num) {
        if(big_heap.empty()){
            big_heap.push(num);
            return;
        }
        if(big_heap.size() == small_heap.size()){
            if(num<big_heap.top()){
                big_heap.push(num);
            }else if(num>small_heap.top()){
                small_heap.push(num);
            }
        }
        else if(big_heap.size()> small_heap.size()){
            if(num < big_heap.top()){
                small_heap.push(big_heap.top());
                big_heap.pop();
                big_heap.push(num);
            }else{
                small_heap.push(num);
            }

        }else if(small_heap.size()>big_heap.size()){
            if(num<big_heap.top()){
                big_heap.push(num);
            }else{
                big_heap.push(small_heap.top());
                small_heap.pop();
                small_heap.push(num);
            }
        }
    }
    
    double findMedian() {
        if(big_heap.size() == small_heap.size()){
            return (big_heap.top()+small_heap.top())/2;
        }else if(big_heap.size()>small_heap.size()){
                return big_heap.top();
        }
        return small_heap.top();
    }
};





int main(){

    std::priority_queue<int> big_heap;
    if(big_heap.empty()){

    }
    int test[] = {6,10,1,7,99,4,33};
    for(int i=0;i<7;i++){
        big_heap.push(test[i]);
    }
    printf("%d\n",big_heap.top());
    big_heap.push(1000);
    printf("%d\n",big_heap.top());
    for(int i=0;i<3;i++){
        big_heap.pop();
    }
    printf("%d\n",big_heap.top());
    printf("%d\n",big_heap.size());
    
    
    
    
    // std::stack<int> S;
    // if (S.empty())
    // {
    //     printf("S is empty");
    // }
    // S.push(5);
    // S.push(6);
    // S.push(10);
    // printf("S.top = %d\n", S.top());
    // S.pop();
    // S.pop();
    // printf("S.top = %d\n", S.top());
    // printf("S.top = %d\n", S.size());

    // std::queue<int> Q;
    // if (Q.empty())
    // {
    //     printf("Q is empty!\n");
    // }
    // Q.push(5);
    // Q.push(6);
    // Q.push(10);
    // printf("Q.front = %d\n", Q.front());
    // Q.pop();
    // Q.pop();
    // printf("Q.front = %d\n", Q.front());
    // Q.push(1);
    // printf("Q.back = %d\n", Q.back());
    // printf("Q.size = %d\n", Q.size());
    return 0;
}