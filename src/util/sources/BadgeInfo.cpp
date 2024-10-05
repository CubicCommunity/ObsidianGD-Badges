#include "../BadgeInfo.hpp"

#include "../Badges.hpp"

#include <string>
#include <map>

#include <Geode/Geode.hpp>

#include <Geode/utils/web.hpp>

using namespace geode::prelude;

// badge button event
void BadgeInfo::onInfoBadge(CCObject *sender)
{
    auto nodeObject = as<CCNode *>(sender);
    auto badge_ID = nodeObject->getID();

    if (badge_ID == Badges::getBadgeStringID[Badges::BadgeID::Director])
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
    else if (badge_ID == Badges::getBadgeStringID[Badges::BadgeID::TeamManager])
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
    else if (badge_ID == Badges::getBadgeStringID[Badges::BadgeID::TeamMember])
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
    else if (badge_ID == Badges::getBadgeStringID[Badges::BadgeID::CrewManager])
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
    else if (badge_ID == Badges::getBadgeStringID[Badges::BadgeID::CrewMember])
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