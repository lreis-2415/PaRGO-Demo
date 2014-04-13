#include"waterCoveringOperator.h"

void WaterCoveringOperator::wdemLayer(RasterLayer<double> &layerD) 
{
  _pwDEMLayer = &layerD;
}

void WaterCoveringOperator::demLayer(RasterLayer<double> &layer) 
{
  pzDEMLayer = &layer;
}

bool WaterCoveringOperator::Operator(const CellCoord &coord)
{
	CellSpace<double> &dem = *(_pDEMLayer->cellSpace());
	CellSpace<double> &wdem = *(_pwDEMLayer->cellSpace());
    int xSize = _pDEMLayer->_pMetaData->row;  //row count of the input raster data
    int ySize = _pDEMLayer->_pMetaData->column;  //column count of the input raster data
    int iRow = coord.iRow();
    int iCol = coord.iCol();
    int ROW = _pDEMLayer->_pMetaData->.LoctoGloRow(iRow()); //change the local coordinates of sub-domain to be global coordinates in the original raster data 
    int COL = _pDEMLayer->_pMetaData->.LoctoGloCol(iCol); 
    if (ROW == 0 || ROW == xSize-1 || COL == 0 || COL == ySize-1) //on the border
    {
    	wdem[i][j] = dem[i][j];
    } else   //not on the border 
    {
    	wdem[i][j] = maxwaterlevel; 
    }    
	return true;
}
