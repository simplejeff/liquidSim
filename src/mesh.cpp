#include "mesh.h"

#include <iostream>
#include <fstream>

#include <QFileInfo>
#include <QString>
#include <Eigen/Dense>
#include <limits>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <math.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include "util/tiny_obj_loader.h"

using namespace Eigen;
using namespace std;

void Mesh::initFromVectors(const std::vector<Vector3f> &vertices,
           const std::vector<Vector3i> &faces)
{
    _vertices = vertices;
    _faces = faces;
    srand (static_cast <unsigned> (time(0)));
}

void Mesh::generateSubdivisionStructs() {
    for(int i = 0; i < _vertices.size(); i++) {
        Vector3f coords = _vertices[i];
        Vertex v;
        v.coords = coords;
        vertexMap.insert({currVertex, v});
        currVertex++;
    }
    oldVertices = currVertex;
    for(int j = 0; j < _faces.size(); j++) {
        Vector3i vertices = _faces[j];
        vertices += Vector3i(1, 1, 1);
        Face f;
        f.vertices = vertices;
        vertexMap[vertices[0]].faces.insert(currFace);
        vertexMap[vertices[1]].faces.insert(currFace);
        vertexMap[vertices[2]].faces.insert(currFace);
        faceMap.insert({currFace, f});
        currFace++;
    }
    oldFaces = currFace;
}

void Mesh::generateDenoiseStructs() {
    for(int i = 0; i < _vertices.size(); i++) {
        Vector3f coords = _vertices[i];
        Vertex v;
        v.coords = coords;
        vertexMap.insert({currVertex, v});
        currVertex++;
    }
    for(int j = 0; j < _faces.size(); j++) {    
        Vector3i vertices = _faces[j];
        vertices += Vector3i(1, 1, 1);
        Face f;
        f.vertices = vertices;
        Vertex vertex1 = vertexMap[vertices[0]];
        Vertex vertex2 = vertexMap[vertices[1]];
        Vertex vertex3 = vertexMap[vertices[2]];
        Vector3f p1 = vertex1.coords;
        Vector3f p2 = vertex2.coords;
        Vector3f p3 = vertex3.coords;
        Vector3f v1 = p2 - p1;
        Vector3f v2 = p3 - p1;
        Vector3f n = v1.cross(v2);
        n = n.normalized();
        f.normal = n;
        vertexMap[vertices[0]].faces.insert(currFace);
        vertexMap[vertices[1]].faces.insert(currFace);
        vertexMap[vertices[2]].faces.insert(currFace);
        faceMap.insert({currFace, f});
        currFace++;
    }
    for(std::pair<int, Vertex> vertexPair : vertexMap) {
        Vertex vert = vertexPair.second;
        std::unordered_set<int> faces = vert.faces;
        Vector3f totalAreaNorm = Vector3f(0.f, 0.f, 0.f);
        for(const int &i : faces) {
            Face f = faceMap[i];
            Vector3f p1 = vertexMap[f.vertices[0]].coords;
            Vector3f p2 = vertexMap[f.vertices[1]].coords;
            Vector3f p3 = vertexMap[f.vertices[2]].coords;
            Vector3f v1 = p2 - p1;
            Vector3f v2 = p3 - p1;
            float currArea = (v1.cross(v2)).norm();
            totalAreaNorm += f.normal*currArea;
        }
        totalAreaNorm = totalAreaNorm.normalized();
        vert.normal = totalAreaNorm;
        vertexMap[vertexPair.first] = vert;
    }
    std::cout << "vert size : " << vertexMap.size() << std::endl;
    std::cout << "face size : " << faceMap.size() << std::endl;
}

void Mesh::denoise() {
    generateDenoiseStructs();
    std::unordered_map<int, Vector3f> newVerticeMap;
    for(std::pair<int, Vertex> vertexPair : vertexMap) {
        Vertex vert = vertexPair.second;
        Vector3f newPoint = denoisePoint(vertexPair.first, vert.normal);
        newVerticeMap.insert({vertexPair.first, newPoint});
    }
    for (std::pair<int, Vector3f> newPoint : newVerticeMap)
    {
        Vertex vert = vertexMap[newPoint.first];
        vert.coords = newPoint.second;
        vertexMap[newPoint.first] = vert;
    }
    convertNoiseStructBack();
}

Eigen::Vector3f Mesh::denoisePoint(int vert1, Eigen::Vector3f norm) {
    Vector3f vert1Coord = vertexMap[vert1].coords;
    std::vector<int> neighborVerts = getNeighbors(vert1, neighborRadius);
    float sum = 0.f;
    float normalizer = 0.f;
    for(int i = 0; i < neighborVerts.size(); i++) {
        Vector3f currCoords = vertexMap[neighborVerts[i]].coords;
        float t = (vert1Coord - currCoords).norm();
        float h = norm.dot(vert1Coord - currCoords);
        float wc = exp((-t*t)/(2.f*sigmaC*sigmaC));
        float ws = exp((-h*h)/(2.f*sigmaS*sigmaS));
        sum += wc*ws*h;
        normalizer += wc*ws;
    }
    if(normalizer > 0.f) {
        return vert1Coord - norm*(sum/normalizer);
    } else {
        return vert1Coord;
    }
}

std::vector<int> Mesh::getNeighbors(int vert1, float radius) {
    std::unordered_set<int> visitedFaces;
    std::unordered_set<int> visitedVertices;
    std::queue<int> verts;
    std::vector<int> neighborVerts = std::vector<int>();
    verts.push(vert1);
    visitedVertices.insert(vert1);
    int currVert;
    std::unordered_set<int> currFaces;
    while(!verts.empty()) {
        currVert = verts.front();
        verts.pop();
        if(withinRadius(currVert, vert1, radius)) {
            if(currVert != vert1) {
                neighborVerts.push_back(currVert);
            }
            currFaces = vertexMap[currVert].faces;
            for(const int &f : currFaces) {
                if(visitedFaces.count(f) <= 0) {
                    visitedFaces.insert(f);
                    for(int i = 0; i < 3; i++) {
                        int faceVert = faceMap[f].vertices[i];
                        if(visitedVertices.count(faceVert) <= 0) {
                            visitedVertices.insert(faceVert);
                            verts.push(faceVert);
                        }
                    }
                }
            }
        }
    }

    return neighborVerts;
}

bool Mesh::withinRadius(int vert1, int vert2, float radius) {
    Vector3f coord1 = vertexMap[vert1].coords;
    Vector3f coord2 = vertexMap[vert2].coords;
    float dist = (coord1-coord2).norm();
    return radius >= dist;
}

void Mesh::generateNoisyImage() {
    for(int i = 0; i < _vertices.size(); i++) {
        Vector3f coords = _vertices[i];
        float rand1 = .002f - (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*.004f;
        float rand2 = .002f - (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*.004f;
        float rand3 = .002f - (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*.004f;
        coords += Vector3f(rand1, rand2, rand3);
        _vertices[i] = coords;
    }
}

void Mesh::generateSimplifyStructs() {
    for(int i = 0; i < _vertices.size(); i++) {
        Vector3f coords = _vertices[i];
        Vertex v;
        v.coords = coords;
        vertexMap.insert({currVertex, v});
        currVertex++;
    }
    oldVertices = currVertex;
    for(int j = 0; j < _faces.size(); j++) {
        Vector3i vertices = _faces[j];
        vertices += Vector3i(1, 1, 1);
        Face f;
        f.vertices = vertices;
        Vertex vertex1 = vertexMap[vertices[0]];
        Vertex vertex2 = vertexMap[vertices[1]];
        Vertex vertex3 = vertexMap[vertices[2]];
        Vector3f p1 = vertex1.coords;
        Vector3f p2 = vertex2.coords;
        Vector3f p3 = vertex3.coords;
        Vector3f v1 = p2 - p1;
        Vector3f v2 = p3 - p1;
        Vector3f n = v1.cross(v2);
        n = n.normalized();
        f.Q = generateQ(n, p1);
       // f.normal = n;
        vertexMap[vertices[0]].faces.insert(currFace);
        vertexMap[vertices[1]].faces.insert(currFace);
        vertexMap[vertices[2]].faces.insert(currFace);
        faceMap.insert({currFace, f});
        currFace++;
    }
    for(std::pair<int, Vertex> vertexPair : vertexMap) {
        Vertex vert = vertexPair.second;
        std::unordered_set<int> faces = vert.faces;
        Matrix4f Q;
        for(int a = 0; a < 4; a++) {
            for(int b = 0; b < 4; b++) {
                Q(a, b) = 0.f;
            }
        }
        float totalArea = 0.f;
        for(const int &i : faces) {
            Face f = faceMap[i];
            Vector3f p1 = vertexMap[f.vertices[0]].coords;
            Vector3f p2 = vertexMap[f.vertices[1]].coords;
            Vector3f p3 = vertexMap[f.vertices[2]].coords;
            Vector3f v1 = p2 - p1;
            Vector3f v2 = p3 - p1;
            float currArea = (v1.cross(v2)).norm();
            totalArea += currArea;
            Q += f.Q*currArea;
        }
        Q *= (1.f/totalArea);
        vert.Q = Q;
        vertexMap[vertexPair.first] = vert;
    }
    for(std::pair<int, Face> facePair : faceMap) {
        Face currFace = facePair.second;
        for(int a = 0; a < 3; a++) {
            int firstVertexIndex = a;
            int secondVertexIndex = (a == 2 ? 0 : a+1);
            int firstVertex = currFace.vertices[firstVertexIndex];
            int secondVertex = currFace.vertices[secondVertexIndex];
            //get adjacentFace
            int f2 = getAdjacentFace(firstVertex, secondVertex, facePair.first);
            Face adjacentFace = faceMap[f2];
            int currIndex = getOtherVertexIndex(firstVertex, secondVertex, facePair.first);
            int otherIndex = getOtherVertexIndex(firstVertex, secondVertex, f2);
            if(!currFace.changedVertices[currIndex]) {
                collapseCost newCost = genEdge(firstVertex, secondVertex, facePair.first, f2);
                collapseCosts.insert(newCost);
            }
            currFace.changedVertices[currIndex] = 1;
            adjacentFace.changedVertices[otherIndex] = 1;
            faceMap[f2] = adjacentFace;
        }
        faceMap[facePair.first] = currFace;
    }
    oldFaces = currFace;
}

float areaOfTriangle(Vector3f t1, Vector3f t2) {
    return std::abs(t1[0] * (t2[1]-t2[2]) + t1[1] * (t2[2]-t2[0]) + t1[2] * (t2[0]-t2[1]));
}

collapseCost Mesh::genEdge(int vert1, int vert2, int face1, int face2) {
    collapseCost newCost;
    if(vertexMap.count(vert1) <= 0) {
        std::cout << "v1 doesn't exist " << vert1 << std::endl;
    }
    if(vertexMap.count(vert2) <= 0) {
        std::cout << "v2 doesn't exist" << std::endl;
    }
    Vertex v1 = vertexMap[vert1];
    Vertex v2 = vertexMap[vert2];
    newCost.vert1 = vert1;
    newCost.vert2 = vert2;
    newCost.face1 = face1;
    newCost.face2 = face2;
    newCost.newVert = getMinErrorPoint(v1.Q + v2.Q);
    Vector4f v = Vector4f(newCost.newVert[0], newCost.newVert[1], newCost.newVert[2], 1.f);
    newCost.cost = v.transpose()*(v1.Q + v2.Q)*v;
    v1.edges.insert(newCost);
    v2.edges.insert(newCost);
    vertexMap[vert1] = v1;
    vertexMap[vert2] = v2;
    return newCost;
}

Vector3f Mesh::getMinErrorPoint(Matrix4f q) {
    Matrix4f calc;
    calc << q(0, 0), q(0, 1), q(0, 2), q(0, 3),
            q(0, 1), q(1, 1), q(1, 2), q(1, 3),
            q(0, 2), q(1, 2), q(2, 2), q(2, 3),
            0.f,     0.f,     0.f,     1.f;
    Vector4f v = calc.inverse() * Vector4f(0.f, 0.f, 0.f, 1.f);
    return Vector3f(v[0], v[1], v[2]);
}

int Mesh::getAdjacentFace(int vert1, int vert2, int face1) {
    std::unordered_set<int> vert1Faces = vertexMap[vert1].faces;
    std::unordered_set<int> vert2Faces = vertexMap[vert2].faces;
    for(const int &firstFace : vert1Faces) {
        for(const int &secondFace : vert2Faces) {
            if(firstFace == secondFace && firstFace != face1) {
                return firstFace;
            }
        }
    }
    return 0;
}

Vector3f Mesh::getMidpoint(int face1, int face2, int vert1, int vert2) {
    Face f1 = faceMap[face1];
    Face f2 = faceMap[face2];
    int vert3 = f1.vertices(getOtherVertexIndex(vert1, vert2, face1));
    int vert4 = f2.vertices(getOtherVertexIndex(vert1, vert2, face2));
    Vector3f v1 = vertexMap[vert1].coords;
    Vector3f v2 = vertexMap[vert2].coords;
    Vector3f v3 = vertexMap[vert3].coords;
    Vector3f v4 = vertexMap[vert4].coords;
    return v1*(3.f/8.f) + v2*(3.f/8.f) + v3*(1.f/8.f) + v4*(1.f/8.f);
}

int Mesh::getOtherVertexIndex(int vert1, int vert2, int face1) {
    Face f = faceMap[face1];
    Vector3i verts = f.vertices;
    for(int i = 0; i < 3; i++) {
        if(verts[i] != vert1 && verts[i] != vert2) {
            return i;
        }
    }
    return -1;
}

void Mesh::newFace(int v1, int v2, int v3) {
    Vertex vert1 = vertexMap[v1];
    Vertex vert2 = vertexMap[v2];
    Vertex vert3 = vertexMap[v3];
    Face f;
    f.vertices = Vector3i(v1, v2, v3);
    faceMap.insert({currFace, f});
   /* vert1.changedFaces.push_back(currFace);
    vert2.changedFaces.push_back(currFace);
    vert3.changedFaces.push_back(currFace);*/
    vertexMap[v1] = vert1;
    vertexMap[v2] = vert2;
    vertexMap[v3] = vert3;
    currFace++;
}

std::unordered_set<int> Mesh::getAdjacentVertices(int v) {
    std::unordered_set<int> adjacentFaces;
    Vertex vert = vertexMap[v];
    std::unordered_set<int> vertFaces = vert.faces;
    for(const int &i : vertFaces) {
        Face f = faceMap[i];
        for(int j = 0; j < 3; j++) {
            int faceVert = f.vertices[j];
            if(faceVert != v) {
                adjacentFaces.insert(faceVert);
            }
        }
    }
    return adjacentFaces;
}

void Mesh::subdivide() {
    generateSubdivisionStructs();
    //for each face in our mesh
    for(int i = 1; i < oldFaces; i++) {
        Face currFace = faceMap[i];
        Vector3i currFaceVerts = currFace.vertices;
        //for each side of the face's triangle
        for(int a = 0; a < 3; a++) {
            int firstVertexIndex = a;
            int secondVertexIndex = (a == 2 ? 0 : a+1);
            int firstVertex = currFaceVerts[firstVertexIndex];
            int secondVertex = currFaceVerts[secondVertexIndex];
            //get adjacentFace
            int f2 = getAdjacentFace(firstVertex, secondVertex, i);
            Face adjacentFace = faceMap[f2];
            //getOtherVertexIndex of adjacentFace and currFace
            int faceSideIndex = getOtherVertexIndex(firstVertex, secondVertex, i);
            int adjacentFaceSideIndex = getOtherVertexIndex(firstVertex, secondVertex, f2);
            //check if first or second face contain the new vertex to generate
            bool firstContainsNewVert = currFace.changedVertices[faceSideIndex];
            bool secondContainsNewVert = adjacentFace.changedVertices[adjacentFaceSideIndex];
            //if so, add it in to whatever face is missing it
            if(firstContainsNewVert || secondContainsNewVert) {
                if(!firstContainsNewVert) {
                    currFace.changedVertices[faceSideIndex] = adjacentFace.changedVertices[adjacentFaceSideIndex];
                }
                if(!secondContainsNewVert) {
                    adjacentFace.changedVertices[adjacentFaceSideIndex] = currFace.changedVertices[faceSideIndex];
                }
            } else {
                //else we must calculate midpoint and create the new vertex
                Vector3f midpoint = getMidpoint(i, f2, firstVertex, secondVertex);
                Vertex v;
                v.coords = midpoint;
                vertexMap.insert({currVertex, v});
                currFace.changedVertices[faceSideIndex] = currVertex;
                adjacentFace.changedVertices[adjacentFaceSideIndex] = currVertex;
                currVertex++;
            }
            faceMap[i] = currFace;
            faceMap[f2] = adjacentFace;
        }
        //generate all 4 new faces in count
        Vector3i newFaceVerts = currFace.changedVertices;
        newFace(currFaceVerts[0], newFaceVerts[2], newFaceVerts[1]);
        newFace(currFaceVerts[1], newFaceVerts[0], newFaceVerts[2]);
        newFace(newFaceVerts[0], currFaceVerts[2], newFaceVerts[1]);
        newFace(newFaceVerts[1], newFaceVerts[2], newFaceVerts[0]);
    }
    //create map of vertex Id to vec3f
    std::unordered_map<int, Vector3f> newVerticeMap;
    for(int j = 1; j < oldFaces; j++) {
        Face currFace = faceMap[j];
        Vector3i currFaceVerts = currFace.vertices;
        //for each vertex in face
        for(int v = 0; v < 3; v++) {
            int currVec = currFaceVerts[v];
            if(newVerticeMap.find(currVec) == newVerticeMap.end()) {
                std::unordered_set<int> surroundingVerts = getAdjacentVertices(currVec);
                int numVerts = surroundingVerts.size();
                bool isThree = (numVerts == 3);
                Vector3f currVal;
                if(isThree) {
                    currVal = vertexMap[currVec].coords * (7.f/16.f);
                } else {
                    currVal = vertexMap[currVec].coords * (5.f/8.f);
                }
                for(int surroundingVert : surroundingVerts) {
                    if(isThree) {
                        currVal += vertexMap[surroundingVert].coords * (3.f/16.f);
                    } else {
                        currVal += vertexMap[surroundingVert].coords * (3.f/(8.f*(float)numVerts));
                    }
                }
                newVerticeMap.insert({currVec, currVal});
            }
        }
    }
    for (std::pair<int, Vector3f> newPoint : newVerticeMap)
    {
        Vertex vert = vertexMap[newPoint.first];
        //std::cout << "first :" << vert.coords << std::endl;
        //std::cout << "second :" << newPoint.second << std::endl;
        vert.coords = newPoint.second;
        vertexMap[newPoint.first] = vert;
    }
    convertSubdivisionStructBack();
}

void Mesh::convertSubdivisionStructBack() {
    _vertices = std::vector<Vector3f>();
    _faces = std::vector<Vector3i>();
    for(int i = 1; i < currVertex; i++) {
        _vertices.push_back(vertexMap[i].coords);
    }
    for(int j = oldFaces; j < currFace; j++) {
        Vector3i vertices = faceMap[j].vertices;
        vertices -= Vector3i(1, 1, 1);
        _faces.push_back(vertices);
    }
}

void Mesh::convertNoiseStructBack() {
    _vertices = std::vector<Vector3f>();
    _faces = std::vector<Vector3i>();
    std::unordered_map<int, int> reorderVertex;
    int currVert = 0;
    for(std::pair<int, Vertex> vertexPair : vertexMap) {
        _vertices.push_back(vertexPair.second.coords);
        reorderVertex.insert({vertexPair.first, currVert});
        currVert++;
    }
    for(std::pair<int, Face> facePair : faceMap) {
        Vector3i vertices = facePair.second.vertices;
        vertices = Vector3i(reorderVertex[vertices[0]], reorderVertex[vertices[1]], reorderVertex[vertices[2]]);
        _faces.push_back(vertices);
    }

}

void Mesh::convertSimplifyStructBack() {
    _vertices = std::vector<Vector3f>();
    _faces = std::vector<Vector3i>();
    int currVert = 0;
    std::unordered_map<int, int> reorderVertex;
    for(std::pair<int, Vertex> vertexPair : vertexMap) {
        _vertices.push_back(vertexPair.second.coords);
        reorderVertex.insert({vertexPair.first, currVert});
        currVert++;
    }
    for(std::pair<int, Face> facePair : faceMap) {
        Vector3i vertices = facePair.second.vertices;
        vertices = Vector3i(reorderVertex[vertices[0]], reorderVertex[vertices[1]], reorderVertex[vertices[2]]);
        _faces.push_back(vertices);
    }
}

void Mesh::edgeCollapse() {
    collapseCost min = *(collapseCosts.begin());
    int face1, face2, vert1, vert2;
    face1 = min.face1;
    face2 = min.face2;
    vert1 = min.vert1;
    vert2 = min.vert2;
    if(vertexMap.count(vert1) <= 0) {
        std::cout << "edgeCollapse vert1 doesn't exist " << vert1 << std::endl;
    }
    if(vertexMap.count(vert2) <= 0) {
        std::cout << "edgeCollapse vert1 doesn't exist " << vert1 << std::endl;
    }
    int skipVert1 = getOtherPointOnFace(vert1, vert2, face1);
    int skipVert2 = getOtherPointOnFace(vert1, vert2, face2);
    int skipFace1 = getAdjacentFace(skipVert1, vert2, face1);
    int skipFace2 = getAdjacentFace(skipVert2, vert2, face2);
    Vertex vertex1 = vertexMap[vert1];
    Vertex vertex2 = vertexMap[vert2];
    Vector3f midcoord = min.newVert;
    Vertex midvert;
    midvert.Q = vertex1.Q + vertex2.Q;
    midvert.coords = midcoord;
    int vertexPoint = currVertex;
    vertexMap.insert({vertexPoint, midvert});
    setAdjacentSides(vert1, face1, face2, vertexPoint);
    setAdjacentSides(vert2, face1, face2, vertexPoint);
    setAdjacentEdges(vert1, min, vertexPoint, skipVert1, skipVert2, skipFace1, skipFace2, face1, face2);
    setAdjacentEdgesV2(vert2, min, vertexPoint, skipVert1, skipVert2);
    collapseCosts.erase(min);
    currVertex++;
    removeFaceFromVerts(face1, vert1, vert2);
    removeFaceFromVerts(face2, vert1, vert2);
    faceMap.erase(face1);
    faceMap.erase(face2);
    vertexMap.erase(vert1);
    vertexMap.erase(vert2);
}

int Mesh::getOtherPointOnFace(int vert1, int vert2, int face1) {
    Face f1 = faceMap[face1];
    for(int a = 0; a < 3; a++) {
        int currVert = f1.vertices[a];
        if(currVert != vert1 && currVert != vert2) {
            return currVert;
        }
    }
    return 0;
}



void Mesh::setAdjacentEdges(int vert1, collapseCost min, int newVert, int skipVert1, int skipVert2, int skipFace1, int skipFace2, int initFace1, int initFace2) {
    Vertex vertex1 = vertexMap[vert1];
    for(const collapseCost &c : vertex1.edges) {
        //vertex1.edges.erase(c);
        if(!(c == min)) {
            int vertVal = c.vert1;
            if(vertVal == vert1) {
                vertVal = c.vert2;
            }
            Vertex vertValVertex = vertexMap[vertVal];
            vertValVertex.edges.erase(c);
            vertexMap[vertVal] = vertValVertex;
            int face1 = c.face1;
            int face2 = c.face2;
            if(vertVal == skipVert1) {
                if(face1 == initFace1) {
                    face1 = skipFace1;
                } else {
                    face2 = skipFace1;
                }
            }
            if(vertVal == skipVert2) {
                if(face1 == initFace2) {
                    face1 = skipFace2;
                } else {
                    face2 = skipFace2;
                }
            }
            collapseCost newCost = genEdge(vertVal, newVert, face1, face2);
            collapseCosts.insert(newCost);
        }
        collapseCosts.erase(c);
    }
}

void Mesh::setAdjacentEdgesV2(int vert1, collapseCost min, int newVert, int skipVert1, int skipVert2) {
    Vertex vertex1 = vertexMap[vert1];
    for(const collapseCost &c : vertex1.edges) {
        //vertex1.edges.erase(c);
        if(!(c == min)) {
            int vertVal = c.vert1;
            if(vertVal == vert1) {
                vertVal = c.vert2;
            }
            Vertex vertValVertex = vertexMap[vertVal];
            vertValVertex.edges.erase(c);
            vertexMap[vertVal] = vertValVertex;
            if(vertVal != skipVert1 && vertVal != skipVert2) {
                collapseCost newCost = genEdge(vertVal, newVert, c.face1, c.face2);
                collapseCosts.insert(newCost);
            }
        }
        collapseCosts.erase(c);
    }
}


void Mesh::removeFaceFromVerts(int face, int vert1, int vert2) {
    Face f = faceMap[face];
    Vector3i verts = f.vertices;
    for(int a = 0; a < 3; a++) {
        int vertVal = verts[a];
        if(vertVal != vert1 && vertVal != vert2) {
            if(vertexMap.count(verts[a]) <= 0) {
                std::cout << "removeface v1 doesn't exist " << verts[a] << std::endl;
            }
            Vertex v = vertexMap[verts[a]];
            std::unordered_set<int> faces = v.faces;
            faces.erase(face);
            //faces.erase(std::remove(faces.begin(), faces.end(), face), faces.end());
            v.faces = faces;
            vertexMap[verts[a]] = v;
        }
    }
}

void Mesh::setAdjacentSides(int v, int face1, int face2, int newVert) {
    Vertex vertex = vertexMap[v];
    Vertex newVertex = vertexMap[newVert];
    std::unordered_set<int> vertFaces = vertex.faces;
    for(const int &i : vertFaces) {
        int currF = i;
        if(currF != face1 && currF != face2) {
            newVertex.faces.insert(currF);
            Face currFace = faceMap[currF];
            for(int a = 0; a < 3; a++) {
                if(currFace.vertices[a] == v) {
                    currFace.vertices[a] = newVert;
                   /* Vertex vertex1 = vertexMap[currFace.vertices[0]];
                    Vertex vertex2 = vertexMap[currFace.vertices[1]];
                    Vertex vertex3 = vertexMap[currFace.vertices[2]];
                    Vector3f p1 = vertex1.coords;
                    Vector3f p2 = vertex2.coords;
                    Vector3f p3 = vertex3.coords;
                    Vector3f v1 = p2 - p1;
                    Vector3f v2 = p3 - p1;
                    Vector3f n = v1.cross(v2);
                    n = n.normalized();
                    currFace.Q = generateQ(n, p1);*/
                   // currFace.normal = n;
                    faceMap[currF] = currFace;
                    break;
                }
            }
        }
    }
    vertexMap[newVert] = newVertex;
}

Matrix4f Mesh::generateQ(Vector3f n, Vector3f p) {
    Matrix4f Q;
    float a = n[0];
    float b = n[1];
    float c = n[2];
    float d = (-p).dot(n);
    Q << a*a, a*b, a*c, a*d,
         a*b, b*b, b*c, b*d,
         a*c, b*c, c*c, c*d,
         a*d, b*d, c*d, d*d;
    return Q;
}

void Mesh::simplify(int num) {
    generateSimplifyStructs();
    while(faceMap.size() > num) {
        edgeCollapse();
    }
    convertSimplifyStructBack();
}

std::shared_ptr<Shape> Mesh::makeMesh() {
    std::vector<float> shapedata = std::vector<float>();
    for(Vector3i face:_faces) {
        Vector3f p1 = _vertices[face[0]];
        Vector3f p2 = _vertices[face[1]];
        Vector3f p3 = _vertices[face[2]];
        Vector3f v1 = p2 - p1;
        Vector3f v2 = p3 - p1;
        Vector3f n = v1.cross(v2);
        n = n.normalized();
        Vector2f texture = Vector2f(0.f, 0.f);
        shapedata.push_back(p1[0]);
        shapedata.push_back(p1[1]);
        shapedata.push_back(p1[2]);
        shapedata.push_back(n[0]);
        shapedata.push_back(n[1]);
        shapedata.push_back(n[2]);
        shapedata.push_back(texture[0]);
        shapedata.push_back(texture[1]);

        shapedata.push_back(p2[0]);
        shapedata.push_back(p2[1]);
        shapedata.push_back(p2[2]);
        shapedata.push_back(n[0]);
        shapedata.push_back(n[1]);
        shapedata.push_back(n[2]);
        shapedata.push_back(texture[0]);
        shapedata.push_back(texture[1]);

        shapedata.push_back(p3[0]);
        shapedata.push_back(p3[1]);
        shapedata.push_back(p3[2]);
        shapedata.push_back(n[0]);
        shapedata.push_back(n[1]);
        shapedata.push_back(n[2]);
        shapedata.push_back(texture[0]);
        shapedata.push_back(texture[1]);
    }
    std::shared_ptr<Shape> shape = std::make_shared<Shape>(shapedata);
    return shape;
}

std::shared_ptr<Shape> Mesh::makeGround() {
    std::vector<float> shapedata = std::vector<float>();
    Vector3f bot1 = Vector3f(-3.f, 0.f, 3.f);
    Vector3f bot2 = Vector3f(-3.f, 0.f, -3.f);
    Vector3f bot3 = Vector3f(3.f, 0.f, 3.f);
    Vector3f bot4 = Vector3f(3.f, 0.f, -3.f);
    Vector3f botnorm = Vector3f(0.f, -1.f, 0.f);
    Vector2f texture = Vector2f(0.f, 0.f);
    shapedata.push_back(bot1[0]);
    shapedata.push_back(bot1[1]);
    shapedata.push_back(bot1[2]);
    shapedata.push_back(botnorm[0]);
    shapedata.push_back(botnorm[1]);
    shapedata.push_back(botnorm[2]);
    shapedata.push_back(texture[0]);
    shapedata.push_back(texture[1]);

    shapedata.push_back(bot3[0]);
    shapedata.push_back(bot3[1]);
    shapedata.push_back(bot3[2]);
    shapedata.push_back(botnorm[0]);
    shapedata.push_back(botnorm[1]);
    shapedata.push_back(botnorm[2]);
    shapedata.push_back(texture[0]);
    shapedata.push_back(texture[1]);

    shapedata.push_back(bot2[0]);
    shapedata.push_back(bot2[1]);
    shapedata.push_back(bot2[2]);
    shapedata.push_back(botnorm[0]);
    shapedata.push_back(botnorm[1]);
    shapedata.push_back(botnorm[2]);
    shapedata.push_back(texture[0]);
    shapedata.push_back(texture[1]);

    shapedata.push_back(bot2[0]);
    shapedata.push_back(bot2[1]);
    shapedata.push_back(bot2[2]);
    shapedata.push_back(botnorm[0]);
    shapedata.push_back(botnorm[1]);
    shapedata.push_back(botnorm[2]);
    shapedata.push_back(texture[0]);
    shapedata.push_back(texture[1]);

    shapedata.push_back(bot3[0]);
    shapedata.push_back(bot3[1]);
    shapedata.push_back(bot3[2]);
    shapedata.push_back(botnorm[0]);
    shapedata.push_back(botnorm[1]);
    shapedata.push_back(botnorm[2]);
    shapedata.push_back(texture[0]);
    shapedata.push_back(texture[1]);

    shapedata.push_back(bot4[0]);
    shapedata.push_back(bot4[1]);
    shapedata.push_back(bot4[2]);
    shapedata.push_back(botnorm[0]);
    shapedata.push_back(botnorm[1]);
    shapedata.push_back(botnorm[2]);
    shapedata.push_back(texture[0]);
    shapedata.push_back(texture[1]);
    std::shared_ptr<Shape> shape = std::make_shared<Shape>(shapedata);
    return shape;
}

void Mesh::loadFromFile(const std::string &filePath)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    QFileInfo info(QString(filePath.c_str()));
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err,
                                info.absoluteFilePath().toStdString().c_str(), (info.absolutePath().toStdString() + "/").c_str(), true);
    if(!err.empty()) {
        std::cerr << err << std::endl;
    }

    if(!ret) {
        std::cerr << "Failed to load/parse .obj file" << std::endl;
        return;
    }

    for(size_t s = 0; s < shapes.size(); s++) {
        size_t index_offset = 0;
        for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            unsigned int fv = shapes[s].mesh.num_face_vertices[f];

            Vector3i face;
            for(size_t v = 0; v < fv; v++) {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

		face[v] = idx.vertex_index;

            }
            _faces.push_back(face);

            index_offset += fv;
        }
    }
    for(size_t i = 0; i < attrib.vertices.size(); i += 3) {
	_vertices.emplace_back(attrib.vertices[i], attrib.vertices[i + 1], attrib.vertices[i + 2]);
    }
    std::cout << "Loaded " << _faces.size() << " faces and " << _vertices.size() << " vertices" << std::endl;
}

void Mesh::saveToFile(const std::string &filePath)
{
    std::ofstream outfile;
    outfile.open(filePath);

    // Write vertices
    for (size_t i = 0; i < _vertices.size(); i++)
    {
        const Vector3f &v = _vertices[i];
        outfile << "v " << v[0] << " " << v[1] << " " << v[2] << std::endl;
    }

    // Write faces
    for (size_t i = 0; i < _faces.size(); i++)
    {
        const Vector3i &f = _faces[i];
        outfile << "f " << (f[0]+1) << " " << (f[1]+1) << " " << (f[2]+1) << std::endl;
    }

    outfile.close();
}
