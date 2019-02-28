#ifndef IMAGE_H
#define IMAGE_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>

/// @brief Struct that holds the information of an Allegro bitmap to be represented on the Window.
struct Image {
	ALLEGRO_BITMAP* image; 	/**< Bitmap containing the information of the image.*/

	//Image initialization attributes
	std::string imagePath;	/**< Path from where the image has been loaded. If the image has been copied from another image, the path will be the empty string.*/

	/** Default constructor. Because the path of the file containing the image is not specified, it creates an invalid image.*/
	Image() { init(""); } //Invalid image
	
	/** Parametric constructor of the class. Creates an image loading it from a file.
	*	@param image_path Path from where the image will be loaded.
	*/
	Image(std::string image_path) { init(image_path); }
	
	/** Parametric constructor of the class. Creates an image given the bitmap that will store.
	*	@param bitmap Bitmap of the image.
	*/
	Image(ALLEGRO_BITMAP * bitmap) { init(bitmap); }
	
	/** Destructor of the struct.*/
	~Image() { destroy(); }

	/** Copy constructor. Given an Image, creates a clone of it.
	*	@param i Reference image.
	*/
	Image(const Image & i) { copy(i); }
	
	/** Assignment operator. 
	*	@param i Reference image to be copied.
	*/
	Image& operator=(const Image & i) {
		if (this != &i) {
			destroy();
			copy(i);
		}
		return *this;
	}

	/** @return The width of the image in pixels. */
	int width() const{
		if(isValid()) return al_get_bitmap_width(image);
		else return 0;
	}

	/** @return The height of the image in pixels. */
	int height() const {
		if (isValid()) return al_get_bitmap_height(image);
		else return 0;
	}

	/** @return @a true if it's a valid image (successfully loaded), @a false otherwise. */
	bool isValid() const { return image != NULL; }
	
	/** @return @a true if it's an invalid image (unsuccessfully loaded), @a false otherwise. */
	bool isInvalid() const { return !isValid(); }

	/** Initializes the Image given a file path from where the image will be loaded.
	*	@param image_path Path of the image.
	*/
	void init(std::string image_path) {
		this->imagePath = image_path;
		if (imagePath != "") image = al_load_bitmap(imagePath.c_str());
		else image = NULL;
	}

	/** Initializes the Image given an Allegro bitmap that will be cloned.
	*	@param bitmap Allegro bitmap.
	*/
	void init(ALLEGRO_BITMAP * bitmap) {
		image = al_clone_bitmap(bitmap);
		imagePath = "";
	}

	/** Releases the dynamically allocated memory of the struct. */
	void destroy() {
		al_destroy_bitmap(image);
		image = NULL;
	}

	/** Copies the information of @p i into this Image, creating a clone.
	*	@param i Copied Image.
	*/
	void copy(const Image & i) {
		if (i.isValid()) {
			image = al_clone_bitmap(i.image);
			imagePath = i.imagePath;
		}
		else init(i.imagePath);
	}
};

#endif