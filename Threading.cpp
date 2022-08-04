// Threading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include "Shard.h"
#include "Threading.h"
int counts = 0;
int maxSizePerShard = 50;
void ShardUpdates(std::vector<Blog>& blogs, const size_t& partitions, vector<Shard>& vectorShared);
void CounterThread()
{

    while (counts <= 300) {
        std::cout << counts << std::endl;

        ++counts;
    }
  
    return;
 
}
void AddBulkItems() {
    string title = "Test blog post ";
    string content = "Test blog content ";
    int i = 0;
    int count = 100;
   vector<Blog> blogs;
    for (int index = 0; index <= count; ++index) {
        title = title + std::to_string(index);
        content = content + std::to_string(index);
        blogs.push_back(Blog(index, title, content));
    }
 
    std::size_t const partitions = blogs.size() / maxSizePerShard;
    vector<Shard> vectorShared;
    ShardUpdates(blogs, partitions, vectorShared);

    for (Shard _shard: vectorShared) {
        string message = "Currently on Shard " + to_string(_shard.GetShardId());
        string messageEnd = "Done with Shard " + to_string(_shard.GetShardId());
        cout << message  << endl;
        for (Blog blogItem : _shard.GetData()) {
            cout <<"Blog Post Id "<<blogItem.GetId() << " Title : " << blogItem.GetTitle() << " Date Posted : " << blogItem.GetPostedTime() << endl;
        }

        cout << messageEnd << endl;
    }
}

void ShardUpdates(std::vector<Blog>& blogs, const size_t& partitions, vector<Shard>& vectorShared)
{
    std::vector<Blog> half1(blogs.begin(), blogs.begin() + partitions);
    std::vector<Blog> half2(blogs.begin() + partitions, blogs.end());
  
    vectorShared.push_back(Shard(1, half1));
    vectorShared.push_back(Shard(1, half2));
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

