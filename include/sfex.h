#ifndef SFEX_H
#define SFEX_H

#include <SFML/Graphics.hpp>
#include <cmath>

//For Test
#include <iostream>

template <class T>
std::ostream& operator<<(std::ostream& out, sf::Vector2<T> v)
{
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}
template <class T>
sf::Vector2<T> operator-(sf::Vector2<T> left, T right)
{
	return sf::Vector2<T>(left.x - right, left.y - right);
}
namespace sfex{
    template <class T>
    static T length(sf::Vector2<T> v)
    {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    template <class T>
    static sf::Vector2<T> norm(sf::Vector2<T> v) //Returns v if v = (0, 0)
    {
        return v == sf::Vector2<T>(0, 0) ? v : v / length(v);
    }

    template <class T>
    class Matrix2
    {
    public:
        T a11;
        T a12;
        T a21;
        T a22;

        Matrix2(T a11, T a12, T a21, T a22)
            : a11{a11}, a12{a12}, a21{a21}, a22{a22}
        {
        }

        Matrix2<T> operator*(Matrix2<T>& m1)
        {
            return Matrix2<T>(a11 * m1.a11 + a12 * m1.a21,
                              a11 * m1.a12 + a12 * m1.a22,
                              a21 * m1.a11 + a22 * m1.a21,
                              a21 * m1.a12 + a22 * m1.a22);
        }

    };
    template <typename T>
    sf::Vector2<T> operator*(sfex::Matrix2<T> left, sf::Vector2<T>& right)
    {
        return sf::Vector2<T>(left.a11 * right.x + left.a12 * right.y,
                              left.a21 * right.x + left.a22 * right.y);
    }

    typedef Matrix2<float> Matrix2f;

    template <class T>
    static sf::Vector2f reflect(sf::Vector2<T> incoming, sf::Vector2<T> reflector)
    {
        /*        1     |v_x² - v_y²    2v_x v_y
         *  A = -----   |
         *     ||v||^2  |2v_x v_y       v_y²-v_x²
         */
        Matrix2f reflexMatrix(reflector.x * reflector.x - reflector.y * reflector.y,
                2 * reflector.x * reflector.y, 2 * reflector.x * reflector.y,
                reflector.y * reflector.y - reflector.x * reflector.x);
        return reflexMatrix * incoming * (reflector.x * reflector.x + reflector.y * reflector.y);
    }

    static void drawPoint(sf::RenderTarget& target, const sf::Vector2f point, sf::Color color = sf::Color::White)
    {
        sf::RectangleShape p(sf::Vector2f(1, 1));
        p.setPosition(point);
        p.setFillColor(color);
        target.draw(p);
    }

    static void drawPoints(sf::RenderTarget& target, const sf::Shape* shape, sf::Color color = sf::Color::White)// sf::RenderStates states = sf::RenderStates())
    {
        sf::RectangleShape r(sf::Vector2f(1, 1));
        r.setPosition(shape->getPosition());
        r.setFillColor(sf::Color::Red);
        target.draw(r);
        for (size_t i = 0; i < shape->getPointCount(); ++i)
        {
            sf::RectangleShape s(sf::Vector2f(1, 1));

            s.setPosition(sf::Vector2f(shape->getPoint(i).x + shape->getPosition().x - shape->getOrigin().x,
                                       shape->getPoint(i).y + shape->getPosition().y - shape->getOrigin().y));
            target.draw(s);
        }
    }
	
	static bool mouseButtonReleased(sf::Mouse::Button button) 
	{
		static bool pressed[sf::Mouse::ButtonCount];
		if (!sf::Mouse::isButtonPressed(button) && pressed[button])
		{
			pressed[button] = false;
			return true;
		}
		else if (sf::Mouse::isButtonPressed(button) && !pressed[button])
		{
			pressed[button] = true;
		}
		
		return false;
	}
	
	static sf::Mouse::Button mouseButtonReleased()
	{
		for (int i = 0; i < sf::Mouse::ButtonCount; ++i)
		{
			if(mouseButtonReleased(static_cast<sf::Mouse::Button>(i)))
				return static_cast<sf::Mouse::Button>(i);
		}
		return sf::Mouse::ButtonCount;
	}
	
	static bool keyReleased(sf::Keyboard::Key key)
	{
		static bool pressed[sf::Keyboard::KeyCount];
		if (!sf::Keyboard::isKeyPressed(key) && pressed[key])
		{
			pressed[key] = false;
			return true;
		}
		else if (sf::Keyboard::isKeyPressed(key) && !pressed[key])
		{
			pressed[key] = true;
		}
		
		return false;
	}
	
	static bool anyKeyPressed()
	{
		for (int i = 0; i < sf::Keyboard::KeyCount; i++)
				if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
					return true;
		return false;
	}
	
} // namespace sfex


namespace std
{
	template <typename T>
	static std::string to_string(sf::Vector2<T> vector)
	{
		return "(" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + ")";
	}
} //namespace std

#endif // SFEX_H
