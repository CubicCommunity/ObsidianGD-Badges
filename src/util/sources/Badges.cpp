#include "../Badges.hpp"

std::map<Badges::BadgeID, std::string> Badges::getBadgeStringID{
    {Badges::BadgeID::Director, "director"},
    {Badges::BadgeID::CrewManager, "crew-manager"},
    {Badges::BadgeID::CrewMember, "crew-member"},
    {Badges::BadgeID::TeamManager, "team-manager"},
    {Badges::BadgeID::TeamMember, "team-member"}};