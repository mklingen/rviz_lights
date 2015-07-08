#ifndef MESH2_DISPLAY_H_
#define MESH2_DISPLAY_H_

#ifndef Q_MOC_RUN
#include <boost/shared_ptr.hpp>
#include <rviz/display.h>
#include <rviz/properties/color_property.h>
#include <rviz/properties/vector_property.h>
#include <rviz/properties/enum_property.h>
#include <OGRE/OgreLight.h>
#endif

namespace Ogre
{
    class SceneNode;
}

namespace rviz_lights
{

    class LightDisplay: public rviz::Display
    {
            Q_OBJECT
        public:
            // Constructor.  pluginlib::ClassLoader creates instances by calling
            // the default constructor, so make sure you have one.
            LightDisplay();
            virtual ~LightDisplay();

            private Q_SLOTS:
                void updateLight();
                void destroyLights();
            // Overrides of protected virtual functions from Display.  As much
            // as possible, when Displays are not enabled, they should not be
            // subscribed to incoming data and should not show anything in the
            // 3D view.  These functions are where these connections are made
            // and broken.
        protected:
            virtual void onInitialize();

            // A helper to clear this display back to the initial state.
            virtual void reset();

            virtual void onEnable();
            virtual void onDisable();

            rviz::ColorProperty* diffuseColorProperty;
            rviz::ColorProperty* specularColorProperty;
            rviz::ColorProperty* ambientColorProperty;
            rviz::VectorProperty* positionProperty;
            rviz::VectorProperty* directionProperty;
            rviz::EnumProperty* typeProperty;
            rviz::BoolProperty* destroyProperty;

            Ogre::Light* light;

    };
} // end namespace mesh2_plugin

#endif // MESH2_DISPLAY_H_
