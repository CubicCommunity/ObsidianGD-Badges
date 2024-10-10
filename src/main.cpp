#include "util/Badges.hpp"

#include <string>
#include <map>
#include <thread>

#include <Geode/Geode.hpp>

#include <Geode/ui/Notification.hpp>

#include <Geode/utils/web.hpp>

#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/CommentCell.hpp>

#include <Geode/binding/ProfilePage.hpp>
#include <Geode/binding/CommentCell.hpp>

using namespace geode::prelude;

// its modding time
auto getThisMod = geode::getMod();

// for getting badges
EventListener<web::WebTask> ogdBadgeRequest;

// create badge button
void setNewBadge(std::string id, CCMenu *username_menu, float size, auto pointer)
{
	// checks the map for this value to see if its invalid
	bool idFailTest = Badges::badgeSpriteName[id].empty();

	if (idFailTest)
	{
		log::debug("Badge id '{}' is invalid.", id.c_str());
	}
	else
	{
		if (username_menu)
		{
			if (auto alreadyBadge = username_menu->getChildByID(id))
			{
				alreadyBadge->removeMeAndCleanup();
			};

			// gets sprite filename
			auto newBadge = Badges::badgeSpriteName[id].c_str();

			if (getThisMod->getSettingValue<bool>("console"))
				log::debug("Setting badge to {}...", newBadge);

			CCSprite *badgeSprite = CCSprite::create(newBadge);
			badgeSprite->setScale(size);

			CCMenuItemSpriteExtra *badge = CCMenuItemSpriteExtra::create(
				badgeSprite,
				pointer,
				menu_selector(Badges::onInfoBadge));
			badge->setID(id);
			badge->setZOrder(1);

			username_menu->addChild(badge);
			username_menu->updateLayout();

			if (getThisMod->getSettingValue<bool>("console"))
				log::debug("Badge {} successfully set", newBadge);
		};
	};
};

// attempt fetch badge locally and remotely
void onCheckForBadge(CCMenu *username_menu, float size, auto pointer, int accID)
{
	// gets locally saved badge id
	std::string cacheStd = getThisMod->getSavedValue<std::string>(fmt::format("cache-badge-u{}", (int)accID));
	auto badgeCache = cacheStd.c_str();

	if (getThisMod->getSettingValue<bool>("console"))
		log::debug("Revising badge for user {} of ID '{}'...", (int)accID, badgeCache);

	// web request event
	ogdBadgeRequest.bind([pointer, username_menu, size, accID](web::WebTask::Event *e)
						 {
			if (web::WebResponse *ogdReqRes = e->getValue())
			{
				std::string ogdWebResUnwr = ogdReqRes->string().unwrapOr("Uh oh!");
				std::string savedString = getThisMod->getSavedValue<std::string>(fmt::format("cache-badge-u{}", (int)accID));

				if (getThisMod->getSettingValue<bool>("console")) log::debug("Processing remotely-obtained string '{}'...", ogdWebResUnwr.c_str());

                if (ogdWebResUnwr.c_str() == savedString.c_str()) {
                    if (getThisMod->getSettingValue<bool>("console")) log::debug("Badge for user of ID {} up-to-date", (int)accID);
                } else {
					bool failed = Badges::badgeSpriteName[ogdWebResUnwr].empty();
                    
					if (failed) {
						if (getThisMod->getSettingValue<bool>("console")) log::error("Badge of ID '{}' failed validation test", ogdWebResUnwr.c_str());
					} else {
						getThisMod->setSavedValue(fmt::format("cache-badge-u{}", (int)accID), ogdWebResUnwr);

                    	if (getThisMod->getSettingValue<bool>("console")) log::debug("Fetched badge {} remotely", ogdWebResUnwr.c_str());
					
                    	setNewBadge(ogdWebResUnwr, username_menu, size, pointer);
					};
                };
			}
			else if (web::WebProgress *p = e->getProgress())
			{
				if (getThisMod->getSettingValue<bool>("console")) log::debug("badge id progress: {}", p->downloadProgress().value_or(0.f));
			}
			else if (e->isCancelled())
			{
				if (getThisMod->getSettingValue<bool>("console")) log::error("Badge web request failed");
				if (getThisMod->getSettingValue<bool>("err-notifs")) Notification::create("Unable to fetch badge", NotificationIcon::Error, 2.5f)->show();
			}; });

	// sends the web request
	auto ogdReq = web::WebRequest();
	ogdBadgeRequest.setFilter(ogdReq.get(fmt::format("https://raw.githubusercontent.com/CubicCommunity/InstallOGDPS/main/data/publicBadges/{}.txt", (int)accID)));

	// checks the map with the cache as a key to see if its invalid
	bool isNotCached = Badges::badgeSpriteName[cacheStd].empty();

	if (isNotCached)
	{
		if (getThisMod->getSettingValue<bool>("console"))
			log::error("Badge id '{}' from cache is invalid", badgeCache);
	}
	else
	{
		if (getThisMod->getSettingValue<bool>("console"))
			log::debug("Fetched badge id '{}' from cache", badgeCache);
		setNewBadge(cacheStd, username_menu, size, pointer);
	};
};

class $modify(Profile, ProfilePage)
{
	// modified vanilla loadPageFromUserInfo function
	void loadPageFromUserInfo(GJUserScore * user)
	{
		ProfilePage::loadPageFromUserInfo(user);

		if (getThisMod->getSettingValue<bool>("show-profile"))
		{
			auto mLayer = m_mainLayer;
			CCMenu *username_menu = typeinfo_cast<CCMenu *>(mLayer->getChildByIDRecursive("username-menu"));

			onCheckForBadge(username_menu, 0.875f, this, user->m_accountID);

			if (getThisMod->getSettingValue<bool>("console"))
				log::debug("Viewing profile of ID {}", user->m_accountID);
		};
	};
};

class $modify(Comment, CommentCell)
{
	// modified vanilla loadFromComment function
	void loadFromComment(GJComment * comment)
	{
		CommentCell::loadFromComment(comment);

		if (getThisMod->getSettingValue<bool>("show-comments"))
		{
			auto mLayer = m_mainLayer;
			CCMenu *username_menu = typeinfo_cast<CCMenu *>(mLayer->getChildByIDRecursive("username-menu"));

			onCheckForBadge(username_menu, 0.5f, this, comment->m_accountID);

			if (getThisMod->getSettingValue<bool>("console"))
				log::debug("Viewing comment profile of ID {}", comment->m_accountID);
		};
	};
};