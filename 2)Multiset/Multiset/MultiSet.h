#pragma once
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <list>
#include <iostream>
#include <stdexcept> 
#include <string>


	template <typename T>
class StatMultiSet {
	//private:
public:
		std::multiset<T> inSet;
		T min, max,size;
		mutable bool change_flag_avg, change_flag_lb, change_flag_ub;
		std::map<T, unsigned int> CashMap;
		// std::queue <T> qUnder, qAbove;
		mutable float cacheAVG;
		mutable std::map <T, int> cacheAbove, cacheLower;

		//methods
		void addNum(T value);
		int CountAbove(const T t) const;
		int CountLower(const T t) const;
		float getAvg() const;
		void showAll() const ;
		//present purposes only
		void Raise();
		//после полей класса 
		




		void addNum(const std::vector<T> &vec) {

			for (auto it : vec) {
				addNum(it);
			}
			

		}
		void addNum(const std::multiset<T> &mSet) {

			for (auto it : mSet) {
				addNum(it);
			}

		}

		void addNum(const StatMultiSet& a_stat_set) {
			for (auto it : a_stat_set)
				addNum(it);


		}




		T getMax() const {
			return max;
		}
		T getMin() const{
			return min;
		}
		
		
	/*	int CountAbove(const T t) const{
			
			
			if (change_flag_ub) {
				int c_ab = 0;
				std::multiset<T>::iterator it = inSet.lower_bound(t);
				if (it == inSet.begin()) { cacheAbove.insert(std::pair<T,int> (t, inSet.size())); change_flag_ub = false; return inSet.size(); }
				else if (it == inSet.end()) { cacheAbove.insert(std::pair<T, int>(t, 0)); change_flag_ub = false; return 0; }
				else {
					for (; it != inSet.end(); it++)
						c_ab++;

					change_flag_ub = false; cacheAbove.insert(std::pair<T, int>(t, c_ab)); return c_ab;
				}
			}
		
			else {
				std::map<T, int>::iterator it = cacheAbove.find(t);
					
				

				return it->second;
			}
		}

		

		int CountLower(const T t) const {

			if (change_flag_lb) {
				int c_ab = 0;
				 std::multiset<T>::iterator it = inSet.lower_bound(t); 
				 if (it == inSet.begin()) { cacheLower.insert(std::pair<T, int>(t, 0)); change_flag_lb = false; return 0; }
				 else if (it == inSet.end()) { cacheLower.insert(std::pair<T, int>(t, inSet.size())); change_flag_lb = false; return inSet.size(); }

				 else {
					 for (; it != inSet.end(); it++)
						 c_ab++;

					 cacheLower.insert(std::pair<T, int>(t, inSet.size() - c_ab)); change_flag_lb = false;
					 return   inSet.size() - c_ab;

				 }
			}

			else {
				std::map<T, int>::iterator it = cacheLower.find(t);
				return it->second;
			}





			/*
			
			 else if (it == inSet.end()) return inSet.size();

			 else {
				 for ( ;it != inSet.end(); it++)
					 c_ab++;


				return inSet.size()-c_ab;

			}
				*/
			
		//	for (std::multiset<T>::iterator it = inSet.upper_bound (t); it != inSet().end(); it++)
			//	c_ab++;
			

			/*
			for (auto it : inSet) {
				if (it < t) c_ab++;
			}
			
			

		}
*/
	 



};

void execute();


template <typename T>
void StatMultiSet<T>::addNum(T value) {
			 
			if (typeid(T) == typeid(std::string)) throw "excep";
		
			if (inSet.empty()) {
				min = value;
				max = value;
			}
			else {
				if (value>max) max = value;
				if (value<min) min = value;
			}
			inSet.insert(value),
				change_flag_avg= change_flag_lb =change_flag_ub = true;


			 
		

}


template <typename T>
int  StatMultiSet<T>::CountAbove(const T t) const{
			
			
			if (change_flag_ub) {
				int c_ab = 0;
				std::multiset<T>::iterator it = inSet.lower_bound(t);
				if (it == inSet.begin()) { cacheAbove.insert(std::pair<T,int> (t, inSet.size())); change_flag_ub = false; return inSet.size(); }
				else if (it == inSet.end()) { cacheAbove.insert(std::pair<T, int>(t, 0)); change_flag_ub = false; return 0; }
				else {
					for (; it != inSet.end(); it++)
						c_ab++;

					change_flag_ub = false; cacheAbove.insert(std::pair<T, int>(t, c_ab)); return c_ab;
				}
			}
		
			else {
				std::map<T, int>::iterator it = cacheAbove.find(t);
					
				

				return it->second;
			}
		}
template <typename T>
int StatMultiSet<T>::CountLower(const T t) const {

			if (change_flag_lb) {
				int c_ab = 0;
				 std::multiset<T>::iterator it = inSet.lower_bound(t); 
				 if (it == inSet.begin()) { cacheLower.insert(std::pair<T, int>(t, 0)); change_flag_lb = false; return 0; }
				 else if (it == inSet.end()) { cacheLower.insert(std::pair<T, int>(t, inSet.size())); change_flag_lb = false; return inSet.size(); }

				 else {
					 for (; it != inSet.end(); it++)
						 c_ab++;

					 cacheLower.insert(std::pair<T, int>(t, inSet.size() - c_ab)); change_flag_lb = false;
					 return   inSet.size() - c_ab;

				 }
			}

			else {
				std::map<T, int>::iterator it = cacheLower.find(t);
				return it->second;
			}

}
template <typename T>
float StatMultiSet<T>::getAvg() const {
	double avg = 0;
	if (change_flag_avg) {
		for (auto it : inSet) {
			avg = avg + it / (inSet.size());
		}
		cacheAVG = avg;
		change_flag_avg = false;
		return static_cast<float>(avg);
	}


	else return cacheAVG;


}

template <typename T>
void StatMultiSet<T>::showAll() const {
	if (inSet.size() != 0) {
		std::cout << "For now you have: \n";

		/*
		for (std::multiset<T>::iterator it = inSet.begin(); it != inSet.end(); it++)
		std::cout << *it << " ";


		for (std::multiset<T>::reverse_iterator it = inSet.rbegin(); it != inSet.rend(); it++)
		std::cout << *it << " ";

		*/

		for (auto it : inSet) {
			std::cout << it << " ";
		}
		std::cout << std::endl;

	}
	else std::cout << "For now you have nothing yet \n";


}

template<typename T>
inline void StatMultiSet<T>::Raise()
{
	std::cout << "Choose your destiny,mortal ! \n\n1) Add number\n2) Get element list\n3) Get elements above x\n4) Get elements bellow x\n5)Exit\n";
	int choose;
	T x;
	std::string choice;
	bool on = true;

	while (on) {
		std::cout << "Choice = ";
		std::cin >> choose;
		switch (choose) {
		case 1: {
			std::cout << "It will be: ";
			std::cin >> x;
			addNum(x);
			
			
			break;
		}
		case 2: {
			showAll();
			break;
		}
		case 3: {
			std::cout << "X=  ";
			std::cin >> x;
			StatMultiSet<T>::CountAbove(x);
			
			
			break;
		}
		case 4: {
			std::cout << "X=  ";
			std::cin >> x;
			StatMultiSet<T>::CountLower(x);
			
			
			break;
		}

		case 5: {

			on = false;
			break;
		}


		}
	}


}
