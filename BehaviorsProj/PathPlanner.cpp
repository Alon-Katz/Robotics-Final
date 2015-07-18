#include "PathPlanner.h"

 class  node
    {
    public:
	 	 int n,m;
        // current position
        int xPos;
        int yPos;

        // total distance already travelled to reach the node
        int level;

        // priority=level+remaining distance estimate
        int priority;  // smaller: higher priority

    	node(int xp, int yp, int d, int p);
        int getxPos() const;
        int getyPos() const;
        int getLevel() const;
        int getPriority() const;
        const int & estimate(const int & xDest, const int & yDest) const;
        void updatePriority(const int & xDest, const int & yDest);

        // give better priority to going strait instead of diagonally
        void nextLevel(const int & i); // i: direction
    };


node::node(int xp, int yp, int d, int p)
{
	xPos=xp;
	yPos=yp;
	level=d;
	priority=p;
}

int node::getxPos() const
{
	return xPos;
}
int node::getyPos() const
{
	return yPos;
}
int node::getLevel() const
{
	return level;
}
int node::getPriority() const
{
	return priority;
}
void node::updatePriority(const int & xDest, const int & yDest)
{
	 priority=level+estimate(xDest, yDest)*10; //A*
}

// give better priority to going strait instead of diagonally
void node::nextLevel(const int & i) // i: direction
{
	 level+=(dir==8?(i%2==0?10:14):10);
}

// Estimation function for the remaining distance to the goal.
const int & node::estimate(const int & xDest, const int & yDest) const
{
	static int xd, yd, d;
	xd=xDest-xPos;
	yd=yDest-yPos;

	// Euclidian Distance
	d=static_cast<int>(sqrt(xd*xd+yd*yd));

	return(d);
}

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
  return a.node::getPriority() > b.node::getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
string PathPlanner::pathFind( int  xStart, int  yStart,
                 int  xFinish, int  yFinish, int** map)
{
    static priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static node* n0;
    static node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;

    // reset the node maps
	for(x=0;x<n;x++)
    {
        for(y=0;y<m;y++)
        {
            closed_nodes_map[x][y]=0;
            open_nodes_map[x][y]=0;
        }
    }


	delete n0;

    // create the start node and push into list of open nodes
    n0=new node(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[xStart][yStart]=n0->node::getPriority(); // mark it on the open nodes map

    // A* search
    while(!pq[pqi].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes
        n0=new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(), 
                     pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

        x=n0->getxPos(); y=n0->getyPos();

        pq[pqi].pop(); // remove the node from the open list
        open_nodes_map[x][y]=0;
        // mark it on the closed nodes map
        closed_nodes_map[x][y]=1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if(x==xFinish && y==yFinish) 
        {
            // generate the path from finish to start
            // by following the directions
            string path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[x][y];
                c='0'+(j+dir/2)%dir;
                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }

            // garbage collection
            delete n0;
            // empty the leftover nodes
            while(!pq[pqi].empty()) pq[pqi].pop();           
            return path;
        }

        // generate moves (child nodes) in all possible directions
        for(i=0;i<dir;i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || map[xdx][ydy]==1 
                || closed_nodes_map[xdx][ydy]==1))
            {
                // generate a child node
                m0=new node( xdx, ydy, n0->getLevel(), 
                             n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);

                // if it is not in the open list then add into that
                if(open_nodes_map[xdx][ydy]==0)
                {
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    pq[pqi].push(*m0);

                    delete m0;
                    // mark its parent node direction
                    dir_map[xdx][ydy]=(i+dir/2)%dir;
                }
                else if(open_nodes_map[xdx][ydy]>m0->getPriority())
                {
                    // update the priority info
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy]=(i+dir/2)%dir;

                    // replace the node
                    // by emptying one pq to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(pq[pqi].top().getxPos()==xdx && 
                           pq[pqi].top().getyPos()==ydy))
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pq[pqi].pop(); // remove the wanted node
                    
                    // empty the larger size pq to the smaller one
                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0); // add the better node instead

                    delete m0;
                }
                //else delete m0; // garbage collection
            }
        }
        delete n0; // garbage collection
    }
    return ""; // no route found
}

vector<Location> PathPlanner::getPathLocations( string  direction, int  startY, int  startX)
{
	Location locations[n*m];
	Location destPoint;
	int index;
	int sourceX = startX;
	int sourceY = startY;
	m_counter = direction.length();
	_path.resize(direction.length());

	for(index = 0; index < direction.length(); index++)
	{
		switch(direction[index])
		{
			case('0'):
			{
				destPoint.setX(sourceX + 1);
				destPoint.setY(sourceY);

				break;
			}
			case('1'):
			{
				destPoint.setX(sourceX + 1);
				destPoint.setY(sourceY + 1);
				break;
			}
			case('2'):
			{
				destPoint.setX(sourceX);
				destPoint.setY(sourceY + 1);
				break;
			}
			case('3'):
			{
				destPoint.setX(sourceX - 1);
				destPoint.setY(sourceY + 1);
				break;
			}
			case('4'):
			{
				destPoint.setX(sourceX - 1);
				destPoint.setY(sourceY);
				break;
			}
			case('5'):
			{
				destPoint.setX(sourceX - 1);
				destPoint.setY(sourceY - 1);
				break;
			}
			case('6'):
			{
				destPoint.setX(sourceX);
				destPoint.setY(sourceY - 1);
				break;
			}
			case('7'):
			{
				destPoint.setX(sourceX + 1);
				destPoint.setY(sourceY - 1);
				break;
			}
			default:
			{
				cout << endl << "default "  << direction[index] << endl;
				break;
			}
		}

		sourceX = destPoint.getX();
		sourceY = destPoint.getY();
		destPoint.setYaw(0);


		locations[index] = destPoint;
		_path[index] = destPoint;
	}

	for (int i = 0; i < direction.length(); i++)
	{
		cout << "location is : (" << locations[i].getX() << " , " << locations[i].getY() << ")  "  << direction[i]  << "  " <<  i << endl;
	}

	return _path;


}
int PathPlanner::getWaypointsSize()
{
	return m_counter;
}

PathPlanner::PathPlanner(int width, int height) : n(width), m(height)
{
		closed_nodes_map = new int *[n] ;

		for( int i = 0 ; i < n ; i++ )
			closed_nodes_map[i] = new int[m];

		open_nodes_map = new int *[n] ;

		for( int i = 0 ; i < n ; i++ )
			open_nodes_map[i] = new int[m];

		dir_map = new int *[n] ;

		for( int i = 0 ; i < n ; i++ )
			dir_map[i] = new int[m];
}

PathPlanner::~PathPlanner()
{
	for( int i = 0 ; i < n ; i++ )
		delete [] closed_nodes_map[i] ;
	delete [] closed_nodes_map ;

	for( int i = 0 ; i < n ; i++ )
		delete [] open_nodes_map[i] ;
	delete [] open_nodes_map ;

	for( int i = 0 ; i < n ; i++ )
		delete [] dir_map[i] ;
	delete [] dir_map ;
}

vector<Location> PathPlanner::getWayPoints()
{
	//return _wayPoints._wayPoints;
}
