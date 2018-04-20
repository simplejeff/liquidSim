QT += core gui opengl

TARGET = cs195u_engine
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14
CONFIG += c++14

unix:!macx {
    LIBS += -lGLU
}
macx {
    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
    QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
    CONFIG += c++11
}
win32 {
    DEFINES += GLEW_STATIC
    LIBS += -lopengl32 -lglu32
}
linux {
    # fixes an issue with linux and vr libraries
    QMAKE_CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0
}

SOURCES += \
    libs/gl/textures/TextureParameters.cpp \
    libs/gl/textures/TextureParametersBuilder.cpp \
    libs/gl/util/FullScreenQuad.cpp \
    libs/glew-1.10.0/src/glew.c \
    src/main.cpp \
    src/mainwindow.cpp \
    src/view.cpp \
    src/viewformat.cpp \
    src/engine/graphics/FBO.cpp \
    src/engine/graphics/IBO.cpp \
    src/engine/graphics/VAO.cpp \
    src/engine/graphics/VBO.cpp \
    src/mesh.cpp \
    src/engine/graphics/camera.cpp \
    src/engine/graphics/depth_buffer.cpp \
    src/engine/graphics/font.cpp \
    src/engine/graphics/graphics.cpp \
    src/engine/graphics/graphics_debug.cpp \
    src/engine/graphics/kinect.cpp \
    src/engine/graphics/light.cpp \
    src/engine/graphics/material.cpp \
    src/engine/graphics/particle_system.cpp \
    src/engine/graphics/render_buffer.cpp \
    src/engine/graphics/resource_loader.cpp \
    src/engine/graphics/shader.cpp \
    src/engine/graphics/shape.cpp \
    src/engine/graphics/texture.cpp \
    src/engine/graphics/texture_1D.cpp \
    src/engine/graphics/texture_2D.cpp \
    src/engine/graphics/texture_3D.cpp \
    src/engine/graphics/VBO_attrib_marker.cpp \
    src/engine/entities/entity.cpp \
    src/engine/entities/colliders/collider_entity.cpp \
    src/engine/entities/colliders/cube_collider.cpp \
    src/engine/entities/colliders/plane_collider.cpp \
    src/engine/entities/colliders/sphere_collider.cpp \
    src/engine/entities/geometry/cube_entity.cpp \
    src/engine/entities/geometry/geom_entity.cpp \
    src/engine/entities/geometry/plane_entity.cpp \
    src/engine/entities/geometry/sphere.cpp \
    src/engine/entities/misc/transform_entity.cpp \
    src/engine/entities/physics/constraints/constraint.cpp \
    src/engine/entities/physics/constraints/density_constraint.cpp \
    src/engine/entities/physics/dynamics/dynamic_physics_entity.cpp \
    src/engine/entities/physics/dynamics/particle_system_entity.cpp \
    src/engine/entities/physics/forces/force.cpp \
    src/engine/entities/physics/forces/gravity_force.cpp \
    src/engine/entities/physics/kernels/kernel.cpp \
    src/engine/entities/physics/statics/static_physics_entity.cpp \
    src/engine/entities/physics/physics_entity.cpp \
    src/engine/entities/physics/kernels/poly6_kernel.cpp \
    src/engine/entities/renderables/cube_renderable.cpp \
    src/engine/entities/renderables/particle_system_renderable.cpp \
    src/engine/entities/renderables/plane_renderable.cpp \
    src/engine/entities/renderables/renderable_entity.cpp \
    src/engine/entities/renderables/sphere_renderable.cpp \
    src/engine/entities/world/particle_system_world_entity.cpp \
    src/engine/entities/world/world_entity.cpp \
    src/engine/system/collision/collision.cpp \
    src/engine/system/simulation/physics_system.cpp \
    src/engine/system/simulation/simulation.cpp \
    src/engine/system/simulation/solver.cpp \
    src/engine/scene/scene.cpp \
    src/engine/renderer/renderer.cpp \
    src/engine/entities/generators/particle_system_generator.cpp

HEADERS += \
    libs/gl/textures/TextureParameters.h \
    libs/gl/textures/TextureParametersBuilder.h \
    libs/gl/util/FullScreenQuad.h \
    libs/glew-1.10.0/include/GL/glew.h \
    libs/stb/stb_rect_pack.h \
    libs/stb/stb_truetype.h \
    src/mainwindow.h \
    src/view.h \
    src/viewformat.h \
    src/engine/graphics/FBO.h \
    src/engine/graphics/IBO.h \
    src/engine/graphics/VAO.h \
    src/engine/graphics/VBO.h \
    src/mesh.h \
    util/tiny_obj_loader.h \
    Eigen/Cholesky \
    Eigen/CholmodSupport \
    Eigen/Core \
    Eigen/Dense \
    Eigen/Eigen \
    Eigen/Eigenvalues \
    Eigen/Geometry \
    Eigen/Householder \
    Eigen/IterativeLinearSolvers \
    Eigen/Jacobi \
    Eigen/LU \
    Eigen/MetisSupport \
    Eigen/OrderingMethods \
    Eigen/PardisoSupport \
    Eigen/PaStiXSupport \
    Eigen/QR \
    Eigen/QtAlignedMalloc \
    Eigen/Sparse \
    Eigen/SparseCholesky \
    Eigen/SparseCore \
    Eigen/SparseLU \
    Eigen/SparseQR \
    Eigen/SPQRSupport \
    Eigen/StdDeque \
    Eigen/StdList \
    Eigen/StdVector \
    Eigen/SuperLUSupport \
    Eigen/SVD \
    Eigen/UmfPackSupport \
    Eigen/src/Cholesky/LDLT.h \
    Eigen/src/Cholesky/LLT.h \
    Eigen/src/Cholesky/LLT_LAPACKE.h \
    Eigen/src/CholmodSupport/CholmodSupport.h \
    Eigen/src/Core/arch/AltiVec/Complex.h \
    Eigen/src/Core/arch/AltiVec/MathFunctions.h \
    Eigen/src/Core/arch/AltiVec/PacketMath.h \
    Eigen/src/Core/arch/AVX/Complex.h \
    Eigen/src/Core/arch/AVX/MathFunctions.h \
    Eigen/src/Core/arch/AVX/PacketMath.h \
    Eigen/src/Core/arch/AVX/TypeCasting.h \
    Eigen/src/Core/arch/AVX512/MathFunctions.h \
    Eigen/src/Core/arch/AVX512/PacketMath.h \
    Eigen/src/Core/arch/CUDA/Complex.h \
    Eigen/src/Core/arch/CUDA/Half.h \
    Eigen/src/Core/arch/CUDA/MathFunctions.h \
    Eigen/src/Core/arch/CUDA/PacketMath.h \
    Eigen/src/Core/arch/CUDA/PacketMathHalf.h \
    Eigen/src/Core/arch/CUDA/TypeCasting.h \
    Eigen/src/Core/arch/Default/Settings.h \
    Eigen/src/Core/arch/NEON/Complex.h \
    Eigen/src/Core/arch/NEON/MathFunctions.h \
    Eigen/src/Core/arch/NEON/PacketMath.h \
    Eigen/src/Core/arch/SSE/Complex.h \
    Eigen/src/Core/arch/SSE/MathFunctions.h \
    Eigen/src/Core/arch/SSE/PacketMath.h \
    Eigen/src/Core/arch/SSE/TypeCasting.h \
    Eigen/src/Core/arch/ZVector/Complex.h \
    Eigen/src/Core/arch/ZVector/MathFunctions.h \
    Eigen/src/Core/arch/ZVector/PacketMath.h \
    Eigen/src/Core/functors/AssignmentFunctors.h \
    Eigen/src/Core/functors/BinaryFunctors.h \
    Eigen/src/Core/functors/NullaryFunctors.h \
    Eigen/src/Core/functors/StlFunctors.h \
    Eigen/src/Core/functors/TernaryFunctors.h \
    Eigen/src/Core/functors/UnaryFunctors.h \
    Eigen/src/Core/products/GeneralBlockPanelKernel.h \
    Eigen/src/Core/products/GeneralMatrixMatrix.h \
    Eigen/src/Core/products/GeneralMatrixMatrix_BLAS.h \
    Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h \
    Eigen/src/Core/products/GeneralMatrixMatrixTriangular_BLAS.h \
    Eigen/src/Core/products/GeneralMatrixVector.h \
    Eigen/src/Core/products/GeneralMatrixVector_BLAS.h \
    Eigen/src/Core/products/Parallelizer.h \
    Eigen/src/Core/products/SelfadjointMatrixMatrix.h \
    Eigen/src/Core/products/SelfadjointMatrixMatrix_BLAS.h \
    Eigen/src/Core/products/SelfadjointMatrixVector.h \
    Eigen/src/Core/products/SelfadjointMatrixVector_BLAS.h \
    Eigen/src/Core/products/SelfadjointProduct.h \
    Eigen/src/Core/products/SelfadjointRank2Update.h \
    Eigen/src/Core/products/TriangularMatrixMatrix.h \
    Eigen/src/Core/products/TriangularMatrixMatrix_BLAS.h \
    Eigen/src/Core/products/TriangularMatrixVector.h \
    Eigen/src/Core/products/TriangularMatrixVector_BLAS.h \
    Eigen/src/Core/products/TriangularSolverMatrix.h \
    Eigen/src/Core/products/TriangularSolverMatrix_BLAS.h \
    Eigen/src/Core/products/TriangularSolverVector.h \
    Eigen/src/Core/util/BlasUtil.h \
    Eigen/src/Core/util/Constants.h \
    Eigen/src/Core/util/DisableStupidWarnings.h \
    Eigen/src/Core/util/ForwardDeclarations.h \
    Eigen/src/Core/util/Macros.h \
    Eigen/src/Core/util/Memory.h \
    Eigen/src/Core/util/Meta.h \
    Eigen/src/Core/util/MKL_support.h \
    Eigen/src/Core/util/NonMPL2.h \
    Eigen/src/Core/util/ReenableStupidWarnings.h \
    Eigen/src/Core/util/StaticAssert.h \
    Eigen/src/Core/util/XprHelper.h \
    Eigen/src/Core/Array.h \
    Eigen/src/Core/ArrayBase.h \
    Eigen/src/Core/ArrayWrapper.h \
    Eigen/src/Core/Assign.h \
    Eigen/src/Core/Assign_MKL.h \
    Eigen/src/Core/AssignEvaluator.h \
    Eigen/src/Core/BandMatrix.h \
    Eigen/src/Core/Block.h \
    Eigen/src/Core/BooleanRedux.h \
    Eigen/src/Core/CommaInitializer.h \
    Eigen/src/Core/ConditionEstimator.h \
    Eigen/src/Core/CoreEvaluators.h \
    Eigen/src/Core/CoreIterators.h \
    Eigen/src/Core/CwiseBinaryOp.h \
    Eigen/src/Core/CwiseNullaryOp.h \
    Eigen/src/Core/CwiseTernaryOp.h \
    Eigen/src/Core/CwiseUnaryOp.h \
    Eigen/src/Core/CwiseUnaryView.h \
    Eigen/src/Core/DenseBase.h \
    Eigen/src/Core/DenseCoeffsBase.h \
    Eigen/src/Core/DenseStorage.h \
    Eigen/src/Core/Diagonal.h \
    Eigen/src/Core/DiagonalMatrix.h \
    Eigen/src/Core/DiagonalProduct.h \
    Eigen/src/Core/Dot.h \
    Eigen/src/Core/EigenBase.h \
    Eigen/src/Core/ForceAlignedAccess.h \
    Eigen/src/Core/Fuzzy.h \
    Eigen/src/Core/GeneralProduct.h \
    Eigen/src/Core/GenericPacketMath.h \
    Eigen/src/Core/GlobalFunctions.h \
    Eigen/src/Core/Inverse.h \
    Eigen/src/Core/IO.h \
    Eigen/src/Core/Map.h \
    Eigen/src/Core/MapBase.h \
    Eigen/src/Core/MathFunctions.h \
    Eigen/src/Core/MathFunctionsImpl.h \
    Eigen/src/Core/Matrix.h \
    Eigen/src/Core/MatrixBase.h \
    Eigen/src/Core/NestByValue.h \
    Eigen/src/Core/NoAlias.h \
    Eigen/src/Core/NumTraits.h \
    Eigen/src/Core/PermutationMatrix.h \
    Eigen/src/Core/PlainObjectBase.h \
    Eigen/src/Core/Product.h \
    Eigen/src/Core/ProductEvaluators.h \
    Eigen/src/Core/Random.h \
    Eigen/src/Core/Redux.h \
    Eigen/src/Core/Ref.h \
    Eigen/src/Core/Replicate.h \
    Eigen/src/Core/ReturnByValue.h \
    Eigen/src/Core/Reverse.h \
    Eigen/src/Core/Select.h \
    Eigen/src/Core/SelfAdjointView.h \
    Eigen/src/Core/SelfCwiseBinaryOp.h \
    Eigen/src/Core/Solve.h \
    Eigen/src/Core/SolverBase.h \
    Eigen/src/Core/SolveTriangular.h \
    Eigen/src/Core/StableNorm.h \
    Eigen/src/Core/Stride.h \
    Eigen/src/Core/Swap.h \
    Eigen/src/Core/Transpose.h \
    Eigen/src/Core/Transpositions.h \
    Eigen/src/Core/TriangularMatrix.h \
    Eigen/src/Core/VectorBlock.h \
    Eigen/src/Core/VectorwiseOp.h \
    Eigen/src/Core/Visitor.h \
    Eigen/src/Eigenvalues/ComplexEigenSolver.h \
    Eigen/src/Eigenvalues/ComplexSchur.h \
    Eigen/src/Eigenvalues/ComplexSchur_LAPACKE.h \
    Eigen/src/Eigenvalues/EigenSolver.h \
    Eigen/src/Eigenvalues/GeneralizedEigenSolver.h \
    Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h \
    Eigen/src/Eigenvalues/HessenbergDecomposition.h \
    Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h \
    Eigen/src/Eigenvalues/RealQZ.h \
    Eigen/src/Eigenvalues/RealSchur.h \
    Eigen/src/Eigenvalues/RealSchur_LAPACKE.h \
    Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h \
    Eigen/src/Eigenvalues/SelfAdjointEigenSolver_LAPACKE.h \
    Eigen/src/Eigenvalues/Tridiagonalization.h \
    Eigen/src/Geometry/arch/Geometry_SSE.h \
    Eigen/src/Geometry/AlignedBox.h \
    Eigen/src/Geometry/AngleAxis.h \
    Eigen/src/Geometry/EulerAngles.h \
    Eigen/src/Geometry/Homogeneous.h \
    Eigen/src/Geometry/Hyperplane.h \
    Eigen/src/Geometry/OrthoMethods.h \
    Eigen/src/Geometry/ParametrizedLine.h \
    Eigen/src/Geometry/Quaternion.h \
    Eigen/src/Geometry/Rotation2D.h \
    Eigen/src/Geometry/RotationBase.h \
    Eigen/src/Geometry/Scaling.h \
    Eigen/src/Geometry/Transform.h \
    Eigen/src/Geometry/Translation.h \
    Eigen/src/Geometry/Umeyama.h \
    Eigen/src/Householder/BlockHouseholder.h \
    Eigen/src/Householder/Householder.h \
    Eigen/src/Householder/HouseholderSequence.h \
    Eigen/src/IterativeLinearSolvers/BasicPreconditioners.h \
    Eigen/src/IterativeLinearSolvers/BiCGSTAB.h \
    Eigen/src/IterativeLinearSolvers/ConjugateGradient.h \
    Eigen/src/IterativeLinearSolvers/IncompleteCholesky.h \
    Eigen/src/IterativeLinearSolvers/IncompleteLUT.h \
    Eigen/src/IterativeLinearSolvers/IterativeSolverBase.h \
    Eigen/src/IterativeLinearSolvers/LeastSquareConjugateGradient.h \
    Eigen/src/IterativeLinearSolvers/SolveWithGuess.h \
    Eigen/src/Jacobi/Jacobi.h \
    Eigen/src/LU/arch/Inverse_SSE.h \
    Eigen/src/LU/Determinant.h \
    Eigen/src/LU/FullPivLU.h \
    Eigen/src/LU/InverseImpl.h \
    Eigen/src/LU/PartialPivLU.h \
    Eigen/src/LU/PartialPivLU_LAPACKE.h \
    Eigen/src/MetisSupport/MetisSupport.h \
    Eigen/src/misc/blas.h \
    Eigen/src/misc/Image.h \
    Eigen/src/misc/Kernel.h \
    Eigen/src/misc/lapack.h \
    Eigen/src/misc/lapacke.h \
    Eigen/src/misc/lapacke_mangling.h \
    Eigen/src/misc/RealSvd2x2.h \
    Eigen/src/OrderingMethods/Amd.h \
    Eigen/src/OrderingMethods/Eigen_Colamd.h \
    Eigen/src/OrderingMethods/Ordering.h \
    Eigen/src/PardisoSupport/PardisoSupport.h \
    Eigen/src/PaStiXSupport/PaStiXSupport.h \
    Eigen/src/plugins/ArrayCwiseBinaryOps.h \
    Eigen/src/plugins/ArrayCwiseUnaryOps.h \
    Eigen/src/plugins/BlockMethods.h \
    Eigen/src/plugins/CommonCwiseBinaryOps.h \
    Eigen/src/plugins/CommonCwiseUnaryOps.h \
    Eigen/src/plugins/MatrixCwiseBinaryOps.h \
    Eigen/src/plugins/MatrixCwiseUnaryOps.h \
    Eigen/src/QR/ColPivHouseholderQR.h \
    Eigen/src/QR/ColPivHouseholderQR_LAPACKE.h \
    Eigen/src/QR/CompleteOrthogonalDecomposition.h \
    Eigen/src/QR/FullPivHouseholderQR.h \
    Eigen/src/QR/HouseholderQR.h \
    Eigen/src/QR/HouseholderQR_LAPACKE.h \
    Eigen/src/SparseCholesky/SimplicialCholesky.h \
    Eigen/src/SparseCholesky/SimplicialCholesky_impl.h \
    Eigen/src/SparseCore/AmbiVector.h \
    Eigen/src/SparseCore/CompressedStorage.h \
    Eigen/src/SparseCore/ConservativeSparseSparseProduct.h \
    Eigen/src/SparseCore/MappedSparseMatrix.h \
    Eigen/src/SparseCore/SparseAssign.h \
    Eigen/src/SparseCore/SparseBlock.h \
    Eigen/src/SparseCore/SparseColEtree.h \
    Eigen/src/SparseCore/SparseCompressedBase.h \
    Eigen/src/SparseCore/SparseCwiseBinaryOp.h \
    Eigen/src/SparseCore/SparseCwiseUnaryOp.h \
    Eigen/src/SparseCore/SparseDenseProduct.h \
    Eigen/src/SparseCore/SparseDiagonalProduct.h \
    Eigen/src/SparseCore/SparseDot.h \
    Eigen/src/SparseCore/SparseFuzzy.h \
    Eigen/src/SparseCore/SparseMap.h \
    Eigen/src/SparseCore/SparseMatrix.h \
    Eigen/src/SparseCore/SparseMatrixBase.h \
    Eigen/src/SparseCore/SparsePermutation.h \
    Eigen/src/SparseCore/SparseProduct.h \
    Eigen/src/SparseCore/SparseRedux.h \
    Eigen/src/SparseCore/SparseRef.h \
    Eigen/src/SparseCore/SparseSelfAdjointView.h \
    Eigen/src/SparseCore/SparseSolverBase.h \
    Eigen/src/SparseCore/SparseSparseProductWithPruning.h \
    Eigen/src/SparseCore/SparseTranspose.h \
    Eigen/src/SparseCore/SparseTriangularView.h \
    Eigen/src/SparseCore/SparseUtil.h \
    Eigen/src/SparseCore/SparseVector.h \
    Eigen/src/SparseCore/SparseView.h \
    Eigen/src/SparseCore/TriangularSolver.h \
    Eigen/src/SparseLU/SparseLU.h \
    Eigen/src/SparseLU/SparseLU_column_bmod.h \
    Eigen/src/SparseLU/SparseLU_column_dfs.h \
    Eigen/src/SparseLU/SparseLU_copy_to_ucol.h \
    Eigen/src/SparseLU/SparseLU_gemm_kernel.h \
    Eigen/src/SparseLU/SparseLU_heap_relax_snode.h \
    Eigen/src/SparseLU/SparseLU_kernel_bmod.h \
    Eigen/src/SparseLU/SparseLU_Memory.h \
    Eigen/src/SparseLU/SparseLU_panel_bmod.h \
    Eigen/src/SparseLU/SparseLU_panel_dfs.h \
    Eigen/src/SparseLU/SparseLU_pivotL.h \
    Eigen/src/SparseLU/SparseLU_pruneL.h \
    Eigen/src/SparseLU/SparseLU_relax_snode.h \
    Eigen/src/SparseLU/SparseLU_Structs.h \
    Eigen/src/SparseLU/SparseLU_SupernodalMatrix.h \
    Eigen/src/SparseLU/SparseLU_Utils.h \
    Eigen/src/SparseLU/SparseLUImpl.h \
    Eigen/src/SparseQR/SparseQR.h \
    Eigen/src/SPQRSupport/SuiteSparseQRSupport.h \
    Eigen/src/StlSupport/details.h \
    Eigen/src/StlSupport/StdDeque.h \
    Eigen/src/StlSupport/StdList.h \
    Eigen/src/StlSupport/StdVector.h \
    Eigen/src/SuperLUSupport/SuperLUSupport.h \
    Eigen/src/SVD/BDCSVD.h \
    Eigen/src/SVD/JacobiSVD.h \
    Eigen/src/SVD/JacobiSVD_LAPACKE.h \
    Eigen/src/SVD/SVDBase.h \
    Eigen/src/SVD/UpperBidiagonalization.h \
    Eigen/src/UmfPackSupport/UmfPackSupport.h \
    src/engine/util/common_includes.h \
    src/engine/graphics/camera.h \
    src/engine/graphics/constants.h \
    src/engine/graphics/cube_data.h \
    src/engine/graphics/cylinder_data.h \
    src/engine/graphics/depth_buffer.h \
    src/engine/graphics/font.h \
    src/engine/graphics/graphics.h \
    src/engine/graphics/graphics_debug.h \
    src/engine/graphics/kinect.h \
    src/engine/graphics/light.h \
    src/engine/graphics/material.h \
    src/engine/graphics/particle_system.h \
    src/engine/graphics/render_buffer.h \
    src/engine/graphics/resource_loader.h \
    src/engine/graphics/shader.h \
    src/engine/graphics/shader_attrib_locations.h \
    src/engine/graphics/shape.h \
    src/engine/graphics/sphere_data.h \
    src/engine/graphics/texture.h \
    src/engine/graphics/texture_1D.h \
    src/engine/graphics/texture_2D.h \
    src/engine/graphics/texture_3D.h \
    src/engine/graphics/VBO_attrib_marker.h \
    src/engine/entities/entity.h \
    src/engine/entities/colliders/collider_entity.h \
    src/engine/entities/colliders/cube_collider.h \
    src/engine/entities/colliders/plane_collider.h \
    src/engine/entities/colliders/sphere_collider.h \
    src/engine/entities/generators/particle_system_generator.h \
    src/engine/entities/geometry/cube_entity.h \
    src/engine/entities/geometry/geom_entity.h \
    src/engine/entities/geometry/plane_entity.h \
    src/engine/entities/geometry/sphere.h \
    src/engine/entities/misc/transform_entity.h \
    src/engine/entities/physics/constraints/constraint.h \
    src/engine/entities/physics/constraints/density_constraint.h \
    src/engine/entities/physics/dynamics/dynamic_physics_entity.h \
    src/engine/entities/physics/dynamics/particle_system_entity.h \
    src/engine/entities/physics/forces/force.h \
    src/engine/entities/physics/forces/gravity_force.h \
    src/engine/entities/physics/kernels/kernel.h \
    src/engine/entities/physics/kernels/poly6_kernel.h \
    src/engine/entities/physics/statics/static_physics_entity.h \
    src/engine/entities/physics/physics_entity.h \
    src/engine/entities/renderables/cube_renderable.h \
    src/engine/entities/renderables/particle_system_renderable.h \
    src/engine/entities/renderables/plane_renderable.h \
    src/engine/entities/renderables/renderable_entity.h \
    src/engine/entities/renderables/sphere_renderable.h \
    src/engine/entities/world/particle_system_world_entity.h \
    src/engine/entities/world/world_entity.h \
    src/engine/system/collision/collision.h \
    src/engine/system/simulation/physics_system.h \
    src/engine/system/simulation/simulation.h \
    src/engine/system/simulation/solver.h \
    src/engine/util/fileloader.h \
    src/engine/scene/scene.h \
    src/engine/renderer/renderer.h

DEFINES += _USE_MATH_DEFINES
DEFINES += TIXML_USE_STL
DEFINES += GLM_SWIZZLE

FORMS += src/mainwindow.ui
INCLUDEPATH += src libs glm libraries libraries/openvr/headers libs/glew-1.10.0/include libraries/freeglut/include
DEPENDPATH += src libs glm libraries libraries/openvr/headers libs/glew-1.10.0/include libraries/freeglut/include 

RESOURCES += \
    res/shaders/shaders.qrc \
    res/fonts/fonts.qrc \
    res/images/images.qrc

OTHER_FILES += \
    res/images/grass.png \

DISTFILES += \
    res/shaders/shader.vert \
    res/shaders/shader.frag \
    res/shaders/particles.vert \
    res/shaders/particles.frag


# Don't add the -pg flag unless you know what you are doing. It makes QThreadPool freeze on Mac OS X
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON += -Waddress -Warray-bounds -Wc++0x-compat -Wchar-subscripts -Wformat\
                          -Wmain -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type \
                          -Wsequence-point -Wsign-compare -Wstrict-overflow=1 -Wswitch \
                          -Wtrigraphs -Wuninitialized -Wunused-label -Wunused-variable \
                          -Wvolatile-register-var -Wno-extra

QMAKE_CXXFLAGS += -g

defineTest(copyToDestdir) {
    files = $$1
    for(FILE, files) {
        CONFIG(debug, debug|release) {
            DDIR = $${OUT_PWD}/debug
        } else {
            DDIR = $${OUT_PWD}/release
        }

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g
        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }
    export(QMAKE_POST_LINK)
}

win32 {
    contains(QT_ARCH, i386) {
        message("32 bit build")
            LIBS += -L$$PWD/libraries/openvr/lib/win32/ -lopenvr_api
            copyToDestdir($$PWD/libraries/openvr/bin/win32/openvr_api.dll)
            LIBS += -L$$PWD/libraries/freeglut/lib/ -lfreeglut
            copyToDestdir($$PWD/libraries/freeglut/bin/freeglut.dll)
    } else {
        message("64 bit build")
            LIBS += -L$$PWD/libraries/openvr/lib/win64/ -lopenvr_api
            copyToDestdir($$PWD/libraries/openvr/bin/win64/openvr_api.dll)
            LIBS += -L$$PWD/libraries/freeglut/lib/x64/ -lfreeglut
            copyToDestdir($$PWD/libraries/freeglut/bin/x64/freeglut.dll)
    }
}

macx {
    LIBS += -L$$PWD/libraries/openvr/bin/osx32 -lopenvr_api
}

linux {

    LIBS += -L$$PWD/libraries/steam-runtime/amd64/lib/x86_64-linux-gnu
    LIBS += -L$$PWD/libraries/steam-runtime/amd64/lib
    LIBS += -L$$PWD/libraries/steam-runtime/amd64/usr/lib/x86_64-linux-gnu
    LIBS += -L$$PWD/libraries/steam-runtime/amd64/usr/lib
    LIBS += -L$$PWD/libraries/steam-runtime/i386/lib/i386-linux-gnu
    LIBS += -L$$PWD/libraries/steam-runtime/i386/lib
    LIBS += -L$$PWD/libraries/steam-runtime/i386/usr/lib/i386-linux-gnu
    LIBS += -L$$PWD/libraries/steam-runtime/i386/usr/lib
    LIBS += -L$$PWD/libraries/openvr/bin/linux64 -lopenvr_api
}
