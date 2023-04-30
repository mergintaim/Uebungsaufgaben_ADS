//File k5bin5.h
//class used for node representation
class CBNode
{
public:
	static int GLO_Node_count;
public:
    CBNode *left;
    CBNode *right;
    CBNode *dad;
	int ID;
    int value;
	string vname;
public:

	//construction
	CBNode( CBNode *dad=NULL,CBNode *left=NULL,CBNode *right=NULL,
			int value=0,string vname=""):
			dad(dad),left(left),right(right),value(value),vname(vname){
				ID=GLO_Node_count; GLO_Node_count++;
			};
};
//class used for logic optimization data
class CBTree
{
public:

	//initial tree
	CBNode *iroot;			//tree root for initial root
	vector<string> ivars;	//sequence of variables

	//working area
	CBNode *vroot;			//tree root for actual root
	vector<string> vars;	//sequence of variables

	//optimization
	CBNode *minroot;		//current minimal solution
	vector<string> minvars;	//sequence of variables
	int mincardn;

	//construction
	CBTree(){
		vroot=NULL;
		iroot=NULL;
		minroot=NULL;
		mincardn=0;
	};
	//destruction
	~CBTree(){
		rel_tree(vroot);
		rel_tree(iroot);
		rel_tree(minroot);
	};
	//traversation
	void  tr_inorderpat( CBNode *n, string &pat);

	//tree construction
	void  rel_tree( CBNode * &n);
	CBNode *  bt_copy_t( CBNode * &n,CBNode * &nc);
	void  bt_insert_node(CBNode * pdad,CBNode * &root,
		int depth, string key, int val);
	void  bt_setvar(string vname);
	void  bt_prvar(vector<string> pvars);

	//exchanging variables
	void  ev_collectnode( CBNode *n, string &seaname,vector<CBNode *> &vnodes);
	void  ev_exchvar(CBNode *n, string &vtname, string &vfname);
	void  sweep_var(string &vn);
	void  sweep_allvar(string vn);

	//reducing variables
	void  reda_lr(CBNode *n);
	int  red_lr( CBNode *n,int depth,string &sig);
	bool  isleaf(CBNode *n);

};
