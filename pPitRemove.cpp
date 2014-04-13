#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include "neighborhood.h"
#include "cellSpace.h"
#include "basicTypes.h"
#include "rasterLayer.h"
#include "application.h"
#include "waterCoveringOperator.h"
#include "waterRemovalOperator.h"

using namespace std;
using namespace GPRO;

int main(int argc, char *argv[]) 
{
	/*  enum ProgramType{MPI_Type = 0,
				   MPI_OpenMP_Type,
				   CUDA_Type};*/
	Application::START(MPI_OpenMP_Type, argc, argv); //init

	char* inputfilename;
    char* outputtempname;
	char* neighborfile1;
    char* neighborfile2;
	char* outputfilename;
	if (argc < 7)
	{
		inputfilename = argv[1];
        outputtempname = argv[2];
		neighborfile1 = argv[3]; 
		neighborfile2 = argv[4]; 
		outputfilename = argv[5];
	}	
    //Step 1: Water-covering
    RasterLayer<double>  inputLayer1;  // create input raster layer
    RasterLayer<double>  outputLayer1 ; // create output raster layer
    inputLayer1.readNeighborhood(neighborfile1); //get the neighborhood window parameter (1×1 window for water-covering step in this algorithm)
    inputLayer1.readFile(inputfilename); //open input raster data file, and automatically make domain decomposition
    outputLayer1.copyLayerInfo(inputLayer1); //automatically make domain decomposition for output raster data
    WaterCoveringOperator WcOper; //create an object of the operator of water-covering
    WcOper.demLayer(inputLayer1); // load the input DEM layer
    WcOper.wdemLayer(outputLayer1); //load the output layer of water-covering DEM
    WcOper.Run();   // execute the parallel computing for water-covering step 
    outputLayer1.writeFile(outputtempname);  //write the results in output raster file

    //Step 2: Water-removal
    RasterLayer<double>  inputLayer2;  // create input raster layer
    RasterLayer<double>  outputLayer2 ; // create output raster layer
    inputLayer2.readNeighborhood(neighborfile2); //get the neighborhood window parameter (3×3 window for water-removal step in this algorithm). Arbitrary size of neighborhood window can be assigned by the config file.
    inputLayer2.readFile(inputfilename); //open input raster data file, and automatically make domain decomposition
    outputLayer2.readNeighborhood(neighborfile2); //get the neighborhood window parameter (3×3 window for water-removal step in this algorithm)
    outputLayer2.readFile(outputtempname); //open input water-covering DEM file, and automatically make domain decomposition
    WaterRemovalOperator WrOper;  //create an object of the operator of water-removal
    WrOper.demLayer(inputLayer2);  //load the input DEM layer
    WrOper.wdemLayer (outputLayer2); //load the output layer of water-removal DEM
    WrOper.Run();   // execute the parallel computing for water-removal step
    outputLayer2.writeFile(outputfilename); //write the results in output raster file
    Application::END();  // clean the parallel computing resources
}
