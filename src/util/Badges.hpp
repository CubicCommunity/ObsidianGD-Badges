#pragma once

#include <string>
#include <map>

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class Badges
{
public:
    enum class BadgeID
    {
        Director = 1,
        CrewManager = 2,
        CrewMember = 3,
        TeamManager = 4,
        TeamMember = 5
    };

    static std::map<BadgeID, std::string> badgeStringID;
    static std::map<std::string, std::string> badgeSpriteName;
    
    void onInfoBadge(CCObject *sender);
};