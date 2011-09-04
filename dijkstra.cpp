struct edge
{
	int to,weight;
	
	edge()
	{
	}
	
	edge(int a,int b):to(a),weight(b)
	{
	}
};

struct state
{
	int node,distance;
	
	state()
	{
	}
	
	state(int a,int b):node(a),distance(b)
	{
	}
	
};

bool operator<(const state &x,const state &y)
{
	return x.distance>y.distance;	// top of priority_queue is maximum
}

int dijkstra(vector<edge> [],int,int,int);

int dijkstra(vector<edge> graph[],int n,int source,int destination)
{
	int dist[n+2]; // distance from start vertex to each vertex
	memset(dist,0x3f,sizeof(dist)); 
	
	priority_queue<state> Q; 
	
	dist[source]=0;
	Q.push(state(source,0));
	
	while(Q.empty()==false)
	{	
		state now=Q.top();
		Q.pop();
		int curr_dist=now.distance;
		int curr_node=now.node;
		
		if(curr_node==destination)
			return curr_dist;
			
		if(curr_dist>dist[curr_node])
			continue;
			
		int i,tmp,next_node;
		for(i=0;i<graph[curr_node].size();++i)
		{
			tmp=curr_dist+graph[curr_node][i].weight;
			next_node=graph[curr_node][i].to;
			if(tmp<dist[next_node])
			{
				dist[next_node]=tmp;
				Q.push(state(next_node,tmp));
			}
		}
	}
	
	return -1;//no connection exists
}
