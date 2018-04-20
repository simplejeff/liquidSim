#ifndef VIEW_H
#define VIEW_H

#include "engine/util/common_includes.h"
#include "mesh.h"
#include "engine/graphics/shape.h"
#include "GL/glew.h"
#include <qgl.h>
#include <QGLWidget>
#include <QTime>
#include <QTimer>
#include <memory>
#include <openvr.h>
#include "glm/glm.hpp"
#include "engine/entities/physics/statics/static_physics_entity.h"
#include "engine/entities/geometry/sphere.h"
#include "engine/entities/renderables/sphere_renderable.h"
#include "engine/entities/colliders/sphere_collider.h"
#include "engine/entities/physics/dynamics/particle_system_entity.h"
#include "engine/entities/world/particle_system_world_entity.h"
#include "engine/entities/geometry/plane_entity.h"
#include "engine/entities/generators/particle_system_generator.h"
#include "engine/entities/geometry/cube_entity.h"
#include "engine/entities/renderables/cube_renderable.h"
#include "engine/entities/colliders/cube_collider.h"
#include "engine/entities/physics/forces/gravity_force.h"
#include "engine/entities/renderables/plane_renderable.h"
#include "engine/system/simulation/simulation.h"
#include "engine/renderer/renderer.h"

#include "src/engine/graphics/FBO.h"
#include "src/engine/graphics/particle_system.h"
#include "src/engine/graphics/kinect.h"
class Graphics;
class Camera;

/**
 * This is similar to your "CS1971FrontEnd" class. Here you will receive all of the input events
 * to forward to your game.
 *
 * @brief The View class
 */
class View : public QGLWidget
{
    Q_OBJECT

public:
    View(QWidget *parent);
    ~View();

private:
    static const int FRAMES_TO_AVERAGE = 30;
    void wheelEvent(QWheelEvent *event);
    void keyRepeatEvent(QKeyEvent *event);
    ParticleSystemGenerator generator;
    ParticleSystemWorldEntity *world_entity;
    TransformEntity default_transform;
    PlaneEntity *plane;
    PlaneRenderable *plane_renderable;
    CubeEntity *cube;
    CubeCollider *cube_collider;
    StaticPhysicsEntity *static_cube;
    CubeRenderable *cube_renderable;
    WorldEntity *plane_world;
    Scene scene;
    PhysicsSystem system;
    GravityForce gravity;
    Simulation *sim;
    Renderer *renderer;
    Mesh m_mesh;
    std::shared_ptr<Shape> m_shape;
    std::shared_ptr<Shape> m_ground;
    glm::vec3 gravitySphere;
   // std::shared_ptr<Kinect> m_kinect;
    QWidget *m_window;
    QTime m_time;
    QTimer m_timer;
    bool m_captureMouse;
    std::map<QString, bool> keys;
    float m_fps;
    int m_frameIndex;
    float m_frameTimes[FRAMES_TO_AVERAGE];
    Graphics* m_graphics;

    // TODO (Warmup 1): You might want to remove this after completing the lab
    std::shared_ptr<Camera> m_camera;

    float m_near, m_far;
    // TODO (Warmup 1): Add an application variable to the View class
    // head mounted display (goggles)
    vr::IVRSystem *m_hmd;

    // position of the tracking devices (hand controllers and goggles)
    vr::TrackedDevicePose_t m_trackedDevicePose[vr::k_unMaxTrackedDeviceCount];
    glm::mat4 m_mat4DevicePose [vr::k_unMaxTrackedDeviceCount];
    bool m_activeTrackedDevice[vr::k_unMaxTrackedDeviceCount];

    // size of each eye "screen"
    uint32_t m_eyeWidth, m_eyeHeight;

    // view matrices for rendering the vr scene
    glm::mat4 m_leftProjection, m_leftPose;
    glm::mat4 m_rightProjection, m_rightPose;
    glm::mat4 m_hmdPose;

    // vr eye frame buffers
    std::shared_ptr<FBO> m_leftEyeBuffer;
    std::shared_ptr<FBO> m_rightEyeBuffer;
    bool createFrameBuffer(int nWidth, int nHeight, FBO &eyeFBO);

    // initialized openGL
    void initializeGL();

    // initialized the vr system
    void initVR();
    void paintGL();

    // render the scene for a given eye
    void renderEye(vr::EVREye eye);
    void resizeGL(int w, int h);

    // hand controllers pos
    void obtainControllerPositions();

    // updates the position of the hmd
    void updatePoses();

    // updates current controller inputs
    void updateInputs();

    // mouse and keyboard events
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    // draw event
    void draw();

    // converts a vr hmd matrix to a glm::mat4
    glm::mat4 vrMatrixToGlm(const vr::HmdMatrix34_t &mat) {
        return glm::mat4x4(
            mat.m[0][0], mat.m[1][0], mat.m[2][0], 0.0f,
            mat.m[0][1], mat.m[1][1], mat.m[2][1], 0.0f,
            mat.m[0][2], mat.m[1][2], mat.m[2][2], 0.0f,
            mat.m[0][3], mat.m[1][3], mat.m[2][3], 1.0f
        );
    }

    // converts a vr hmd matrix to a glm::mat4
    glm::mat4 vrMatrixToGlm(const vr::HmdMatrix44_t &mat) {
        return glm::mat4x4(
            mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
            mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
            mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
            mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
        );
    }

public slots:
    void fileOpen();

private slots:
    void tick();
};

#endif // VIEW_H

