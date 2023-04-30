// K5bin5.cpp 
//


#include "stdafx.h"
#include "Aufgabe_5_Trees.h"
int CBNode::GLO_Node_count=0;

/*
** logic optimization 
*/

//---------------------------------------------------------------
CBNode * CBTree::bt_copy_t( CBNode * &n,CBNode * &nc)
{
	CBNode *tmp;
	tmp = NULL;
	if(n){
		tmp = new CBNode(nc,NULL,NULL,n->value,n->vname);
		tmp->left  = bt_copy_t(n->left,tmp);
		tmp->right = bt_copy_t(n->right,tmp);
	}
	return tmp;
}

//---------------------------------------------------------------
void CBTree::bt_setvar(string vname)
{
	vars.push_back(vname);
}
//---------------------------------------------------------------
void CBTree::ev_collectnode( CBNode *n, string &seaname,vector<CBNode *> &vnodes)
{
    if( n){
		if(n->vname==seaname)
			vnodes.push_back(n);
        ev_collectnode( n->left,seaname,vnodes);
        ev_collectnode( n->right,seaname,vnodes);
    }
}
//---------------------------------------------------------------
void CBTree::bt_prvar(vector<string> pvars)
{
	printf("VVV Variables\n");
	for(int ii=0; ii<(int)pvars.size(); ii++){
		printf("    V[%d]= %s\n",ii,pvars[ii].c_str());
	}
}

//---------------------------------------------------------------
void CBTree::sweep_var(string &vn)
{
	string pat;
	int cardn;
	string sig;
	vector<string> cvars;
	cvars = vars;
	for(int ii=1; ii<(int)vars.size(); ii++){
		ev_exchvar(vroot,vars[ii-1],vars[ii]);
		swap(vars[ii],vars[ii-1]);
		cardn = red_lr(vroot,vars.size(),sig);

		if(mincardn>cardn){
			printf("        #######Improvement found and saved\n");
			printf("        Node Cardinality old: %d,Node Cardinality new: %d\n",mincardn,cardn);
			minvars = vars;
			rel_tree(minroot);
			minroot = bt_copy_t(vroot,minroot);
			mincardn = cardn;
		}
	}
}
void CBTree::sweep_allvar(string &vn)
{
	string pat;
	string sig;
	printf("Initial Reduce ...\n");
	mincardn = red_lr(vroot,vars.size(),sig);
	minvars = vars;
	minroot = bt_copy_t(vroot,minroot);
	tr_inorderpat(vroot,pat);

	for(int ii=0; ii<(int)vars.size(); ii++){
		printf("----Sweep %s-----------------------------\n",
			vars[0].c_str());
		sweep_var(vars[0]);
	}
}

//---------------------------------------------------------------
void swapn(CBNode * &lson,CBNode * &rson)
{
	CBNode *tmp;
	tmp = lson;
	lson = rson;
	rson  = tmp;
}
void swaps(string &lson,string &rson)
{
	string tmp;
	tmp = lson;
	lson = rson;
	rson  = tmp;
}
void CBTree::ev_exchvar(CBNode *n, string &vtname, string &vfname)
{
	enum tystate {CNOCHANGE, CLEFT, CRIGHT, CMIDDLE};
	vector<CBNode *> vnodes;
	CBNode *lson;
	CBNode *rson;
	CBNode *tmp;
	printf("        Swap %s<->%s\n",vfname.c_str(),vtname.c_str());
	tystate state=CNOCHANGE;
	ev_collectnode(n,vtname,vnodes);
	for(int ii=0; ii<(int)vnodes.size(); ii++){

		printf("        #Node %d. %s ",ii,vnodes[ii]->vname.c_str());
		state=CNOCHANGE; tmp=NULL;
		lson=vnodes[ii]->left; rson=vnodes[ii]->right;
		if(lson == NULL && rson != NULL)
			if(rson->vname==vfname)state = CLEFT;
		if(rson == NULL && lson != NULL)
			if(lson->vname==vfname)state = CRIGHT;
		if(lson!=NULL && rson!=NULL){
			if(rson->vname==vfname && lson->vname==vfname)state = CMIDDLE;
			if(rson->vname==vfname && lson->vname!=vfname)state = CLEFT;
			if(rson->vname!=vfname && lson->vname==vfname)state = CRIGHT;
		}
		if(state==CLEFT){
			tmp = bt_copy_t(lson,tmp);
			vnodes[ii]->left = new CBNode(vnodes[ii],lson,tmp,vnodes[ii]->value,vfname);
			if(lson!=NULL)tmp->dad=lson->dad=vnodes[ii]->left;
		}else if(state==CRIGHT){
			tmp = bt_copy_t(rson,tmp);
			vnodes[ii]->right = new CBNode(vnodes[ii],tmp,rson,vnodes[ii]->value,vfname);
			if(rson!=NULL)tmp->dad=rson->dad=vnodes[ii]->right;
		}
		if(state==CMIDDLE || state==CLEFT || state==CRIGHT ){
			lson=vnodes[ii]->left;
			rson=vnodes[ii]->right;
			swapn(rson->left,lson->right);
			if(rson->left!=NULL)rson->left->dad=rson;
			if(lson->right!=NULL)lson->right->dad=lson;
			swaps(lson->vname,vnodes[ii]->vname);
			rson->vname = lson->vname;
		}else printf(" NOCHANGE");
		printf("\n");
	}
}

//---------------------------------------------------------------
void CBTree::bt_insert_node(CBNode * pdad,CBNode * &root, int depth, string &key, int val)
{
	if(root==NULL){
		root = new CBNode(pdad);
		if(depth<(int)vars.size())
			root->vname=vars[depth];
	}
	if(depth<(int)key.size()){
		if(key[depth]=='0'){
			bt_insert_node(root,root->left,depth+1,key,val);
		}else{
			bt_insert_node(root,root->right,depth+1,key,val);
		}
	}else{
		root->value=val;
	}

}
//---------------------------------------------------------------

void CBTree::tr_inorderpat( CBNode *n, string &pat)
{
	char buf[256]="-";
    if( n){
		pat += '1';
        tr_inorderpat( n->right,pat);
		pat = pat.substr(0,pat.size()-1);
		for(int ii=0;ii<(int)pat.size(); ii++)printf("         ");
		printf(".........");
		if(n->dad!=NULL){
			sprintf(buf,"%s%d ",n->dad->vname.c_str(),n->dad->ID);
		}
		printf("(%4s-(%s%d)),[%4s,%2d]\n",
			n->vname.c_str(),buf,n->ID,pat.c_str(),n->value);
		pat += '0';
        tr_inorderpat( n->left,pat);
		pat = pat.substr(0,pat.size()-1);
    }
	fflush(NULL);
}
//---------------------------------------------------------------
void CBTree::rel_tree( CBNode * &n)
{
    if( n){
		rel_tree( n->left);
		rel_tree( n->right);
		delete n;
		n = NULL;
    }
}
//---------------------------------------------------------------
bool CBTree::isleaf(CBNode *n)
{
	return (n->left == NULL && n->right == NULL);
}
//---------------------------------------------------------------
void CBTree::reda_lr(CBNode *n)
{
	printf("        Reducing Node %s\n",n->vname.c_str());
	if(n->dad==NULL){//root will be removed
		vroot=n->left;
	}else{//internal node
		if(n->dad->left == n)
			n->dad->left = n->left;
		else
			n->dad->right = n->left;
	}
	if(n->left!=NULL)n->left->dad = n->dad;
	n->left = NULL;
	rel_tree(n);
}
//---------------------------------------------------------------
int CBTree::red_lr( CBNode *n,int depth,string &sig)
{
	int rednum=0;
	string lsig="";
	string rsig="";
	string ssig="";
	sig = "";
    if( n){
		rednum=1;	//counts the actual node
		if(!isleaf(n)){//left or right son or both notequal NULLs 
			//build signatur from nodes of lower levels
			rednum += red_lr( n->left,depth-1,lsig);
			rednum += red_lr( n->right,depth-1,rsig);
			ssig = lsig;
			if(n->left!=NULL)lsig += n->left->vname;
			if(n->right!=NULL)rsig += n->right->vname;
			sig  = lsig + "0";sig += rsig + "1";
			if(lsig==rsig){
				reda_lr( n);sig=ssig;rednum--;//node removed
			}
		}else{
			if(n->vname!=""){//zero is represented by empty subtrees
				reda_lr(n);sig="0";rednum--;
			}else{
				if(n->value==1)	sig = "1";
				else			sig = "0";
			}
		}
    }
	return rednum;
}
//---------------------------------------------------------------

void main()
{
	printf("Starting logic minimization...\n");
	CBTree btree;
	string pat;

	//define variables
	btree.bt_setvar(string("a"));
	btree.bt_setvar(string("b"));
	btree.bt_setvar(string("c"));
	btree.bt_setvar(string("d"));

	//define logical function
	btree.bt_insert_node(NULL,btree.vroot,0,string("0101"),1);
	btree.bt_insert_node(NULL,btree.vroot,0,string("0111"),1);
	btree.bt_insert_node(NULL,btree.vroot,0,string("0110"),1);
	btree.bt_insert_node(NULL,btree.vroot,0,string("0010"),1);
	btree.bt_insert_node(NULL,btree.vroot,0,string("1101"),1);
	btree.bt_insert_node(NULL,btree.vroot,0,string("1001"),1);

	//get the initial tree as first solution
	btree.iroot = btree.bt_copy_t(btree.vroot,btree.iroot);
	btree.ivars = btree.vars;

	//get initial tree
	printf("Initial Tree...\n");
	btree.tr_inorderpat(btree.vroot,pat);
    printf( "\n");

	//Stifting and reduction
	printf("Sweep all variables ...\n");
	btree.sweep_allvar(string("a"));
    printf( "\n");

	//get the best solution
	printf("Best solution...\n");
	printf("Number of Nodes %d\n\n",btree.mincardn);
	btree.tr_inorderpat(btree.minroot,pat);
    printf( "\n");
	char c; cin>>c;

}
