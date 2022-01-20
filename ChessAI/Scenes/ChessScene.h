#pragma once

#include <Scene/Scene.h>

#include <string>

class ChessScene final : public Integrian2D::Scene
{
public:
	ChessScene(const std::string& name);
	virtual ~ChessScene() override;

	virtual void Start() override;

	virtual void Update() override;

private:
	
};