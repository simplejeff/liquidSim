#ifndef GRID_H
#define GRID_H

#include <Eigen/Core>
#include <vector>
#include <unordered_map>

using namespace Eigen;

class Grid
{
public:
    Grid(float gridSizeX, float gridSizeY, float gridSizeZ,
         float gridStartX, float gridStartY, float gridStartZ, float cellWidth);

    std::vector<std::vector<int> > getNN(std::vector<Vector3f> &positions);

private:
    int hash(Vector3i c);
    Vector3i getCell(Vector3f particle);
    std::vector<int> getNeighboursForParticle(int particleID,
                                              std::vector<Vector3f> &positions,
                                              std::unordered_map<int, std::vector<int>> &cellList);

    float _gridStartX;
    float _gridStartY;
    float _gridStartZ;

    float _gridSizeX;
    float _gridSizeY;
    float _gridSizeZ;

    float _cellWidth;
    int _sx;
    int _sy;
    int _sz;
};

#endif // GRID_H
