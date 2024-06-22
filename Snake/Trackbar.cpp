#include "Trackbar.h"
#include <iostream>
Trackbar::Trackbar(sf::Vector2f pos)
{
    track.setSize(sf::Vector2f(200, 10));
    track.setPosition(pos);
    track.setFillColor(sf::Color::White);

    slider.setSize(sf::Vector2f(10, 20));
    slider.setPosition(track.getPosition().x, track.getPosition().y - 5);
    slider.setFillColor(sf::Color::Red);

    font.loadFromFile("../External/Fonts/Lato-Black.ttf");
    valueText.setFont(font);
    valueText.setPosition(sf::Vector2f(pos.x + track.getSize().x + 10, pos.y-5));
    valueText.setCharacterSize(16);
    valueText.setFillColor(sf::Color::Black);
    valueText.setString("200");
    
}

void Trackbar::draw(sf::RenderWindow& window)
{
    window.draw(track);
    window.draw(slider);
    window.draw(valueText);
}

void Trackbar::handleEvent(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            // Check if the mouse is pressed on the slider
            if (slider.getGlobalBounds().contains(mousePos))
            {
                dragging = true;
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)// MouseButtonReleased will not work very well
    {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Stop dragging the slider
            dragging = false;
        }
    }

    else if (event.type == sf::Event::MouseMoved)
    {
        sf::Vector2f mousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
        // Update the trackbar if dragging
        if (dragging && track.getGlobalBounds().contains(mousePos))
        {
            update(mousePos);
        }
        else
        {
            dragging = false; // Stop dragging if mouse is outside the trackbar
        }
    }
}

void Trackbar::update(sf::Vector2f mousePos)
{
    if (dragging)
    {
        float newX = mousePos.x - slider.getSize().x / 2;
        if (newX < track.getPosition().x) {
            newX = track.getPosition().x;
        }
        else if (newX > track.getPosition().x + track.getSize().x - slider.getSize().x) {
            newX = track.getPosition().x + track.getSize().x - slider.getSize().x;
        }

        slider.setPosition(newX, slider.getPosition().y);
        float value = getValue();
        std::string strvalue = std::to_string(value).substr(0, std::to_string(value).find("."));
        

        valueText.setString(strvalue);
        

    }
}

int Trackbar::getValue()
{
    float position = slider.getPosition().x - track.getPosition().x;
    float range = track.getSize().x - slider.getSize().x;
    float value = 200 - (position / range) * 190;
    return value;
}
