// vector::begin/end
#include <iostream>
#include <vector>
#include<string.h>
#include<cmath>
#include<map>

void print(const std::string& file, const std::string& func, const int& line){
  std::cout<<line<<std::endl;
}
void prints(const std::string& func){
  std::cout<<func<<std::endl;
}
char* basename(char* path) {
   char* ptr = rindex(path, '/');
   return ptr ? ++ptr : (char*)path;
 }


float ndcg(std::vector<float>& items, int n){
  float s = 0;
  for(int i=0; i<n && i<items.size(); i++){
    s += items[i] / (log(i+2)/log(2));
  }
  return s;
}

void inserts(std::vector<float>& doc_items, std::vector<float>& box_items, int n){
  std::vector<float> results;
  // 初始为doc的前n个
  for(int i = 0, doc_size = doc_items.size(); i < doc_size && i < n; ++i) {
    results.push_back(doc_items[i]);
  }

  int start=0, i=0, boxs_size=box_items.size();
  // 取box前n个， 依次插入
  for(i = 0, boxs_size = box_items.size(); i < boxs_size && i < n; ++i) {
    float max_score = .0f;
    int max_score_idx = 0;
    float box = box_items[i];
    // int doc_idx = 0;

    // 遍历所有位置， 计算最大ndcg
    for(int j = start, result_size = results.size(); j <= result_size && j <= n; ++j) {
      results.insert(results.begin()+j, box);
      float cur_ndcg = ndcg(results, n);
      max_score = max_score > cur_ndcg? max_score: cur_ndcg;
      max_score_idx = max_score > cur_ndcg? max_score_idx: j;
      results.erase(results.begin()+j);
    }
    if(max_score_idx >= n){ // 插入位置在最后， 可以不用继续比较了
      // doc_idx = n;
      break;
    }
    //在最大 ndcg位置插入box
    results.insert(results.begin()+max_score_idx, box);
    //每次只比较前n个
    results.resize(n);
    // doc_idx = n - i;
    start = max_score_idx + 1;
  }
   //i = box还没比较的位置, n-i=doc还没比较的位置， 按照两路归并插入
   int doc_pointer = n-i;
   int box_pointer = i;
   while(doc_pointer < doc_items.size() && box_pointer < box_items.size()){
     float doc_score = doc_items[doc_pointer];
     float box_score = box_items[box_pointer];
     if(doc_score > box_score){
       results.push_back(doc_score);
       ++doc_pointer;
     }
     else{
       results.push_back(box_score);
       ++box_pointer;
     }
   }
   		while (box_pointer < box_items.size()) {
			results.push_back(box_items[box_pointer]);
			++box_pointer;
		}

		while (doc_pointer < doc_items.size()) {
			results.push_back(doc_items[doc_pointer]);
			++doc_pointer;
		}
     
  for(int i = 0, result_size = results.size(); i < result_size; ++i) {
    std::cout<<results[i]<<std::endl;
  }
}
void inserts_mp(std::vector<float>& doc_items, std::vector<float>& box_items, int n){
  std::vector<float> results;
  std::vector<float> top_mp;
//   std::map<int, int> pos_times;

  // 初始为doc的前n个
  for(int i = 0, doc_size = doc_items.size(); i < doc_size && i < n; ++i) {
    results.push_back(doc_items[i]);
    top_mp.push_back(doc_items[i]);
  }

  int i=0, boxs_size=box_items.size();
  // 取box前n个， 依次插入
  for(i = 0; i < boxs_size && i < n; ++i) {
    float max_score = .0f;
    float box = box_items[i];
    int max_score_idx =0;

    // 遍历所有位置， 计算最大ndcg
    for(int j = 0, top_mp_size = top_mp.size(); j <= top_mp_size && j <= n; ++j) {
      top_mp.insert(top_mp.begin()+j, box);
      float cur_ndcg = ndcg(top_mp, n);
      max_score = max_score > cur_ndcg? max_score: cur_ndcg;
      max_score_idx = max_score > cur_ndcg? max_score_idx: j;
      top_mp.erase(top_mp.begin()+j);
    }

    // std::map<int, int>::iterator iter = pos_times.find(max_score_idx);
    // if(iter != pos_times.end()){
    //     int times = iter->second;
    //     max_score_idx +=times;
    //     iter->second +=1;
    // }else{
    //     pos_times[max_score_idx] = 1;
    // }
    max_score_idx += i;
    if(max_score_idx >= n){ // 插入位置在最后， 可以不用继续比较了
      // doc_idx = n;
      break;
    }
    //在最大 ndcg位置插入box
    results.insert(results.begin()+max_score_idx, box);
    //每次只比较前n个
    if(results.size()>n)
        results.resize(n);
  }
   //i = box还没比较的位置, n-i=doc还没比较的位置， 按照两路归并插入
   int doc_pointer = n-i;
   int box_pointer = i;
   while(doc_pointer < doc_items.size() && box_pointer < box_items.size()){
     float doc_score = doc_items[doc_pointer];
     float box_score = box_items[box_pointer];
     if(doc_score > box_score){
       results.push_back(doc_score);
       ++doc_pointer;
     }
     else{
       results.push_back(box_score);
       ++box_pointer;
     }
   }
   		while (box_pointer < box_items.size()) {
			results.push_back(box_items[box_pointer]);
			++box_pointer;
		}

		while (doc_pointer < doc_items.size()) {
			results.push_back(doc_items[doc_pointer]);
			++doc_pointer;
		}
     
  for(int i = 0, result_size = results.size(); i < result_size; ++i) {
    std::cout<<results[i]<<std::endl;
  }
}

	bool GetInterleavingOrDiffABParamValue(std::string& param_name, std::string* value){
    *value ="0";
    return true;
  }


int main ()
{
  uint32_t bt = 1642321444;
	uint32_t et = 1642321446;
	uint32_t ct = 1642321445;
  if(bt < et){
	  std::cout<<"<"<<std::endl;
  }

  std::string test="";
  std::string exp_name="ts";
  GetInterleavingOrDiffABParamValue(exp_name, &test);

  if(test >"0" && test<= "9"){
    int e = std::stoi(test);
    std::cout<<e<<" "<<exp_name<<" "<<std::endl;
  }
  else{
    std::cout<<"not good"<<std::endl;
  }

 std::map<std::string, float> ins;
 ins.erase("test");
 std::cout<<ins.size()<<std::endl;

  	// time_t t = time(NULL);
	// 	struct tm * tm= localtime(&t);
	// 	unsigned int search_time = mktime(tm);
    // std::cout<<t<<" "<<search_time<<std::endl;
  // uint32_t begin_time = DateTime::Parse(config_ptr.begin_time(), "yyyy-MM-dd HH:mm:ss").GetTotalSecond();
//   std::vector<float> mps;
//   mps.push_back(0.6);
//   mps.push_back(0.5);
//   mps.push_back(0.7);
//   mps.push_back(0.2);
//   mps.push_back(0.8);

//   int k=0;
//   for(std::vector<float>::iterator it=mps.begin(); it!=mps.end(); ++it){
//     float x = *it; 
//     if(x>0.61){
//       // float res = *x;
//       mps.erase(it);
//       mps.insert(mps.begin(),x);
//       k +=1;
// for(int i = 0, result_size = mps.size(); i < result_size; ++i) {
//     std::cout<<mps[i]<<" ";
//   }


//   std::cout<<"--------"<<std::endl;
//     }
//   }

// mps.erase(mps.begin(),mps.begin()+k);

// for(int i = 0, result_size = mps.size(); i < result_size; ++i) {
//     // std::cout<<mps[i]<<std::endl;
  
//     if(mps[i] >0.61){
//       mps[i]=mps.back();
//       mps.erase(i);
//       mps.insert(i);
//     }

//   std::cout<<"---"<<std::endl;
//     for(int j = 0, s = mps.size(); j < s; ++j) {
//     std::cout<<mps[j]<<std::endl;
//   }
//   // std::cout<<"---"<<std::endl;
// }
//   std::cout<<"--------"<<std::endl;
      // mps.pop_back();
      // mps.pop_back();
//   std::cout<<"--------"<<std::endl;
// for(int i = 0, result_size = mps.size(); i < result_size; ++i) {
//     std::cout<<mps[i]<<std::endl;
//   }



//   mps.push_back(0.4);
  // std::vector<float> boxs;
  // boxs.push_back(0.65);
  // boxs.push_back(0.55);
//   boxs.push_back(0.45);

  // inserts_mp(mps, boxs, 3);

  // mps.insert(mps.begin()+2, 0.2);
  // std::cout<<mps.size()<<std::endl;




  //   std::cout<<"Running In ["<<__PRETTY_FUNCTION__<<"]"<<std::endl;
  //   // std::cout<<"Running In ["<<__FUNCDNAME__<<"]"<<std::endl;
  //   std::cout<<"Running In ["<<__FUNCTION__<<"]"<<std::endl;
  //   std::cout<<"Running In ["<<__func__<<"]"<<std::endl;
  //   std::cout<<"Running In ["<<__LINE__<<"]"<<std::endl;
  //   std::cout<<"Running In ["<<__FILE__<<"]"<<std::endl;
  //   std::cout<<"----"<<std::endl;
  //   prints(basename(""));
  //   prints(std::string(__func__) +":"+ std::string(basename(__FILE__)));

  // std::vector<int*> myvector;
  // for (int i=1; i<=5; i++){
	//    int k = i;
	//    int* x = &k;
	//    std::cout<<x<<" "<<*x<<std::endl;
	// //   std::cout<<i<<" "<<std::endl;
	//    myvector.push_back(x);
  // }
  // std::cout << "myvector contains:";
  // for (std::vector<int*>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
  //   std::cout << ' ' << *it << ' ' << *(*it)<<"|";
  // std::cout << '\n';

  return 0;
}