#ifndef _GAME_RENDER_ANIMATION_H
#define _GAME_RENDER_ANIMATION_H
#include <components/nif/data.hpp>
#include <openengine/ogre/renderer.hpp>
#include "../mwworld/refdata.hpp"
#include "../mwworld/ptr.hpp"
#include "../mwworld/actiontalk.hpp"
#include "../mwworld/environment.hpp"
#include <components/nif/node.hpp>
#include <map>

namespace MWRender{

class Animation{
    
   protected:
    
    OEngine::Render::OgreRenderer &mRend;
    MWWorld::Environment& mEnvironment;
    static std::map<std::string, int> mUniqueIDs;

    float time;
	float startTime;
	float stopTime;
	bool loop;
	bool animate;
	//Represents a rotation index for each bone
	std::vector<int>rindexI;
    //Represents a translation index for each bone
	std::vector<int>tindexI;
	
	//Only shapes with morphing data will need a shape number
	int shapeNumber;
	std::vector<std::vector<int>> shapeIndexI;

	//Ogre::SkeletonInstance* skel;
     std::vector<Nif::NiTriShapeCopy>* shapes;          //All the NiTriShapeData for this creature

    
   

    std::vector<Nif::NiKeyframeData>* transformations;
    std::map<std::string,float> textmappings;
    Ogre::Entity* base;
    void handleShapes(std::vector<Nif::NiTriShapeCopy>* allshapes, Ogre::Entity* creaturemodel, Ogre::SkeletonInstance *skel);
    void handleAnimationTransforms(Ogre::Entity* model);
    bool timeIndex( float time, std::vector<float> times, int & i, int & j, float & x );
    std::string getUniqueID(std::string mesh);
	
    public:
     Animation(MWWorld::Environment& _env, OEngine::Render::OgreRenderer& _rend): mRend(_rend), mEnvironment(_env), loop(false), animate(false){};
	 virtual void runAnimation(float timepassed) = 0;
	 void startScript(std::string groupname, int mode, int loops);
    
    
     ~Animation();
 
};
}
#endif