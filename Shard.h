#pragma once
#include "Blog.h"
#include <vector>
class Shard {
public:
	Shard(int shardid, vector<Blog> blogs) : ShardId(shardid), Data(blogs) {

	}
	void SetData(vector<Blog> blogs) {
		Data = blogs;
	}
	int GetShardId() {
		return ShardId;
	}
	vector<Blog> GetData() {
		return Data;
	}
	vector<Blog> GetData(int shard) {
		if(shard == GetShardId())
			return Data;
		nullptr;
	}
private:
	int ShardId;
	vector<Blog> Data;
};