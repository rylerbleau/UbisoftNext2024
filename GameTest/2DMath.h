#ifndef MATH_H
#define MATH_H

#include <iostream>

namespace MATH{


	
	#ifndef VERY_SMALL				// to avoid dividing by 0
	#define VERY_SMALL 1.0e-7f
	#endif

	#ifndef PI
	#define PI 3.14159265f
	#endif

	#ifndef DEGREES_TO_RADIANS
	#define DEGREES_TO_RADIANS (PI / 180.0f)
	#endif	

	#ifndef RADIANS_TO_DEGREES
	#define RADIANS_TO_DEGREES (180.0f / PI)
	#endif

	struct Vec2 {
		float x;
		float y;

		void set(float x_, float y_) {
			x = x_;
			y = y_;
		}

		inline void print(const char* comment = nullptr) const {
			if (comment) printf("%s: ", comment);
			printf("%f, %f\n", x, y);
		}

		// constructors ------------------------------------------------//

		inline Vec2() { set(0.0f, 0.0f); }
		inline Vec2(float x_, float y_) { set(x_, y_); }
		inline Vec2(const Vec2& v_) { set(v_.x, v_.y); }
	

		// operator overloads ------------------------------------------//

		inline const Vec2 operator + (const Vec2& v_) const {
			return Vec2(x + v_.x, y + v_.y);
		}

		inline const Vec2 operator - (const Vec2& v_) const {
			return Vec2(x - v_.x, y - v_.y);
		}

		inline const Vec2 operator * (const float f) const {
			return Vec2(f * x, f * y);
		}

		inline const Vec2 operator / (const float f) const {
			if (abs(f) < VERY_SMALL) {
				// divide by zero
				return *this;
			}
			return Vec2(x / f, y / f);
		}

		inline Vec2& operator = (const Vec2& v_) {
			set(v_.x, v_.y);
			return *this;
		}

		inline Vec2& operator += (const Vec2& v_) {
			x += v_.x;
			y += v_.y;
			return *this;
		}

		inline Vec2& operator -= (const Vec2& v_) {
			x -= v_.x;
			y -= v_.y;
			return *this;
		}

		inline Vec2& operator *=(const float f) {
			x *= f;
			y *= f;
			return *this;
		}

		inline const Vec2 operator - () const {
			return Vec2(-x, -y);
		}

		// Vec2 Math --------------------------------------------------//

		inline static float dot(const Vec2& a, const Vec2& b) {
			return(a.x * b.x + a.y * b.y);
		}

		inline static float mag(const Vec2& a) {
			return(sqrt(a.x * a.x + a.y * a.y));
		}

		inline static Vec2 normalize(const Vec2& a) {
			float mag = sqrt(a.x * a.x + a.y * a.y);
			if (mag < VERY_SMALL) {
				// divide by zero
				return a;
			}
			return Vec2(a.x / mag, a.y / mag);
		}

		static float distance(const Vec2& a, const Vec2& b) {
			Vec2 d = a - b;
			return(mag(d));
		}

		static Vec2 lerp(const Vec2 &a, const Vec2 &b, float t){	//  0 <= t <= 1
			return (a + ((b - a) * t));
		}
	};

	// Line ----------------------------------------------------------------//

	struct Line {
		Vec2 start;
		Vec2 end;
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
	};

	// Mat2 -----------------------------------------------------------------------//

	struct Mat2 {
		float AA; float AB;
		float BA; float BB;

		void set(float AA_, float AB_, float BA_, float BB_ ) {
			AA = AA_;
			AB = AB_;
			BA = BA_;
			BB = BB_;
		}
		
		inline Mat2() { set(1.0f, 0.0f, 0.0f, 1.0f); }		// identity
		inline Mat2(float AA_, float AB_, float BA_, float BB_) { set(AA_, AB_, BA_, BB_); }
		inline Mat2(const Mat2& m_) { set(m_.AA, m_.AB, m_.BA, m_.BB); }


		// overloads ------------------------------------------------------------------//
		inline const Vec2 operator * (const Vec2 &v) const {
			return Vec2(AA * v.x + AB * v.y, BA * v.x + BB * v.y);
		}

		// math -----------------------------------------------------------------------//

		inline static Vec2 RotateAround2D(const float angleInDegrees, const Vec2& v_) {
			float angleInRad = angleInDegrees * DEGREES_TO_RADIANS;
			Mat2 rotation = Mat2(cos(angleInRad), -sin(angleInRad), sin(angleInRad), cos(angleInRad));
			return rotation * v_;
		}

		inline static Mat2 RotationMatrix2D(const float angleInDegrees) {
			float angleInRad = angleInDegrees * DEGREES_TO_RADIANS;
			return Mat2(cos(angleInRad), -sin(angleInRad), sin(angleInRad), cos(angleInRad));
			
		}
	};

	
}


using namespace MATH;

namespace COLLISIONS {

	inline static bool PointCircle() {

	}


}




#endif MATH_H