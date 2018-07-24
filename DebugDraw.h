#pragma once

#include <Box2D.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class DebugDraw : public b2Draw
{
public:
	DebugDraw(sf::RenderWindow &window);
	virtual ~DebugDraw();

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	void DrawTransform(const b2Transform& xf) override;
	void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;
	
	void DrawAABB(b2AABB* aabb, const b2Color& color);
	sf::Color B2SFColor(const b2Color &color, int alpha);
	void DrawMouseJoint(b2Vec2& p1, b2Vec2& p2, const b2Color &boxColor, const b2Color &lineColor);

private:
	sf::RenderWindow *m_window;
};
