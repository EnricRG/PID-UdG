#ifndef ANGLE_H
#define ANGLE_H

static const double PI = 3.14159265358979323846; /**< PI constant.*/

static const double DEG_TO_RAD_CONVERSION_FACTOR = PI / 180; /**< Conversion factor to convert from degrees to radians.*/
static const double RAD_TO_DEG_CONVERSION_FACOTR = 180 / PI; /**< Conversion factor to convert from radians to degrees.*/

static const int NO_CONVERSION = 0; /**< A conversion type with this value means basically there is no conversion.*/
static const int DEGS_TO_RADS = 1;	/**< A conversion type with this value means that the angle has been instantiated with degrees but converted to radians.*/
static const int RADS_TO_DEGS = 2;	/**< A conversion type with this value means that the angle has been instantiated with radians but converted to degrees.*/

static const int UNESPECIFIED = NO_CONVERSION;	/**< No unit for the angle is specified.*/
static const int RADS = DEGS_TO_RADS;			/**< The angle's units are radians.*/
static const int DEGS = RADS_TO_DEGS;			/**< The angle's unit are degrees.*/

/// @brief Struct that stores an angle.
/**
*	This struct can sotre an angle in different units: degrees, radians or unspecified. If you use degrees or radians, conversions can be made between them.
*/
struct Angle {
	float start, 			/**< Starting angle.*/
		  delta; 		 	/**< Difference between the starting point and end point of the angle.*/
	int units; 				/**< Angle's units.*/

	/** Default constructor of Angle.
	*/
	Angle() { start = 0; delta = 0; units = NO_CONVERSION; }
	
	/** Parametric constructor of Angle. Allows you to convert the angle's units when instantiated.
	*	@param start Starting angle.
	*	@param delta Difference between the starting point and end point of the angle.
	*	@param conversion_type Type of converion.
	*/
	Angle(float start, float delta, int conversion_type) {
		this->start = start;
		this->delta = delta;
		this->units = conversion_type;
		convertThis(conversion_type);
	}

	/** Converts an angle given the conversion factor. It's basically a multiplication.
	*	@param angle Numeric angle to be converted.
	*	@param conversion_factor Conversion factor.
	*	@return The conversion for @p angle.
	*/
	float convert(float angle, float conversion_factor) {
		return angle * conversion_factor;
	}

	/** Given the conversion factor, converts *this Angle (the angle that calls the method).
	*	@param conversion_type Conversion type applied on the conversion.
	*/
	void convertThis(int conversion_type) {
		switch (conversion_type) {
			case DEGS_TO_RADS:
				start = convert(start, DEG_TO_RAD_CONVERSION_FACTOR);
				delta = convert(delta, DEG_TO_RAD_CONVERSION_FACTOR);
				break;
			case RADS_TO_DEGS:
				start = convert(start, RAD_TO_DEG_CONVERSION_FACOTR);
				delta = convert(delta, RAD_TO_DEG_CONVERSION_FACOTR);
				break;
			default:
				break;
		}
	}

	/** Makes a reverse conversion of the angle. If it was set in degrees, will convert it to radians and viceversa.
	*/
	void reverseConversion() {
		switch (units) {
		case RADS:
			convertThis(RADS_TO_DEGS);
			break;
		case DEGS:
			convertThis(DEGS_TO_RADS);
			break;
		default: 
			break;
		}
	}

	//note that this operators work even if the conversion types are different. Be careful if you use them.
	/** Operator that defines the addition operation between two angles.
	*	@param a The other angle.
	*/
	Angle operator+(const Angle & a) { return Angle((start > a.start) ? a.start : start, delta + a.delta, NO_CONVERSION); }
	
	/** Operator that defines the subtraction operation between two angles.
	*	@param a The other angle.
	*/
	Angle operator-(const Angle & a) { return Angle((start > a.start) ? a.start : start, delta - a.delta, NO_CONVERSION); }
};

#endif