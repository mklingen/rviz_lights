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

    class LightProperties: public rviz::Display
    {
            Q_OBJECT
        public:
            // Constructor.  pluginlib::ClassLoader creates instances by calling
            // the default constructor, so make sure you have one.
            LightProperties();
            virtual ~LightProperties();

            private Q_SLOTS:
                void updateLight();
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

            ::rviz::BoolProperty *property_shadows_;
            ::rviz::BoolProperty *property_cameralight_;
            ::rviz::BoolProperty *property_keylight_;
            ::rviz::BoolProperty *property_filllight_;
            ::rviz::BoolProperty *property_backlight_;

    };
} // end namespace mesh2_plugin

#endif // MESH2_DISPLAY_H_
