#include"waterRemovalOperator.h"

void WaterRemovalOperator::
demLayer(RasterLayer<double> &layerD) 
{
  _pDEMLayer = &layerD;
  _pDEMNbrhood = layerD.nbrhood();
  cellSize = _pDEMLayer->_pMetaData->cellSize;
  noData = _pDEMLayer->_pMetaData->noData;
  Configure(_pDEMLayer, false); // false means not to send and receive the data of _pDEMLayer for each process after each round of iteration
}

void WaterRemovalOperator::wdemLayer(RasterLayer<double> &layerD) 
{
  _pwDEMLayer = &layerD;
  Configure(_pwDEMLayer,true); // true means need to send and receive the data of _pwDEMLayer for each process after each round of iteration
}

// operator function for water-removal step
bool WaterRemovalOperator::Operator(const CellCoord &coord)
{

	CellSpace<double> &dem = *(_pDEMLayer->cellSpace());
	CellSpace<double> &wdem = *(_pwDEMLayer->cellSpace());
	int xSize = _pDEMLayer->_pMetaData->row; //metadata of raster layer
	int ySize = _pDEMLayer->_pMetaData->column;
	int iRow = coord.iRow();
	int iCol = coord.iCol();
	Neighborhood<double>& nbrhoodD = *(_pDEMNbrhood);
	int iNeighborCells = ((int)sqrt((double)nbrhoodD.size())) / 2;   // assign the neighborhood window
	int i, j;
	int temp = 0;
	if( wdem[iRow][iCol] > dem[iRow][iCol] )
	{
		for(i = iRow - iNeighborCells; i <= iRow + iNeighborCells; i++)
		{
			for(j = iCol - iNeighborCells; j <= iCol + iNeighborCells; j++)
			{			
				if( dem[iRow][iCol] >= (wdem[i][j] + gap) )
				{
					wdem[iRow][iCol] = dem[iRow][iCol];
					Termination = 0; // denote if the iterative processing will continue
				}
				else 
				{
					if( wdem[iRow][iCol] > (wdem[i][j] + gap) )
					{
						wdem[iRow][iCol] = wdem[i][j] + gap;
						Termination = 0;
					}
				}
			}
		}
	}
	return true;
}
