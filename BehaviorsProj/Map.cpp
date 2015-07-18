/*
 * Map.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: Itay Eylon
 */

#include "Map.h"
#include "lodepng.h"
#include <math.h>
#include <iostream>


Map::Map(double grid_resulotion){
			m_width = 0;
			m_height = 0;
			m_grid_resulotion = grid_resulotion;
		}
Map::Map()
{

}
vector<Location> Map::InitMap(ConfigurationManager p_configData) {
	InflatingMap(p_configData.map_path, p_configData.robot_width, p_configData.map_resolution);
	createGrids(p_configData.grid_resolution, p_configData.map_resolution, p_configData.map_path);
	vector<Location> wayPoints = getRoute(Location(p_configData.start_x, p_configData.start_y), Location(p_configData.target_x, p_configData.target_y));
	vector<unsigned char> test = colorizeWaypoints(wayPoints);
	lodepng::encode("test.png", test, m_width, m_height);

	return wayPoints;
}

vector<unsigned char> Map::colorizeWaypoints(vector<Location> p_wayPoints)
{
	vector<unsigned char> newImage; //the raw pixels

	m_vec.clear();
	lodepng::decode(m_vec, m_width, m_height, "roboticLabMap.png");

	// init map

	for (unsigned int i = 0; i < this->m_vec.size(); i++)
	{
		newImage.push_back(this->m_vec[i]);
	}

	Location curr = p_wayPoints[0];
	unsigned cell;
	for (unsigned i = 0; i<m_wayPointsSize; i++)
	{
		curr = p_wayPoints[i];
		cell = ((curr.getY() * 4)   * m_width * 4 + (curr.getX() * 4) * 4);
		newImage[cell + 0] = 255;
		newImage[cell + 1] = 0;
		newImage[cell + 2] = 0;
		newImage[cell + 3] = 255;
	}

	return newImage;
}

void Map::InflatingMap(const char* filename, int p_intRobotSize, double p_mapResolution) {

	int factorMapSize = (ceil(p_intRobotSize / p_mapResolution) );

	//decode
	lodepng::decode(m_vec, m_width, m_height, filename);
	bool* array = new bool [m_width*m_height];

	// GET VECTOR FROM MAP (scanning)
	for (int row = 0; row < m_height; row++) {
		for (int col = 0; col < m_width; col++) {
			int current_pixel = (row * 4 * m_width) + (col * 4);
			if ((m_vec[current_pixel] != 255) ||	// R
				(m_vec[current_pixel + 1] != 255) || // G
				(m_vec[current_pixel + 2] != 255)) {// B
				array[(row * m_width) + col] = true;
			}
			else {
				array[(row * m_width) + col] = false;
			}
		}
	}

	// NIPUAH
	for (int row = 0; row < m_height; row++)
	{
		for (int col = 0; col < m_width; col++)
		{
			int current_pixel_array = (row * m_width) + (col);
			int current_pixel = (row * 4 * m_width) + (col * 4);

			if (array[current_pixel_array] == true) // paint
			{
				int start = current_pixel - factorMapSize * m_width * 4 - factorMapSize * 4;
				int start2 = current_pixel_array - factorMapSize * m_width - factorMapSize;

				for(int rowIndex = 0; rowIndex < factorMapSize * 2 + 1; rowIndex++)
				{
					for(int colIndex = 0; colIndex < factorMapSize * 2 + 1; colIndex++)
					{
						int calc = start + rowIndex * m_width * 4 + colIndex * 4;

						if(calc + 2 < m_vec.size())
						{
							m_vec[calc] = 0;
							m_vec[calc + 1] = 0;
							m_vec[calc + 2] = 0;

						}
					}
				}
			}
		}
	}

	lodepng::encode(INFLATED_MAP_NAME, m_vec, m_width, m_height);
}

int Map::getCellValue(int row, int col)
{
	return m_original_grid[row][col];
}

int Map::getGridRow(double row)
{
	return (row * this->m_grid_resulotion);
}

int Map::getGridCol(double col)
{
	return (col * this->m_grid_resulotion);
}

int** Map::getGrid()
{
	return this->m_original_grid;
}

unsigned Map::getWidth()
{
	return this->m_width;
}

unsigned Map::getHeight()
{
	return this->m_height;
}

void Map::convertMapToGrid(double p_Grid_Resolution, double p_Map_Resolution, const char* pngName){

	m_vec.clear();

	// VEC TO GRID
	//decode
	lodepng::decode(m_vec, m_width, m_height, pngName);

	cellSize = p_Grid_Resolution / p_Map_Resolution;

	const unsigned int rowSize = floor(m_height/cellSize);
	const unsigned int colSize = floor(m_width/cellSize);

	// netanel bug...
	//int matrix[n][m];

	/*matrix = (int**)malloc(rowSize * sizeof(int*));

	for (int i=0; i<rowSize; i++)
	{
		matrix[i] = (int*)malloc(colSize * sizeof(int));
	}*/

	matrix = new int *[rowSize] ;

	for( int i = 0 ; i < rowSize ; i++ )
		matrix[i] = new int[colSize];


 	std::vector<unsigned char>gridVector;
	gridVector.resize(rowSize*colSize*4);

	// 95
	for (int gridRow = 0; gridRow < rowSize; gridRow++)
	{
		// 137
		for (int gridCol = 0; gridCol < colSize; gridCol++)
		{
			// Loading the map to a grid
			matrix[gridRow][gridCol] = checkIfOccupy(gridRow,gridCol, cellSize);

			// Calculating the current Pixel
			int current_pixel = (gridRow * 4 * colSize) + (gridCol * 4);

			// Checks whether the cell is full or empty
			if(matrix[gridRow][gridCol] == 1)
			{
				gridVector[current_pixel] = 0;
				gridVector[current_pixel + 1] = 0;
				gridVector[current_pixel + 2] = 0;
			}
			else
			{
				gridVector[current_pixel] = 255;
				gridVector[current_pixel + 1] = 255;
				gridVector[current_pixel + 2] = 255;
			}
			gridVector[current_pixel + 3] = 255;
		}
	}

	string strNewName = pngName;
	strNewName += "_grid";
	lodepng::encode(strNewName, gridVector, colSize, rowSize);

}

int Map::checkIfOccupy(int gridRow, int gridCol, int cellSize)
{
	int isblack = 0;

	int originalRow = gridRow * cellSize;
	int originalCol = gridCol * cellSize;

	for (int SingleCellRow = originalRow; SingleCellRow < originalRow + 4; SingleCellRow++)
	{
		for (int singleCellCol = originalCol; singleCellCol < originalCol + 4; singleCellCol++)
		{
			int current_pixel = (SingleCellRow * 4 * m_width) + (singleCellCol * 4);
			//cout << current_pixel << endl;
			if ((m_vec[current_pixel] != 255) ||	// R
					(m_vec[current_pixel + 1] != 255) || // G
					(m_vec[current_pixel + 2] != 255)) // B
			{
				isblack = 1;

				break;
			}
		}
	}

	return isblack;
}

void Map::createGrids(double grid_resolution, double map_resolution, const char* originalMap){
	convertMapToGrid(grid_resolution,
									   map_resolution,
									   originalMap);

	convertMapToGrid(grid_resolution,
									   map_resolution,
									   INFLATED_MAP_NAME);
}

int Map::getWaypointsSize()
{
	return m_wayPointsSize;
}

vector<Location> Map::getRoute(Location sourceLocation, Location destLocation)
{

	PathPlanner pp(this->m_height/cellSize,this->m_width/cellSize);

	for (int x = 0; x < pp.n; x++)
	{
		for (int y = 0; y < pp.m; y++)
		{
			if(x == sourceLocation.getX()/cellSize && y == sourceLocation.getY()/cellSize)
				cout << " ";
			cout << matrix[x][y];
		}

		cout << endl;
	}

	cout << endl << endl;

	int xA, yA, xB, yB;

	yA = sourceLocation.getX() / cellSize;
	xA = sourceLocation.getY() / cellSize;

	yB = destLocation.getX() / cellSize;
	xB = destLocation.getY() / cellSize;


	cout<<"Map Size (X,Y): "<< pp.n<<","<<pp.m<<endl;
	cout<<"Start: "<<xA<<","<<yA<<endl;
	cout<<"Finish: "<<xB<<","<<yB<<endl;
	// get the route
	clock_t start = clock();
	string route=pp.pathFind(xA, yA, xB, yB, matrix);
	if(route=="") cout<<"An empty route generated!"<<endl;
	clock_t end = clock();
	double time_elapsed = double(end - start);
	cout<<"Time to calculate the route (ms): "<<time_elapsed<<endl;
	cout<<"Route:"<<endl;
	cout<<route<<endl<<endl;

	// follow the route on the map and display it
	if(route.length()>0)
	{
		int j; char c;
		int x=xA;
		int y=yA;
		matrix[x][y]=2;
		for(int i=0;i<route.length();i++)
		{
			c =route.at(i);
			j=atoi(&c);
			x=x+dx[j];
			y=y+dy[j];
			matrix[x][y]=3;
		}
		matrix[x][y]=4;

		// display the map with the route
		for(int x=0;x<pp.n;x++)
		{
			for(int y=0;y<pp.m;y++)
				if(matrix[x][y]==0)
					cout<<".";
				else if(matrix[x][y]==1)
					cout<<"O"; //obstacle
				else if(matrix[x][y]==2)
					cout<<"S"; //start
				else if(matrix[x][y]==3)
					cout<<"R"; //route
				else if(matrix[x][y]==4)
					cout<<"F"; //finish
			cout<<endl;
		}
	}

	vector<Location> waypoints = pp.getPathLocations(route,xA,yA);
	m_wayPointsSize = pp.getWaypointsSize();

	return waypoints;
}

Map::~Map() {
	// TODO Auto-generated destructor stub
	for( int i = 0 ; i < m_width/4 ; i++ )
		delete [] matrix[i] ;
	delete [] matrix ;
}


