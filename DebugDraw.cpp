#include "DebugDraw.h"

#include "Utilities.h"

DebugDraw::DebugDraw(sf::RenderWindow &window)
{
	m_window = &window;
}

DebugDraw::~DebugDraw()
{

}

//convert a Box2D (float 0.0f - 1.0f range) color to a SFML color (uint8 0 - 255 range)
sf::Color DebugDraw::B2SFColor(const b2Color &color, int alpha = 255)
{
	sf::Color result((sf::Uint8)(color.r * 255), (sf::Uint8)(color.g * 255), (sf::Uint8)(color.b * 255), (sf::Uint8) alpha);
	return result;
}

void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
{
	sf::VertexArray polygon;
	polygon.append(sf::Vertex(sf::Vector2f(aabb->lowerBound.x * math::RATIO, aabb->lowerBound.y * math::RATIO), B2SFColor(color, 50)));
	polygon.append(sf::Vertex(sf::Vector2f(aabb->upperBound.x * math::RATIO, aabb->lowerBound.y * math::RATIO), B2SFColor(color, 50)));
	polygon.append(sf::Vertex(sf::Vector2f(aabb->upperBound.x  *math::RATIO, aabb->upperBound.y * math::RATIO), B2SFColor(color, 50)));
	polygon.append(sf::Vertex(sf::Vector2f(aabb->lowerBound.x * math::RATIO, aabb->upperBound.y * math::RATIO), B2SFColor(color, 50)));
	polygon.setPrimitiveType(sf::LinesStrip);

	m_window->draw(polygon);
}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	sf::RectangleShape point;
	point.setPosition(p.x*math::RATIO, -p.y*math::RATIO);
	point.setSize(sf::Vector2f(1.0f, 1.0f));
	point.setOutlineColor(B2SFColor(color));
	point.setOutlineThickness(1.0f);
	m_window->draw(point); 
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
	float x, y;
	x = xf.p.x * math::RATIO;
	y = xf.p.y * math::RATIO;
	b2Vec2 p1 = xf.p, p2;

	//red (X axis)
	p2.x = p1.x + xf.q.GetAngle();
	p2.y = p1.y + xf.q.GetAngle();
	
	
	sf::VertexArray redLine(sf::Lines, 2);
	redLine[0].position.x = p1.x*math::RATIO;
	redLine[0].position.y = -p1.y*math::RATIO;
	redLine[1].position.x = p2.x*math::RATIO;
	redLine[1].position.y = -p2.y*math::RATIO;
	
	redLine[0].color =  sf::Color::Red;
	redLine[1].color = sf::Color::Red;

	//green (Y axis)
	p2.x = p1.x - xf.q.GetAngle();
	p2.y = p1.y - xf.q.GetAngle();
	
	sf::VertexArray greenLine(sf::Lines, 2);
	greenLine[0].position.x = p1.x*math::RATIO;
	greenLine[0].position.y = -p1.y*math::RATIO;
	greenLine[1].position.x = p2.x*math::RATIO;
	greenLine[1].position.y = -p2.y*math::RATIO;

	greenLine[0].color = sf::Color::Green;
	greenLine[1].color = sf::Color::Green;


	m_window->draw(redLine);
	m_window->draw(greenLine);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::VertexArray line;
	line.append(sf::Vertex(sf::Vector2f(p1.x*math::RATIO, -p1.y * math::RATIO), B2SFColor(color)));
	line.append(sf::Vertex(sf::Vector2f(p2.x*math::RATIO, -p2.y * math::RATIO), B2SFColor(color)));
	line.setPrimitiveType(sf::LinesStrip);
	m_window->draw(line);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	//no converion in cordinates of center and upper left corner, Circle in sfml is managed by default with the center
	sf::CircleShape circle(radius * math::RATIO);
	circle.setPosition((center.x - radius) * math::RATIO, (-center.y - radius) * math::RATIO);
	circle.setFillColor(B2SFColor(color, 50));
	circle.setOutlineThickness(1.0f);
	circle.setOutlineColor(B2SFColor(color));

	// line of the circle wich shows the angle
	b2Vec2 p;
	p.x = center.x + (radius * axis.x);
	p.y = center.y + (radius * axis.y);
	
	sf::VertexArray line;
	line.setPrimitiveType(sf::LinesStrip);
	line.append(sf::Vertex(sf::Vector2f((center.x) * math::RATIO, (-center.y) * math::RATIO), B2SFColor(color)));
	line.append(sf::Vertex(sf::Vector2f(p.x * math::RATIO, -p.y * math::RATIO), B2SFColor(color)));

	m_window->draw(circle);
	m_window->draw(line);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	sf::CircleShape circle(radius * math::RATIO);
	circle.setPosition(center.x * math::RATIO, -center.y * math::RATIO);
	circle.setOutlineColor(B2SFColor(color, 50));
	circle.setOutlineThickness(1.0f);

	m_window->draw(circle);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(vertexCount);
	for (int32 i = 0; i<vertexCount; i++)
	{
		b2Vec2 vertex = vertices[i];
		polygon.setPoint(i, sf::Vector2f(vertex.x * math::RATIO, -vertex.y * math::RATIO));
	}
	polygon.setFillColor(B2SFColor(color, 50));
	polygon.setOutlineColor(B2SFColor(color));
	polygon.setOutlineThickness(1.0f);
	m_window->draw(polygon);
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(vertexCount);
	for (int32 i = 0; i < vertexCount; i++)
	{
		b2Vec2 vertex = vertices[i];
		polygon.setPoint(i, sf::Vector2f(vertex.x * math::RATIO, -vertex.y * math::RATIO));
	}
	polygon.setOutlineColor(B2SFColor(color));
	polygon.setOutlineThickness(1.0f);
	m_window->draw(polygon);
}


void DebugDraw::DrawMouseJoint(b2Vec2& p1, b2Vec2& p2, const b2Color &boxColor, const b2Color &lineColor)
{
	sf::VertexArray polygon(sf::LinesStrip, 4);
	sf::VertexArray polygon2(sf::LinesStrip, 4);
	float p1x = p1.x * math::RATIO;
	float p1y = p1.y * math::RATIO;
	float p2x = p2.x * math::RATIO;
	float p2y = p2.y * math::RATIO;
	float size = 4.0f;

	sf::Color boxClr = B2SFColor(boxColor);
	sf::Color lineClr = B2SFColor(lineColor);

	//first green box for the joint
	polygon[0].position = sf::Vector2f(p1x - size / 2, -p1y - size / 2);
	polygon[0].color = boxClr;
	polygon[1].position = sf::Vector2f(p1x + size / 2, -p1y - size / 2);
	polygon[1].color = boxClr;
	polygon[2].position = sf::Vector2f(p1x + size / 2, -p1y + size / 2);
	polygon[2].color = boxClr;
	polygon[3].position = sf::Vector2f(p1x - size / 2, -p1y + size / 2);
	polygon[3].color = boxClr;	

	//second green box for the joint
	polygon2[0].position = sf::Vector2f(p2x - size / 2, -p2y - size / 2);
	polygon[0].color = boxClr;
	polygon2[1].position = sf::Vector2f(p2x + size / 2, -p2y - size / 2);
	polygon[1].color = boxClr;
	polygon2[2].position = sf::Vector2f(p2x + size / 2, -p2y + size / 2);
	polygon[2].color = boxClr;
	polygon2[3].position = sf::Vector2f(p2x - size / 2, -p2y + size / 2);
	polygon[3].color = boxClr;

	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(p1x, -p1y);
	line[0].color = lineClr;
	line[1].position = sf::Vector2f(p2x, -p2y);
	line[1].color = lineClr;
	
	m_window->draw(polygon);
	m_window->draw(polygon2);
	m_window->draw(line);
}
