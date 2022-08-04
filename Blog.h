#pragma once
#include <string>
#include <time.h>
using namespace std;
class Blog {
public:
	Blog(int id, string title,string content, time_t postTime = time(0), int contentScore = 0) :
		BlogId(id),Title(title),Content(content),PostedTime(postTime), ContentScore(contentScore)
	{}
	/*Blog(int id, string title, string content) :
		BlogId(id), Title(title), Content(content)
	{}*/
	~Blog() {

	}
	void SetId(int id) {
		BlogId = id;
	}
	void SetTitle(string title) {
		Title = title;
	}
	void SetContent(string content) {
		Content = content;
	}
	void SetPostedTime(time_t postedTime) {
		PostedTime = postedTime;
	}
	void SetContentScore(int contentScore) {
		ContentScore = contentScore;
	}

	int GetId() {
		return BlogId;
	}
	string GetTitle() {
		return Title;
	}
	string GetContent() {
		return Content;
	}
	time_t GetPostedTime() {
		return PostedTime;
	}
	int GetContentScore() {
		return ContentScore;
	}
private:
	int BlogId;
	string Title;
	string Content;
	time_t PostedTime = time(0);
	int ContentScore =0;
};