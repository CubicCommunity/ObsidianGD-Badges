#include "../Badges.hpp"
#include "../BadgeInfo.hpp"

#include <Geode/Geode.hpp>

#include <Geode/utils/web.hpp>

using namespace geode::prelude;

std::map<Badges::BadgeID, std::string> Badges::getBadgeStringID{
    {Badges::BadgeID::Director, "director"},
    {Badges::BadgeID::CrewManager, "crew-manager"},
    {Badges::BadgeID::CrewMember, "crew-member"},
    {Badges::BadgeID::TeamManager, "team-manager"},
    {Badges::BadgeID::TeamMember, "team-member"}};

std::map<std::string, std::string> Badges::getBadgeSpriteName{
    {Badges::getBadgeStringID[Badges::BadgeID::Director], "crew-member.png"_spr},
    {Badges::getBadgeStringID[Badges::BadgeID::CrewManager], "crew-member.png"_spr},
    {Badges::getBadgeStringID[Badges::BadgeID::CrewManager], "crew-member.png"_spr},
    {Badges::getBadgeStringID[Badges::BadgeID::TeamManager], "team-member.png"_spr},
    {Badges::getBadgeStringID[Badges::BadgeID::TeamMember], "team-member.png"_spr}};

void Badges::setNewBadge(std::string id, cocos2d::CCLayer *mLayer, float size, auto parent)
{
    if (id.empty())
    {
        return;
    }
    else
    {
        CCMenu *username_menu = typeinfo_cast<CCMenu *>(mLayer->getChildByIDRecursive("username-menu"));

        if (auto alreadyBadge = username_menu->getChildByID(id))
        {
            alreadyBadge->removeMeAndCleanup();
        };

        if (username_menu)
        {
            CCSprite *badgeSprite = CCSprite::create(Badges::getBadgeSpriteName[id].c_str());
            badgeSprite->setScale(size);

            CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
                badgeSprite,
                parent,
                menu_selector(BadgeInfo::onInfoBadge));
            badge->setID(id);
            badge->setZOrder(1);

            username_menu->addChild(badge);
            username_menu->updateLayout();
        };
    };
};