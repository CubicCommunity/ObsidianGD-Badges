#include "../Badges.hpp"

#include <string>
#include <map>

#include <Geode/Geode.hpp>

#include <Geode/utils/web.hpp>

using namespace geode::prelude;

std::map<Badges::BadgeID, std::string> Badges::badgeStringID{
    {Badges::BadgeID::Director, "director"},
    {Badges::BadgeID::CrewManager, "crew-manager"},
    {Badges::BadgeID::CrewMember, "crew-member"},
    {Badges::BadgeID::TeamManager, "team-manager"},
    {Badges::BadgeID::TeamMember, "team-member"}};

std::map<std::string, std::string> Badges::badgeSpriteName{
    {Badges::badgeStringID[Badges::BadgeID::Director], "crew-member.png"_spr},
    {Badges::badgeStringID[Badges::BadgeID::CrewManager], "crew-member.png"_spr},
    {Badges::badgeStringID[Badges::BadgeID::CrewManager], "crew-member.png"_spr},
    {Badges::badgeStringID[Badges::BadgeID::TeamManager], "team-member.png"_spr},
    {Badges::badgeStringID[Badges::BadgeID::TeamMember], "team-member.png"_spr}};

// badge button event
void Badges::onInfoBadge(CCObject *sender)
{
    // gets the node that triggered the function
    auto nodeObject = as<CCNode *>(sender);
    auto badge_ID = nodeObject->getID();

    if (badge_ID == Badges::badgeStringID[Badges::BadgeID::Director])
    {
        geode::createQuickPopup(
            "OBSIDIAN Director",
            "This user is the <cj>director</c> of <cp>OBSIDIAN</c>. They manage and supervise everything.",
            "OK", "Learn More",
            [](auto, bool btn2)
            {
                if (btn2)
                {
                    web::openLinkInBrowser("https://www.obsidianmg.cc/#crew");
                };
            });
    }
    else if (badge_ID == Badges::badgeStringID[Badges::BadgeID::TeamManager])
    {
        geode::createQuickPopup(
            "ObsidianGD Manager",
            "This user is a <cy>manager</c> of <cp>ObsidianGD</c>. They manage group projects and collaborations.",
            "OK", "Learn More",
            [](auto, bool btn2)
            {
                if (btn2)
                {
                    web::openLinkInBrowser("https://www.obsidianmg.cc/gd-team/#team");
                };
            });
    }
    else if (badge_ID == Badges::badgeStringID[Badges::BadgeID::TeamMember])
    {
        geode::createQuickPopup(
            "ObsidianGD Team Member",
            "This user is a <cg>member</c> of <cp>ObsidianGD</c>. They partake in group projects and collaborations.",
            "OK", "Learn More",
            [](auto, bool btn2)
            {
                if (btn2)
                {
                    web::openLinkInBrowser("https://www.obsidianmg.cc/gd-team/#team");
                };
            });
    }
    else if (badge_ID == Badges::badgeStringID[Badges::BadgeID::CrewManager])
    {
        geode::createQuickPopup(
            "OBSIDIAN Manager",
            "This user is a <cy>manager</c> of <cp>OBSIDIAN</c>. They manage group projects.",
            "OK", "Learn More",
            [](auto, bool btn2)
            {
                if (btn2)
                {
                    web::openLinkInBrowser("https://www.obsidianmg.cc/#crew");
                };
            });
    }
    else if (badge_ID == Badges::badgeStringID[Badges::BadgeID::CrewMember])
    {
        geode::createQuickPopup(
            "OBSIDIAN Crew Member",
            "This user is a <cg>member</c> of <cp>OBSIDIAN</c>. They partake in group content creation.",
            "OK", "Learn More",
            [](auto, bool btn2)
            {
                if (btn2)
                {
                    web::openLinkInBrowser("https://www.obsidianmg.cc/#crew");
                };
            });
    };
};