#pragma once
#ifndef _INITIAL_SCENE_H_
#define  _INITIAL_SCENE_H_
#include"cocos2d.h"
#include "AudioEngine.h"

USING_NS_CC;

class initial_scene :public cocos2d::Scene {
public:
	static cocos2d::Scene* pause_Scene(RenderTexture* sqr);


	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuCloseCallback2(cocos2d::Ref* pSender);
	void menuCloseCallback3(cocos2d::Ref* pSender);

	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	CREATE_FUNC(initial_scene);
	static void problemLoading(const char* filename);


	void push_button();
	//AudioEngine* audio;
	//CocosDenshion::SimpleAudioEngine* audio;//±≥æ∞“Ù¿÷π‹¿Ì∆˜
private:
};

#endif