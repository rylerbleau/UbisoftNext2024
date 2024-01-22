#include "stdafx.h"
#include "Collectible.h"

void Collectible::Update(const float deltaTime)
{
	if (!inUse) return;
	Ref<PhysicsComponent> body = GetComponent<PhysicsComponent>();
	body->Update(deltaTime);
	GetComponent<CircleComponent>()->UpdateCircleComponent(body);
	switch (type) {
	case PROJECTILE_TYPE::HP:
		GetComponent<LineComponent>()->UpdateLineComponent(body);
		break;
	case PROJECTILE_TYPE::HEAT:
		GetComponent<RectangleComponent>()->UpdateRectangleComponent(body);
		break;
	case PROJECTILE_TYPE::BULLET_SIZE:
		GetComponent<LineComponent>()->UpdateLineComponent(body);
		break;
	default:
		break;
	}
	

}

void Collectible::Render()
{
	if (!inUse) return;
	

	switch (type) {
	case PROJECTILE_TYPE::HP:
		GetComponent<LineComponent>()->Render();
		break;
	case PROJECTILE_TYPE::HEAT:
		GetComponent<RectangleComponent>()->Render();
		break;
	case PROJECTILE_TYPE::BULLET_SIZE:
		GetComponent<LineComponent>()->Render();
		break;

	default:
		break;
	}
	GetComponent<CircleComponent>()->Render();
}

	


void Collectible::Init(PROJECTILE_TYPE type_)
{
	RemoveAllComponents();

	inUse = true;
	float rad = 20.0f;
	type = type_;

	MATH::Vec2 pos = MATH::Vec2(FRAND_RANGE(rad, APP_VIRTUAL_WIDTH - rad), APP_VIRTUAL_HEIGHT + rad);

	std::vector<MATH::Line> lines;
	AddComponent<PhysicsComponent>(this, pos, MATH::Vec2(0.0f, -0.2f), MATH::Vec2(), 0.0f, 0.0f, 1.0f, true);


	switch (type) {
	case PROJECTILE_TYPE::HP:
		AddComponent<CircleComponent>(this, pos, rad, 15.0f,
			1.0f, 1.0f, 1.0f, true, false);
		lines.push_back(MATH::Line{ MATH::Vec2(-5.0f, 0.0f), MATH::Vec2(5.0f, 0.0f) , 1.0f, 0.0f, 0.0f});
		lines.push_back(MATH::Line{ MATH::Vec2(0.0f, 5.0f), MATH::Vec2(0.0f, -5.0f) , 1.0f, 0.0f, 0.0f });
		AddComponent<LineComponent>(this, lines, MATH::Vec2());

		break;
	case PROJECTILE_TYPE::HEAT:
		AddComponent<RectangleComponent>(this, pos, MATH::Vec2(20.0f, 10.0f),
			0.0f, 1.0f, 0.0f, true, true);
		AddComponent<CircleComponent>(this, pos, rad, 15.0f,
			1.0f, 1.0f, 1.0f, true, false);

		break;
	case PROJECTILE_TYPE::BULLET_SIZE:
		AddComponent<CircleComponent>(this, pos, rad, 15.0f,
			1.0f, 1.0f, 1.0f, true, false);
		lines.push_back(MATH::Line{ MATH::Vec2(-5.0f, 0.0f), MATH::Vec2(5.0f, 0.0f) , 0.0f, 1.0f, 0.0f });
		lines.push_back(MATH::Line{ MATH::Vec2(0.0f, 5.0f), MATH::Vec2(0.0f, -5.0f) , 0.0f, 1.0f, 0.0f });
		AddComponent<LineComponent>(this, lines, MATH::Vec2());

		break;
	default:
		AddComponent<CircleComponent>(this, pos, rad, 15.0f,
			0.0f, 0.0f, 0.0f, false, false);
		
		break;
	}
}

void Collectible::OnCollect(float& curHP, float maxHP, float& heatGainRate, float& bulletSize, float maxBsize)
{
	switch (type) {
	case PROJECTILE_TYPE::HP:
		curHP += 1.0f;
		if (curHP > maxHP) curHP = maxHP;
		break;
	case PROJECTILE_TYPE::HEAT:
		heatGainRate *= 0.8f;
		break;
	case PROJECTILE_TYPE::BULLET_SIZE:
		bulletSize = MATH::Lerp(bulletSize, maxBsize, 0.25f);
		break;
	default:
		break;
		
	}
}

void Collectible::Kill()
{
	RemoveAllComponents();
	inUse = false;
}
