#include "util/Badges.hpp"

#include <Geode/Geode.hpp>

#include <Geode/utils/web.hpp>

#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(Profile, ProfilePage)
{
	struct Fields
	{
		EventListener<web::WebTask> ogdBadgeRequest;
		std::string badgeID;
		int accID;
	};

	void loadPageFromUserInfo(GJUserScore * user)
	{
		ProfilePage::loadPageFromUserInfo(user);

		auto layer = m_mainLayer;
		m_fields->accID = user->m_accountID;

		Profile::onCheckForBadge();
		log::debug("Viewing profile of ID {}", m_fields->accID);
	};

	void onCheckForBadge()
	{
		auto badgeCache = geode::getMod()->getSavedValue<std::string>(fmt::format("cache-badge-u{}", m_fields->accID)).c_str();

		if (badgeCache)
		{
			log::debug("Fetched badge {} from cache", badgeCache);

			Profile::setNewBadge(badgeCache);
		};

		m_fields->ogdBadgeRequest.bind([this](web::WebTask::Event *e)
									   {
				if (web::WebResponse *ogdReqRes = e->getValue())
			{
				std::string ogdWebResultUnwrapped = ogdReqRes->string().unwrapOr("Uh oh!");

                if (ogdWebResultUnwrapped.c_str() == geode::getMod()->getSavedValue<std::string>(fmt::format("cache-badge-u{}", m_fields->accID)).c_str()) {
                    log::debug("Badge for user of ID {} up-to-date", m_fields->accID);
                } else {
                    geode::getMod()->setSavedValue(fmt::format("cache-badge-u{}", m_fields->accID), ogdWebResultUnwrapped);
                    log::debug("Fetched badge {} remotely", ogdWebResultUnwrapped);

                    Profile::setNewBadge(ogdWebResultUnwrapped);
                };
			}
			else if (web::WebProgress *p = e->getProgress())
			{
				log::debug("badge id progress: {}", p->downloadProgress().value_or(0.f));
			}
			else if (e->isCancelled())
			{
				log::debug("The request was cancelled... So sad :(");
			}; });

		auto ogdReq = web::WebRequest();
		m_fields->ogdBadgeRequest.setFilter(ogdReq.get(fmt::format("https://raw.githubusercontent.com/CubicCommunity/InstallOGDPS/main/data/publicBadges/{}.txt", (int)m_fields->accID)));
	};

	void setNewBadge(std::string id)
	{
		auto layer = m_mainLayer;
		CCMenu *username_menu = typeinfo_cast<CCMenu *>(layer->getChildByIDRecursive("username-menu"));

		if (id == Badges::getBadgeStringID[Badges::BadgeID::Director])
		{
			if (auto alreadyBadge = username_menu->getChildByID(id))
			{
				alreadyBadge->removeMeAndCleanup();
			};

			m_fields->badgeID = id;

			CCSprite *badgeSprite = CCSprite::create("crew-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(Profile::onInfoBadge));
			badge->setID(id);
			badge->setZOrder(1);

			username_menu->addChild(badge);
			username_menu->updateLayout();
		}
		else if (id == Badges::getBadgeStringID[Badges::BadgeID::TeamManager])
		{
			if (auto alreadyBadge = username_menu->getChildByID(id))
			{
				alreadyBadge->removeMeAndCleanup();
			};

			m_fields->badgeID = id;

			CCSprite *badgeSprite = CCSprite::create("team-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(Profile::onInfoBadge));
			badge->setID(id);
			badge->setZOrder(1);

			username_menu->addChild(badge);
			username_menu->updateLayout();
		}
		else if (id == Badges::getBadgeStringID[Badges::BadgeID::TeamMember])
		{
			if (auto alreadyBadge = username_menu->getChildByID(id))
			{
				alreadyBadge->removeMeAndCleanup();
			};

			m_fields->badgeID = id;

			CCSprite *badgeSprite = CCSprite::create("team-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(Profile::onInfoBadge));
			badge->setID(id);
			badge->setZOrder(1);

			username_menu->addChild(badge);
			username_menu->updateLayout();
		}
		else if (id == Badges::getBadgeStringID[Badges::BadgeID::CrewManager])
		{
			if (auto alreadyBadge = username_menu->getChildByID(id))
			{
				alreadyBadge->removeMeAndCleanup();
			};

			m_fields->badgeID = id;

			CCSprite *badgeSprite = CCSprite::create("crew-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(Profile::onInfoBadge));
			badge->setID(id);
			badge->setZOrder(1);

			username_menu->addChild(badge);
			username_menu->updateLayout();
		}
		else if (id == Badges::getBadgeStringID[Badges::BadgeID::CrewMember])
		{
			if (auto alreadyBadge = username_menu->getChildByID(id))
			{
				alreadyBadge->removeMeAndCleanup();
			};

			m_fields->badgeID = id;

			CCSprite *badgeSprite = CCSprite::create("crew-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(Profile::onInfoBadge));
			badge->setID(id);
			badge->setZOrder(1);

			username_menu->addChild(badge);
			username_menu->updateLayout();
		};
	};

	void onInfoBadge(CCObject * sender)
	{
		if (m_fields->badgeID == Badges::getBadgeStringID[Badges::BadgeID::Director])
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
		else if (m_fields->badgeID == Badges::getBadgeStringID[Badges::BadgeID::TeamManager])
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
		else if (m_fields->badgeID == Badges::getBadgeStringID[Badges::BadgeID::TeamMember])
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
		else if (m_fields->badgeID == Badges::getBadgeStringID[Badges::BadgeID::CrewManager])
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
		else if (m_fields->badgeID == Badges::getBadgeStringID[Badges::BadgeID::CrewMember])
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
};