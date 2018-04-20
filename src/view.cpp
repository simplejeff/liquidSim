#include "view.h"

#include "viewformat.h"
#include "engine/graphics/graphics_debug.h"
#include "engine/graphics/graphics.h"
#include "engine/graphics/camera.h"
#include "engine/graphics/material.h"
#include "src/engine/graphics/FBO.h"
#include "src/engine/graphics/texture_2D.h"
#include "gl/textures/TextureParametersBuilder.h"


#include <QApplication>
#include <QKeyEvent>
#include <iostream>
using namespace std;
using namespace glm;

View::View(QWidget *parent) : QGLWidget(ViewFormat(), parent),
    m_window(parent->parentWidget()),
    m_time(), m_timer(),
    m_captureMouse(true),
    m_fps(0), m_frameIndex(0),
    m_graphics(nullptr),
    m_camera(nullptr)
{
    /** SUPPORT CODE START **/

    // View needs all mouse move events, not just mouse drag events
    setMouseTracking(true);

    // Hide the cursor since this is a fullscreen app
    if(m_captureMouse) {
        QApplication::setOverrideCursor(Qt::BlankCursor);
    }
    else {
        QApplication::setOverrideCursor(Qt::ArrowCursor);
    }

    // View needs keyboard focus
    setFocusPolicy(Qt::StrongFocus);

    // The game loop is implemented using a timer
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(tick()));

    // Initialize frame times for last FRAMES_TO_AVERAGE frames
    for (int i = 0; i < FRAMES_TO_AVERAGE; i++) {
        m_frameTimes[i] = 0;
    }

    m_frameIndex = 0;

    /** SUPPORT CODE END **/
}

View::~View()
{
    delete(world_entity);
    /*(delete(plane);
    delete(plane_renderable);*/
    delete(cube);
    delete(cube_collider);
    delete(static_cube);
    delete(cube_renderable);
    delete(plane_world);
    delete(sim);
    delete(renderer);
    if(m_hmd) {

        /* Shutdown the VR system */
        vr::VR_Shutdown();
        m_hmd = NULL;
    }
}

void View::initializeGL()
{
    /** SUPPORT CODE START **/
    gravitySphere = glm::vec3(0.f, 2.f, 0.f);
    // Initialize graphics object
    m_graphics = Graphics::getGlobalInstance();

    // Enable depth testing, so that objects are occluded based on depth instead of drawing order.
    m_graphics->enableDepthTest();

    // Enable back-face culling, meaning only the front side of every face is rendered.
    // Also specify that the front face is represented by vertices in counterclockwise order (this is
    // the default).
    m_graphics->enableBackfaceCulling();

    // Enable alpha blending, so that materials with an alpha value < 1 are not totally opaque.
    m_graphics->enableBlendTest();

    // Disable stencil test for now (students may change this for final projects)
    m_graphics->disableStencilTest();

    m_near = 0.1f;
    m_far = 100.0f;

    initVR();

    // Start a timer that will try to get 60 frames per second (the actual
    // frame rate depends on the operating system and other running programs)
    m_time.start();
    m_timer.start(1000 / 60);

    // Center the mouse, which is explained more in mouseMoveEvent() below.
    // This needs to be done here because the mouse may be initially outside
    // the fullscreen window and will not automatically receive mouse move
    // events. This occurs if there are two monitors and the mouse is on the
    // secondary monitor.
    QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));

    /** SUPPORT CODE END **/

    // TODO (Lab 1): Initialize camera
    m_camera = std::make_shared<Camera>();
    m_camera->setEye(glm::vec3(0, 2, 5));
    m_camera->setLook(glm::vec3(0, 0, -1));
    m_graphics->setCamera(m_camera);
    // TODO (Lab 1): Initialize material
    Material myFirstMaterial;
    myFirstMaterial.color = glm::vec3(0, 1, 0);
    m_graphics->addMaterial("green", myFirstMaterial);
    Material mySecondMaterial;
    mySecondMaterial.color = glm::vec3(0, 0, 1);
    m_graphics->addMaterial("blue", mySecondMaterial);
    // TODO (Warmup 1): Initialize application
    keys["up"] = false;
    keys["down"] = false;
    keys["left"] = false;
    keys["right"] = false;
    keys["forward"]= false;
    keys["backward"] = false;
    keys["gleft"] = false;
    keys["gright"] = false;
    keys["gforward"]= false;
    keys["gbackward"] = false;
    keys["wireframe"] = false;
    keys["simulation"] = false;

    QString infile = "C:/Users/Jeff/Documents/graphics/mesh_visualiser/meshes/teapot.obj";
    //m_mesh.loadFromFile(infile.toStdString());
    //m_kinect = std::make_shared<Kinect>();

    //Add particle system
        world_entity = generator.GenerateCubeOfSpheres(Vector3f(-.5,-.5,.5),Vector3f(.5,-.5,.5),Vector3f(-.5,-.5,-.5),8,Vector3f(0,1,0),.5,.2,true);

    //add plane
    //Add base plane
        default_transform;
        default_transform.SetTranslate(Vector3f(0, 0, 0));
        float scale = 3;
       // plane = new PlaneEntity(&default_transform,Vector3f(-.5,-.5,.5)*scale,Vector3f(.5,-.5,.5)*scale,Vector3f(.5,-.5,-.5)*scale,Vector3f(-.5,-.5,-.5)*scale);

        /*PlaneCollider plane_collider(&plane);
        StaticPhysicsEntity static_plane(&plane_collider);
        static_plane.SetCoefficientRestitution(.9);
        static_plane.SetCoefficientFriction(.2);*/
       // plane_renderable = new PlaneRenderable(plane);
       // plane_renderable->SetColor(Vector3f(0,0,1));

        cube = new CubeEntity(&default_transform, 3.0f, Vector3f(-.5,-.5,.5)*scale,Vector3f(.5,-.5,.5)*scale,Vector3f(-.5,-.5,-.5)*scale);

        cube_collider = new CubeCollider(cube);
        static_cube = new StaticPhysicsEntity(cube_collider);
           static_cube->SetCoefficientRestitution(.9);
           static_cube->SetCoefficientFriction(.2);

        cube_renderable = new CubeRenderable(cube);
           cube_renderable->SetColor(Vector3f(1,0,1));


        plane_world = new WorldEntity(static_cube,cube_renderable);

           //Add objects to the scene
           scene.AddEntity(world_entity);
           scene.AddEntity(plane_world);

           //Create simulation
           system.AddForce(&gravity);
           sim = new Simulation(EULER,&system);
           sim->AddSceneEntities(scene);

           renderer = new Renderer(&scene);
}

void View::initVR() {
    std::cout << "is this called multiple " << std::endl;

    vr::EVRInitError error = vr::VRInitError_None;

   /* VR_Init will attempt to connect to a hmd attached
    * to the machine. The VRApplication_Scene parameter
    * specifies a 3D application that will be drawing an
    * environment. Be sure to call VR_Shutdown in the
    * destructor!
    */
    m_hmd = vr::VR_Init(&error, vr::VRApplication_Scene);

    /* ensure no errors occured during initialization */
    if (error != vr::VRInitError_None) {
        m_hmd = nullptr;
        string message = vr::VR_GetVRInitErrorAsEnglishDescription(error);
        std::cout << "Unable to init VR" + message;
        return;
    }


    /*
     * Provides the game with the minimum size that it should use for
     * its offscreen render target to minimize pixel stretching.
     * This size is matched with the projection matrix and distortion
     * function and will change from display to display depending on
     * resolution, distortion, and field of view.
     */
    m_hmd->GetRecommendedRenderTargetSize(&m_eyeWidth, &m_eyeHeight);


    /* VRCompositor simplifies the process of displaying images
     * by taking care of distortion, prediction, synchronization
     * and other subtle rendering issues.
     */
    if (!vr::VRCompositor()) {
        string message = "Compositor initialization failed. See log file for details";
        std::cout << "Unable to init VR" + message;
    }

   /* if running on a windows enviorment, we need
    * to initialize VRSystem to use the MinGW compiler
    * instead of the default.
    */
    #if defined(__GNUC__) && defined(_WIN32)
        vr::IVRSystem *vr_sys = vr::VRSystem();
        typedef void (vr::IVRSystem::*FuncPtr1)(vr::HmdMatrix34_t *, vr::EVREye);
        FuncPtr1 get_eye_to_head_transform = reinterpret_cast<FuncPtr1>(&vr::IVRSystem::GetEyeToHeadTransform);
        typedef void (vr::IVRSystem::*FuncPtr2)(vr::HmdMatrix44_t *, vr::EVREye, float, float);
        FuncPtr2 get_projection = reinterpret_cast<FuncPtr2>(&vr::IVRSystem::GetProjectionMatrix);

        vr::HmdMatrix34_t leftView, rightView;
        (vr_sys->*get_eye_to_head_transform)(&leftView, vr::Eye_Left);
        (vr_sys->*get_eye_to_head_transform)(&rightView, vr::Eye_Right);

        m_leftPose = vrMatrixToGlm(leftView);
        m_rightPose = vrMatrixToGlm(rightView);

        vr::HmdMatrix44_t leftProj, rightProj;
        (vr_sys->*get_projection)(&leftProj, vr::Eye_Left, m_near, m_far);
        (vr_sys->*get_projection)(&rightProj, vr::Eye_Right, m_near, m_far);

        m_leftProjection = vrMatrixToGlm(leftProj);
        m_rightProjection = vrMatrixToGlm(rightProj);

    # else
        /* Instead of [Model * View * Projection]
         * The VR equivalent is [Model * View * Eye * Projection]
         *
         * Normally View and Eye will be multiplied together and
         * treated as View in your application.
         */
        m_leftPose = vrMatrixToGlm(m_hmd->GetEyeToHeadTransform(vr::Eye_Left));
        m_rightPose = vrMatrixToGlm(m_hmd->GetEyeToHeadTransform(vr::Eye_Right));

        m_leftProjection = vrMatrixToGlm(m_hmd->GetProjectionMatrix(vr::Eye_Left, m_near, m_far));
        m_rightProjection = vrMatrixToGlm(m_hmd->GetProjectionMatrix(vr::Eye_Right, m_near, m_far));
    #endif

        /* VR frame buffers for each eye*/
        m_leftEyeBuffer = std::make_shared<FBO>(1,FBO::DEPTH_STENCIL_ATTACHMENT::DEPTH_ONLY, m_eyeWidth, m_eyeHeight,
                                                TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE,
                                                TextureParameters::FILTER_METHOD::LINEAR,
                                                GL_UNSIGNED_BYTE);
        m_rightEyeBuffer = std::make_shared<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::DEPTH_ONLY, m_eyeWidth, m_eyeHeight,
                                                 TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE,
                                                 TextureParameters::FILTER_METHOD::LINEAR,
                                                 GL_UNSIGNED_BYTE);
}

void View::paintGL()
{
    /** SUPPORT CODE START **/
    if (m_hmd) {
        m_camera->setVR(true);
        vr::IVRSystem *vr_sys = vr::VRSystem();
        typedef void (vr::IVRSystem::*FuncPtr1)(vr::HmdMatrix34_t *, vr::EVREye);
        FuncPtr1 get_eye_to_head_transform = reinterpret_cast<FuncPtr1>(&vr::IVRSystem::GetEyeToHeadTransform);
        typedef void (vr::IVRSystem::*FuncPtr2)(vr::HmdMatrix44_t *, vr::EVREye, float, float);
        FuncPtr2 get_projection = reinterpret_cast<FuncPtr2>(&vr::IVRSystem::GetProjectionMatrix);

        vr::HmdMatrix34_t leftView, rightView;
        (vr_sys->*get_eye_to_head_transform)(&leftView, vr::Eye_Left);
        (vr_sys->*get_eye_to_head_transform)(&rightView, vr::Eye_Right);

        m_leftPose = vrMatrixToGlm(leftView);
        m_rightPose = vrMatrixToGlm(rightView);

        vr::HmdMatrix44_t leftProj, rightProj;
        (vr_sys->*get_projection)(&leftProj, vr::Eye_Left, m_near, m_far);
        (vr_sys->*get_projection)(&rightProj, vr::Eye_Right, m_near, m_far);

        m_leftProjection = vrMatrixToGlm(leftProj);
        m_rightProjection = vrMatrixToGlm(rightProj);

        /* render the current location of the controllers */
        obtainControllerPositions();

        /* Left Eye */
        m_leftEyeBuffer->bind();
        glViewport(0, 0, m_eyeWidth, m_eyeHeight);
        renderEye(vr::Eye_Left);
        m_leftEyeBuffer->unbind();

        /* Right Eye */
        m_rightEyeBuffer->bind();
        glViewport(0, 0, m_eyeWidth, m_eyeHeight);
        renderEye(vr::Eye_Right);
        m_rightEyeBuffer->unbind();

        /* Submit frames to the Compositor */
        vr::Texture_t leftEyeTexture = {(void*) m_leftEyeBuffer->getColorAttachment(0).id(), vr::TextureType_OpenGL, vr::ColorSpace_Gamma};
        /* Updated scene texture to display for left eye*/
        vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);

        vr::Texture_t rightEyeTexture = {(void*) m_rightEyeBuffer->getColorAttachment(0).id(), vr::TextureType_OpenGL, vr::ColorSpace_Gamma};
        /* Updated scene texture to display for right eye*/
        vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

    } else {
        m_camera->setVR(false);
        draw();
    }
}

void View::draw() {
    m_graphics->setClearColor(glm::vec3(0, 0, 0));
    m_graphics->clearScreen(Graphics::CLEAR_FLAG::ALL);
    m_graphics->clearShader();
    m_graphics->setDefaultMaterial();

    /** SUPPORT CODE END **/
    // TODO (Lab 1): Call your game rendering code here
    m_graphics->clearTransform();
    //m_graphics->setMaterial("green");

    //    m_graphics->clearTransform();
    //    m_graphics->translate(gravitySphere);
    //    m_graphics->scale(glm::vec3(.1f, .1f, .1f));
    //    m_graphics->drawShape("sphere");
    m_graphics->clearTransform();
    renderer->Render(m_graphics);
    #if GRAPHICS_DEBUG_LEVEL > 0
        m_graphics->printDebug();
        m_graphics->printShaderDebug();
        m_graphics->printFBODebug();
    #endif

        /** SUPPORT CODE END **/
}

void View::renderEye(vr::EVREye eye) {
    glm::mat4x4 p = eye == vr::Eye_Left ? m_leftProjection : m_rightProjection;
    glm::mat4x4 v = (eye == vr::Eye_Right ? m_leftPose : m_rightPose) * m_hmdPose;
    m_camera->setView(v);
    m_camera->setProj(p);
    draw();
}

void View::obtainControllerPositions() {

    /* don't draw controllers if somebody else has input focus */
    if(m_hmd->IsInputFocusCapturedByAnotherProcess() )
        return;

    /* enumerate all controllers */
    for (vr::TrackedDeviceIndex_t trackedDeviceIndex = vr::k_unTrackedDeviceIndex_Hmd + 1;
         trackedDeviceIndex < vr::k_unMaxTrackedDeviceCount;
         trackedDeviceIndex++) {

        /* controller not connected, ignore it */
        if (!m_hmd->IsTrackedDeviceConnected(trackedDeviceIndex))
            continue;

        /* not a hand controller, ignore it */
        if(m_hmd->GetTrackedDeviceClass(trackedDeviceIndex) != vr::TrackedDeviceClass_Controller)
            continue;


        /* controller position invalid, ignore it */
        if(!m_trackedDevicePose[trackedDeviceIndex].bPoseIsValid)
            continue;

        /* controller transformation matrix, use it as needed */
        const glm::mat4 &mat = m_mat4DevicePose[trackedDeviceIndex];
    }
}



void View::updatePoses() {

    /* You can update your head and hand positions here */
    if(m_hmd) {
        vr::VRCompositor()->WaitGetPoses(m_trackedDevicePose, vr::k_unMaxTrackedDeviceCount, nullptr, 0);

        if (m_trackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid) {
            glm::mat4 h = vrMatrixToGlm(m_trackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].mDeviceToAbsoluteTracking);
            m_hmdPose = glm::inverse(h);
        }
    }
}

void View::resizeGL(int w, int h)
{
    /** SUPPORT CODE START **/

    m_graphics->setViewport(glm::vec2(0, 0), glm::vec2(w, h));

    /** SUPPORT CODE END **/

    // TODO (Lab 1): Resize the camera
    m_camera->setScreenSize(glm::vec2(w, h));

    // TODO (Warmup 1): Resize the application
}

void View::mousePressEvent(QMouseEvent *event)
{
    // TODO (Warmup 1): Handle mouse press events
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    /** SUPPORT CODE START **/

    // This starter code implements mouse capture, which gives the change in
    // mouse position since the last mouse movement. The mouse needs to be
    // recentered after every movement because it might otherwise run into
    // the edge of the screen, which would stop the user from moving further
    // in that direction. Note that it is important to check that deltaX and
    // deltaY are not zero before recentering the mouse, otherwise there will
    // be an infinite loop of mouse move events.
    int deltaX = event->x() - width() / 2;
    int deltaY = event->y() - height() / 2;

    if(m_captureMouse) {

        if (deltaX == 0 && deltaY == 0) {
            return;
        }

        QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
    }

    /** SUPPORT CODE END **/

    // TODO (Lab 1): Handle mouse movements here
    m_camera->rotate(-deltaX / 100.f, -deltaY / 100.f);
    // TODO (Warmup 1): Handle mouse movements here
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    // TODO (Warmup 1): Handle mouse release here
}

void View::wheelEvent(QWheelEvent *event)
{
    // TODO (Warmup 1): Handle mouse wheel events here
}

void View::keyPressEvent(QKeyEvent *event)
{
    /** SUPPORT CODE START **/

    // Don't remove this -- helper code for key repeat events
    if(event->isAutoRepeat()) {
        keyRepeatEvent(event);
        return;
    }

    // Feel free to remove this
    if (event->key() == Qt::Key_Escape) QApplication::quit();

    /** SUPPORT CODE END **/

    // TODO (Lab 1): Handle keyboard presses here
    // strafe movement
    if(event->key() == Qt::Key_W) {
        keys["forward"] = true;
    }
    if(event->key() == Qt::Key_S) {
        keys["backward"] = true;
    }
    if(event->key() == Qt::Key_A) {
        keys["left"] = true;
    }
    if(event->key() == Qt::Key_D) {
        keys["right"] = true;
    }
    if(event->key() == Qt::Key_Z) {
        keys["up"] = true;
    }
    if(event->key() == Qt::Key_X) {
        keys["down"] = true;
    }
    if(event->key() == Qt::Key_I) {
        keys["gforward"] = true;
    }
    if(event->key() == Qt::Key_K) {
        keys["gbackward"] = true;
    }
    if(event->key() == Qt::Key_J) {
        keys["gleft"] = true;
    }
    if(event->key() == Qt::Key_L) {
        keys["gright"] = true;
    }
    if(event->key() == Qt::Key_P) {
        keys["simulation"] = true;
    }
    // TODO (Warmup 1): Handle keyboard presses here
}

void View::keyRepeatEvent(QKeyEvent *event)
{
    // TODO (Warmup 1): Handle key repeats (happens when holding down keys)
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    /** SUPPORT CODE START **/

    // Don't remove this -- helper code for key repeat events
    if(event->isAutoRepeat()) {
        return;
    }

    /** SUPPORT CODE END **/

    // TODO (Warmup 1): Handle key releases
    if(event->key() == Qt::Key_W) {
        keys["forward"] = false;
    }
    if(event->key() == Qt::Key_S) {
        keys["backward"] = false;
    }
    if(event->key() == Qt::Key_A) {
        keys["left"] = false;
    }
    if(event->key() == Qt::Key_D) {
        keys["right"] = false;
    }
    if(event->key() == Qt::Key_Z) {
        keys["up"] = false;
    }
    if(event->key() == Qt::Key_X) {
        keys["down"] = false;
    }
    if(event->key() == Qt::Key_I) {
        keys["gforward"] = false;
    }
    if(event->key() == Qt::Key_K) {
        keys["gbackward"] = false;
    }
    if(event->key() == Qt::Key_J) {
        keys["gleft"] = false;
    }
    if(event->key() == Qt::Key_L) {
        keys["gright"] = false;
    }
    if(event->key() == Qt::Key_M) {
        keys["wireframe"] = !keys["wireframe"];
    }
    if(event->key() == Qt::Key_P) {
        keys["simulation"] = false;
    }
}

void View::updateInputs() {

    /* don't render when not using headset */
    if(!m_hmd) {
        return;
    }
    /* process controller inputs */
    for(vr::TrackedDeviceIndex_t deviceIndex = 0;
        deviceIndex < vr::k_unMaxTrackedDeviceCount;
        deviceIndex++) {

        vr::VRControllerState_t state;
        if(m_hmd->GetControllerState(deviceIndex, &state, sizeof(state))) {
            m_activeTrackedDevice[deviceIndex] = (state.ulButtonPressed == 0);

            if (state.ulButtonPressed) {
               std::cout << "controller pressed! " << std::to_string(deviceIndex) << std::endl; /* controller button is presses */
            }

            if (state.ulButtonTouched) {
                /* controller button is being touched */
            }
        }
    }

    for (unsigned int deviceIndex = 0; deviceIndex < vr::k_unMaxTrackedDeviceCount; deviceIndex++) {
        if (m_trackedDevicePose[deviceIndex].bPoseIsValid) {
            /* update the controller's position matrix */
            m_mat4DevicePose[deviceIndex] = vrMatrixToGlm(m_trackedDevicePose[deviceIndex].mDeviceToAbsoluteTracking);
             //  the numbering of the index of left and right controller might change based on the machine ur using
            if(deviceIndex == 2) {
                glm::vec3 leftPos = glm::vec3(0.f);
                leftPos.x = (m_mat4DevicePose[deviceIndex])[3][0];
                leftPos.y = (m_mat4DevicePose[deviceIndex])[3][1];
                leftPos.z = (m_mat4DevicePose[deviceIndex])[3][2];
                //leftPos of controller
            }
            if(deviceIndex == 3) {
                glm::vec3 rightPos = glm::vec3(0.f);
                rightPos.x = (m_mat4DevicePose[deviceIndex])[3][0];
                rightPos.y = (m_mat4DevicePose[deviceIndex])[3][1];
                rightPos.z = (m_mat4DevicePose[deviceIndex])[3][2];
                //rightPos of controller
            }
        } else {
            /* invalid position, don't track */
            m_activeTrackedDevice[deviceIndex] = false;
        }
    }
}

void View::tick()
{
    /** SUPPORT CODE START **/

    // Get the number of seconds since the last tick (variable update rate)
    float seconds = m_time.restart() * 0.001f;

    m_frameTimes[m_frameIndex] = seconds;
    m_frameIndex = (m_frameIndex + 1) % FRAMES_TO_AVERAGE;
    m_fps = 0;
    for (int i = 0; i < FRAMES_TO_AVERAGE; i++) {
        m_fps += m_frameTimes[i];
    }
    m_fps /= FRAMES_TO_AVERAGE;
    m_fps = 1.f / m_fps;

    // Display fps
    QString title = "CS195U Engine";

    m_window->setWindowTitle(title + ", FPS: " + QString::number(m_fps, 'f', 3));

    /** SUPPORT CODE END **/


    // TODO (Warmup 1): Implement the game update here
    glm::vec3 look = m_camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z)); // forward-backward
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);
    glm::vec3 up = glm::vec3(0, 1.f, 0);
    if(keys["forward"]) {
        m_camera->translate(dir*seconds);
    }
    if(keys["backward"]) {
        m_camera->translate(-dir*seconds);
    }
    if(keys["left"]) {
        m_camera->translate(perp*seconds);
    }
    if(keys["right"]) {
        m_camera->translate(-perp*seconds);
    }
    if(keys["up"]) {
        m_camera->translate(up*seconds);
    }
    if(keys["down"]) {
        m_camera->translate(-up*seconds);
    }
  /*  glm::vec3 gForward = glm::vec3(0, 0, -1.f);
    glm::vec3 gLeft = glm::vec3(-1.f, 0, 0);
   if(keys["gforward"]) {
        gravitySphere += gForward*seconds;
    }
    if(keys["gbackward"]) {
        gravitySphere -= gForward*seconds;
    }
    if(keys["gleft"]) {
        gravitySphere += gLeft*seconds;
    }
    if(keys["gright"]) {
        gravitySphere -= gLeft*seconds;
    }*/
    if(keys["wireframe"]) {
        m_graphics->setWireframe(true);
    } else {
        m_graphics->setWireframe(false);
    }
    if(keys["simulation"]) {
        sim->Update(seconds);
    }
    /** SUPPORT CODE START **/
    /* VR updates */
    updatePoses();
    updateInputs();

    // Flag this view for repainting (Qt will call paintGL() soon after)
    update();

    /** SUPPORT CODE END **/
}

/* File dialog */
void View::fileOpen() {
}
