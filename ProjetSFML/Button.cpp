#include "Button.hpp"

sf::Sprite* m_sprite;

Button::Button(sf::IntRect _rect, sf::Vector2f _position)
{
	m_rect = _rect;
	m_position = _position;
	m_isClicked = false;
	m_overred = false;
	m_isReleased = false;
	m_timer = 0.f;
	m_timerMax = 0.1f;
	m_color = sf::Color::White;
}

Button::~Button()
{
}

void Button::Update(sf::RenderWindow& _window, float _dt)
{
	m_overred = Hovered(_window);
	if (m_isClicked && m_isReleased)
	{
		m_timer += _dt;


		if (m_timer >= m_timerMax)
		{
			m_isClicked = false;
			m_isReleased = false;
			m_timer = 0.f;
		}
	}
}

bool Button::Click(sf::RenderWindow& _window)
{
	if (Hovered(_window))
	{
		m_isClicked = true;
		return true;
	}
	return false;
}

void Button::Release()
{
	m_isReleased = true;
}

void Button::SetSprite(sf::Sprite* _sprite)
{
	m_sprite = _sprite;
}

void Button::Draw(sf::RenderTarget& _window)
{
	m_sprite->setPosition(m_position);

	sf::IntRect temp;
	temp = m_rect;
	if (m_isClicked)
	{
		temp.position.x += m_rect.size.x;
	}
	else if (m_overred)
	{
		temp.position.x += m_rect.size.x * 2;
	}

	m_sprite->setColor(m_color);
	m_sprite->setTextureRect(temp);
	_window.draw(*m_sprite);
}

bool Button::Hovered(sf::RenderWindow& _window)
{
	sf::Vector2i mPos = sf::Mouse::getPosition(_window);

	sf::FloatRect cRect;
	cRect.position = m_position;
	cRect.size = sf::Vector2f( m_rect.size * 4);

	return cRect.contains(sf::Vector2f(mPos.x, mPos.y));
}
