// Threading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include "Shard.h"
#include "Threading.h"
int counts = 0;
int maxSizePerShard = 50;
void CounterThread()
{

    while (counts <= 300) {
        std::cout << counts << std::endl;

        ++counts;
    }
  
    return;
 
}
void ShardUpdates(std::vector<Blog>& blogs, const size_t & partitions, vector<Shard>& vectorShared, const int &index)
{ 

    if (index == 0) {
        std::vector<Blog> half1(blogs.begin(), blogs.begin() + partitions);
        vectorShared.push_back(Shard(1, half1));
    }
    else {
        std::vector<Blog> half2(blogs.begin() + partitions, blogs.end());
        vectorShared.push_back(Shard(2, half2));
    }

}
//void ShardUpdates(std::vector<Blog>& blogs, const size_t& partitions, vector<Shard>& vectorShared)
//{
//    std::vector<Blog> half1(blogs.begin(), blogs.begin() + partitions);
//    vectorShared.push_back(Shard(1, half1));
//    std::vector<Blog> half2(blogs.begin() + partitions, blogs.end());
//    vectorShared.push_back(Shard(2, half2));
//
//}
void AddBulkItems() {
    string title = "Test blog post ";
    string content = "Test blog content ";
    int i = 0;
    int count = 100;
   vector<Blog> blogs;
    for (int index = 0; index <= count; ++index) {
        title = title ;
        content = content;
        blogs.push_back(Blog(index, title, content));
    }
 
    std::size_t const partitions = maxSizePerShard;
        //blogs.size() / 2;
    vector<Shard> vectorShared;
    std::thread SharedJoined1(ShardUpdates, std::ref(blogs), std::ref(partitions), std::ref(vectorShared), (0));
    SharedJoined1.join();
    std::thread SharedJoined2(ShardUpdates, std::ref(blogs), std::ref(partitions), std::ref(vectorShared), (1));
    SharedJoined2.join();
  /*  std::thread SharedJoined();
    SharedJoined.join();*/
 /*   ShardUpdates(blogs, partitions, vectorShared);*/
    for (Shard _shard: vectorShared) {
        string message = "Currently on Shard " + to_string(_shard.GetShardId());
        string messageEnd = "Done with Shard " + to_string(_shard.GetShardId());
        cout << message  << endl;
        for (Blog blogItem : _shard.GetData()) {
            cout <<"Blog Post Id "<<blogItem.GetId() << " Title : " << blogItem.GetTitle() << " Date Posted : " << blogItem.GetPostedTime() << endl;
        }

        cout << messageEnd << endl;
    }
    
    
  /*  SharedJoined.join();*/
}



int main()
{

  // 

    std::thread BulkAdd(AddBulkItems);
    std::thread Counter(CounterThread);
    std::cout << "Hello World!\n";
    BulkAdd.join();
    Counter.join();
    return 0;
}

