#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include <QColor>
#include <tf/transform_listener.h>

#include <rviz/visualization_manager.h>
#include <rviz/properties/color_property.h>
#include <rviz/properties/float_property.h>
#include <rviz/properties/int_property.h>
#include <rviz/frame_manager.h>

#include "light_properties.h"

namespace rviz_lights
{

    // The constructor must have no arguments, so we can't give the
    // constructor the parameters it needs to fully initialize.
    LightProperties::LightProperties()
    {

    }

    // After the top-level rviz::Display::initialize() does its own setup,
    // it calls the subclass's onInitialize() function.  This is where we
    // instantiate all the workings of the class.  We make sure to also
    // call our immediate super-class's onInitialize() function, since it
    // does important stuff setting up the message filter.
    //
    //  Note that "MFDClass" is a typedef of
    // ``MessageFilterDisplay<message type>``, to save typing that long
    // templated class name every time you need to refer to the
    // superclass.
    void LightProperties::onInitialize()
    {
    	rviz::Display::onInitialize();

    	scene_manager_->setShadowTechnique(Ogre::SHADOWTYPE_NONE);

        Ogre::Light* mainDirectional = scene_manager_->getLight( "MainDirectional" );
        mainDirectional->setCastShadows(false);

        Ogre::Light *light = scene_manager_->createLight("FillLight");
        light->setType(Ogre::Light::LT_DIRECTIONAL);
        light->setDiffuseColour(0.6, 0.55, 0.5);
        light->setSpecularColour(1, 1, 1);
        light->setDirection(0.05, 0.01, -1);
        light->setCastShadows(true);

        Ogre::Light *light2 = scene_manager_->createLight("BackLight");
        light2->setType(Ogre::Light::LT_DIRECTIONAL);
        light2->setDiffuseColour(0.2, 0.25, 0.3);
        light2->setSpecularColour(1, 1, 1);
        light2->setDirection(-0.1, -0.1, 0.05);
        light2->setCastShadows(false);

        Ogre::Light *light3 = scene_manager_->createLight("KeyLight");
        light3->setType(Ogre::Light::LT_DIRECTIONAL);
        light3->setDiffuseColour(0.4, 0.4, 0.4);
        light3->setSpecularColour(1, 1, 1);
        light3->setDirection(0.1, 0.1, -0.05);
        light3->setCastShadows(false);

        scene_manager_->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
        scene_manager_->setShadowColour(Ogre::ColourValue(0.3, 0.3, 0.3, 1.0));

        property_shadows_ = new ::rviz::BoolProperty("Enable Shadows", false, "Enable shadows", this, SLOT(updateLight()));
        property_cameralight_ = new ::rviz::BoolProperty("Camera Light", true, "Enable Camera Light", this, SLOT(updateLight()));
        property_keylight_ = new ::rviz::BoolProperty("Key Light", true, "Enable Key Light", this, SLOT(updateLight()));
        property_filllight_ = new ::rviz::BoolProperty("Fill Light", true, "Enable Fill Light", this, SLOT(updateLight));
        property_backlight_= new ::rviz::BoolProperty("Back Light", true, "Enable Back Light", this, SLOT(updateLight()));

    	updateLight();

    }

    LightProperties::~LightProperties()
    {
        onDisable();
        scene_manager_->destroyLight("KeyLight");
        scene_manager_->destroyLight("FillLight");
        scene_manager_->destroyLight("BackLight");
    }

    void LightProperties::onEnable()
    {
        updateLight();
    }

    void LightProperties::onDisable()
    {
        scene_manager_->setShadowTechnique(Ogre::SHADOWTYPE_NONE);

        Ogre::Light* mainDirectional = scene_manager_->getLight( "MainDirectional" );
        Ogre::Light* keyLight = scene_manager_->getLight( "KeyLight" );
        Ogre::Light* fillLight = scene_manager_->getLight( "FillLight" );
        Ogre::Light* backLight = scene_manager_->getLight( "BackLight" );
        mainDirectional->setVisible(true);
        keyLight->setVisible(false);
        fillLight->setVisible(false);
        backLight->setVisible(false);
    }

    void LightProperties::updateLight()
    {
        bool shadows = property_shadows_->getBool();
        bool cam = property_cameralight_->getBool();
        bool key = property_keylight_->getBool();
        bool fill = property_filllight_->getBool();
        bool back = property_backlight_->getBool();


        scene_manager_->setShadowTechnique(shadows ? Ogre::SHADOWTYPE_STENCIL_ADDITIVE : Ogre::SHADOWTYPE_NONE);

        Ogre::Light* mainDirectional = scene_manager_->getLight( "MainDirectional" );
        Ogre::Light* keyLight = scene_manager_->getLight( "KeyLight" );
        Ogre::Light* fillLight = scene_manager_->getLight( "FillLight" );
        Ogre::Light* backLight = scene_manager_->getLight( "BackLight" );
        mainDirectional->setVisible(cam);
        keyLight->setVisible(key);
        fillLight->setVisible(fill);
        backLight->setVisible(back);
    }

    // Clear the visuals by deleting their objects.
    void LightProperties::reset()
    {
        rviz::Display::reset();
    }

} // end namespace rviz_plugin_tutorials

// Tell pluginlib about this class.  It is important to do this in
// global scope, outside our package's namespace.
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rviz_lights::LightProperties, rviz::Display )
