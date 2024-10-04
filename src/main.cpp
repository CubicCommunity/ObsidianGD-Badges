#include "util/Badges.hpp"
#include "util/BadgeInfo.hpp"

#include <Geode/Geode.hpp>

#include <Geode/utils/web.hpp>

#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/CommentCell.hpp>

using namespace geode::prelude;

class $modify(Profile, ProfilePage)
{
	struct Fields
	{
		std::string badgeID;
		EventListener<web::WebTask> ogdBadgeRequest;
		int accID;
	};

	void loadPageFromUserInfo(GJUserScore * user)
	{
		ProfilePage::loadPageFromUserInfo(user);
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

			CCMenu *username_menu = typeinfo_cast<CCMenu *>(m_mainLayer->getChildByIDRecursive("username-menu"));
			Profile::setNewBadge(badgeCache, username_menu);
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
					
			CCMenu *username_menu = typeinfo_cast<CCMenu *>(m_mainLayer->getChildByIDRecursive("username-menu"));

                    Profile::setNewBadge(ogdWebResultUnwrapped, username_menu);
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

	void setNewBadge(std::string id, CCMenu * username_menu)
	{
		if (id == Badges::getBadgeStringID[Badges::BadgeID::Director])
		{
			if (auto alreadyBadge = username_menu->getChildByID(id))
			{
				alreadyBadge->removeMeAndCleanup();
			};

			CCSprite *badgeSprite = CCSprite::create("crew-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(BadgeInfo::onInfoBadge));
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

			CCSprite *badgeSprite = CCSprite::create("team-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(BadgeInfo::onInfoBadge));
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

			CCSprite *badgeSprite = CCSprite::create("team-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(BadgeInfo::onInfoBadge));
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

			CCSprite *badgeSprite = CCSprite::create("crew-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(BadgeInfo::onInfoBadge));
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

			CCSprite *badgeSprite = CCSprite::create("crew-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(BadgeInfo::onInfoBadge));
			badge->setID(id);
			badge->setZOrder(1);

			username_menu->addChild(badge);
			username_menu->updateLayout();
		};
	};
};

class $modify(Comment, CommentCell)
{
	struct Fields
	{
		std::string badgeID;
		EventListener<web::WebTask> ogdBadgeRequest;
		int accID;
	};

	void loadFromComment(GJComment * comment)
	{
		CommentCell::loadFromComment(comment);
		m_fields->accID = comment->m_accountID;

		Comment::onCheckForBadge();
		log::debug("Viewing profile of ID {}", m_fields->accID);
	};

	void onCheckForBadge()
	{
		auto badgeCache = geode::getMod()->getSavedValue<std::string>(fmt::format("cache-badge-u{}", m_fields->accID)).c_str();

		if (badgeCache)
		{
			log::debug("Fetched badge {} from cache", badgeCache);

			CCMenu *username_menu = typeinfo_cast<CCMenu *>(m_mainLayer->getChildByIDRecursive("username-menu"));
			Comment::setNewBadge(badgeCache, username_menu);
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
					
			CCMenu *username_menu = typeinfo_cast<CCMenu *>(m_mainLayer->getChildByIDRecursive("username-menu"));

                    Comment::setNewBadge(ogdWebResultUnwrapped, username_menu);
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

	void setNewBadge(std::string id, CCMenu * username_menu)
	{
		if (id == Badges::getBadgeStringID[Badges::BadgeID::Director])
		{
			if (auto alreadyBadge = username_menu->getChildByID(id))
			{
				alreadyBadge->removeMeAndCleanup();
			};

			CCSprite *badgeSprite = CCSprite::create("crew-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(BadgeInfo::onInfoBadge));
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

			CCSprite *badgeSprite = CCSprite::create("team-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(BadgeInfo::onInfoBadge));
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

			CCSprite *badgeSprite = CCSprite::create("team-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(BadgeInfo::onInfoBadge));
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

			CCSprite *badgeSprite = CCSprite::create("crew-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(BadgeInfo::onInfoBadge));
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

			CCSprite *badgeSprite = CCSprite::create("crew-member.png"_spr);
			badgeSprite->setScale(0.925f);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				this,
				menu_selector(BadgeInfo::onInfoBadge));
			badge->setID(id);
			badge->setZOrder(1);

			username_menu->addChild(badge);
			username_menu->updateLayout();
		};
	};
};