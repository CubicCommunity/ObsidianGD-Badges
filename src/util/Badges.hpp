#pragma once

#include <map>
#include <string>

class Badges
{
public:
    enum class BadgeID {
        Director = 1,
        CrewManager = 2,
        CrewMember = 3,
        TeamManager = 4,
        TeamMember = 4
    };

    static std::map<BadgeID, std::string> getBadgeStringID;
};