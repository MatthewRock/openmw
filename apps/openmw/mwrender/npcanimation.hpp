#ifndef GAME_RENDER_NPCANIMATION_H
#define GAME_RENDER_NPCANIMATION_H

#include "animation.hpp"

#include "../mwworld/inventorystore.hpp"

#include "weaponanimation.hpp"

namespace ESM
{
    struct NPC;
}

namespace MWRender
{

class NeckController;
class HeadAnimationTime;

class NpcAnimation : public Animation, public WeaponAnimation, public MWWorld::InventoryStoreListener
{
public:
    virtual void equipmentChanged();
    virtual void permanentEffectAdded(const ESM::MagicEffect *magicEffect, bool isNew, bool playSound);

public:
    typedef std::map<ESM::PartReferenceType,std::string> PartBoneMap;

    enum ViewMode {
        VM_Normal,
        VM_FirstPerson,
        VM_HeadOnly
    };

private:
    static const PartBoneMap sPartList;

    bool mListenerDisabled;

    // Bounded Parts
    PartHolderPtr mObjectParts[ESM::PRT_Count];
    std::string mSoundIds[ESM::PRT_Count];

    const ESM::NPC *mNpc;
    std::string    mHeadModel;
    std::string    mHairModel;
    ViewMode       mViewMode;
    bool mShowWeapons;
    bool mShowCarriedLeft;

    enum NpcType
    {
        Type_Normal,
        Type_Werewolf,
        Type_Vampire
    };
    NpcType mNpcType;

    int mPartslots[ESM::PRT_Count];  //Each part slot is taken by clothing, armor, or is empty
    int mPartPriorities[ESM::PRT_Count];

    osg::Vec3f mFirstPersonOffset;

    boost::shared_ptr<HeadAnimationTime> mHeadAnimationTime;
    boost::shared_ptr<WeaponAnimationTime> mWeaponAnimationTime;

    bool mSoundsDisabled;

    void updateNpcBase();

    PartHolderPtr insertBoundedPart(const std::string &model, const std::string &bonename,
                                        const std::string &bonefilter, bool enchantedGlow, osg::Vec4f* glowColor=NULL);

    void removeIndividualPart(ESM::PartReferenceType type);
    void reserveIndividualPart(ESM::PartReferenceType type, int group, int priority);

    bool addOrReplaceIndividualPart(ESM::PartReferenceType type, int group, int priority, const std::string &mesh,
                                    bool enchantedGlow=false, osg::Vec4f* glowColor=NULL);
    void removePartGroup(int group);
    void addPartGroup(int group, int priority, const std::vector<ESM::PartReference> &parts,
                                    bool enchantedGlow=false, osg::Vec4f* glowColor=NULL);

    virtual void setRenderBin();

    osg::ref_ptr<NeckController> mFirstPersonNeckController;

protected:
    virtual void addControllers();

public:
    /**
     * @param ptr
     * @param disableListener  Don't listen for equipment changes and magic effects. InventoryStore only supports
     *                         one listener at a time, so you shouldn't do this if creating several NpcAnimations
     *                         for the same Ptr, eg preview dolls for the player.
     *                         Those need to be manually rendered anyway.
     * @param disableSounds    Same as \a disableListener but for playing items sounds
     * @param viewMode
     */
    NpcAnimation(const MWWorld::Ptr& ptr, osg::ref_ptr<osg::Group> parentNode, Resource::ResourceSystem* resourceSystem, bool disableListener = false,
                 bool disableSounds = false, ViewMode viewMode=VM_Normal);
    virtual ~NpcAnimation();

    virtual void enableHeadAnimation(bool enable);

    virtual void setWeaponGroup(const std::string& group);

    virtual osg::Vec3f runAnimation(float timepassed);

    /// A relative factor (0-1) that decides if and how much the skeleton should be pitched
    /// to indicate the facing orientation of the character.
    virtual void setPitchFactor(float factor) { mPitchFactor = factor; }

    virtual void showWeapons(bool showWeapon);
    virtual void showCarriedLeft(bool show);

    virtual void attachArrow();
    virtual void releaseArrow(float attackStrength);

    virtual osg::Group* getArrowBone();
    virtual osg::Node* getWeaponNode();
    virtual Resource::ResourceSystem* getResourceSystem();

    // WeaponAnimation
    virtual void showWeapon(bool show) { showWeapons(show); }

    void setViewMode(ViewMode viewMode);

    void updateParts();

    /// Rebuilds the NPC, updating their root model, animation sources, and equipment.
    void rebuild();

    /// Get the inventory slot that the given node path leads into, or -1 if not found.
    int getSlot(const osg::NodePath& path) const;

    virtual void setVampire(bool vampire);

    /// Set a translation offset (in object root space) to apply to meshes when in first person mode.
    void setFirstPersonOffset(const osg::Vec3f& offset);

    virtual void updatePtr(const MWWorld::Ptr& updated);
};

}

#endif
