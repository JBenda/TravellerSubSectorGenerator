#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include <string>

class Text : public sf::Drawable, public sf::Transformable{
public:
  Text() = default;
  Text(const std::string& str);
  Text(const std::string& str, const sf::Font& font, int size);
  void setString(const std::string& str);
  void setFillColor(const sf::Color& color);
  void setFontSize(int size);
  void setFont(const sf::Font* font);
  void setFont(const sf::Font& font) { setFont(&font); }
  /**
   * @brief set Text width. Insert new line when text exceeds the limit.
   * @param width new width limit
   */
  void setWidth(float width);
  float getHeight() const;
  sf::Rect<float> getBoundingBox() const;

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
  void updateGeometrie() const;
  std::string m_text;
  const sf::Font* m_font = nullptr;
  int m_fontSize = 14;
  float m_textWidth = 50; ///<< Text tile width for line break. 0 = no line wrapping
  mutable uint64_t m_fontTextureId = 0;
  sf::Color m_color = sf::Color::Magenta;
  mutable sf::Rect<float> m_boundingBox;
  mutable sf::VertexArray m_vertices{sf::PrimitiveType::Triangles};
  mutable bool m_needUpdate = false; ///<< updates vertices by next draw call
};
