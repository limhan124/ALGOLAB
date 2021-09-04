#include<iostream>
#include <climits>
#include<algorithm>

#define MAX (1024*64+4)
#define NMAX 2052
using namespace std;
typedef struct{
  int position;
  int word;
}point;
bool cmp(point a,point b)
{
  return a.position<b.position;
}
point line[MAX];
int word_frequency[NMAX];
int testcases(){
  //n个单词
  int n;
  cin>>n;
  //总次数
  int sum=0;
  //每个单词出现的次数
  // vector<int> word_frequency(n);
  for(int i=0;i<n;i++){
    cin>>word_frequency[i];
    sum+=word_frequency[i];
  }
  
  // point line[sum];
  int count=0;
  for(int i=0;i<n;i++){
    for(int j=0;j<word_frequency[i];j++){
      cin>>line[count].position;
      line[count].word=i;
      count++;
    }
  }
  sort(line,line+sum,cmp);
  
  int left=0;
  int right=sum-1;
  int ans=INT_MAX;
  while(word_frequency[line[right].word]>1){
    word_frequency[line[right].word]--;
    right--;
  }
  while(word_frequency[line[left].word]>1){
    word_frequency[line[left].word]--;
    left++;
  }
  ans=line[right].position-line[left].position+1;
  while(true)
  {
    int word=line[left].word;
    word_frequency[word]--;
    left++;
    while(line[right].word!=word)
    {
      right++;
      if(right>=sum)
        goto xxx;
      word_frequency[line[right].word]++;
    }
    while(word_frequency[line[left].word]>1)
    {
      word_frequency[line[left].word]--;
      left++;
    }
    int tmp_ans=line[right].position-line[left].position+1;
    if(tmp_ans<ans){
      ans=tmp_ans;
    }
  }
  xxx:
  std::cout<<ans<<std::endl;
  return 0;
}
int main(){
  int cases;
  cin>>cases;
  for(;cases;cases--){
    testcases();
  }
  return 0;
}

