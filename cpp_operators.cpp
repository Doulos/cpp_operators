/*
 * This code is from an article with the title **C++ Operators** found on the Doulos website under KnowHow.
 *
 * This C++ source illustrates the use of C++ operators.
 *
 */
static_assert( __cplusplus >= 201402L, "C++14 required" ); //< Due to use of std::exchange
#include <iostream>
#include <utility>
#include <cmath>

struct Coord // 2-dimensional Cartesian coordinates
{
  // Constructors
  Coord( void ) = default;
  Coord( double x, double y ): m_x(x), m_y(y) {}
  // Because we are illustrating assignment, we need to obey the rule of 5
  Coord( const Coord& rhs ) : m_x{ rhs.m_x }, m_y{ rhs.m_y } {}
  Coord( Coord&& rhs ) noexcept
  : m_x{ std::exchange(rhs.m_x,std::nan("")) }
  , m_y{ std::exchange(rhs.m_y,std::nan("")) }
  {}
  // Accessors
  double& x( void ) { return m_x; }
  double& y( void ) { return m_y; }
  // Copy assignment
  Coord& operator=( const Coord& rhs ) {
    if( this != &rhs ) {
      m_x = rhs.m_x;
      m_y = rhs.m_y;
    }
    return *this;
  }
  // Move assignment
  Coord& operator=( Coord&& rhs ) {
    if( this != &rhs ) {
      m_x = std::exchange(rhs.m_x,std::nan(""));
      m_y = std::exchange(rhs.m_y,std::nan(""));
    }
    return *this;
  }
  // Arithmetic
  Coord& operator+=( const Coord& rhs ) {
    m_x += rhs.m_x;
    m_y += rhs.m_y;
    return *this;
  }
  Coord  operator+( const Coord& rhs ) const { return Coord{*this} += rhs; }
  Coord  operator+( void ) const { return *this; } // Unary +
  Coord  operator-( void ) const { return Coord{-m_x, -m_y }; } // Unary -
  Coord& operator-=( const Coord& rhs ) {
    *this += -rhs;
    return *this;
  }
  Coord  operator-( const Coord& rhs ) const { return Coord{*this} -= rhs; } // Subtract
  Coord& operator*=( double rhs ) {
    m_x *= rhs;
    m_y *= rhs;
    return *this;
  }
  Coord  operator*( double rhs ) const { return Coord{*this} *= rhs; }
  friend Coord  operator*( double lhs, const Coord& rhs ) {
    return rhs * lhs;
  }
  Coord& operator/=( double rhs ) {
    m_x /= rhs;
    m_y /= rhs;
    return *this;
  }
  Coord  operator/( double rhs ) const { return Coord{*this} /= rhs; }
  // Comparison
  bool operator==( const Coord& rhs ) const {
    return m_x == rhs.m_x && m_y == rhs.m_y; 
  }
  bool operator!=( const Coord &rhs ) const { 
    return !(*this == rhs); }
  bool operator< ( const Coord& rhs ) const { 
    return (rhs.m_x - m_x) < (m_y - rhs.m_y); 
  }
  bool operator<=( const Coord &rhs ) const { 
    return (*this == rhs) || (*this < rhs); 
  }
  bool operator>=( const Coord &rhs ) const { 
    return !(*this < rhs); 
  }
  bool operator> ( const Coord &rhs ) const { 
    return !(*this <= rhs); 
  }
  Coord& operator++() { m_x += 1.0; m_y += 1.0; return *this; }
  Coord& operator++(int) { auto previous{*this}; m_x += 1.0; m_y += 1.0; return previous; }
  friend std::ostream& operator<<( std::ostream& os, const Coord& rhs ) {
    os << "Coord{ " << rhs.m_x << ", " << rhs.m_y << " }";
    return os;
  }
private:
  double m_x, m_y;
};

#define SHOW(expr) std::cout << #expr << " = " << (expr) << '\n'

int main()
{
  Coord c1{1.0,2.0}, c2{3.0,4.0}, c3{};
  SHOW( c1 );
  SHOW( c2 );
  SHOW( c3 );
  
  SHOW( c3 = c1 + c2);
  SHOW( c3 );
  SHOW( ++c2 );
  SHOW( c3++ );
  SHOW( c1-c2 );
  SHOW( c1 += c3 );
  SHOW( 3*c1 );
  SHOW( c1*3 );
  SHOW( (c2 += Coord{5.0,6.0}) );

  return 0;
}
