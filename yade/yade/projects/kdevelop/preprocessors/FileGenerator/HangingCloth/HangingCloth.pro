# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./preprocessors/FileGenerator/HangingCloth
# Target is a library:  

LIBS += -lMesh2D \
        -lSerialization \
        -lSAPCollider \
        -lAABB \
        -lSphere \
        -lClosestFeatures \
        -lSimpleSpringDynamicEngine \
        -lMassSpringBody2RigidBodyDynamicEngine \
        -lMath \
        -lBody \
        -lEngine \
        -lInteraction \
        -lMultiMethods \
        -lPersistentSAPCollider \
        -lSpringGeometry \
        -lSpringPhysics \
        -lExplicitMassSpringDynamicEngine \
        -lInteractionSphere \
        -lInteractionDescriptionSet2AABBFunctor \
        -lRigidBodyParameters \
        -lParticleSetParameters \
        -lActionMomentumDamping \
        -lActionForceDamping \
        -lSDECDynamicEngine \
        -lActionReset \
        -lSDECLinearContactModel \
        -lSDECParameters \
        -lSDECPermanentLink \
        -lSDECPermanentLinkPhysics \
        -lBox \
        -lInteractionBox \
        -rdynamic 
INCLUDEPATH = $(YADEINCLUDEPATH) 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../plugins/Body/GeometricalModel/Mesh2D/$(YADEDYNLIBPATH) \
               ../../../toolboxes/Libraries/Serialization/$(YADEDYNLIBPATH) \
               ../../../plugins/Interaction/BroadInteractor/SAPCollider/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/BoundingVolume/AABB/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/GeometricalModel/Sphere/$(YADEDYNLIBPATH) \
               ../../../plugins/Interaction/InteractionGeometry/ClosestFeatures/$(YADEDYNLIBPATH) \
               ../../../plugins/Engine/DynamicEngine/SimpleSpringDynamicEngine/$(YADEDYNLIBPATH) \
               ../../../plugins/Engine/DynamicEngine/MassSpringBody2RigidBodyDynamicEngine/$(YADEDYNLIBPATH) \
               ../../../toolboxes/Libraries/Math/$(YADEDYNLIBPATH) \
               ../../../yade/Body/Body/$(YADEDYNLIBPATH) \
               ../../../yade/Engine/$(YADEDYNLIBPATH) \
               ../../../yade/Interaction/Interaction/$(YADEDYNLIBPATH) \
               ../../../toolboxes/Libraries/MultiMethods/$(YADEDYNLIBPATH) \
               ../../../plugins/Interaction/BroadInteractor/PersistentSAPCollider/$(YADEDYNLIBPATH) \
               ../../../plugins/Interaction/InteractionGeometry/SpringGeometry/$(YADEDYNLIBPATH) \
               ../../../plugins/Interaction/InteractionPhysics/SpringPhysics/$(YADEDYNLIBPATH) \
               ../../../plugins/Engine/DynamicEngine/ExplicitMassSpringDynamicEngine/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/InteractionDescription/InteractionSphere/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/BoundingVolumeFunctor/InteractionDescriptionSet2AABBFunctor/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/BodyPhysicalParameters/RigidBodyParameters/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/BodyPhysicalParameters/ParticleSetParameters/$(YADEDYNLIBPATH) \
               ../../../plugins/Engine/ActionDampingFunctor/ActionMomentumDamping/$(YADEDYNLIBPATH) \
               ../../../plugins/Engine/ActionDampingFunctor/ActionForceDamping/$(YADEDYNLIBPATH) \
               ../../../plugins/Engine/DynamicEngine/SDECDynamicEngine/$(YADEDYNLIBPATH) \
               ../../../plugins/Engine/Action/ActionReset/$(YADEDYNLIBPATH) \
               ../../../plugins/Interaction/InteractionPhysicsFunctor/SDECContactPhysics/SDECLinearContactModel/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/BodyPhysicalParameters/SDECParameters/$(YADEDYNLIBPATH) \
               ../../../plugins/Interaction/InteractionGeometry/SDECPermanentLink/$(YADEDYNLIBPATH) \
               ../../../plugins/Interaction/InteractionPhysics/SDECPermanentLinkPhysics/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/GeometricalModel/Box/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/InteractionDescription/InteractionBox/$(YADEDYNLIBPATH) \
               ../../../plugins/Geometry/GeometricalModel/Mesh2D/$(YADEDYNLIBPATH) \
               ../../../plugins/Geometry/BoundingVolume/AABB/$(YADEDYNLIBPATH) \
               ../../../plugins/Geometry/GeometricalModel/Sphere/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/MassSpringBody/$(YADEDYNLIBPATH) \
               ../../../plugins/Geometry/InteractionDescription/InteractionSphere/$(YADEDYNLIBPATH) \
               ../../../plugins/Geometry/BoundingVolumeFunctor/InteractionDescriptionSet2AABBFunctor/$(YADEDYNLIBPATH) \
               ../../../yade/Body/$(YADEDYNLIBPATH) \
               ../../../yade/Geometry/$(YADEDYNLIBPATH) \
               ../../../yade/Interaction/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/BodyPhysicalParameters/RigidBody/$(YADEDYNLIBPATH) \
               ../../../plugins/Geometry/InteractionGeometry/InteractionSphere/$(YADEDYNLIBPATH) \
               ../../../plugins/Geometry/BoundingVolumeFactory/CollisionGeometrySet2AABBFactory/$(YADEDYNLIBPATH) \
               ../../../plugins/Geometry/CollisionGeometry/InteractionSphere/$(YADEDYNLIBPATH) \
               ../../../plugins/Engine/DynamicEngine/ParticleBallisticEngine/$(YADEDYNLIBPATH) \
               ../../../plugins/Body/RigidBody/$(YADEDYNLIBPATH) \
               $(YADEDYNLIBPATH) 
QMAKE_CXXFLAGS_RELEASE += -lpthread \
                          -pthread 
QMAKE_CXXFLAGS_DEBUG += -lpthread \
                        -pthread 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += HangingCloth.hpp 
SOURCES += HangingCloth.cpp 
