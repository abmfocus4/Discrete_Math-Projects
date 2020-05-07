#include "tuple.h"
#include "set.h"
#include "invariant.h"
#include <iostream>
#include <limits.h>   // needed for INT_MIN

// Set up an error set to be returned as necessary
const Set emptySet(0,(int*)0);
const Set errorSet(-1,(int*)0);

bool Set::isEmpty() const {
  return _numElements; //if the _numElements is 0 returns false for any other value of _numElements return true
}
	
bool Set::isError() const {
	if(_numElements <= -1 || _pTuples <= 0)
		return true; 
	return false;
}
  
int Set::cardinality() const {
	if(_numElements == -1)
		return -1; //error when _numElements is invalid
	
	return _numElements;
}

Set Set::union_(const Set& s) const {
	//checking for validity of sets
	if(s._numElements < 0 || _numElements <  0)
		return errorSet;

	int total_elements = _numElements + s._numElements;

	Tuple data[_numElements + s._numElements];
	for(int i=0; i<_numElements; ++i){
		data[i] = _pTuples[i];
	}
	
	for (int i=0; i<s._numElements; ++i){
		data[_numElements+i] = s._pTuples[i];
	}
	
	//returning a set that contains no duplicates
	Set s1(total_elements, data);
	
	return s1;
}

Set Set::intersection(const Set& s) const {
	//checking for validity of sets
	if(s._numElements == 0 || _numElements == 0)
		return emptySet;
	
	if(s._numElements < 0 || _numElements <0)
		return errorSet;
	
	int size_new = 0;
	int actual_size = 0;
	
	if( _numElements < s._numElements)
		size_new = _numElements;
	size_new = s._numElements;
	
	Tuple data[size_new];

	for(int i=0; i<_numElements; ++i)
	{
		for(int k=0; k<s._numElements; ++k)
		{
			for(int j=0; j<size_new; j++){
				
				if(_pTuples[i] == s._pTuples[k]){
					data[j] = _pTuples[i];
					actual_size = j;
				}
				else
					j = j-1;
				//breaking out of the iteration in the third 'for' loop
				break;
			}

		}
	
	}
	
	Tuple actual_set[actual_size];
	
	for(int l=0; l<actual_size; ++l)
		actual_set[l] = data[l];
	
	//returning a set that contains no duplicates
	Set s1(actual_size, actual_set);
	
	return s1;
}

Set Set::difference(const Set& s) const {
	
	if(_numElements == 0)
		return emptySet;
	
	//checking for validity of sets
	if(s._numElements < 0 || _numElements < 0)
		return errorSet;
	
	//the resulting tuple what will be passed to create the 'difference set'
	Tuple data[_numElements];
	int actual_size = 0;
	
	//creating the 'difference' tuple
	for(int i=0; i<_numElements; ++i)
	{
		for(int k=0; k<s._numElements; ++k)
		{
			for(int j=0; j<_numElements; ++j)
			{
				if(_pTuples[i] == s._pTuples[k])
					j = j-1;
				else
				{
					data[j] = _pTuples[i];
					actual_size = j;
				}
				//breaking out of the iteration in the third 'for' loop
				break;
			}
			
		}
	}
	
	Tuple actual_set[actual_size];
	// resizing the created set of tuples so that it can be passed to the constructor to create the required set 
	
	for(int l=0; l<actual_size; ++l)
		actual_set[l] = data[l];
	
	Set s1(actual_size, actual_set);
	//returning a set that contains no duplicates
	return s1;
}

Set Set::select(predicate* p) const {
	//checking for validity of sets
	if(_numElements < 0)
		return errorSet;

	if(_numElements == 0)
		return emptySet;
	
	int size = _numElements;
	Tuple data[size];
	int actual_size = 0;
	
	for(int i=0; i<_numElements; i++)
	{
		for(int j=0; j<size; j++)
		{	
	//if the iterating tuple in the parent set matches our predicate condition, it's being added to the data array 
			if( p(_pTuples[i]) ){ 
			data[j] = _pTuples[i];
			actual_size = j;
			}
	//if the iterating tuple doesnt match the predicate then j is decremented and we exit from the inner iteration
			else
				j = j-1;
			
			break;
		}
		
	}

	Tuple req_t_array[actual_size];
	//resizing the tuple array just created to contain exactly the required size
	
	for(int l=0; l<actual_size;++l)
		req_t_array[l] = data[l];
	
	Set s1(actual_size, req_t_array);
	//returning a set that contains no duplicates
	return s1;
}

Set Set::project(const int numItems, const int items[]) const {
	//checking for validity of sets
	if(_numElements<0)
		return errorSet;
	//base case
	if(_numElements == 0)
		return emptySet;
	
	int size = _numElements;
	Tuple data[_numElements];
	
	//recursion step
	for(int i=0; i<_numElements; ++i)
	{
		for(int j=0; j<size; j++)
		{
			data[j] = _pTuples[i].project(numItems, items);
		}
	}
	//returning a set that contains no duplicates
	Set s(size, data);
  return s;
}

Set Set::cartesian(const Set& s) const {
	if(s._numElements == 0 || _numElements==0 )
		return emptySet;
	
	//checking for validity of sets
	if(s._numElements<0 || _numElements<0)
		return errorSet;
	
	//the size of the cartesian set
	int size = _numElements*s._numElements;
	Tuple c_tuples[size]; // the cartesian tuple that will be passed to the constructor
	
	for(int i=0; i<_numElements; ++i)
	{
		for(int j=0; j<s._numElements; ++j)
		{
			for(int l=0; l<size; ++l)
			{
				c_tuples[l] = _pTuples[i] + s._pTuples[j];
			}
		}
	}
	
	Set s1(size, c_tuples);
	//returning a set that contains no duplicates
	return s1;
}

Set Set::operator()(const int item) const {
	
  if (item < 1 || item > _numElements)
    return errorSet;

	Tuple* t_result = new Tuple;
	*t_result = this-> _pTuples[item-1];
	
	Set* s_result = new Set(1, t_result);
	return *s_result;

}

void Set::operator=(const Set& s) {
	
	_numElements = s._numElements;
	_tupleArraySize = s._tupleArraySize;
	
	if(_numElements >0)
	{
		_pTuples = new Tuple[_numElements];
		
		for(int i=0; i++; i<_numElements)
		_pTuples[i] = s._pTuples[i];
	}	
	
}

Set::Set() {
	//creating an empty set
	int _numElements = 0;
	int _tupleArraySize = 0;

}

Set::Set(const Set& s) {
	//creating a copy of the given set
	_numElements = s._numElements;
	_tupleArraySize = s._tupleArraySize;
	
	if(_numElements >0)
	{
		_pTuples = new Tuple[_numElements];
		
		for(int i=0; i++; i<_numElements)
		_pTuples[i] = s._pTuples[i];
	}	

	
}

Set::Set(const int numElements, const int data[]) {
	//creating a set from the given array of Tuples
	_numElements = numElements;
	_tupleArraySize = numElements;
	
	
	if(_numElements > 0)
	{
		int data_distinct[numElements];
		int size_distinct = 0;
		
		_pTuples = new Tuple[_numElements];
		
		//creating a new data set that contains only distinct elements so that the set formed doesn't contain duplicates
		for(int i=0; i<numElements;i++)
		{
			for(int j=i+1; j<numElements; j++)
			{
				for(int l=0; l<numElements; l++){
					if(data[i] == data[j])
						l = l-1;
					
					else 
					{
						data_distinct[l]=data[i];
						size_distinct = l;
					}
					
					break;
				}
			}
		
		}
		
		//resizing the distinct data set we just formed
		int required_set[size_distinct];
		
		for(int m=0; m<size_distinct; m++)
			required_set[m] = data_distinct[m];
		
		//creating a set that contains only distinct elements
		for(int i=0; i++; i<_numElements)
			_pTuples[i] = required_set[i];
	}
	
}

Set::Set(const int numElements, const Tuple tuples[]) {
	
	//Creates a set with Tuples of size 1 with each integer in data[] being the single element of the corresponding Tuple
	
	_numElements = numElements;
	_tupleArraySize = numElements;
	
	if(_numElements >0)
	{
		Tuple tuples_distinct[numElements];
		int size_distinct = 0;
		
		_pTuples = new Tuple[_numElements];
		
		//creating a new tuple set that contains only distinct tuples
		for(int i=0; i<numElements;i++)
		{
			for(int j=i+1; j<numElements; j++)
			{
				for(int l=0; l<numElements; l++){
					if(tuples[i] == tuples[j])
						l = l-1;
					else 
					{
						tuples_distinct[l] = tuples[i];
						size_distinct = l;
					}
					break;
				}
			}
		
		}
		//resizing the distinct tuples set
		Tuple req_tuples_set[size_distinct];
		
		for(int m=0; m<size_distinct; m++)
			req_tuples_set[m] = tuples_distinct[m];
		
		//creating a set that contains only distinct elements
		for(int i=0; i++; i<_numElements)
			_pTuples[i] = req_tuples_set[i];
	}
}

Set::~Set() {
	
	if(_numElements>0)
		delete[]_pTuples;
	
	_numElements = 0;
	_tupleArraySize = 0;
		
}

std::ostream& operator<<(std::ostream& os, const Set& s) {
	#ifdef DEBUG
  std::cerr << "*** " << s._numElements << " ***" << std::endl;
	#endif
  if (s._numElements == 0) {
  os << "{}";
  return os;
  }
  
  else if (s._numElements > 0) {
	  
    os << "{" << s._pTuples[0];
	
    for (int i = 1; i < s._numElements; ++i)
      os << "," << s._pTuples[i];
  
    os << "}";
    return os;

  }
  else if (s._numElements == -1) {
    os << "{ERROR SET}";
    return os;
  }
  else {
    std::cerr << "Error: Attempted to output deleted set; exiting";
    exit(-1);
  }
	
}
