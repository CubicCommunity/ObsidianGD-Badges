#pragma once

#include <map>
#include <string>

#include <Geode/Geode.hpp>

#include <Geode/utils/web.hpp>

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
        TeamMember = 4
    };

    static std::map<BadgeID, std::string> getBadgeStringID;
};