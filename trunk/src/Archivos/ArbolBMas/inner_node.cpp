#include "inner_node.h"
inner_node::inner_node(){ this->prev=0; return; };
inner_node::~inner_node(){ return; };

inner_node & inner_node::operator=(const inner_node &rhs)
{
	if (this != &rhs) {
		this->l = rhs.l;
		this->prev = rhs.prev;
    }

    return *this;
}

int inner_node::compare(std::pair<int, std::string> l, std::pair<int, std::string> r)
{
    return l.second < r.second;
}

int inner_node::search(string str)
{
 /*initialization to test
 vector<char> data;
 
 std::pair<int, std::string> first(1,"abismo");
 std::pair<int, std::string> second(2, "boludo");
 std::pair<int, std::string> third(3, "cmo");
 std::pair<int, std::string> fourth(4, "deloitte");
 
 this->l.push_back(first);
 this->l.push_back(second);
 this->l.push_back(third);
 this->l.push_back(fourth);
 this->prev = 5;
 
 cout << "counter:" << this->l.size() << endl;
 
 sort(this->l.begin(), this->l.end(), inner_node::compare);
 
 end of initialization*/
 
 //cout << "comparing " << this->l[0].second << " with " << str << endl;
 if(this->l.size()==0)
	 return 0;
 if(this->l[0].second > str)
   return this->prev;
 if(this->l[0].second == str)
   return this->prev;
   
 for(int i=1; i<this->l.size(); i++)
 {
  //cout << "counter:" << i << endl;
  //cout << "comparing " << this->l[i].second << " with " << str << endl;
  if(this->l[i].second > str)
    return this->l[i-1].first;
  if(this->l[i].second == str)
    return this->l[i-1].first;
 }
 return l[l.size()-1].first;
}

std::vector<char> inner_node::serialize()
{
 /*initialization to test
 vector<char> data;
 
 std::pair<int, std::string> first(1,"test");
 std::pair<int, std::string> second(2, "a");
 std::pair<int, std::string> third(3, "bmo");
 std::pair<int, std::string> fourth(4, "deloitte");
 
 this->l.push_back(first);
 this->l.push_back(second);
 this->l.push_back(third);
 this->l.push_back(fourth);
 this->prev = 5;
 
 
 end of initialization*/
 
 vector<char> retval;
 vector<char> *mem = &retval;
 std::vector<std::pair<int, std::string> >::iterator it;
 char *tmp;
 int size=0;
 //add header
 mem->push_back('I');
 
 //add the pointer to the block containing stuff that is smaller than the smallest key
 tmp = (char*)&(this->prev);
 for(int i=0;i<4;i++)
 {
  mem->push_back(tmp[i]);
 }
 
 //add size of the list
 size = this->l.size();
 //cout << size << endl;
 
 tmp = (char*)&size;
 for(int i=0;i<4;i++)
 {
  mem->push_back(tmp[i]);
 }
 //add all the elements of the list
 for(it = this->l.begin(); it != this->l.end(); it++)
 {
  //add block numbers
  size=it->first;
  tmp=(char*)&size;
  for(int i=0;i<4;i++)
  {
   mem->push_back(tmp[i]);
  }
  //add the size of the key
  size=strlen(it->second.c_str());
  tmp=(char*)&size;
  for(int i=0;i<4;i++)
  {
   mem->push_back(tmp[i]);
  }
  
  tmp=(char*)it->second.c_str();
  for(int i=0;i<strlen(tmp);i++)
  {
   mem->push_back(tmp[i]);
  }
 }
 return retval;
}

char inner_node::peek(vector<char> node)
{
     return  node[0];
}

void inner_node::deserialize(std::vector<char> s)
{
 std::vector<char> *v=&s;
 int i=0;
 int size=0;
 int strsize=0;
 int blocknum=0;
 char *str;
 char *tmp;
 std::pair<int, std::string> elem;
 //remove header
 char h = (*v)[i++];
 tmp=(char*)&(this->prev);
 //get prev item
 for(int j=0;j<4;)
         tmp[j++]=(*v)[i++];
 //get size of the structure
 tmp=(char*)&size;
 for(int j=0;j<4;)
         tmp[j++]=(*v)[i++];
 //get all the elements of the block        
 for (int l=0;l<size;l++)
 {
     //get blocknumber
     tmp=(char*)&blocknum;
     for(int j=0;j<4;)
         tmp[j++]=(*v)[i++];
     //get size of string
     tmp=(char*)&strsize;
     for(int j=0;j<4;)
         tmp[j++]=(*v)[i++];
     //get string
     str=(char*)malloc((strsize+1)*sizeof(char));
     for(int k=0;k<strsize;)
             str[k++]=(*v)[i++];
     str[strsize]='\0';
     
     elem.first = blocknum;
     elem.second = string(str);
     free(str);
     this->l.push_back(elem);
 }
}

void inner_node::initialization()
{
 std::pair<int, std::string> first(78,"test");
 std::pair<int, std::string> second(2, "a");
 std::pair<int, std::string> third(3, "bmo");
 std::pair<int, std::string> fourth(13, "deloitte");
 std::pair<int, std::string> fifth(35, "prueba");
 
 this->l.push_back(first);
 this->l.push_back(second);
 this->l.push_back(third);
 this->l.push_back(fourth);
 this->l.push_back(fifth);
 this->prev = 5;

 sort(this->l.begin(), this->l.end(), inner_node::compare);
}

int inner_node::getsize()
{

 vector<char> tmp;
 tmp=this->serialize();
 int retval=tmp.size();
 return retval;
}

//after this is called, the current inner node is the new root, the first inner node of the pair
//the left son and the second is the right son, leftlock and rightblocks are the pointers where
//the left son and right son will be stored on disk
std::pair<inner_node,inner_node> inner_node::split_root(int maxsize, int leftblock, int rightblock)
{
 inner_node right;
 inner_node left;
 std::pair<inner_node,inner_node> retval;
 int curleftsize=0;
 int i=0;
 string currentstr;
 left.prev=this->prev;
 std::pair<int, std::string> rootelems;
 
 curleftsize+=9; //the left hand thing has to be at least 9 bytes on disk
 while(curleftsize < maxsize/2)
 {
	 if(i==this->l.size())
		 break; //this should not happen as you should never call this function in this case
	 curleftsize+=8; //one int for the size of the string, one int for the pointer
	 curleftsize+=this->l[i].second.size();
	 left.l.push_back(this->l[i++]);
 }

 //if(i!=this->l.size())
 //	left.l.push_back(this->l[i++]);
 //I add one new element so that this left son is not underflowed

 left.prev=this->prev;
 currentstr = this->l[i].second;
 right.prev = this->l[i++].first;

 while(i < l.size())
	 right.l.push_back(this->l[i++]);
 //we're done creating the root sons, we have to create a new root

 this->prev = leftblock;
 rootelems.first=rightblock;
 rootelems.second=currentstr;

 this->l.clear();
 this->l.push_back(rootelems);

 retval.first = left;
 retval.second = right;
 return retval;
}



//returns 1 if there is an overflow, 0 if there was no problem, -1 if the item was already there
int inner_node::add(std::pair<int, std::string> newelem, int maxsize)
{
	for(int i=0;i<this->l.size();i++)
	{
		//if this happens, then this element already exists. this should not happen
		if(newelem.second==this->l[i].second)
			return -1;
	}
	//there is nothing with this key in, insert in the back and sort
	this->l.push_back(newelem);
	sort(this->l.begin(), this->l.end(), inner_node::compare);
	//if the on-disk size is larger than the max size of the node, then return 1 as this is an overflow
	if(this->getsize()>maxsize)
		return 1;
	//the best of cases
	return 0;
}

//returns 0 if the node is not unbalanced after delete
//returns 1 if the node is unbalanced after delete
//return -1 if what you want to delete is not even in the node
int inner_node::del(string elem, int maxsize)
{
	int erased=0;
	std::vector<std::pair<int, std::string> >::iterator it;
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

//the old node will have the first half, the new node, the second half and the pair will have the pointer and string
std::pair<inner_node,std::pair<int,std::string> > inner_node::split(int maxsize, int leftblock)
{
	inner_node lretval;
	std::pair<int,std::string> iretval;
	std::pair<inner_node,std::pair<int,std::string> > retval;
	std::vector<std::pair<int,std::string> > loldnode;
	std::vector<std::pair<int,std::string> > lnewnode;
	int elemsleftnode=0;
	int leftsize=0;
	int currsize=this->getsize();
	
	iretval.first=leftblock;

	leftsize+=9; //one char for the header

	for(;elemsleftnode < currsize; elemsleftnode++)
	{
		if(leftsize>maxsize/2)
			break;
		leftsize += 8; //the pointer and the size of the key
		leftsize += this->l[elemsleftnode].second.size();
		loldnode.push_back(this->l[elemsleftnode]);
	}
	iretval.second=this->l[elemsleftnode].second;
	lretval.prev=this->l[elemsleftnode].first;
	elemsleftnode++;
	for(;elemsleftnode < this->l.size();elemsleftnode)
	{
		lnewnode.push_back(this->l[elemsleftnode++]);
	}

	this->l=loldnode;
	lretval.l=lnewnode;
	retval.first = lretval;
	retval.second = iretval;
	return retval;
}
