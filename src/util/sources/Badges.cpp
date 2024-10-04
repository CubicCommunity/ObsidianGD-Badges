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