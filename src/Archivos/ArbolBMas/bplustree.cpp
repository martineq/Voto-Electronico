#include "bplustree.h"


bplustree::bplustree(void)
{
}


bplustree::~bplustree(void){
	delete (this->f);
}

int bplustree::del(string key)
{
	//this implementation ignores the underflow
	int bn=0;
	int status=0;
	vector<char> tmp;
	tmp=this->search(key);

	if(this->q.size()==0)
		return 1; // this should not happen
	bn=this->q.back();
	this->q.pop_back();
	status=this->n.del(key,this->bs);
	this->f->setblock(this->n.serialize(),bn);
	return 0;
}

std::pair<vector<char>,std::string> bplustree::getnext()
{
	leaf_node tmp;
	std::pair<std::pair<vector<char>,std::string>,int> rretval=this->n.nextelem();
	std::pair<vector<char>,std::string> empty;
	vector<char> block;
	
	//this is to take into account that there might be empty blocks with a next pointer
	while(rretval.first.second.size() == 0 && rretval.second !=0)
	{
		block = this->f->getblock(rretval.second);
		tmp.deserialize(block);
		this->n=tmp;
		rretval=this->n.nextelem();
	}

	//i was not in the last element of the node
	if(rretval.second==0)
		return rretval.first;
	//this was the last element of the tree
	if(rretval.second==-1)
	{
		this->clear();
		return rretval.first;
	}
	//this was the last element of the node, we need to get a new one
	block = this->f->getblock(rretval.second);
	tmp.deserialize(block);
	this->n=tmp;
	return rretval.first;

}

void bplustree::newtree(string p, int bs)
{
//	int rootblock=this->getrootblock();
	leaf_node root;
	this->f = new ffile(p,bs);
	this->bs = bs; //this will be used as max size of the tree nodes
//	cout << "root: "<<rootblock <<endl;
	this->bs = this->f->newblock();
//	cout << "root: "<<rootblock <<endl;
//	cout << "size: "<<bs <<endl;
	this->f->setblock(root.serialize(),this->getrootblock());
}


void bplustree::opentree(string p, int bs){
	this->f = new ffile(p,bs);
	this->bs = bs;
}

void bplustree::initialize()
{
	leaf_node l;
	leaf_node r;
	inner_node i;
	vector<char> data;
	data.push_back(1);
}

vector<char> bplustree::search(string key)
{
	leaf_node l;
	inner_node i;
	inner_node empty;
	vector<char> block;
	std::vector<char> retval;
	int bn=0;
	char blocktype=0;

	q.clear();
	bn=this->getrootblock();

	block=this->f->getblock(bn);

	this->q.push_back(bn);
	while(i.peek(block)=='I')
	{
		i=empty; //if we dont do this, we'll add in the previous i.
		i.deserialize(block);
		bn=i.search(key);
		block=this->f->getblock(bn);
		q.push_back(bn);
	}
	//up to this point, I have a block that is not an inner node
	//i also have a queue with the path to my node
	l.deserialize(block);
	retval=l.search(key);
	//i save the last search to a temporary location
	this->n=l;
	return retval;
}

int bplustree::add(string key, vector<char> data){

	if(key.size() + data.size() > this->bs-12) //just to make sure i am not inserting something larger than a block
		return -1;
	vector<char> tmp;
	int bn=0;
	leaf_node target;
	int status=0;
	std::pair<vector<char>,std::string> newleafelem;
	vector<char> block;
	std::pair<int, std::string> newinnerelem;
	inner_node tmpinner;
	leaf_node tmpleaf;
	int left=0;
	int right=0;
	int parent=0;
	char blocktype='L';
	std::pair<inner_node,leaf_node> pairifleaf;
	std::pair<inner_node, inner_node> pairifnode;

	if(key.size()==0)
		return 1;

	tmp=this->search(key);
	//so, up to this point, i have a queue with the path to my block
	//and a copy of the block in which i searched stuff
	
	//if the data was already there, do not add a thing
	if (tmp.size()!=0)
		return -1;
	target=this->n;

	bn=this->q.back();
	this->q.pop_back();

	newleafelem.first=data;
	newleafelem.second=key;

	status=this->n.add(newleafelem,this->bs);
	if(status == -1)
		return status; //this should never happen
	if(status == 0)
	{
		//there was no overflow, so we just write and return
		this->f->setblock(this->n.serialize(),bn);
		//we need to get rid of the last search crap because after an insert, 
		//it might not be consistent
		this->clear();
		return 0;
	}
	//case where you have an overflow in a leaf
	//we have two cases here, either this is a root, or it isnt
	tmpleaf=this->n;
	//the first overflow we can have must necessarily come from a leaf node, therefore, in tmpleaf
	//we have either a regular leaf or the root
	while(status==1)
	{
		if(bn==this->getrootblock() && blocktype == 'L')
		{
			//we inserted a block in the root which was full and overflowed
			left = this->f->newblock();
			right = this->f->newblock();
			pairifleaf=tmpleaf.split_root(this->bs,left,right);
			this->f->setblock(pairifleaf.first.serialize(),this->getrootblock());
			this->f->setblock(tmpleaf.serialize(),left);
			this->f->setblock(pairifleaf.second.serialize(),right);
			//there is nothing else to do, clean up and leave
			this->clear();
			return 0;
		}
		if(bn==this->getrootblock() && blocktype == 'I')
		{
			//we inserted a block and it split till the root
			left = this->f->newblock();
			right = this->f->newblock();
			pairifnode = tmpinner.split_root(this->bs,left,right);
			this->f->setblock(tmpinner.serialize(),this->getrootblock());
			this->f->setblock(pairifnode.first.serialize(),left);
			this->f->setblock(pairifnode.second.serialize(),right);
			//there is nothing else to split, clean up and leave
			this->clear();
			return 0;
		}
		//missing the breaking of the leaf and inner node when its not the root

		if(blocktype == 'I')
		{
			//in tmpinner we have a copy of the current block
			//in bn we have the current block number
			std::pair<inner_node,std::pair<int,std::string> > splitrst;
			vector<char> strg; //storage to get father
			inner_node ftr;
			int rlt;
			//we need to get a new block
			right = this->f->newblock();
			splitrst = tmpinner.split(this->bs,right);
			this->f->setblock(tmpinner.serialize(),bn); //write my data
			this->f->setblock(splitrst.first.serialize(),right); //write my data
			bn=this->q.back(); //get node in which to write stuff
			strg=this->f->getblock(bn); //get block
			ftr.deserialize(strg); //get node
			rlt=ftr.add(splitrst.second,this->bs);
			if(rlt==0)
			{
				status=0;
				this->f->setblock(ftr.serialize(),bn);

			}
			if(rlt==-1)
			{
				cout << "this should not have happened!!" << endl;
				exit(1);
			}
			if(rlt==1)
			{
				//this means we have to recurse because the parent overflowed
				tmpinner=ftr;
				status=1;
			}
		}

		if(blocktype == 'L')
		{
			//a leaf that is not a node
			std::pair<leaf_node,std::pair<int,std::string> > splitres; //storage to savage my own crap
			vector<char> stg; //storage to get father
			inner_node father;
			int reslt; //storage for the addition to the father

			right = this->f->newblock(); //i will definitely need a new block
			splitres=tmpleaf.split(this->bs,right);
			this->f->setblock(tmpleaf.serialize(),bn); //write my data
			this->f->setblock(splitres.first.serialize(),right); //write my data
			bn=this->q.back(); //get node in which to write stuff
			stg=this->f->getblock(bn); //get block
			father.deserialize(stg); //get node
			reslt=father.add(splitres.second,this->bs);
			if(reslt==0)
			{
				status=0;
				this->f->setblock(father.serialize(),bn);

			}
			if(reslt==-1)
			{
				cout << "this should not have happened!!" << endl;
				exit(1);
			}
			if(reslt==1)
			{
				//this means we have to recurse because the parent overflowed
				tmpinner=father;
				blocktype = 'I';
				status=1;
			}
		}

		/*bn=this->q.back();
		q.pop_back();
		block=this->f->getblock(bn);
		status=tmpinner.peek(block);
		if(blocktype == 'I')
			tmpinner.deserialize(block);
		if(blocktype == 'L')
			tmpleaf->deserialize(block);
			*/
	}
	return 0;
}


int bplustree::modify(string key, vector<char> data)
{
	if(key.size() + data.size() > this->bs-12) //just to make sure i am not inserting something larger than a block
		return -1;
	vector<char> tmp;
	int bn=0;
	leaf_node target;
	int status=0;
	std::pair<vector<char>,std::string> newleafelem;
	vector<char> block;
	std::pair<int, std::string> newinnerelem;
	inner_node tmpinner;
	leaf_node tmpleaf;
	int left=0;
	int right=0;
	int parent=0;
	char blocktype='L';
	std::pair<inner_node,leaf_node> pairifleaf;
	std::pair<inner_node, inner_node> pairifnode;

	if(key.size()==0)
		return 1;

	tmp=this->search(key);
	//so, up to this point, i have a queue with the path to my block
	//and a copy of the block in which i searched stuff
	
	//if the data was already there, do not add a thing
	if (tmp.size()==0)
		return -1;
	target=this->n;

	bn=this->q.back();
	this->q.pop_back();

	newleafelem.first=data;
	newleafelem.second=key;

	status=this->n.modify(newleafelem,this->bs);
	if(status == -1)
		return status; //this should never happen
	if(status == 0)
	{
		//there was no overflow, so we just write and return
		this->f->setblock(this->n.serialize(),bn);
		//we need to get rid of the last search crap because after an insert, 
		//it might not be consistent
		this->clear();
		return 0;
	}
	//case where you have an overflow in a leaf
	//we have two cases here, either this is a root, or it isnt
	tmpleaf=this->n;
	//the first overflow we can have must necessarily come from a leaf node, therefore, in tmpleaf
	//we have either a regular leaf or the root
	while(status==1)
	{
		if(bn==this->getrootblock() && blocktype == 'L')
		{
			//we inserted a block in the root which was full and overflowed
			left = this->f->newblock();
			right = this->f->newblock();
			pairifleaf=tmpleaf.split_root(this->bs,left,right);
			this->f->setblock(pairifleaf.first.serialize(),this->getrootblock());
			this->f->setblock(tmpleaf.serialize(),left);
			this->f->setblock(pairifleaf.second.serialize(),right);
			//there is nothing else to do, clean up and leave
			this->clear();
			return 0;
		}
		if(bn==this->getrootblock() && blocktype == 'I')
		{
			//we inserted a block and it split till the root
			left = this->f->newblock();
			right = this->f->newblock();
			pairifnode = tmpinner.split_root(this->bs,left,right);
			this->f->setblock(tmpinner.serialize(),this->getrootblock());
			this->f->setblock(pairifnode.first.serialize(),left);
			this->f->setblock(pairifnode.second.serialize(),right);
			//there is nothing else to split, clean up and leave
			this->clear();
			return 0;
		}
		//missing the breaking of the leaf and inner node when its not the root

		if(blocktype == 'I')
		{
			//in tmpinner we have a copy of the current block
			//in bn we have the current block number
			std::pair<inner_node,std::pair<int,std::string> > splitrst;
			vector<char> strg; //storage to get father
			inner_node ftr;
			int rlt;
			//we need to get a new block
			right = this->f->newblock();
			splitrst = tmpinner.split(this->bs,right);
			this->f->setblock(tmpinner.serialize(),bn); //write my data
			this->f->setblock(splitrst.first.serialize(),right); //write my data
			bn=this->q.back(); //get node in which to write stuff
			strg=this->f->getblock(bn); //get block
			ftr.deserialize(strg); //get node
			rlt=ftr.add(splitrst.second,this->bs);
			if(rlt==0)
			{
				status=0;
				this->f->setblock(ftr.serialize(),bn);

			}
			if(rlt==-1)
			{
				cout << "this should not have happened!!" << endl;
				exit(1);
			}
			if(rlt==1)
			{
				//this means we have to recurse because the parent overflowed
				tmpinner=ftr;
				status=1;
			}
		}

		if(blocktype == 'L')
		{
			//a leaf that is not a node
			std::pair<leaf_node,std::pair<int,std::string> > splitres; //storage to savage my own crap
			vector<char> stg; //storage to get father
			inner_node father;
			int reslt; //storage for the addition to the father

			right = this->f->newblock(); //i will definitely need a new block
			splitres=tmpleaf.split(this->bs,right);
			this->f->setblock(tmpleaf.serialize(),bn); //write my data
			this->f->setblock(splitres.first.serialize(),right); //write my data
			bn=this->q.back(); //get node in which to write stuff
			stg=this->f->getblock(bn); //get block
			father.deserialize(stg); //get node
			reslt=father.add(splitres.second,this->bs);
			if(reslt==0)
			{
				status=0;
				this->f->setblock(father.serialize(),bn);

			}
			if(reslt==-1)
			{
				cout << "this should not have happened!!" << endl;
				exit(1);
			}
			if(reslt==1)
			{
				//this means we have to recurse because the parent overflowed
				tmpinner=father;
				blocktype = 'I';
				status=1;
			}
		}

		/*bn=this->q.back();
		q.pop_back();
		block=this->f->getblock(bn);
		status=tmpinner.peek(block);
		if(blocktype == 'I')
			tmpinner.deserialize(block);
		if(blocktype == 'L')
			tmpleaf->deserialize(block);
			*/
	}
	return 0;
}
