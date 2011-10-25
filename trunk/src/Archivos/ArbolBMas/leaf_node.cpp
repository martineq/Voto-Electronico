#include "leaf_node.h"
leaf_node::leaf_node(){ this->currentpos=this->next=0; return; };
leaf_node::~leaf_node(){ return; };

leaf_node & leaf_node::operator=(const leaf_node &rhs)
{
	if (this != &rhs) {
		this->next = rhs.next;
		this->l = rhs.l;
		this->currentpos = rhs.currentpos;
    }

    return *this;
}

void leaf_node::initialization()
{
 vector<char> data;
 data.push_back('H');
 data.push_back('L');
 std::pair<vector<char>, std::string> first(data,"test");
 data[0]='K';
 data[1]='R';
 std::pair<vector<char>, std::string> second(data, "a");
 data[0]='L';
 data[1]='L';
 std::pair<vector<char>, std::string> third(data, "bmo");
 data[0]='M';
 data[1]='G';
 data.push_back('T');
 std::pair<vector<char>, std::string> fourth(data, "deloitte");
 this->l.push_back(first);
 this->l.push_back(second);
 this->l.push_back(third);
 this->l.push_back(fourth);
 this->next = 5;
 sort(this->l.begin(), this->l.end(), leaf_node::compare);
}

void leaf_node::setnext(int n)
{
	this->next=n;
}

int leaf_node::compare(std::pair<vector<char>, std::string> l, std::pair<vector<char>, std::string> r)
{
    return l.second < r.second;
}

//this funcion returns a pair, one member of the pair is a status bit, the other is the complete key,data pair
std::pair<std::pair<vector<char>,std::string>,int> leaf_node::nextelem()
{
	std::pair<std::pair<vector<char>,std::string>,int> retval;
	if (this->l.size()==0 && this->next != 0)
	{	
		retval.second=this->next;
		return retval;
	}; // I have to take into account that there might be empty nodes but with a next pointer 
	if (this->l.size()==0)
		return retval;
	retval.second=0;
	retval.first = this->l[this->currentpos++];
	if((int)this->l.size()==this->currentpos)
	{
		if(this->next==0)
			retval.second=-1;
		else
			retval.second=this->next;
	}
	return retval;
}

std::vector<char> leaf_node::search(string str)
{
 vector<char> retval;
 this->currentpos=0;  
 
 if(this->l.size()==0)
	 return retval; //the thing is empty, this should not happen but still...
 
 while(this->l[this->currentpos].second < str)
 {
   if ((int)this->l.size()-1== this->currentpos)
	   break;
   this->currentpos++;
 }

 if(this->l[this->currentpos].second == str) 
   return this->l[this->currentpos++].first; //the plus plus is on purpose, i need it to actually be able to implement the nextelem stuff
 
 return retval; //the thing was not found so I return an empty vector
}

std::vector<char> leaf_node::serialize()
{
 /*initialization to test
 vector<char> data;
 
 data.push_back('H');
 data.push_back('L');
 std::pair<vector<char>, std::string> first(data,"test");
 data[0]='K';
 data[1]='R';
 std::pair<vector<char>, std::string> second(data, "a");
 data[0]='L';
 data[1]='L';
 std::pair<vector<char>, std::string> third(data, "bmo");
 data[0]='M';
 data[1]='G';
 data.push_back('T');
 std::pair<vector<char>, std::string> fourth(data, "deloitte");

 
 
 this->l.push_back(first);
 this->l.push_back(second);
 this->l.push_back(third);
 this->l.push_back(fourth);
 this->next = 5;
 end of initialization*/
 
 vector<char> retval;
 vector<char> *mem = &retval;
 std::vector<std::pair<vector<char>, std::string> >::iterator it;
 char *tmp;
 int size;
 //add header
 mem->push_back('L'); //this is a Leaf node, therefore, it uses an L header
 
 //add the pointer to the block containing stuff that is smaller than the smallest key
 tmp = (char*)&(this->next);
 for(int i=0;i<4;i++)
 {
  mem->push_back(tmp[i]);
 }
 
 //add size of the list
 size = this->l.size();
 tmp = (char*)&size;
 for(int i=0;i<4;i++)
 {
  mem->push_back(tmp[i]);
 }
 
 //add all the elements of the list
 for(it = this->l.begin(); it != this->l.end(); it++)
 {
  //add the size of the key
  size=strlen(it->second.c_str());
  tmp=(char*)&size;
  for(int i=0;i<4;i++)
  {
   mem->push_back(tmp[i]);
  }
  
  tmp=(char*)it->second.c_str();
  for(int i=0;i<(int)strlen(tmp);i++)
  {
   mem->push_back(tmp[i]);
  }
  
  //add the size of the data
  size=it->first.size();
  
  //cout << "add size of data: " << size << endl; 
  
  tmp=(char*)&size;
  for(int i=0;i<4;i++)
  {
   mem->push_back(tmp[i]);
  }
  
  for(int i=0;i<(int)it->first.size();i++)
  {
   mem->push_back(it->first[i]);
  }
 }
 return retval;
}

char leaf_node::peek(vector<char> node)
{
     return  (node)[0];
}

// No description
void leaf_node::deserialize(std::vector<char> v)
{
 int i=0; //this will be the index we will be using
 i++; //skip the header
 int inttmp=0;
 int size=0;
 int elemsize=0;
 
 char *charptr=(char*)&inttmp;
 for(int j=0;j<4;j++)
 {
   charptr[j]=v[i++];
 }
 this->next=inttmp; //deserialized the pointer to the next leaf
  
 charptr=(char*)&size;
 for(int j=0;j<4;j++)
 {
   charptr[j]=v[i++]; //deserialized the number of elements in the thing
 }
 
 
 for(int it=0; it < size; it++) // iterate over the s
 {
        
    std::pair<vector<char>, std::string> data; //get the needed storage to keep the item
    
    charptr=(char*)&elemsize;
    for(int j=0;j<4;j++)
    {
       charptr[j]=v[i++]; //deserialized size of the key
    }
    for(int j=0;j<elemsize;j++)
    {
       data.second.push_back(v[i++]); //serialize the string
    }
    elemsize=0;
    charptr=(char*)&elemsize;
    
    for(int j=0;j<4;j++)
    {
       charptr[j]=v[i++]; //deserialized size of the data
    }
    
    for(int j=0;j<elemsize;j++)
    {
       //cout << v[i] << endl;
       data.first.push_back(v[i++]); //serialize the data
    }
    
    this->l.push_back(data);
 }
}


int leaf_node::getsize()
{
	vector<char> tmp;
	tmp=this->serialize();
	return tmp.size();
}

//after this function is called, the current leaf_node has the data that is larger than the new root
//and the leaf node in the pair has the data that is lowe than the new root
//the inner node in the pair is escencially the new root

std::pair<inner_node,leaf_node> leaf_node::split_root(int maxsize, int rightblock, int leftblock)
{
	std::pair<inner_node,leaf_node> retval;
	std::vector<std::pair<vector<char>,std::string> > tmpl;
	int leftsize=0;
	int elemsleftnode=0;
	std::pair<int, std::string> rootelems;
	int currsize=this->l.size();
	retval.second.next=leftblock;
	leftsize+=5; //1 char for the head, 1 int for the next

	//for(elemsleftnode;elemsleftnode < this->l.size();elemsleftnode++)
	for(;elemsleftnode < currsize; elemsleftnode++)
	{
		if(leftsize>maxsize/2)
			break;
		leftsize += 8;
		leftsize += this->l[elemsleftnode].first.size();
		leftsize += this->l[elemsleftnode].second.size();
		retval.second.l.push_back(this->l[elemsleftnode]);
	}
	rootelems.second=this->l[elemsleftnode-1].second;
	for(;elemsleftnode < (int)this->l.size();elemsleftnode)
	{
		tmpl.push_back(this->l[elemsleftnode++]);
	}

	rootelems.first=rightblock;
	
	retval.first.prev=leftblock;

	retval.second.next=rightblock;
	retval.first.l.push_back(rootelems);
	//this->next=rightblock;

	this->l=tmpl;

	return retval;
}

int leaf_node::add(std::pair<vector<char>,std::string> newelem, int maxsize)
{
	for(int i=0;i<(int)this->l.size();i++)
	{
		//if this happens, then this element already exists. this should not happen
		if(newelem.second==this->l[i].second)
			return -1;
	}
	//there is nothing with this key in, insert in the back and sort
	this->l.push_back(newelem);
	sort(this->l.begin(), this->l.end(), leaf_node::compare);
	//if the on-disk size is larger than the max size of the node, then return 1 as this is an overflow
	if(this->getsize()>maxsize)
		return 1;
	//the best of cases
	return 0;
}

int leaf_node::modify(std::pair<vector<char>,std::string> newelem, int maxsize)
{
	int modified=0;
	for(int i=0;i<(int)this->l.size();i++)
	{
		//if this happens, then this element already exists. we modify
		if(newelem.second==this->l[i].second)
		{
			this->l[i].first=newelem.first;
			modified = 1;
		}
	}
	//we modified the element and we overflowed
	if(this->getsize()>maxsize && modified==1)
		return 1;
	//we modified the element but didnt overflow
	if(modified==1)
		return 0;
	//we screwed it and did not modify anything
	return -1;
}

//returns 0 if the node is not unbalanced after delete
//returns 1 if the node is unbalanced after delete
//return -1 if what you want to delete is not even in the node
int leaf_node::del(string elem, int maxsize)
{
	int erased=0;
	std::vector<std::pair<vector<char>,std::string> >::iterator it;
	for(it = this->l.begin(); it != this->l.end(); it++)
	{
		if(it->second==elem)
		{
			erased = 1;
			this->l.erase(it);
			break;
		}
	}
	if(erased == 0)
		return -1;
	if(this->getsize() < maxsize/2)
		return 1;
	return 0;
}

std::pair<leaf_node,std::pair<int,std::string> > leaf_node::split(int maxsize, int rightblock)
{
	//the tree estucture relies on the fact that the next node remains unmutable when it splits
	//otherwise getnext() fails misserably when it requires the next ordered element
	leaf_node lretval;
	std::pair<int,std::string> iretval;
	std::pair<leaf_node,std::pair<int,std::string> > retval;
	std::vector<std::pair<vector<char>,std::string> > loldleaf;
	std::vector<std::pair<vector<char>,std::string> > lnewleaf;
	int elemsleftnode=0;
	int leftsize=0;
	int currsize=this->getsize();
	
	
	lretval.next=this->next;
	this->next=rightblock;
	iretval.first=rightblock;

	leftsize+=5; //one char for the header

	for(;elemsleftnode < currsize; elemsleftnode++)
	{
		if(leftsize>maxsize/2)
			break;
		leftsize += 8;
		leftsize += this->l[elemsleftnode].first.size();
		leftsize += this->l[elemsleftnode].second.size();
		loldleaf.push_back(this->l[elemsleftnode]);
	}
	iretval.second=this->l[elemsleftnode-1].second;
	for(;elemsleftnode < (int)this->l.size();elemsleftnode)
	{
		lnewleaf.push_back(this->l[elemsleftnode++]);
	}

	this->l=loldleaf;
	lretval.l=lnewleaf;
	retval.first = lretval;
	retval.second = iretval;
	return retval;
}
