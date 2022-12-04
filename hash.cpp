#include "source.h"
class MyHashMap
{
private:
    struct map
    {
        int key;
        int value;
        struct map *next;
        map(int K, int V) : key(K), value(V), next(nullptr) {}
    };

public:
    MyHashMap()
    {
        hashMap.resize(len);
    }

    void put(int key, int value)
    {
        int keyHash = hash(key);
        if (hashMap[keyHash] == nullptr)
            hashMap[keyHash] = new map(key, value);
        else
        {
            if (hashMap[keyHash]->key == key)
            {
                hashMap[keyHash]->value = value; //更新
                return;
            }
            /*1*/
            auto p = hashMap[keyHash]->next;
            while (p != nullptr)
            {
                if (p->key == key)
                {
                    p->value = value;
                    return;
                }
                p = p->next;
            }
            /*1这种写法,最后新添加的节点，没有接上去，因为最后一次遍历之后p指针指向最后一个节点的next
            也就是nullptr，并不指向某个地址，需要第二种写法添加链表节点*/
            p = new map(key, value);

            /*2*/
            /*
            auto p = hashMap[keyHash];
            while (p->next) {
                if (p->next->key == key) {
                    p->next->value = value;
                    return;
                }
                p = p->next;
            }
            p->next = new map(key, value);
            */
        }
    }

    int get(int key)
    {
        int keyHash = hash(key);
        if (hashMap[keyHash] == nullptr)
            return -1;
        auto p = hashMap[keyHash];
        if (p->key == key)
            return p->value;
        while (p->next)
        {
            if (p->next->key == key)
                return p->next->value;
            p = p->next;
        }
        return -1;
    }

    void remove(int key)
    {
        int keyHash = hash(key);
        if (hashMap[keyHash] == nullptr)
            return;
        auto p = hashMap[keyHash];
        if (p->key == key)
        {
            hashMap[keyHash] = p->next;
            delete p;
            return;
        }
        auto next = p->next;
        while (next)
        {
            if (next->key == key)
            {
                p->next = next->next;
                delete next;
                return;
            }
            p = next;
            next = next->next;
        }
    }

private:
    int hash(int key)
    {
        return (key % len);
    }
    int len = 31;
    vector<struct map *> hashMap;
};

class Solution
{
public:
    bool isIsomorphic(string s, string t)
    {
        if (s.size() != t.size())
            return false;
        std::unordered_map<char, char> Map;
        std::unordered_set<char> Set;
        for (int i = 0; i < s.size(); i++)
        {
            if (Map.count(s[i]) <= 0)
            {
                if (Set.count(t[i]) <= 0)
                { /*判断该值是否被映射过*/
                    Map[s[i]] = t[i];
                    Set.insert(t[i]);
                }
                else
                    return false;
            }
            else
            {
                auto it = Map.find(s[i]);
                if (t[i] != it->second)
                    return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution obj;
    string s = "foo";
    string t = "bar";
    cout << obj.isIsomorphic(s, t) << endl;

    return 0;
}
