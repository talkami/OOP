#include <map>
#include <list>
#include <algorithm>
#include <string>
#include <iostream>
#include <ctime>

using namespace std;

class Date {
    long time; // msec from a point in time, as returned by clock()

public:
	Date(long msecFromNow = 0) : time(clock() + msecFromNow) {}
	operator long()const {return time;}
};

template<class K, class V, size_t SIZE, class FetchFunc>
class Cache {
    
	class Holder {
	public:
		V val;
		mutable typename list<K>::iterator posInList;
		Holder() {}
		Holder(V v, Date exp, typename list<K>::iterator pos)
		: val(v), posInList(pos), expiry(exp), accessed(Date()) {}
		operator V()const {accessed = Date(); return val;}
    	bool expired()const {return Date() >= expiry;}
    	Date lastAccessed()const {return accessed;}
	private:
		Date expiry;
    	mutable Date accessed;
	};
	
	map<K, Holder> cache;
	list<K> accessed; // sort by accessed date
	FetchFunc fetchFunc;
	
	void removeLeastAccessed() {
		K key = accessed.back(); // get the last in the list
		cout << "removing: " << key << endl;
		cache.erase(key); // remove the pair associated with this key
		accessed.pop_back(); // remove the last in the list
	}
public:
	Cache(FetchFunc fetchF): fetchFunc (fetchF) {}
	
	V get(K key) {
		auto itr = cache.find(key);
		if(itr != cache.end() && !itr->second.expired()) {
			auto itrInList = itr->second.posInList;
			accessed.push_front(*itrInList);
			accessed.erase(itrInList);
			itr->second.posInList = accessed.begin();
			cout << "serving from cache: " << key << endl;
			return itr->second;
		}
		else {
			if(itr == cache.end()) {
				if(cache.size() >= SIZE) {
					removeLeastAccessed();
				}
				cout << "adding: " << key << endl; // adding in line 57
			}
			else { // expired
				accessed.erase(itr->second.posInList);
				cout << "updating expired record: " << key << endl;                
			}
			auto vpair = fetchFunc(key);
			accessed.push_front(key);
			cache[key] =
				{vpair.first, Date(vpair.second), accessed.begin()};
			return vpair.first;
		}
	}
};

template<class K, class V, size_t SIZE, class FetchFunc>
Cache<K, V, SIZE, FetchFunc> createCache(FetchFunc fetchFunc) {
    return fetchFunc;
}

int main() {
	constexpr size_t SIZE = 2;
	auto cache = createCache<string, string, SIZE>(
		[](const string& key){
			return pair<string, long>{"value for: " + key,
									 0 /*expiry in msec*/ };
		});
		
    cout << "lines 77-79:" << endl;
	cout << cache.get("http://www.tau.ac.il") << endl;
	cout << cache.get("http://www.tau.ac.il") << endl;
	cout << cache.get("http://www.ynet.co.il") << endl;
    cout << "lines 80-82:" << endl;
	cout << cache.get("http://www.tau.ac.il") << endl;
	cout << cache.get("http://www.google.com") << endl;
	cout << cache.get("http://www.ynet.co.il") << endl;

	return 0;

}

