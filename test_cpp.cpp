// vector::begin/end
#include <iostream>
#include <vector>

int main ()
{
  std::vector<int*> myvector;
  for (int i=1; i<=5; i++){
	   int k = i;
	   int* x = &k;
	   std::cout<<x<<" "<<*x<<std::endl;
	//   std::cout<<i<<" "<<std::endl;
	   myvector.push_back(x);
  }
  std::cout << "myvector contains:";
  for (std::vector<int*>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it << ' ' << *(*it)<<"|";
  std::cout << '\n';

  return 0;
}