#pragma once

#ifndef SCENES_NOTIMPLEMENTEDSCENE_H_
#define SCENES_NOTIMPLEMENTEDSCENE_H_

#include "Scene.h"

class Screen;

class NotImplementedScene : public Scene {
public:
	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& theScreen) override;
	virtual const std::string& GetSceneName() const override;
};

#endif /* SCENES_NOTIMPLEMENTEDSCENE_H_*/