#ifndef MESH_H
#define MESH_H

#include <vector>
#include <map>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "src/engine/graphics/Shape.h"

#include <Eigen/StdVector>

EIGEN_DEFINE_STL_VECTOR_SPECIALIZATION(Eigen::Matrix2f)
EIGEN_DEFINE_STL_VECTOR_SPECIALIZATION(Eigen::Matrix3f)
EIGEN_DEFINE_STL_VECTOR_SPECIALIZATION(Eigen::Matrix3i)

struct Vertex;
struct Face;
struct collapseCost;
struct collapseCost {
    int vert1;
    int vert2;
    int face1;
    int face2;
    Eigen::Vector3f newVert;
    float cost;
    //compare for order.
    bool operator <(const collapseCost& cc) const
    {
        if(cost == cc.cost) {
            if(vert1 == cc.vert1) {
                return vert2 < cc.vert2;
            } else {
                return vert1 < cc.vert1;
            }
        } else {
            return (cost < cc.cost);
        }
    }
    //equality
    bool operator ==(const collapseCost& cc) const
    {
        return ((vert1 == cc.vert1) && (vert2 == cc.vert2)) || ((vert1 == cc.vert2) && (vert2 == cc.vert1));
    }
};
namespace std {
    template<>
    struct hash<collapseCost> {
        inline size_t operator()(const collapseCost& x) const {
            float v = x.cost + 10000*x.vert1 + 10000000*x.vert2;
            size_t value = std::hash<float>{}(v);
            return value;
        }
    };
}
struct Vertex {
    Eigen::Vector3f coords;
    std::unordered_set<int> faces;
    Eigen::Matrix4f Q;
    std::unordered_set<collapseCost> edges;
    Eigen::Vector3f normal;
};
struct Face {
    Eigen::Vector3i vertices;
    Eigen::Vector3i changedVertices = Eigen::Vector3i(0, 0, 0);
    Eigen::Vector3f normal;
    Eigen::Matrix4f Q;
};
class Mesh
{
public:
    int currVertex = 1;
    int currFace = 1;
    int oldVertices;
    int oldFaces;
    std::unordered_map<int, Vertex> vertexMap;
    std::unordered_map<int, Face> faceMap;
    std::set<collapseCost> collapseCosts;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    void initFromVectors(const std::vector<Eigen::Vector3f> &vertices,
         const std::vector<Eigen::Vector3i> &faces);
    void loadFromFile(const std::string &filePath);
    void saveToFile(const std::string &filePath);
    std::shared_ptr<Shape> makeMesh();
    std::shared_ptr<Shape> makeGround();
    void generateSubdivisionStructs();
    void generateSimplifyStructs();
    void generateDenoiseStructs();
    void convertSubdivisionStructBack();
    void convertSimplifyStructBack();
    void convertNoiseStructBack();
    void subdivide();
    void denoise();
    void generateNoisyImage();
    void simplify(int num);
private:
    Eigen::Vector3f denoisePoint(int vert1, Eigen::Vector3f norm);
    bool withinRadius(int vert1, int vert2, float radius);
    int getAdjacentFace(int vert1, int vert2, int face1);
    std::vector<int> getNeighbors(int vert1, float radius);
    Eigen::Vector3f getMidpoint(int face1, int face2, int vert1, int vert2);
    int getOtherVertexIndex(int vert1, int vert2, int face1);
    void newFace(int v1, int v2, int v3);
    void edgeCollapse();
    void setAdjacentSides(int v, int face1, int face2, int newVert);
    Eigen::Matrix4f generateQ(Eigen::Vector3f n, Eigen::Vector3f p);
    std::unordered_set<int> getAdjacentVertices(int v);
    void removeFaceFromVerts(int face, int vert1, int vert2);
    collapseCost genEdge(int vert1, int vert2, int face1, int face2);
    Eigen::Vector3f getMinErrorPoint(Eigen::Matrix4f q);
    void setAdjacentEdges(int vert1, collapseCost min, int newVert, int skipVert1, int skipVert2, int skipFace1, int skipFace2, int initFace1, int initFace2);
    void setAdjacentEdgesV2(int vert1, collapseCost min, int newVert, int skipVert1, int skipVert2);
    float areaOfTriangle(Eigen::Vector3f t1, Eigen::Vector3f t2);
    int getOtherPointOnFace(int vert1, int vert2, int face1);
    std::vector<Eigen::Vector3f> _vertices;
    std::vector<Eigen::Vector3i> _faces;
    int vertexNum = 0;
    int faceNum = 0;
    std::map<int, Eigen::Vector3f> _vertexMap;
    std::map<int, Eigen::Vector3i> _faceMap;
    std::map<int, std::vector<int>> _vertexToFace;
    float neighborRadius = .05f;
    float sigmaC = .1f;
    float sigmaS = .1f;
};

#endif // MESH_H
