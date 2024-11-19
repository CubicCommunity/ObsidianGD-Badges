#include "../Badges.hpp"

#include <string>
#include <map>

#include <Geode/Geode.hpp>

#include <Geode/utils/web.hpp>

using namespace geode::prelude;

std::map<Badges::BadgeID, std::string> Badges::badgeStringID{
    {Badges::BadgeID::Cubic, "cubic"},
    {Badges::BadgeID::Director, "director"},
    {Badges::BadgeID::CrewManager, "crew-manager"},
    {Badges::BadgeID::CrewMember, "crew-member"},
    {Badges::BadgeID::TeamManager, "team-manager"},
    {Badges::BadgeID::TeamMember, "team-member"},
    {Badges::BadgeID::Collaborator, "collaborator"}};

std::map<std::string, std::string> Badges::badgeSpriteName{
    {Badges::badgeStringID[Badges::BadgeID::Cubic], "cubic-studios.png"_spr},
    {Badges::badgeStringID[Badges::BadgeID::Director], "crew-member.png"_spr},
    {Badges::badgeStringID[Badges::BadgeID::CrewManager], "crew-member.png"_spr},
    {Badges::badgeStringID[Badges::BadgeID::CrewManager], "crew-member.png"_spr},
    {Badges::badgeStringID[Badges::BadgeID::TeamManager], "team-member.png"_spr},
    {Badges::badgeStringID[Badges::BadgeID::TeamMember], "team-member.png"_spr},
    {Badges::badgeStringID[Badges::BadgeID::Collaborator], "collaborator.png"_spr}};

// badge button event
void Badges::onInfoBadge(CCObject *sender)
{
    // gets the node that triggered the function
    auto nodeObject = as<CCNode *>(sender);
    auto badge_ID = nodeObject->getID();

    if (badge_ID == Badges::badgeStringID[Badges::BadgeID::Cubic])
    {
        geode::createQuickPopup(
            "Cubic Studios",
            "This user is a <cj>staff member</c> of <cc>Cubic Studios</c>. They partake in the activities of a department of Cubic.",
            "OK", "Learn More",
            [](auto, bool btn2)
            {
                if (btn2)
                {
                    web::openLinkInBrowser("https://www.youtube.com/c/CubicCommunity/");
                };
            });
    }
    else if (badge_ID == Badges::badgeStringID[Badges::BadgeID::Director])
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
    }
    else if (badge_ID == Badges::badgeStringID[Badges::BadgeID::Collaborator])
    {
        geode::createQuickPopup(
            "OBSIDIAN Collaborator",
            "This user is a <cg>collaborator</c> of <cp>OBSIDIAN</c> and/or <cp>ObsidianGD</c>. They've directly worked on the crew's or team's projects as an outsider.",
            "OK", "Learn More",
            [](auto, bool btn2)
            {
                if (btn2)
                {
                    web::openLinkInBrowser("https://www.obsidianmg.cc/#crew");
                };
            });
    }
    else
    {
        geode::createQuickPopup(
            "Oops!",
            "This badge has <cr>no available information</c>. This is likely unintentional, please report it as an issue in the mod's repository.",
            "OK", "Report",
            [](auto, bool btn2)
            {
                if (btn2)
                {
                    web::openLinkInBrowser("https://www.github.com/CubicCommunity/ObsidianGD-Badges/issues/");
                };
            });
    };
};