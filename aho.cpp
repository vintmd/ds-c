#include <cstdio>
#include <cstring>
#include <queue>

#define MAX_CHAR_NUM 500006
#define MAX_STRING_LEN 100006
/*
 * the aho use the double array to build the machine
 */
struct Aho{
	struct state{ 
		int next[26];//if there is only a-z. also can expend to the 256 ascii 
		//cnt how many string finish in this state
		int fail,cnt;//this table's fail point to the next statetable.
	}statetable[MAX_CHAR_NUM];//how many chars are there

	int size;//count of the ac nodes

	std::queue<int> que;

	int init(){
		while(que.size()){
			que.pop();	
		}
		size = 1;	//has one root node
		for(int i=0;i<MAX_CHAR_NUM;++i){
			memset(statetable[i].next,0,sizeof(statetable[i].next));
			statetable[i].fail = 0;	
			statetable[i].cnt = 0;
		}
	}
	//insert the mode string s
	int insert(char *S){
		int now = 0;
		int len = strlen(S);
		for(int i=0;i<len;++i){
			char c = S[i];	
			if(!statetable[now].next[c-'a']){
				statetable[now].next[c-'a']	= size++;
			}
			now = statetable[now].next[c-'a'];
		}
		statetable[now].cnt++;
	}
	//build the failed point
	//each node has one char
	//the fail pointer only point to the statetable items
	int build()	{
		statetable[0].fail = -1;
		que.push(0);
		while(que.size()){
			//the u is the index of which statetable
			int u = que.front();	
			que.pop();
			for(int i = 0;i<26;i++){
				if(statetable[u].next[i]){
					if(0 == u)	statetable[statetable[u].next[i]].fail = 0;
					else{
						int v = statetable[u].fail;	
						//look for the father or ff or fff ... pointer item whether has the next[i]
						while(-1 != v){
							if(statetable[v].next[i]){
								//has the next[i]	
								statetable[statetable[u].next[i]].fail = statetable[v].next[i];
								break;
							}
							v = statetable[v].fail;
						}
						if(-1 == v){
							statetable[statetable[u].next[i]].fail = 0;	
						}
					}
					//push the next[i] into the que
					que.push(statetable[u].next[i]);
				}//end of if	
				
			}
		}//finish the build fail point
		return 0;
	}
	//get the index of statetable item from the now to the root
	//get the cnt sum of each node
	int Get(int now){
		int res = 0;
		while(now){
			res += statetable[now].cnt;	
			statetable[now].cnt = 0;
			now = statetable[now].fail;
		}	
		return res;
	}

	//the main string S
	int match(char *S){
		int len = strlen(S);
		int now = 0;
		int res = 0; //return the how many keyword are there in machine 
		//if there are two same keyword only count once so need to set zero after the count
		for(int i = 0;i < len;i++){
			char c = S[i];	
			if(statetable[now].next[c-'a']){
				now = statetable[now].next[c-'a'];	
			}else{
				int p = statetable[now].fail;	
				while(p != -1 && statetable[p].next[c-'a'] == 0) p = statetable[p].fail;
				if(-1 == p) now = 0;
				else{
					now = statetable[p].next[c-'a'] ;
				}
			}
			if(statetable[now].cnt){
				res = res + Get(now);	
			}
			 
		}
		return res;		
	}
}aho;

int T;//times
int N;//how many mode strings
char str[MAX_STRING_LEN];
int main(){
	int ret;
	scanf("%d",&T);	
	while(T--){
		scanf("%d",&N);	
		aho.init();
		for(int i=0;i<N;i++){
			scanf("%s",str);
			aho.insert(str);
		}
		aho.build();
		scanf("%s",str);
		ret = aho.match(str);
		printf("%d\n",ret);
	}
	return 0;
}
