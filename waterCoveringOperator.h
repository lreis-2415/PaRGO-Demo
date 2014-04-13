#ifndef WATERCOVERINGOPERATOR_H
#define WATERCOVERINGOPERATOR_H

#include "cellSpace.h"
#include "neighborhood.h"
#include "rasterOperator.h"
#include "rasterLayer.h"
#include <cmath>
#include <functional>

using namespace GPRO;

class WaterCoveringOperator : public RasterOperator<double> 
{
  public:
     WaterCoveringOperator()
            :RasterOperator<double>(),
             pzDEMLayer(0), pwDEMLayer(0), maxwaterlevel(10000.0) {}  //initial water level which floods all of DEM
    ~WaterCoveringOperator() {}   
  
    void demLayer(RasterLayer<double> &layerD);
	void wdemLayer(RasterLayer<double> &layerD);
    virtual bool Operator(const CellCoord &coord);

  public:
    double maxwaterlevel;
 	RasterLayer<double> * pzDEMLayer;  // input raster layer
 	RasterLayer<double> * pwDEMLayer;  // output raster layer
};

#endif