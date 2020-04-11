#include <stdio.h>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>

/*
*分糖果,g 为需求因子，s为糖果大小,s>=g 才可以
*对g和s进行排序，遍历的去匹配
*leetcode 455
*/
int findContentChildren(std::vector<int>& g,std::vector<int>& s){
    std::sort(g.begin(),g.end());
    std::sort(s.begin(),s.end());
    int child =0;//代表g的排序
    int cookie = 0 ;//代表s的排序
    while(child<g.size() &&   cookie<s.size()){
        if(g[child]<=s[cookie]){
            //g被满足
            child++;
        }
        cookie++;
    }
    return child;
}

/**
 * 摇摆序列,最长子序列的长度（不是连续的，只需要返回摇摆序列长度就行）
 * leetcode 376
*/
int wiggleMaxLength(std::vector<int>& nums){
    if(nums.size()<2){
        return nums.size();
    }
    static const int BEGIN = 0;
    static const int UP =1;
    static const int DOWN =2;
    int STATE = BEGIN;
    int max_length =1;
    for(int i=1;i<nums.size();i++){
        switch (STATE)
        {
        case BEGIN:
            if(nums[i-1]<nums[i]){
                STATE = UP;
                max_length ++;
            }else if(nums[i-1]>nums[i]){
                STATE=DOWN;
                max_length++;
            }
            break;
        case UP:
            if(nums[i-1]>nums[i]){
                STATE = DOWN;
                max_length++;
            }
            break;
        case DOWN:
            if(nums[i-1]<nums[i]){
                STATE = UP;
                max_length++;
            }
            break;
        }

    }
    return max_length;
}

/**
 * 移除K个数字,通过栈实现
 *leetcode 402 
*/
std::string removeKdigits(std::string num,int k){
    std::vector<int> S;//使用vector当做栈，因为vector可以遍历，本质上内部和stack'一样
    std::string result = "";
    for(int i=0;i<num.length();i++){
        int number= num[i]-'0';  //这个是字符转数字
        while(S.size()!=0 && S[S.size()-1] >number && k>0){
            S.pop_back();//当栈是的数字大时，可以一直删除，直到遇到小的再入栈
            k--;
        }
        if(number!=0 || S.size()!=0){
            S.push_back(number);
        }
    }
    while(S.size()!=0 && k>0){
        S.pop_back();
        k--;
    }
    //遍历栈元素
    for(int i=0;i<S.size();i++){
        result.append(1,'0'+S[i]);//数字转字符
    }
    if(result == ""){
        result = "0";
    }
    return result;
}

/**
 * 跳跃游戏,这里面包含一个最多，就会有贪心的思想,通过index数组来计算
 * 解题思路：
 * 1，如果某一个作为 起跳点 的格子可以跳跃的距离是 3，那么表示后面 3 个格子都可以作为 起跳点。
 * 2，可以对每一个能作为 起跳点 的格子都尝试跳一次，把 能跳到最远的距离 不断更新。
 * 3，如果可以一直跳到最后，就成功了。
 * leetcode 55
*/
bool canJump(std::vector<int>& nums){
    std::vector<int> index;
    for(int i=0;i<nums.size();i++){
        index.push_back(i+nums[i]);
    }
    int jump =0;
    int max_index = index[0];
    while(jump<index.size()&& jump<=max_index){
        if(max_index<index[jump]){
            max_index = index[jump];
        }
        jump++;
    }
    if(jump == index.size()){//遍历结束
       return true; 
    }
    return false;
}

/**
 * 跳跃有戏2
 * leetcode 45
 * 
*/

int jump(std::vector<int>& nums){
    

}







int main(){
    printf("greedy\n");
    const int RMB[] = {200,100,20,10,5,1};
    const int NUM = 6;
    int X = 628;
    int count =0;
    for(int i=0;i<NUM;i++){
        int use = X/RMB[i];
        count+=use;
        X = X - use*RMB[i];
        printf("需要面额%d的张数%d\n",RMB[i],count);
        printf("剩余需要支付的金额:%d\n",X);
    }
    printf("总共需要%d张\n",count);
    return 0;
}