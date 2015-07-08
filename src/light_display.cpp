#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include <QColor>
#include <tf/transform_listener.h>

#include <rviz/visualization_manager.h>
#include <rviz/properties/color_property.h>
#include <rviz/properties/float_property.h>
#include <rviz/properties/int_property.h>
#include <rviz/frame_manager.h>

#include "light_display.h"

namespace rviz_lights
{

    // The constructor must have no arguments, so we can't give the
    // constructor the parameters it needs to fully initialize.
    LightDisplay::LightDisplay()
    {
        light = NULL;
        typeProperty = NULL;
        specularColorProperty = NULL;
        diffuseColorProperty = NULL;
        positionProperty = NULL;
        directionProperty = NULL;
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
    void LightDisplay::onInitialize()
    {
    	rviz::Display::onInitialize();
    	Ogre::Light::LightTypes type;
    	typeProperty = new rviz::EnumProperty("Light Type",
    	        "POINT",
    	        "The type of the light.", this, SLOT(updateLight()));

    	typeProperty->addOption("POINT", (int)Ogre::Light::LT_POINT);
        typeProperty->addOption("DIRECTIONAL", (int)Ogre::Light::LT_DIRECTIONAL);
        typeProperty->addOption("SPOT", (int)Ogre::Light::LT_SPOTLIGHT);

        positionProperty = new rviz::VectorProperty("Position",
                Ogre::Vector3(0, 0, 0),
                "The position of the light", this, SLOT(updateLight()));

        directionProperty = new rviz::VectorProperty("Direction",
                Ogre::Vector3(0, 0, -1),
                "The direction of the light", this, SLOT(updateLight()));

        ambientColorProperty = new rviz::ColorProperty("Ambient Color",
                QColor(255, 255, 255),
                "The diffuse color of the light", this, SLOT(updateLight()));

    	diffuseColorProperty = new rviz::ColorProperty("Diffuse Color",
    	        QColor(255, 255, 255),
    	        "The diffuse color of the light", this, SLOT(updateLight()));

        specularColorProperty = new rviz::ColorProperty("Specular Color",
                QColor(50, 50, 50),
                "The specular color of the light", this, SLOT(updateLight()));

        destroyProperty = new rviz::BoolProperty("Destroy All Lights", false, "When this is clicked, ALL lights except this one will be destroyed.", this, SLOT(destroyLights()));

    	updateLight();

    }

    LightDisplay::~LightDisplay()
    {
        scene_manager_->destroyLight(light);
        light = NULL;
    }

    void LightDisplay::destroyLights()
    {
        scene_manager_->destroyAllLights();
        light = NULL;
        updateLight();
    }

    void LightDisplay::onEnable()
    {
        light->setVisible(isEnabled());
    }

    void LightDisplay::onDisable()
    {
        light->setVisible(isEnabled());
    }

    void LightDisplay::updateLight()
    {
        if (!light)
        {
            light = scene_manager_->createLight();
        }

        light->setVisible(isEnabled());

        light->setType((Ogre::Light::LightTypes)(typeProperty->getOptionInt() ));
        light->setPosition(positionProperty->getVector());
        light->setDirection(directionProperty->getVector());
        QColor diffuse = diffuseColorProperty->getColor();
        light->setDiffuseColour(diffuse.redF(), diffuse.greenF(), diffuse.blueF());
        QColor specular = specularColorProperty->getColor();
        light->setSpecularColour(specular.redF(), specular.greenF(), specular.blueF());
        QColor ambient = ambientColorProperty->getColor();
        scene_manager_->setAmbientLight(Ogre::ColourValue(ambient.redF(), ambient.greenF(), ambient.blueF(), 1.0f));
    }

    // Clear the visuals by deleting their objects.
    void LightDisplay::reset()
    {
        rviz::Display::reset();
        scene_manager_->destroyLight(light);
        light = NULL;
    }

} // end namespace rviz_plugin_tutorials

// Tell pluginlib about this class.  It is important to do this in
// global scope, outside our package's namespace.
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rviz_lights::LightDisplay,rviz::Display )
