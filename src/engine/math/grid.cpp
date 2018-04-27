#include "src/engine/math/grid.h"
#include <unordered_map>

Grid::Grid(float gridSizeX, float gridSizeY, float gridSizeZ,
           float gridStartX, float gridStartY, float gridStartZ, float cellWidth) :
    _gridStartX(gridStartX),
    _gridStartY(gridStartY),
    _gridStartZ(gridStartZ),
    _gridSizeX(gridSizeX),
    _gridSizeY(gridSizeY),
    _gridSizeZ(gridSizeZ),
    _cellWidth(cellWidth)
{
    _sx = std::ceil(_gridSizeX / _cellWidth);
    _sy = std::ceil(_gridSizeY / _cellWidth);
    _sz = std::ceil(_gridSizeZ / _cellWidth);
}

int Grid::hash(Vector3i c)
{
    //similar to converting a 2d array to 1d convert 3d array to 1d is the hash.
    int i = c[0];
    int j = c[1];
    int k = c[2];

    return i + j * _sx + k * _sx * _sy;
}

Vector3i Grid::getCell(Vector3f particle)
{
    int i = (int)std::floor((particle[0] - _gridStartX) / _cellWidth);
    int j = (int)std::floor((particle[1] - _gridStartY) / _cellWidth);
    int k = (int)std::floor((particle[2] - _gridStartZ) / _cellWidth);

    return Vector3i(i, j, k);
}

std::vector<std::vector<int>> Grid::getNN(std::vector<Vector3f> &positions)
{
    std::unordered_map<int, std::vector<int>> cellList;

//    #pragma omp parallel for
    for (unsigned p = 0; p < positions.size(); p++) {
        int hashC = hash(getCell(positions.at(p)));
        cellList[hashC].push_back(p);
    }

    std::vector<std::vector<int>> neighbours(positions.size());
    #pragma omp parallel for
    for (unsigned i = 0; i < positions.size(); i++) {
        neighbours.at(i) = getNeighboursForParticle(i, positions, cellList);
    }

    return neighbours;
}

std::vector<int> Grid::getNeighboursForParticle(int particleID,
                                                std::vector<Vector3f> &positions,
                                                std::unordered_map<int, std::vector<int>> &cellList)
{
    std::vector<int> neighbours;
    Vector3i cell = getCell(positions.at(particleID));
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            for (int k = -1; k < 2; k++) {
                Vector3i curCell = Vector3i(cell[0] + i, cell[1] + j, cell[2] + k);
                if (curCell[0] < 0 || curCell[0] >= _sx) continue;
                if (curCell[1] < 0 || curCell[1] >= _sy) continue;
                if (curCell[2] < 0 || curCell[2] >= _sz) continue;
                std::vector<int> curCellParticles = cellList[hash(curCell)];
                for (int p : curCellParticles) {
                    if (p != particleID) {
                        neighbours.push_back(p);
                    }
                }
            }
        }
    }

    return neighbours;
}
