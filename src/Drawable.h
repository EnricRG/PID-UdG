#ifndef DRAWABLE_H
#define DRAWABLE_H

#ifdef BUILD_DLL
#define DLL_EXPORT  
#else
#define DLL_EXPORT  
#endif

class Window; //forward declaration to avoid circular references when compiling

//interface Drawable

/// @brief Abstract class representing an interface of a Drawable object.
/**
*	A drawable object is one that can draw on a Window
*/
class Drawable
{
public:

	/** Default constructor.
	*/
	Drawable() {};
	
	/** Virtual Destructor.
	*/
	virtual ~Drawable() {}
	
	/** Pure virtual method that forbids this class to be instantiated, making it abstract. This method is called to draw what the object wants to.
	*	@param w Target Window to draw on.
	*/
	virtual void draw(Window & w) = 0;
};

#endif
