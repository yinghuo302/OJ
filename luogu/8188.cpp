/*
 * @Author: zanilia
 * @Date: 2023-02-28 10:57:00
 * @LastEditTime: 2023-02-28 11:36:15
 * @Descripttion: 
 */
#include <iostream>
#include <functional>
#define MAX_M 100000
using namespace std;
template<class DataType,class Compare>
class Heap {
private:
    DataType* _data;
    unsigned _size; //当前大小
    unsigned _capacity; //总容量
    void upAdjust();
    void downAdjust(int low=1);
public:
    Heap(); 
    Heap(unsigned Capacity);
    ~Heap();
    void push(const DataType& element); 
    const DataType& pop();
    const DataType& top();
	void reserve(int capacity);
	void clear();
    bool empty();
    unsigned int size(); 
    unsigned capacity();
};
template<class DataType,class Compare>
Heap<DataType,Compare>::Heap():_size(0),_capacity(20),_data(new DataType[21]){}

template<class DataType,class Compare>
Heap<DataType,Compare>::Heap(unsigned capacity):_size(0),_capacity(capacity),_data(new DataType[capacity+1]){}

template<class DataType,class Compare>
Heap<DataType,Compare>::~Heap(){
    delete[] _data;
    _size = 0;
    _capacity = 0;
}

template<class DataType,class Compare>
void Heap<DataType,Compare>::reserve(int capacity){
	if(_capacity > capacity)
		return ;
	_capacity = capacity;
	DataType* tem = new DataType[_capacity+1];
	for(unsigned i =1;i<=_size;++i)
		tem[i] = _data[i];
	delete[] _data;
	_data = tem;
}

template<class DataType,class Compare>
void Heap<DataType,Compare>::upAdjust(){
    unsigned element_need_adjust = _size, parent = _size>>1;
    Compare cmp;
    while (parent>=1){
        if(!cmp(_data[element_need_adjust],_data[parent])){
            DataType tem = _data[element_need_adjust];
            _data[element_need_adjust] = _data[parent];
            _data[parent] = tem;
            element_need_adjust >>= 1;
            parent >>= 1;
        }
        else
            break;
    } 
}

template<class DataType,class Compare>
void Heap<DataType,Compare>::downAdjust(int low){
    unsigned child = low<<1;
    Compare cmp;
    while (child <=_size){
        if(child<_size&&cmp(_data[child],_data[child+1]))
            ++child;
        if(cmp(_data[low],_data[child])){
            DataType tem = _data[low];
            _data[low] = _data[child];
            _data[child] = tem;
            low = child;
            child = low << 1;
        }
        else
            break;
    }
}

template<class DataType,class Compare>
void Heap<DataType,Compare>::push(const DataType& element){
    if(_size == _capacity)
        reserve(_size<<1);
    _data[++_size] = element;
    upAdjust();
} 

template<class DataType,class Compare>
const DataType& Heap<DataType,Compare>::pop(){
    _data[0] = _data[1];
    _data[1] = _data[_size];
    --_size;
    downAdjust();
    return _data[0];
}

template<class DataType,class Compare>
void Heap<DataType,Compare>::clear(){
    _size = 0;
}

template<class DataType,class Compare>
const DataType& Heap<DataType,Compare>::top(){
    return _data[1];
}

template<class DataType,class Compare>
bool Heap<DataType,Compare>::empty(){
    return (_size==0);
}

template<class DataType,class Compare>
unsigned Heap<DataType,Compare>::size(){
    return _size;
}

template<class DataType,class Compare>
unsigned Heap<DataType,Compare>::capacity(){
    return _capacity;
}
int emails[MAX_M];
int t;
int m,n,k;
int tem;
Heap<int,less<int>> hp;
int main(){
	cin >> t;
	while(t--){
		cin >> m >> n >> k;
		hp.clear();
		hp.reserve(k);
		for(int i=0;i<n;i++)
			cin >> emails[i];
		for(int i=0;i<k;i++)
			hp.push(emails[i]);
		        
	}
}