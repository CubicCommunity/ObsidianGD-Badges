#include "util/Badges.hpp"
#include "util/BadgeInfo.hpp"

#include <Geode/Geode.hpp>

#include <Geode/utils/web.hpp>

#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/CommentCell.hpp>

using namespace geode::prelude;

// its modding time
auto getThisMod = geode::getMod();

// if user invalid
std::string str404 = "404: Not Found";
auto char404 = str404.c_str();

// create badge button
void setNewBadge(std::string id, cocos2d::CCLayer *mLayer, float size, auto parent)
{
	if (id == str404 || id.c_str() == char404 || id.empty())
	{
		return;
	}
	else
	{
		CCMenu *username_menu = typeinfo_cast<CCMenu *>(mLayer->getChildByIDRecursive("username-menu"));

		if (auto alreadyBadge = username_menu->getChildByID(id))
		{
			alreadyBadge->removeMeAndCleanup();
		};

		auto newBadge = Badges::getBadgeSpriteName[id].c_str();

		if (getThisMod->getSettingValue<bool>("console")) log::debug("Setting badge to {}...", newBadge);

		if (username_menu)
		{
			CCSprite *badgeSprite = CCSprite::create(newBadge);
			badgeSprite->setScale(size);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				parent,
				menu_selector(BadgeInfo::onInfoBadge));
			badge->setID(id);
			badge->setZOrder(1);

			username_menu->addChild(badge);
			username_menu->updateLayout();
		};
	};
};

// attempt fetch badge locally and remotely
void onCheckForBadge(EventListener<web::WebTask> ogdBadgeRequest, cocos2d::CCLayer *mLayer, float size, auto parent, int accID)
{
	auto cacheStd = getThisMod->getSavedValue<std::string>(fmt::format("cache-badge-u{}", accID));
	auto badgeCache = cacheStd.c_str();

	if (badgeCache == char404 || cacheStd == str404 || cacheStd.empty())
	{
		if (getThisMod->getSettingValue<bool>("console"))
			log::debug("Badge unavailable.");
	}
	else
	{
		if (getThisMod->getSettingValue<bool>("console"))
			log::debug("Fetched badge {} from cache", badgeCache);
		setNewBadge(cacheStd, mLayer, size, parent);
	};

	ogdBadgeRequest.bind([parent, mLayer, size, accID](web::WebTask::Event *e)
						 {
				if (web::WebResponse *ogdReqRes = e->getValue())
			{
				std::string ogdWebResultUnwrapped = ogdReqRes->string().unwrapOr("Uh oh!");
				std::string savedString = getThisMod->getSavedValue<std::string>(fmt::format("cache-badge-u{}", accID));

                if (ogdWebResultUnwrapped.c_str() == savedString.c_str()) {
                    if (getThisMod->getSettingValue<bool>("console")) log::debug("Badge for user of ID {} up-to-date", accID);
                } else {
                    if (ogdWebResultUnwrapped.c_str() == char404 || ogdWebResultUnwrapped == str404 || ogdWebResultUnwrapped.empty()) getThisMod->setSavedValue(fmt::format("cache-badge-u{}", accID), ogdWebResultUnwrapped);
                    if (getThisMod->getSettingValue<bool>("console")) log::debug("Fetched badge {} remotely", ogdWebResultUnwrapped);
					
                    setNewBadge(ogdWebResultUnwrapped, mLayer, size, parent);
                };
			}
			else if (web::WebProgress *p = e->getProgress())
			{
				if (getThisMod->getSettingValue<bool>("console")) log::debug("badge id progress: {}", p->downloadProgress().value_or(0.f));
			}
			else if (e->isCancelled())
			{
				if (getThisMod->getSettingValue<bool>("console")) log::debug("The request was cancelled... So sad :(");
			}; });

	auto ogdReq = web::WebRequest();
	ogdBadgeRequest.setFilter(ogdReq.get(fmt::format("https://raw.githubusercontent.com/CubicCommunity/InstallOGDPS/main/data/publicBadges/{}.txt", (int)accID)));
};

class $modify(Profile, ProfilePage)
{
	struct Fields
	{
		std::string badgeID;
		EventListener<web::WebTask> ogdBadgeRequest;
	};

	void loadPageFromUserInfo(GJUserScore * user)
	{
		ProfilePage::loadPageFromUserInfo(user);

		if (getThisMod->getSettingValue<bool>("show-profile"))
		{
			onCheckForBadge(m_fields->ogdBadgeRequest, m_mainLayer, 0.875f, this, user->m_accountID);

			if (getThisMod->getSettingValue<bool>("console"))
				log::debug("Viewing profile of ID {}", user->m_accountID);
		};
	};

	void setNewBadge(std::string id, cocos2d::CCLayer * mLayer, float size, auto parent)
	{
		if (id.c_str() == char404 || id.empty())
		{
			return;
		}
		else
		{
			CCMenu *username_menu = typeinfo_cast<CCMenu *>(mLayer->getChildByIDRecursive("username-menu"));

			if (auto alreadyBadge = username_menu->getChildByID(id))
			{
				alreadyBadge->removeMeAndCleanup();
			};

			if (username_menu)
			{
				CCSprite *badgeSprite = CCSprite::create(Badges::getBadgeSpriteName[id].c_str());
				badgeSprite->setScale(size);

				CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
					badgeSprite,
					parent,
					menu_selector(BadgeInfo::onInfoBadge));
				badge->setID(id);
				badge->setZOrder(1);

				username_menu->addChild(badge);
				username_menu->updateLayout();
			};
		};
	};
};

class $modify(Comment, CommentCell)
{
	struct Fields
	{
		std::string badgeID;
		EventListener<web::WebTask> ogdBadgeRequest;
	};

	// modified vanilla loadFromComment function
	void loadFromComment(GJComment * comment)
	{
		CommentCell::loadFromComment(comment);

		if (getThisMod->getSettingValue<bool>("show-comments"))
		{
			onCheckForBadge(m_fields->ogdBadgeRequest, m_mainLayer, 0.5f, this, comment->m_accountID);

			if (getThisMod->getSettingValue<bool>("console"))
				log::debug("Viewing profile of ID {}", comment->m_accountID);
		};
	};
};