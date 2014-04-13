#ifndef WATERREMOVALOPERATOR_H
#define WATERREMOVALOPERATOR_H

#include "cellSpace.h"
#include "neighborhood.h"
#include "rasterOperator.h"
#include "rasterLayer.h"
#include <cmath>
#include <functional>

using namespace GPRO;

class WaterRemovalOperator : public RasterOperator<double> 
{
  public:
    WaterRemovalOperator()
      :RasterOperator<double>(),
       _pDEMLayer(0), _pwDEMLayer(0), num(0), flag(true),gap(0.00005){}
   
    ~WaterRemovalOperator() {}
 
    void demLayer(RasterLayer<double> &layerD);
	void wdemLayer(RasterLayer<double> &layerD);

    virtual bool Operator(const CellCoord &coord);

  public:
	double gap;  //step value for elevation revision
	RasterLayer<double> *_pDEMLayer;
	RasterLayer<double> *_pwDEMLayer;
	Neighborhood<double> *_pDEMNbrhood;
};

#endif