/*
 * ChainHashTable.h
 *
 *  Created on: ??�/??�/????
 *      Author: ENG.HamaDa
 */

#ifndef CHAINHASHTABLE_H_
#define CHAINHASHTABLE_H_
#include  <list>
#include <vector>
#include <iostream>




template <typename T>
class ChainHashTable{
public:
	enum{lazy_deleted =-1 ,empty =0  ,hold};
	class HashTableEntry{
	public:
		unsigned int m_flag ;
		std::list<T> head;
	};

	HashTableEntry *m_table;
	unsigned int size_of_hashtable;


    unsigned int (*hashFunc)(const int &data , unsigned int &size);

	ChainHashTable(unsigned int (*hashFunc)(const int &data , unsigned int &size), unsigned int n=101);

	void hashTableInitalize(unsigned int (*hashFun)(const int &data , unsigned int &size), unsigned int n);

     bool insert(const T &data);

     bool find(const T &data) ;
     T remove(const T &data, bool &found);
     void dump();


     int at(int index, std::vector<T> &contents);
     ChainHashTable(ChainHashTable<T>& other);
     const ChainHashTable<T>& operator=(ChainHashTable<T>& rhs);

    ~ChainHashTable();
};



template <typename T>
ChainHashTable<T>::ChainHashTable(unsigned int (*hashFunc)(const int &data , unsigned int &size), unsigned int n){
		this->size_of_hashtable =n;
		this->m_table = new HashTableEntry[n];
		this->hashFunc=hashFunc;
		for (unsigned int i = 0; i < n; ++i) {
			(m_table+i)->m_flag=0;
		}
	}

template <typename T>
	void ChainHashTable<T>::hashTableInitalize(unsigned int (*hashFun)(const int &data , unsigned int &size), unsigned int n){
		this->size_of_hashtable =n;
		this->m_table = new HashTableEntry[n];
		this->hashFunc=hashFunc;
		for (unsigned int i = 0; i < n; ++i) {
			(m_table+i)->m_flag=0;
		}
	}

    // Functions in a standard hash table interface,
    // independent of implementation:
template <typename T>
     bool ChainHashTable<T>::insert(const T &data){
    	 unsigned int i = hashFunc(data, size_of_hashtable);
    	 if((i < size_of_hashtable )&&(this->find(data) != true)){
    		 (m_table+i)->m_flag=hold;
        	 (m_table+i)->head.push_front(data);

    	 }else{
    		 return false;
    	 }

    	 return true;
     }

template <typename T>
     bool ChainHashTable<T>::find(const T &data) {
    	 std::list<int>::iterator it;
    	 unsigned int i = hashFunc(data, size_of_hashtable);
    	 if((i < size_of_hashtable) && ((m_table+i)->m_flag == hold)){
    		 for (it=(m_table+i)->head.begin() ; it != (m_table+i)->head.end() ;++it ) {
				if(*it == data){
					return true;
				}
			}//for

    	 }
    		 return false;

     }

template <typename T>
     T ChainHashTable<T>::remove(const T &data, bool &found){
    	 unsigned int i = hashFunc(data, size_of_hashtable);
    	 found =this->find(data);
    	 if(found == true){
        	 (m_table+i)->head.remove(data);
        	 if((m_table+i)->head.size()  == 0){
        		 (m_table+i)->m_flag =lazy_deleted;
        	 }
        	 return data;
    	 }else{
    		 found =false;
    		 return false;
    	 }


     }

    // Functions for debugging and grading:
template <typename T>
     void ChainHashTable<T>::dump(){
    	 std::list<int>::iterator it;
    	 std::cout<<"ChainHashTable dump; size:" <<size_of_hashtable <<" buckets"<<std::endl;
    	 for (unsigned int i = 0; i < size_of_hashtable; ++i) {
    		 std::cout<<"["<< i<<"]:";
    		 for (it=(m_table+i)->head.begin() ; it != (m_table+i)->head.end() ;++it ) {
    			 std::cout<<*it<<" , ";
			}
    		 std::cout<<std::endl;
		}
     }

template <typename T>
     int ChainHashTable<T>::at(int index, std::vector<T> &contents) {
    	 std::list<int>::iterator it;
    	 if((index < 0) ||((unsigned int)index > size_of_hashtable)){
    		  throw std::out_of_range("the index it out of rang of Hashtable");
    		  return false;
    	 }
    	 for (it=(m_table+index)->head.begin() ; it != (m_table+index)->head.end() ;++it ){
    		 contents.push_back(*it);
    	 }
    	 return (m_table+index)->head.size();

     }
		template <typename T>
     ChainHashTable<T>::ChainHashTable(ChainHashTable& other){
    	 std::list<int>::iterator it;
    	 /***************************/
    	 hashTableInitalize(other.hashFunc , other.size_of_hashtable);
    	 /***************************/
    	 for (unsigned int i = 0; i < other.size_of_hashtable; ++i) {
    		 ((this->m_table) + i)->m_flag =((other.m_table) + i)->m_flag;
    		 for (it=(other.m_table+i)->head.end(); it != (other.m_table+i)->head.begin() ;--it) {
    			 ((this->m_table) + i)->head.push_front(*it);
			}//it for

		}// i for
     }

     template <typename T>
     const ChainHashTable<T>& ChainHashTable<T>::operator =(ChainHashTable& rhs){
    	 std::list<int>::iterator it;
    	 unsigned char minSize =rhs.size_of_hashtable > this->size_of_hashtable? this->size_of_hashtable:rhs.size_of_hashtable;

    	 for (unsigned int i = 0; i < minSize ; ++i) {
    		 ((this->m_table) + i)->m_flag =((rhs.m_table) + i)->m_flag;
    		 for (it=(rhs.m_table+i)->head.end(); it != (rhs.m_table+i)->head.begin() ;--it) {
    			 ((this->m_table) + i)->head.push_front(*it);
			}//it for

		}// i for
    	 return *this;
     }



    // There are no other data members that the different derived classes
    // would have in common
     template <typename T>
     ChainHashTable<T>::~ChainHashTable(){
    	for (unsigned int i = 0; i <size_of_hashtable ; ++i) {
			if((m_table+i)->m_flag){
				(m_table+i)->head.clear();
			}
		}
    	delete [] m_table;
    }


#endif /* CHAINHASHTABLE_H_ */
